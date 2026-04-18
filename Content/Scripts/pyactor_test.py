"""Minimal test PyActor — begin_play logs 'Pyactor: hello world' and flips
a module-level flag so test_spawn can confirm _spawn_pyactor wired the
PythonModule/PythonClass correctly."""
import unreal_engine as ue

# Reset by test_pyactor_assign before each run, set by PyActorTest.begin_play.
begin_play_fired = False


class PyActorTest:
    def begin_play(self):
        global begin_play_fired
        begin_play_fired = True
        ue.log('Pyactor: hello world')
