"""Shared utility functions used across multiple modules."""
from __future__ import annotations

import datetime
import subprocess
from typing import Optional

try:
    import unreal_engine as ue
except ImportError:
    ue = None


# Windows FILETIME conversion

_WIN_TICKS        = 10_000_000
_EPOCH_DIFF_TICKS = (
    datetime.datetime(1970, 1, 1) - datetime.datetime(1601, 1, 1)
).total_seconds() * _WIN_TICKS


def filetime_to_dt(raw: int) -> Optional[datetime.datetime]:
    """Convert a Windows FILETIME (100-ns ticks since 1601-01-01) to datetime.

    Accepts plain int or ctypes integer types (their int() is called).
    Returns None for sentinel values (0, UINT64_MAX).
    """
    raw = int(raw)
    if raw in (0, 2**64 - 1):
        return None
    try:
        return datetime.datetime.fromtimestamp((raw - _EPOCH_DIFF_TICKS) / _WIN_TICKS)
    except (OSError, ValueError):
        return None


# Human-readable byte sizes

def human_size(n) -> Optional[str]:
    """Convert byte count to human-readable string, e.g. '22.51 MB'.

    Returns None if *n* is None; returns '?' on conversion failure.
    """
    if n is None:
        return None
    try:
        val = float(n)
    except (TypeError, ValueError):
        return '?'
    if val == 0:
        return '0 B'
    for unit in ('B', 'KB', 'MB', 'GB', 'TB'):
        if val < 1024.0 or unit == 'TB':
            return f"{val:.2f} {unit}" if unit != 'B' else f"{int(val)} B"
        val /= 1024.0
    return f"{val:.2f} PB"


# Open path in Chrome

def open_with_chrome(path: str) -> None:
    """Open *path* in Chrome via ``cmd /c start chrome "<path>"``.

    Chrome renders URLs/HTML/images directly; for other file types it
    falls through to its configured handler.
    """
    try:
        subprocess.Popen(
            ['cmd', '/c', 'start', 'chrome', path],
            shell=False,
            creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0),
        )
        if ue:
            ue.log(f'utils: opened "{path}" in Chrome')
    except Exception as e:
        if ue:
            ue.log_warning(f'utils: Chrome launch failed: {e}')
