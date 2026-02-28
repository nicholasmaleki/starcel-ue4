# sysinfo.py  v2 — Cross-Platform System Information Library

Supports **Windows** (primary), **macOS**, **Linux**.

---

## Files

| File | Purpose |
|------|---------|
| `sysinfo.py` | Main library — `get_info_string()`, `get_info_dict()`, `save_snapshot()`, `load_snapshots()` |
| `activity_tracker.py` | Background daemon for mouse/keyboard tracking (run separately) |
| `everything_api.py` | Voidtools Everything wrapper (Windows, reusable standalone) |

---

## Install

### All platforms
```bash
pip install psutil requests py-cpuinfo pynput
```

### Windows extras (strongly recommended)
```bash
pip install wmi pywin32 GPUtil comtypes
```

### macOS extras
```bash
pip install pyobjc-framework-AppKit pyobjc-framework-Quartz
```

### Linux extras
```bash
sudo apt install wmctrl xclip dunst
```

---

## Quick Start

```python
from sysinfo import get_info_string, get_info_dict

print(get_info_string(mode="normal", units="usa"))

data = get_info_dict(mode="advanced", units="metric")
print(data["cpu"]["cpu_name"])
print(data["memory"]["usage_pct"])
print(data["clipboard"]["preview"])
print(data["open_apps"]["count"])
print(data["activity"]["actions_per_min"])

if data["battery"]:
    print(data["battery"]["percent"])
```

---

## Activity Tracking (Mouse & Keyboard)

Run this **once in the background** before using sysinfo:

```bash
python activity_tracker.py        # runs forever, Ctrl+C to stop
python activity_tracker.py &      # macOS/Linux background
python activity_tracker.py --reset  # reset all counters
```

### What it tracks
- Mouse: L/R/M clicks, scroll events, distance traveled (pixels → converted to real units)
- Keyboard: total keystrokes, top keys by frequency
- Rates: clicks/min, keys/min, **Actions Per Minute (APM)**
- All-time totals that persist across restarts

### Stats file location
| Platform | Path |
|----------|------|
| Windows | `%APPDATA%\sysinfo\activity_stats.json` |
| macOS | `~/Library/Application Support/sysinfo/activity_stats.json` |
| Linux | `~/.local/share/sysinfo/activity_stats.json` |

---

## Snapshots (Save to Disk)

```python
from sysinfo import save_snapshot, load_snapshots

# Append a snapshot (human-readable + compact JSON summary line)
path = save_snapshot(mode="normal", units="usa")

# Load all past snapshots as list of dicts
for s in load_snapshots()[-5:]:
    print(s["ts"], s["cpu_pct"], s.get("apm"))

# Auto-save every 5 minutes
import time
while True:
    save_snapshot()
    time.sleep(300)
```

### CLI
```bash
python sysinfo.py                          # print normal report
python sysinfo.py --mode advanced          # print advanced report
python sysinfo.py --units metric           # use metric units
python sysinfo.py --save                   # save snapshot
python sysinfo.py --history                # show snapshot table
python sysinfo.py --dict                   # dump raw dict
python sysinfo.py --out C:\logs\log.txt    # custom snapshot path
```

### Snapshot format
```
############################################################
# SNAPSHOT  2025-08-01 14:32:00  [NORMAL  USA]
############################################################
... human-readable text ...

SUMMARY: {"ts": "...", "cpu_pct": 12.5, "ram_pct": 67.2, "apm": 142.3, ...}
```

---

## Modes

| Section | normal | advanced |
|---------|:------:|:--------:|
| System overview | ✓ | ✓ |
| CPU | ✓ | ✓ + per-core % |
| GPU | ✓ | ✓ + driver info |
| Memory & Swap | ✓ | ✓ |
| Storage | ✓ | ✓ + serial/interface |
| Network | ✓ | ✓ + all adapters |
| Display | ✓ | ✓ |
| Audio | ✓ | ✓ |
| Battery | ✓ (if present) | ✓ + wear % |
| Bluetooth | ✗ | ✓ |
| Weather | ✓ | ✓ |
| Clipboard | ✓ | ✓ |
| Notifications | ✓ | ✓ |
| Open Apps | ✓ | ✓ |
| Activity (APM) | ✓ | ✓ |
| Top Processes | ✗ | ✓ |
| File System Stats | ✗ | ✓ |
| Cooling / Fans | ✗ | ✓ |

---

## Units

| Setting | Temps | Wind | Mouse distance |
|---------|-------|------|----------------|
| `"usa"` | °F | mph | in / ft / mi |
| `"metric"` | °C | km/h | cm / m / km |

---

## Custom Modes

```python
from sysinfo import MODES
MODES["minimal"] = {
    "system": True, "cpu": True, "memory": True,
}
```

---

## Everything API (Windows only)

```python
from everything_api import EverythingAPI
api = EverythingAPI()  # needs Everything64.dll in same folder + Everything running

print(api.count())                     # total indexed objects
print(api.count(r'"C:\Users\you\Downloads"'))

for item in api.search("*.py", max_results=10):
    print(item["full_path"], item["size"])
```

Download `Everything64.dll` from: https://www.voidtools.com/Everything-SDK.zip

---

## Clipboard Info

`data["clipboard"]`:
- `content_type`: `"text"` | `"image"` | `"files"` | `"empty"`
- text: `char_count`, `word_count`, `line_count`, `preview`
- image: `image_size` (e.g. `"1920x1080"`)
- files: `has_files` (count), `file_list`

Linux needs `xclip`, `xsel`, or `wl-paste`.

---

## Open Apps

- **Windows**: taskbar entries (processes with a visible window) — name, title, CPU%, RAM MB
- **macOS**: foreground apps via `osascript`
- **Linux**: windows via `wmctrl`

---

## Notifications

- **Windows**: DND/Focus Assist state + recent push notification event log
- **macOS**: Focus Mode state via `defaults`
- **Linux**: dunst notification count via `dunstctl`
