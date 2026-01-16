"""
history.py
Robust history tracking system with crash-safe logging + rotation.

Features:
- Separate classes per history type
- Automatic file logging with rotation
- Rotate by time window or entry count
- Folder per log session
- Log start/end markers
- Retention cleanup by count or age
- Clipboard tracking
- Optional keyboard logging
"""

import os
import json
import threading
import time
import shutil
from datetime import datetime, timedelta

try:
    import pyperclip
except ImportError:
    pyperclip = None

try:
    import pynput
    from pynput import keyboard
except ImportError:
    pynput = None


# --- Ensure log directory exists ---
LOG_DIR = os.path.join(os.getcwd(), "Logs")
os.makedirs(LOG_DIR, exist_ok=True)


# ------------------------------------------------------------
# Base History With Rotation + Retention
# ------------------------------------------------------------
class BaseHistory:
    def __init__(
        self,
        name,
        rotate_by="session",      # session, second, minute, hour, day, week, month, year
        max_entries=None,         # int
        max_files=None,           # retention count
        max_age=None,             # timedelta
    ):
        self.name = name
        self.data = []
        self.timestamps = []
        self.enabled = True

        self.rotate_by = rotate_by
        self.max_entries = max_entries
        self.max_files = max_files
        self.max_age = max_age

        self.entries_written = 0
        self.log_start_time = datetime.now()

        self.base_dir = os.path.join(LOG_DIR, self.name)
        os.makedirs(self.base_dir, exist_ok=True)

        self._open_new_log()

    # ---------------- Rotation ---------------- #

    def _rotation_delta(self):
        if self.rotate_by == "session":
            return None
        if self.rotate_by == "second":
            return timedelta(seconds=1)
        if self.rotate_by == "minute":
            return timedelta(minutes=1)
        if self.rotate_by == "hour":
            return timedelta(hours=1)
        if self.rotate_by == "day":
            return timedelta(days=1)
        if self.rotate_by == "week":
            return timedelta(weeks=1)
        if self.rotate_by == "month":
            return timedelta(days=30)
        if self.rotate_by == "year":
            return timedelta(days=365)
        return None

    def _should_rotate(self):
        if self.max_entries and self.entries_written >= self.max_entries:
            return True

        delta = self._rotation_delta()
        if delta and datetime.now() - self.log_start_time >= delta:
            return True

        return False

    def _open_new_log(self):
        self.log_start_time = datetime.now()
        self.entries_written = 0

        folder_name = self.log_start_time.strftime("%Y-%m-%d_%H-%M-%S")
        self.log_folder = os.path.join(self.base_dir, folder_name)
        os.makedirs(self.log_folder, exist_ok=True)

        self.log_file = os.path.join(self.log_folder, f"{self.name}.log")

        with open(self.log_file, "w", encoding="utf-8") as f:
            f.write(json.dumps({"log_start": self.log_start_time.isoformat()}) + "\n")

    def _close_log(self):
        try:
            with open(self.log_file, "a", encoding="utf-8") as f:
                f.write(json.dumps({"log_end": datetime.now().isoformat()}) + "\n")
        except Exception:
            pass

        self._cleanup_logs()

    def _rotate(self):
        self._close_log()
        self._open_new_log()

    # ---------------- Cleanup ---------------- #

    def _cleanup_logs(self):
        if not os.path.exists(self.base_dir):
            return

        folders = sorted(os.listdir(self.base_dir))
        paths = [os.path.join(self.base_dir, f) for f in folders if os.path.isdir(os.path.join(self.base_dir, f))]

        # Max files
        if self.max_files and len(paths) > self.max_files:
            for p in paths[:-self.max_files]:
                shutil.rmtree(p, ignore_errors=True)

        # Max age
        if self.max_age:
            now = datetime.now()
            for p in paths:
                try:
                    ts = datetime.strptime(os.path.basename(p), "%Y-%m-%d_%H-%M-%S")
                    if now - ts > self.max_age:
                        shutil.rmtree(p, ignore_errors=True)
                except Exception:
                    pass

    # ---------------- Logging ---------------- #

    def log(self, item):
        if not self.enabled:
            return

        if self._should_rotate():
            self._rotate()

        ts = datetime.now()

        if isinstance(item, list):
            self.data.extend(item)
            self.timestamps.extend([ts] * len(item))
            self._write_to_file(item, ts)
        else:
            self.data.append(item)
            self.timestamps.append(ts)
            self._write_to_file(item, ts)

    def _write_to_file(self, item, ts):
        with open(self.log_file, "a", encoding="utf-8") as f:
            if isinstance(item, list):
                for i in item:
                    f.write(json.dumps({"timestamp": ts.isoformat(), "data": i}) + "\n")
                    self.entries_written += 1
            else:
                f.write(json.dumps({"timestamp": ts.isoformat(), "data": item}) + "\n")
                self.entries_written += 1

    # ---------------- API ---------------- #

    def enable(self):
        self.enabled = True

    def disable(self):
        self.enabled = False

    def get_history(self):
        return self.data

    def get_timestamps(self):
        return self.timestamps

    def clear(self):
        self.data.clear()
        self.timestamps.clear()
        self._rotate()


# ------------------------------------------------------------
# Subclasses
# ------------------------------------------------------------
class KeyboardHistory(BaseHistory):
    def __init__(self):
        super().__init__("Keyboard")


class CopyHistory(BaseHistory):
    def __init__(self):
        super().__init__("Copy")
        self.last_clipboard = None

    def poll_clipboard(self):
        if pyperclip is None:
            return
        try:
            current = pyperclip.paste()
            if current != self.last_clipboard and current != "":
                self.last_clipboard = current
                self.log(current)
        except Exception as e:
            print(f"Clipboard polling error: {e}")


class ActionHistory(BaseHistory):
    def __init__(self):
        super().__init__("Action")


class InsertHistory(BaseHistory):
    def __init__(self):
        super().__init__("Insert")


class DeleteHistory(BaseHistory):
    def __init__(self):
        super().__init__("Delete")


class MovementHistory(BaseHistory):
    def __init__(self):
        super().__init__("Movement")


class UndoHistory(BaseHistory):
    def __init__(self):
        super().__init__("Undo")


class CrashHistory(BaseHistory):
    def __init__(self):
        super().__init__("Crash")


# ------------------------------------------------------------
# History Manager
# ------------------------------------------------------------
class HistoryManager:
    POLL_INTERVAL = 0.5

    def __init__(self, auto_start=True, poll_clipboard=True, keyboard_logging=True):
        self.histories = {
            "Keyboard": KeyboardHistory(),
            "Copy": CopyHistory(),
            "Action": ActionHistory(),
            "Insert": InsertHistory(),
            "Delete": DeleteHistory(),
            "Movement": MovementHistory(),
            "Undo": UndoHistory(),
            "Crash": CrashHistory(),
        }

        self._stop_event = threading.Event()
        self.poll_clipboard_enabled = poll_clipboard
        self.keyboard_logging_enabled = keyboard_logging

        if auto_start:
            self.start_background_thread()

    # --- Logging API ---

    def log(self, history_type, item):
        if history_type not in self.histories:
            raise ValueError(f"Unknown history type: {history_type}")
        self.histories[history_type].log(item)

    def enable_type(self, history_type):
        self.histories[history_type].enable()

    def disable_type(self, history_type):
        self.histories[history_type].disable()

    def get_history(self, history_type):
        return self.histories[history_type].get_history()

    def get_timestamps(self, history_type):
        return self.histories[history_type].get_timestamps()

    def clear_history(self, history_type=None):
        if history_type:
            self.histories[history_type].clear()
        else:
            for h in self.histories.values():
                h.clear()

    # --- Background tasks ---

    def start_background_thread(self):
        self._thread = threading.Thread(target=self._background_loop, daemon=True)
        self._thread.start()

        if self.keyboard_logging_enabled and pynput is not None:
            self._start_keyboard_listener()

    def stop_background_thread(self):
        self._stop_event.set()

        if hasattr(self, "_keyboard_listener"):
            self._keyboard_listener.stop()

        if hasattr(self, "_thread"):
            self._thread.join()

        for h in self.histories.values():
            h._close_log()

    def _background_loop(self):
        while not self._stop_event.is_set():
            if self.poll_clipboard_enabled:
                self.poll_copy()
            time.sleep(self.POLL_INTERVAL)

    # --- Clipboard polling ---

    def poll_copy(self):
        self.histories["Copy"].poll_clipboard()

    # --- Keyboard logging ---

    def _start_keyboard_listener(self):
        def on_press(key):
            try:
                self.log("Keyboard", str(key).replace("'", ""))
            except Exception as e:
                self.log("Crash", f"Keyboard logging error: {e}")

        self._keyboard_listener = keyboard.Listener(on_press=on_press)
        self._keyboard_listener.start()
