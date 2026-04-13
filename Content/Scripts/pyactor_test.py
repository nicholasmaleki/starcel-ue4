"""Simple test PyActor that logs begin_play/tick to verify module+class assignment."""
import unreal_engine as ue


class PyActorTest:
    """Attach to a BP_PyActor to verify PythonModule/PythonClass assignment works.

    Logs on begin_play and every 2 seconds during tick.
    """

    def begin_play(self):
        self._timer = 0.0
        self._tick_count = 0
        actor_name = 'unknown'
        try:
            actor_name = self.uobject.get_name()
        except Exception:
            pass
        ue.log(f'PyActorTest: begin_play OK on "{actor_name}"')

    def tick(self, dt):
        self._timer += dt
        if self._timer >= 2.0:
            self._timer = 0.0
            self._tick_count += 1
            ue.log(f'PyActorTest: tick #{self._tick_count}')
