"""
sysinfo.py  v2
==============
Cross-platform system information library.
Supports: Windows (primary), macOS, Linux.

Public API
----------
    get_info_string(mode, units)  → str
    get_info_dict(mode, units)    → dict
    save_snapshot(path, mode, units)
    load_snapshots(path)          → list of summary dicts

Update interval
---------------
UPDATE_INTERVAL = 5  # seconds — reference for polling loops

Modes: "normal" | "advanced"
Units: "usa" (°F, mph) | "metric" (°C, km/h)

Install
-------
    pip install psutil pynput requests py-cpuinfo

Windows extras (optional):
    pip install wmi pywin32 GPUtil comtypes

macOS extras (optional):
    pip install pyobjc-framework-AppKit pyobjc-framework-Quartz

Activity tracking
-----------------
Run `python activity_tracker.py` in the background to enable mouse/keyboard metrics.
"""

from __future__ import annotations

import ctypes
import datetime
import json
import math
import os
import platform
import re
import shutil
import socket
import subprocess
import sys
import time
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple

import psutil

# ── OS detection ─────────────────────────────────────────────────────────────
_OS       = platform.system()
_IS_WIN   = _OS == "Windows"
_IS_MAC   = _OS == "Darwin"
_IS_LINUX = _OS == "Linux"

# ── Windows-only imports ─────────────────────────────────────────────────────
_WMI_OK = _GPUTIL_OK = _WINREG_OK = False
_WMI = None

if _IS_WIN:
    try:
        import winreg as _winreg
        _WINREG_OK = True
    except ImportError:
        pass
    try:
        import wmi as _wmi_mod
        _WMI = _wmi_mod.WMI()
        _WMI_OK = True
    except Exception:
        pass
    try:
        import GPUtil as _GPUtil
        _GPUTIL_OK = True
    except Exception:
        pass

# ── cross-platform optional ──────────────────────────────────────────────────
try:
    import cpuinfo as _cpuinfo
    _CPUINFO_OK = True
except Exception:
    _CPUINFO_OK = False

try:
    import requests as _requests
    _REQUESTS_OK = True
except Exception:
    _REQUESTS_OK = False

# ── Everything (Windows) ─────────────────────────────────────────────────────
_EVERYTHING_OK = False
_EVERYTHING = None
if _IS_WIN:
    try:
        from everything_api import EverythingAPI as _EverythingAPI
        _EVERYTHING = _EverythingAPI()
        _EVERYTHING_OK = True
    except Exception:
        pass

# ── Update interval reference ────────────────────────────────────────────────
UPDATE_INTERVAL = 5  # seconds

# ── Data directory for persistence ───────────────────────────────────────────
def _data_dir() -> Path:
    if _IS_WIN:
        base = Path(os.environ.get("APPDATA", Path.home()))
    elif _IS_MAC:
        base = Path.home() / "Library" / "Application Support"
    else:
        base = Path(os.environ.get("XDG_DATA_HOME", Path.home() / ".local" / "share"))
    d = base / "sysinfo"
    d.mkdir(parents=True, exist_ok=True)
    return d

DATA_DIR      = _data_dir()
SNAPSHOT_FILE = DATA_DIR / "snapshots.txt"

# ── Activity tracker stats file ───────────────────────────────────────────────
_ACTIVITY_STATS_FILE = DATA_DIR / "activity_stats.json"


# ═══════════════════════════════════════════════════════════════════════════════
# UNIT HELPERS
# ═══════════════════════════════════════════════════════════════════════════════

def _c_to_f(c: float) -> float:
    return c * 9 / 5 + 32

def _temp(c: Optional[float], units: str) -> str:
    if c is None:
        return "N/A"
    return f"{_c_to_f(c):.1f}°F" if units == "usa" else f"{c:.1f}°C"

def _px_to_dist(px: float, units: str, dpi: float = 96.0) -> str:
    inches = px / dpi
    if units == "usa":
        if inches >= 63360:
            return f"{inches/63360:.2f} mi"
        if inches >= 12:
            return f"{inches/12:.2f} ft"
        return f"{inches:.1f} in"
    cm = inches * 2.54
    if cm >= 100000:
        return f"{cm/100000:.2f} km"
    if cm >= 100:
        return f"{cm/100:.2f} m"
    return f"{cm:.1f} cm"

def _bytes_to_gb(b: int) -> float: return b / (1024 ** 3)
def _bytes_to_mb(b: int) -> float: return b / (1024 ** 2)
def _bytes_to_tb(b: int) -> float: return b / (1024 ** 4)

def _fmt_uptime(seconds: float) -> str:
    d, rem = divmod(int(seconds), 86400)
    h, rem = divmod(rem, 3600)
    m, s   = divmod(rem, 60)
    parts = []
    if d: parts.append(f"{d}d")
    if h: parts.append(f"{h}h")
    parts.append(f"{m}m {s}s")
    return " ".join(parts)

def _safe(func, default=None):
    try:
        r = func()
        return r if r is not None else default
    except Exception:
        return default

def _run(cmd: List[str], timeout: int = 5) -> str:
    try:
        return subprocess.check_output(
            cmd, text=True, stderr=subprocess.DEVNULL, timeout=timeout
        ).strip()
    except Exception:
        return ""

def _run_ps(cmd: str, timeout: int = 5) -> str:
    return _run(["powershell", "-NoProfile", "-Command", cmd], timeout=timeout)


# ═══════════════════════════════════════════════════════════════════════════════
# CLIPBOARD
# ═══════════════════════════════════════════════════════════════════════════════

def _collect_clipboard() -> Dict[str, Any]:
    out: Dict[str, Any] = {
        "content_type": "empty",
        "preview":      "",
        "char_count":   None,
        "word_count":   None,
        "line_count":   None,
        "image_size":   None,
        "has_files":    None,
        "file_list":    None,
    }

    if _IS_WIN:
        try:
            text = _run_ps("Get-Clipboard -Format Text 2>$null")
            if text:
                out["content_type"] = "text"
                out["preview"]      = text[:120].replace("\n", "↵")
                out["char_count"]   = len(text)
                out["word_count"]   = len(text.split())
                out["line_count"]   = text.count("\n") + 1
                return out
        except Exception:
            pass
        try:
            img = _run_ps(
                "Add-Type -AssemblyName System.Windows.Forms; "
                "[System.Windows.Forms.Clipboard]::ContainsImage()"
            )
            if img.strip().lower() == "true":
                size = _run_ps(
                    "Add-Type -AssemblyName System.Windows.Forms; "
                    "$i=[System.Windows.Forms.Clipboard]::GetImage(); "
                    "if($i){\"$($i.Width)x$($i.Height)\"}"
                )
                out["content_type"] = "image"
                out["image_size"]   = size or "unknown"
                out["preview"]      = f"Image ({out['image_size']})"
                return out
        except Exception:
            pass
        try:
            files = _run_ps("Get-Clipboard -Format FileDropList 2>$null")
            if files:
                fl = [f.strip() for f in files.splitlines() if f.strip()]
                out["content_type"] = "files"
                out["has_files"]    = len(fl)
                out["file_list"]    = fl[:10]
                out["preview"]      = f"{len(fl)} file(s): " + ", ".join(Path(f).name for f in fl[:3])
                return out
        except Exception:
            pass

    elif _IS_MAC:
        text = _run(["pbpaste"])
        if text:
            out["content_type"] = "text"
            out["preview"]      = text[:120].replace("\n", "↵")
            out["char_count"]   = len(text)
            out["word_count"]   = len(text.split())
            out["line_count"]   = text.count("\n") + 1

    elif _IS_LINUX:
        for cmd in [["xclip", "-selection", "clipboard", "-o"],
                    ["xsel", "--clipboard", "--output"],
                    ["wl-paste"]]:
            text = _run(cmd)
            if text:
                out["content_type"] = "text"
                out["preview"]      = text[:120].replace("\n", "↵")
                out["char_count"]   = len(text)
                out["word_count"]   = len(text.split())
                out["line_count"]   = text.count("\n") + 1
                break

    return out


# ═══════════════════════════════════════════════════════════════════════════════
# NOTIFICATIONS
# ═══════════════════════════════════════════════════════════════════════════════

def _collect_notifications() -> Dict[str, Any]:
    out: Dict[str, Any] = {"count": "N/A", "items": [], "dnd_active": False}

    if _IS_WIN:
        # Focus Assist / DND check
        try:
            dnd = _run_ps(
                "(Get-ItemProperty "
                "'HKCU:\\Software\\Microsoft\\Windows\\CurrentVersion\\CloudStore"
                "\\Store\\DefaultAccount\\Current\\default$windows.data.notifications"
                ".quiethourssettings\\windows.data.notifications.quiethourssettings'"
                " -ErrorAction SilentlyContinue).Data 2>$null"
            )
            out["dnd_active"] = bool(dnd and len(dnd) > 5)
        except Exception:
            pass

        # Recent notifications via event log
        try:
            raw = _run_ps(
                "Get-WinEvent -LogName 'Microsoft-Windows-PushNotification-Platform/Operational' "
                "-MaxEvents 10 -ErrorAction SilentlyContinue | "
                "Select-Object -First 5 -ExpandProperty Message",
                timeout=5
            )
            if raw:
                items = [l.strip() for l in raw.splitlines() if l.strip()][:5]
                out["count"] = len(items)
                out["items"] = items
        except Exception:
            pass

    elif _IS_MAC:
        try:
            dnd = _run(["defaults", "read",
                        "com.apple.controlcenter", "NSStatusItem Visible FocusModes"])
            out["dnd_active"] = dnd.strip() == "1"
        except Exception:
            pass

    elif _IS_LINUX:
        try:
            raw = _run(["dunstctl", "count", "displayed"], timeout=2)
            out["count"] = int(raw) if raw.isdigit() else "N/A"
        except Exception:
            pass

    return out


# ═══════════════════════════════════════════════════════════════════════════════
# OPEN APPLICATIONS
# ═══════════════════════════════════════════════════════════════════════════════

def _collect_open_apps() -> Dict[str, Any]:
    out: Dict[str, Any] = {"count": 0, "apps": []}

    if _IS_WIN:
        try:
            raw = _run_ps(
                "Get-Process | Where-Object {$_.MainWindowHandle -ne 0 "
                "-and $_.MainWindowTitle -ne ''} | "
                "Select-Object ProcessName,MainWindowTitle,"
                "@{N='CPU';E={[Math]::Round($_.CPU,1)}},"
                "@{N='RAM_MB';E={[Math]::Round($_.WorkingSet/1MB,1)}} | "
                "ConvertTo-Json -Compress",
                timeout=7
            )
            if raw:
                items = json.loads(raw)
                if isinstance(items, dict):
                    items = [items]
                apps = []
                for it in items:
                    name  = (it.get("ProcessName") or "").strip()
                    title = (it.get("MainWindowTitle") or "").strip()
                    if name:
                        apps.append({
                            "name":   name,
                            "title":  title[:60],
                            "cpu":    it.get("CPU", 0),
                            "mem_mb": it.get("RAM_MB", 0),
                        })
                out["apps"]  = apps
                out["count"] = len(apps)
        except Exception:
            pass

    elif _IS_MAC:
        try:
            script = ('tell application "System Events" to get the name of every process '
                      'whose background only is false')
            result = _run(["osascript", "-e", script], timeout=4)
            if result:
                apps = [a.strip() for a in result.split(",") if a.strip()]
                out["apps"]  = [{"name": a, "title": a} for a in apps]
                out["count"] = len(apps)
        except Exception:
            pass

    elif _IS_LINUX:
        try:
            result = _run(["wmctrl", "-l"], timeout=3)
            if result:
                apps = []
                for line in result.splitlines():
                    parts = line.split(None, 3)
                    if len(parts) >= 4:
                        apps.append({"name": parts[3].strip()[:60],
                                     "title": parts[3].strip()[:60]})
                out["apps"]  = apps
                out["count"] = len(apps)
        except Exception:
            pass

    return out


# ═══════════════════════════════════════════════════════════════════════════════
# ACTIVITY (reads from activity_tracker.py JSON file)
# ═══════════════════════════════════════════════════════════════════════════════

def _collect_activity(units: str) -> Dict[str, Any]:
    not_running = {
        "tracker_running": False,
        "note": "Start 'python activity_tracker.py' in background to enable."
    }

    stats = None
    try:
        if _ACTIVITY_STATS_FILE.exists():
            stats = json.loads(_ACTIVITY_STATS_FILE.read_text())
    except Exception:
        pass

    if not stats:
        return not_running

    out: Dict[str, Any] = {
        "tracker_running":     True,
        "session_start":       stats.get("session_start"),
        "mouse_left_clicks":   stats.get("mouse_left_clicks", 0),
        "mouse_right_clicks":  stats.get("mouse_right_clicks", 0),
        "mouse_middle_clicks": stats.get("mouse_middle_clicks", 0),
        "mouse_total_clicks":  stats.get("mouse_total_clicks", 0),
        "mouse_scroll_events": stats.get("mouse_scroll_events", 0),
        "key_total":           stats.get("key_total", 0),
        "clicks_per_min":      stats.get("clicks_per_min", 0),
        "keys_per_min":        stats.get("keys_per_min", 0),
        "actions_per_min":     stats.get("actions_per_min", 0),
        "alltime_mouse_clicks":stats.get("alltime_mouse_clicks", 0),
        "alltime_key_total":   stats.get("alltime_key_total", 0),
        "alltime_scroll":      stats.get("alltime_scroll", 0),
        "top_keys":            sorted(
            stats.get("key_counts", {}).items(),
            key=lambda x: x[1], reverse=True
        )[:8],
    }
    dist_px = stats.get("mouse_distance_px", 0)
    out["mouse_distance"]   = _px_to_dist(dist_px, units)
    alltime_px = stats.get("alltime_distance_px", 0)
    out["alltime_distance"] = _px_to_dist(alltime_px, units)

    return out


# ═══════════════════════════════════════════════════════════════════════════════
# SYSTEM
# ═══════════════════════════════════════════════════════════════════════════════

def _collect_system() -> Dict[str, Any]:
    out: Dict[str, Any] = {}
    out["platform"]     = _OS
    out["pc_name"]      = platform.node()
    out["os_name"]      = platform.system()
    out["os_version"]   = platform.version()
    out["os_release"]   = platform.release()
    out["architecture"] = platform.machine()
    out["hostname"]     = socket.gethostname()
    out["python_ver"]   = platform.python_version()

    out["uptime_sec"] = time.time() - psutil.boot_time()
    out["uptime_str"] = _fmt_uptime(out["uptime_sec"])

    now = datetime.datetime.now()
    out["date"] = now.strftime("%m/%d/%Y")
    out["time"] = now.strftime("%I:%M:%S %p")
    out["timezone"] = datetime.datetime.now().astimezone().tzname()

    out["total_processes"] = len(psutil.pids())
    try:
        out["total_threads"] = sum(
            p.num_threads() for p in psutil.process_iter(["num_threads"])
            if p.info.get("num_threads")
        )
    except Exception:
        out["total_threads"] = "N/A"

    # Startup items
    startup = 0
    if _IS_WIN and _WINREG_OK:
        for hive, path in [
            (_winreg.HKEY_CURRENT_USER, r"Software\Microsoft\Windows\CurrentVersion\Run"),
            (_winreg.HKEY_LOCAL_MACHINE, r"Software\Microsoft\Windows\CurrentVersion\Run"),
        ]:
            try:
                with _winreg.OpenKey(hive, path) as k:
                    startup += _winreg.QueryInfoKey(k)[1]
            except Exception:
                pass
    elif _IS_MAC:
        r = _run(["osascript", "-e",
                  'tell application "System Events" to get the name of every login item'])
        startup = len(r.split(",")) if r else 0
    elif _IS_LINUX:
        d = Path.home() / ".config" / "autostart"
        startup = len(list(d.glob("*.desktop"))) if d.exists() else 0
    out["startup_programs"] = startup

    # Power plan
    if _IS_WIN:
        r = _run(["powercfg", "/getactivescheme"])
        m = re.search(r"\((.+)\)", r)
        out["power_plan"] = m.group(1) if m else r or "N/A"
    elif _IS_MAC:
        out["power_plan"] = (_run(["pmset", "-g", "ps"]).splitlines() or ["N/A"])[0].strip()
    else:
        out["power_plan"] = "N/A"

    # Secure boot
    if _IS_WIN:
        r = _run_ps("Confirm-SecureBootUEFI 2>$null")
        out["secure_boot"] = "Enabled" if "True" in r else "Disabled"
    else:
        out["secure_boot"] = "N/A"

    # BIOS / Board
    if _IS_WIN and _WMI_OK:
        try:
            bios  = _WMI.Win32_BIOS()[0]
            board = _WMI.Win32_BaseBoard()[0]
            out["bios_version"]    = getattr(bios, "Name", "N/A")
            out["bios_date"]       = (getattr(bios, "ReleaseDate", "") or "")[:8]
            out["mb_manufacturer"] = getattr(board, "Manufacturer", "N/A")
            out["mb_model"]        = getattr(board, "Product", "N/A")
        except Exception:
            out["bios_version"] = out["bios_date"] = "N/A"
            out["mb_manufacturer"] = out["mb_model"] = "N/A"
    elif _IS_MAC:
        out["mb_manufacturer"] = "Apple"
        out["mb_model"]        = _run(["sysctl", "-n", "hw.model"]) or "N/A"
        out["bios_version"]    = "N/A"
    else:
        out["bios_version"]    = _safe(lambda: Path("/sys/class/dmi/id/bios_version").read_text().strip(), "N/A")
        out["mb_manufacturer"] = _safe(lambda: Path("/sys/class/dmi/id/board_vendor").read_text().strip(), "N/A")
        out["mb_model"]        = _safe(lambda: Path("/sys/class/dmi/id/board_name").read_text().strip(), "N/A")

    return out


# ═══════════════════════════════════════════════════════════════════════════════
# CPU
# ═══════════════════════════════════════════════════════════════════════════════

def _collect_cpu(units: str) -> Dict[str, Any]:
    out: Dict[str, Any] = {}
    freq = psutil.cpu_freq()

    if _CPUINFO_OK:
        try:
            info = _cpuinfo.get_cpu_info()
            out["cpu_name"] = info.get("brand_raw", platform.processor())
            out["l1_cache"] = info.get("l1_data_cache_size", "N/A")
            out["l2_cache"] = info.get("l2_cache_size", "N/A")
            out["l3_cache"] = info.get("l3_cache_size", "N/A")
        except Exception:
            out["cpu_name"] = platform.processor()
    else:
        out["cpu_name"] = platform.processor()

    out["physical_cores"]    = psutil.cpu_count(logical=False)
    out["logical_cores"]     = psutil.cpu_count(logical=True)
    out["base_clock_ghz"]    = round(freq.max / 1000, 2) if freq else "N/A"
    out["current_clock_ghz"] = round(freq.current / 1000, 2) if freq else "N/A"
    out["utilization_pct"]   = psutil.cpu_percent(interval=0.2)
    out["per_core_pct"]      = psutil.cpu_percent(interval=0.2, percpu=True)

    # Temperatures
    try:
        temps = psutil.sensors_temperatures()
        vals = []
        for label, entries in temps.items():
            if any(x in label.lower() for x in ["core", "cpu", "k10temp", "coretemp", "cpu_thermal"]):
                vals += [e.current for e in entries]
        if vals:
            out["cpu_temp_avg_c"] = sum(vals) / len(vals)
            out["cpu_temp_max_c"] = max(vals)
        else:
            out["cpu_temp_avg_c"] = out["cpu_temp_max_c"] = None
    except Exception:
        out["cpu_temp_avg_c"] = out["cpu_temp_max_c"] = None

    if _IS_MAC and out.get("cpu_temp_avg_c") is None:
        r = _run(["osx-cpu-temp"])
        m = re.search(r"([\d.]+)", r)
        if m:
            out["cpu_temp_avg_c"] = out["cpu_temp_max_c"] = float(m.group(1))

    if _IS_WIN and _WMI_OK:
        try:
            proc = _WMI.Win32_Processor()[0]
            out["virtualization"] = bool(getattr(proc, "VirtualizationFirmwareEnabled", False))
            out["l2_cache_kb"]    = getattr(proc, "L2CacheSize", "N/A")
            out["l3_cache_kb"]    = getattr(proc, "L3CacheSize", "N/A")
            out["socket_desig"]   = getattr(proc, "SocketDesignation", "N/A")
        except Exception:
            pass

    return out


# ═══════════════════════════════════════════════════════════════════════════════
# GPU
# ═══════════════════════════════════════════════════════════════════════════════

def _collect_gpu(units: str) -> List[Dict[str, Any]]:
    gpus: List[Dict[str, Any]] = []

    if _IS_WIN and _GPUTIL_OK:
        try:
            for g in _GPUtil.getGPUs():
                gpus.append({
                    "name":         g.name,
                    "driver":       g.driver,
                    "utilization":  f"{g.load*100:.0f}%",
                    "mem_used_gb":  round(g.memoryUsed/1024, 2),
                    "mem_total_gb": round(g.memoryTotal/1024, 2),
                    "mem_util_pct": f"{g.memoryUtil*100:.0f}%",
                    "temp_c":       g.temperature,
                    "temp_display": _temp(g.temperature, units),
                })
        except Exception:
            pass

    if _IS_WIN and _WMI_OK:
        try:
            for i, vc in enumerate(_WMI.Win32_VideoController()):
                extra = {
                    "name":        getattr(vc, "Name", "N/A"),
                    "driver_ver":  getattr(vc, "DriverVersion", "N/A"),
                    "driver_date": (getattr(vc, "DriverDate", "") or "")[:8],
                    "vram_gb":     round(int(getattr(vc, "AdapterRAM", 0) or 0)/1024**3, 2),
                    "resolution":  f"{getattr(vc,'CurrentHorizontalResolution','?')}x{getattr(vc,'CurrentVerticalResolution','?')}",
                    "refresh_hz":  getattr(vc, "CurrentRefreshRate", "N/A"),
                }
                if i < len(gpus):
                    gpus[i].update(extra)
                else:
                    gpus.append(extra)
        except Exception:
            pass

    elif _IS_MAC:
        try:
            raw = _run(["system_profiler", "SPDisplaysDataType"], timeout=8)
            name_m = re.search(r"Chipset Model:\s*(.+)", raw)
            vram_m = re.search(r"VRAM.*?:\s*(.+)", raw)
            gpus.append({
                "name":     (name_m.group(1).strip() if name_m else "N/A"),
                "vram_str": (vram_m.group(1).strip() if vram_m else "N/A"),
            })
        except Exception:
            pass

    elif _IS_LINUX:
        try:
            raw = _run([
                "nvidia-smi",
                "--query-gpu=name,driver_version,utilization.gpu,memory.used,memory.total,temperature.gpu",
                "--format=csv,noheader,nounits"
            ], timeout=4)
            for line in raw.splitlines():
                parts = [p.strip() for p in line.split(",")]
                if len(parts) >= 6:
                    gpus.append({
                        "name":         parts[0],
                        "driver_ver":   parts[1],
                        "utilization":  f"{parts[2]}%",
                        "mem_used_gb":  round(int(parts[3])/1024, 2),
                        "mem_total_gb": round(int(parts[4])/1024, 2),
                        "temp_c":       float(parts[5]),
                        "temp_display": _temp(float(parts[5]), units),
                    })
        except Exception:
            pass

    return gpus


# ═══════════════════════════════════════════════════════════════════════════════
# MEMORY
# ═══════════════════════════════════════════════════════════════════════════════

def _collect_memory(units: str) -> Dict[str, Any]:
    vm = psutil.virtual_memory()
    sw = psutil.swap_memory()
    out = {
        "total_gb":     round(_bytes_to_gb(vm.total), 2),
        "used_gb":      round(_bytes_to_gb(vm.used), 2),
        "available_gb": round(_bytes_to_gb(vm.available), 2),
        "usage_pct":    vm.percent,
        "cached_gb":    round(_bytes_to_gb(getattr(vm, "cached", 0) or 0), 2),
        "swap_total_gb":round(_bytes_to_gb(sw.total), 2),
        "swap_used_gb": round(_bytes_to_gb(sw.used), 2),
        "swap_pct":     sw.percent,
        "speed_mhz":    "N/A", "slots_used": "N/A",
        "slots_total":  "N/A", "form_factor": "N/A",
    }
    if _IS_WIN and _WMI_OK:
        try:
            chips = _WMI.Win32_PhysicalMemory()
            speeds = [int(c.Speed) for c in chips if getattr(c, "Speed", None)]
            out["speed_mhz"]  = speeds[0] if speeds else "N/A"
            out["slots_used"] = len(chips)
            ff_map = {8: "DIMM", 12: "SODIMM", 13: "SODIMM"}
            ff_val = int(getattr(chips[0], "FormFactor", 0)) if chips else 0
            out["form_factor"] = ff_map.get(ff_val, f"Code {ff_val}")
            arr = _WMI.Win32_PhysicalMemoryArray()
            out["slots_total"] = sum(int(s.MemoryDevices) for s in arr)
        except Exception:
            pass
    elif _IS_MAC:
        raw = _run(["system_profiler", "SPMemoryDataType"], timeout=6)
        m = re.search(r"Speed:\s*(\d+\s*MHz)", raw)
        if m:
            out["speed_mhz"] = m.group(1)
        out["slots_used"] = raw.count("Bank ") or "N/A"
    return out


# ═══════════════════════════════════════════════════════════════════════════════
# STORAGE
# ═══════════════════════════════════════════════════════════════════════════════

def _collect_storage(units: str) -> List[Dict[str, Any]]:
    drives = []
    for part in psutil.disk_partitions(all=False):
        d: Dict[str, Any] = {
            "letter": part.mountpoint,
            "device": part.device,
            "fs":     part.fstype,
        }
        try:
            usage = psutil.disk_usage(part.mountpoint)
            d["total_tb"]  = round(_bytes_to_tb(usage.total), 3)
            d["used_tb"]   = round(_bytes_to_tb(usage.used), 3)
            d["free_tb"]   = round(_bytes_to_tb(usage.free), 3)
            d["usage_pct"] = usage.percent
        except Exception:
            d["total_tb"] = d["used_tb"] = d["free_tb"] = d["usage_pct"] = "N/A"

        d["is_system"] = (
            part.mountpoint.upper().rstrip("\\") == os.environ.get("SystemDrive", "C:").upper()
            if _IS_WIN else part.mountpoint == "/"
        )

        if _IS_WIN and _WMI_OK:
            try:
                ld = _WMI.Win32_LogicalDisk(DeviceID=part.mountpoint.rstrip("\\"))
                if ld:
                    d["label"] = getattr(ld[0], "VolumeName", "") or ""
                disks = _WMI.Win32_DiskDrive()
                if disks:
                    dk = disks[0]
                    d["model"]      = getattr(dk, "Model", "N/A")
                    d["serial"]     = (getattr(dk, "SerialNumber", "") or "").strip()
                    d["interface"]  = getattr(dk, "InterfaceType", "N/A")
                    d["media_type"] = getattr(dk, "MediaType", "N/A")
            except Exception:
                pass
        elif _IS_MAC:
            info = _run(["diskutil", "info", part.device], timeout=4)
            m = re.search(r"Device Block Name.*?:\s*(.+)", info)
            d["model"] = m.group(1).strip() if m else "N/A"
        elif _IS_LINUX:
            dev_name = Path(part.device).name
            d["model"] = _safe(
                lambda: Path(f"/sys/block/{dev_name}/device/model").read_text().strip(), "N/A"
            )

        drives.append(d)
    return drives


# ═══════════════════════════════════════════════════════════════════════════════
# NETWORK
# ═══════════════════════════════════════════════════════════════════════════════

def _collect_network(units: str) -> Dict[str, Any]:
    out: Dict[str, Any] = {}
    if _REQUESTS_OK:
        try:
            out["wan_ip"] = _requests.get("https://api.ipify.org", timeout=3).text.strip()
        except Exception:
            out["wan_ip"] = "N/A"
    else:
        out["wan_ip"] = "N/A"

    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.connect(("8.8.8.8", 80))
        out["local_ip"] = s.getsockname()[0]
        s.close()
    except Exception:
        out["local_ip"] = "N/A"

    if _IS_WIN:
        raw = _run_ps(
            "Get-DnsClientServerAddress -AddressFamily IPv4 | "
            "Select-Object -ExpandProperty ServerAddresses"
        )
        out["dns_servers"] = ", ".join(l.strip() for l in raw.splitlines() if l.strip())[:3*16] or "N/A"
    elif _IS_MAC:
        raw = _run(["scutil", "--dns"])
        servers = re.findall(r"nameserver\[\d+\] : (.+)", raw)
        out["dns_servers"] = ", ".join(servers[:3]) or "N/A"
    else:
        try:
            content = Path("/etc/resolv.conf").read_text()
            servers = re.findall(r"nameserver\s+(.+)", content)
            out["dns_servers"] = ", ".join(servers[:3]) or "N/A"
        except Exception:
            out["dns_servers"] = "N/A"

    try:
        net_io = psutil.net_io_counters()
        out["total_sent_gb"] = round(_bytes_to_gb(net_io.bytes_sent), 2)
        out["total_recv_gb"] = round(_bytes_to_gb(net_io.bytes_recv), 2)
    except Exception:
        out["total_sent_gb"] = out["total_recv_gb"] = "N/A"

    try:
        out["active_connections"] = len(psutil.net_connections())
    except Exception:
        out["active_connections"] = "N/A"

    # Adapters (non-loopback, up)
    adapters = []
    for name, addrs in psutil.net_if_addrs().items():
        if any(name.lower().startswith(x) for x in ["lo", "loop", "veth", "virbr", "docker", "vmnet"]):
            continue
        adapter: Dict[str, Any] = {"name": name}
        for addr in addrs:
            if addr.family == socket.AF_INET:
                adapter["ipv4"] = addr.address
            elif addr.family == socket.AF_INET6:
                adapter["ipv6"] = addr.address
        stat = psutil.net_if_stats().get(name)
        if stat:
            adapter["speed_mbps"] = stat.speed
            adapter["is_up"]      = stat.isup
        if adapter.get("is_up"):
            adapters.append(adapter)
    out["adapters"] = adapters

    # Wi-Fi
    if _IS_WIN:
        raw = _run(["netsh", "wlan", "show", "interfaces"])
        if raw:
            sm = re.search(r"^\s*SSID\s*:\s*(.+)", raw, re.MULTILINE)
            sig = re.search(r"Signal\s*:\s*(.+)", raw)
            spd = re.search(r"Receive rate.*?:\s*(.+)", raw)
            out["wifi_ssid"]   = sm.group(1).strip()  if sm  else "N/A"
            out["wifi_signal"] = sig.group(1).strip()  if sig else "N/A"
            out["wifi_speed"]  = spd.group(1).strip()  if spd else "N/A"
    elif _IS_MAC:
        airport = _run([
            "/System/Library/PrivateFrameworks/Apple80211.framework"
            "/Versions/Current/Resources/airport", "-I"
        ])
        sm = re.search(r" SSID: (.+)", airport)
        sp = re.search(r"lastTxRate: (\d+)", airport)
        out["wifi_ssid"]  = sm.group(1).strip() if sm else "N/A"
        out["wifi_speed"] = f"{sp.group(1)} Mbps" if sp else "N/A"
    elif _IS_LINUX:
        out["wifi_ssid"] = _run(["iwgetid", "-r"]) or "N/A"

    return out


# ═══════════════════════════════════════════════════════════════════════════════
# DISPLAY
# ═══════════════════════════════════════════════════════════════════════════════

def _collect_display() -> List[Dict[str, Any]]:
    displays = []
    if _IS_WIN and _WMI_OK:
        try:
            for vc in _WMI.Win32_VideoController():
                displays.append({
                    "name":       getattr(vc, "Name", "N/A"),
                    "resolution": f"{getattr(vc,'CurrentHorizontalResolution','?')}x{getattr(vc,'CurrentVerticalResolution','?')}",
                    "refresh_hz": getattr(vc, "CurrentRefreshRate", "N/A"),
                    "vram_gb":    round(int(getattr(vc, "AdapterRAM", 0) or 0)/1024**3, 2),
                })
        except Exception:
            pass
    if _IS_WIN and not displays:
        try:
            u32 = ctypes.windll.user32
            displays.append({"name": "Primary",
                              "resolution": f"{u32.GetSystemMetrics(0)}x{u32.GetSystemMetrics(1)}"})
        except Exception:
            pass
    elif _IS_MAC:
        raw = _run(["system_profiler", "SPDisplaysDataType"], timeout=6)
        for m in re.finditer(r"Resolution:\s*(.+)", raw):
            displays.append({"name": "Display", "resolution": m.group(1).strip()})
    elif _IS_LINUX:
        raw = _run(["xrandr", "--current"])
        for m in re.finditer(r"(\S+) connected.*?(\d+x\d+)\+", raw):
            displays.append({"name": m.group(1), "resolution": m.group(2)})
    return displays


# ═══════════════════════════════════════════════════════════════════════════════
# AUDIO
# ═══════════════════════════════════════════════════════════════════════════════

def _collect_audio() -> Dict[str, Any]:
    out: Dict[str, Any] = {"output_device": "N/A", "input_device": "N/A", "master_volume": "N/A"}
    if _IS_WIN and _WMI_OK:
        try:
            devs = _WMI.Win32_SoundDevice()
            out["output_device"]  = getattr(devs[0], "Name", "N/A") if devs else "N/A"
            out["input_device"]   = getattr(devs[-1], "Name", "N/A") if len(devs) > 1 else "N/A"
            out["all_devices"]    = [getattr(d, "Name", "N/A") for d in devs]
        except Exception:
            pass
        try:
            vol = _run_ps(
                "Add-Type -AssemblyName System.Windows.Forms; "
                "try{[audio.volume]::GetMasterVolumeLevelScalar()*100}catch{$null}"
            )
            out["master_volume"] = f"{round(float(vol))}%" if vol.strip().replace(".", "").isdigit() else "N/A"
        except Exception:
            pass
    elif _IS_MAC:
        vol = _run(["osascript", "-e", "output volume of (get volume settings)"])
        out["master_volume"] = f"{vol}%" if vol.isdigit() else "N/A"
    elif _IS_LINUX:
        raw = _run(["pactl", "info"])
        m = re.search(r"Default Sink:\s*(.+)", raw)
        if m:
            out["output_device"] = m.group(1).strip()
        m2 = re.search(r"Default Source:\s*(.+)", raw)
        if m2:
            out["input_device"] = m2.group(1).strip()
    return out


# ═══════════════════════════════════════════════════════════════════════════════
# BATTERY
# ═══════════════════════════════════════════════════════════════════════════════

def _collect_battery() -> Optional[Dict[str, Any]]:
    battery = psutil.sensors_battery()
    if battery is None:
        return None
    out: Dict[str, Any] = {
        "percent":    round(battery.percent, 1),
        "plugged_in": battery.power_plugged,
        "status":     "Charging" if battery.power_plugged else "Discharging",
        "wear_pct":   "N/A",
    }
    sl = battery.secsleft
    if sl and sl > 0 and sl != psutil.POWER_TIME_UNKNOWN:
        out["time_remaining"] = _fmt_uptime(sl)
    else:
        out["time_remaining"] = "Plugged in" if battery.power_plugged else "Calculating..."

    if _IS_WIN and _WMI_OK:
        try:
            b = _WMI.Win32_Battery()[0]
            d = int(getattr(b, "DesignCapacity", 0) or 0)
            f = int(getattr(b, "FullChargeCapacity", 0) or 0)
            out["wear_pct"] = round((1 - f/d)*100, 1) if d else "N/A"
        except Exception:
            pass
    elif _IS_MAC:
        raw = _run(["system_profiler", "SPPowerDataType"])
        m = re.search(r"Condition:\s*(.+)", raw)
        out["health"] = m.group(1).strip() if m else "N/A"
    elif _IS_LINUX:
        for bat in Path("/sys/class/power_supply").glob("BAT*"):
            try:
                full = int((bat/"energy_full").read_text())
                des  = int((bat/"energy_full_design").read_text())
                out["wear_pct"] = round((1 - full/des)*100, 1) if des else "N/A"
                break
            except Exception:
                pass
    return out


# ═══════════════════════════════════════════════════════════════════════════════
# BLUETOOTH
# ═══════════════════════════════════════════════════════════════════════════════

def _collect_bluetooth() -> Dict[str, Any]:
    out: Dict[str, Any] = {"adapter_present": False, "adapter_name": "N/A", "devices": []}

    if _IS_WIN:
        try:
            raw = _run_ps(
                "Get-PnpDevice -Class Bluetooth -ErrorAction SilentlyContinue | "
                "Select-Object FriendlyName,Status | ConvertTo-Json -Compress",
                timeout=5
            )
            if raw:
                items = json.loads(raw)
                if isinstance(items, dict):
                    items = [items]
                all_devs = [{"name": (it.get("FriendlyName") or "").strip(),
                              "status": (it.get("Status") or "").strip()}
                             for it in items if it.get("FriendlyName")]
                adapters  = [d for d in all_devs if any(
                    x in d["name"].lower() for x in ["adapter", "radio", "host"])]
                periph    = [d for d in all_devs if d not in adapters]
                out["adapter_present"] = bool(adapters)
                out["adapter_name"]    = adapters[0]["name"] if adapters else "N/A"
                out["devices"]         = periph
        except Exception:
            pass

    elif _IS_MAC:
        raw = _run(["system_profiler", "SPBluetoothDataType"], timeout=6)
        if raw:
            out["adapter_present"] = "Bluetooth" in raw
            devices = re.findall(r"^\s{8}(.+):$", raw, re.MULTILINE)
            out["devices"] = [{"name": d.strip()} for d in devices[:10]]

    elif _IS_LINUX:
        try:
            raw = _run(["bluetoothctl", "devices"], timeout=3)
            devs = []
            for line in raw.splitlines():
                m = re.match(r"Device ([\w:]+)\s+(.+)", line)
                if m:
                    devs.append({"mac": m.group(1), "name": m.group(2)})
            out["devices"]         = devs
            out["adapter_present"] = bool(devs) or bool(_run(["hciconfig"]))
        except Exception:
            pass

    return out


# ═══════════════════════════════════════════════════════════════════════════════
# WEATHER
# ═══════════════════════════════════════════════════════════════════════════════

def _collect_weather(units: str) -> Dict[str, Any]:
    if not _REQUESTS_OK:
        return {"error": "pip install requests"}
    try:
        geo  = _requests.get("https://ipapi.co/json/", timeout=4).json()
        city = geo.get("city", "Unknown")
        state = geo.get("region", "")
        lat   = geo.get("latitude", 0)
        lon   = geo.get("longitude", 0)
        out   = {"location": f"{city}, {state}" if state else city}

        tu = "fahrenheit" if units == "usa" else "celsius"
        wu = "mph" if units == "usa" else "kmh"
        r  = _requests.get(
            f"https://api.open-meteo.com/v1/forecast"
            f"?latitude={lat}&longitude={lon}"
            f"&current=temperature_2m,relative_humidity_2m,wind_speed_10m,weather_code"
            f"&temperature_unit={tu}&wind_speed_unit={wu}&timezone=auto",
            timeout=4
        ).json()
        curr = r.get("current", {})
        u_t = "°F" if units == "usa" else "°C"
        u_w = "mph" if units == "usa" else "km/h"
        wmo  = {0:"Clear",1:"Mainly clear",2:"Partly cloudy",3:"Overcast",
                45:"Fog",51:"Light drizzle",61:"Light rain",71:"Light snow",95:"Thunderstorm"}
        code = curr.get("weather_code", -1)
        out["temperature"] = f"{curr.get('temperature_2m','N/A')}{u_t}"
        out["humidity"]    = f"{curr.get('relative_humidity_2m','N/A')}%"
        out["wind_speed"]  = f"{curr.get('wind_speed_10m','N/A')} {u_w}"
        out["conditions"]  = wmo.get(code, f"Code {code}")
        return out
    except Exception as e:
        return {"error": str(e)}


# ═══════════════════════════════════════════════════════════════════════════════
# TOP PROCESSES
# ═══════════════════════════════════════════════════════════════════════════════

def _collect_processes(n: int = 10) -> List[Dict[str, Any]]:
    procs = []
    for p in sorted(
        psutil.process_iter(["pid", "name", "cpu_percent", "memory_percent", "status"]),
        key=lambda x: x.info.get("cpu_percent") or 0,
        reverse=True
    )[:n]:
        procs.append({
            "pid":     p.info["pid"],
            "name":    p.info["name"],
            "cpu_pct": round(p.info.get("cpu_percent") or 0, 1),
            "mem_pct": round(p.info.get("memory_percent") or 0, 2),
            "status":  p.info.get("status", ""),
        })
    return procs


# ═══════════════════════════════════════════════════════════════════════════════
# FILE SYSTEM
# ═══════════════════════════════════════════════════════════════════════════════

def _collect_filesystem(units: str) -> Dict[str, Any]:
    out: Dict[str, Any] = {}

    # Trash / Recycle Bin
    if _IS_WIN:
        try:
            rb = _run_ps(
                "$s=New-Object -ComObject Shell.Application; "
                "($s.Namespace(10).Items()|Measure-Object -Property Size -Sum).Sum"
            )
            out["recycle_bin_mb"] = round(_bytes_to_mb(int(rb)), 1) if rb.strip().isdigit() else "N/A"
        except Exception:
            out["recycle_bin_mb"] = "N/A"
    else:
        trash = (Path.home() / ".Trash" if _IS_MAC
                 else Path.home() / ".local" / "share" / "Trash" / "files")
        try:
            total = sum(f.stat().st_size for f in trash.rglob("*") if f.is_file())
            out["trash_mb"] = round(_bytes_to_mb(total), 1)
        except Exception:
            out["trash_mb"] = "N/A"

    # Installed programs
    count = 0
    if _IS_WIN and _WINREG_OK:
        for hive, path in [
            (_winreg.HKEY_LOCAL_MACHINE, r"SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall"),
            (_winreg.HKEY_LOCAL_MACHINE, r"SOFTWARE\WOW6432Node\Microsoft\Windows\CurrentVersion\Uninstall"),
            (_winreg.HKEY_CURRENT_USER,  r"SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall"),
        ]:
            try:
                with _winreg.OpenKey(hive, path) as k:
                    count += _winreg.QueryInfoKey(k)[0]
            except Exception:
                pass
    elif _IS_MAC:
        count = len(list(Path("/Applications").glob("*.app")))
    elif _IS_LINUX:
        raw = _run(["dpkg", "--list"], timeout=5)
        count = len([l for l in raw.splitlines() if l.startswith("ii ")]) or 0
        if not count:
            raw = _run(["rpm", "-qa"], timeout=5)
            count = len(raw.splitlines())
    out["installed_programs"] = count

    # Everything counts (Windows only)
    if _EVERYTHING_OK:
        try:
            out["total_objects"]     = f"{_EVERYTHING.count():,}"
            out["downloads_objects"] = f"{_EVERYTHING.count(chr(34)+str(Path.home()/'Downloads')+chr(34)):,}"
            out["documents_objects"] = f"{_EVERYTHING.count(chr(34)+str(Path.home()/'Documents')+chr(34)):,}"
        except Exception:
            out["total_objects"] = "N/A"
    else:
        out["total_objects"] = "N/A (Everything not running)" if _IS_WIN else "N/A"

    return out


# ═══════════════════════════════════════════════════════════════════════════════
# COOLING
# ═══════════════════════════════════════════════════════════════════════════════

def _collect_cooling(units: str) -> Dict[str, Any]:
    out: Dict[str, Any] = {"fans": [], "all_temps": {}}

    try:
        fans = psutil.sensors_fans()
        for name, entries in fans.items():
            for e in entries:
                out["fans"].append({"label": e.label or name, "rpm": e.current})
    except Exception:
        pass

    if _IS_WIN and _WMI_OK and not out["fans"]:
        try:
            for f in _WMI.Win32_Fan():
                out["fans"].append({"label": getattr(f, "Name", "Fan"),
                                    "rpm": getattr(f, "DesiredSpeed", "N/A")})
        except Exception:
            pass

    try:
        temps = psutil.sensors_temperatures()
        out["all_temps"] = {
            name: [{"label": t.label or name, "c": t.current,
                    "display": _temp(t.current, units)} for t in readings]
            for name, readings in temps.items()
        }
    except Exception:
        pass

    return out


# ═══════════════════════════════════════════════════════════════════════════════
# MODES
# ═══════════════════════════════════════════════════════════════════════════════

MODES: Dict[str, Dict[str, bool]] = {
    "normal": {
        "system":        True,
        "cpu":           True,
        "gpu":           True,
        "memory":        True,
        "storage":       True,
        "network":       True,
        "display":       True,
        "audio":         True,
        "battery":       True,
        "bluetooth":     False,
        "weather":       True,
        "clipboard":     True,
        "notifications": True,
        "open_apps":     True,
        "activity":      True,
        "processes":     False,
        "filesystem":    False,
        "cooling":       False,
    },
    "advanced": {
        "system":        True,
        "cpu":           True,
        "gpu":           True,
        "memory":        True,
        "storage":       True,
        "network":       True,
        "display":       True,
        "audio":         True,
        "battery":       True,
        "bluetooth":     True,
        "weather":       True,
        "clipboard":     True,
        "notifications": True,
        "open_apps":     True,
        "activity":      True,
        "processes":     True,
        "filesystem":    True,
        "cooling":       True,
    },
}


# ═══════════════════════════════════════════════════════════════════════════════
# DICT OUTPUT
# ═══════════════════════════════════════════════════════════════════════════════

def get_info_dict(mode: str = "normal", units: str = "usa") -> Dict[str, Any]:
    """
    Return a structured dict of system info.

    Parameters
    ----------
    mode  : 'normal' | 'advanced'
    units : 'usa' | 'metric'
    """
    sections = MODES.get(mode, MODES["normal"])
    data: Dict[str, Any] = {
        "_mode":      mode,
        "_units":     units,
        "_platform":  _OS,
        "_timestamp": datetime.datetime.now().isoformat(),
    }
    if sections.get("system"):        data["system"]        = _safe(_collect_system, {})
    if sections.get("cpu"):           data["cpu"]           = _safe(lambda: _collect_cpu(units), {})
    if sections.get("gpu"):           data["gpu"]           = _safe(lambda: _collect_gpu(units), [])
    if sections.get("memory"):        data["memory"]        = _safe(lambda: _collect_memory(units), {})
    if sections.get("storage"):       data["storage"]       = _safe(lambda: _collect_storage(units), [])
    if sections.get("network"):       data["network"]       = _safe(lambda: _collect_network(units), {})
    if sections.get("display"):       data["display"]       = _safe(_collect_display, [])
    if sections.get("audio"):         data["audio"]         = _safe(_collect_audio, {})
    if sections.get("battery"):       data["battery"]       = _safe(_collect_battery, None)
    if sections.get("bluetooth"):     data["bluetooth"]     = _safe(_collect_bluetooth, {})
    if sections.get("weather"):       data["weather"]       = _safe(lambda: _collect_weather(units), {})
    if sections.get("clipboard"):     data["clipboard"]     = _safe(_collect_clipboard, {})
    if sections.get("notifications"): data["notifications"] = _safe(_collect_notifications, {})
    if sections.get("open_apps"):     data["open_apps"]     = _safe(_collect_open_apps, {})
    if sections.get("activity"):      data["activity"]      = _safe(lambda: _collect_activity(units), {})
    if sections.get("processes"):     data["processes"]     = _safe(_collect_processes, [])
    if sections.get("filesystem"):    data["filesystem"]    = _safe(lambda: _collect_filesystem(units), {})
    if sections.get("cooling"):       data["cooling"]       = _safe(lambda: _collect_cooling(units), {})
    return data


# ═══════════════════════════════════════════════════════════════════════════════
# STRING OUTPUT
# ═══════════════════════════════════════════════════════════════════════════════

def get_info_string(mode: str = "normal", units: str = "usa") -> str:
    """Return a human-readable string of system info."""
    d = get_info_dict(mode=mode, units=units)
    lines: List[str] = []

    def H(title: str) -> None:
        lines.append("")
        lines.append(f"── {title} {'─'*(52-min(len(title),50))}")

    def C(*pairs, sep: str = ", ") -> None:
        """One line of label: value pairs, comma-separated."""
        parts = []
        for label, value in pairs:
            v = str(value) if value is not None else ""
            if v and v not in ("N/A", "None", ""):
                parts.append(f"{label}: {v}")
        if parts:
            lines.append("  " + sep.join(parts))

    def R(label: str, value: Any, pad: int = 28) -> None:
        v = str(value) if value is not None else ""
        if v and v not in ("N/A", "None"):
            lines.append(f"  {label:<{pad}} {v}")

    # Header
    now = datetime.datetime.now()
    lines.append(f"╔{'═'*54}╗")
    lines.append(f"║  SYSTEM INFO  {now.strftime('%m/%d/%Y  %I:%M:%S %p'):<37}║")
    lines.append(f"║  Mode: {mode.upper():<12} Platform: {_OS:<21}║")
    lines.append(f"╚{'═'*54}╝")

    # ── SYSTEM ────────────────────────────────────────────────────────────────
    if "system" in d:
        s = d["system"]
        H("SYSTEM")
        C(("PC", s.get("pc_name")), ("OS", f"{s.get('os_name')} {s.get('os_release')}"),
          ("Arch", s.get("architecture")))
        C(("Uptime", s.get("uptime_str")), ("Time", f"{s.get('date')} {s.get('time')}"),
          ("TZ", s.get("timezone")))
        C(("Power", s.get("power_plan")), ("Secure Boot", s.get("secure_boot")))
        C(("Board", s.get("mb_model")), ("Mfr", s.get("mb_manufacturer")),
          ("BIOS", s.get("bios_version")))
        C(("Processes", s.get("total_processes")), ("Threads", s.get("total_threads")),
          ("Startup Items", s.get("startup_programs")))
        if mode == "advanced":
            C(("Python", s.get("python_ver")), ("Hostname", s.get("hostname")))
            C(("OS Build", s.get("os_version")))

    # ── CPU ───────────────────────────────────────────────────────────────────
    if "cpu" in d:
        c = d["cpu"]
        H("CPU")
        R("Name", c.get("cpu_name"))
        C(("Cores", f"{c.get('physical_cores')}P/{c.get('logical_cores')}L"),
          ("Base", f"{c.get('base_clock_ghz')} GHz"),
          ("Now", f"{c.get('current_clock_ghz')} GHz"),
          ("Load", f"{c.get('utilization_pct')}%"))
        C(("Temp Avg", _temp(c.get("cpu_temp_avg_c"), units)),
          ("Temp Max", _temp(c.get("cpu_temp_max_c"), units)))
        if mode == "advanced":
            per = c.get("per_core_pct", [])
            if per:
                chunks = [per[i:i+8] for i in range(0, len(per), 8)]
                for ci, chunk in enumerate(chunks):
                    lines.append("  " + "  ".join(
                        f"C{ci*8+i}:{v:.0f}%" for i, v in enumerate(chunk)))
            C(("L2", f"{c.get('l2_cache_kb','N/A')} KB"),
              ("L3", f"{c.get('l3_cache_kb','N/A')} KB"),
              ("Virt", str(c.get("virtualization", "N/A"))))

    # ── GPU ───────────────────────────────────────────────────────────────────
    if "gpu" in d and d["gpu"]:
        H("GPU")
        for i, g in enumerate(d["gpu"]):
            if len(d["gpu"]) > 1:
                lines.append(f"  [GPU {i}]")
            R("Name", g.get("name"))
            C(("Load", g.get("utilization")), ("Temp", g.get("temp_display")),
              ("VRAM", f"{g.get('mem_used_gb','?')}/{g.get('mem_total_gb', g.get('vram_gb','?'))} GB"),
              ("Mem%", g.get("mem_util_pct")))
            if mode == "advanced":
                C(("Driver", g.get("driver_ver")), ("Date", g.get("driver_date")),
                  ("Res", g.get("resolution")), ("Hz", g.get("refresh_hz")))

    # ── MEMORY ────────────────────────────────────────────────────────────────
    if "memory" in d:
        m = d["memory"]
        H("MEMORY & SWAP")
        C(("RAM", f"{m.get('used_gb')}/{m.get('total_gb')} GB"),
          ("Usage", f"{m.get('usage_pct')}%"),
          ("Free", f"{m.get('available_gb')} GB"),
          ("Cached", f"{m.get('cached_gb')} GB"))
        C(("Speed", f"{m.get('speed_mhz')} MHz"),
          ("Slots", f"{m.get('slots_used')}/{m.get('slots_total')}"),
          ("Form", m.get("form_factor")))
        C(("Swap", f"{m.get('swap_used_gb')}/{m.get('swap_total_gb')} GB"),
          ("Swap%", f"{m.get('swap_pct')}%"))

    # ── STORAGE ───────────────────────────────────────────────────────────────
    if "storage" in d and d["storage"]:
        H("STORAGE")
        for drv in d["storage"]:
            lbl = drv.get("label", "")
            tag = drv.get("letter", "?") + (f" [{lbl}]" if lbl else "")
            sys_t = " [SYSTEM]" if drv.get("is_system") else ""
            lines.append(f"  {tag}{sys_t}  {drv.get('model','')}")
            C(("Used", f"{drv.get('used_tb')}/{drv.get('total_tb')} TB"),
              ("Free", f"{drv.get('free_tb')} TB"),
              ("Usage", f"{drv.get('usage_pct')}%"))
            if mode == "advanced":
                C(("Interface", drv.get("interface")), ("Type", drv.get("media_type")),
                  ("Serial", drv.get("serial")))

    # ── NETWORK ───────────────────────────────────────────────────────────────
    if "network" in d:
        n = d["network"]
        H("NETWORK")
        C(("WAN", n.get("wan_ip")), ("Local", n.get("local_ip")),
          ("Conns", n.get("active_connections")))
        C(("Wi-Fi", n.get("wifi_ssid")), ("Signal", n.get("wifi_signal")),
          ("Link", n.get("wifi_speed")))
        C(("DNS", n.get("dns_servers")))
        C(("Sent", f"{n.get('total_sent_gb')} GB"),
          ("Recv", f"{n.get('total_recv_gb')} GB"))
        if mode == "advanced":
            for adapter in n.get("adapters", []):
                lines.append(
                    f"    [{adapter['name']}]  {adapter.get('ipv4','N/A')}"
                    f"  {adapter.get('speed_mbps','?')} Mbps")

    # ── DISPLAY ───────────────────────────────────────────────────────────────
    if "display" in d and d["display"]:
        H("DISPLAY")
        for disp in d["display"]:
            C((disp.get("name", "Display"),
               f"{disp.get('resolution','?')} @ {disp.get('refresh_hz','?')} Hz"))

    # ── AUDIO ─────────────────────────────────────────────────────────────────
    if "audio" in d:
        a = d["audio"]
        H("AUDIO")
        C(("Output", a.get("output_device")), ("Input", a.get("input_device")),
          ("Volume", a.get("master_volume")))

    # ── BATTERY ───────────────────────────────────────────────────────────────
    if d.get("battery"):
        b = d["battery"]
        H("BATTERY")
        C(("Charge", f"{b.get('percent')}%"), ("Status", b.get("status")),
          ("Time", b.get("time_remaining")), ("Wear", f"{b.get('wear_pct')}%"),
          ("Health", b.get("health")))

    # ── BLUETOOTH ─────────────────────────────────────────────────────────────
    if "bluetooth" in d:
        bt = d["bluetooth"]
        H("BLUETOOTH")
        C(("Adapter", bt.get("adapter_name")),
          ("Present", str(bt.get("adapter_present"))))
        devs = bt.get("devices", [])
        if devs:
            for dev in devs[:8]:
                st = dev.get("status", "")
                lines.append(f"    • {dev.get('name','?')}" + (f"  [{st}]" if st else ""))
        else:
            lines.append("    (no paired devices found)")

    # ── WEATHER ───────────────────────────────────────────────────────────────
    if "weather" in d and not d["weather"].get("error"):
        w = d["weather"]
        H("WEATHER")
        C(("Location", w.get("location")), ("Conditions", w.get("conditions")))
        C(("Temp", w.get("temperature")), ("Humidity", w.get("humidity")),
          ("Wind", w.get("wind_speed")))

    # ── CLIPBOARD ─────────────────────────────────────────────────────────────
    if "clipboard" in d:
        cb = d["clipboard"]
        H("CLIPBOARD")
        ct = cb.get("content_type", "empty")
        if ct == "text":
            C(("Type", "Text"), ("Chars", cb.get("char_count")),
              ("Words", cb.get("word_count")), ("Lines", cb.get("line_count")))
            R("Preview", f'"{cb.get("preview","")}"')
        elif ct == "image":
            C(("Type", "Image"), ("Size", cb.get("image_size")))
        elif ct == "files":
            C(("Type", "Files"), ("Count", cb.get("has_files")))
            fl = cb.get("file_list", [])
            if fl:
                lines.append("    " + ", ".join(Path(f).name for f in fl[:5]))
        else:
            lines.append("  (clipboard empty)")

    # ── NOTIFICATIONS ─────────────────────────────────────────────────────────
    if "notifications" in d:
        notif = d["notifications"]
        H("NOTIFICATIONS")
        C(("Count", notif.get("count")),
          ("DND/Focus", "Active" if notif.get("dnd_active") else "Off"))
        for item in notif.get("items", [])[:5]:
            lines.append(f"    • {str(item)[:70]}")

    # ── OPEN APPLICATIONS ─────────────────────────────────────────────────────
    if "open_apps" in d:
        apps_d = d["open_apps"]
        H("OPEN APPLICATIONS")
        lines.append(f"  Total: {apps_d.get('count', 0)}")
        for app in apps_d.get("apps", [])[:20]:
            name  = app.get("name", "?")
            title = app.get("title", "")
            cpu   = app.get("cpu_pct")
            mem   = app.get("mem_mb")
            disp  = f"  {name}"
            if title and title.lower() != name.lower():
                disp += f"  —  {title[:45]}"
            if cpu is not None and mem is not None:
                disp += f"  (CPU {cpu}%, RAM {mem} MB)"
            lines.append("   " + disp)

    # ── ACTIVITY ──────────────────────────────────────────────────────────────
    if "activity" in d:
        act = d["activity"]
        H("MOUSE & KEYBOARD ACTIVITY")
        if not act.get("tracker_running"):
            lines.append(f"  ⚠  {act.get('note', 'Tracker not running.')}")
        else:
            C(("APM", act.get("actions_per_min")),
              ("Clicks/min", act.get("clicks_per_min")),
              ("Keys/min", act.get("keys_per_min")))
            C(("L-click", act.get("mouse_left_clicks")),
              ("R-click", act.get("mouse_right_clicks")),
              ("M-click", act.get("mouse_middle_clicks")),
              ("Scroll", act.get("mouse_scroll_events")))
            C(("Mouse dist (session)", act.get("mouse_distance")),
              ("All-time dist", act.get("alltime_distance")))
            C(("Keys (session)", act.get("key_total")),
              ("All-time keys", act.get("alltime_key_total")),
              ("All-time clicks", act.get("alltime_mouse_clicks")))
            top = act.get("top_keys", [])
            if top:
                R("Top keys", ", ".join(f"{k}({n})" for k, n in top[:6]))

    # ── TOP PROCESSES ─────────────────────────────────────────────────────────
    if mode == "advanced" and "processes" in d and d["processes"]:
        H("TOP PROCESSES  (by CPU)")
        lines.append(f"  {'PID':<7} {'Name':<24} {'CPU%':>6}  {'MEM%':>6}  Status")
        lines.append(f"  {'─'*52}")
        for p in d["processes"]:
            lines.append(
                f"  {p['pid']:<7} {p['name'][:23]:<24} "
                f"{p['cpu_pct']:>6.1f}%  {p['mem_pct']:>5.2f}%  {p['status']}"
            )

    # ── FILE SYSTEM ───────────────────────────────────────────────────────────
    if mode == "advanced" and "filesystem" in d:
        fs = d["filesystem"]
        H("FILE SYSTEM")
        C(("Total Objects", fs.get("total_objects")),
          ("Installed", fs.get("installed_programs")))
        C(("Downloads", fs.get("downloads_objects")),
          ("Documents", fs.get("documents_objects")))
        rb = fs.get("recycle_bin_mb") or fs.get("trash_mb")
        if rb:
            C(("Trash/Recycle Bin", f"{rb} MB"))

    # ── COOLING ───────────────────────────────────────────────────────────────
    if mode == "advanced" and "cooling" in d:
        cool = d["cooling"]
        H("COOLING")
        fans = cool.get("fans", [])
        if fans:
            R("Fans", ", ".join(f"{f.get('label','Fan')}: {f.get('rpm')} RPM" for f in fans))
        for sensor, readings in cool.get("all_temps", {}).items():
            for r in readings[:3]:
                lines.append(f"  {r.get('label', sensor):<30} {r.get('display','N/A')}")

    lines.append("")
    lines.append(f"── {'─'*52}")
    lines.append(f"  Snapshot dir: {DATA_DIR}")
    lines.append(f"  Update interval ref: {UPDATE_INTERVAL}s   Units: {units.upper()}")
    lines.append("")

    return "\n".join(lines)


# ═══════════════════════════════════════════════════════════════════════════════
# SNAPSHOT SAVE / LOAD
# ═══════════════════════════════════════════════════════════════════════════════

def save_snapshot(
    path: Optional[str] = None,
    mode: str = "normal",
    units: str = "usa",
    include_dict: bool = False,
) -> str:
    """
    Append a snapshot to a plaintext .txt file.
    Each snapshot includes the human-readable string + a compact SUMMARY JSON line.

    Parameters
    ----------
    path         : file path (default: DATA_DIR/snapshots.txt)
    mode         : 'normal' | 'advanced'
    units        : 'usa' | 'metric'
    include_dict : also append full JSON dict

    Returns
    -------
    str — path written to
    """
    dest = Path(path) if path else SNAPSHOT_FILE
    dest.parent.mkdir(parents=True, exist_ok=True)

    text = get_info_string(mode=mode, units=units)
    data = get_info_dict(mode=mode, units=units)

    ts = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    header = f"\n{'#'*60}\n# SNAPSHOT  {ts}  [{mode.upper()}  {units.upper()}]\n{'#'*60}\n"

    # Compact summary for easy recall
    sys_s  = data.get("system", {})
    cpu_s  = data.get("cpu", {})
    mem_s  = data.get("memory", {})
    net_s  = data.get("network", {})
    act_s  = data.get("activity", {})
    summary: Dict[str, Any] = {
        "ts":       ts,
        "mode":     mode,
        "platform": _OS,
        "uptime":   sys_s.get("uptime_str"),
        "cpu_pct":  cpu_s.get("utilization_pct"),
        "cpu_temp": cpu_s.get("cpu_temp_avg_c"),
        "ram_pct":  mem_s.get("usage_pct"),
        "ram_gb":   mem_s.get("used_gb"),
        "wan_ip":   net_s.get("wan_ip"),
    }
    bat = data.get("battery")
    if bat:
        summary["battery_pct"] = bat.get("percent")
    if act_s.get("tracker_running"):
        summary["apm"]            = act_s.get("actions_per_min")
        summary["alltime_keys"]   = act_s.get("alltime_key_total")
        summary["alltime_clicks"] = act_s.get("alltime_mouse_clicks")

    weather = data.get("weather", {})
    if weather and not weather.get("error"):
        summary["weather"] = f"{weather.get('temperature')}, {weather.get('conditions')}"

    with dest.open("a", encoding="utf-8") as f:
        f.write(header)
        f.write(text)
        f.write("\nSUMMARY: " + json.dumps(summary) + "\n")
        if include_dict:
            f.write("\nJSON:\n" + json.dumps(data, indent=2, default=str) + "\n")

    return str(dest)


def load_snapshots(path: Optional[str] = None) -> List[Dict[str, Any]]:
    """
    Load all SUMMARY lines from snapshot file.
    Returns list of dicts, oldest first.

    Example
    -------
        snaps = load_snapshots()
        for s in snaps[-5:]:   # last 5
            print(s['ts'], s['cpu_pct'], s.get('apm'))
    """
    dest = Path(path) if path else SNAPSHOT_FILE
    summaries = []
    if not dest.exists():
        return summaries
    for line in dest.read_text(encoding="utf-8").splitlines():
        if line.startswith("SUMMARY: "):
            try:
                summaries.append(json.loads(line[9:]))
            except Exception:
                pass
    return sorted(summaries, key=lambda x: x.get("ts", ""))


# ═══════════════════════════════════════════════════════════════════════════════
# CLI SELF-TEST
# ═══════════════════════════════════════════════════════════════════════════════

if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser(description="sysinfo.py - System Information Library")
    parser.add_argument("--mode",    default="normal", choices=list(MODES.keys()))
    parser.add_argument("--units",   default="usa",    choices=["usa", "metric"])
    parser.add_argument("--dict",    action="store_true", help="Print raw dict")
    parser.add_argument("--save",    action="store_true", help="Save snapshot to disk")
    parser.add_argument("--history", action="store_true", help="Show snapshot history")
    parser.add_argument("--out",     default=None,        help="Snapshot output path")
    args = parser.parse_args()

    if args.history:
        snaps = load_snapshots()
        if not snaps:
            print(f"No snapshots yet. Run with --save to create one.")
            print(f"Default file: {SNAPSHOT_FILE}")
        else:
            print(f"{'Timestamp':<22} {'CPU%':>5}  {'RAM%':>5}  {'APM':>6}  {'Battery':>7}  WAN IP")
            print("─" * 72)
            for s in snaps:
                print(
                    f"{s.get('ts','?'):<22} {str(s.get('cpu_pct','?')):>5}  "
                    f"{str(s.get('ram_pct','?')):>5}  {str(s.get('apm','─')):>6}  "
                    f"{str(s.get('battery_pct','─')):>6}%  {s.get('wan_ip','?')}"
                )
    elif args.save:
        p = save_snapshot(path=args.out, mode=args.mode, units=args.units)
        print(f"Snapshot saved → {p}")
    elif args.dict:
        import pprint
        pprint.pprint(get_info_dict(mode=args.mode, units=args.units))
    else:
        print(get_info_string(mode=args.mode, units=args.units))
