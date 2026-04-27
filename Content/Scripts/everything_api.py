"""
everything_api.py
=================
Standalone wrapper around the Voidtools Everything SDK DLL.
Place this file alongside Everything64.dll (or Everything32.dll).
Everything must be running in the background.

Usage
-----
    from everything_api import EverythingAPI

    api = EverythingAPI()                              # auto-finds DLL
    print(api.count())                                 # total objects
    print(api.count(r'"C:\\Users\\you\\Downloads"'))   # scoped count

    for item in api.search("*.py", max_results=10):
        print(item["full_path"], item["size"])

Download Everything64.dll from:
    https://www.voidtools.com/Everything-SDK.zip
"""

from __future__ import annotations

import ctypes
import datetime
import os
import struct
from pathlib import Path
from typing import Any, Dict, List, Optional

from utils import filetime_to_dt as _filetime_to_dt


REQ_FILE_NAME = 0x00000001
REQ_PATH = 0x00000002
REQ_SIZE = 0x00000010
REQ_DATE_CREATED = 0x00000020
REQ_DATE_MODIFIED= 0x00000040
REQ_ATTRIBUTES = 0x00000100

SORT_NAME_ASC = 1
SORT_SIZE_DESC = 6


class EverythingAPI:
    """Thin wrapper around Everything64.dll."""

    def __init__(self, dll_path: Optional[str] = None):
        if dll_path is None:
            candidates = [
                Path(__file__).parent / "Everything64.dll",
                Path(__file__).parent / "Everything32.dll",
                "Everything64.dll",
                "Everything32.dll",
            ]
            for c in candidates:
                if Path(c).exists():
                    dll_path = str(c)
                    break
        if dll_path is None:
            raise FileNotFoundError(
                "Everything64.dll not found. Download the Everything SDK from "
                "https://www.voidtools.com/Everything-SDK.zip and place "
                "Everything64.dll next to this file."
            )
        self._dll = ctypes.WinDLL(dll_path)
        self._setup()

    def _setup(self) -> None:
        d = self._dll
        d.Everything_SetSearchW.argtypes = [ctypes.c_wchar_p]
        d.Everything_SetSearchW.restype = None
        d.Everything_SetRequestFlags.argtypes = [ctypes.c_uint]
        d.Everything_SetRequestFlags.restype = None
        d.Everything_SetSort.argtypes = [ctypes.c_uint]
        d.Everything_SetSort.restype = None
        d.Everything_SetMax.argtypes = [ctypes.c_uint]
        d.Everything_SetMax.restype = None
        d.Everything_QueryW.argtypes = [ctypes.c_bool]
        d.Everything_QueryW.restype = ctypes.c_bool
        d.Everything_GetNumResults.argtypes = []
        d.Everything_GetNumResults.restype = ctypes.c_uint
        d.Everything_GetTotResults.argtypes = []
        d.Everything_GetTotResults.restype = ctypes.c_uint
        d.Everything_GetResultFileNameW.argtypes = [ctypes.c_uint]
        d.Everything_GetResultFileNameW.restype = ctypes.c_wchar_p
        d.Everything_GetResultPathW.argtypes = [ctypes.c_uint]
        d.Everything_GetResultPathW.restype = ctypes.c_wchar_p
        d.Everything_GetResultSize.argtypes = [ctypes.c_uint, ctypes.POINTER(ctypes.c_ulonglong)]
        d.Everything_GetResultSize.restype = ctypes.c_bool
        d.Everything_IsFolderResult.argtypes = [ctypes.c_uint]
        d.Everything_IsFolderResult.restype = ctypes.c_bool

    def _query(self, query: str, max_results: int = 1,
               flags: int = REQ_FILE_NAME | REQ_PATH | REQ_SIZE) -> None:
        self._dll.Everything_SetSearchW(query)
        self._dll.Everything_SetRequestFlags(flags)
        self._dll.Everything_SetSort(SORT_NAME_ASC)
        self._dll.Everything_SetMax(max_results)
        self._dll.Everything_QueryW(True)

    def count(self, query: str = "") -> int:
        """Total number of matching objects (files + folders)."""
        self._query(query, max_results=1)
        return self._dll.Everything_GetTotResults()

    def search(self, query: str = "", max_results: int = 100) -> List[Dict[str, Any]]:
        """Return list of result dicts with name, path, full_path, size, is_folder."""
        self._query(query, max_results=max_results)
        n = self._dll.Everything_GetNumResults()
        results = []
        for i in range(n):
            name = self._dll.Everything_GetResultFileNameW(i) or ""
            path = self._dll.Everything_GetResultPathW(i) or ""
            size_buf = ctypes.c_ulonglong(0)
            self._dll.Everything_GetResultSize(i, ctypes.byref(size_buf))
            results.append({
                "name":      name,
                "path":      path,
                "full_path": os.path.join(path, name),
                "size":      size_buf.value,
                "is_folder": self._dll.Everything_IsFolderResult(i),
            })
        return results
