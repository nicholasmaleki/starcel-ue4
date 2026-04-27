import os
import subprocess
import unreal_engine as ue
from unreal_engine import FVector, FRotator, FTransform
from unreal_engine.enums import ECollisionChannel
from unreal_engine_tools import find_component

# Python component: hover-shrink + clickable file-open for spawn_icon
#
# CRASH NOTE: do NOT call `smc.bind_event('OnClicked', ...)` — two-param
# sparse delegates crash UEP at UEPyModule.cpp:4502.
#
# CLICK STRATEGY: We know OnBeginCursorOver / OnEndCursorOver fire correctly
# (one-param sparse delegates work).  So we track _hovered state from those
# callbacks and detect mouse-down during hover in tick().  No cursor trace
# needed — the hover events tell us the cursor is already over our sphere.


def _open_with_default_app(path):
    """Open *path* with the OS's default handler, the same as a Windows
    Explorer double-click — the "open" verb for that file type."""
    try:
        if hasattr(os, 'startfile'):
            os.startfile(path)
        else:
            subprocess.Popen(
                ['cmd', '/c', 'start', '', path],
                shell=False,
                creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0),
            )
        ue.log(f'IconSphere: opened "{path}"')
    except Exception as e:
        ue.log_warning(f'IconSphere: open failed for "{path}": {e}')


class IconSphere:
    """
    Hover-shrink + click-to-open for BP_Icon.

    Click = cursor is hovering (OnBeginCursorOver fired) + LMB rising edge.
    """
    HOVER_DELTA = 0.3
    LERP_SPEED = 8.0

    def begin_play(self):
        self.uobject.enable_input()
        self.player_controller = self.uobject.get_player_controller()
        try:
            self.player_controller.bEnableMouseOverEvents = True
            self.player_controller.bEnableClickEvents = True
            self.player_controller.CurrentClickTraceChannel = \
                ECollisionChannel.ECC_WorldDynamic
        except Exception as e:
            ue.log_warning(f'IconSphere: pc setup failed: {e}')

        # Captured lazily on first tick: spawn_icon's set_actor_transform
        # runs AFTER world.actor_spawn() returns, so begin_play here would
        # see the BP default scale, not the caller's requested scale.
        self.base_scale = None
        self.target_scale = None
        self._hovered = False
        self._was_mouse_down = False

        # Find the owner actor for source_path lookup
        self.owner_actor = None
        for getter in ('get_owner', 'get_actor'):
            try:
                self.owner_actor = getattr(self.uobject, getter)()
                if self.owner_actor is not None:
                    break
            except Exception:
                continue

        # Bind hover events (one-param sparse delegates — safe)
        self.smc = None
        try:
            self.smc = find_component(self.uobject, "Sphere")
            if self.smc is not None:
                self.smc.bind_event('OnBeginCursorOver', self.on_hover_begin)
                self.smc.bind_event('OnEndCursorOver',   self.on_hover_end)
        except Exception as e:
            ue.log_warning(f'IconSphere: hover bind failed: {e}')

        owner_name = 'None'
        try:
            if self.owner_actor:
                owner_name = self.owner_actor.get_name()
        except Exception:
            pass
        ue.log(f'IconSphere: ready  owner={owner_name}  '
               f'smc={self.smc is not None}  pc={self.player_controller is not None}')

    # Hover callbacks

    def on_hover_begin(self, mesh):
        self._hovered = True
        if self.base_scale is None:
            self.base_scale = self.uobject.get_actor_scale()
        d = self.HOVER_DELTA
        bs = self.base_scale
        self.target_scale = FVector(bs.x - d, bs.y - d, bs.z - d)

    def on_hover_end(self, mesh):
        self._hovered = False
        self.target_scale = self.base_scale

    # Source path lookup

    def _get_source_path(self):
        """Read source_path lazily from the owner actor (set after spawn)."""
        if self.owner_actor is not None:
            p = getattr(self.owner_actor, 'source_path', None)
            if p:
                return p
        return getattr(self.uobject, 'source_path', None)

    # Mouse button check

    def _is_mouse_down(self):
        if self.player_controller is None:
            return False
        try:
            from unreal_engine import FKey
            return self.player_controller.IsInputKeyDown(FKey('LeftMouseButton'))
        except Exception:
            pass
        try:
            return self.player_controller.IsInputKeyDown('LeftMouseButton')
        except Exception:
            pass
        # Last resort: try on the uobject itself
        try:
            return self.uobject.is_input_key_down('LeftMouseButton')
        except Exception:
            return False

    # Tick

    def tick(self, dt):
        # First tick: capture the post-spawn actor scale as our base.
        if self.base_scale is None:
            self.base_scale = self.uobject.get_actor_scale()
            self.target_scale = self.base_scale
            return

        # hover scale lerp
        cur = self.uobject.get_actor_scale()
        tgt = self.target_scale
        a = min(1.0, self.LERP_SPEED * dt)
        self.uobject.set_actor_scale(FVector(
            cur.x + (tgt.x - cur.x) * a,
            cur.y + (tgt.y - cur.y) * a,
            cur.z + (tgt.z - cur.z) * a,
        ))

        # click = hovered + LMB rising edge
        mouse_down = self._is_mouse_down()
        if mouse_down and not self._was_mouse_down and self._hovered:
            path = self._get_source_path()
            if path:
                ue.log(f'IconSphere: CLICK → "{path}"')
                _open_with_default_app(path)
            else:
                ue.log('IconSphere: CLICK (no source_path)')
        self._was_mouse_down = mouse_down
