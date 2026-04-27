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
from unreal_engine_tools import get_world, apply_material

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
M_COLOR = '/Game/Materials/M_TranslucentTransformGizmoMaterial.M_TranslucentTransformGizmoMaterial'

ORIGIN = FVector(0, 0, 0)

# rotation helper
# BasicShapes Cone and Cylinder are both authored along +Z (cone apex at +Z,
# pivot at base center). _rot(axis) returns the FRotator that makes the +Z
# mesh axis point along *axis* in world space.
#
# FindLookAtRotation aims local +X at *axis*; subtracting 90° pitch then
# remaps local +Z (the cone tip) to where +X was, i.e. along *axis*.
#
# Roll wipe: FindLookAtRotation hits a degenerate case when *axis* is exactly
# world-up (+Z). MakeFromX falls back to UpVector=(1,0,0), which makes the
# decomposed rotator come out as FRotator(90, 0, 180) — that 180° of roll
# survives `pitch -= 90` and rolls the +Z cone upside-down (wide base on top).
# The other five cardinal axes (incl. -Z) get roll=0 from FindLookAtRotation
# already, so zeroing roll only affects the +Z case.
def _rot(axis):
    r = KismetMathLibrary.FindLookAtRotation(ORIGIN, axis)
    r.pitch -= 90
    r.roll  = 0
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

# bounding box — 8 corners, 12 edges (each edge stored as (axis_idx, dj, dk))
# dj/dk are ±1 positions along the two axes perpendicular to axis_idx.
BBOX_CORNERS = [(dx, dy, dz)
                for dx in (-1, 1)
                for dy in (-1, 1)
                for dz in (-1, 1)]
BBOX_EDGES = [(ai, dj, dk)
              for ai in (0, 1, 2)
              for dj in (-1, 1)
              for dk in (-1, 1)]
BBOX_LOCAL_EXTENT = 50.0  # BasicShapes half-extent; multiplied by actor scale

# colour / hover state
_actor_mid    = {}   # actor → MID
_actor_colors = {}   # actor → (r, g, b, emissive)
_piece_off    = {}   # actor → FVector offset from target centre (world-space)
_bbox_dynamic = {}   # actor → ('corner',(dx,dy,dz)) | ('edge',ai,dj,dk) | ('wire',ai,dj,dk) | ('bracket',(dx,dy,dz,seg_axis))
_hover_groups = {}   # actor → list of sibling actors that hover/unhover together (e.g. the 3 segments of one L-bracket)

def _set_color(actor, red, green, blue, emissive):
    mid = _actor_mid.get(actor)
    if not mid: return
    try: mid.set_material_vector_parameter('Color', ue.FVector(red, green, blue))
    except: pass
    try: mid.set_material_scalar_parameter('Emissive Multiplier', emissive)
    except: pass

def _apply_color(actor, red, green, blue, emissive=2.0, opacity=0.8):
    # Delegate to unreal_engine_tools.apply_material so the gizmo uses the
    # same material-loading + MID-creation path as the rest of the project.
    try:
        mid = apply_material(
            actor=actor,
            material_path=M_COLOR,
            params={
                'Color':              (red, green, blue),
                'Emissive Multiplier': emissive,
                'Opacity':             opacity,
            },
        )
        _actor_mid[actor]    = mid
        _actor_colors[actor] = (red, green, blue, emissive)
    except Exception as e:
        _log(f"color fail: {e}")

def _hover_enter(actor):
    for t in _hover_groups.get(actor, [actor]):
        if t in _actor_colors:
            red, green, blue, emissive = _actor_colors[t]
            _set_color(t, min(red+0.5, 1), min(green+0.5, 1), min(blue+0.5, 1), emissive * 5)

def _hover_exit(actor):
    for t in _hover_groups.get(actor, [actor]):
        if t in _actor_colors:
            _set_color(t, *_actor_colors[t])

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

# bbox helpers
def _component(v, i):
    return v.x if i == 0 else (v.y if i == 1 else v.z)

def _vec_from_components(c0, c1, c2):
    return FVector(c0, c1, c2)

def _query_local_extent(target):
    """Local-space half-extent of the target's static mesh, in mesh units
    (before actor scale or rotation). Falls back to BBOX_LOCAL_EXTENT for
    a basic 100uu shape if the mesh's bounds can't be read."""
    try:
        smc = target.StaticMeshComponent
        result = smc.GetLocalBounds()
        if result is not None and len(result) >= 2:
            mn, mx = result[0], result[1]
            return FVector((mx.x - mn.x) * 0.5,
                           (mx.y - mn.y) * 0.5,
                           (mx.z - mn.z) * 0.5)
    except Exception as e:
        _log(f"GetLocalBounds fail, falling back to AABB: {e}")
    # Fallback: world AABB / scale (correct when rotation == identity, which
    # is true at spawn time when this is first called and cached).
    try:
        scale = target.GetActorScale3D()
        _, world_extent = target.GetActorBounds()
        return FVector(world_extent.x / max(0.001, scale.x),
                       world_extent.y / max(0.001, scale.y),
                       world_extent.z / max(0.001, scale.z))
    except Exception as e:
        _log(f"GetActorBounds fail, using default: {e}")
    return FVector(BBOX_LOCAL_EXTENT, BBOX_LOCAL_EXTENT, BBOX_LOCAL_EXTENT)

_local_extent_cache = {}   # target actor → cached local half-extent FVector

def local_half_extent(target):
    """Cached local half-extent. Memoized in a module-level dict — querying
    the mesh bounds each tick would waste a lookup, and the local mesh
    doesn't change when the actor is scaled or rotated. Keyed on the actor
    itself (UEPython wrappers are hashable)."""
    cached = _local_extent_cache.get(target)
    if cached is None:
        cached = _query_local_extent(target)
        _local_extent_cache[target] = cached
    return cached

def bbox_world_half_extent(target):
    """Half-extent of the target's oriented bbox (local-axis aligned),
    pre-rotation. Scaled by actor scale."""
    try:
        s = target.GetActorScale3D()
    except Exception:
        s = target.get_actor_scale()
    le = local_half_extent(target)
    return FVector(le.x * s.x, le.y * s.y, le.z * s.z)

def _rotate_local(rotation, local_vec):
    # FRotator * FVector → FRotator::RotateVector via UEPython's nb_multiply.
    # Avoids KismetMathLibrary.Quat_RotateVector — UEPython's UFUNCTION arg
    # converter has no FQuat→Q branch, so that path errors every tick.
    return rotation * local_vec

def bbox_piece_world_transform(target, kind, data):
    """Return (world_loc, world_rot, world_scale) for a dynamic bbox piece."""
    loc  = target.get_actor_location()
    rot  = target.get_actor_rotation()
    h    = bbox_world_half_extent(target)

    if kind == 'corner':
        dx, dy, dz = data
        local_off = FVector(dx * h.x, dy * h.y, dz * h.z)
        world_off = _rotate_local(rot, local_off)
        return (loc + world_off, rot, FVector(0.20, 0.20, 0.20))

    if kind == 'edge':
        ai, dj, dk = data
        others = [i for i in (0, 1, 2) if i != ai]
        comps  = [0.0, 0.0, 0.0]
        comps[others[0]] = dj * _component(h, others[0])
        comps[others[1]] = dk * _component(h, others[1])
        local_off = _vec_from_components(*comps)
        world_off = _rotate_local(rot, local_off)
        return (loc + world_off, rot, FVector(0.16, 0.16, 0.16))

    if kind == 'wire':
        ai, dj, dk = data
        others = [i for i in (0, 1, 2) if i != ai]
        comps  = [0.0, 0.0, 0.0]
        comps[others[0]] = dj * _component(h, others[0])
        comps[others[1]] = dk * _component(h, others[1])
        local_off = _vec_from_components(*comps)
        world_off = _rotate_local(rot, local_off)
        axis_vec   = [FVector(1,0,0), FVector(0,1,0), FVector(0,0,1)][ai]
        axis_rot   = _rot(axis_vec)
        combined   = KismetMathLibrary.ComposeRotators(axis_rot, rot)
        length     = 2.0 * _component(h, ai)
        return (loc + world_off, combined,
                FVector(0.03, 0.03, length / 100.0))

    if kind == 'bracket':
        # One leg of an L-shape at corner (dx,dy,dz). The leg lies along local
        # axis seg_axis and runs from the corner inward (toward the box center)
        # for ~25% of that edge's length.
        dx, dy, dz, seg_axis = data
        corner_signs = (dx, dy, dz)
        h_seg        = _component(h, seg_axis)
        seg_length   = 0.5 * h_seg            # 25% of the full edge (2 * h_seg)
        seg_half     = 0.5 * seg_length

        comps = [corner_signs[i] * _component(h, i) for i in (0, 1, 2)]
        # Pull the seg_axis component inward by half the segment length so the
        # cylinder's far tip sits exactly on the corner.
        comps[seg_axis] = corner_signs[seg_axis] * (h_seg - seg_half)

        local_off = _vec_from_components(*comps)
        world_off = _rotate_local(rot, local_off)

        axis_vec  = [FVector(1,0,0), FVector(0,1,0), FVector(0,0,1)][seg_axis]
        axis_rot  = _rot(axis_vec)
        combined  = KismetMathLibrary.ComposeRotators(axis_rot, rot)

        return (loc + world_off, combined,
                FVector(0.06, 0.06, seg_length / 100.0))

    return (loc, rot, FVector(1, 1, 1))

def update_bbox_piece(actor, target):
    """Reposition + re-orient + re-scale a bbox piece to follow target."""
    spec = _bbox_dynamic.get(actor)
    if not spec:
        return
    kind, data = spec
    try:
        wloc, wrot, wscale = bbox_piece_world_transform(target, kind, data)
        actor.set_actor_transform(FTransform(wloc, wrot, wscale))
    except Exception as e:
        _log(f"bbox update fail: {e}")

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
    _bbox_dynamic.clear()
    _hover_groups.clear()
    _local_extent_cache.clear()

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
    #
    # All three rings are translucent and intersect at the center, so
    # translucent sorting between them is otherwise undefined → z-fight.
    # Assigning each a unique TranslucencySortPriority makes the draw order
    # deterministic (higher = drawn later = appears on top). Rings sit above
    # the rest of the gizmo (which defaults to 0) so they stay readable when
    # the camera puts an arrow in front of a ring.
    _log("-- rings --")
    for ring_idx, (name, ax, rgb) in enumerate(AXES3):
        off = FVector(0, 0, 0)
        a   = _spawn(SH_CYL, base, _rot(ax), FVector(1.8, 1.8, 0.10), f"GR_{name}", off)
        if a:
            _apply_color(a, *rgb, emissive=1.8)
            try:
                a.StaticMeshComponent.TranslucencySortPriority = 10 + ring_idx
            except Exception as e:
                _log(f"ring sort priority fail ({name}): {e}")
            handles[a] = ('rotate', ax)

    # ── scale handles  (small Cube, 175 uu along axis past arrows)
    _log("-- scale --")
    for name, ax, rgb in AXES6:
        off = ax * 175
        a   = _spawn(SH_CUBE, base + off, FRotator(0, 0, 0),
                     FVector(0.18, 0.18, 0.18), f"GS_{name}", off)
        if a:
            _apply_color(a, *rgb, emissive=1.0)
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
            _apply_color(a, *rgb, emissive=1.5)
            handles[a] = ('plane', (d1, d2))

    # ── bounding box wireframe + corner/edge handles
    # Wireframe edges are non-interactive (thin cylinders along each bbox edge).
    # Corner handles resize along all 3 local axes (opposite corner anchors).
    # Edge handles resize along the 2 perpendicular axes (opposite edge anchors).
    # Modifiers (handled in pyactor_gizmo):
    #   Ctrl  → lock aspect ratio (uniform scale)
    #   Shift → scale symmetrically from center (center stays, both sides move)
    #   Alt   → fine-grained (0.1× delta)
    _log("-- bbox --")
    for ai, dj, dk in BBOX_EDGES:
        a = _spawn(SH_CYL, base, FRotator(0, 0, 0),
                   FVector(0.03, 0.03, 0.5),
                   f"GBB_W_{ai}{dj:+d}{dk:+d}", FVector(0, 0, 0))
        if a:
            # Dim grey wireframe so the bright yellow corner brackets dominate.
            _apply_color(a, 0.45, 0.45, 0.45, emissive=0.3)
            try:
                a.SetActorEnableCollision(False)
            except Exception:
                pass
            _bbox_dynamic[a] = ('wire', (ai, dj, dk))

    # Yellow corner brackets — 3 thin cylinders per corner, each running inward
    # along one local axis (X, Y, Z) so the trio forms a 3D L-shape selection
    # marker. All 3 segments share the same bbox_corner drag and hover/unhover
    # together via _hover_groups.
    for dx, dy, dz in BBOX_CORNERS:
        seg_actors = []
        for seg_axis in (0, 1, 2):
            a = _spawn(SH_CYL, base, FRotator(0, 0, 0),
                       FVector(0.06, 0.06, 0.5),
                       f"GBB_BR_{dx:+d}{dy:+d}{dz:+d}_{seg_axis}",
                       FVector(0, 0, 0))
            if a:
                _apply_color(a, 1.00, 1.00, 0.20, emissive=1.5)
                handles[a]       = ('bbox_corner', (dx, dy, dz))
                _bbox_dynamic[a] = ('bracket', (dx, dy, dz, seg_axis))
                seg_actors.append(a)
        for a in seg_actors:
            _hover_groups[a] = seg_actors

    for ai, dj, dk in BBOX_EDGES:
        a = _spawn(SH_CUBE, base, FRotator(0, 0, 0),
                   FVector(0.16, 0.16, 0.16),
                   f"GBB_E_{ai}{dj:+d}{dk:+d}", FVector(0, 0, 0))
        if a:
            _apply_color(a, 1.00, 1.00, 0.20, emissive=0.9)
            handles[a] = ('bbox_edge', (ai, dj, dk))
            _bbox_dynamic[a] = ('edge', (ai, dj, dk))

    _log(f"=== done: {len(handles)} handles, {len(_bbox_dynamic)} bbox pieces ===")
    return target, gizmo_root, handles

# Interaction logic migrated to pyactor_gizmo.GizmoController.
# Spawn via spawn_pyactor('pyactor_gizmo', 'GizmoController') and call its
# setup(uobject, input_manager, target, handles, piece_offsets=_piece_off).
