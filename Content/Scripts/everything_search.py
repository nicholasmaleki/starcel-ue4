"""
everything_search.py
====================
Wraps the voidtools Everything SDK DLL with rich per-file metadata.
Place this file and metadata.py in the same directory as Everything64.dll.

Requirements
------------
- Everything running in the background.
- Everything64.dll from https://www.voidtools.com/Everything-SDK.zip

Optional dependencies (degrade gracefully):
    pip install mutagen Pillow opencv-python-headless openpyxl pymupdf python-docx rarfile py7zr

Supported query syntax  —  all native Everything syntax passes through unchanged:

    '"C:\\\\Users\\\\nicho\\\\Downloads" pdf'
    '*.py'
    'potato'
    'ext:mp4 dm:lastmonth'
    'size:>1mb !ext:exe'
    '*.png OR *.jpg OR *.hdr'
"""

from __future__ import annotations

import ctypes
import datetime
import os
import re
import stat
import struct
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Dict, Iterator, List, Optional, Union

import metadata as _meta
from utils import filetime_to_dt as _filetime_to_dt, human_size as _human_size

# Windows FILETIME helpers — now in utils.py


# SDK constants
REQ_FILE_NAME = 0x00000001
REQ_PATH = 0x00000002
REQ_FULL_PATH = 0x00000004
REQ_EXTENSION = 0x00000008
REQ_SIZE = 0x00000010
REQ_DATE_CREATED = 0x00000020
REQ_DATE_MODIFIED = 0x00000040
REQ_DATE_ACCESSED = 0x00000080
REQ_ATTRIBUTES = 0x00000100
REQ_RUN_COUNT = 0x00000400
REQ_DATE_RUN = 0x00000800
REQ_DATE_RECENTLY_CHGD = 0x00001000

DEFAULT_FLAGS = REQ_FULL_PATH | REQ_SIZE | REQ_DATE_CREATED | REQ_DATE_MODIFIED

SORT_NAME_ASC = 1
SORT_NAME_DESC = 2
SORT_SIZE_ASC = 5
SORT_SIZE_DESC = 6
SORT_DATE_CREATED_ASC = 11
SORT_DATE_CREATED_DESC = 12
SORT_DATE_MODIFIED_ASC = 13
SORT_DATE_MODIFIED_DESC = 14
SORT_DATE_ACCESSED_ASC = 23
SORT_DATE_ACCESSED_DESC = 24


# File-type classification
_EXT_VIDEO = frozenset(
    '3g2 3gp 3gp2 3gpp amv asf avi bdmv bik d2v divx drc dsa dsm dss dsv evo '
    'f4v flc fli flic flv hdmov ifo ivf m1v m2p m2t m2ts m2v m4v mkv mov '
    'mp2v mp4 mp4v mpe mpeg mpg mpls mpv2 mpv4 mts ogm ogv pss pva qt ram '
    'ratdvd rm rmm rmvb roq rpm smil smk swf tp tpr ts vob vp6 webm wm wmp wmv'.split()
)
_EXT_IMAGE = frozenset(
    'ani apng avif bmp cur gif heic heif hif ico jfi jfif jif jpe jpeg jpg '
    'pcx png psb psd rle svg tga tif tiff webp wmf hdr rgbe exr'.split()
)
_EXT_AUDIO = frozenset(
    'aac ac3 aif aifc aiff amr ape au cda dts fla flac it m1a m2a m3u m4a m4b '
    'mid midi mka mod mp2 mp3 mpa mpc ogg opus ra rmi snd spc voc wav weba wma xm'.split()
)
_EXT_DOC = frozenset(
    'doc docm docx dot dotm dotx epub mobi odt pdf rtf txt wpd wps wri'.split()
)
_EXT_SHEET = frozenset('csv ods xls xlsb xlsm xlsx xltm xltx'.split())
_EXT_PPTX = frozenset('odp pot potm potx pps ppsm ppsx ppt pptm pptx'.split())
_EXT_EXEC = frozenset('bat cmd exe msi msp msu ps1 scr'.split())
_EXT_ARCHIVE = frozenset('7z ace arj bz2 cab gz gzip jar r00 rar tar tgz z zip cbz cbr'.split())
_EXT_3D = frozenset(
    '3ds amf blend dae fbx glb gltf lwo lws ma mb obj off ply skp stl step stp '
    'vrml wrl x3d zpr'.split()
)
_EXT_CRYPTO = frozenset('asc gpg pgp key pem crt cer p7b p12 pfx pub'.split())
_EXT_DB = frozenset('db sqlite sqlite3 db3 s3db sl3'.split())
_EXT_FONT = frozenset('ttf otf woff woff2 eot fon'.split())
_EXT_EMAIL = frozenset('eml msg'.split())
_EXT_TORRENT = frozenset('torrent'.split())
_EXT_LINK = frozenset('lnk'.split())


_EXT_CATEGORIES: Dict[str, str] = {}
for _cat, _exts in [
    ('Video',        _EXT_VIDEO),
    ('Image',        _EXT_IMAGE),
    ('Audio',        _EXT_AUDIO),
    ('Document',     _EXT_DOC),
    ('Spreadsheet',  _EXT_SHEET),
    ('Presentation', _EXT_PPTX),
    ('Executable',   _EXT_EXEC),
    ('Archive',      _EXT_ARCHIVE),
    ('3D',           _EXT_3D),
    ('Crypto/Key',   _EXT_CRYPTO),
    ('Database',     _EXT_DB),
    ('Font',         _EXT_FONT),
    ('Email',        _EXT_EMAIL),
    ('Torrent',      _EXT_TORRENT),
    ('Shortcut',     _EXT_LINK),
]:
    for _e in _exts:
        _EXT_CATEGORIES[_e] = _cat


def _classify(ext: str) -> str:
    e = ext.lower().lstrip('.')
    cat = _EXT_CATEGORIES.get(e)
    if cat:
        return cat
    if e in _meta.TEXT_EXTS:
        return 'Text/Code'
    return 'File'


# Formatting helpers
def fmt_date(dt_val: Optional[datetime.datetime], python_style: bool = False) -> Optional[str]:
    """
    Format a datetime object.
    python_style=False (default) → DD/MM/YYYY HH:MM AM/PM
    python_style=True            → YYYY-MM-DD HH:MM:SS
    """
    if dt_val is None:
        return None
    if python_style:
        return dt_val.strftime('%Y-%m-%d %H:%M:%S')
    return dt_val.strftime('%d/%m/%Y %I:%M %p')


# _human_size — now in utils.py


def _permission_string(full_path: str) -> Optional[str]:
    try:
        return stat.filemode(os.stat(full_path).st_mode)
    except (OSError, ValueError):
        return None


# Result dataclass
DEFAULT_FIELD_ORDER: List[str] = [
    # Core
    'name', 'type', 'size', 'permissions', 'date_modified', 'date_created',
    # Media
    'dimensions', 'length', 'color_mode', 'bit_depth', 'dpi',
    # Audio tags
    'album', 'album_artist', 'artist', 'title', 'track',
    'year', 'genre', 'bitrate', 'sample_rate', 'channels',
    # Archive
    'file_count', 'dir_count', 'total_uncompressed',
    'compression_method', 'encrypted', 'archive_comment', 'nested_archives',
    # Spreadsheet / Presentation
    'sheet_count', 'slide_count', 'notes_count',
    # Crypto / Key
    'key_type', 'algorithm', 'key_id', 'created', 'expires',
    'user_id', 'packet_types', 'armored', 'key_comment',
    # Database
    'db_tables', 'db_encoding', 'db_page_size', 'db_page_count',
    # Font
    'font_family', 'font_subfamily', 'font_full_name',
    'font_version', 'glyph_count', 'units_per_em',
    # Email
    'email_subject', 'email_sender', 'email_recipients',
    'email_date', 'email_attachments',
    # Torrent
    'torrent_name', 'torrent_files', 'torrent_size',
    'torrent_tracker', 'torrent_created', 'torrent_private',
    # Shortcut  —  Target and Start In at the top of the shortcut section
    'shortcut_target', 'shortcut_working_dir', 'shortcut_args',
    'shortcut_icon', 'shortcut_hotkey', 'shortcut_show',
    # 3D
    'info_3d',
    # Always last
    'full_path',
]


@dataclass
class Result:
    """Single search result with rich metadata. All fields default to None."""
    # Identity
    name:          Optional[str] = None
    full_path:     Optional[str] = None
    type:          Optional[str] = None
    # Size
    size_bytes:    Optional[int] = None
    size:          Optional[str] = None
    # Dates
    date_modified: Optional[datetime.datetime] = None
    date_created:  Optional[datetime.datetime] = None
    # Permissions
    permissions:   Optional[str] = None
    # Image / video
    dimensions:    Optional[tuple] = None
    length:        Optional[str] = None
    color_mode:    Optional[str] = None
    bit_depth:     Optional[int] = None
    dpi:           Optional[str] = None
    # Audio tags
    album:         Optional[str] = None
    album_artist:  Optional[str] = None
    artist:        Optional[str] = None
    title:         Optional[str] = None
    track:         Optional[str] = None
    year:          Optional[str] = None
    genre:         Optional[str] = None
    bitrate:       Optional[int] = None
    sample_rate:   Optional[int] = None
    channels:      Optional[int] = None
    # Archive
    file_count:          Optional[int] = None
    dir_count:           Optional[int] = None
    total_uncompressed:  Optional[str] = None
    compression_method:  Optional[str] = None
    encrypted:           Optional[str] = None
    archive_comment:     Optional[str] = None
    nested_archives:     Optional[int] = None
    # Spreadsheet / Presentation
    sheet_count:   Optional[int] = None
    slide_count:   Optional[int] = None
    notes_count:   Optional[int] = None
    # Crypto / Key
    key_type:      Optional[str] = None
    algorithm:     Optional[str] = None
    key_id:        Optional[str] = None
    created:       Optional[str] = None
    expires:       Optional[str] = None
    user_id:       Optional[str] = None
    packet_types:  Optional[str] = None
    armored:       Optional[bool] = None
    key_comment:   Optional[str] = None
    # Database
    db_tables:     Optional[str] = None
    db_encoding:   Optional[str] = None
    db_page_size:  Optional[int] = None
    db_page_count: Optional[int] = None
    # Font
    font_family:      Optional[str] = None
    font_subfamily:   Optional[str] = None
    font_full_name:   Optional[str] = None
    font_version:     Optional[str] = None
    glyph_count:      Optional[int] = None
    units_per_em:     Optional[int] = None
    # Email
    email_subject:     Optional[str] = None
    email_sender:      Optional[str] = None
    email_recipients:  Optional[str] = None
    email_date:        Optional[str] = None
    email_attachments: Optional[int] = None
    # Torrent
    torrent_name:    Optional[str] = None
    torrent_files:   Optional[int] = None
    torrent_size:    Optional[str] = None
    torrent_tracker: Optional[str] = None
    torrent_created: Optional[str] = None
    torrent_private: Optional[str] = None
    # Shortcut
    shortcut_target:      Optional[str] = None
    shortcut_working_dir: Optional[str] = None
    shortcut_args:        Optional[str] = None
    shortcut_icon:        Optional[str] = None
    shortcut_hotkey:      Optional[str] = None
    shortcut_show:        Optional[str] = None
    # 3D
    info_3d:       Optional[str] = None

    def to_dict(
        self,
        order: Optional[List[str]] = None,
        python_dates: bool = False,
    ) -> Dict[str, Any]:
        order = order or DEFAULT_FIELD_ORDER
        out: Dict[str, Any] = {}
        for key in order:
            if key == 'date_modified':
                out[key] = fmt_date(self.date_modified, python_dates)
            elif key == 'date_created':
                out[key] = fmt_date(self.date_created, python_dates)
            else:
                out[key] = getattr(self, key, None)
        return out

    def __str__(self) -> str:
        lines = []
        for k, v in self.to_dict().items():
            if v is not None and v != '':
                label = k.replace('_', ' ').capitalize()
                lines.append(f"  {label:<22} {v}")
        return '\n'.join(lines)


# Query parser
_NATIVE_TOKEN_RE = re.compile(
    r'^(?:'
    r'ext:|path:|folder:|file:|parent:|noext:'
    r'|dm:|dc:|da:|drc:|dr:'
    r'|size:|len:|count:|depth:'
    r'|attrib:|type:|wfn:|wc:'
    r'|regex:|noregex:'
    r'|!|AND\b|OR\b|NOT\b'
    r'|[<>|()]'
    r')',
    re.IGNORECASE,
)
_QUOTED_PATH_RE = re.compile(r'"([A-Za-z]:[^"]*)"')
_GLOB_EXT_RE = re.compile(r'^\*\.(\w+)$')


def _parse_query(raw: str) -> str:
    path_reps: List[str] = []

    def _sub(m: re.Match) -> str:
        path_reps.append(f'path:"{m.group(1)}"')
        return f'\x00{len(path_reps)-1}\x00'

    working = _QUOTED_PATH_RE.sub(_sub, raw)
    tokens: List[str] = []
    exts:   List[str] = []

    for token in working.split():
        ph = re.fullmatch(r'\x00(\d+)\x00', token)
        if ph:
            tokens.append(path_reps[int(ph.group(1))]); continue
        if _NATIVE_TOKEN_RE.match(token):
            tokens.append(token); continue
        m = _GLOB_EXT_RE.match(token)
        if m:
            exts.append(m.group(1)); continue
        tokens.append(token)

    if exts:
        tokens.append('ext:' + ';'.join(exts))
    return ' '.join(tokens)


# Main client
class EverythingSearch:
    """
    Everything SDK wrapper with rich per-file metadata.

    Usage
    -----
    with EverythingSearch() as es:
        for r in es.search('"C:\\\\Users\\\\Downloads" pdf', limit=20):
            print(r)

    # MP4s from the past month (native Everything syntax)
    for r in es.search('*.mp4 dm:lastmonth', sort=SORT_DATE_MODIFIED_DESC):
        print(r)

    # Images by format
    for r in es.search_image_formats('png', 'jpg', 'hdr'):
        print(r)

    # Enable metadata extraction errors for debugging:
    import metadata; metadata._DEBUG = True
    """

    def __init__(self, dll_path: Optional[Union[str, Path]] = None):
        if dll_path is None:
            dll_path = Path(__file__).parent / 'Everything64.dll'
        self._dll_path = str(dll_path)
        self._dll: Optional[ctypes.WinDLL] = None
        self._path_buf = ctypes.create_unicode_buffer(32767)
        self._size_buf = ctypes.c_ulonglong(0)
        self._mtime_buf = ctypes.c_ulonglong(0)
        self._ctime_buf = ctypes.c_ulonglong(0)

    def __enter__(self):
        self.connect(); return self

    def __exit__(self, *_):
        self.close()

    def connect(self) -> None:
        if self._dll:
            return
        try:
            self._dll = ctypes.WinDLL(self._dll_path)
        except (FileNotFoundError, OSError) as exc:
            raise FileNotFoundError(
                f"Could not load DLL from '{self._dll_path}'.\n"
                "Download from https://www.voidtools.com/Everything-SDK.zip"
            ) from exc
        self._setup_signatures()

    def close(self) -> None:
        """Unload the DLL. Safe to call multiple times."""
        if not self._dll:
            return
        try:
            # Use c_size_t to avoid OverflowError on 64-bit Python
            handle = ctypes.c_size_t(self._dll._handle)
            ctypes.windll.kernel32.FreeLibrary(handle)
        except Exception:
            pass   # DLL will be released when the process exits anyway
        self._dll = None

    # Core search
    def search(
        self,
        query: str,
        *,
        limit:        int = -1,
        sort:         int = SORT_DATE_MODIFIED_DESC,
        flags:        int = DEFAULT_FLAGS,
        regex:        bool = False,
        metadata:     bool = True,
        python_dates: bool = False,
        custom_order: Optional[List[str]] = None,
    ) -> Iterator[Result]:
        """
        Search Everything and yield Result objects.

        query        : Everything GUI or native SDK query string.
        limit        : Max results (-1 = unlimited).
        sort         : SORT_* constant.
        flags        : REQ_* bitmask.
        regex        : Treat query as a regex.
        metadata     : Enrich with filesystem metadata. Set False for fast results.
        python_dates : Use ISO date strings in to_dict() / __str__.
        custom_order : Field order for to_dict() / __str__.
        """
        if not self._dll:
            raise RuntimeError("Not connected. Use 'with EverythingSearch() as es:'")

        sdk_query = _parse_query(query)
        dll = self._dll
        try:
            dll.Everything_Reset()
            dll.Everything_SetSearchW(sdk_query)
            dll.Everything_SetRegex(bool(regex))
            dll.Everything_SetRequestFlags(flags)
            dll.Everything_SetSort(sort)
            if limit >= 0:
                dll.Everything_SetMax(limit)

            if not dll.Everything_QueryW(True):
                err = dll.Everything_GetLastError()
                _E = {1:'Out of memory', 2:'IPC unavailable – is Everything running?',
                      3:'RegisterClassEx failed', 4:'CreateWindow failed',
                      5:'CreateThread failed', 6:'Invalid index', 7:'Invalid call'}
                raise RuntimeError(f"Query failed: {_E.get(err, f'error {err}')}")

            num = dll.Everything_GetNumResults()
        except RuntimeError:
            raise
        except Exception as exc:
            print(f"[EverythingSearch.search] SDK error: {type(exc).__name__}: {exc}")
            return

        for i in range(num):
            try:
                full_path = size_bytes = date_modified = date_created = None

                if flags & REQ_FULL_PATH:
                    dll.Everything_GetResultFullPathNameW(i, self._path_buf, 32767)
                    full_path = self._path_buf.value
                if flags & REQ_SIZE:
                    dll.Everything_GetResultSize(i, self._size_buf)
                    size_bytes = self._size_buf.value
                if flags & REQ_DATE_MODIFIED:
                    dll.Everything_GetResultDateModified(i, self._mtime_buf)
                    date_modified = _filetime_to_dt(self._mtime_buf.value)
                if flags & REQ_DATE_CREATED:
                    dll.Everything_GetResultDateCreated(i, self._ctime_buf)
                    date_created = _filetime_to_dt(self._ctime_buf.value)

                p = Path(full_path) if full_path else None
                name = p.name   if p else None
                ext = p.suffix if p else ''
                ftype = _classify(ext)

                result = Result(
                    name = name,
                    full_path = full_path,
                    type = ftype,
                    size_bytes = size_bytes,
                    size = _human_size(size_bytes),
                    date_modified = date_modified,
                    date_created = date_created,
                    permissions = _permission_string(full_path) if full_path else None,
                )

                if metadata and full_path and p and p.exists():
                    try:
                        self._enrich(result, full_path, ext.lower().lstrip('.'), ftype)
                    except Exception as exc:
                        print(f"[EverythingSearch] metadata error for '{full_path}': "
                              f"{type(exc).__name__}: {exc}")

                yield result

            except Exception as exc:
                print(f"[EverythingSearch] error on result {i}: {type(exc).__name__}: {exc}")
                continue

    # Enrichment dispatcher
    def _enrich(self, r: Result, path: str, ext: str, ftype: str) -> None:
        if ftype == 'Image':
            info = _meta.image_info(path, ext)
            r.dimensions = info.get('dimensions')
            r.color_mode = info.get('color_mode')
            r.bit_depth = info.get('bit_depth')
            r.dpi = info.get('dpi')

        elif ftype == 'Video':
            info = _meta.video_info(path)
            r.dimensions = info.get('dimensions')
            if info.get('length_s'):
                r.length = _meta._fmt_duration(info['length_s'])

        elif ftype == 'Audio':
            tags = _meta.audio_tags(path)
            if tags.get('length_s'):
                r.length = _meta._fmt_duration(tags['length_s'])
            r.album = tags.get('album')
            r.album_artist = tags.get('album_artist')
            r.artist = tags.get('artist')
            r.title = tags.get('title')
            r.track = tags.get('track')
            r.year = tags.get('year')
            r.genre = tags.get('genre')
            r.bitrate = tags.get('bitrate')
            r.sample_rate = tags.get('sample_rate')
            r.channels = tags.get('channels')

        elif ftype == 'Archive':
            info = _meta.archive_info(path, ext)
            r.file_count = info.get('file_count')
            r.dir_count = info.get('dir_count')
            r.total_uncompressed= info.get('total_uncompressed')
            r.compression_method= info.get('compression_method')
            r.encrypted = info.get('encrypted')
            r.archive_comment = info.get('comment')
            r.nested_archives = info.get('nested_archives')

        elif ftype == 'Document':
            r.length = _meta.doc_length(path, ext)

        elif ftype == 'Spreadsheet':
            info = _meta.spreadsheet_info(path, ext)
            r.dimensions = info.get('dimensions')
            r.sheet_count = info.get('sheet_count')
            if r.dimensions:
                r.length = f"{r.dimensions[0]:,} rows × {r.dimensions[1]:,} cols"

        elif ftype == 'Presentation':
            info = _meta.presentation_info(path, ext)
            r.slide_count = info.get('slide_count')
            r.notes_count = info.get('notes_count')
            if r.slide_count:
                r.length = f"{r.slide_count} slides"

        elif ftype == 'Crypto/Key':
            info = _meta.crypto_info(path, ext)
            r.key_type = info.get('key_type')
            r.algorithm = info.get('algorithm')
            r.key_id = info.get('key_id')
            r.created = info.get('created')
            r.expires = info.get('expires')
            r.user_id = info.get('user_id')
            r.packet_types = info.get('packet_types')
            r.armored = info.get('armored')
            r.key_comment = info.get('comment')

        elif ftype == 'Database':
            info = _meta.sqlite_info(path)
            if info.get('table_count') is not None:
                tables = info.get('tables', [])
                if tables:
                    summary = ', '.join(
                        f"{t['name']}({t['rows'] if t['rows'] is not None else '?'})"
                        for t in tables[:8])
                    if len(tables) > 8:
                        summary += f' … +{len(tables)-8} more'
                    r.db_tables = summary
                r.db_encoding = info.get('encoding')
                r.db_page_size = info.get('page_size')
                r.db_page_count = info.get('page_count')

        elif ftype == 'Font':
            info = _meta.font_info(path, ext)
            r.font_family = info.get('family')
            r.font_subfamily = info.get('subfamily')
            r.font_full_name = info.get('full_name')
            r.font_version = info.get('version')
            r.glyph_count = info.get('glyph_count')
            r.units_per_em = info.get('units_per_em')

        elif ftype == 'Email':
            info = _meta.email_info(path, ext)
            r.email_subject = info.get('subject')
            r.email_sender = info.get('sender')
            r.email_recipients = info.get('recipients')
            r.email_date = info.get('date')
            r.email_attachments = info.get('attachment_count')

        elif ftype == 'Torrent':
            info = _meta.torrent_info(path)
            r.torrent_name = info.get('name')
            r.torrent_files = info.get('file_count')
            r.torrent_size = info.get('total_size')
            r.torrent_tracker = info.get('tracker')
            r.torrent_created = info.get('creation_date')
            r.torrent_private = info.get('private')

        elif ftype == 'Shortcut':
            info = _meta.lnk_info(path)
            r.shortcut_target = info.get('target')
            r.shortcut_working_dir = info.get('working_dir')
            r.shortcut_args = info.get('arguments')
            r.shortcut_icon = info.get('icon')
            r.shortcut_hotkey = info.get('hotkey')
            r.shortcut_show = info.get('show_cmd')

        elif ftype == '3D':
            r.info_3d = _meta.model_3d_info(path, ext)

        elif ftype == 'Text/Code':
            r.length = _meta.text_line_count(path, ext)

    # Convenience helpers
    def search_in(self, folder: Union[str, Path], keywords: str = '', **kw) -> Iterator[Result]:
        """Search inside a folder. Mirrors GUI: "C:\\folder" keyword"""
        return self.search(f'"{folder}" {keywords}'.strip(), **kw)

    def search_ext(self, *extensions: str, keywords: str = '', **kw) -> Iterator[Result]:
        """Search by file extension(s). e.g. search_ext('pdf', 'docx')"""
        tokens = ' '.join(f'*.{e.lstrip(".")}' for e in extensions)
        return self.search(f'{tokens} {keywords}'.strip(), **kw)

    def search_image_formats(self, *formats: str, keywords: str = '', **kw) -> Iterator[Result]:
        """
        Search for specific image formats.
        search_image_formats('png', 'jpg', 'hdr') → ext:png;jpg;hdr
        """
        return self.search_ext(*formats, keywords=keywords, **kw)

    def search_video(self,   keywords: str = '', **kw): return self.search_ext(*_EXT_VIDEO,   keywords=keywords, **kw)
    def search_audio(self,   keywords: str = '', **kw): return self.search_ext(*_EXT_AUDIO,   keywords=keywords, **kw)
    def search_image(self,   keywords: str = '', **kw): return self.search_ext(*_EXT_IMAGE,   keywords=keywords, **kw)
    def search_doc(self,     keywords: str = '', **kw): return self.search_ext(*_EXT_DOC,     keywords=keywords, **kw)
    def search_3d(self,      keywords: str = '', **kw): return self.search_ext(*_EXT_3D,      keywords=keywords, **kw)
    def search_pptx(self,    keywords: str = '', **kw): return self.search_ext(*_EXT_PPTX,    keywords=keywords, **kw)
    def search_archive(self, keywords: str = '', **kw): return self.search_ext(*_EXT_ARCHIVE, keywords=keywords, **kw)
    def search_crypto(self,  keywords: str = '', **kw): return self.search_ext(*_EXT_CRYPTO,  keywords=keywords, **kw)
    def search_links(self,   keywords: str = '', **kw): return self.search_ext(*_EXT_LINK,    keywords=keywords, **kw)
    def search_fonts(self,   keywords: str = '', **kw): return self.search_ext(*_EXT_FONT,    keywords=keywords, **kw)
    def search_db(self,      keywords: str = '', **kw): return self.search_ext(*_EXT_DB,      keywords=keywords, **kw)

    # ctypes signatures
    def _setup_signatures(self) -> None:
        dll = self._dll
        BOOL = ctypes.c_bool
        DWORD = ctypes.c_ulong
        WCHAR = ctypes.c_wchar_p
        PULL = ctypes.POINTER(ctypes.c_ulonglong)

        dll.Everything_Reset.argtypes = []; dll.Everything_Reset.restype = None
        dll.Everything_SetSearchW.argtypes = [WCHAR]; dll.Everything_SetSearchW.restype = None
        dll.Everything_SetRegex.argtypes = [BOOL];  dll.Everything_SetRegex.restype = None
        dll.Everything_SetRequestFlags.argtypes = [DWORD]; dll.Everything_SetRequestFlags.restype = None
        dll.Everything_SetSort.argtypes = [DWORD]; dll.Everything_SetSort.restype = None
        dll.Everything_SetMax.argtypes = [DWORD]; dll.Everything_SetMax.restype = None
        dll.Everything_QueryW.argtypes = [BOOL];  dll.Everything_QueryW.restype = BOOL
        dll.Everything_GetNumResults.argtypes = []; dll.Everything_GetNumResults.restype = DWORD
        dll.Everything_GetLastError.argtypes = []; dll.Everything_GetLastError.restype = DWORD
        dll.Everything_GetResultFullPathNameW.argtypes = [DWORD, WCHAR, DWORD]
        dll.Everything_GetResultFullPathNameW.restype = None
        dll.Everything_GetResultSize.argtypes = [DWORD, PULL]; dll.Everything_GetResultSize.restype = None
        dll.Everything_GetResultDateModified.argtypes = [DWORD, PULL]; dll.Everything_GetResultDateModified.restype = None
        dll.Everything_GetResultDateCreated.argtypes = [DWORD, PULL]; dll.Everything_GetResultDateCreated.restype = None


# Demo
if __name__ == '__main__':
    QUERIES = [
        ('"C:\\Users\\nicho\\Downloads" pdf',     "PDFs in Downloads"),
        ('*.mp4 dm:lastmonth',                    "MP4s — past month (native syntax)"),
        ('*.py',                                  "Python files (line count)"),
        ('*.cpp OR *.h OR *.jl',                  "C++ / Julia files"),
        ('*.fbx',                                 "FBX 3D files (vertices + faces)"),
        ('*.blend',                               "Blender files"),
        ('*.zip',                                 "ZIP archives"),
        ('*.gpg OR *.asc OR *.pgp',               "PGP/GPG files"),
        ('*.lnk',                                 "Shortcuts (Target + Start In)"),
        ('*.sqlite OR *.db',                      "SQLite databases"),
        ('*.ttf OR *.otf',                        "Font files"),
        ('*.torrent',                             "Torrent files"),
        ('*.png OR *.jpg OR *.hdr',               "PNG / JPG / HDR images"),
    ]

    with EverythingSearch() as es:
        for q, label in QUERIES:
            print(f"\n{'='*65}")
            print(f"  {label}")
            print(f"  Query: {q!r}")
            print('='*65)
            for r in es.search(q, limit=2):
                print(r)
                print()
