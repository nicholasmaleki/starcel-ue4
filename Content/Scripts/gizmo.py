"""
gizmo.py  –  interactive transform gizmo, UE4.27 standalone

Uses BasicShapes ONLY (Cone, Cylinder, Cube) – they have collision built in,
so get_hit_result_under_cursor always detects them.  Imported FBX assets have
no collision profile by default so the cursor trace passes straight through.

Pieces
------
  Move   arrows   : ±X ±Y ±Z   (6 × Cone)
  Rotate rings    :  X  Y  Z   (3 × flat Cylinder)
  Scale  handles  : ±X ±Y ±Z   (6 × small Cube)
  Plane  squares  :  XY XZ YZ  (3 × flat Cube)

No attach_to_actor – each piece stores a world-space offset from the target,
updated manually every tick.  This avoids any attachment / collision side-effects.

Hover : emissive ×5 + RGB +0.5 while cursor is over a piece.
"""

import unreal_engine as ue
from unreal_engine.classes import StaticMeshActor, StaticMesh, Material, KismetMathLibrary
from unreal_engine.enums import EComponentMobility
from unreal_engine import FVector, FRotator, FTransform
import os
from unreal_engine_tools import get_world

world = get_world()

# crash log
DESKTOP   = os.path.join(os.path.expanduser("~"), "Desktop")
_log_file = open(os.path.join(DESKTOP, "gizmo_crash_log.txt"), "w", buffering=1)

def _log(msg):
    ue.log_warning(msg)
    _log_file.write(msg + "\n")

# mesh paths (BasicShapes – always have collision)
SH_CONE = '/Engine/BasicShapes/Cone'
SH_CYL  = '/Engine/BasicShapes/Cylinder'
SH_CUBE = '/Engine/BasicShapes/Cube'
M_COLOR = '/Game/Materials/M_Color.M_Color'

ORIGIN = FVector(0, 0, 0)

# rotation helper
# BasicShapes Cone and Cylinder are both authored along +Z.
# _rot(axis) returns the FRotator that makes the +Z axis point along *axis*.
# This is identical to the test_cylinder pattern in main.py.
def _rot(axis):
    r = KismetMathLibrary.FindLookAtRotation(ORIGIN, axis)
    r.pitch += 90
    return r

# axis / plane tables
AXES6 = [
    # (label,  axis_vec,              (r,    g,    b   ))
    ('X',  FVector( 1, 0, 0), (1.00, 0.10, 0.10)),
    ('Xn', FVector(-1, 0, 0), (0.70, 0.05, 0.05)),
    ('Y',  FVector( 0, 1, 0), (0.10, 1.00, 0.10)),
    ('Yn', FVector( 0,-1, 0), (0.05, 0.70, 0.05)),
    ('Z',  FVector( 0, 0, 1), (0.10, 0.30, 1.00)),
    ('Zn', FVector( 0, 0,-1), (0.05, 0.15, 0.70)),
]
AXES3 = [
    ('X', FVector(1, 0, 0), (1.00, 0.10, 0.10)),
    ('Y', FVector(0, 1, 0), (0.10, 1.00, 0.10)),
    ('Z', FVector(0, 0, 1), (0.10, 0.30, 1.00)),
]
PLANES = [
    # (label, plane_normal, (r,g,b), in-plane dir1, in-plane dir2)
    ('XY', FVector(0, 0, 1), (1.00, 1.00, 0.10), FVector(1,0,0), FVector(0,1,0)),
    ('XZ', FVector(0, 1, 0), (0.10, 1.00, 1.00), FVector(1,0,0), FVector(0,0,1)),
    ('YZ', FVector(1, 0, 0), (1.00, 0.10, 1.00), FVector(0,1,0), FVector(0,0,1)),
]

# colour / hover state
_actor_mid    = {}   # actor → MID
_actor_colors = {}   # actor → (r, g, b, emissive)
_piece_off    = {}   # actor → FVector offset from target centre (world-space)

def _set_color(actor, red, green, blue, emissive):
    mid = _actor_mid.get(actor)
    if not mid: return
    try: mid.set_material_vector_parameter('Color', ue.FVector(red, green, blue))
    except: pass
    try: mid.set_material_scalar_parameter('Emissive Multiplier', emissive)
    except: pass

def _apply_color(actor, red, green, blue, emissive=2.0):
    try:
        mat = ue.load_object(Material, M_COLOR)
        mid = actor.StaticMeshComponent.create_material_instance_dynamic(mat)
        actor.StaticMeshComponent.set_material(0, mid)
        _actor_mid[actor]    = mid
        _actor_colors[actor] = (red, green, blue, emissive)
        _set_color(actor, red, green, blue, emissive)
    except Exception as e:
        _log(f"color fail: {e}")

def _hover_enter(actor):
    if actor in _actor_colors:
        red, green, blue, emissive = _actor_colors[actor]
        _set_color(actor, min(red+0.5, 1), min(green+0.5, 1), min(blue+0.5, 1), emissive * 5)

def _hover_exit(actor):
    if actor in _actor_colors:
        _set_color(actor, *_actor_colors[actor])

# spawn helper
def _spawn(path, loc, rot, sc, label, offset):
    """Spawn one BasicShape actor, record its offset from target."""
    mesh = ue.load_object(StaticMesh, path)
    if not mesh:
        _log(f"MISSING: {path}")
        return None
    actor = world.actor_spawn(StaticMeshActor)
    smc = actor.StaticMeshComponent
    smc.SetStaticMesh(mesh)
    smc.Mobility = EComponentMobility.Movable
    actor.SetActorEnableCollision(True)
    actor.set_actor_transform(FTransform(loc, rot, sc))
    actor.set_actor_label(label)
    _piece_off[actor] = offset
    return actor

# build
def test_gizmos(location=None):
    """
    Spawn demo cylinder + full gizmo.
    Returns (target, gizmo_root, handles).
    gizmo_root is a dummy actor (not used for parenting).
    handles: actor → (kind, data)

    location — FVector spawn position for the target cylinder.
               Defaults to FVector(0, 0, 100).
    """
    _log("=== test_gizmos ===")
    _piece_off.clear()
    _actor_mid.clear()
    _actor_colors.clear()

    if location is None:
        location = FVector(0, 0, 100)

    # target cylinder
    target = world.actor_spawn(StaticMeshActor)
    target.StaticMeshComponent.SetStaticMesh(
        ue.load_object(StaticMesh, '/Engine/BasicShapes/Cylinder'))
    target.StaticMeshComponent.Mobility = EComponentMobility.Movable
    target.set_actor_transform(
        FTransform(location, FRotator(0, 0, 0), FVector(0.5, 0.5, 1.0)))
    target.set_actor_label("GizmoTarget")
    target.SetActorEnableCollision(True)

    # dummy root (just for API compatibility – not used for parenting)
    gizmo_root = world.actor_spawn(StaticMeshActor)
    gizmo_root.StaticMeshComponent.Mobility = EComponentMobility.Movable
    gizmo_root.set_actor_label("GizmoRoot")

    base    = target.get_actor_location()
    handles = {}

    # ── move arrows  (Cone, tip points along axis, centered 100 u from base)
    # Cone is authored along +Z (tip at top). _rot(ax) points the tip toward ax.
    # Scale (0.12, 0.12, 0.9): 12 uu wide, 90 uu tall → tip at base + ax*145
    _log("-- arrows --")
    for name, ax, rgb in AXES6:
        off = ax * 100
        a   = _spawn(SH_CONE, base + off, _rot(ax), FVector(0.12, 0.12, 0.9), f"GM_{name}", off)
        if a:
            _apply_color(a, *rgb)
            handles[a] = ('axis', ax)

    # ── rotation rings  (flat Cylinder, centered on target)
    # Cylinder authored along +Z. _rot(ax) makes the cylinder axis = ax,
    # so the flat faces lie perpendicular to ax → ring rotates around ax.
    # Scale (1.8, 1.8, 0.10): 180 uu diameter ring, 10 uu thick.
    _log("-- rings --")
    for name, ax, rgb in AXES3:
        off = FVector(0, 0, 0)
        a   = _spawn(SH_CYL, base, _rot(ax), FVector(1.8, 1.8, 0.10), f"GR_{name}", off)
        if a:
            _apply_color(a, *rgb, em=1.8)
            handles[a] = ('rotate', ax)

    # ── scale handles  (small Cube, 175 uu along axis past arrows)
    _log("-- scale --")
    for name, ax, rgb in AXES6:
        off = ax * 175
        a   = _spawn(SH_CUBE, base + off, FRotator(0, 0, 0),
                     FVector(0.18, 0.18, 0.18), f"GS_{name}", off)
        if a:
            _apply_color(a, *rgb, em=1.0)
            handles[a] = ('scale', ax)

    # ── plane handles  (flat Cube at the corner between each axis pair)
    # Scale (0.28, 0.28, 0.05): a thin square panel.
    # _rot(normal) points the cube's +Z (thin axis) toward the plane's normal,
    # so the flat face lies in the correct plane.
    _log("-- planes --")
    for pname, normal, rgb, d1, d2 in PLANES:
        off = d1 * 35 + d2 * 35
        a   = _spawn(SH_CUBE, base + off, _rot(normal),
                     FVector(0.28, 0.28, 0.05), f"GP_{pname}", off)
        if a:
            _apply_color(a, *rgb, em=1.5)
            handles[a] = ('plane', (d1, d2))

    _log(f"=== done: {len(handles)} handles ===")
    return target, gizmo_root, handles

# Interaction logic migrated to pyactor_gizmo.GizmoController.
# Spawn via spawn_pyactor('pyactor_gizmo', 'GizmoController') and call its
# setup(uobject, input_manager, target, handles, piece_offsets=_piece_off).
