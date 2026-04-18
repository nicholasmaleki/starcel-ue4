"""Gridline hover/drag resize controller for UnrealTableRenderer.

Instantiated automatically when UnrealTableRenderer is created with
``enable_resize=True``. Consumers must:

1. Call ``controller.set_player_controller(pc)`` once a PlayerController exists.
2. Call ``controller.tick(dt)`` from a PyActor tick.

Layout is not re-run during drag; the cell-size dict is updated on LMB
release and then ``render_table()`` is called to rebuild.
"""
from __future__ import annotations

from typing import Optional

try:
    import unreal_engine as ue
    from unreal_engine import FVector
    from unreal_engine.enums import EMouseCursor, ECollisionChannel
except ImportError:
    ue = None
    FVector = None
    EMouseCursor = None
    ECollisionChannel = None

try:
    from click_helpers import cursor_hit_actor, is_mouse_down
except ImportError:
    def cursor_hit_actor(uobject, player_controller, channel=None):
        if player_controller is None:
            return None
        try:
            hit = player_controller.get_hit_result_under_cursor(channel, False)
            if hit is not None:
                return hit.actor
        except Exception:
            return None
        return None

    def is_mouse_down(player_controller) -> bool:
        if player_controller is None:
            return False
        try:
            from unreal_engine import FKey
            return player_controller.IsInputKeyDown(FKey('LeftMouseButton'))
        except Exception:
            return False


MIN_CELL_SIZE = 10.0

AXIS_CURSOR_NAME = {
    0: 'ResizeUpDown',
    1: 'ResizeLeftRight',
    2: 'CardinalCross',
}


def _cursor_for_axis(axis: int):
    name = AXIS_CURSOR_NAME.get(axis, 'CardinalCross')
    if EMouseCursor is None:
        return None
    return getattr(EMouseCursor, name, getattr(EMouseCursor, 'Default', None))


class GridlineResizeController:
    """Per-renderer hover/drag controller for resizing rows/cols/layers."""

    def __init__(self, renderer, player_controller=None):
        self.renderer = renderer
        self.player_controller = player_controller
        self.last_render_location = None

        self._hover_actor = None
        self._drag_active = False
        self._drag_meta = None
        self._drag_initial_mouse_world = None
        self._drag_initial_size = 0.0
        self._drag_plane_point = None
        self._drag_plane_normal = None
        self._lmb_down_last = False

    def set_player_controller(self, pc):
        self.player_controller = pc

    def tick(self, dt: float):
        if self.player_controller is None or self.renderer is None:
            return

        lmb_down = is_mouse_down(self.player_controller)

        if self._drag_active:
            if not lmb_down:
                self._finish_drag()
        else:
            hit = cursor_hit_actor(None, self.player_controller)
            meta = self.renderer.gridline_metadata.get(hit) if hit else None

            if meta is not None:
                self._set_cursor(_cursor_for_axis(meta['axis']))
                if lmb_down and not self._lmb_down_last:
                    self._start_drag(hit, meta)
                self._hover_actor = hit
            else:
                if self._hover_actor is not None:
                    self._set_cursor(getattr(EMouseCursor, 'Default', None))
                self._hover_actor = None

        self._lmb_down_last = lmb_down

    def clear_on_rerender(self):
        self._hover_actor = None
        self._drag_active = False
        self._drag_meta = None

    def _set_cursor(self, cursor):
        if cursor is None:
            return
        try:
            self.player_controller.CurrentMouseCursor = cursor
        except Exception:
            pass

    def _start_drag(self, actor, meta):
        axis = meta['axis']
        target_index = meta.get('resize_target_index')
        if target_index is None or axis not in (0, 1, 2):
            return

        midpoint = meta['midpoint']
        axis_dir = meta['direction']

        mouse_world = self._mouse_world_on_plane(midpoint, axis_dir)
        if mouse_world is None:
            return

        self._drag_active = True
        self._drag_meta = meta
        self._drag_initial_mouse_world = mouse_world
        self._drag_initial_size = self.renderer.get_effective_size(axis, target_index)
        self._drag_plane_point = midpoint
        self._drag_plane_normal = self._plane_normal_for_axis(axis_dir)

    def _finish_drag(self):
        meta = self._drag_meta
        self._drag_active = False
        self._drag_meta = None

        if meta is None:
            return

        axis = meta['axis']
        axis_dir = meta['direction']
        target_index = meta.get('resize_target_index')
        if target_index is None or axis not in (0, 1, 2):
            return

        mouse_world = self._mouse_world_on_plane(
            self._drag_plane_point, axis_dir
        )
        if mouse_world is None:
            return

        delta = FVector(
            mouse_world.x - self._drag_initial_mouse_world.x,
            mouse_world.y - self._drag_initial_mouse_world.y,
            mouse_world.z - self._drag_initial_mouse_world.z,
        )
        delta_along = (
            delta.x * axis_dir.x + delta.y * axis_dir.y + delta.z * axis_dir.z
        )
        new_size = max(MIN_CELL_SIZE, self._drag_initial_size + delta_along)
        self.renderer.set_user_size(axis, target_index, new_size)

        self._rebuild_table()

    def _rebuild_table(self):
        try:
            self.renderer.rerender_last()
        except Exception as e:
            if ue is not None:
                ue.log_warning(f'GridlineResizeController rebuild failed: {e}')

    def _mouse_world_on_plane(self, plane_point, axis_dir):
        if self.player_controller is None:
            return None
        try:
            success, origin, direction = (
                self.player_controller.DeprojectMousePositionToWorld()
            )
        except Exception:
            return None
        if not success:
            return None

        normal = self._plane_normal_for_axis(axis_dir)
        denom = (
            direction.x * normal.x
            + direction.y * normal.y
            + direction.z * normal.z
        )
        if abs(denom) < 1e-6:
            return None

        diff = FVector(
            plane_point.x - origin.x,
            plane_point.y - origin.y,
            plane_point.z - origin.z,
        )
        t = (diff.x * normal.x + diff.y * normal.y + diff.z * normal.z) / denom
        if t < 0:
            return None

        return FVector(
            origin.x + direction.x * t,
            origin.y + direction.y * t,
            origin.z + direction.z * t,
        )

    def _plane_normal_for_axis(self, axis_dir):
        cam_fwd = self._camera_forward()
        if cam_fwd is None:
            return FVector(0, 0, 1) if abs(axis_dir.z) < 0.5 else FVector(1, 0, 0)

        dot = (
            cam_fwd.x * axis_dir.x
            + cam_fwd.y * axis_dir.y
            + cam_fwd.z * axis_dir.z
        )
        normal = FVector(
            cam_fwd.x - axis_dir.x * dot,
            cam_fwd.y - axis_dir.y * dot,
            cam_fwd.z - axis_dir.z * dot,
        )
        length = (normal.x ** 2 + normal.y ** 2 + normal.z ** 2) ** 0.5
        if length < 1e-6:
            return FVector(0, 0, 1) if abs(axis_dir.z) < 0.5 else FVector(1, 0, 0)
        return FVector(normal.x / length, normal.y / length, normal.z / length)

    def _camera_forward(self) -> Optional['FVector']:
        pc = self.player_controller
        if pc is None:
            return None
        try:
            cam_mgr = pc.PlayerCameraManager
            rot = cam_mgr.GetCameraRotation()
            from unreal_engine.classes import KismetMathLibrary
            return KismetMathLibrary.GetForwardVector(rot)
        except Exception:
            return None
