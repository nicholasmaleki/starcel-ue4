import os
import unreal_engine as ue
from unreal_engine import FVector, FRotator, FTransform
from unreal_engine.enums import ECollisionChannel
from unreal_engine_tools import find_component

# Python component: hover-shrink + clickable sound playback for spawn_sound.
#
# Modeled on pyactor_icon.IconSphere — same hover/click strategy, same lazy
# source-path lookup, but the click plays audio instead of opening a file.
#
# CRASH NOTE: do NOT call `smc.bind_event('OnClicked', ...)` — two-param
# sparse delegates crash UEP at UEPyModule.cpp:4502.
#
# CLICK STRATEGY: OnBeginCursorOver / OnEndCursorOver fire correctly
# (one-param sparse delegates work).  Track _hovered from those callbacks
# and detect mouse-down during hover in tick() — no cursor trace needed.
#
# SOUND RESOLUTION (in priority order, checked lazily on each click so values
# attached after begin_play are still picked up):
#   1) actor.sound          USoundBase ref attached at spawn (asset or
#                           USoundWaveProcedural built via ffmpeg decode).
#   2) actor.Sound          BP-public variable (UE asset path).
#   3) actor.source_path    Filesystem audio file — decoded on first click
#                           via ue_spawn._build_procedural_wave (the audio
#                           equivalent of pil_image_to_texture for icons),
#                           and cached so subsequent clicks reuse the wave.


def _decode_sound_from_path(path):
    """Decode *path* into a transient USoundWaveProcedural via ffmpeg.

    Mirrors how spawn_icon dynamically converts an arbitrary image file to a
    Texture2D (PIL -> pil_image_to_texture).  Here ffmpeg -> PCM ->
    SoundWaveProcedural, exposed by ue_spawn._build_procedural_wave.
    """
    if not path or not os.path.isfile(path):
        return None
    try:
        from ue_spawn import _build_procedural_wave
        sw, _ = _build_procedural_wave(path)
        return sw
    except Exception as e:
        ue.log_warning(f'SoundSphere: decode failed for "{path}": {e}')
        return None


class SoundSphere:
    """
    Hover-shrink + click-to-play for BP_SoundSphere.

    Click = cursor is hovering (OnBeginCursorOver fired) + LMB rising edge.
    On click, plays the resolved sound at the actor's current location via
    `self.uobject.play_sound_at_location(sound, location)`.
    """
    HOVER_DELTA = 0.3
    LERP_SPEED  = 8.0

    def begin_play(self):
        self.uobject.enable_input()
        self.player_controller = self.uobject.get_player_controller()
        try:
            self.player_controller.bEnableMouseOverEvents = True
            self.player_controller.bEnableClickEvents     = True
            self.player_controller.CurrentClickTraceChannel = \
                ECollisionChannel.ECC_WorldDynamic
        except Exception as e:
            ue.log_warning(f'SoundSphere: pc setup failed: {e}')

        self.base_scale      = self.uobject.get_actor_scale()
        self.target_scale    = self.base_scale
        self._hovered        = False
        self._was_mouse_down = False
        self._cached_sound   = None

        # Find the owner actor for sound / source_path lookup
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
            ue.log_warning(f'SoundSphere: hover bind failed: {e}')

        owner_name = 'None'
        try:
            if self.owner_actor:
                owner_name = self.owner_actor.get_name()
        except Exception:
            pass
        ue.log(f'SoundSphere: ready  owner={owner_name}  '
               f'smc={self.smc is not None}  pc={self.player_controller is not None}')

    # Hover callbacks

    def on_hover_begin(self, mesh):
        self._hovered = True
        d  = self.HOVER_DELTA
        bs = self.base_scale
        self.target_scale = FVector(bs.x - d, bs.y - d, bs.z - d)

    def on_hover_end(self, mesh):
        self._hovered = False
        self.target_scale = self.base_scale

    # Sound resolution (lazy, like IconSphere._get_source_path)

    def _get_sound(self):
        """Resolve the sound to play.  See module header for source priority.

        The result is cached on first successful resolution so we don't
        re-decode a filesystem path on every click.
        """
        if self._cached_sound is not None:
            return self._cached_sound

        # 1+2) python attribute (sound / Sound) on owner actor or the component
        for attr in ('sound', 'Sound'):
            for src in (self.owner_actor, self.uobject):
                if src is None:
                    continue
                try:
                    snd = getattr(src, attr, None)
                except Exception:
                    snd = None
                if snd is not None:
                    self._cached_sound = snd
                    return snd

        # 3) filesystem path -> decode on demand
        path = None
        for src in (self.owner_actor, self.uobject):
            if src is None:
                continue
            try:
                p = getattr(src, 'source_path', None)
            except Exception:
                p = None
            if p:
                path = p
                break
        if path:
            snd = _decode_sound_from_path(path)
            if snd is not None:
                self._cached_sound = snd
                return snd

        return None

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
        try:
            return self.uobject.is_input_key_down('LeftMouseButton')
        except Exception:
            return False

    # Tick

    def tick(self, dt):
        # hover scale lerp
        cur = self.uobject.get_actor_scale()
        tgt = self.target_scale
        a   = min(1.0, self.LERP_SPEED * dt)
        self.uobject.set_actor_scale(FVector(
            cur.x + (tgt.x - cur.x) * a,
            cur.y + (tgt.y - cur.y) * a,
            cur.z + (tgt.z - cur.z) * a,
        ))

        # click = hovered + LMB rising edge
        mouse_down = self._is_mouse_down()
        if mouse_down and not self._was_mouse_down and self._hovered:
            self._play()
        self._was_mouse_down = mouse_down

    def _read_attr(self, name, default):
        """Read *name* from the owner actor or component, returning *default*
        if missing or unreadable."""
        for src in (self.owner_actor, self.uobject):
            if src is None:
                continue
            try:
                v = getattr(src, name, None)
            except Exception:
                v = None
            if v is not None:
                return v
        return default

    def _play(self):
        sound = self._get_sound()
        if sound is None:
            ue.log_warning('SoundSphere: CLICK (no sound — set actor.sound, '
                           'actor.Sound, or actor.source_path)')
            return
        volume     = float(self._read_attr('volume',     1.0))
        pitch      = float(self._read_attr('pitch',      1.0))
        start_time = float(self._read_attr('start_time', 0.0))
        try:
            loc = self.uobject.get_actor_location()
            self.uobject.play_sound_at_location(
                sound, loc, volume, pitch, start_time)
            ue.log(f'SoundSphere: CLICK -> play_sound_at_location '
                   f'at {loc}  vol={volume}  pitch={pitch}')
        except Exception as e:
            ue.log_warning(f'SoundSphere: play_sound_at_location failed: {e}')


class ProceduralSoundHost:
    """
    Minimal host for a transient USoundWaveProcedural attached to BP_PyActorEmpty.

    ue_spawn._play_audio_file_as_actor sets `self.uobject.sound_wave` and the
    AudioComponent after spawn; this proxy exists so the wave has a Python-side
    ref attached to the actor's lifetime (UEP releases Python attrs with the
    actor, so the wave survives until the actor is destroyed).
    """
    def begin_play(self):
        pass
