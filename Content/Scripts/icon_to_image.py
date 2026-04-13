"""
icon_to_image.py
================
Extract Windows file/folder icons and thumbnails as PIL RGBA images.

Public API
----------
    # ── Single file ────────────────────────────────────────────────────────
    img  = get_icon(input_path, preview=True, debug=False)
            -> PIL.Image.Image  (256x256 RGBA)

    info = get_icon_info(input_path, preview=True, debug=False)
            -> dict  (see _ICON_INFO_FIELDS below; 'image' key holds PIL Image)

    # No output_path → returns info dict; with output_path → saves PNG (+ optionally dict)
    extract_icon(input_path, output_path, preview=True, debug=False)  -> None
    extract_icon(input_path,              preview=True, debug=False)   -> dict
    extract_icon(input_path, output_path, preview=True, debug=False,
                 return_info=True)                                     -> dict

    # ── Folder scan ────────────────────────────────────────────────────────
    # return_info=False (default) → {path: PIL Image}   or saves PNGs
    # return_info=True            → {path: info dict}   (never saves, output_dir ignored)
    get_folder_icons(folder_path, preview=True, debug=False,
                     recursive=False, output_dir=None,
                     return_info=False)
            -> dict

    # ── Priority queue ─────────────────────────────────────────────────────
    q = IconQueue()
    q.add(path, priority=0)
    q.add_many(paths, priority=0)

    # return_info=False → yields (path, PIL Image)
    # return_info=True  → yields (path, info dict)
    for path, result in q.process(preview=True, debug=False, return_info=False):
        ...

    # return_info=False → saves PNGs, returns list of output paths
    # return_info=True  → saves PNGs AND returns {path: info dict}
    q.process_to_dir(output_dir, preview=True, debug=False, return_info=False)

_ICON_INFO_FIELDS
-----------------
    full_path      str                 absolute path as given
    name           str                 filename with extension  (or raw token)
    stem           str                 filename without extension
    extension      str                 lower-case extension incl. dot, e.g. ".pdf"
    is_dir         bool
    size_bytes     int | None
    size           str | None          human-readable, e.g. "22.51 MB"
    date_modified  datetime | None
    date_created   datetime | None     (st_ctime on Windows = creation time)
    date_accessed  datetime | None
    is_preview     bool                True = content thumbnail, False = type icon
    cost_tier      str                 "icon" | "image" | "video" | "render"
    image          PIL.Image.Image     256×256 RGBA

input_path can be:
  - Real file path  (.exe, .dll, .lnk, .pdf, .py, .ini, any type …)
  - Real folder path  (special folders like Downloads get unique icons)
  - Extension string  (".pdf", ".mp3", "docx" …)
  - "<folder>"        → generic folder icon
  - ""                → generic unknown-file icon

PDF preview:    pip install pymupdf
SVG preview:    Inkscape at C:\\Program Files\\Inkscape (already installed)
Video preview:  pip install opencv-python
HDR/EXR:        pip install imageio numpy

Notes
-----
- _imagelist_icon trusts the NOMINAL size from SHGetImageList, not _icon_size().
  Shell image list icons report small HICON bitmap dimensions even when drawn at
  256px — the size is in the LIST, not the HICON header.
- All unknown/unregistered extensions fall through to _imagelist_icon which asks
  the shell for whatever icon it would show in Explorer.
"""

import datetime
import os
import sys
import ctypes
import ctypes.wintypes
import win32ui
import win32gui
import win32con
from pathlib import Path
from PIL import Image

# ── Constants ─────────────────────────────────────────────────────────────────

SHGFI_ICON              = 0x0000_0100
SHGFI_LARGEICON         = 0x0000_0000
SHGFI_SYSICONINDEX      = 0x0000_4000
SHGFI_USEFILEATTRIBUTES = 0x0000_0010
FILE_ATTRIBUTE_NORMAL   = 0x80
FILE_ATTRIBUTE_DIRECTORY= 0x10

SHIL_LARGE      = 0x0   # 32×32
SHIL_EXTRALARGE = 0x2   # 48×48
SHIL_JUMBO      = 0x4   # 256×256

PREVIEW_EXTENSIONS = {
    ".png", ".jpg", ".jpeg", ".bmp", ".gif", ".tiff", ".tif", ".webp",
    ".ico", ".hdr", ".exr", ".tga", ".psd", ".heic", ".heif", ".avif",
    ".raw", ".cr2", ".nef", ".arw",
    ".mp4", ".mkv", ".mov", ".avi", ".wmv", ".flv", ".webm", ".m4v",
    ".mpg", ".mpeg", ".3gp", ".ts", ".mts", ".m2ts",
    ".svg", ".pdf",
}

PIL_EXTENSIONS = {
    ".png", ".jpg", ".jpeg", ".bmp", ".gif", ".tiff", ".tif",
    ".webp", ".ico", ".tga", ".psd", ".heic", ".heif", ".avif",
}

ASSOCIATED_EXTENSIONS = {
    ".py", ".pyi", ".pyw",
    ".md", ".markdown", ".rst",
    ".ini", ".cfg", ".conf", ".toml", ".yaml", ".yml", ".json", ".xml",
    ".vbs", ".js", ".ts", ".jsx", ".tsx", ".bat", ".cmd", ".ps1", ".sh",
    ".sln", ".csproj", ".vcxproj", ".props", ".targets",
    ".lng", ".log", ".csv", ".tsv", ".txt", ".nfo", ".readme",
    ".pdf", ".docx", ".xlsx", ".pptx", ".odt", ".ods", ".odp",
    ".html", ".htm", ".css", ".scss", ".less",
    ".c", ".cpp", ".h", ".hpp", ".cs", ".java", ".rb", ".php", ".go",
    ".rs", ".swift", ".kt", ".lua", ".r", ".m", ".f90",
    ".sql", ".graphql", ".proto",
    ".reg", ".inf",
}

# ── Globals ───────────────────────────────────────────────────────────────────

_DEBUG         = False
_INKSCAPE_PATH = None
_comctl32      = None

def _dbg(*args):
    if _DEBUG:
        print("[icon_debug]", *args)


# ── COM initialisation ────────────────────────────────────────────────────────

_COM_INITIALISED = False

def _ensure_com():
    global _COM_INITIALISED
    if _COM_INITIALISED:
        return
    hr = ctypes.windll.ole32.CoInitializeEx(None, 0x2)
    _dbg("CoInitializeEx hr={}".format(hr))
    _COM_INITIALISED = True


# ── Structs ───────────────────────────────────────────────────────────────────

class SHFILEINFO(ctypes.Structure):
    _fields_ = [
        ("hIcon",         ctypes.wintypes.HANDLE),
        ("iIcon",         ctypes.c_int),
        ("dwAttributes",  ctypes.wintypes.DWORD),
        ("szDisplayName", ctypes.c_wchar * 260),
        ("szTypeName",    ctypes.c_wchar * 80),
    ]


class _ICONINFO(ctypes.Structure):
    _fields_ = [
        ("fIcon",    ctypes.wintypes.BOOL),
        ("xHotspot", ctypes.wintypes.DWORD),
        ("yHotspot", ctypes.wintypes.DWORD),
        ("hbmMask",  ctypes.wintypes.HANDLE),
        ("hbmColor", ctypes.wintypes.HANDLE),
    ]


class _GUID(ctypes.Structure):
    _fields_ = [
        ("Data1", ctypes.c_ulong),
        ("Data2", ctypes.c_ushort),
        ("Data3", ctypes.c_ushort),
        ("Data4", ctypes.c_ubyte * 8),
    ]

_IID_IImageList = _GUID(
    0x46EB5926, 0x582E, 0x4017,
    (ctypes.c_ubyte * 8)(0x9F, 0xDF, 0xE8, 0x99, 0x8D, 0xAA, 0x09, 0x50),
)


# ── Filesystem metadata helper ────────────────────────────────────────────────

from utils import human_size as _human_size


def _stat_info(input_path):
    """
    Return a dict of filesystem fields for *input_path*.
    All date/size fields are None for tokens like ".pdf" or "<folder>".

    Keys: full_path, name, stem, extension, is_dir,
          size_bytes, size, date_modified, date_created, date_accessed.
    """
    full_path = input_path
    is_real   = os.path.exists(input_path)

    if is_real:
        name      = os.path.basename(input_path.rstrip("/\\")) or input_path
        stem, ext = os.path.splitext(name)
        is_dir    = os.path.isdir(input_path)
    elif input_path == "<folder>":
        name, stem, ext, is_dir = "<folder>", "<folder>", "", True
    else:
        # bare extension or unrecognised token
        _, ext = os.path.splitext(input_path)
        ext    = (ext or ("." + input_path.lstrip("."))).lower()
        name   = input_path
        stem   = os.path.splitext(input_path)[0]
        is_dir = False

    size_bytes = date_modified = date_created = date_accessed = None
    if is_real and not is_dir:
        try:
            st             = os.stat(input_path)
            size_bytes     = st.st_size
            date_modified  = datetime.datetime.fromtimestamp(st.st_mtime)
            date_created   = datetime.datetime.fromtimestamp(st.st_ctime)   # creation on Windows
            date_accessed  = datetime.datetime.fromtimestamp(st.st_atime)
        except OSError:
            pass
    elif is_real and is_dir:
        try:
            st            = os.stat(input_path)
            date_modified = datetime.datetime.fromtimestamp(st.st_mtime)
            date_created  = datetime.datetime.fromtimestamp(st.st_ctime)
            date_accessed = datetime.datetime.fromtimestamp(st.st_atime)
        except OSError:
            pass

    return {
        "full_path":     full_path,
        "name":          name,
        "stem":          stem,
        "extension":     ext.lower(),
        "is_dir":        is_dir,
        "size_bytes":    size_bytes,
        "size":          _human_size(size_bytes),
        "date_modified": date_modified,
        "date_created":  date_created,
        "date_accessed": date_accessed,
    }

# ── Batch / folder / priority-queue helpers ───────────────────────────────────

_COST = {
    "icon":   0,
    "image":  1,
    "video":  2,
    "render": 3,
}

_COST_NAMES = {v: k for k, v in _COST.items()}   # 0->"icon", 1->"image", etc.

def _build_info_dict(input_path, img, is_pil):
    """
    Combine _stat_info() with the extracted PIL image and derived fields.
    Returns the complete info dict described in _ICON_INFO_FIELDS.
    """
    info              = _stat_info(input_path)
    info["image"]     = img
    info["is_preview"]= bool(is_pil)
    info["cost_tier"] = _COST_NAMES.get(_path_cost(input_path), "icon")
    return info


# ── Public API ────────────────────────────────────────────────────────────────

def get_icon(input_path, preview=True, debug=False):
    """
    Extract the icon/thumbnail for *input_path* and return as a 256×256 PIL RGBA Image.

    input_path can be a real file, real folder, extension string (".pdf"),
    "<folder>" for a generic folder icon, or "" for a generic unknown-file icon.

    preview=True  : image/video/svg/pdf files return a content thumbnail.
    preview=False : always return the file-type icon.
    debug=True    : print detailed trace of every resolution attempt.
    """
    global _DEBUG
    _DEBUG = debug
    _ensure_com()
    _dbg("get_icon({!r}, preview={})".format(input_path, preview))

    hicon, size, is_pil = _resolve(input_path, preview)
    try:
        if is_pil:
            _dbg("result: PIL Image 256×256")
            return hicon                        # already a PIL Image from preview path
        _dbg("result: HICON={} size={}px -> rendering".format(hicon, size))
        img = _hicon_to_pil(hicon, size)
        win32gui.DestroyIcon(hicon)
        return img
    except Exception:
        if not is_pil:
            try:
                win32gui.DestroyIcon(hicon)
            except Exception:
                pass
        raise


def get_icon_info(input_path, preview=True, debug=False):
    """
    Extract the icon/thumbnail for *input_path* and return a rich info dict.

    The dict contains all filesystem metadata plus the image — see the module
    docstring (_ICON_INFO_FIELDS) for the full list of keys.  The 'image' key
    holds a 256×256 PIL RGBA Image; no files are written.

    Parameters
    ----------
    input_path : str
        Anything accepted by get_icon().
    preview : bool
        True (default) returns content thumbnails for image/video/pdf/svg.
    debug : bool
        Print detailed resolution trace.

    Returns
    -------
    dict
    """
    global _DEBUG
    _DEBUG = debug
    _ensure_com()
    _dbg("get_icon_info({!r}, preview={})".format(input_path, preview))

    hicon, size, is_pil = _resolve(input_path, preview)
    try:
        if is_pil:
            img = hicon   # already PIL from preview path
        else:
            img = _hicon_to_pil(hicon, size)
            win32gui.DestroyIcon(hicon)
    except Exception:
        if not is_pil:
            try:
                win32gui.DestroyIcon(hicon)
            except Exception:
                pass
        raise

    return _build_info_dict(input_path, img, is_pil)


def extract_icon(input_path, output_path=None, preview=True, debug=False,
                 return_info=False):
    """
    Extract the icon/thumbnail for *input_path*.

    Behaviour depends on *output_path* and *return_info*:

    output_path=None (omitted)
        → Returns an info dict (see _ICON_INFO_FIELDS).  No file is written.
          Equivalent to get_icon_info().

    output_path given, return_info=False (default)
        → Saves PNG to *output_path*.  Returns None.
          Original behaviour, fully backwards-compatible.

    output_path given, return_info=True
        → Saves PNG to *output_path* AND returns the info dict.

    Parameters
    ----------
    input_path  : str
    output_path : str or None
    preview     : bool
    debug       : bool
    return_info : bool
        Force dict return even when output_path is provided.

    Returns
    -------
    None | dict
    """
    global _DEBUG
    _DEBUG = debug
    _ensure_com()

    hicon, size, is_pil = _resolve(input_path, preview)
    try:
        if is_pil:
            img = hicon
        else:
            img = _hicon_to_pil(hicon, size)
            win32gui.DestroyIcon(hicon)
    except Exception:
        if not is_pil:
            try:
                win32gui.DestroyIcon(hicon)
            except Exception:
                pass
        raise

    if output_path is not None:
        img.save(output_path, "PNG")

    if output_path is None or return_info:
        return _build_info_dict(input_path, img, is_pil)
    return None


# ── Dispatcher ────────────────────────────────────────────────────────────────

def _resolve(input_path, preview):
    """Returns (hicon_or_pil_image, size, is_pil_image)."""

    if input_path == "<folder>":
        _dbg("mode: generic folder token")
        hicon, size = _plain_folder_icon()
        return hicon, size, False

    if os.path.isdir(input_path):
        _dbg("mode: real directory")
        hicon, size = _special_folder_icon(input_path)
        return hicon, size, False

    if os.path.isfile(input_path):
        ext = os.path.splitext(input_path)[1].lower()
        _dbg("mode: real file, ext={}".format(ext))

        if preview and ext in PREVIEW_EXTENSIONS:
            _dbg("attempting preview for {}".format(ext))
            img = _get_preview(input_path, ext)
            if img is not None:
                _dbg("preview succeeded")
                return img, 256, True
            _dbg("preview failed, falling back to icon")

        if ext == ".lnk":
            hicon, size = _lnk_icon(input_path)
            return hicon, size, False

        if ext in ASSOCIATED_EXTENSIONS:
            _dbg("associated extension, using registry/extension lookup")
            hicon, size = _extension_icon(ext)
            if hicon:
                return hicon, size, False
            _dbg("registry lookup failed, falling back to _best_file_icon")

        hicon, size = _best_file_icon(input_path)
        return hicon, size, False

    # Bare extension or unrecognised path
    _, ext = os.path.splitext(input_path)
    candidate = (ext or input_path).strip()
    if candidate and not candidate.startswith("."):
        candidate = "." + candidate
    _dbg("mode: extension lookup for {!r}".format(candidate))
    hicon, size = _extension_icon(candidate)
    if not hicon:
        raise RuntimeError("Could not resolve any icon for: {!r}".format(input_path))
    return hicon, size, False


# ── Preview / thumbnail ───────────────────────────────────────────────────────

def _get_preview(path, ext):
    if ext == ".pdf":
        _dbg("  preview: trying PDF render")
        img = _pdf_preview(path)
        if img:
            return img
        _dbg("  preview: PDF render failed")
        return None

    if ext == ".svg":
        _dbg("  preview: trying SVG render")
        return _svg_preview(path)

    if ext in {".mp4", ".mkv", ".mov", ".avi", ".wmv", ".flv", ".webm",
               ".m4v", ".mpg", ".mpeg", ".3gp", ".ts", ".mts", ".m2ts"}:
        _dbg("  preview: trying video frame grab")
        try:
            # fix for cv2 dlls
            python_root = Path(sys.prefix)
            os.add_dll_directory(str(python_root))
            os.add_dll_directory(str(python_root / "DLLs"))
            os.add_dll_directory(str(python_root / "Lib" / "site-packages" / "cv2"))

            import cv2
            cap = cv2.VideoCapture(path, cv2.CAP_FFMPEG)
            cap.set(cv2.CAP_PROP_BUFFERSIZE, 1)
            ok, frame = cap.read()
            cap.release()
            if ok:
                return _fit_256(Image.fromarray(
                    cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)).convert("RGBA"))
            _dbg("  preview: cv2 read failed")
        except Exception as e:
            _dbg("  preview: cv2 exception:", e)
        return None

    if ext in PIL_EXTENSIONS:
        _dbg("  preview: trying PIL open")
        try:
            img = Image.open(path)
            img.load()
            return _fit_256(img.convert("RGBA"))
        except Exception as e:
            _dbg("  preview: PIL open failed:", e)

    if ext in {".hdr", ".exr"}:
        _dbg("  preview: trying imageio HDR/EXR")
        try:
            import imageio.v2 as imageio
            import numpy as np
            data = imageio.imread(path)
            data = np.clip(data / (data.max() + 1e-6), 0, 1)
            data = (data * 255).astype("uint8")
            if data.ndim == 2:
                data = np.stack([data] * 3, axis=-1)
            return _fit_256(Image.fromarray(data[..., :3].copy()).convert("RGBA"))
        except Exception as e:
            _dbg("  preview: imageio failed:", e)

    return None


def _pdf_preview(path):
    _dbg("    pdf: trying shell thumbnail provider")
    img = _shell_thumbnail(path, require_thumbnail=True)
    if img is not None:
        _dbg("    pdf: shell thumbnail succeeded")
        return img
    _dbg("    pdf: shell thumbnail failed, falling back to pymupdf")
    try:
        import fitz
        _dbg("    pdf: using pymupdf")
        doc  = fitz.open(path)
        page = doc[0]
        pix  = page.get_pixmap(matrix=fitz.Matrix(3, 3), alpha=False)
        doc.close()
        return _fit_256(
            Image.frombytes("RGB", (pix.width, pix.height), pix.samples).convert("RGBA"))
    except Exception as e:
        _dbg("    pdf: pymupdf failed:", e)

    try:
        from pdf2image import convert_from_path
        _dbg("    pdf: using pdf2image")
        pages = convert_from_path(path, dpi=72, first_page=1, last_page=1)
        if pages:
            return _fit_256(pages[0].convert("RGBA"))
    except Exception as e:
        _dbg("    pdf: pdf2image failed:", e)

    return None


def _find_inkscape():
    global _INKSCAPE_PATH
    if _INKSCAPE_PATH:
        return _INKSCAPE_PATH
    import shutil
    for candidate in [
        r"C:\Program Files\Inkscape\bin\inkscape.exe",
        r"C:\Program Files (x86)\Inkscape\bin\inkscape.exe",
    ]:
        if os.path.isfile(candidate):
            _INKSCAPE_PATH = candidate
            return candidate
    found = shutil.which("inkscape")
    if found:
        _INKSCAPE_PATH = found
        return found
    return None


def _svg_preview(path):
    img = _shell_thumbnail(path, require_thumbnail=False)
    if img is not None:
        _dbg("    svg: shell thumbnail provider succeeded")
        return img
    _dbg("    svg: shell thumbnail failed, trying Inkscape")

    ink = _find_inkscape()
    if ink:
        try:
            import subprocess
            from io import BytesIO
            r = subprocess.run(
                [ink, "--export-type=png", "--export-width=256",
                 "--export-height=256", "--export-filename=-", path],
                capture_output=True, timeout=15,
            )
            if r.returncode == 0 and r.stdout:
                _dbg("    svg: Inkscape succeeded")
                return _fit_256(Image.open(BytesIO(r.stdout)).convert("RGBA"))
            _dbg("    svg: Inkscape non-zero exit {}".format(r.returncode))
        except Exception as e:
            _dbg("    svg: Inkscape failed:", e)

    try:
        from svglib.svglib import svg2rlg
        from reportlab.graphics import renderPM
        from io import BytesIO
        drawing = svg2rlg(path)
        if drawing and drawing.width > 0 and drawing.height > 0:
            sc = min(256 / drawing.width, 256 / drawing.height)
            drawing.width  *= sc
            drawing.height *= sc
            drawing.transform = (sc, 0, 0, sc, 0, 0)
            buf = BytesIO()
            renderPM.drawToFile(drawing, buf, fmt="PNG")
            buf.seek(0)
            _dbg("    svg: svglib succeeded")
            return _fit_256(Image.open(buf).convert("RGBA"))
        _dbg("    svg: svglib returned None or zero-size")
    except Exception as e:
        _dbg("    svg: svglib failed:", str(e).split("\n")[0])

    try:
        import cairosvg
        from io import BytesIO
        png = cairosvg.svg2png(url=path, output_width=256, output_height=256)
        _dbg("    svg: cairosvg succeeded")
        return _fit_256(Image.open(BytesIO(png)).convert("RGBA"))
    except Exception as e:
        _dbg("    svg: cairosvg failed:", str(e).split("\n")[0])

    try:
        img = _svg_via_aggdraw(path)
        if img:
            _dbg("    svg: aggdraw succeeded")
            return img
    except Exception as e:
        _dbg("    svg: aggdraw failed:", e)

    return None


def _svg_via_aggdraw(path):
    import aggdraw
    import xml.etree.ElementTree as ET
    import re

    root   = ET.parse(path).getroot()
    SVG_NS = "http://www.w3.org/2000/svg"
    vb     = root.get("viewBox", "")
    if vb:
        parts = [float(x) for x in re.split(r"[\s,]+", vb.strip()) if x]
        vb_w, vb_h = parts[2], parts[3]
    else:
        vb_w = float(re.sub(r"[^\d.]", "", root.get("width",  "256")) or 256)
        vb_h = float(re.sub(r"[^\d.]", "", root.get("height", "256")) or 256)

    scale  = min(256 / max(vb_w, 1), 256 / max(vb_h, 1))
    canvas = Image.new("RGBA", (256, 256), (0, 0, 0, 0))
    draw   = aggdraw.Draw(canvas)

    def parse_color(s):
        if not s or s in ("none", "transparent"):
            return None
        s = s.strip()
        if s.startswith("#"):
            h = s.lstrip("#")
            if len(h) == 3:
                h = "".join(c*2 for c in h)
            try:
                return int(h[0:2], 16), int(h[2:4], 16), int(h[4:6], 16)
            except Exception:
                return None
        if s.startswith("rgb("):
            n = re.findall(r"\d+", s)
            if len(n) >= 3:
                return int(n[0]), int(n[1]), int(n[2])
        return None

    def pb(elem):
        fc = parse_color(elem.get("fill",   "black"))
        sc = parse_color(elem.get("stroke", "none"))
        sw = float(elem.get("stroke-width", "1")) * scale
        return (aggdraw.Pen(sc, max(1, sw), 255) if sc else None,
                aggdraw.Brush(fc, 255) if fc else None)

    def render(elem):
        tag = elem.tag.replace("{" + SVG_NS + "}", "")
        pen, brush = pb(elem)
        if not pen and not brush:
            brush = aggdraw.Brush((0, 0, 0), 255)
        if tag == "rect":
            x = float(elem.get("x", "0")) * scale
            y = float(elem.get("y", "0")) * scale
            w = float(elem.get("width",  "0")) * scale
            h = float(elem.get("height", "0")) * scale
            if w > 0 and h > 0:
                draw.rectangle([x, y, x+w, y+h], pen, brush)
        elif tag in ("circle", "ellipse"):
            cx = float(elem.get("cx", "0")) * scale
            cy = float(elem.get("cy", "0")) * scale
            rx = float(elem.get("r",  elem.get("rx", "0"))) * scale
            ry = float(elem.get("r",  elem.get("ry", "0"))) * scale
            if rx > 0 and ry > 0:
                draw.ellipse([cx-rx, cy-ry, cx+rx, cy+ry], pen, brush)
        elif tag == "line":
            coords = [float(elem.get(k, "0")) * scale for k in ("x1","y1","x2","y2")]
            if pen:
                draw.line(coords, pen)
        elif tag in ("polyline", "polygon"):
            pts = [float(v) * scale for v in re.findall(r"[-\d.]+", elem.get("points",""))]
            if len(pts) >= 4:
                (draw.polygon if tag == "polygon" else draw.line)(pts, pen, brush)
        elif tag == "path":
            d = elem.get("d", "")
            if d:
                try:
                    draw.symbol((0, 0), aggdraw.Symbol(d), pen, brush)
                except Exception:
                    pass
        if tag in ("g", "svg", "defs", "symbol", "use", "clipPath", "mask"):
            for child in elem:
                try:
                    render(child)
                except Exception:
                    pass

    for child in root:
        try:
            render(child)
        except Exception:
            pass
    draw.flush()
    return _fit_256(canvas)


def _shell_thumbnail(path, require_thumbnail=True):
    _dbg("  shell_thumbnail path={!r} require={}".format(path, require_thumbnail))
    try:
        IID_SIIF = (ctypes.c_byte * 16)(
            0x79, 0x8B, 0xC1, 0xBC, 0x16, 0xBA, 0x2F, 0x44,
            0x80, 0xC4, 0x8A, 0x59, 0xC3, 0x0C, 0x46, 0x3B,
        )
        factory = ctypes.c_void_p()
        hr = ctypes.windll.shell32.SHCreateItemFromParsingName(
            path, None, ctypes.byref(IID_SIIF), ctypes.byref(factory),
        )
        _dbg("    SHCreateItemFromParsingName hr={}".format(hr))
        if hr != 0 or not factory:
            return None

        class SIZE(ctypes.Structure):
            _fields_ = [("cx", ctypes.c_long), ("cy", ctypes.c_long)]

        flags = 0x2 if require_thumbnail else 0x0
        sz    = SIZE(256, 256)
        hbmp  = ctypes.c_size_t()

        vtbl = ctypes.cast(factory, ctypes.POINTER(ctypes.c_void_p)).contents.value
        vptr = ctypes.cast(ctypes.c_void_p(vtbl), ctypes.POINTER(ctypes.c_void_p))

        GetImage = ctypes.WINFUNCTYPE(
            ctypes.HRESULT, ctypes.c_void_p, SIZE, ctypes.c_uint,
            ctypes.POINTER(ctypes.c_size_t),
        )(ctypes.cast(ctypes.c_void_p(vptr[3]), ctypes.c_void_p).value)

        hr = GetImage(factory, sz, flags, ctypes.byref(hbmp))
        _dbg("    GetImage hr={} hbmp={}".format(hr, hbmp.value))

        Release = ctypes.WINFUNCTYPE(ctypes.c_ulong, ctypes.c_void_p)(
            ctypes.cast(ctypes.c_void_p(vptr[2]), ctypes.c_void_p).value
        )
        Release(factory)

        if hr != 0 or not hbmp.value:
            return None

        hbmp_int = int(hbmp.value)
        w, h = 256, 256

        class BITMAPINFOHEADER(ctypes.Structure):
            _fields_ = [
                ("biSize",          ctypes.c_uint32),
                ("biWidth",         ctypes.c_int32),
                ("biHeight",        ctypes.c_int32),
                ("biPlanes",        ctypes.c_uint16),
                ("biBitCount",      ctypes.c_uint16),
                ("biCompression",   ctypes.c_uint32),
                ("biSizeImage",     ctypes.c_uint32),
                ("biXPelsPerMeter", ctypes.c_int32),
                ("biYPelsPerMeter", ctypes.c_int32),
                ("biClrUsed",       ctypes.c_uint32),
                ("biClrImportant",  ctypes.c_uint32),
            ]

        bih = BITMAPINFOHEADER()
        bih.biSize        = ctypes.sizeof(BITMAPINFOHEADER)
        bih.biWidth       = w
        bih.biHeight      = -h
        bih.biPlanes      = 1
        bih.biBitCount    = 32
        bih.biCompression = 0

        buf   = (ctypes.c_byte * (w * h * 4))()
        hdc_s = win32gui.GetDC(0)
        hdc   = win32ui.CreateDCFromHandle(hdc_s)
        rows  = ctypes.windll.gdi32.GetDIBits(
            hdc.GetSafeHdc(), hbmp_int, 0, h, buf,
            ctypes.byref(bih), 0,
        )
        hdc.DeleteDC()
        win32gui.ReleaseDC(0, hdc_s)
        ctypes.windll.gdi32.DeleteObject(hbmp_int)
        _dbg("    bitmap size: {}x{} rows={}".format(w, h, rows))

        if rows <= 0:
            return None

        import numpy as np
        arr           = np.frombuffer(bytes(buf), dtype=np.uint8).reshape(h, w, 4).copy()
        alpha_channel = arr[:, :, 3]
        rgb_channel   = arr[:, :, :3]
        _dbg("    bitmap alpha min={} max={} rgb_max={}".format(
            int(alpha_channel.min()), int(alpha_channel.max()), int(rgb_channel.max())))
        if alpha_channel.max() == 0:
            if rgb_channel.max() > 0:
                _dbg("    bitmap: zero-alpha detected, treating as opaque RGB")
                arr[:, :, 3] = 255
        else:
            a    = alpha_channel.astype(np.float32) / 255.0
            mask = a > 0
            for c in range(3):
                channel       = arr[:, :, c].astype(np.float32)
                channel[mask] = np.clip(channel[mask] / a[mask], 0, 255)
                arr[:, :, c]  = channel.astype(np.uint8)
        arr = arr[:, :, [2, 1, 0, 3]]
        img = Image.fromarray(arr.astype(np.uint8))

        opaque = arr[:, :, 3] > 128
        if opaque.sum() > 0:
            dark       = ((arr[:, :, 0] < 8) & (arr[:, :, 1] < 8) & (arr[:, :, 2] < 8) & opaque)
            dark_ratio = dark.sum() / opaque.sum()
            _dbg("    bitmap dark_ratio={:.3f}".format(float(dark_ratio)))
            if dark_ratio > 0.98:
                _dbg("    bitmap: result is all-black, treating as failed thumbnail")
                return None

        return _fit_256(img)

    except Exception as e:
        _dbg("    shell_thumbnail exception:", e)
        return None


def _fit_256(img):
    img.thumbnail((256, 256), Image.LANCZOS)
    canvas = Image.new("RGBA", (256, 256), (0, 0, 0, 0))
    canvas.paste(img, ((256 - img.width) // 2, (256 - img.height) // 2))
    return canvas


# ── Special / shell folder icons ──────────────────────────────────────────────

def _special_folder_icon(path):
    _dbg("  special_folder_icon: {}".format(path))
    h, s = _imagelist_icon(path, FILE_ATTRIBUTE_DIRECTORY, use_attrs=False)
    if h:
        return h, s
    return _plain_folder_icon()


def _plain_folder_icon():
    system32 = os.path.join(os.environ.get("SystemRoot", r"C:\Windows"), "system32")
    for src, idx in [
        (os.path.join(system32, "imageres.dll"), 3),
        (os.path.join(system32, "shell32.dll"),  3),
    ]:
        if os.path.isfile(src):
            h, s = _private_extract(src, idx)
            if h:
                return h, s
    return 0, 32


# ── Shortcut resolution ───────────────────────────────────────────────────────

def _lnk_icon(lnk_path):
    _dbg("  resolving .lnk: {}".format(lnk_path))
    try:
        import win32com.client
        shell    = win32com.client.Dispatch("WScript.Shell")
        lnk      = shell.CreateShortcut(lnk_path)
        target   = lnk.TargetPath.strip()   if lnk.TargetPath   else ""
        icon_loc = lnk.IconLocation.strip() if lnk.IconLocation else ""
        _dbg("  lnk target={!r}  iconloc={!r}".format(target, icon_loc))

        if icon_loc and icon_loc not in (",0", ","):
            icon_src, idx = _split_icon_loc(icon_loc)
            _dbg("  lnk custom icon src={!r} idx={}".format(icon_src, idx))
            if icon_src and os.path.isfile(icon_src):
                h, s = _private_extract(icon_src, idx)
                _dbg("  lnk PrivateExtract on custom: h={} s={}".format(h, s))
                if h and s >= 48:
                    return h, s
                h2, s2 = _imagelist_icon(icon_src, FILE_ATTRIBUTE_NORMAL)
                if h2:
                    if h:
                        win32gui.DestroyIcon(h)
                    return h2, s2
                if h:
                    return h, s

        if target:
            if os.path.isdir(target):
                return _special_folder_icon(target)
            if os.path.isfile(target):
                return _best_file_icon(target)

    except Exception as e:
        _dbg("  lnk win32com error:", e)

    try:
        target, icon_src, icon_idx = _parse_lnk_binary(lnk_path)
        _dbg("  lnk binary: target={!r} icon={!r} idx={}".format(target, icon_src, icon_idx))
        if icon_src and os.path.isfile(icon_src):
            h, s = _private_extract(icon_src, icon_idx)
            if h and s >= 48:
                return h, s
        if target:
            if os.path.isdir(target):
                return _special_folder_icon(target)
            if os.path.isfile(target):
                return _best_file_icon(target)
    except Exception as e:
        _dbg("  lnk binary parse error:", e)

    h, s = _imagelist_icon(lnk_path, FILE_ATTRIBUTE_NORMAL)
    if h:
        return h, s
    hicon = _shgetfileinfo_icon(lnk_path, FILE_ATTRIBUTE_NORMAL)
    if hicon:
        return hicon, 32
    system32 = os.path.join(os.environ.get("SystemRoot", r"C:\Windows"), "system32")
    for src, idx in [
        (os.path.join(system32, "shell32.dll"),  0),
        (os.path.join(system32, "imageres.dll"), 2),
    ]:
        if os.path.isfile(src):
            h, s = _private_extract(src, idx)
            if h:
                return h, s
    raise RuntimeError("Could not extract any icon from shortcut: {!r}".format(lnk_path))


def _split_icon_loc(icon_loc):
    if "," in icon_loc:
        src, _, idx_s = icon_loc.rpartition(",")
        src = src.strip().strip('"')
        try:
            idx = int(idx_s)
        except ValueError:
            idx = 0
    else:
        src, idx = icon_loc.strip().strip('"'), 0
    return os.path.expandvars(src), idx


def _parse_lnk_binary(lnk_path):
    import struct, re
    with open(lnk_path, "rb") as f:
        data = f.read()
    if len(data) < 76 or data[:4] != b"\x4c\x00\x00\x00":
        return "", "", 0
    flags  = struct.unpack_from("<I", data, 20)[0]
    offset = 76
    if flags & 0x01:
        if offset + 2 > len(data):
            return "", "", 0
        offset += 2 + struct.unpack_from("<H", data, offset)[0]
    if flags & 0x02:
        if offset + 4 > len(data):
            return "", "", 0
        offset += struct.unpack_from("<I", data, offset)[0]
    IS_UNICODE = bool(flags & 0x80)

    def read_str(off):
        if off + 2 > len(data):
            return "", off
        count = struct.unpack_from("<H", data, off)[0]
        off  += 2
        if IS_UNICODE:
            s = data[off:off+count*2].decode("utf-16-le", errors="replace")
            return s, off + count * 2
        return data[off:off+count].decode("cp1252", errors="replace"), off + count

    icon_path = ""
    icon_idx  = 0
    for section, flag in [("relative",0x08),("workdir",0x10),("args",0x20),("icon",0x40)]:
        if flags & flag:
            s, offset = read_str(offset)
            if section == "icon" and s:
                if "," in s:
                    ip, _, ii = s.rpartition(",")
                    try:
                        icon_idx = int(ii)
                    except ValueError:
                        icon_idx = 0
                    icon_path = os.path.expandvars(ip.strip())
                else:
                    icon_path = os.path.expandvars(s.strip())

    target_path = ""
    for m in re.finditer(
        rb"[A-Za-z]:\\(?:[^\x00-\x1f\x7f\\/:*?\"<>|]+\\)*"
        rb"[^\x00-\x1f\x7f\\/:*?\"<>|]+\.[A-Za-z]{2,4}\x00",
        data[76:]
    ):
        c = m.group(0)[:-1].decode("latin-1", errors="replace")
        if os.path.exists(c):
            target_path = c
            break

    return target_path, icon_path, icon_idx


# ── Core icon extraction ──────────────────────────────────────────────────────

def _best_file_icon(path, index=0):
    _dbg("  _best_file_icon: {} idx={}".format(path, index))
    h1, s1 = _private_extract(path, index)
    _dbg("    PrivateExtract: h={} s={}".format(h1, s1))
    h2, s2 = _imagelist_icon(path, FILE_ATTRIBUTE_NORMAL)
    _dbg("    ImageList:      h={} s={}".format(h2, s2))

    if h1 and h2:
        if s1 >= s2:
            win32gui.DestroyIcon(h2)
            return h1, s1
        win32gui.DestroyIcon(h1)
        return h2, s2
    if h1:
        return h1, s1
    if h2:
        return h2, s2

    if index == 0:
        for size in [256, 128, 64, 48, 32]:
            hicon = ctypes.windll.user32.LoadImageW(
                None, path, win32con.IMAGE_ICON, size, size,
                win32con.LR_LOADFROMFILE | win32con.LR_DEFAULTCOLOR,
            )
            if hicon:
                _dbg("    LoadImage: h={} s={}".format(hicon, size))
                return hicon, size

    hicon = _shgetfileinfo_icon(path, FILE_ATTRIBUTE_NORMAL)
    _dbg("    SHGetFileInfo fallback: h={}".format(hicon))
    if hicon:
        return hicon, 32

    raise RuntimeError("Could not extract icon from: {!r}".format(path))


def _extension_icon(ext):
    _dbg("  _extension_icon: {}".format(ext))

    h1, s1 = _registry_icon(ext)
    _dbg("    registry result: h={} s={}".format(h1, s1))

    fake   = "C:\\fakefile{}".format(ext)
    h2, s2 = _imagelist_icon(fake, FILE_ATTRIBUTE_NORMAL, use_attrs=True)
    _dbg("    imagelist (fake) result: h={} s={}".format(h2, s2))

    if h1 and h2:
        if s1 >= s2:
            win32gui.DestroyIcon(h2)
            return h1, s1
        win32gui.DestroyIcon(h1)
        return h2, s2
    if h1:
        return h1, s1
    if h2:
        return h2, s2

    hicon = _shgetfileinfo_icon(fake, FILE_ATTRIBUTE_NORMAL, use_attrs=True)
    _dbg("    shgetfileinfo fallback: h={}".format(hicon))
    return (hicon, 32) if hicon else (0, 0)


def _registry_icon(ext):
    import winreg

    def rget(subkey, value_name=""):
        try:
            with winreg.OpenKey(winreg.HKEY_CLASSES_ROOT, subkey) as k:
                if value_name:
                    val, _ = winreg.QueryValueEx(k, value_name)
                    return val
                return winreg.QueryValue(k, "")
        except OSError:
            return None

    def is_uwp(s):
        return bool(s and (s.startswith("@") or "ms-resource://" in s))

    def icon_str_for_progid(prog_id):
        s = rget(r"{}\DefaultIcon".format(prog_id))
        if is_uwp(s):
            s = None
        if not s:
            cv = rget(r"{}\CurVer".format(prog_id))
            if cv:
                s2 = rget(r"{}\DefaultIcon".format(cv))
                if not is_uwp(s2):
                    s = s2
        return s

    def exe_from_command(cmd):
        if not cmd:
            return None
        cmd = cmd.strip()
        if cmd.startswith('"'):
            end = cmd.find('"', 1)
            exe = os.path.expandvars(cmd[1:end]) if end > 1 else ""
        else:
            exe = os.path.expandvars(cmd.split()[0])
        return exe if exe and os.path.isfile(exe) else None

    prog_id  = rget(ext)
    _dbg("    registry: ext={} progid={}".format(ext, prog_id))
    icon_str = icon_str_for_progid(prog_id) if prog_id else None
    _dbg("    registry: DefaultIcon={}".format(icon_str))

    if not icon_str:
        try:
            with winreg.OpenKey(winreg.HKEY_CLASSES_ROOT,
                                r"{}\OpenWithProgids".format(ext)) as k:
                i = 0
                while True:
                    try:
                        name, _, _ = winreg.EnumValue(k, i)
                        if name:
                            s = icon_str_for_progid(name)
                            _dbg("    registry: OpenWithProgid {} -> {}".format(name, s))
                            if s and not is_uwp(s):
                                icon_str = s
                                break
                        i += 1
                    except OSError:
                        break
        except OSError:
            pass

    if not icon_str:
        cmd = rget(r"{}\shell\open\command".format(prog_id)) if prog_id else None
        if not cmd:
            try:
                with winreg.OpenKey(winreg.HKEY_CLASSES_ROOT,
                                    r"{}\OpenWithProgids".format(ext)) as k:
                    i = 0
                    while True:
                        try:
                            name, _, _ = winreg.EnumValue(k, i)
                            if name:
                                c = rget(r"{}\shell\open\command".format(name))
                                if c:
                                    cmd = c
                                    break
                            i += 1
                        except OSError:
                            break
            except OSError:
                pass
        exe = exe_from_command(cmd)
        _dbg("    registry: open cmd exe={}".format(exe))
        if exe:
            icon_str = exe + ",0"

    if not icon_str or is_uwp(icon_str):
        _dbg("    registry: no usable icon_str found")
        return 0, 0

    icon_str = os.path.expandvars(icon_str.strip().strip('"'))
    _dbg("    registry: resolved icon_str={}".format(icon_str))

    src, idx = (_split_icon_loc(icon_str) if "," in icon_str
                else (os.path.expandvars(icon_str), 0))
    src = os.path.expandvars(src)
    _dbg("    registry: src={} idx={}".format(src, idx))

    if not os.path.isfile(src):
        _dbg("    registry: source file NOT FOUND: {}".format(src))
        return 0, 0

    h, s = _private_extract(src, idx)
    _dbg("    registry: PrivateExtract h={} s={}".format(h, s))
    if h:
        return h, s

    h, s = _imagelist_icon(src, FILE_ATTRIBUTE_NORMAL)
    _dbg("    registry: imagelist h={} s={}".format(h, s))
    return (h, s) if h else (0, 0)


# ── Shell image list ──────────────────────────────────────────────────────────

def _get_comctl32():
    global _comctl32
    if _comctl32 is None:
        _comctl32 = ctypes.windll.comctl32
        _comctl32.ImageList_GetIcon.restype  = ctypes.c_size_t
        _comctl32.ImageList_GetIcon.argtypes = [
            ctypes.c_void_p,
            ctypes.c_int,
            ctypes.c_uint,
        ]
    return _comctl32


def _imagelist_icon(path, file_attributes, use_attrs=False):
    try:
        shfi  = SHFILEINFO()
        flags = SHGFI_SYSICONINDEX | SHGFI_LARGEICON
        if use_attrs:
            flags |= SHGFI_USEFILEATTRIBUTES

        himl = ctypes.windll.shell32.SHGetFileInfoW(
            path, file_attributes, ctypes.byref(shfi),
            ctypes.sizeof(shfi), flags,
        )
        _dbg("    _imagelist_icon {!r}: himl={} iIcon={}".format(path, himl, shfi.iIcon))
        if not himl:
            return 0, 0

        icon_index = shfi.iIcon
        comctl32   = _get_comctl32()

        for shil, nominal_px in [(SHIL_JUMBO, 256), (SHIL_EXTRALARGE, 48), (SHIL_LARGE, 32)]:
            jumbo_himl = ctypes.c_void_p()
            hr = ctypes.windll.shell32.SHGetImageList(
                shil, ctypes.byref(_IID_IImageList), ctypes.byref(jumbo_himl),
            )
            _dbg("    SHGetImageList({}px) hr={} himl={}".format(
                nominal_px, hr, jumbo_himl.value))
            if hr == 0 and jumbo_himl.value:
                hicon = comctl32.ImageList_GetIcon(jumbo_himl.value, icon_index, 0x1)
                _dbg("    ImageList_GetIcon({}px) -> {}".format(nominal_px, hicon))
                if hicon:
                    _dbg("    returning nominal size {}px".format(nominal_px))
                    return hicon, nominal_px

        hicon = comctl32.ImageList_GetIcon(himl, icon_index, 0x1)
        _dbg("    ImageList_GetIcon(shfi himl) -> {}".format(hicon))
        if hicon:
            return hicon, 32

    except Exception as e:
        _dbg("    _imagelist_icon exception:", e)
    return 0, 0


# ── PrivateExtractIcons ───────────────────────────────────────────────────────

def _private_extract(path, index):
    for size in [256, 128, 64, 48, 32]:
        hicon  = ctypes.wintypes.HANDLE(0)
        hidx   = ctypes.wintypes.UINT(0)
        count  = ctypes.windll.user32.PrivateExtractIconsW(
            path, index, size, size,
            ctypes.byref(hicon), ctypes.byref(hidx), 1, 0,
        )
        if count > 0 and hicon.value:
            actual = _icon_size(int(hicon.value))
            _dbg("    PrivateExtract({}, idx={}) -> actual={}px".format(size, index, actual))
            return int(hicon.value), actual
    return 0, 0


def _icon_size(hicon):
    try:
        info = win32gui.GetIconInfo(hicon)
        hbm  = info[4] or info[3]
        if hbm:
            return win32ui.CreateBitmapFromHandle(hbm).GetInfo()["bmWidth"]
    except Exception:
        pass
    return 32


# ── SHGetFileInfo direct icon (32px fallback) ─────────────────────────────────

def _shgetfileinfo_icon(path, file_attributes, use_attrs=False):
    shfi  = SHFILEINFO()
    flags = SHGFI_ICON | SHGFI_LARGEICON
    if use_attrs:
        flags |= SHGFI_USEFILEATTRIBUTES
    ret = ctypes.windll.shell32.SHGetFileInfoW(
        path, file_attributes, ctypes.byref(shfi), ctypes.sizeof(shfi), flags,
    )
    return shfi.hIcon if (ret and shfi.hIcon) else 0


# ── HICON -> PIL Image ────────────────────────────────────────────────────────

def _hicon_to_pil(hicon, size):
    # Set argtypes so ctypes treats the HICON as a 64-bit void pointer on
    # 64-bit Windows — without this, large handle values overflow c_int.
    _GetIconInfo = ctypes.windll.user32.GetIconInfo
    _GetIconInfo.argtypes = [ctypes.c_void_p, ctypes.POINTER(_ICONINFO)]
    _GetIconInfo.restype  = ctypes.wintypes.BOOL
    if not hicon or not _GetIconInfo(hicon, ctypes.byref(_ICONINFO())):
        raise RuntimeError("Invalid icon handle: {}".format(hicon))

    draw_size = 256
    _dbg("  _hicon_to_pil: nominal={} draw={}".format(size, draw_size))

    hdc_s   = win32gui.GetDC(0)
    hdc     = win32ui.CreateDCFromHandle(hdc_s)
    hdc_mem = hdc.CreateCompatibleDC()
    bmp     = win32ui.CreateBitmap()
    bmp.CreateCompatibleBitmap(hdc, draw_size, draw_size)
    hdc_mem.SelectObject(bmp)
    hdc_mem.FillSolidRect((0, 0, draw_size, draw_size), 0x00000000)
    win32gui.DrawIconEx(
        hdc_mem.GetSafeHdc(), 0, 0, hicon, draw_size, draw_size, 0, None, win32con.DI_NORMAL,
    )
    raw = bmp.GetBitmapBits(True)
    img = Image.frombuffer("RGBA", (draw_size, draw_size), raw, "raw", "BGRA", 0, 1).copy()
    hdc_mem.DeleteDC()
    hdc.DeleteDC()
    win32gui.ReleaseDC(0, hdc_s)
    win32gui.DeleteObject(bmp.GetHandle())

    import numpy as np
    arr = np.frombuffer(raw, dtype=np.uint8).reshape(draw_size, draw_size, 4)
    rgb_max = arr[:, :, :3].max(axis=2)
    rows_with_content = np.any(rgb_max > 8, axis=1)
    cols_with_content = np.any(rgb_max > 8, axis=0)
    if rows_with_content.any():
        top    = int(np.argmax(rows_with_content))
        bottom = int(len(rows_with_content) - np.argmax(rows_with_content[::-1]))
        left   = int(np.argmax(cols_with_content))
        right  = int(len(cols_with_content) - np.argmax(cols_with_content[::-1]))
        content_w = right - left
        content_h = bottom - top
        _dbg("  _hicon_to_pil: content box=({},{},{},{}) size={}x{}".format(
            left, top, right, bottom, content_w, content_h))
        if content_w <= 56 and content_h <= 56 and left <= 8 and top <= 8:
            sq = max(content_w, content_h)
            cx = (left + right) // 2
            cy = (top + bottom) // 2
            half      = (sq + 1) // 2
            sq_left   = max(0, cx - half)
            sq_top    = max(0, cy - half)
            sq_right  = min(draw_size, sq_left + sq)
            sq_bottom = min(draw_size, sq_top  + sq)
            _dbg("  _hicon_to_pil: upscaling {}x{} stamp -> 256x256".format(
                content_w, content_h))
            img = img.crop((sq_left, sq_top, sq_right, sq_bottom)).resize(
                (256, 256), Image.NEAREST)
    else:
        _dbg("  _hicon_to_pil: no content detected (blank icon)")

    return img




def _path_cost(path):
    if not path or path == "<folder>":
        return _COST["icon"]
    if os.path.isdir(path):
        return _COST["icon"]
    ext = os.path.splitext(path)[1].lower()
    if ext in PIL_EXTENSIONS or ext == ".ico":
        return _COST["image"]
    if ext in {".mp4", ".mkv", ".mov", ".avi", ".wmv", ".flv", ".webm",
               ".m4v", ".mpg", ".mpeg", ".3gp", ".ts", ".mts", ".m2ts"}:
        return _COST["video"]
    if ext in {".pdf", ".svg", ".hdr", ".exr"}:
        return _COST["render"]
    return _COST["icon"]


def get_folder_icons(folder_path, preview=True, debug=False,
                     recursive=False, output_dir=None,
                     return_info=False):
    """
    Extract icons/thumbnails for every item directly inside *folder_path*.
    Items are processed cheapest-first.

    Parameters
    ----------
    folder_path : str
    preview     : bool
    debug       : bool
    recursive   : bool
        Subdirectories are included as folder icons (not expanded).
    output_dir  : str or None
        If given and *return_info* is False, PNGs are saved here.
        Ignored when *return_info* is True.
    return_info : bool
        False (default): values in the returned dict are PIL Images.
            If *output_dir* is also given, images are saved as PNGs and
            the dict is empty (original behaviour).
        True: values are info dicts (see _ICON_INFO_FIELDS).
            *output_dir* is ignored — no files are written.

    Returns
    -------
    dict
        return_info=False, no output_dir : {path: PIL.Image.Image}
        return_info=False, output_dir    : {}  (files saved, dict empty)
        return_info=True                 : {path: info_dict}
    """
    global _DEBUG
    _DEBUG = debug
    _ensure_com()

    if not os.path.isdir(folder_path):
        raise ValueError("Not a directory: {!r}".format(folder_path))

    entries = sorted(os.listdir(folder_path), key=lambda n: _path_cost(
        os.path.join(folder_path, n)))
    entries = [os.path.join(folder_path, n) for n in entries]

    results = {}
    for path in entries:
        try:
            hicon, size, is_pil = _resolve(path, preview)
            try:
                img = hicon if is_pil else _hicon_to_pil(hicon, size)
                if not is_pil:
                    win32gui.DestroyIcon(hicon)
            except Exception:
                if not is_pil:
                    try:
                        win32gui.DestroyIcon(hicon)
                    except Exception:
                        pass
                raise

            if return_info:
                results[path] = _build_info_dict(path, img, is_pil)
            elif output_dir:
                os.makedirs(output_dir, exist_ok=True)
                out = os.path.join(output_dir, os.path.basename(path) + ".png")
                img.save(out, "PNG")
            else:
                results[path] = img

        except Exception as e:
            _dbg("get_folder_icons: SKIP {!r}: {}".format(path, e))

    return results


def sort_by_cost(paths):
    """
    Return *paths* sorted from least-intensive to most-intensive extraction.
    """
    return sorted(paths, key=_path_cost)


class IconQueue:
    r"""
    A priority queue of icon extraction jobs.

    Items are sorted cheapest-first so that fast shell-icon lookups always
    run before expensive PDF/SVG/video renders, regardless of insertion order.
    Higher *priority* values within the same cost tier are processed first.

    Usage
    -----
    q = IconQueue()
    q.add(r"C:\folder\file.py")
    q.add(r"C:\folder\movie.mp4")         # processed after .py
    q.add(r"C:\folder\logo.svg")          # most expensive, last
    q.add(r"C:\folder\urgent.ini", priority=10)

    # Yields (path, PIL Image):
    for path, img in q.process(preview=True):
        print(path, img.size)

    # Yields (path, info dict):
    for path, info in q.process(preview=True, return_info=True):
        print(info["name"], info["size"], info["date_modified"])
        info["image"].show()
    """

    def __init__(self):
        self._items   = []
        self._counter = 0

    def add(self, path, priority=0):
        """
        Add *path* to the queue.

        Parameters
        ----------
        path     : str   file, folder, or extension string
        priority : int   higher values run first within the same cost tier
        """
        import heapq
        cost = _path_cost(path)
        heapq.heappush(self._items, (cost, -priority, self._counter, path))
        self._counter += 1

    def add_many(self, paths, priority=0):
        """Add multiple paths with the same priority."""
        for p in paths:
            self.add(p, priority=priority)

    def peek_order(self):
        """
        Return the planned processing order as a list of (path, cost, priority)
        without consuming any items.
        """
        return [(item[3], item[0], -item[1]) for item in sorted(self._items)]

    def __len__(self):
        return len(self._items)

    def process(self, preview=True, debug=False, return_info=False):
        """
        Process all queued items cheapest/highest-priority first.

        Parameters
        ----------
        preview     : bool
        debug       : bool
        return_info : bool
            False (default): yields (path, PIL.Image.Image)
            True:            yields (path, info_dict)
                             info_dict contains all filesystem metadata plus
                             the PIL image under the 'image' key.

        Yields
        ------
        (str, PIL.Image.Image)   if return_info=False
        (str, dict)              if return_info=True

        The queue is empty after this call.
        """
        import heapq
        _ensure_com()
        while self._items:
            cost, neg_pri, _order, path = heapq.heappop(self._items)
            try:
                hicon, size, is_pil = _resolve(path, preview)
                try:
                    img = hicon if is_pil else _hicon_to_pil(hicon, size)
                    if not is_pil:
                        win32gui.DestroyIcon(hicon)
                except Exception:
                    if not is_pil:
                        try:
                            win32gui.DestroyIcon(hicon)
                        except Exception:
                            pass
                    raise

                if return_info:
                    yield path, _build_info_dict(path, img, is_pil)
                else:
                    yield path, img

            except Exception as e:
                _dbg("IconQueue.process: SKIP {!r}: {}".format(path, e))

    def process_to_dir(self, output_dir, preview=True, debug=False,
                       return_info=False):
        """
        Process all queued items and save PNGs to *output_dir*.

        Parameters
        ----------
        output_dir  : str
        preview     : bool
        debug       : bool
        return_info : bool
            False (default): saves PNGs, returns list[str] of saved paths.
            True:            saves PNGs AND returns {path: info_dict}.
                             The info dict includes the PIL image in 'image'.

        Returns
        -------
        list[str]               if return_info=False
        dict {str: info_dict}   if return_info=True
        """
        os.makedirs(output_dir, exist_ok=True)
        saved   = []
        infos   = {}
        for path, result in self.process(preview=preview, debug=debug,
                                         return_info=return_info):
            if return_info:
                img  = result["image"]
                info = result
            else:
                img  = result

            name = os.path.basename(path) or path.strip(".\\/") or "icon"
            out  = os.path.join(output_dir, name + ".png")
            img.save(out, "PNG")
            saved.append(out)
            if return_info:
                infos[path] = info

        return infos if return_info else saved


# ── __main__ demo ─────────────────────────────────────────────────────────────
#
# if __name__ == "__main__":
#     tests = [
#         (r"C:\Users\nicho\Documents\Unreal Projects\Starcel9\Content\CLITools\Everything-1.4.1.1030.x64", "Everything-1.4.1.1030.x64.png"),
#         (r"C:\Users\nicho\Downloads\Library\weapons\firearms\manuals\thompson_tommy_full_auto_1927.pdf", "thompson_tommy_full_auto_1927.png"),
#         (r"C:\Users\nicho\Documents\Unreal Projects\Starcel9\Content\Movies\psychedelic.mp4", "psychedelic.png"),
#         (r"C:\Users\nicho\Downloads", "Downloads.png"),
#         (r"C:\Windows\system32\notepad.exe", "notepad.png"),
#         (r"C:\Users\nicho\Documents\Unreal Projects\Starcel9\Content\Scripts\input_devices.py", "input_devices.png"),
#         (r"C:\Users\nicho\Documents\Unreal Projects\Starcel9\Content\Scripts\cli.pyi", "cli.png"),
#         (r"C:\Users\nicho\Documents\Unreal Projects\Starcel9\Starcel9.sln", "Starcel9.png"),
#         (r"C:\Users\nicho\Documents\Unreal Projects\Starcel9\README.md", "README.png"),
#         (r"C:\Users\nicho\Documents\Unreal Projects\Starcel9\Images\duck.png", "duck.png"),
#         (r"C:\Users\nicho\Documents\Unreal Projects\Starcel9\Images\duck.hdr", "duck_hdr.png"),
#         (r"C:\Users\nicho\Documents\Unreal Projects\Starcel9\Images\StarcelUE5-old\favicon.ico", "favicon.png"),
#         (r"C:\Users\nicho\Documents\Unreal Projects\Starcel9\Images\StarcelUE5-old\pbr.gif", "pbr.png"),
#         (r"C:\Users\nicho\Documents\Unreal Projects\Starcel9\Images\branding\logo.svg", "logo.png"),
#         (r"C:\Users\nicho\Documents\Unreal Projects\Starcel9\Content\CLITools\Everything-1.4.1.1030.x64\everything.exe", "everything.png"),
#         (r"C:\Users\nicho\Documents\Unreal Projects\Starcel9\Content\CLITools\Everything-1.4.1.1030.x64\everything-startup.vbs", "everything-startup.png"),
#         (r"C:\Users\nicho\Documents\Unreal Projects\Starcel9\Content\CLITools\Everything-1.4.1.1030.x64\Everything.lng", "Everything_lng.png"),
#         (r"C:\Users\nicho\Documents\Unreal Projects\Starcel9\Content\CLITools\Everything-1.4.1.1030.x64\Everything.ini", "Everything_ini.png"),
#         (r"C:\ProgramData\Microsoft\Windows\Start Menu\Programs\everything.lnk", "everything_lnk.png"),
#         (r"C:\ProgramData\Microsoft\Windows\Start Menu\Programs\WSL.lnk", "WSL.png"),
#         (r"C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Visual Studio Installer.lnk", "Visual_Studio_Installer.png"),
#         (r"C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Immersive Control Panel.lnk", "Immersive_Control_Panel.png"),
#         (r"C:\Users\nicho\Downloads\projectMSDL-Windows-x64-2.0-pre3\projectMSDL\textures\sunrise.jpg", "sunrise.png"),
#         (r"C:\Users\nicho\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup\everything-startup.lnk", "branding.png"),
#     ]
#
#     # ── Original save-to-disk mode (unchanged) ────────────────────────────────
#     for path, out in tests:
#         try:
#             extract_icon(path, out, debug=False)
#             print("OK (save):", out)
#         except Exception as e:
#             print("FAIL:", out, "->", e)
#
#     print()
#
#     # ── Dict-return mode via get_icon_info() ──────────────────────────────────
#     path = r"C:\Users\nicho\Downloads\Library\weapons\firearms\manuals\thompson_tommy_full_auto_1927.pdf"
#     info = get_icon_info(path, preview=True)
#     print("get_icon_info():")
#     for k, v in info.items():
#         if k == "image":
#             print(f"  image       : {v.size} {v.mode}")
#         else:
#             print(f"  {k:<15}: {v}")
#
#     print()
#
#     # ── Dict-return mode via extract_icon(output_path=None) ───────────────────
#     info2 = extract_icon(path, preview=True)
#     assert info2["full_path"] == path
#     print("extract_icon(no output_path) -> dict, keys:", list(info2))
#
#     print()
#
#     # ── Dict-return mode via extract_icon(output_path=..., return_info=True) ──
#     info3 = extract_icon(path, "thompson_preview.png", return_info=True)
#     print("extract_icon(output_path, return_info=True) -> saved + dict")
#     print("  size:", info3["size"])
#
#     print()
#
#     # ── IconQueue.process(return_info=True) ───────────────────────────────────
#     q = IconQueue()
#     q.add_many([p for p, _ in tests[:4]])
#     print("Queue process(return_info=True):")
#     for path, info in q.process(preview=True, return_info=True):
#         img = info["image"]
#         print(f"  {info['name']:<40}  {info['size'] or 'dir':<12}  "
#               f"{'preview' if info['is_preview'] else 'icon':<8}  "
#               f"{img.size}")
#
#     print()
#
#     # ── IconQueue.process_to_dir(return_info=True) ────────────────────────────
#     q2 = IconQueue()
#     q2.add_many([p for p, _ in tests[:4]])
#     infos = q2.process_to_dir("icons_out", return_info=True)
#     print("process_to_dir(return_info=True) -> saved + dict, count:", len(infos))
#     for path, info in infos.items():
#         print(f"  {info['name']}  modified={info['date_modified']}")
#
#     print()
#
#     # ── get_folder_icons(return_info=True) ────────────────────────────────────
#     folder = r"C:\Users\nicho\Documents\Unreal Projects\Starcel9\Content\CLITools\Everything-1.4.1.1030.x64"
#     folder_infos = get_folder_icons(folder, preview=False, return_info=True)
#     print("get_folder_icons(return_info=True), count:", len(folder_infos))
#     for path, info in folder_infos.items():
#         print(f"  {info['name']:<40}  {info['extension']:<8}  "
#               f"{info['size'] or 'dir':<12}  {info['cost_tier']}")


# extract_icon(r"C:\Users\nicho\Documents\Unreal Projects\Starcel9\Content\Movies\psychedelic.mp4", preview=True, return_info=True)["image"].show()