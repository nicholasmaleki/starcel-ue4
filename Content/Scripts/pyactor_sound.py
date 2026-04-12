import unreal_engine as ue
from unreal_engine import FVector, FRotator, FTransform
from unreal_engine.enums import ECollisionChannel

# ---------------------------------------------------------------------------
# Python component: clickable sound sphere
# ---------------------------------------------------------------------------
#
# CRASH NOTE: do NOT call `smc.bind_event('OnClicked', ...)` on
# UPrimitiveComponent in UE4.27 + UEP.  The two-param sparse delegate
# crashes `ue_bind_pyevent` at UEPyModule.cpp:4502 with an access violation
# at 0x8.  Click detection is done via tick-based cursor trace + rising-edge
# LMB comparison, same pattern as `gizmo.py` and `pyactor_icon.py`.
# ---------------------------------------------------------------------------


class SoundSphere:
    """
    Attach to BP_SoundSphere.
    Blueprint needs StaticMeshComponent (sphere) + public Sound (SoundBase).

    Clicking the sphere plays the assigned Sound at the sphere's location.
    Click detection is tick-based — see the module header for the reason.
    """
    def begin_play(self):
        self.sound = getattr(self.uobject, 'Sound', None)
        self._was_mouse_down = False

        try:
            self.uobject.enable_input()
        except Exception:
            pass

        self.player_controller = None
        try:
            self.player_controller = self.uobject.get_player_controller()
            if self.player_controller is not None:
                self.player_controller.bEnableClickEvents     = True
                self.player_controller.bEnableMouseOverEvents = True
                self.player_controller.CurrentClickTraceChannel = \
                    ECollisionChannel.ECC_WorldDynamic
        except Exception as e:
            ue.log_warning(f'SoundSphere: player controller setup failed: {e}')

        self.owner_actor = None
        try:
            self.owner_actor = self.uobject.get_owner()
        except Exception:
            pass

    # ------------------------------------------------------------------ #
    # Tick — click detection
    # ------------------------------------------------------------------ #

    def tick(self, dt):
        if self.owner_actor is None or self.player_controller is None:
            return

        hit_actor = self._cursor_hit_actor()
        mouse_down = self._is_mouse_down()
        if mouse_down and not self._was_mouse_down:
            try:
                same = False
                if hit_actor is not None:
                    try:
                        same = (hit_actor == self.owner_actor)
                    except Exception:
                        pass
                    if not same:
                        try:
                            same = hit_actor.get_name() == self.owner_actor.get_name()
                        except Exception:
                            pass
                if same:
                    self._play()
            except Exception:
                pass
        self._was_mouse_down = mouse_down

    def _cursor_hit_actor(self):
        try:
            hit = self.uobject.get_hit_result_under_cursor(
                ECollisionChannel.ECC_WorldDynamic)
            if hit is not None:
                return hit.actor
        except Exception:
            pass
        try:
            hit = self.player_controller.get_hit_result_under_cursor(
                ECollisionChannel.ECC_WorldDynamic, False)
            if hit is not None:
                return hit.actor
        except Exception:
            pass
        return None

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
            return False

    def _play(self):
        if self.sound is None:
            self.sound = getattr(self.uobject, 'Sound', None)
        if self.sound:
            try:
                self.uobject.play_sound_at_location(
                    self.sound, self.uobject.get_actor_location())
            except Exception as e:
                ue.log_warning(f'SoundSphere: play_sound_at_location failed: {e}')
        else:
            ue.log_warning('SoundSphere: no Sound asset assigned.')
