"""
pyactor_gizmo.py — Global gizmo interaction PyActor

Replaces gizmo.setup_gizmo_interaction — the drag/hover/rotate/scale update
logic that used to run via a tick closure called from Main.tick now runs on
this single PyActor's tick(self, dt).

Usage:
    from ue_spawn import _spawn_pyactor
    from gizmo import test_gizmos, _piece_off

    target, gizmo_root, handles = test_gizmos()
    pyactor = _spawn_pyactor('pyactor_gizmo', 'GizmoController')
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
from unreal_engine import FVector, FRotator
from unreal_engine.enums import ECollisionChannel


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
        self._ready          = False
        self._uobject_ref    = None
        self._target         = None
        self._handles        = None
        self._piece_offsets  = None
        self._all_actors     = set()

        self._down = False
        self._drag = False
        self._kind = None
        self._data = None
        self._loc0 = None
        self._rot0 = None
        self._scl0 = None
        self._hit0 = None
        self._off0 = None
        self._hov  = None

    def setup(self, uobject, input_manager, target, handles, piece_offsets):
        """Wire the controller to gizmo pieces + input. Bindings happen here,
        not in begin_play, because begin_play has no access to the host's
        HotkeyManager."""
        self._uobject_ref   = uobject
        self._target        = target
        self._handles       = handles
        self._piece_offsets = piece_offsets
        self._all_actors    = set(handles.keys()) | {target}

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

    def tick(self, delta_time):
        if not self._ready or self._target is None:
            return

        target = self._target

        # Reposition every gizmo piece to follow the target
        tgt = target.get_actor_location()
        for actor, off in self._piece_offsets.items():
            try:
                actor.set_actor_location(tgt + off)
            except Exception:
                pass

        # Cursor trace
        try:
            hit = self._uobject_ref.get_hit_result_under_cursor(
                ECollisionChannel.ECC_Visibility)
        except Exception:
            hit = None
        hit_actor = hit.actor if hit else None
        on_gizmo  = hit_actor in self._all_actors

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
            _log(f"Drag start: {kind} on {hit_actor.get_name()}")

        # Drag update
        if self._drag and self._down and hit:
            cur  = hit.impact_point
            loc0 = self._loc0
            rot0 = self._rot0
            hit0 = self._hit0
            kind = self._kind
            data = self._data

            if kind == 'free':
                target.set_actor_location(cur - self._off0)

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
                delta = (diff.x*ax.x + diff.y*ax.y + diff.z*ax.z) * 0.01
                s     = self._scl0
                target.SetActorScale3D(FVector(
                    max(0.05, s.x + abs(ax.x) * delta),
                    max(0.05, s.y + abs(ax.y) * delta),
                    max(0.05, s.z + abs(ax.z) * delta),
                ))

        if self._drag and not self._down:
            self._drag = False
