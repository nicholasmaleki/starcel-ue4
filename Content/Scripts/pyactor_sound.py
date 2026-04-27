import os
import unreal_engine as ue
from unreal_engine import FVector, FRotator, FTransform
from unreal_engine.enums import ECollisionChannel

# Python component: hover-shrink + clickable sound playback for spawn_sound.
#
# Modeled on pyactor_icon.IconSphere — same hover/click strategy, same lazy
# source-path lookup, but the click plays audio instead of opening a file.
#
# CRASH NOTE: do NOT bind UPrimitiveComponent or AActor cursor events
# (OnBeginCursorOver / OnEndCursorOver / OnClicked / OnReleased) via
# `bind_event`.  All of them are sparse multicast delegates in UE 4.27+
# (DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_* in PrimitiveComponent.h /
# Actor.h).  FSparseDelegateProperty has no inline storage, so UEP's
# ue_bind_pyevent dereferences a nullptr from GetMulticastDelegate at
# UEPyModule.cpp:4502 and crashes with an access violation reading 0x8.
# One-param sparse delegates crash too — the param count never matters.
#
# CLICK STRATEGY: tick-based cursor trace via get_hit_result_under_cursor,
# same as gizmo.py and pyactor_text3d.py.  Edge-trigger target_scale on
# hover enter/leave; rising-edge LMB during hover = click.
#
# SOUND RESOLUTION (in priority order, checked lazily on each click so values
# attached after begin_play are still picked up):
#   1) actor.sound          USoundBase ref attached at spawn (asset or
#                           USoundWaveProcedural built via ffmpeg decode).
#                           For procedural waves, actor.sound_pcm holds the
#                           raw PCM bytes — see PROCEDURAL QUEUE below.
#   2) actor.Sound          BP-public variable (UE asset path).
#   3) actor.source_path    Filesystem audio file — decoded on first click
#                           via ue_spawn._build_procedural_wave (the audio
#                           equivalent of pil_image_to_texture for icons),
#                           and cached so subsequent clicks reuse the wave.
#
# PROCEDURAL QUEUE: USoundWaveProcedural.QueueAudio is a streaming append —
# the audio engine pulls from the queue only while a source is actively
# rendering.  Queueing at decode time and playing seconds later doesn't
# work; the queue state by play time isn't what we queued.  So we cache
# the raw PCM (in self._cached_pcm or actor.sound_pcm) and call
# sound.queue_audio(pcm) immediately before each play_sound_at_location.


def _decode_sound_from_path(path):
    """Decode *path* into a transient USoundWaveProcedural via ffmpeg.
    Returns (sound_wave, pcm_bytes) or (None, None).

    Mirrors how spawn_icon dynamically converts an arbitrary image file to a
    Texture2D (PIL -> pil_image_to_texture).  Here ffmpeg -> PCM ->
    SoundWaveProcedural, exposed by ue_spawn._build_procedural_wave.  The
    PCM is returned alongside the wave so the caller can re-queue it onto
    the wave right before each play_sound_at_location call.
    """
    if not path or not os.path.isfile(path):
        return None, None
    try:
        from ue_spawn import _build_procedural_wave
        sw, pcm, _ = _build_procedural_wave(path)
        return sw, pcm
    except Exception as e:
        ue.log_warning(f'SoundSphere: decode failed for "{path}": {e}')
        return None, None


class SoundSphere:
    """
    Hover-shrink + click-to-play for BP_SoundSphere.

    Click = cursor trace hits this actor + LMB rising edge.  Plays the
    resolved sound at the actor's current location via
    `self.uobject.play_sound_at_location(sound, location)`.
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
            ue.log_warning(f'SoundSphere: pc setup failed: {e}')

        self.base_scale = self.uobject.get_actor_scale()
        self.target_scale = self.base_scale
        self._hovered = False
        self._was_mouse_down = False
        self._cached_sound = None
        self._cached_pcm = None

        # Find the owner actor for sound / source_path lookup
        self.owner_actor = None
        for getter in ('get_owner', 'get_actor'):
            try:
                self.owner_actor = getattr(self.uobject, getter)()
                if self.owner_actor is not None:
                    break
            except Exception:
                continue

        owner_name = 'None'
        try:
            if self.owner_actor:
                owner_name = self.owner_actor.get_name()
        except Exception:
            pass
        ue.log(f'SoundSphere: ready  owner={owner_name}  '
               f'pc={self.player_controller is not None}')

    # Sound resolution (lazy, like IconSphere._get_source_path)

    def _get_sound(self):
        """Resolve the sound to play.  See module header for source priority.

        The result is cached on first successful resolution so we don't
        re-decode a filesystem path on every click.  For procedural waves,
        the matching PCM bytes are cached too (see PROCEDURAL QUEUE in the
        module header).
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
                    # Pick up matching PCM if present (set by ue_spawn for
                    # procedural waves; absent for regular USoundBase assets).
                    try:
                        self._cached_pcm = getattr(src, 'sound_pcm', None)
                    except Exception:
                        pass
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
            snd, pcm = _decode_sound_from_path(path)
            if snd is not None:
                self._cached_sound = snd
                self._cached_pcm = pcm
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
        # Tick-based hover detection — see CRASH NOTE in module header for
        # why we can't bind cursor-over events.
        hovered = False
        try:
            hit = self.uobject.get_hit_result_under_cursor(
                ECollisionChannel.ECC_WorldDynamic)
            hovered = hit is not None and hit.actor == self.uobject
        except Exception:
            hovered = False
        if hovered != self._hovered:
            self._hovered = hovered
            if hovered:
                d, bs = self.HOVER_DELTA, self.base_scale
                self.target_scale = FVector(bs.x - d, bs.y - d, bs.z - d)
            else:
                self.target_scale = self.base_scale

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
        # Re-queue PCM right before play.  See PROCEDURAL QUEUE in module header.
        if self._cached_pcm is not None:
            try:
                sound.queue_audio(self._cached_pcm)
            except Exception as e:
                ue.log_warning(f'SoundSphere: queue_audio failed: {e}')
        volume = float(self._read_attr('volume',     1.0))
        pitch = float(self._read_attr('pitch',      1.0))
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
