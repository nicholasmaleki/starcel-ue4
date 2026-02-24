import unreal_engine as ue
from unreal_engine import FVector, FRotator, FTransform

# ---------------------------------------------------------------------------
# Python component: clickable sound sphere
# ---------------------------------------------------------------------------
class SoundSphere:
    """
    Attach to BP_SoundSphere.
    Blueprint needs StaticMeshComponent (sphere) + public Sound (SoundBase).
    """
    def begin_play(self):
        self.sound = getattr(self.uobject, 'Sound', None)
        try:
            smc = self.uobject.StaticMeshComponent
            smc.bind_event('OnClicked', self.on_clicked)
            # smc.bind_event('OnComponentBeginOverlap', self.on_overlap)
        except Exception as e:
            ue.log_warning(f'SoundSphereActor: could not bind events: {e}')

    def on_clicked(self, mesh, button):
        self._play()

    # def on_overlap(self, *args):
    #     self._play()

    def _play(self):
        if self.sound is None:
            self.sound = getattr(self.uobject, 'Sound', None)
        if self.sound:
            self.uobject.play_sound_at_location(
                self.sound, self.uobject.get_actor_location())
        else:
            ue.log_warning('SoundSphereActor: no Sound asset assigned.')