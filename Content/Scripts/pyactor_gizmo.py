"""
pyactor_gizmo.py — Global gizmo interaction PyActor

Replaces gizmo.setup_gizmo_interaction — the drag/hover/rotate/scale update
logic that used to run via a tick closure called from Main.tick now runs on
this single PyActor's tick(self, dt).

Usage:
    from ue_spawn import spawn_pyactor
    from gizmo import test_gizmos, _piece_off

    target, gizmo_root, handles = test_gizmos()
    pyactor = spawn_pyactor('pyactor_gizmo', 'GizmoController')
    pyactor.get_py_proxy().setup(
        uobject=main.uobject,
        input_manager=main.input,
        target=target,
        handles=handles,
        piece_offsets=_piece_off,
    )
"""

import math
import unreal_engine as ue
from unreal_engine import FVector, FRotator, FTransform
from unreal_engine.classes import KismetMathLibrary
from unreal_engine.enums import ECollisionChannel


# Inkscape-style modifier keys:
#   Ctrl  → lock aspect ratio (uniform scale by dominant factor)
#   Shift → scale symmetrically around center (center stays fixed)
#   Alt   → fine-grained (0.1× delta)
_MOD_CTRL = ("LeftControl", "RightControl")
_MOD_SHIFT = ("LeftShift",   "RightShift")
_MOD_ALT = ("LeftAlt",     "RightAlt")


def _any_down(uobject_ref, keys):
    for k in keys:
        try:
            if uobject_ref.is_input_key_down(k):
                return True
        except Exception:
            pass
    return False


def _inverse_rotate(rotation, world_vec):
    """World vector → local (actor frame) via inverse rotation.

    Uses FRotator.inversed() + FRotator * FVector (which calls
    FRotator::RotateVector internally). Avoids KismetMathLibrary.Quat_*
    — UEPython's UFUNCTION arg converter has no FQuat→Q branch, so the
    quaternion path errors every call.
    """
    return rotation.inversed() * world_vec


def _rotate_local(rotation, local_vec):
    # See _inverse_rotate for why we don't go through Quat_RotateVector.
    return rotation * local_vec


def _vec_get(v, i):
    return v.x if i == 0 else (v.y if i == 1 else v.z)


def _log(msg):
    try:
        ue.log_warning(msg)
    except Exception:
        pass


class GizmoController:
    """PyActor that owns the per-frame gizmo interaction state + tick.

    begin_play leaves it idle. Call .setup(...) after spawn to wire it up to
    the target + handles produced by gizmo.test_gizmos().
    """

    def begin_play(self):
        self._ready = False
        self._uobject_ref = None
        self._player_controller = None
        self._target = None
        self._handles = None
        self._piece_offsets = None
        self._bbox_dynamic = None
        self._all_actors = set()

        self._down = False
        self._drag = False
        self._kind = None
        self._data = None
        self._loc0 = None
        self._rot0 = None
        self._scl0 = None
        self._hit0 = None
        self._off0 = None
        self._plane_normal = None
        self._hov = None

    def setup(self, uobject, input_manager, target, handles, piece_offsets,
              bbox_dynamic=None):
        """Wire the controller to gizmo pieces + input. Bindings happen here,
        not in begin_play, because begin_play has no access to the host's
        HotkeyManager.

        bbox_dynamic: optional dict of {actor: (kind, data)} for bounding-box
        pieces whose world transform must be recomputed each tick from the
        target's current scale/rotation."""
        self._uobject_ref = uobject
        self._target = target
        self._handles = handles
        self._piece_offsets = piece_offsets
        self._bbox_dynamic = bbox_dynamic or {}
        # Only handle actors (interactable) + target participate in hover/drag.
        # Wireframe pieces live in _bbox_dynamic but have collision disabled,
        # so they won't appear as cursor hits anyway.
        self._all_actors = set(handles.keys()) | {target}

        try:
            self._player_controller = uobject.get_player_controller()
        except Exception:
            self._player_controller = None

        input_manager.bind_press("LeftMouseButton",   self._press)
        input_manager.bind_release("LeftMouseButton", self._release)

        self._ready = True
        _log("GizmoController: ready")

    def _press(self):
        self._down = True

    def _release(self):
        self._down = False
        if self._drag:
            self._drag = False
            try:
                _log(f"Drag end pos={self._target.get_actor_location()}")
            except Exception:
                pass

    # Drag-plane projection helpers
    #
    # The previous implementation read cur from get_hit_result_under_cursor's
    # impact_point. As soon as the cursor left every collidable surface (or
    # the dragged handle outran it), the trace returned no hit and the drag
    # froze — visible as "the resize hits a limit" once you move the mouse
    # past the corner cube. We instead deproject the mouse ray each tick and
    # intersect it with a stable plane chosen at drag start, so cur is always
    # defined regardless of what (if anything) the cursor is hovering over.
    @staticmethod
    def _normalize_vec(v):
        L = math.sqrt(v.x * v.x + v.y * v.y + v.z * v.z)
        if L < 1e-6:
            return FVector(0, 0, 1)
        return FVector(v.x / L, v.y / L, v.z / L)

    def _camera_forward_unit(self):
        pc = self._player_controller
        if pc is None:
            return FVector(1, 0, 0)
        try:
            rot = pc.PlayerCameraManager.GetCameraRotation()
            return KismetMathLibrary.GetForwardVector(rot)
        except Exception:
            return FVector(1, 0, 0)

    def _compute_drag_plane_normal(self, kind, data):
        """Pick a plane whose normal stays meaningful for the whole drag.

        - axis / scale: plane contains the axis; normal = camera-forward
          projected perpendicular to the axis (so the plane faces the
          camera as well as possible while still containing the axis).
        - plane: the literal plane defined by the two in-plane directions.
        - rotate: the rotation plane (normal = rotation axis).
        - free / bbox_corner / bbox_edge: camera-facing plane through hit0.
        """
        cam_fwd = self._camera_forward_unit()

        if kind in ('axis', 'scale'):
            ax = data
            dot = cam_fwd.x * ax.x + cam_fwd.y * ax.y + cam_fwd.z * ax.z
            n = FVector(cam_fwd.x - ax.x * dot,
                        cam_fwd.y - ax.y * dot,
                        cam_fwd.z - ax.z * dot)
            L = math.sqrt(n.x * n.x + n.y * n.y + n.z * n.z)
            if L < 1e-3:
                # camera ~parallel to axis — pick any vector perp to ax
                fb = FVector(0, 0, 1) if abs(ax.x) > 0.9 else FVector(1, 0, 0)
                d = ax.x * fb.x + ax.y * fb.y + ax.z * fb.z
                n = FVector(fb.x - ax.x * d, fb.y - ax.y * d, fb.z - ax.z * d)
            return self._normalize_vec(n)

        if kind == 'plane':
            d1, d2 = data
            n = FVector(d1.y * d2.z - d1.z * d2.y,
                        d1.z * d2.x - d1.x * d2.z,
                        d1.x * d2.y - d1.y * d2.x)
            return self._normalize_vec(n)

        if kind == 'rotate':
            return self._normalize_vec(data)

        # 'free', 'bbox_corner', 'bbox_edge' (or fallback): camera-facing
        return self._normalize_vec(cam_fwd)

    def _mouse_world_on_plane(self, plane_point, plane_normal):
        pc = self._player_controller
        if pc is None:
            return None
        try:
            success, origin, direction = pc.DeprojectMousePositionToWorld()
        except Exception:
            return None
        if not success:
            return None

        n = plane_normal
        denom = direction.x * n.x + direction.y * n.y + direction.z * n.z
        if abs(denom) < 1e-6:
            return None

        diff = FVector(plane_point.x - origin.x,
                       plane_point.y - origin.y,
                       plane_point.z - origin.z)
        t = (diff.x * n.x + diff.y * n.y + diff.z * n.z) / denom
        if t < 0:
            return None

        return FVector(origin.x + direction.x * t,
                       origin.y + direction.y * t,
                       origin.z + direction.z * t)

    def tick(self, delta_time):
        if not self._ready or self._target is None:
            return

        target = self._target

        # Reposition every gizmo piece to follow the target
        tgt = target.get_actor_location()
        for actor, off in self._piece_offsets.items():
            if actor in self._bbox_dynamic:
                continue  # bbox pieces use scale/rotation-aware update below
            try:
                actor.set_actor_location(tgt + off)
            except Exception:
                pass

        # Bounding-box pieces: rebuild transform from current scale/rotation
        if self._bbox_dynamic:
            try:
                from gizmo import update_bbox_piece
                for actor in self._bbox_dynamic:
                    update_bbox_piece(actor, target)
            except Exception as e:
                _log(f"bbox tick update fail: {e}")

        # Cursor trace
        try:
            hit = self._uobject_ref.get_hit_result_under_cursor(
                ECollisionChannel.ECC_Visibility)
        except Exception:
            hit = None
        hit_actor = hit.actor if hit else None
        on_gizmo = hit_actor in self._all_actors

        # Hover (emissive bump via gizmo._hover_enter/_exit)
        new_hov = hit_actor if on_gizmo else None
        if new_hov != self._hov:
            try:
                from gizmo import _hover_exit, _hover_enter
                if self._hov:
                    _hover_exit(self._hov)
                if new_hov:
                    _hover_enter(new_hov)
            except Exception:
                pass
            self._hov = new_hov

        # Drag start
        if on_gizmo and self._down and not self._drag and hit:
            kind, data = self._handles.get(hit_actor, ('free', None))
            self._drag = True
            self._kind = kind
            self._data = data
            self._loc0 = target.get_actor_location()
            self._rot0 = target.get_actor_rotation()
            try:
                self._scl0 = target.GetActorScale3D()
            except Exception:
                self._scl0 = target.get_actor_scale()
            self._hit0 = hit.impact_point
            self._off0 = hit.impact_point - target.get_actor_location()
            self._plane_normal = self._compute_drag_plane_normal(kind, data)
            _log(f"Drag start: {kind} on {hit_actor.get_name()}")

        # Drag update — cur comes from a ray/plane intersection rather than
        # the cursor's hit result, so the drag keeps tracking the mouse even
        # when the cursor is over empty space (or the handle has outrun the
        # cursor during a resize).
        if self._drag and self._down:
            cur = self._mouse_world_on_plane(self._hit0, self._plane_normal)
            if cur is not None:
                loc0 = self._loc0
                rot0 = self._rot0
                hit0 = self._hit0
                kind = self._kind
                data = self._data

                if kind == 'free':
                    target.set_actor_location(cur - self._off0)

                elif kind == 'axis':
                    ax = data
                    diff = cur - loc0
                    t = diff.x*ax.x + diff.y*ax.y + diff.z*ax.z
                    target.set_actor_location(loc0 + ax * t)

                elif kind == 'plane':
                    d1, d2 = data
                    diff = cur - loc0
                    t1 = diff.x*d1.x + diff.y*d1.y + diff.z*d1.z
                    t2 = diff.x*d2.x + diff.y*d2.y + diff.z*d2.z
                    target.set_actor_location(loc0 + d1*t1 + d2*t2)

                elif kind == 'rotate':
                    nrm = data
                    v1 = hit0 - loc0
                    v2 = cur  - loc0
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
                        # 2026-04-26: rotation now composed in world space.
                        # Old code added `ang` directly to rot0.roll/pitch/yaw,
                        # which silently re-interpreted the world-axis delta as
                        # an Euler increment in the actor's local frame. When
                        # the actor was inverted (e.g. pitch≈±180), the local
                        # frame was flipped vs. world, so the rotation appeared
                        # opposite to the cursor drag. Building the delta as a
                        # world rotator and composing with rot0 keeps the delta
                        # meaningful regardless of starting orientation.
                        # ROLLBACK: replace the 6 lines below with
                        #     target.set_actor_rotation(FRotator(
                        #         rot0.roll  + nrm.x * ang,
                        #         rot0.pitch + nrm.y * ang,
                        #         rot0.yaw   + nrm.z * ang,
                        #     ))
                        delta = FRotator(0, 0, 0)
                        delta.roll = nrm.x * ang
                        delta.pitch = nrm.y * ang
                        delta.yaw = nrm.z * ang
                        target.set_actor_rotation(
                            KismetMathLibrary.ComposeRotators(rot0, delta))

                elif kind == 'scale':
                    ax = data
                    diff = cur - hit0
                    delta = (diff.x*ax.x + diff.y*ax.y + diff.z*ax.z) * 0.01
                    s = self._scl0
                    target.SetActorScale3D(FVector(
                        max(0.05, s.x + abs(ax.x) * delta),
                        max(0.05, s.y + abs(ax.y) * delta),
                        max(0.05, s.z + abs(ax.z) * delta),
                    ))

                elif kind == 'bbox_corner':
                    self._drag_bbox_corner(cur, data)

                elif kind == 'bbox_edge':
                    self._drag_bbox_edge(cur, data)

        if self._drag and not self._down:
            self._drag = False

    # Bounding-box drag helpers (Inkscape-style modifiers)
    #
    # The bounding box is oriented with the actor's local frame (matches the
    # mesh's own axes), so drags are computed in local space via an inverse
    # rotation, then applied as (scale, location) on the actor.
    #
    # Modifiers — queried via is_input_key_down each tick so they respond
    # mid-drag (Inkscape-style "hold to toggle"):
    #   Ctrl  → lock aspect ratio (uniform scale by dominant factor)
    #   Shift → scale symmetrically around center (center stays fixed)
    #   Alt   → fine-grained drag (multiply delta by 0.1)
    _MIN_HALF_EXTENT = 2.5  # world-space floor — prevents zero/flip

    def _drag_bbox_corner(self, cur, data):
        target = self._target
        dx, dy, dz = data
        loc0, rot0, s0, hit0 = self._loc0, self._rot0, self._scl0, self._hit0

        # Per-mesh local extent (50uu for BasicShapes, but differs for any
        # imported mesh). h0 = local extent × original scale = original world
        # half-extent in the actor-local frame.
        from gizmo import local_half_extent
        le = local_half_extent(target)
        h0 = FVector(le.x * s0.x, le.y * s0.y, le.z * s0.z)
        dp = cur - hit0
        dpl = _inverse_rotate(rot0, dp)

        if _any_down(self._uobject_ref, _MOD_ALT):
            dpl = FVector(dpl.x * 0.1, dpl.y * 0.1, dpl.z * 0.1)

        new_hx = h0.x + dx * dpl.x
        new_hy = h0.y + dy * dpl.y
        new_hz = h0.z + dz * dpl.z

        if _any_down(self._uobject_ref, _MOD_CTRL):
            fx = new_hx / h0.x if h0.x > 1e-6 else 1.0
            fy = new_hy / h0.y if h0.y > 1e-6 else 1.0
            fz = new_hz / h0.z if h0.z > 1e-6 else 1.0
            f = max((fx, fy, fz), key=lambda v: abs(v - 1.0))
            new_hx, new_hy, new_hz = h0.x * f, h0.y * f, h0.z * f

        mn = self._MIN_HALF_EXTENT
        new_hx = max(new_hx, mn)
        new_hy = max(new_hy, mn)
        new_hz = max(new_hz, mn)

        target.SetActorScale3D(FVector(new_hx / le.x,
                                       new_hy / le.y,
                                       new_hz / le.z))

        if _any_down(self._uobject_ref, _MOD_SHIFT):
            target.set_actor_location(loc0)
        else:
            a0_local = FVector(-dx * h0.x, -dy * h0.y, -dz * h0.z)
            a0_world = loc0 + _rotate_local(rot0, a0_local)
            new_anchor_local = FVector(-dx * new_hx, -dy * new_hy, -dz * new_hz)
            target.set_actor_location(
                a0_world - _rotate_local(rot0, new_anchor_local))

    def _drag_bbox_edge(self, cur, data):
        target = self._target
        ai, dj, dk = data
        loc0, rot0, s0, hit0 = self._loc0, self._rot0, self._scl0, self._hit0

        from gizmo import local_half_extent
        le = local_half_extent(target)
        le_list = [le.x, le.y, le.z]
        h0_list = [le.x * s0.x, le.y * s0.y, le.z * s0.z]
        dp = cur - hit0
        dpl = _inverse_rotate(rot0, dp)
        dp_list = [dpl.x, dpl.y, dpl.z]

        if _any_down(self._uobject_ref, _MOD_ALT):
            dp_list = [c * 0.1 for c in dp_list]

        others = [i for i in (0, 1, 2) if i != ai]
        dir_list = [0, 0, 0]
        dir_list[others[0]] = dj
        dir_list[others[1]] = dk

        new_h = list(h0_list)
        for i in others:
            new_h[i] = h0_list[i] + dir_list[i] * dp_list[i]

        if _any_down(self._uobject_ref, _MOD_CTRL):
            fs = [new_h[i] / h0_list[i] if h0_list[i] > 1e-6 else 1.0
                  for i in others]
            f = max(fs, key=lambda v: abs(v - 1.0))
            for i in others:
                new_h[i] = h0_list[i] * f

        mn = self._MIN_HALF_EXTENT
        new_h = [max(h, mn) for h in new_h]

        target.SetActorScale3D(FVector(new_h[0] / le_list[0],
                                       new_h[1] / le_list[1],
                                       new_h[2] / le_list[2]))

        if _any_down(self._uobject_ref, _MOD_SHIFT):
            target.set_actor_location(loc0)
        else:
            a_local = [0.0, 0.0, 0.0]
            a_local[others[0]] = -dir_list[others[0]] * h0_list[others[0]]
            a_local[others[1]] = -dir_list[others[1]] * h0_list[others[1]]
            a0_world = loc0 + _rotate_local(rot0, FVector(*a_local))

            new_anchor_local = [0.0, 0.0, 0.0]
            new_anchor_local[others[0]] = -dir_list[others[0]] * new_h[others[0]]
            new_anchor_local[others[1]] = -dir_list[others[1]] * new_h[others[1]]
            target.set_actor_location(
                a0_world - _rotate_local(rot0, FVector(*new_anchor_local)))
