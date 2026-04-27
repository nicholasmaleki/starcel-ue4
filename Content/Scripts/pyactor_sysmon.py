import os
import shutil
import subprocess
from pathlib import Path

import unreal_engine as ue
from unreal_engine_tools import find_component

# Python component: live system monitor (background-process variant)
#
# Spawn via spawn_system_monitor(...) in ue_spawn.py.
#
# Architecture
# ------------
# A separate Python process (sysinfo_worker.py) does the heavy WMI /
# PowerShell / HTTP work and writes the formatted display string to
# {APPDATA}/sysinfo/sysmon_text.txt. This PyActor only reads that file
# from tick(), so the UE thread is never blocked by sysinfo collection.
#
# The worker is launched against an external system Python — NOT
# sys.executable, which inside UE is UE4Editor.exe. The worker self-exits
# when our PID dies so it doesn't leak on editor crash.


_SCRIPT_DIR = Path(__file__).resolve().parent
_DATA_DIR = Path(os.environ.get("APPDATA", str(Path.home()))) / "sysinfo"
_RESULT_FILE = _DATA_DIR / "sysmon_text.txt"
_PID_FILE = _DATA_DIR / "sysmon_worker.pid"
_WORKER_PY = _SCRIPT_DIR / "sysinfo_worker.py"


def _find_python():
    """Locate an external Python interpreter. Never sys.executable — inside
    UE that's UE4Editor.exe and would re-launch the editor."""
    for name in ("python", "python3", "py"):
        p = shutil.which(name)
        if p and "ue4editor" not in p.lower() and "unrealeditor" not in p.lower():
            return p
    for p in (
        Path.home() / "AppData/Local/Programs/Python/Python39/python.exe",
        Path.home() / "AppData/Local/Programs/Python/Python310/python.exe",
        Path.home() / "AppData/Local/Programs/Python/Python311/python.exe",
        Path.home() / "AppData/Local/Programs/Python/Python312/python.exe",
        Path.home() / "AppData/Local/Programs/Python/Python313/python.exe",
        Path("C:/Python39/python.exe"),
        Path("C:/Python310/python.exe"),
    ):
        if p.exists():
            return str(p)
    return None


def _kill_prior_worker():
    """If a previous worker is still alive (e.g. script hot-reloaded without
    end_play firing), terminate it before spawning a new one."""
    try:
        if not _PID_FILE.exists():
            return
        pid = int(_PID_FILE.read_text().strip())
    except Exception:
        return
    try:
        import psutil
        if psutil.pid_exists(pid):
            psutil.Process(pid).terminate()
    except Exception:
        pass
    try:
        _PID_FILE.unlink()
    except Exception:
        pass


class PyActorSysmon:
    """
    Reads the worker-written display string from disk and pushes it to a
    Text3DComponent. All expensive collection happens out-of-process.
    """

    READ_INTERVAL = 1.0   # seconds between file polls (cheap stat + maybe read)
    WORKER_INTERVAL = 300 # seconds between sysinfo refreshes in the worker

    def begin_play(self):
        self._elapsed = 0.0
        self.text3d = None
        self._proc = None
        self._mtime = 0.0

        py = _find_python()
        if py is None:
            ue.log_warning(
                "PyActorSysmon: no external Python found on PATH or in common "
                "install locations — sysmon will stay on 'Loading...'. Install "
                "Python 3.9+ and ensure psutil is available."
            )
            return

        _kill_prior_worker()

        cmd = [
            py, str(_WORKER_PY),
            "--parent-pid", str(os.getpid()),
            "--interval",   str(self.WORKER_INTERVAL),
            "--mode",       "minimal",
            "--units",      "usa",
        ]
        flags = getattr(subprocess, "CREATE_NO_WINDOW", 0)
        env = dict(os.environ)
        env["PYTHONIOENCODING"] = "utf-8"
        try:
            self._proc = subprocess.Popen(
                cmd,
                cwd=str(_SCRIPT_DIR),
                creationflags=flags,
                env=env,
                stdout=subprocess.DEVNULL,
                stderr=subprocess.DEVNULL,
                stdin=subprocess.DEVNULL,
            )
            ue.log(f"PyActorSysmon: worker spawned (PID {self._proc.pid})")
        except Exception as e:
            ue.log_warning(f"PyActorSysmon: failed to spawn worker: {e}")
            self._proc = None

    def tick(self, dt):
        # Lazy component lookup — components are added after BeginPlay.
        if self.text3d is None:
            try:
                self.text3d = find_component(self.uobject, "Text3DComponent")
            except Exception:
                pass
            if self.text3d is None:
                return

        self._elapsed += dt
        if self._elapsed < self.READ_INTERVAL:
            return
        self._elapsed = 0.0

        try:
            st = _RESULT_FILE.stat()
        except FileNotFoundError:
            return
        if st.st_mtime <= self._mtime:
            return
        self._mtime = st.st_mtime

        try:
            text = _RESULT_FILE.read_text(encoding="utf-8")
        except Exception as e:
            ue.log_warning(f"PyActorSysmon: failed to read result file: {e}")
            return

        try:
            self.text3d.Text = text
        except Exception as e:
            ue.log_warning(f"PyActorSysmon: failed to set Text3D text: {e}")

    def end_play(self, reason):
        if self._proc is not None:
            try:
                self._proc.terminate()
            except Exception:
                pass
            self._proc = None
