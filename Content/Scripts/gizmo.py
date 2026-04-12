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
from unreal_engine.enums import EComponentMobility, ECollisionChannel
from unreal_engine import FVector, FRotator, FTransform
import os, math
from unreal_engine_tools import get_world

world = get_world()

# ── crash log ──────────────────────────────────────────────────────────────
DESKTOP   = os.path.join(os.path.expanduser("~"), "Desktop")
_log_file = open(os.path.join(DESKTOP, "gizmo_crash_log.txt"), "w", buffering=1)

def _log(msg):
    ue.log_warning(msg)
    _log_file.write(msg + "\n")

# ── mesh paths  (BasicShapes – always have collision) ──────────────────────
SH_CONE = '/Engine/BasicShapes/Cone'
SH_CYL  = '/Engine/BasicShapes/Cylinder'
SH_CUBE = '/Engine/BasicShapes/Cube'
M_COLOR = '/Game/Materials/M_Color.M_Color'

_O = FVector(0, 0, 0)

# ── rotation helper ────────────────────────────────────────────────────────
# BasicShapes Cone and Cylinder are both authored along +Z.
# _rot(axis) returns the FRotator that makes the +Z axis point along *axis*.
# This is identical to the test_cylinder pattern in main.py.
def _rot(axis):
    r = KismetMathLibrary.FindLookAtRotation(_O, axis)
    r.pitch += 90
    return r

# ── axis / plane tables ────────────────────────────────────────────────────
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

# ── colour / hover state ───────────────────────────────────────────────────
_actor_mid    = {}   # actor → MID
_actor_colors = {}   # actor → (r, g, b, emissive)
_piece_off    = {}   # actor → FVector offset from target centre (world-space)

def _set_color(a, r, g, b, em):
    mid = _actor_mid.get(a)
    if not mid: return
    try: mid.set_material_vector_parameter('Color', ue.FVector(r, g, b))
    except: pass
    try: mid.set_material_scalar_parameter('Emissive Multiplier', em)
    except: pass

def _apply_color(a, r, g, b, em=2.0):
    try:
        mat = ue.load_object(Material, M_COLOR)
        mid = a.StaticMeshComponent.create_material_instance_dynamic(mat)
        a.StaticMeshComponent.set_material(0, mid)
        _actor_mid[a]    = mid
        _actor_colors[a] = (r, g, b, em)
        _set_color(a, r, g, b, em)
    except Exception as e:
        _log(f"color fail: {e}")

def _hover_enter(a):
    if a in _actor_colors:
        r, g, b, e = _actor_colors[a]
        _set_color(a, min(r+0.5, 1), min(g+0.5, 1), min(b+0.5, 1), e * 5)

def _hover_exit(a):
    if a in _actor_colors:
        _set_color(a, *_actor_colors[a])

# ── spawn helper ───────────────────────────────────────────────────────────
def _spawn(path, loc, rot, sc, label, offset):
    """Spawn one BasicShape actor, record its offset from target."""
    mesh = ue.load_object(StaticMesh, path)
    if not mesh:
        _log(f"MISSING: {path}")
        return None
    a = world.actor_spawn(StaticMeshActor)
    smc = a.StaticMeshComponent
    smc.SetStaticMesh(mesh)
    smc.Mobility = EComponentMobility.Movable
    a.SetActorEnableCollision(True)
    a.set_actor_transform(FTransform(loc, rot, sc))
    a.set_actor_label(label)
    _piece_off[a] = offset
    return a

# ── build ──────────────────────────────────────────────────────────────────
def test_gizmos():
    """
    Spawn demo cylinder + full gizmo.
    Returns (target, gizmo_root, handles).
    gizmo_root is a dummy actor (not used for parenting).
    handles: actor → (kind, data)
    """
    _log("=== test_gizmos ===")
    _piece_off.clear()
    _actor_mid.clear()
    _actor_colors.clear()

    # target cylinder
    target = world.actor_spawn(StaticMeshActor)
    target.StaticMeshComponent.SetStaticMesh(
        ue.load_object(StaticMesh, '/Engine/BasicShapes/Cylinder'))
    target.StaticMeshComponent.Mobility = EComponentMobility.Movable
    target.set_actor_transform(
        FTransform(FVector(0, 0, 100), FRotator(0, 0, 0), FVector(0.5, 0.5, 1.0)))
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

# ── interaction ────────────────────────────────────────────────────────────
_st = {
    'down': False, 'drag': False,
    'kind': None,  'data': None,
    'loc0': None,  'rot0': None, 'scl0': None,
    'hit0': None,  'off0': None,
    'hov':  None,
}

def setup_gizmo_interaction(uobject, input_manager, target, gizmo_root, handles):
    """Returns on_tick(dt) callable for Main.tick()."""
    all_actors = set(handles.keys()) | {target}

    def _press():   _st['down'] = True
    def _release():
        _st['down'] = False
        if _st['drag']:
            _st['drag'] = False
            _log(f"Drag end pos={target.get_actor_location()}")

    input_manager.bind_press("LeftMouseButton",   _press)
    input_manager.bind_release("LeftMouseButton", _release)
    _log("Interaction ready")

    def on_tick(delta_time):
        # ── reposition every gizmo piece to follow the target ──────────
        tgt = target.get_actor_location()
        for actor, off in _piece_off.items():
            actor.set_actor_location(tgt + off)

        # ── cursor trace ───────────────────────────────────────────────
        hit       = uobject.get_hit_result_under_cursor(ECollisionChannel.ECC_Visibility)
        hit_actor = hit.actor if hit else None
        on_gizmo  = hit_actor in all_actors

        # hover
        new_hov = hit_actor if on_gizmo else None
        if new_hov != _st['hov']:
            if _st['hov']: _hover_exit(_st['hov'])
            if new_hov:    _hover_enter(new_hov)
            _st['hov'] = new_hov

        # drag start
        if on_gizmo and _st['down'] and not _st['drag'] and hit:
            kind, data = handles.get(hit_actor, ('free', None))
            _st.update({
                'drag': True, 'kind': kind, 'data': data,
                'loc0': target.get_actor_location(),
                'rot0': target.get_actor_rotation(),
                'scl0': target.GetActorScale3D(),
                'hit0': hit.impact_point,
                'off0': hit.impact_point - target.get_actor_location(),
            })
            _log(f"Drag start: {kind} on {hit_actor.get_name()}")

        # drag update
        if _st['drag'] and _st['down'] and hit:
            cur  = hit.impact_point
            loc0 = _st['loc0']
            rot0 = _st['rot0']
            hit0 = _st['hit0']
            kind = _st['kind']
            data = _st['data']

            if kind == 'free':
                target.set_actor_location(cur - _st['off0'])

            elif kind == 'axis':
                ax   = data
                diff = cur - loc0
                t    = diff.x*ax.x + diff.y*ax.y + diff.z*ax.z
                target.set_actor_location(loc0 + ax * t)

            elif kind == 'plane':
                d1, d2 = data
                diff   = cur - loc0
                t1 = diff.x*d1.x + diff.y*d1.y + diff.z*d1.z
                t2 = diff.x*d2.x + diff.y*d2.y + diff.z*d2.z
                target.set_actor_location(loc0 + d1*t1 + d2*t2)

            elif kind == 'rotate':
                nrm = data
                v1  = hit0 - loc0
                v2  = cur  - loc0
                # flatten onto the ring plane
                d1 = v1.x*nrm.x + v1.y*nrm.y + v1.z*nrm.z
                d2 = v2.x*nrm.x + v2.y*nrm.y + v2.z*nrm.z
                v1 = FVector(v1.x-nrm.x*d1, v1.y-nrm.y*d1, v1.z-nrm.z*d1)
                v2 = FVector(v2.x-nrm.x*d2, v2.y-nrm.y*d2, v2.z-nrm.z*d2)
                l1 = math.sqrt(v1.x**2+v1.y**2+v1.z**2)
                l2 = math.sqrt(v2.x**2+v2.y**2+v2.z**2)
                if l1 > 0.1 and l2 > 0.1:
                    v1 = FVector(v1.x/l1, v1.y/l1, v1.z/l1)
                    v2 = FVector(v2.x/l2, v2.y/l2, v2.z/l2)
                    dot = max(-1.0, min(1.0, v1.x*v2.x+v1.y*v2.y+v1.z*v2.z))
                    cx = v1.y*v2.z-v1.z*v2.y
                    cy = v1.z*v2.x-v1.x*v2.z
                    cz = v1.x*v2.y-v1.y*v2.x
                    sgn = 1.0 if cx*nrm.x+cy*nrm.y+cz*nrm.z > 0 else -1.0
                    ang = math.degrees(math.acos(dot)) * sgn
                    target.set_actor_rotation(FRotator(
                        rot0.roll  + nrm.x * ang,
                        rot0.pitch + nrm.y * ang,
                        rot0.yaw   + nrm.z * ang,
                    ))

            elif kind == 'scale':
                ax    = data
                diff  = cur - hit0
                # Project movement onto handle axis. abs() so both +X and -X
                # handles increase scale.x when pulled away from centre.
                delta = (diff.x*ax.x + diff.y*ax.y + diff.z*ax.z) * 0.01
                s     = _st['scl0']
                target.SetActorScale3D(FVector(
                    max(0.05, s.x + abs(ax.x) * delta),
                    max(0.05, s.y + abs(ax.y) * delta),
                    max(0.05, s.z + abs(ax.z) * delta),
                ))

        if _st['drag'] and not _st['down']:
            _st['drag'] = False

    return on_tick
