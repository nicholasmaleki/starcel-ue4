import unreal_engine as ue
from unreal_engine.classes import (
    StaticMeshActor, StaticMesh, Material,
    KismetMathLibrary,
)
from unreal_engine.enums import EComponentMobility, ECollisionChannel
from unreal_engine import FVector, FRotator, FTransform, FLinearColor
import os

world = ue.get_editor_world()

DESKTOP = os.path.join(os.path.expanduser("~"), "Desktop")
_log_file = open(os.path.join(DESKTOP, "gizmo_crash_log.txt"), "w", buffering=1)

def _log(msg):
    ue.log_warning(msg)
    _log_file.write(msg + "\n")


# --- Gizmo arrow construction ---

CONE_MESH   = '/Engine/BasicShapes/Cone'
SPHERE_MESH = '/Engine/BasicShapes/Sphere'
CYL_MESH    = '/Engine/BasicShapes/Cylinder'

# Each axis: (axis_vec, rotation to point cone along axis, shaft_offset, tip_offset)
AXES = {
    'X': (FVector(1,0,0), FRotator(0, 0, -90),  FVector(50,0,0),  FVector(90,0,0),  FLinearColor(1,0,0,1)),
    'Y': (FVector(0,1,0), FRotator(0, 0,   0),  FVector(0,50,0),  FVector(0,90,0),  FLinearColor(0,1,0,1)),
    'Z': (FVector(0,0,1), FRotator(90,0,   0),  FVector(0,0,50),  FVector(0,0,90),  FLinearColor(0,0,1,1)),
}


def _spawn_arrow_actor(mesh, location, rotation, scale, label):
    a = world.actor_spawn(StaticMeshActor)
    a.StaticMeshComponent.SetStaticMesh(mesh)
    a.StaticMeshComponent.Mobility = EComponentMobility.Movable
    a.set_actor_transform(FTransform(location, rotation, scale))
    a.set_actor_label(label)
    a.SetActorEnableCollision(True)
    return a


def _project_onto_axis(point, axis_origin, axis_dir):
    """Project a world point onto an axis ray, return the projected location."""
    diff = point - axis_origin
    # dot = diff.x*axis_dir.x + diff.y*axis_dir.y + diff.z*axis_dir.z
    dot = (diff.x * axis_dir.x +
           diff.y * axis_dir.y +
           diff.z * axis_dir.z)
    return axis_origin + axis_dir * dot


def test_gizmos():
    """Spawn cylinder with visible XYZ arrow gizmo. Returns (cyl, arrows dict)."""
    cone_mesh = ue.load_object(StaticMesh, CONE_MESH)
    cyl_mesh  = ue.load_object(StaticMesh, CYL_MESH)

    # Target cylinder
    cyl = world.actor_spawn(StaticMeshActor)
    cyl.StaticMeshComponent.SetStaticMesh(cyl_mesh)
    cyl.StaticMeshComponent.Mobility = EComponentMobility.Movable
    cyl.set_actor_transform(FTransform(FVector(0, 0, 100), FRotator(0, 0, 0), FVector(0.5, 0.5, 1.0)))
    cyl.set_actor_label("GizmoTarget")
    cyl.SetActorEnableCollision(True)
    _log(f"Cylinder: {cyl}")

    # Spawn one arrow per axis: shaft (cylinder) + tip (cone), attached to cyl
    arrows = {}  # axis_name -> (shaft_actor, tip_actor, axis_vec)

    for axis_name, (axis_vec, cone_rot, shaft_offset, tip_offset, color) in AXES.items():
        base = cyl.get_actor_location()

        # Shaft
        shaft = _spawn_arrow_actor(
            cyl_mesh,
            base + shaft_offset,
            cone_rot,
            FVector(0.05, 0.05, 0.5),
            f"GizmoShaft_{axis_name}"
        )
        shaft.attach_to_actor(cyl, '', 0)

        # Tip (cone)
        tip = _spawn_arrow_actor(
            cone_mesh,
            base + tip_offset,
            cone_rot,
            FVector(0.15, 0.15, 0.15),
            f"GizmoTip_{axis_name}"
        )
        tip.attach_to_actor(cyl, '', 0)

        arrows[axis_name] = (shaft, tip, axis_vec)
        _log(f"  Arrow {axis_name}: shaft={shaft.get_name()} tip={tip.get_name()}")

    return cyl, arrows


# --- Interaction state ---
_state = {
    'mouse_down': False,
    'dragging': False,
    'drag_axis': None,       # 'X', 'Y', 'Z', or None (free)
    'drag_start_actor': None,
    'drag_start_loc': None,
    'drag_offset': None,
    'hovered': None,
}


def setup_gizmo_interaction(uobject, input_manager, cyl, arrows):
    """Tick-based hover + axis-constrained drag.

    Args:
        arrows: dict of axis_name -> (shaft_actor, tip_actor, axis_vec)
    Returns tick fn for Main.tick().
    """
    # All interactable actors -> axis name (None for the cylinder itself)
    actor_to_axis = {cyl: None}
    for axis_name, (shaft, tip, axis_vec) in arrows.items():
        actor_to_axis[shaft] = axis_name
        actor_to_axis[tip]   = axis_name

    def _on_press():
        _state['mouse_down'] = True

    def _on_release():
        _state['mouse_down'] = False
        if _state['dragging']:
            _state['dragging'] = False
            _log(f"Drag end  axis={_state['drag_axis']}  loc={cyl.get_actor_location()}")

    input_manager.bind_press("LeftMouseButton", _on_press)
    input_manager.bind_release("LeftMouseButton", _on_release)
    _log("Interaction ready")

    def on_tick(delta_time):
        hit = uobject.get_hit_result_under_cursor(ECollisionChannel.ECC_Visibility)
        hit_actor = hit.actor if hit else None
        on_target = hit_actor in actor_to_axis

        # Hover feedback
        if on_target and _state['hovered'] != hit_actor:
            _state['hovered'] = hit_actor
            axis = actor_to_axis.get(hit_actor)
            _log(f"Hover: {hit_actor.get_name()}  axis={axis}")
        elif not on_target and _state['hovered'] and not _state['dragging']:
            _state['hovered'] = None

        # Start drag
        if on_target and _state['mouse_down'] and not _state['dragging'] and hit:
            axis = actor_to_axis.get(hit_actor)
            _state['dragging'] = True
            _state['drag_axis'] = axis
            _state['drag_start_loc'] = cyl.get_actor_location()
            _state['drag_offset'] = hit.impact_point - cyl.get_actor_location()
            _log(f"Drag start  axis={axis}  hit={hit.impact_point}")

        # Drag
        if _state['dragging'] and _state['mouse_down'] and hit:
            cursor_world = hit.impact_point
            if _state['drag_axis'] is None:
                # Free drag (clicked cylinder body)
                cyl.set_actor_location(cursor_world - _state['drag_offset'])
            else:
                # Axis-constrained drag
                axis_vec = arrows[_state['drag_axis']][2]
                projected = _project_onto_axis(
                    cursor_world,
                    _state['drag_start_loc'],
                    axis_vec
                )
                cyl.set_actor_location(projected)

        # Release cleanup
        if _state['dragging'] and not _state['mouse_down']:
            _state['dragging'] = False

    return on_tick
