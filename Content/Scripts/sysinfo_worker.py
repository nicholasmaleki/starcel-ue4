"""
sysinfo_worker.py
=================
Background daemon that periodically calls sysinfo.get_info_string() and writes
the result to a text file. Spawned by pyactor_sysmon.py via subprocess.Popen
against an external system Python interpreter, so the heavy WMI / PowerShell /
HTTP collection work doesn't block the UE thread.

Run:
    python sysinfo_worker.py [--parent-pid PID] [--interval SECS]
                             [--mode MODE] [--units UNITS]

Exits when --parent-pid is no longer alive (so workers don't leak if the
editor crashes) or on SIGTERM / SIGINT.

Writes:
    {APPDATA}/sysinfo/sysmon_text.txt    formatted display string
    {APPDATA}/sysinfo/sysmon_worker.pid  own PID (cleared on graceful exit)
"""

from __future__ import annotations

import argparse
import os
import platform
import signal
import sys
import time
from pathlib import Path

import psutil

# sysinfo.py / activity_tracker.py live in the same directory. Make sure
# they import even if cwd is somewhere else.
sys.path.insert(0, str(Path(__file__).resolve().parent))

from sysinfo import get_info_string  # noqa: E402


def _data_dir() -> Path:
    p = platform.system()
    if p == "Windows":
        base = Path(os.environ.get("APPDATA", Path.home()))
    elif p == "Darwin":
        base = Path.home() / "Library" / "Application Support"
    else:
        base = Path(os.environ.get("XDG_DATA_HOME", Path.home() / ".local" / "share"))
    d = base / "sysinfo"
    d.mkdir(parents=True, exist_ok=True)
    return d


DATA_DIR = _data_dir()
RESULT_FILE = DATA_DIR / "sysmon_text.txt"
PID_FILE = DATA_DIR / "sysmon_worker.pid"


def _write_atomic(path: Path, text: str) -> None:
    tmp = path.with_suffix(path.suffix + ".tmp")
    tmp.write_text(text, encoding="utf-8")
    tmp.replace(path)


def _format(mode: str, units: str) -> str:
    """sysinfo string + optional activity_tracker APM line — matches the
    original PyActorSysmon._update() output exactly."""
    parts = []
    try:
        s = get_info_string(mode=mode, units=units)
        if s:
            parts.append(s.strip())
    except Exception as e:
        parts.append(f"[sysinfo error: {e}]")

    try:
        from activity_tracker import read_stats
        stats = read_stats()
        if stats:
            parts.append(
                f"APM: {stats.get('actions_per_min', 0.0):.1f}  "
                f"Clicks/min: {stats.get('clicks_per_min', 0.0):.1f}  "
                f"Keys/min: {stats.get('keys_per_min', 0.0):.1f}  "
                f"Mouse px: {stats.get('mouse_distance_px', 0.0):.0f}"
            )
    except Exception:
        pass

    return "\n".join(parts) if parts else "(no data)"


def _clear_pid_if_ours() -> None:
    try:
        if PID_FILE.exists() and int(PID_FILE.read_text().strip()) == os.getpid():
            PID_FILE.unlink()
    except Exception:
        pass


def _shutdown(*_):
    _clear_pid_if_ours()
    sys.exit(0)


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--parent-pid", type=int, default=None)
    ap.add_argument("--interval",   type=float, default=300.0)
    ap.add_argument("--mode",       default="minimal")
    ap.add_argument("--units",      default="usa")
    args = ap.parse_args()

    PID_FILE.write_text(str(os.getpid()))

    signal.signal(signal.SIGINT,  _shutdown)
    signal.signal(signal.SIGTERM, _shutdown)

    parent = args.parent_pid

    while True:
        if parent is not None and not psutil.pid_exists(parent):
            _shutdown()

        _write_atomic(RESULT_FILE, _format(args.mode, args.units))

        # Sleep in small chunks so we exit promptly when the parent dies.
        slept = 0.0
        while slept < args.interval:
            chunk = min(2.0, args.interval - slept)
            time.sleep(chunk)
            slept += chunk
            if parent is not None and not psutil.pid_exists(parent):
                _shutdown()


if __name__ == "__main__":
    sys.exit(main())
