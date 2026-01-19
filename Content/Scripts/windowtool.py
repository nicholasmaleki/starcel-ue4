import ctypes
import ctypes.wintypes
import win32gui
import win32con
import win32process
import win32api
import threading
import subprocess
import sys
import os
import signal
import time
import struct

# --------------------------
# Constants
# --------------------------
SPI_GETWORKAREA = 0x0030
PROCESS_QUERY_LIMITED_INFORMATION = 0x1000

_bg_processes = {}  # target_exe -> subprocess.Popen
_watchdog_thread = None
_watchdog_running = False


# --------------------------
# Helpers
# --------------------------
def get_exe_name_from_hwnd(hwnd):
    try:
        _, pid = win32process.GetWindowThreadProcessId(hwnd)
        hProcess = win32api.OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, False, pid)
        buffer = ctypes.create_unicode_buffer(1024)
        size = ctypes.wintypes.DWORD(len(buffer))
        ctypes.windll.kernel32.QueryFullProcessImageNameW(int(hProcess), 0, buffer, ctypes.byref(size))
        win32api.CloseHandle(hProcess)
        return os.path.basename(buffer.value).lower()
    except Exception:
        return None


def is_top_level_window(hwnd):
    return win32gui.GetParent(hwnd) == 0


def print_all_open_window_exes():
    """Print all visible top-level windows and their EXEs"""
    print("\nOpen windows:")
    seen = set()

    def enum_cb(hwnd, _):
        if not is_top_level_window(hwnd):
            return True
        exe = get_exe_name_from_hwnd(hwnd)
        title = win32gui.GetWindowText(hwnd)
        if exe:
            key = (exe, title)
            if key not in seen:
                seen.add(key)
                print(f"{exe:30} | {title}")
        return True

    win32gui.EnumWindows(enum_cb, None)
    print()


def get_all_monitors():
    """Get information about all monitors"""
    monitors = []

    def callback(hMonitor, hdcMonitor, lprcMonitor, dwData):
        monitors.append(hMonitor)
        return True

    # EnumDisplayMonitors callback
    MONITORENUMPROC = ctypes.WINFUNCTYPE(
        ctypes.c_int,
        ctypes.c_ulong,
        ctypes.c_ulong,
        ctypes.POINTER(ctypes.wintypes.RECT),
        ctypes.c_double
    )

    callback_ptr = MONITORENUMPROC(callback)
    ctypes.windll.user32.EnumDisplayMonitors(None, None, callback_ptr, 0)
    return monitors


def get_monitor_rect(hwnd=None, monitor_number=None):
    """Get the full monitor dimensions including taskbar area

    Args:
        hwnd: Window handle (used if monitor_number is None)
        monitor_number: Specific monitor index (0-based)
    """
    try:
        if monitor_number is not None:
            # Get specific monitor
            monitors = get_all_monitors()
            if 0 <= monitor_number < len(monitors):
                monitor = monitors[monitor_number]
                monitor_info = win32api.GetMonitorInfo(monitor)
                return monitor_info['Monitor']

        # Use window's current monitor
        if hwnd:
            monitor = win32api.MonitorFromWindow(hwnd, win32con.MONITOR_DEFAULTTONEAREST)
            monitor_info = win32api.GetMonitorInfo(monitor)
            return monitor_info['Monitor']

        # Fallback to primary monitor
        width = ctypes.windll.user32.GetSystemMetrics(0)  # SM_CXSCREEN
        height = ctypes.windll.user32.GetSystemMetrics(1)  # SM_CYSCREEN
        return (0, 0, width, height)
    except Exception:
        width = ctypes.windll.user32.GetSystemMetrics(0)
        height = ctypes.windll.user32.GetSystemMetrics(1)
        return (0, 0, width, height)


def resize_to_full_screen(hwnd, custom_rect=None, monitor_number=None):
    """Resize window to fill screen or custom rectangle

    Args:
        hwnd: Window handle
        custom_rect: Optional tuple (left, top, width, height)
        monitor_number: Optional monitor index (0-based)
    """
    try:
        if custom_rect:
            # Use custom rectangle (left, top, width, height)
            final_left, final_top, final_width, final_height = custom_rect
        else:
            # Get monitor dimensions
            left, top, right, bottom = get_monitor_rect(hwnd, monitor_number)

            # Simply use the monitor dimensions directly
            # Don't subtract borders - just position at screen edge
            final_left = left
            final_top = top
            final_width = right - left
            final_height = bottom - top

        # Remove maximize style if present
        style = win32gui.GetWindowLong(hwnd, win32con.GWL_STYLE)
        if style & win32con.WS_MAXIMIZE:
            style &= ~win32con.WS_MAXIMIZE
            win32gui.SetWindowLong(hwnd, win32con.GWL_STYLE, style)

        # Position window
        win32gui.SetWindowPos(
            hwnd,
            None,
            final_left,
            final_top,
            final_width,
            final_height,
            win32con.SWP_NOZORDER | win32con.SWP_NOACTIVATE
        )

    except Exception as e:
        pass


def move_to_bottom(hwnd):
    """Move window to bottom of z-order"""
    try:
        win32gui.SetWindowPos(hwnd, win32con.HWND_BOTTOM, 0, 0, 0, 0,
                              win32con.SWP_NOMOVE | win32con.SWP_NOSIZE | win32con.SWP_NOACTIVATE)
    except Exception:
        pass


def get_window_rect_tuple(hwnd):
    """Get window rectangle as tuple for comparison"""
    try:
        rect = win32gui.GetWindowRect(hwnd)
        return rect
    except Exception:
        return None


# --------------------------
# Event-driven AlwaysBottomHook
# --------------------------
class AlwaysBottomHook:
    def __init__(self, target_exe, expand_to_screen=True, custom_rect=None, monitor_number=None):
        """
        Args:
            target_exe: Name of executable to track (e.g., 'notepad.exe')
            expand_to_screen: If True, resize to full screen
            custom_rect: Optional tuple (left, top, width, height) for custom positioning
            monitor_number: Optional monitor index (0-based, None = use window's current monitor)
        """
        self.target_exe = target_exe.lower()
        self.expand = expand_to_screen
        self.custom_rect = custom_rect
        self.monitor_number = monitor_number
        self.running = True
        self.foreground_mode = {}  # hwnd -> is_in_foreground
        self.tracked_windows = set()
        self.window_positions = {}  # hwnd -> (left, top, right, bottom)
        self.hooks = []
        self.callback_ref = None

        # Initial setup
        self._setup_existing_windows()

        # Start event hook thread (no polling thread needed - fully event-driven)
        self.hook_thread = threading.Thread(target=self._event_loop, daemon=True)
        self.hook_thread.start()

    def _setup_existing_windows(self):
        """Find and configure existing windows"""

        def enum_cb(hwnd, _):
            if not is_top_level_window(hwnd):
                return True
            exe = get_exe_name_from_hwnd(hwnd)
            if exe == self.target_exe:
                self.tracked_windows.add(hwnd)
                self.foreground_mode[hwnd] = False
                if self.expand:
                    resize_to_full_screen(hwnd, self.custom_rect, self.monitor_number)
                    self.window_positions[hwnd] = get_window_rect_tuple(hwnd)
                move_to_bottom(hwnd)
            return True

        win32gui.EnumWindows(enum_cb, None)

    def _is_alt_tab_active(self):
        """Check if Alt+Tab switcher is active"""
        try:
            # Check if Alt key is pressed
            VK_MENU = 0x12  # Alt key
            alt_pressed = ctypes.windll.user32.GetAsyncKeyState(VK_MENU) & 0x8000

            if alt_pressed:
                return True

            # Also check for the Task Switcher window class
            foreground = win32gui.GetForegroundWindow()
            if foreground:
                try:
                    class_name = win32gui.GetClassName(foreground)
                    # Task switcher window classes
                    if class_name in ['MultitaskingViewFrame', 'Windows.UI.Core.CoreWindow', 'TaskSwitcherWnd']:
                        return True
                except Exception:
                    pass

            return False
        except Exception:
            return False

    def _event_loop(self):
        """Event hook with message pump"""
        EVENT_SYSTEM_MINIMIZESTART = 0x0016
        EVENT_SYSTEM_FOREGROUND = 0x0003
        EVENT_OBJECT_CREATE = 0x8000
        EVENT_OBJECT_SHOW = 0x8002
        EVENT_OBJECT_DESTROY = 0x8001
        EVENT_OBJECT_LOCATIONCHANGE = 0x800B
        WINEVENT_OUTOFCONTEXT = 0x0000

        def event_callback(hWinEventHook, event, hwnd, idObject, idChild, dwEventThread, dwmsEventTime):
            if idObject != 0 or idChild != 0 or hwnd == 0:
                return

            try:
                exe = get_exe_name_from_hwnd(hwnd)
                if exe != self.target_exe:
                    # Handle global foreground changes for focus monitoring
                    if event == EVENT_SYSTEM_FOREGROUND:
                        # Check if Alt+Tab is active - if so, don't do anything
                        alt_tab_active = self._is_alt_tab_active()
                        if alt_tab_active:
                            return  # Don't interfere during Alt+Tab

                        # Process tracked windows when foreground changes (and not Alt+Tab)
                        for tracked_hwnd in list(self.tracked_windows):
                            if not win32gui.IsWindow(tracked_hwnd):
                                self.tracked_windows.discard(tracked_hwnd)
                                self.foreground_mode.pop(tracked_hwnd, None)
                                self.window_positions.pop(tracked_hwnd, None)
                                continue

                            # If our window was in foreground mode but user switched away
                            if self.foreground_mode.get(tracked_hwnd, False):
                                if hwnd != tracked_hwnd:
                                    # User switched to a different window
                                    self.foreground_mode[tracked_hwnd] = False
                                    move_to_bottom(tracked_hwnd)
                            # Keep non-foreground windows at bottom
                            else:
                                move_to_bottom(tracked_hwnd)
                    return

                # Window created or shown
                if event in [EVENT_OBJECT_CREATE, EVENT_OBJECT_SHOW]:
                    if hwnd not in self.tracked_windows:
                        self.tracked_windows.add(hwnd)
                        self.foreground_mode[hwnd] = False
                        if self.expand:
                            resize_to_full_screen(hwnd, self.custom_rect, self.monitor_number)
                            self.window_positions[hwnd] = get_window_rect_tuple(hwnd)
                        move_to_bottom(hwnd)

                # Window destroyed
                elif event == EVENT_OBJECT_DESTROY:
                    self.tracked_windows.discard(hwnd)
                    self.foreground_mode.pop(hwnd, None)
                    self.window_positions.pop(hwnd, None)

                # Location/size changed - check if user moved/resized
                elif event == EVENT_OBJECT_LOCATIONCHANGE:
                    # Only resize if not in foreground mode
                    if not self.foreground_mode.get(hwnd, False) and self.expand:
                        current_rect = get_window_rect_tuple(hwnd)
                        expected_rect = self.window_positions.get(hwnd)
                        # Only resize if position changed from expected
                        if current_rect != expected_rect:
                            resize_to_full_screen(hwnd, self.custom_rect, self.monitor_number)
                            self.window_positions[hwnd] = get_window_rect_tuple(hwnd)

                # Minimize started - prevent it (Win+D support)
                elif event == EVENT_SYSTEM_MINIMIZESTART:
                    # Schedule restoration in a separate thread to avoid blocking
                    def restore_async():
                        for attempt in range(3):  # Try up to 3 times
                            time.sleep(0.05)
                            try:
                                if win32gui.IsWindow(hwnd):
                                    # Check if window is minimized
                                    if win32gui.IsIconic(hwnd):
                                        # Force restore
                                        win32gui.ShowWindow(hwnd, win32con.SW_RESTORE)
                                        time.sleep(0.01)
                                        if self.expand:
                                            resize_to_full_screen(hwnd, self.custom_rect, self.monitor_number)
                                            self.window_positions[hwnd] = get_window_rect_tuple(hwnd)
                                        if not self.foreground_mode.get(hwnd, False):
                                            move_to_bottom(hwnd)
                                        break  # Successfully restored, exit loop
                                    else:
                                        # Not minimized, we're done
                                        break
                            except Exception:
                                pass  # Try again on next iteration

                    threading.Thread(target=restore_async, daemon=True).start()

                # Foreground change (Alt+Tab)
                elif event == EVENT_SYSTEM_FOREGROUND:
                    # User explicitly focused this window - allow it and STOP sending to bottom
                    self.foreground_mode[hwnd] = True
                    if self.expand:
                        resize_to_full_screen(hwnd, self.custom_rect, self.monitor_number)
                        self.window_positions[hwnd] = get_window_rect_tuple(hwnd)
                    # Don't send to bottom - window should stay in foreground

            except Exception as e:
                pass

        # Create callback
        WINEVENTPROC = ctypes.WINFUNCTYPE(
            None,
            ctypes.wintypes.HANDLE,
            ctypes.wintypes.DWORD,
            ctypes.wintypes.HWND,
            ctypes.wintypes.LONG,
            ctypes.wintypes.LONG,
            ctypes.wintypes.DWORD,
            ctypes.wintypes.DWORD
        )

        self.callback_ref = WINEVENTPROC(event_callback)

        # Install hooks - note: we now listen to ALL foreground events, not just our window
        events = [
            EVENT_SYSTEM_MINIMIZESTART,
            EVENT_SYSTEM_FOREGROUND,
            EVENT_OBJECT_CREATE,
            EVENT_OBJECT_SHOW,
            EVENT_OBJECT_DESTROY,
            EVENT_OBJECT_LOCATIONCHANGE,
        ]

        for evt in events:
            hook = ctypes.windll.user32.SetWinEventHook(
                evt, evt, 0, self.callback_ref, 0, 0, WINEVENT_OUTOFCONTEXT
            )
            if hook:
                self.hooks.append(hook)

        # Message pump
        msg = ctypes.wintypes.MSG()
        while self.running:
            result = ctypes.windll.user32.GetMessageW(ctypes.byref(msg), 0, 0, 0)
            if result == 0 or not self.running:
                break
            ctypes.windll.user32.TranslateMessage(ctypes.byref(msg))
            ctypes.windll.user32.DispatchMessageW(ctypes.byref(msg))

        # Cleanup
        for hook in self.hooks:
            try:
                ctypes.windll.user32.UnhookWinEvent(hook)
            except Exception:
                pass

    def stop(self):
        """Stop the hook"""
        self.running = False
        try:
            ctypes.windll.user32.PostQuitMessage(0)
        except Exception:
            pass


# --------------------------
# Background process entry
# --------------------------
def _run_as_background(target_exe, expand_to_screen, custom_rect=None, monitor_number=None):
    hook = AlwaysBottomHook(target_exe, expand_to_screen, custom_rect, monitor_number)
    while True:
        time.sleep(1)


def _spawn_background(target_exe, expand_to_screen=True, custom_rect=None, monitor_number=None):
    python_exe = sys.executable
    module_path = os.path.abspath(__file__)

    # Build command with arguments
    args = [str(int(expand_to_screen))]

    if custom_rect:
        args.append("rect")
        args.extend(map(str, custom_rect))

    if monitor_number is not None:
        args.append("monitor")
        args.append(str(monitor_number))

    cmd = [
              python_exe,
              module_path,
              "--background",
              target_exe
          ] + args

    proc = subprocess.Popen(
        cmd,
        creationflags=subprocess.DETACHED_PROCESS | subprocess.CREATE_NEW_PROCESS_GROUP,
        close_fds=True
    )
    _bg_processes[target_exe.lower()] = proc
    return proc


# --------------------------
# Public API
# --------------------------
def start_background_hook(target_exe, expand_to_screen=True, custom_rect=None, monitor_number=None):
    """Start a background hook for the specified executable

    Args:
        target_exe: Name of executable (e.g., 'notepad.exe')
        expand_to_screen: If True, resize to full screen
        custom_rect: Optional tuple (left, top, width, height) for custom positioning
        monitor_number: Optional monitor index (0-based, None = use window's current monitor)

    Examples:
        # Fill entire screen on current monitor
        start_background_hook('notepad.exe', expand_to_screen=True)

        # Fill specific monitor
        start_background_hook('notepad.exe', expand_to_screen=True, monitor_number=1)

        # Custom position and size
        start_background_hook('notepad.exe', expand_to_screen=True, custom_rect=(0, 0, 1920, 1080))

        # No resizing, just keep at bottom
        start_background_hook('notepad.exe', expand_to_screen=False)
    """
    target_exe = target_exe.lower()
    proc = _bg_processes.get(target_exe)
    if proc and proc.poll() is None:
        return  # Already running
    _spawn_background(target_exe, expand_to_screen, custom_rect, monitor_number)

    global _watchdog_thread, _watchdog_running
    if not _watchdog_running:
        _watchdog_running = True
        _watchdog_thread = threading.Thread(target=_watchdog_loop, daemon=True)
        _watchdog_thread.start()


def stop_background_hook(target_exe):
    target_exe = target_exe.lower()
    proc = _bg_processes.get(target_exe)
    if proc and proc.poll() is None:
        try:
            proc.send_signal(signal.SIGTERM)
        except Exception:
            pass
    _bg_processes.pop(target_exe, None)


def stop_all_background_hooks():
    global _watchdog_running
    _watchdog_running = False
    for exe, proc in list(_bg_processes.items()):
        try:
            if proc.poll() is None:
                proc.send_signal(signal.SIGTERM)
        except Exception:
            pass
        _bg_processes.pop(exe, None)


def stop_all_background_hooks_systemwide():
    """Stop all background hooks system-wide by killing matching processes"""
    module_name = os.path.splitext(os.path.basename(__file__))[0]

    try:
        result = subprocess.run(
            ["wmic", "process", "where", "name='python.exe'", "get", "ProcessId,CommandLine"],
            capture_output=True, text=True, timeout=5
        )

        killed_count = 0
        for line in result.stdout.splitlines():
            if module_name in line and "--background" in line:
                parts = line.split()
                for part in reversed(parts):
                    try:
                        pid = int(part)
                        subprocess.run(
                            ["taskkill", "/PID", str(pid), "/F"],
                            capture_output=True, timeout=2
                        )
                        killed_count += 1
                        break
                    except (ValueError, subprocess.TimeoutExpired):
                        continue

        if killed_count == 0:
            print("No background hooks found")
        else:
            print(f"Killed {killed_count} background process(es)")

    except Exception as e:
        print(f"Error cleaning up background hooks: {e}")


def is_background_hook_running(target_exe):
    target_exe = target_exe.lower()
    proc = _bg_processes.get(target_exe)
    return proc and proc.poll() is None


# --------------------------
# Watchdog thread
# --------------------------
def _watchdog_loop():
    global _watchdog_running
    while _watchdog_running:
        for exe, proc in list(_bg_processes.items()):
            if proc.poll() is not None:
                _spawn_background(exe)
        time.sleep(2)


# --------------------------
# Entry for background process
# --------------------------
if len(sys.argv) > 1 and sys.argv[1] == "--background":
    target_exe = sys.argv[2]
    expand = bool(int(sys.argv[3])) if len(sys.argv) > 3 else True

    # Parse optional arguments
    custom_rect = None
    monitor_number = None

    i = 4
    while i < len(sys.argv):
        if sys.argv[i] == "rect" and i + 4 < len(sys.argv):
            custom_rect = tuple(map(int, sys.argv[i + 1:i + 5]))
            i += 5
        elif sys.argv[i] == "monitor" and i + 1 < len(sys.argv):
            monitor_number = int(sys.argv[i + 1])
            i += 2
        else:
            i += 1

    _run_as_background(target_exe, expand, custom_rect, monitor_number)



# Enables or disables system-wide minimize/maximize animations.
def set_global_window_animations(enable=True):
    try:
        # Define ANIMATIONINFO structure
        class ANIMATIONINFO(ctypes.Structure):
            _fields_ = [
                ("cbSize", ctypes.c_uint),
                ("iMinAnimate", ctypes.c_int)
            ]

        # Create and populate the structure
        ai = ANIMATIONINFO()
        ai.cbSize = ctypes.sizeof(ANIMATIONINFO)
        ai.iMinAnimate = 1 if enable else 0

        # Use ctypes to call SystemParametersInfoW directly
        ctypes.windll.user32.SystemParametersInfoW(
            win32con.SPI_SETANIMATION,
            ctypes.sizeof(ANIMATIONINFO),
            ctypes.byref(ai),
            win32con.SPIF_SENDCHANGE | win32con.SPIF_UPDATEINIFILE
        )

        if enable:
            print("Animations Enabled")
        else:
            print("Animations Disabled")

    except Exception as e:
        print(f"Error changing animation settings: {e}")