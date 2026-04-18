"""
activity_tracker.py
====================
Background process that tracks mouse/keyboard activity metrics globally.
Runs as a daemon and writes stats to a JSON file for sysinfo.py to read.

Install:  pip install pynput
Run:      python activity_tracker.py          (runs forever)
          python activity_tracker.py --reset  (resets all counters)

Stats tracked
-------------
- Mouse: total clicks (L/R/M), distance traveled (px), scroll events
- Keyboard: total keystrokes, top keys
- Derived: clicks/min, keystrokes/min, actions/min
- Session: start time, uptime
"""

from __future__ import annotations

import argparse
import json
import math
import os
import platform
import signal
import sys
import time
from datetime import datetime
from pathlib import Path
from threading import Lock
from typing import Any, Dict, Optional

# storage path
_PLATFORM = platform.system()

def _default_data_dir() -> Path:
    if _PLATFORM == "Windows":
        base = Path(os.environ.get("APPDATA", Path.home()))
    elif _PLATFORM == "Darwin":
        base = Path.home() / "Library" / "Application Support"
    else:
        base = Path(os.environ.get("XDG_DATA_HOME", Path.home() / ".local" / "share"))
    d = base / "sysinfo"
    d.mkdir(parents=True, exist_ok=True)
    return d

DATA_DIR      = _default_data_dir()
STATS_FILE    = DATA_DIR / "activity_stats.json"
PERSIST_FILE  = DATA_DIR / "activity_persist.json"   # survives restarts
LOG_FILE      = DATA_DIR / "activity_log.txt"

_lock = Lock()

# state
_state: Dict[str, Any] = {
    "session_start":     datetime.now().isoformat(),
    "last_update":       datetime.now().isoformat(),
    # mouse
    "mouse_left_clicks":   0,
    "mouse_right_clicks":  0,
    "mouse_middle_clicks": 0,
    "mouse_total_clicks":  0,
    "mouse_scroll_events": 0,
    "mouse_distance_px":   0.0,
    "mouse_last_x":        None,
    "mouse_last_y":        None,
    # keyboard
    "key_total":           0,
    "key_counts":          {},  # key -> count
    # rates (computed)
    "clicks_per_min":      0.0,
    "keys_per_min":        0.0,
    "actions_per_min":     0.0,
}

# Load persistent totals (all-time, across restarts)
def _load_persist() -> Dict[str, Any]:
    try:
        if PERSIST_FILE.exists():
            return json.loads(PERSIST_FILE.read_text())
    except Exception:
        pass
    return {
        "alltime_mouse_clicks": 0,
        "alltime_key_total":    0,
        "alltime_distance_px":  0.0,
        "alltime_scroll":       0,
    }

_persist = _load_persist()


def _save() -> None:
    """Write current stats + persist to disk atomically."""
    with _lock:
        now = datetime.now()
        _state["last_update"] = now.isoformat()

        # Compute rates over session
        session_sec = (now - datetime.fromisoformat(_state["session_start"])).total_seconds()
        mins = max(session_sec / 60, 0.01667)

        _state["clicks_per_min"]  = round(_state["mouse_total_clicks"] / mins, 2)
        _state["keys_per_min"]    = round(_state["key_total"] / mins, 2)
        _state["actions_per_min"] = round((_state["mouse_total_clicks"] + _state["key_total"]) / mins, 2)

        # Merge with persist
        combined = dict(_state)
        combined["alltime_mouse_clicks"] = _persist["alltime_mouse_clicks"]
        combined["alltime_key_total"]    = _persist["alltime_key_total"]
        combined["alltime_distance_px"]  = _persist["alltime_distance_px"]
        combined["alltime_scroll"]       = _persist["alltime_scroll"]

        # Write stats (for sysinfo.py to read)
        tmp = STATS_FILE.with_suffix(".tmp")
        tmp.write_text(json.dumps(combined, indent=2))
        tmp.replace(STATS_FILE)

        # Write persist
        PERSIST_FILE.write_text(json.dumps(_persist, indent=2))


def _append_log() -> None:
    """Append a summary line to the activity log."""
    with _lock:
        now = datetime.now()
        line = (
            f"{now.strftime('%Y-%m-%d %H:%M:%S')}  "
            f"clicks={_state['mouse_total_clicks']}  "
            f"keys={_state['key_total']}  "
            f"distance_px={_state['mouse_distance_px']:.0f}  "
            f"apm={_state['actions_per_min']:.1f}\n"
        )
        with LOG_FILE.open("a", encoding="utf-8") as f:
            f.write(line)


# pynput listeners
def _start_listeners() -> None:
    try:
        from pynput import mouse, keyboard
    except ImportError:
        print("pynput not installed. Run: pip install pynput", file=sys.stderr)
        sys.exit(1)

    def on_click(x, y, button, pressed):
        if not pressed:
            return
        with _lock:
            btn = str(button).lower()
            if "left"   in btn: _state["mouse_left_clicks"]   += 1
            if "right"  in btn: _state["mouse_right_clicks"]  += 1
            if "middle" in btn: _state["mouse_middle_clicks"] += 1
            _state["mouse_total_clicks"] += 1
            _persist["alltime_mouse_clicks"] += 1

    def on_move(x, y):
        with _lock:
            lx = _state["mouse_last_x"]
            ly = _state["mouse_last_y"]
            if lx is not None and ly is not None:
                dist = math.hypot(x - lx, y - ly)
                _state["mouse_distance_px"] += dist
                _persist["alltime_distance_px"] += dist
            _state["mouse_last_x"] = x
            _state["mouse_last_y"] = y

    def on_scroll(x, y, dx, dy):
        with _lock:
            _state["mouse_scroll_events"] += abs(dy) + abs(dx)
            _persist["alltime_scroll"] += abs(dy) + abs(dx)

    def on_press(key):
        with _lock:
            _state["key_total"] += 1
            _persist["alltime_key_total"] += 1
            key_str = str(key).replace("'", "").replace("Key.", "")
            _state["key_counts"][key_str] = _state["key_counts"].get(key_str, 0) + 1

    mouse_listener = mouse.Listener(on_click=on_click, on_move=on_move, on_scroll=on_scroll)
    keyboard_listener = keyboard.Listener(on_press=on_press)

    mouse_listener.daemon    = True
    keyboard_listener.daemon = True
    mouse_listener.start()
    keyboard_listener.start()

    print(f"[activity_tracker] Listening... stats → {STATS_FILE}")
    print(f"[activity_tracker] Log         → {LOG_FILE}")

    SAVE_INTERVAL = 5    # seconds between disk writes
    LOG_INTERVAL  = 300  # 5 minutes between log entries
    last_log      = time.time()

    def _shutdown(sig, frame):
        _save()
        _append_log()
        print("\n[activity_tracker] Saved and exiting.")
        sys.exit(0)

    signal.signal(signal.SIGINT, _shutdown)
    signal.signal(signal.SIGTERM, _shutdown)

    while True:
        time.sleep(SAVE_INTERVAL)
        _save()
        if time.time() - last_log >= LOG_INTERVAL:
            _append_log()
            last_log = time.time()


def read_stats() -> Optional[Dict[str, Any]]:
    """Called by sysinfo.py to read latest stats (non-blocking)."""
    try:
        if STATS_FILE.exists():
            return json.loads(STATS_FILE.read_text())
    except Exception:
        pass
    return None


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="System activity tracker daemon")
    parser.add_argument("--reset", action="store_true", help="Reset all counters and exit")
    args = parser.parse_args()

    if args.reset:
        for f in [STATS_FILE, PERSIST_FILE]:
            if f.exists():
                f.unlink()
        print("Counters reset.")
        sys.exit(0)

    _start_listeners()
