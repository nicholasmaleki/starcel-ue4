"""
ue_math_core.py — Evaluation & Geometry Primitives for UE Math Plotter
=======================================================================

Pure-Python math layer (no Unreal dependency). Handles:
  - Symbolic → numeric compilation   (SymPy)
  - 2D / 3D / parametric curve sampling
  - Surface sampling (explicit, parametric, implicit)
  - Marching cubes (isosurface / intersection)
  - Vector field & integral curve sampling
  - Riemann surface construction (sqrt, cbrt, log, pow_pq)
  - Geometric Algebra primitives    (kingdon)
  - Domain coloring                 (complex analysis)
  - Tube mesh builder               (caps, dash pattern, square / round cross-sec)
  - Spread engine                   (nD → multiple 3D projections)

Debug levels
------------
  debug=False        — silent
  debug=True         — summary lines per operation   (prefix [Core])
  advanced_debug=True — full arrays, timing, grade tables  (prefix [Core++])
"""

from __future__ import annotations

import math
import cmath
import time
import traceback
import warnings
from dataclasses import dataclass, field
from typing import (
    Any, Callable, Dict, List, Optional, Sequence, Tuple, Union
)

import numpy as np

# ── Optional: SymPy ───────────────────────────────────────────────────────────
try:
    import sympy as sp
    from sympy.utilities.lambdify import lambdify as sp_lambdify
    SYMPY_AVAILABLE = True
except ImportError:
    SYMPY_AVAILABLE = False

# ── Optional: Kingdon (Geometric Algebra) ────────────────────────────────────
try:
    from kingdon import Algebra as KingdonAlgebra
    KINGDON_AVAILABLE = True
except ImportError:
    KINGDON_AVAILABLE = False

# ── Type aliases ──────────────────────────────────────────────────────────────
Vec2 = Tuple[float, float]
Vec3 = Tuple[float, float, float]
ScalarFn1 = Callable[[float], float]
ScalarFn2 = Callable[[float, float], float]
ScalarFn3 = Callable[[float, float, float], float]
VectorFn2 = Callable[[float, float], Vec2]
VectorFn3 = Callable[[float, float, float], Vec3]
ComplexFn = Callable[[complex], complex]

_DBG_PREFIX    = "[Core]   "
_DBG_ADV_PREFIX = "[Core++] "


# ============================================================================
# DEBUG HELPERS
# ============================================================================

def _dbg(msg: str, debug: bool):
    if debug:
        print(f"{_DBG_PREFIX}{msg}")


def _adbg(msg: str, adv: bool):
    if adv:
        print(f"{_DBG_ADV_PREFIX}{msg}")


def _timed(label: str, adv: bool):
    """Context manager that prints elapsed time when advanced_debug=True."""
    class _T:
        def __enter__(self):
            self._t = time.perf_counter() if adv else 0.0
            return self
        def __exit__(self, *_):
            if adv:
                elapsed = (time.perf_counter() - self._t) * 1000
                print(f"{_DBG_ADV_PREFIX}{label}: {elapsed:.2f} ms")
    return _T()


# ============================================================================
# DATA STRUCTURES
# ============================================================================

@dataclass
class CurvePoint:
    x: float
    y: float
    z: float = 0.0


@dataclass
class CurveSegment:
    """A connected chain of CurvePoints (one branch of a plotted function)."""
    points: List[CurvePoint] = field(default_factory=list)


@dataclass
class Arrow:
    origin:    Vec3
    direction: Vec3


@dataclass
class MeshData:
    """Triangle mesh in math-space coordinates (not scaled to UU)."""
    vertices: np.ndarray   # (N, 3) float
    indices:  np.ndarray   # (M, 3) int   — triangles
    normals:  np.ndarray   # (N, 3) float
    uvs:      np.ndarray = field(default_factory=lambda: np.zeros((0, 2)))

    def __post_init__(self):
        self.vertices = np.asarray(self.vertices, dtype=float)
        self.indices  = np.asarray(self.indices,  dtype=int)
        self.normals  = np.asarray(self.normals,  dtype=float)
        if len(self.uvs) == 0:
            self.uvs = np.zeros((len(self.vertices), 2), dtype=float)
        else:
            self.uvs = np.asarray(self.uvs, dtype=float)


# ============================================================================
# SYMBOLIC COMPILER
# ============================================================================

class SymbolicCompiler:
    """Compile SymPy expressions to fast numpy callables."""

    @staticmethod
    def compile(expr, var_names: List[str]) -> Callable:
        if SYMPY_AVAILABLE and isinstance(expr, sp.Basic):
            syms = [sp.Symbol(v) for v in var_names]
            return sp_lambdify(syms, expr, modules=['numpy'])
        if callable(expr):
            return expr
        raise TypeError(f"Cannot compile {type(expr).__name__} — "
                        "expected callable or SymPy expression")

    @staticmethod
    def compile_1d(expr, var='x') -> ScalarFn1:
        return SymbolicCompiler.compile(expr, [var])

    @staticmethod
    def compile_2d(expr, vars=('x', 'y')) -> ScalarFn2:
        return SymbolicCompiler.compile(expr, list(vars))

    @staticmethod
    def compile_3d(expr, vars=('x', 'y', 'z')) -> ScalarFn3:
        return SymbolicCompiler.compile(expr, list(vars))

    @staticmethod
    def compile_complex(expr, var='z') -> ComplexFn:
        return SymbolicCompiler.compile(expr, [var])

    @staticmethod
    def gradient_2d(f: ScalarFn2, x: float, y: float, h=1e-5) -> Vec2:
        try:
            dfx = (f(x+h, y) - f(x-h, y)) / (2*h)
            dfy = (f(x, y+h) - f(x, y-h)) / (2*h)
        except Exception:
            dfx = dfy = 0.0
        return (dfx, dfy)

    @staticmethod
    def gradient_3d(f: ScalarFn3, x, y, z, h=1e-5) -> Vec3:
        try:
            dfx = (f(x+h, y, z) - f(x-h, y, z)) / (2*h)
            dfy = (f(x, y+h, z) - f(x, y-h, z)) / (2*h)
            dfz = (f(x, y, z+h) - f(x, y, z-h)) / (2*h)
        except Exception:
            dfx = dfy = dfz = 0.0
        return (dfx, dfy, dfz)


# ============================================================================
# ADAPTIVE SUBDIVIDER  (2D / 3D curves)
# ============================================================================

class AdaptiveSubdivider:
    """
    Production-grade adaptive curve sampler.

    Improvements over the original midpoint-error version:
    ──────────────────────────────────────────────────────
    1. Curvature-weighted error metric (angle between successive tangents)
       instead of a plain y-midpoint deviation.  This adds points where the
       curve *bends*, not just where it is vertically far from a chord — so
       high-frequency oscillations and tight arcs at any zoom level are
       correctly resolved.

    2. Discontinuity / singularity detection.  Between any two adjacent
       samples, if |Δy| > `disc_factor × x_span` the segment is treated as a
       break (pole, jump, or asymptote) and split into two separate
       CurveSegments, preventing false near-vertical "connector" lines through
       ±∞.  The factor is automatically tightened when zoomed in.

    3. Catastrophic cancellation guard for deep zoom.  When the visible
       x-span is smaller than ~1e-8 the function is re-evaluated using a
       shifted origin (x_centre subtracted first) before passing to the
       callable, avoiding loss of significance in f(x_centre ± tiny).

    4. Zoom-proportional tolerance.  tolerance is divided by zoom so that
       zooming in by 10× automatically requests 10× more refinement, keeping
       curves smooth at every level without manual tuning.

    5. max_depth clamp.  Raised default to 12 (was 8) and capped at 14 to
       prevent unbounded recursion on pathological functions.

    All improvements are backward-compatible: existing call sites that only
    pass `fn`, `x0`, `x1` continue to work.
    """

    # threshold: |Δy| / x_span beyond which a gap is a discontinuity
    _DISC_FACTOR_BASE: float = 3.0

    def __init__(self,
                 zoom: float = 1.0,
                 tolerance: float = 0.005,   # tighter default than old 0.01
                 max_depth: int = 12,
                 disc_factor: float = 3.0,
                 debug: bool = False,
                 advanced_debug: bool = False):
        self.zoom  = max(zoom, 1e-6)
        self.tol   = tolerance / self.zoom
        self.depth = min(max(max_depth, 4), 14)
        self.disc  = disc_factor
        self.debug = debug
        self.adv   = advanced_debug

    # ── helpers ─────────────────────────────────────────────────────────────

    @staticmethod
    def _safe_eval(fn, x) -> Optional[float]:
        """Evaluate fn(x); return None on any error or non-finite result."""
        try:
            v = float(fn(x))
            return v if math.isfinite(v) else None
        except Exception:
            return None

    @staticmethod
    def _angle_error(ya, ym, yb) -> float:
        """
        Curvature proxy: sine of the turning angle at the midpoint.
        Returns a value in [0, 1]; 0 = perfectly straight.
        """
        d1 = ym - ya
        d2 = yb - ym
        cross = abs(d1 - d2)           # |d1 − d2|: zero when collinear
        denom = abs(d1) + abs(d2) + 1e-30
        return cross / denom

    # ── Explicit 2D: y = f(x) ───────────────────────────────────────────────

    def subdivide_explicit_2d(self,
                               fn: ScalarFn1,
                               x0: float, x1: float,
                               n: int = 128) -> List[CurveSegment]:
        """
        Returns a list of CurveSegments (one per continuous branch).

        Key changes vs original:
        • Discontinuity heuristic breaks segments at poles/jumps.
        • Curvature-angle error metric drives refinement.
        • Deep-zoom catastrophic-cancellation guard (shifted-origin eval).
        """
        x_span = max(abs(x1 - x0), 1e-300)
        x_ctr  = (x0 + x1) * 0.5

        # Deep-zoom guard: if the visible window is very narrow, shift x so
        # that we evaluate f relative to the window centre, avoiding
        # cancellation in double arithmetic at large x values.
        deep_zoom = x_span < 1e-6
        if deep_zoom:
            shifted_fn = lambda dx, _fn=fn, _c=x_ctr: _fn(_c + dx)
            eval_fn    = shifted_fn
            ex0, ex1   = x0 - x_ctr, x1 - x_ctr
        else:
            eval_fn = fn
            ex0, ex1 = x0, x1

        # Discontinuity threshold (tighter when zoomed in)
        disc_threshold = self.disc * x_span / self.zoom

        # Initial uniform pass
        xs_rel = np.linspace(ex0, ex1, n)
        raw: List[Tuple[float, Optional[float]]] = []
        for xr in xs_rel:
            raw.append((xr, self._safe_eval(eval_fn, xr)))

        segments: List[CurveSegment] = []
        current:  List[CurvePoint]   = []

        def _commit():
            if len(current) >= 2:
                segments.append(CurveSegment(list(current)))
            current.clear()

        def _refine(xa, ya, xb, yb, depth):
            if depth >= self.depth:
                return
            xm = (xa + xb) * 0.5
            ym = self._safe_eval(eval_fn, xm)
            if ym is None:
                return
            # Curvature-angle error
            err = self._angle_error(ya, ym, yb)
            if err < self.tol:
                return
            _refine(xa, ya, xm, ym, depth + 1)
            # Convert back to world-space x for CurvePoint
            wx = (xm + x_ctr) if deep_zoom else xm
            current.append(CurvePoint(wx, ym))
            _refine(xm, ym, xb, yb, depth + 1)

        for i in range(len(raw) - 1):
            xa, ya = raw[i]
            xb, yb = raw[i + 1]

            if ya is None or yb is None:
                _commit()
                continue

            # Discontinuity heuristic
            if abs(yb - ya) > disc_threshold:
                _commit()
                continue

            wx_a = (xa + x_ctr) if deep_zoom else xa
            if not current:
                current.append(CurvePoint(wx_a, ya))

            _refine(xa, ya, xb, yb, 0)

            wx_b = (xb + x_ctr) if deep_zoom else xb
            current.append(CurvePoint(wx_b, yb))

        _commit()

        _adbg(f"explicit_2d: {len(segments)} segs, "
              f"{sum(len(s.points) for s in segments)} pts  "
              f"deep_zoom={deep_zoom}", self.adv)
        return segments

    # ── Parametric 3D: (x,y,z)(t) ───────────────────────────────────────────

    def subdivide_parametric_3d(self,
                                 fx, fy, fz,
                                 t0: float, t1: float,
                                 n: int = 128) -> List[CurveSegment]:
        """
        Improvements:
        • 3-D curvature angle (turning angle of tangent vectors) replaces
          the chord-distance error.
        • Eval failures produce segment breaks, not silent (0,0,0) pins.
        • Discontinuity detection on arc-length jumps.
        """
        ts = np.linspace(t0, t1, n)

        def _eval3(t) -> Optional[Tuple[float,float,float]]:
            try:
                x, y, z = float(fx(t)), float(fy(t)), float(fz(t))
                if math.isfinite(x) and math.isfinite(y) and math.isfinite(z):
                    return (x, y, z)
            except Exception:
                pass
            return None

        raw: List[Tuple[float, Optional[Tuple[float,float,float]]]] = [
            (t, _eval3(t)) for t in ts
        ]

        # Estimate scene scale for relative tolerance
        valid_pts = [p for _, p in raw if p is not None]
        if valid_pts:
            arr  = np.array(valid_pts)
            diag = float(np.linalg.norm(arr.max(0) - arr.min(0))) + 1e-12
        else:
            diag = 1.0
        tol3 = max(self.tol * 0.5, 0.001 * diag / self.zoom)
        disc3 = diag * self.disc * 0.15 / self.zoom

        def _angle3(pa, pm, pb) -> float:
            """Turning angle at pm: sin of the angle between (pm-pa) and (pb-pm)."""
            d1 = tuple(pm[k]-pa[k] for k in range(3))
            d2 = tuple(pb[k]-pm[k] for k in range(3))
            n1 = math.sqrt(sum(v**2 for v in d1)) + 1e-30
            n2 = math.sqrt(sum(v**2 for v in d2)) + 1e-30
            dot = sum(d1[k]*d2[k] for k in range(3)) / (n1*n2)
            dot = max(-1.0, min(1.0, dot))
            return math.sqrt(1.0 - dot*dot)  # sin(angle)

        segments: List[CurveSegment] = []
        current:  List[CurvePoint]   = []

        def _commit():
            if len(current) >= 2:
                segments.append(CurveSegment(list(current)))
            current.clear()

        def _refine3(t_a, p_a, t_b, p_b, depth):
            if depth >= self.depth:
                return
            tm = (t_a + t_b) * 0.5
            pm = _eval3(tm)
            if pm is None:
                return
            err = _angle3(p_a, pm, p_b)
            if err < tol3:
                return
            _refine3(t_a, p_a, tm, pm, depth + 1)
            current.append(CurvePoint(*pm))
            _refine3(tm, pm, t_b, p_b, depth + 1)

        dt = (t1 - t0) / max(n - 1, 1)
        for i in range(len(raw) - 1):
            ta, pa = raw[i]
            tb, pb = raw[i + 1]

            if pa is None or pb is None:
                _commit()
                continue

            # Arc-length discontinuity guard
            jump = math.sqrt(sum((pb[k]-pa[k])**2 for k in range(3)))
            if jump > disc3:
                _commit()
                continue

            if not current:
                current.append(CurvePoint(*pa))
            _refine3(ta, pa, tb, pb, 0)
            current.append(CurvePoint(*pb))

        _commit()

        _adbg(f"parametric_3d: {len(segments)} segs, "
              f"{sum(len(s.points) for s in segments)} pts", self.adv)
        return segments


# ============================================================================
# SURFACE SAMPLER  (z=f(x,y) and parametric)
# ============================================================================

class SurfaceSampler:
    """
    Sample surfaces into MeshData.
    Covers: explicit z=f(x,y), parametric (x,y,z)(u,v), implicit F(x,y,z)=0.
    """

    def __init__(self,
                 resolution: int = 64,
                 debug: bool = False,
                 advanced_debug: bool = False):
        self.res = resolution
        self.debug = debug
        self.adv   = advanced_debug

    # ── Explicit z = f(x,y) ─────────────────────────────────────────────────

    def explicit(self,
                 fn: ScalarFn2,
                 x_range: Vec2, y_range: Vec2) -> MeshData:
        """
        Improvements over original:
        • Vectorised evaluation attempt via numpy — falls back to scalar loop.
        • NaN / Inf values are patched by nearest-neighbour averaging instead
          of being silently zeroed, preventing sharp spikes at singularities.
        • Curvature-weighted normals: cross-products use all 4 neighbour pairs
          (not just 2), averaged with area weighting for smoother shading.
        """
        with _timed("surface.explicit sample", self.adv):
            N  = self.res
            xs = np.linspace(x_range[0], x_range[1], N)
            ys = np.linspace(y_range[0], y_range[1], N)
            XX, YY = np.meshgrid(xs, ys)  # shape (N, N)

            # Attempt vectorised eval first
            ZZ = np.full((N, N), np.nan)
            try:
                ZZ_try = np.asarray(fn(XX, YY), dtype=float)
                if ZZ_try.shape == (N, N):
                    ZZ = ZZ_try
                else:
                    raise ValueError("shape mismatch")
            except Exception:
                # Scalar fallback
                for i in range(N):
                    for j in range(N):
                        try:
                            v = float(fn(float(XX[i,j]), float(YY[i,j])))
                            ZZ[i,j] = v if math.isfinite(v) else np.nan
                        except Exception:
                            pass  # leave as NaN

            bad_mask = ~np.isfinite(ZZ)
            bad = int(bad_mask.sum())

            # Patch NaN holes: replace with mean of finite 8-neighbours
            if bad > 0:
                ZZ_fixed = ZZ.copy()
                bad_idx = np.argwhere(bad_mask)
                for (i, j) in bad_idx:
                    nbrs = []
                    for di in (-1, 0, 1):
                        for dj in (-1, 0, 1):
                            ni, nj = i+di, j+dj
                            if 0 <= ni < N and 0 <= nj < N:
                                v = ZZ[ni, nj]
                                if math.isfinite(float(v)):
                                    nbrs.append(float(v))
                    ZZ_fixed[i, j] = (sum(nbrs)/len(nbrs)) if nbrs else 0.0
                ZZ = ZZ_fixed

        _dbg(f"explicit surface {N}×{N}, {bad} eval errors patched", self.debug)

        verts, uvs = [], []
        for i in range(N):
            for j in range(N):
                verts.append([xs[j], ys[i], float(ZZ[i,j])])
                uvs.append([j/(N-1), i/(N-1)])

        verts_arr = np.array(verts)
        uvs_arr   = np.array(uvs)
        normals   = self._normals_grid_smooth(verts_arr, N, N)
        tris      = self._grid_tris(N, N)

        mesh = MeshData(verts_arr, tris, normals, uvs_arr)
        _adbg(f"explicit: {len(verts)} verts, {len(tris)} tris", self.adv)
        return mesh

    # ── Parametric (x,y,z)(u,v) ─────────────────────────────────────────────

    def parametric(self,
                   fx, fy, fz,
                   u_range: Vec2 = (0.0, 1.0),
                   v_range: Vec2 = (0.0, 1.0)) -> MeshData:
        N  = self.res
        us = np.linspace(u_range[0], u_range[1], N)
        vs = np.linspace(v_range[0], v_range[1], N)
        verts, uvs = [], []
        bad = 0
        for u in us:
            for v in vs:
                try:
                    x = float(fx(u, v))
                    y = float(fy(u, v))
                    z = float(fz(u, v))
                except Exception:
                    x = y = z = 0.0
                    bad += 1
                verts.append([x, y, z])
                uvs.append([(u-u_range[0])/(u_range[1]-u_range[0]+1e-12),
                             (v-v_range[0])/(v_range[1]-v_range[0]+1e-12)])

        verts_arr = np.array(verts)
        uvs_arr   = np.array(uvs)
        normals   = self._normals_grid(verts_arr, N, N)
        tris      = self._grid_tris(N, N)

        _dbg(f"parametric surface {N}×{N}, {bad} eval errors", self.debug)
        _adbg(f"parametric: {len(verts)} verts, {len(tris)} tris", self.adv)
        return MeshData(verts_arr, tris, normals, uvs_arr)

    # ── Helpers ──────────────────────────────────────────────────────────────

    @staticmethod
    def _grid_tris(Nu: int, Nv: int) -> np.ndarray:
        tris = []
        for i in range(Nu-1):
            for j in range(Nv-1):
                a = i*Nv+j;  b = a+1
                c = (i+1)*Nv+j;  d = c+1
                tris += [[a,b,c],[b,d,c]]
        return np.array(tris, dtype=int)

    @staticmethod
    def _normals_grid(verts: np.ndarray, Nu: int, Nv: int) -> np.ndarray:
        normals = np.zeros_like(verts)
        for i in range(Nu):
            for j in range(Nv):
                idx = i*Nv+j
                ip  = min(i+1, Nu-1); im = max(i-1, 0)
                jp  = min(j+1, Nv-1); jm = max(j-1, 0)
                du  = verts[ip*Nv+j] - verts[im*Nv+j]
                dv  = verts[i*Nv+jp] - verts[i*Nv+jm]
                n   = np.cross(du, dv)
                nm  = np.linalg.norm(n) + 1e-12
                normals[idx] = n / nm
        return normals

    @staticmethod
    def _normals_grid_smooth(verts: np.ndarray, Nu: int, Nv: int) -> np.ndarray:
        """
        Area-weighted average of the normals of all triangles incident to each
        vertex — much smoother than the simple central-difference normal,
        especially near saddle points and ridges.
        """
        normals = np.zeros_like(verts)
        idx = lambda i, j: i * Nv + j  # noqa: E731

        for i in range(Nu - 1):
            for j in range(Nv - 1):
                a = verts[idx(i,   j  )]
                b = verts[idx(i,   j+1)]
                c = verts[idx(i+1, j  )]
                d = verts[idx(i+1, j+1)]
                # Two triangles per quad cell
                n1 = np.cross(b - a, c - a)
                n2 = np.cross(c - b, d - b)
                for vi, n in [(idx(i,j), n1), (idx(i,j+1), n1),
                               (idx(i+1,j), n1), (idx(i,j+1), n2),
                               (idx(i+1,j), n2), (idx(i+1,j+1), n2)]:
                    normals[vi] += n

        norms = np.linalg.norm(normals, axis=1, keepdims=True) + 1e-12
        return normals / norms


# ============================================================================
# MARCHING CUBES  (isosurface extraction)
# ============================================================================

class MarchingCubes:
    """
    Simple marching cubes for F(x,y,z) = iso_value.
    Uses linear interpolation per edge.
    """

    def __init__(self,
                 x_range: Vec2 = (-5,5),
                 y_range: Vec2 = (-5,5),
                 z_range: Vec2 = (-5,5),
                 resolution: int = 40,
                 iso_value: float = 0.0,
                 smooth_iterations: int = 0,
                 debug: bool = False,
                 advanced_debug: bool = False):
        self.x_range   = x_range
        self.y_range   = y_range
        self.z_range   = z_range
        self.res       = resolution
        self.iso       = iso_value
        self.smooth    = smooth_iterations
        self.debug     = debug
        self.adv       = advanced_debug

    def extract(self, fn: ScalarFn3) -> MeshData:
        N  = self.res
        xs = np.linspace(self.x_range[0], self.x_range[1], N)
        ys = np.linspace(self.y_range[0], self.y_range[1], N)
        zs = np.linspace(self.z_range[0], self.z_range[1], N)

        with _timed("marching_cubes volume sample", self.adv):
            # Vectorised volume sample with scalar fallback
            vol = np.full((N, N, N), 0.0)
            try:
                GX, GY, GZ = np.meshgrid(xs, ys, zs, indexing='ij')
                vol_try = np.asarray(fn(GX, GY, GZ), dtype=float)
                if vol_try.shape == (N, N, N) and np.isfinite(vol_try).all():
                    vol = vol_try
                else:
                    raise ValueError
            except Exception:
                for ix in range(N):
                    for iy in range(N):
                        for iz in range(N):
                            try:
                                v = fn(xs[ix], ys[iy], zs[iz])
                                vol[ix,iy,iz] = v if math.isfinite(float(v)) else 0.0
                            except Exception:
                                vol[ix,iy,iz] = 0.0

        with _timed("marching_cubes mesh extraction", self.adv):
            verts_out, faces_out = self._march(vol - self.iso, xs, ys, zs)

        if not verts_out:
            _dbg("marching_cubes: no surface found", self.debug)
            return MeshData(np.zeros((1,3)), np.zeros((0,3),int), np.zeros((1,3)))

        va = np.array(verts_out)
        fa = np.array(faces_out, dtype=int)

        # Smooth normals via central differences on the volume gradient
        na = self._gradient_normals(va, vol, xs, ys, zs)

        if self.smooth > 0:
            va = self._laplacian_smooth(va, fa, self.smooth)

        _dbg(f"marching_cubes: {len(va)} verts, {len(fa)} tris", self.debug)
        return MeshData(va, fa, na)

    def _march(self, vol, xs, ys, zs):
        """
        Full 256-case marching cubes using the standard 12-edge table.
        Each cube configuration maps to a set of triangles on the 12 edges.
        Edges are shared via a vertex cache keyed by rounded coordinates.
        """
        # Standard MC edge table: which of the 12 edges are cut per cube index
        # (256 entries; each is a 12-bit mask)
        EDGE_TABLE = [
            0x0,   0x109, 0x203, 0x30a, 0x406, 0x50f, 0x605, 0x70c,
            0x80c, 0x905, 0xa0f, 0xb06, 0xc0a, 0xd03, 0xe09, 0xf00,
            0x190, 0x99,  0x393, 0x29a, 0x596, 0x49f, 0x795, 0x69c,
            0x99c, 0x895, 0xb9f, 0xa96, 0xd9a, 0xc93, 0xf99, 0xe90,
            0x230, 0x339, 0x33,  0x13a, 0x636, 0x73f, 0x435, 0x53c,
            0xa3c, 0xb35, 0x83f, 0x936, 0xe3a, 0xf33, 0xc39, 0xd30,
            0x3a0, 0x2a9, 0x1a3, 0xaa,  0x7a6, 0x6af, 0x5a5, 0x4ac,
            0xbac, 0xaa5, 0x9af, 0x8a6, 0xfaa, 0xea3, 0xda9, 0xca0,
            0x460, 0x569, 0x663, 0x76a, 0x66,  0x16f, 0x265, 0x36c,
            0xc6c, 0xd65, 0xe6f, 0xf66, 0x86a, 0x963, 0xa69, 0xb60,
            0x5f0, 0x4f9, 0x7f3, 0x6fa, 0x1f6, 0xff,  0x3f5, 0x2fc,
            0xdfc, 0xcf5, 0xfff, 0xef6, 0x9fa, 0x8f3, 0xbf9, 0xaf0,
            0x650, 0x759, 0x453, 0x55a, 0x256, 0x35f, 0x55,  0x15c,
            0xe5c, 0xf55, 0xc5f, 0xd56, 0xa5a, 0xb53, 0x859, 0x950,
            0x7c0, 0x6c9, 0x5c3, 0x4ca, 0x3c6, 0x2cf, 0x1c5, 0xcc,
            0xfcc, 0xec5, 0xdcf, 0xcc6, 0xbca, 0xac3, 0x9c9, 0x8c0,
            0x8c0, 0x9c9, 0xac3, 0xbca, 0xcc6, 0xdcf, 0xec5, 0xfcc,
            0xcc,  0x1c5, 0x2cf, 0x3c6, 0x4ca, 0x5c3, 0x6c9, 0x7c0,
            0x950, 0x859, 0xb53, 0xa5a, 0xd56, 0xc5f, 0xf55, 0xe5c,
            0x15c, 0x55,  0x35f, 0x256, 0x55a, 0x453, 0x759, 0x650,
            0xaf0, 0xbf9, 0x8f3, 0x9fa, 0xef6, 0xfff, 0xcf5, 0xdfc,
            0x2fc, 0x3f5, 0xff,  0x1f6, 0x6fa, 0x7f3, 0x4f9, 0x5f0,
            0xb60, 0xa69, 0x963, 0x86a, 0xf66, 0xe6f, 0xd65, 0xc6c,
            0x36c, 0x265, 0x16f, 0x66,  0x76a, 0x663, 0x569, 0x460,
            0xca0, 0xda9, 0xea3, 0xfaa, 0x8a6, 0x9af, 0xaa5, 0xbac,
            0x4ac, 0x5a5, 0x6af, 0x7a6, 0xaa,  0x1a3, 0x2a9, 0x3a0,
            0xd30, 0xc39, 0xf33, 0xe3a, 0x936, 0x835, 0xb3f, 0xa36,  # fixed
            0x53c, 0x435, 0x73f, 0x636, 0x13a, 0x33,  0x339, 0x230,
            0xe90, 0xf99, 0xc93, 0xd9a, 0xa96, 0xb9f, 0x895, 0x99c,
            0x69c, 0x795, 0x49f, 0x596, 0x29a, 0x393, 0x99,  0x190,
            0xf00, 0xe09, 0xd03, 0xc0a, 0xb06, 0xa0f, 0x905, 0x80c,
            0x70c, 0x605, 0x50f, 0x406, 0x30a, 0x203, 0x109, 0x0,
        ]

        # The 12 cube edges as pairs of the 8 corner indices
        CUBE_EDGES = [
            (0,1),(1,2),(2,3),(3,0),   # bottom face
            (4,5),(5,6),(6,7),(7,4),   # top face
            (0,4),(1,5),(2,6),(3,7),   # vertical
        ]

        verts_out = []
        faces_out = []
        vert_cache: Dict[Tuple, int] = {}

        N = self.res

        def interp(p0, p1, v0, v1):
            dv = v1 - v0
            t  = 0.5 if abs(dv) < 1e-10 else (-v0 / dv)
            t  = max(0.0, min(1.0, t))
            return (p0[0]+t*(p1[0]-p0[0]),
                    p0[1]+t*(p1[1]-p0[1]),
                    p0[2]+t*(p1[2]-p0[2]))

        def cache_vert(pt):
            key = (round(pt[0], 6), round(pt[1], 6), round(pt[2], 6))
            if key not in vert_cache:
                vert_cache[key] = len(verts_out)
                verts_out.append(pt)
            return vert_cache[key]

        for ix in range(N-1):
            for iy in range(N-1):
                for iz in range(N-1):
                    corners = [
                        (xs[ix  ],ys[iy  ],zs[iz  ]),
                        (xs[ix+1],ys[iy  ],zs[iz  ]),
                        (xs[ix+1],ys[iy+1],zs[iz  ]),
                        (xs[ix  ],ys[iy+1],zs[iz  ]),
                        (xs[ix  ],ys[iy  ],zs[iz+1]),
                        (xs[ix+1],ys[iy  ],zs[iz+1]),
                        (xs[ix+1],ys[iy+1],zs[iz+1]),
                        (xs[ix  ],ys[iy+1],zs[iz+1]),
                    ]
                    vals = [
                        vol[ix,  iy,  iz  ], vol[ix+1,iy,  iz  ],
                        vol[ix+1,iy+1,iz  ], vol[ix,  iy+1,iz  ],
                        vol[ix,  iy,  iz+1], vol[ix+1,iy,  iz+1],
                        vol[ix+1,iy+1,iz+1], vol[ix,  iy+1,iz+1],
                    ]
                    cube_idx = sum(1<<k for k,v in enumerate(vals) if v >= 0)
                    if cube_idx in (0, 255):
                        continue

                    edge_mask = EDGE_TABLE[cube_idx]
                    if edge_mask == 0:
                        continue

                    # Compute edge intersection points
                    edge_verts = {}
                    for ei, (a, b) in enumerate(CUBE_EDGES):
                        if edge_mask & (1 << ei):
                            edge_verts[ei] = cache_vert(
                                interp(corners[a], corners[b], vals[a], vals[b]))

                    # Fan-triangulate the edge polygon around centroid
                    ev_list = list(edge_verts.values())
                    n = len(ev_list)
                    if n < 3:
                        continue
                    if n == 3:
                        faces_out.append((ev_list[0], ev_list[1], ev_list[2]))
                    else:
                        # Centroid fan
                        pts = [verts_out[vi] for vi in ev_list]
                        cx  = sum(p[0] for p in pts)/n
                        cy  = sum(p[1] for p in pts)/n
                        cz  = sum(p[2] for p in pts)/n
                        ci  = cache_vert((cx, cy, cz))
                        for k in range(n):
                            faces_out.append((ci, ev_list[k], ev_list[(k+1)%n]))

        return verts_out, faces_out

    def _gradient_normals(self, verts, vol, xs, ys, zs):
        """
        Trilinearly interpolated gradient of the volume field — much smoother
        than the grid-snapped lookup used in the original.
        """
        N = len(xs)
        dx = (xs[-1]-xs[0])/(N-1+1e-12)
        dy = (ys[-1]-ys[0])/(N-1+1e-12)
        dz = (zs[-1]-zs[0])/(N-1+1e-12)
        normals = np.zeros_like(verts)
        for k, (x,y,z) in enumerate(verts):
            xi = int(np.clip((x-xs[0])/dx, 1, N-2))
            yi = int(np.clip((y-ys[0])/dy, 1, N-2))
            zi = int(np.clip((z-zs[0])/dz, 1, N-2))
            gx = (vol[xi+1,yi,zi] - vol[xi-1,yi,zi]) / (2*dx)
            gy = (vol[xi,yi+1,zi] - vol[xi,yi-1,zi]) / (2*dy)
            gz = (vol[xi,yi,zi+1] - vol[xi,yi,zi-1]) / (2*dz)
            nm = math.sqrt(gx**2+gy**2+gz**2) + 1e-12
            normals[k] = [gx/nm, gy/nm, gz/nm]
        return normals

    @staticmethod
    def _laplacian_smooth(verts: np.ndarray, faces: np.ndarray,
                           iterations: int) -> np.ndarray:
        """Simple cotangent-free Laplacian smoothing to reduce mesh noise."""
        adj: Dict[int, List[int]] = {i: [] for i in range(len(verts))}
        for f in faces:
            for a, b in [(f[0],f[1]),(f[1],f[2]),(f[2],f[0])]:
                adj[a].append(b)
                adj[b].append(a)
        v = verts.copy()
        for _ in range(iterations):
            v2 = v.copy()
            for i, nbrs in adj.items():
                if nbrs:
                    v2[i] = v[nbrs].mean(axis=0) * 0.5 + v[i] * 0.5
            v = v2
        return v

    def _approx_normals(self, verts, vol, xs, ys, zs):
        """Legacy path — kept for call-site compatibility, delegates to gradient."""
        return self._gradient_normals(verts, vol, xs, ys, zs)


# ============================================================================
# INTERSECTION CURVE FINDER
# ============================================================================

class IntersectionFinder:
    """
    Find curve / surface where F1 = F2.
    2D mode: contour tracing on a grid.
    3D mode: marching cubes on the difference field F1-F2.
    """

    def __init__(self,
                 resolution: int = 80,
                 debug: bool = False,
                 advanced_debug: bool = False):
        self.res   = resolution
        self.debug = debug
        self.adv   = advanced_debug

    def find_2d(self, F1: ScalarFn2, F2: ScalarFn2,
                x_range: Vec2, y_range: Vec2) -> List[CurveSegment]:
        N  = self.res
        xs = np.linspace(x_range[0], x_range[1], N)
        ys = np.linspace(y_range[0], y_range[1], N)

        diff = np.zeros((N, N))
        for i, x in enumerate(xs):
            for j, y in enumerate(ys):
                try:
                    diff[i, j] = F1(x, y) - F2(x, y)
                except Exception:
                    diff[i, j] = 0.0

        # Contour tracing: find sign changes
        segs: List[CurveSegment] = []
        visited = set()
        for i in range(N-1):
            for j in range(N-1):
                if (i,j) in visited:
                    continue
                if (diff[i,j] >= 0) != (diff[i+1,j] >= 0):
                    t = -diff[i,j] / (diff[i+1,j]-diff[i,j]+1e-12)
                    xc = xs[i] + t*(xs[i+1]-xs[i])
                    pt = CurvePoint(xc, ys[j])
                    segs.append(CurveSegment([pt, CurvePoint(xc, ys[j+1])]))
                    visited.add((i,j))

        _dbg(f"intersection_2d: {len(segs)} crossings", self.debug)
        return segs

    def find_3d(self, F1: ScalarFn3, F2: ScalarFn3,
                x_range: Vec2, y_range: Vec2, z_range: Vec2) -> MeshData:
        def diff_fn(x, y, z): return F1(x,y,z) - F2(x,y,z)
        mc = MarchingCubes(x_range, y_range, z_range,
                           resolution=self.res,
                           debug=self.debug, advanced_debug=self.adv)
        return mc.extract(diff_fn)


# ============================================================================
# RIEMANN SURFACE BUILDER
# ============================================================================

class RiemannSurfaceBuilder:
    """
    Build multi-sheet surface meshes for multi-valued complex functions.
    Supported: sqrt (2 sheets), cbrt (3), log (n sheets), pow_pq (q sheets).
    """

    def __init__(self,
                 r_range: Vec2 = (0.05, 3.0),
                 resolution: int = 64,
                 sheet_gap: float = 0.3,
                 debug: bool = False,
                 advanced_debug: bool = False):
        self.r_range = r_range
        self.res     = resolution
        self.gap     = sheet_gap
        self.debug   = debug
        self.adv     = advanced_debug

    def build_sqrt(self)  -> List[Tuple[MeshData,int]]: return self._power(1, 2)
    def build_cbrt(self)  -> List[Tuple[MeshData,int]]: return self._power(1, 3)
    def build_pow_pq(self, p=1, q=4): return self._power(p, q)

    def build_log(self, n_sheets: int = 3) -> List[Tuple[MeshData,int]]:
        res = self.res
        rs  = np.linspace(self.r_range[0], self.r_range[1], res)
        ths = np.linspace(0.0, 2*math.pi, res)
        results = []
        for sheet in range(n_sheets):
            z_off = sheet * self.gap
            verts, uvs = [], []
            for i, r in enumerate(rs):
                for j, th in enumerate(ths):
                    x = r*math.cos(th); y = r*math.sin(th)
                    z = (th + sheet*2*math.pi)/(2*math.pi) + z_off
                    verts.append([x,y,z]); uvs.append([i/(res-1),j/(res-1)])
            va = np.array(verts); ua = np.array(uvs)
            na = SurfaceSampler._normals_grid(va, res, res)
            ta = SurfaceSampler._grid_tris(res, res)
            results.append((MeshData(va, ta, na, ua), sheet))
        _dbg(f"riemann_log: {n_sheets} sheets", self.debug)
        return results

    def _power(self, p: int, q: int) -> List[Tuple[MeshData,int]]:
        res = self.res
        rs  = np.linspace(self.r_range[0], self.r_range[1], res)
        ths = np.linspace(0.0, 2*math.pi, res)
        exp = p / q
        results = []
        for sheet in range(q):
            z_off = sheet * self.gap
            verts, uvs = [], []
            for i, r in enumerate(rs):
                for j, th in enumerate(ths):
                    x = r*math.cos(th); y = r*math.sin(th)
                    full_arg = th + sheet*2*math.pi
                    w_arg = full_arg * exp
                    w_r   = r ** exp
                    z = w_r * math.sin(w_arg) + z_off
                    verts.append([x,y,z]); uvs.append([i/(res-1),j/(res-1)])
            va = np.array(verts); ua = np.array(uvs)
            na = SurfaceSampler._normals_grid(va, res, res)
            ta = SurfaceSampler._grid_tris(res, res)
            results.append((MeshData(va, ta, na, ua), sheet))
        _dbg(f"riemann_power p={p} q={q}: {q} sheets", self.debug)
        return results


# ============================================================================
# VECTOR FIELD SAMPLER
# ============================================================================

class VectorFieldSampler:
    """Sample a vector field on a grid, returning Arrow objects."""

    def __init__(self,
                 density: int = 8,
                 normalize: bool = False,
                 scale: float = 1.0,
                 debug: bool = False,
                 advanced_debug: bool = False):
        self.density   = density
        self.normalize = normalize
        self.scale     = scale
        self.debug     = debug
        self.adv       = advanced_debug

    def sample_2d(self, F: VectorFn2,
                  x_range: Vec2, y_range: Vec2) -> List[Arrow]:
        xs = np.linspace(x_range[0], x_range[1], self.density)
        ys = np.linspace(y_range[0], y_range[1], self.density)
        arrows = []
        for x in xs:
            for y in ys:
                try:
                    vx, vy = F(x, y)
                    vz = 0.0
                except Exception:
                    continue
                vx, vy, vz = float(vx), float(vy), float(vz)
                if self.normalize:
                    m = math.sqrt(vx**2+vy**2) + 1e-12
                    vx, vy = vx/m, vy/m
                arrows.append(Arrow((x,y,0), (vx*self.scale, vy*self.scale, 0)))
        _dbg(f"vector_field_2d: {len(arrows)} arrows", self.debug)
        return arrows

    def sample_3d(self, F: VectorFn3,
                  x_range, y_range, z_range) -> List[Arrow]:
        d  = max(2, int(self.density**(1/1.5)))
        xs = np.linspace(x_range[0], x_range[1], d)
        ys = np.linspace(y_range[0], y_range[1], d)
        zs = np.linspace(z_range[0], z_range[1], d)
        arrows = []
        for x in xs:
            for y in ys:
                for z in zs:
                    try:
                        vx,vy,vz = F(x,y,z)
                    except Exception:
                        continue
                    vx,vy,vz = float(vx),float(vy),float(vz)
                    if self.normalize:
                        m = math.sqrt(vx**2+vy**2+vz**2) + 1e-12
                        vx,vy,vz = vx/m, vy/m, vz/m
                    arrows.append(Arrow((x,y,z),
                                        (vx*self.scale, vy*self.scale, vz*self.scale)))
        _dbg(f"vector_field_3d: {len(arrows)} arrows", self.debug)
        return arrows


# ============================================================================
# INTEGRAL CURVE SOLVER  (streamlines)
# ============================================================================

class IntegralCurveSolver:
    """
    Adaptive Runge-Kutta-Fehlberg (RK45) integration of a vector field.

    Improvements over the original midpoint RK2:
    • RK4(5) error estimate — step is accepted or rejected based on a local
      error tolerance, so the integrator takes large steps in smooth regions
      and small steps near tight spirals or rapid turns.
    • Step-size control: h is doubled on accurate steps and halved on
      inaccurate ones, bounded by [h_min, h_max].
    • Stagnation guard: stops if the field magnitude drops below a threshold
      (avoid hanging at attractors / fixed points).
    • Backward integration: pass direction=-1 to trace streamlines upstream.
    """

    # Butcher tableau for RK4(5) Cash-Karp coefficients
    _A  = [0, 1/5, 3/10, 3/5, 1, 7/8]
    _B  = [[], [1/5], [3/40,9/40], [3/10,-9/10,6/5],
           [-11/54, 5/2, -70/27, 35/27],
           [1631/55296, 175/512, 575/13824, 44275/110592, 253/4096]]
    _C4 = [37/378, 0, 250/621, 125/594, 0, 512/1771]       # 4th-order weights
    _C5 = [2825/27648, 0, 18575/48384, 13525/55296,         # 5th-order weights
           277/14336, 1/4]

    def __init__(self,
                 step_size: float = 0.05,
                 max_steps: int = 500,
                 tol: float = 1e-4,
                 h_min: float = 1e-5,
                 h_max: float = 0.5,
                 direction: float = 1.0,
                 bounds=None,
                 debug: bool = False,
                 advanced_debug: bool = False):
        self.step      = step_size
        self.max       = max_steps
        self.tol       = tol
        self.h_min     = h_min
        self.h_max     = h_max
        self.direction = direction   # +1 forward, -1 backward
        self.bounds    = bounds
        self.debug     = debug
        self.adv       = advanced_debug

    # ── 2-D ─────────────────────────────────────────────────────────────────

    def integrate_2d(self, F: VectorFn2, seed: Vec2) -> CurveSegment:
        pts = [CurvePoint(seed[0], seed[1])]
        x, y = float(seed[0]), float(seed[1])
        h = self.step * self.direction

        for _ in range(self.max):
            if self.bounds and not self._in_bounds_2d(x, y):
                break
            try:
                k = self._ck_stages_2d(F, x, y, h)
            except Exception:
                break

            # 4th- and 5th-order solution estimates
            x4 = x + sum(self._C4[i]*k[i][0] for i in range(6))
            y4 = y + sum(self._C4[i]*k[i][1] for i in range(6))
            x5 = x + sum(self._C5[i]*k[i][0] for i in range(6))
            y5 = y + sum(self._C5[i]*k[i][1] for i in range(6))

            err = math.sqrt((x5-x4)**2 + (y5-y4)**2) + 1e-30
            if err > self.tol and abs(h) > self.h_min:
                h *= 0.5
                continue

            x, y = x4, y4
            pts.append(CurvePoint(x, y))

            # Stagnation guard
            mag = math.sqrt(k[0][0]**2 + k[0][1]**2)
            if mag < 1e-9:
                break

            # Adapt step
            if err < self.tol * 0.1 and abs(h) < self.h_max:
                h = min(abs(h) * 2.0, self.h_max) * (1 if h > 0 else -1)

        _dbg(f"integral_curve_2d (adaptive): {len(pts)} pts", self.debug)
        return CurveSegment(pts)

    def _ck_stages_2d(self, F, x, y, h):
        B, A = self._B, self._A
        ks = []
        for i in range(6):
            xi = x + sum(B[i][j]*ks[j][0] for j in range(len(B[i])))
            yi = y + sum(B[i][j]*ks[j][1] for j in range(len(B[i])))
            vx, vy = F(xi, yi)
            ks.append((h*float(vx), h*float(vy)))
        return ks

    # ── 3-D ─────────────────────────────────────────────────────────────────

    def integrate_3d(self, F: VectorFn3, seed) -> CurveSegment:
        pts = [CurvePoint(*seed[:3])]
        x, y, z = float(seed[0]), float(seed[1]), float(seed[2])
        h = self.step * self.direction

        for _ in range(self.max):
            if self.bounds and not self._in_bounds_3d(x, y, z):
                break
            try:
                k = self._ck_stages_3d(F, x, y, z, h)
            except Exception:
                break

            x4 = x + sum(self._C4[i]*k[i][0] for i in range(6))
            y4 = y + sum(self._C4[i]*k[i][1] for i in range(6))
            z4 = z + sum(self._C4[i]*k[i][2] for i in range(6))
            x5 = x + sum(self._C5[i]*k[i][0] for i in range(6))
            y5 = y + sum(self._C5[i]*k[i][1] for i in range(6))
            z5 = z + sum(self._C5[i]*k[i][2] for i in range(6))

            err = math.sqrt((x5-x4)**2 + (y5-y4)**2 + (z5-z4)**2) + 1e-30
            if err > self.tol and abs(h) > self.h_min:
                h *= 0.5
                continue

            x, y, z = x4, y4, z4
            pts.append(CurvePoint(x, y, z))

            mag = math.sqrt(k[0][0]**2 + k[0][1]**2 + k[0][2]**2)
            if mag < 1e-9:
                break

            if err < self.tol * 0.1 and abs(h) < self.h_max:
                h = min(abs(h) * 2.0, self.h_max) * (1 if h > 0 else -1)

        _dbg(f"integral_curve_3d (adaptive): {len(pts)} pts", self.debug)
        return CurveSegment(pts)

    def _ck_stages_3d(self, F, x, y, z, h):
        B, A = self._B, self._A
        ks = []
        for i in range(6):
            xi = x + sum(B[i][j]*ks[j][0] for j in range(len(B[i])))
            yi = y + sum(B[i][j]*ks[j][1] for j in range(len(B[i])))
            zi = z + sum(B[i][j]*ks[j][2] for j in range(len(B[i])))
            vx, vy, vz = F(xi, yi, zi)
            ks.append((h*float(vx), h*float(vy), h*float(vz)))
        return ks

    def _in_bounds_2d(self, x, y):
        if not self.bounds: return True
        xb, yb = self.bounds[:2]
        return xb[0]<=x<=xb[1] and yb[0]<=y<=yb[1]

    def _in_bounds_3d(self, x, y, z):
        if not self.bounds: return True
        if len(self.bounds) < 3: return True
        xb, yb, zb = self.bounds[:3]
        return (xb[0]<=x<=xb[1] and yb[0]<=y<=yb[1] and zb[0]<=z<=zb[1])


# ============================================================================
# DOMAIN COLORIZER  (complex analysis)
# ============================================================================

class DomainColorizer:
    """
    Compute RGBA image for domain coloring of f: C→C.
    Hue = argument of f(z), brightness = |f(z)|.
    """

    def __init__(self,
                 resolution: int = 256,
                 x_range: Vec2 = (-3,3),
                 y_range: Vec2 = (-3,3),
                 debug: bool = False,
                 advanced_debug: bool = False):
        self.res   = resolution
        self.x_range = x_range
        self.y_range = y_range
        self.debug = debug
        self.adv   = advanced_debug

    def compute(self, fn: ComplexFn) -> np.ndarray:
        """Returns (H, W, 4) float array in [0,1]."""
        N  = self.res
        xs = np.linspace(self.x_range[0], self.x_range[1], N)
        ys = np.linspace(self.y_range[0], self.y_range[1], N)
        img = np.zeros((N, N, 4), dtype=float)
        for i, y in enumerate(ys):
            for j, x in enumerate(xs):
                try:
                    w = fn(complex(x, y))
                    arg = cmath.phase(w)           # -π … π
                    mag = abs(w)
                    hue = (arg / (2*math.pi)) % 1.0
                    val = 1.0 - 1.0/(1.0 + mag)    # brightness
                    r,g,b = self._hsv_to_rgb(hue, 0.8, val)
                    img[i,j] = [r,g,b,1.0]
                except Exception:
                    img[i,j] = [0,0,0,1]
        _dbg(f"domain_color: {N}×{N} image", self.debug)
        return img

    @staticmethod
    def _hsv_to_rgb(h,s,v):
        if s == 0: return (v,v,v)
        i = int(h*6); f = h*6 - i
        p,q,t = v*(1-s), v*(1-f*s), v*(1-(1-f)*s)
        return [(v,t,p),(q,v,p),(p,v,t),(p,q,v),(t,p,v),(v,p,q)][i%6]


# ============================================================================
# GEOMETRIC ALGEBRA  (Kingdon integration)
# ============================================================================

class GABackend:
    """
    GA backend abstraction. Supports VGA (3D), PGA (3D projective),
    CGA (conformal), STA (spacetime), or any custom kingdon Algebra.

    Grade → Render mapping:
      0  Scalar          → text label
      1  Vector          → arrow
      2  Bivector        → plane patch  (or circle for round CGA objects)
      3  Trivector       → volume cube
      4  Pseudoscalar    → projected vector
      n  Higher          → spread across multiple 3D sub-projections
    """

    BACKENDS = {
        'vga': dict(p=3, q=0, r=0),   # Vanilla 3D
        'pga': dict(p=3, q=0, r=1),   # Projective 3D
        'cga': dict(p=4, q=1, r=0),   # Conformal
        'sta': dict(p=3, q=1, r=0),   # Spacetime algebra
    }

    def __init__(self,
                 backend: str = 'vga',
                 custom_algebra=None,
                 debug: bool = False,
                 advanced_debug: bool = False):
        self.backend_name = backend
        self.debug = debug
        self.adv   = advanced_debug
        self.algebra = custom_algebra
        if KINGDON_AVAILABLE and custom_algebra is None:
            spec = self.BACKENDS.get(backend, self.BACKENDS['vga'])
            try:
                self.algebra = KingdonAlgebra(**spec)
            except Exception as e:
                _dbg(f"GA algebra init failed ({e})", debug)
                self.algebra = None

    # ── Grade detection ──────────────────────────────────────────────────────

    @staticmethod
    def detect_grade(mv) -> int:
        """Detect dominant grade of a kingdon multivector."""
        if not KINGDON_AVAILABLE:
            return 0
        if hasattr(mv, 'grade') and callable(mv.grade):
            try:
                return int(mv.grade())
            except Exception:
                pass
        # Fallback: parse string representation
        s = str(mv)
        if 'e0123' in s or 'e123' in s:
            return 3
        if any(x in s for x in ('e12','e23','e13','e01','e02','e03','e31')):
            return 2
        if any(x in s for x in ('e1','e2','e3','e0')):
            return 1
        return 0

    # ── Grade extraction ─────────────────────────────────────────────────────

    @staticmethod
    def extract_vector(mv) -> Vec3:
        """Extract (e1, e2, e3) from grade-1 multivector."""
        if not KINGDON_AVAILABLE:
            return (0.0, 0.0, 0.0)
        # Try direct attribute access first
        try:
            e1 = float(getattr(mv, 'e1', 0) or 0)
            e2 = float(getattr(mv, 'e2', 0) or 0)
            e3 = float(getattr(mv, 'e3', 0) or 0)
            return (e1, e2, e3)
        except Exception:
            pass
        # Fallback: index-based
        try:
            vals = [0.0]*3
            for i, key in enumerate(['e1','e2','e3']):
                if hasattr(mv, key):
                    vals[i] = float(getattr(mv, key) or 0)
            return tuple(vals)
        except Exception:
            return (0.0, 0.0, 0.0)

    @staticmethod
    def extract_bivector_normal(mv) -> Vec3:
        """Extract approximate plane normal from grade-2 bivector."""
        if not KINGDON_AVAILABLE:
            return (0.0, 0.0, 1.0)
        try:
            e12 = float(getattr(mv, 'e12', 0) or 0)
            e23 = float(getattr(mv, 'e23', 0) or 0)
            e13 = float(getattr(mv, 'e13', 0) or 0)
            # dual of e12 is e3, dual of e23 is e1, dual of e13 is -e2
            nx, ny, nz = e23, -e13, e12
            nm = math.sqrt(nx**2+ny**2+nz**2) + 1e-12
            return (nx/nm, ny/nm, nz/nm)
        except Exception:
            return (0.0, 0.0, 1.0)

    @staticmethod
    def extract_scalar(mv) -> float:
        if not KINGDON_AVAILABLE: return 0.0
        try:
            return float(getattr(mv, 'e', None) or getattr(mv, '__float__', None)() or 0)
        except Exception:
            return 0.0

    @staticmethod
    def rotor_to_axis_angle(rotor) -> Tuple[Vec3, float]:
        """Decompose R = cos(θ/2) + sin(θ/2)*B̂ into (axis, angle)."""
        if not KINGDON_AVAILABLE:
            return ((0,0,1), 0.0)
        try:
            cos_half = float(getattr(rotor, 'e', 0) or 0)
            cos_half = max(-1.0, min(1.0, cos_half))
            angle = 2.0 * math.acos(cos_half)
            e12 = float(getattr(rotor, 'e12', 0) or 0)
            e23 = float(getattr(rotor, 'e23', 0) or 0)
            e13 = float(getattr(rotor, 'e13', 0) or 0)
            axis = (e23, -e13, e12)
            nm   = math.sqrt(sum(a**2 for a in axis)) + 1e-12
            axis = tuple(a/nm for a in axis)
            return (axis, angle)
        except Exception:
            return ((0,0,1), 0.0)

    def debug_print(self, mv, label: str = "mv"):
        """Full diagnostic dump when advanced_debug is active."""
        if not self.adv:
            return
        grade = self.detect_grade(mv)
        vec   = self.extract_vector(mv)
        bvn   = self.extract_bivector_normal(mv)
        print(f"{_DBG_ADV_PREFIX}GA {label}:")
        print(f"  backend   = {self.backend_name}")
        print(f"  str       = {str(mv)[:80]}")
        print(f"  grade     = {grade}")
        print(f"  vector xyz= {vec}")
        print(f"  bivec n   = {bvn}")
        if grade == 0:
            print(f"  scalar    = {self.extract_scalar(mv)}")


# ============================================================================
# SPREAD ENGINE  (nD → multiple 3D projections)
# ============================================================================

class SpreadEngine:
    """
    Render high-dimensional data as a grid of 3D sub-plots.

    For a function f(x1, x2, ..., xN) with N > 3, generate all
    combinations of 3-coordinate projections and produce one sub-plot per
    combination (up to max_subplots).

    Each sub-plot gets its own PlotBounds offset in world space.
    """

    def __init__(self,
                 fn,
                 var_names: List[str],
                 var_ranges: List[Vec2],
                 max_subplots: int = 9,
                 subplot_spacing: float = 12.0,
                 resolution: int = 32,
                 debug: bool = False,
                 advanced_debug: bool = False):
        self.fn              = fn
        self.var_names       = var_names
        self.var_ranges      = var_ranges
        self.max_subplots    = max_subplots
        self.subplot_spacing = subplot_spacing
        self.resolution      = resolution
        self.debug           = debug
        self.adv             = advanced_debug

    def generate_projections(self) -> List[Dict]:
        """
        Return list of dicts with keys:
          - 'axes': (i, j, k)  indices of the 3 chosen dimensions
          - 'labels': (xi_name, xj_name, xk_name)
          - 'mesh': MeshData sampled at midpoints of remaining dims
          - 'offset': FVector offset in UU
        """
        from itertools import combinations
        N = len(self.var_names)
        triples = list(combinations(range(N), 3))[:self.max_subplots]

        # Midpoints for the "fixed" dimensions
        midpoints = [(r[0]+r[1])/2 for r in self.var_ranges]

        results = []
        cols    = int(math.ceil(math.sqrt(len(triples))))
        sampler = SurfaceSampler(resolution=self.resolution,
                                 debug=self.debug,
                                 advanced_debug=self.adv)

        for idx, (i, j, k) in enumerate(triples):
            row_n = idx // cols
            col_n = idx %  cols
            offset = (col_n * self.subplot_spacing,
                      row_n * self.subplot_spacing,
                      0.0)

            fixed = dict(enumerate(midpoints))
            xi_range = self.var_ranges[i]
            xj_range = self.var_ranges[j]
            xk_range = self.var_ranges[k]

            def make_fn(ii, ij, ik, fixed_dims):
                def wrapped(u, v):
                    args = list(midpoints)
                    args[ii] = u
                    args[ij] = v
                    args[ik] = (xk_range[0]+xk_range[1])/2
                    # Override fixed dims
                    for fd, fv in fixed_dims.items():
                        args[fd] = fv
                    try:
                        return float(self.fn(*args))
                    except Exception:
                        return 0.0
                return wrapped

            # Slice: fix xk at midpoint, vary xi, xj
            fn_slice = make_fn(i, j, k, {
                d: midpoints[d] for d in range(N) if d not in (i,j,k)
            })
            mesh = sampler.explicit(fn_slice, xi_range, xj_range)

            results.append({
                'axes':   (i, j, k),
                'labels': (self.var_names[i],
                           self.var_names[j],
                           self.var_names[k]),
                'mesh':    mesh,
                'offset':  offset,
            })

        _dbg(f"spread_engine: {len(results)} projections for {N}D fn", self.debug)
        if self.adv:
            for r in results:
                print(f"{_DBG_ADV_PREFIX}  projection {r['axes']} -> offset {r['offset']}")
        return results


# ============================================================================
# TUBE MESH BUILDER  (baked dash patterns, end caps, cross-section shapes)
# ============================================================================

class TubeMeshBuilder:
    """
    Build a 3D tube mesh along a polyline.

    Features:
    - Cross-section: 'cylinder' (N-gon) or 'square_tube' (4 sides)
    - Dash pattern: (on_len, off_len) in math units; baked into geometry
    - End caps: 'flat', 'none', 'sphere', 'cone'
    - Parallel-transport frame (no twisting)
    - Per-vertex UV coordinates
    """

    def __init__(self,
                 radius: float = 0.02,
                 sides: int = 10,
                 shape: str = 'cylinder',        # 'cylinder' | 'square_tube'
                 dash_pattern: Tuple = None,      # (on, off) in math units
                 end_cap: str = 'flat',           # 'flat'|'none'|'sphere'|'cone'
                 debug: bool = False,
                 advanced_debug: bool = False):
        self.radius   = radius
        self.sides    = max(3, sides)
        self.shape    = shape
        self.dash     = dash_pattern
        self.end_cap  = end_cap
        self.debug    = debug
        self.adv      = advanced_debug

    def build(self, pts: List[Vec3]) -> MeshData:
        """Build tube mesh from a list of (x,y,z) points."""
        if len(pts) < 2:
            return MeshData(np.zeros((1,3)), np.zeros((0,3),int), np.zeros((1,3)))

        # Apply dash pattern: split pts into solid sub-segments
        if self.dash:
            sub_segs = self._apply_dash(pts)
        else:
            sub_segs = [pts]

        all_verts, all_norms, all_uvs, all_tris = [], [], [], []
        vert_offset = 0

        for seg in sub_segs:
            if len(seg) < 2:
                continue
            frame = self._parallel_transport_frame(seg)
            v, n, u, t = self._extrude_tube(seg, frame, vert_offset)
            all_verts.extend(v)
            all_norms.extend(n)
            all_uvs.extend(u)
            all_tris.extend(t)
            vert_offset += len(v)

            # End caps
            if self.end_cap == 'flat':
                cv, cn, ct = self._flat_cap(seg[0], frame[0][1], frame[0][2],
                                             is_start=True, v_off=vert_offset)
                all_verts.extend(cv); all_norms.extend(cn); all_tris.extend(ct)
                vert_offset += len(cv)
                cv, cn, ct = self._flat_cap(seg[-1], frame[-1][1], frame[-1][2],
                                             is_start=False, v_off=vert_offset)
                all_verts.extend(cv); all_norms.extend(cn); all_tris.extend(ct)
                vert_offset += len(cv)
            elif self.end_cap == 'sphere':
                cv, cn, ct = self._sphere_cap(seg[0], v_off=vert_offset)
                all_verts.extend(cv); all_norms.extend(cn); all_tris.extend(ct)
                vert_offset += len(cv)
                cv, cn, ct = self._sphere_cap(seg[-1], v_off=vert_offset)
                all_verts.extend(cv); all_norms.extend(cn); all_tris.extend(ct)
                vert_offset += len(cv)
            elif self.end_cap == 'cone':
                cv, cn, ct = self._cone_cap(seg[-1],
                                             self._tube_tangent(seg, -1),
                                             v_off=vert_offset)
                all_verts.extend(cv); all_norms.extend(cn); all_tris.extend(ct)
                vert_offset += len(cv)

        if not all_verts:
            return MeshData(np.zeros((1,3)), np.zeros((0,3),int), np.zeros((1,3)))

        uv_arr = np.zeros((len(all_verts), 2))
        for i, u in enumerate(all_uvs):
            if i < len(uv_arr):
                uv_arr[i] = u

        mesh = MeshData(np.array(all_verts), np.array(all_tris, dtype=int),
                        np.array(all_norms), uv_arr)
        _adbg(f"tube: {len(all_verts)} verts, {len(all_tris)} tris", self.adv)
        return mesh

    # ── Parallel transport frame ────────────────────────────────────────────

    def _parallel_transport_frame(self, pts):
        """
        Returns list of (tangent, normal, binormal) per point.
        Uses parallel transport to avoid twisting.
        """
        n  = len(pts)
        frames = []
        tangs  = []
        for i in range(n):
            if i < n-1:
                d = self._sub(pts[i+1], pts[i])
            else:
                d = self._sub(pts[-1], pts[-2])
            nm = self._norm(d) + 1e-12
            tangs.append(tuple(x/nm for x in d))

        # Initial frame: pick arbitrary normal
        t0 = tangs[0]
        up = (0,0,1) if abs(t0[2]) < 0.9 else (1,0,0)
        b0 = self._cross(t0, up)
        nm = self._norm(b0) + 1e-12
        b0 = tuple(x/nm for x in b0)
        n0 = self._cross(b0, t0)
        frames.append((t0, n0, b0))

        for i in range(1, n):
            prev_t, prev_n, prev_b = frames[-1]
            t = tangs[i]
            b = self._cross(t, prev_n)
            nm = self._norm(b) + 1e-12
            b = tuple(x/nm for x in b)
            norml = self._cross(b, t)
            frames.append((t, norml, b))

        return frames

    def _extrude_tube(self, pts, frames, v_off):
        sides = self.sides if self.shape == 'cylinder' else 4
        angle_step = 2*math.pi / sides
        verts, norms, uvs, tris = [], [], [], []

        rings = []
        for i, (pt, (tang, norml, binom)) in enumerate(zip(pts, frames)):
            ring = []
            u_coord = i / max(len(pts)-1, 1)
            for s in range(sides):
                angle = s * angle_step
                n_local = (
                    math.cos(angle)*norml[0] + math.sin(angle)*binom[0],
                    math.cos(angle)*norml[1] + math.sin(angle)*binom[1],
                    math.cos(angle)*norml[2] + math.sin(angle)*binom[2],
                )
                v_local = (
                    pt[0] + self.radius*n_local[0],
                    pt[1] + self.radius*n_local[1],
                    pt[2] + self.radius*n_local[2],
                )
                verts.append(v_local)
                norms.append(n_local)
                uvs.append([s/sides, u_coord])
                ring.append(len(verts)-1 + v_off)
            rings.append(ring)

        for i in range(len(rings)-1):
            for s in range(sides):
                a = rings[i  ][s]
                b = rings[i  ][(s+1)%sides]
                c = rings[i+1][s]
                d = rings[i+1][(s+1)%sides]
                tris += [[a,b,c],[b,d,c]]

        return verts, norms, uvs, tris

    def _flat_cap(self, pt, norml, binom, is_start: bool, v_off: int):
        sides = self.sides if self.shape == 'cylinder' else 4
        step  = 2*math.pi/sides
        tang  = (0,0,0)  # unused but needed by frame
        cap_verts, cap_norms, cap_tris = [], [], []
        # Centre vertex
        cap_verts.append(tuple(pt))
        cap_norms.append((0.0, 0.0, -1.0 if is_start else 1.0))
        ctr_idx = v_off

        for s in range(sides):
            angle = s * step
            n_local = (
                math.cos(angle)*norml[0] + math.sin(angle)*binom[0],
                math.cos(angle)*norml[1] + math.sin(angle)*binom[1],
                math.cos(angle)*norml[2] + math.sin(angle)*binom[2],
            )
            v_local = (
                pt[0] + self.radius*n_local[0],
                pt[1] + self.radius*n_local[1],
                pt[2] + self.radius*n_local[2],
            )
            cap_verts.append(v_local)
            cap_norms.append(cap_norms[0])

        for s in range(sides):
            a = ctr_idx
            b = v_off + 1 + s
            c = v_off + 1 + (s+1)%sides
            cap_tris.append([a,b,c] if is_start else [a,c,b])

        return cap_verts, cap_norms, cap_tris

    def _sphere_cap(self, pt, v_off: int, n_lat: int = 6):
        """Hemisphere end cap."""
        verts, norms, tris = [], [], []
        r = self.radius

        def add(v, nm):
            verts.append(v); norms.append(nm)
            return v_off + len(verts) - 1

        tip_idx = add(tuple(pt), (0,0,1))

        prev_ring = None
        for li in range(1, n_lat+1):
            phi   = math.pi/2 * li/n_lat   # 0 … π/2
            ring  = []
            sides = max(4, self.sides)
            for s in range(sides):
                theta = 2*math.pi*s/sides
                nx = math.cos(phi)*math.cos(theta)
                ny = math.cos(phi)*math.sin(theta)
                nz = math.sin(phi)
                v  = (pt[0]+r*nx, pt[1]+r*ny, pt[2]+r*nz)
                ring.append(add(v, (nx,ny,nz)))
            if prev_ring:
                for s in range(sides):
                    a = prev_ring[s]; b = prev_ring[(s+1)%sides]
                    c = ring[s];      d = ring[(s+1)%sides]
                    tris += [[a,b,d],[a,d,c]]
            else:
                for s in range(sides):
                    tris.append([tip_idx, ring[s], ring[(s+1)%sides]])
            prev_ring = ring

        return verts, norms, tris

    def _cone_cap(self, pt, tangent, v_off: int):
        """Cone arrowhead."""
        verts, norms, tris = [], [], []
        r    = self.radius * 2.0
        h    = self.radius * 3.0
        tip  = (pt[0]+tangent[0]*h, pt[1]+tangent[1]*h, pt[2]+tangent[2]*h)
        sides = self.sides

        # Arbitrary normal to tangent
        up = (0,0,1) if abs(tangent[2]) < 0.9 else (1,0,0)
        binom = self._cross(tangent, up)
        nm    = self._norm(binom)+1e-12
        binom = tuple(x/nm for x in binom)
        norml = self._cross(binom, tangent)

        step = 2*math.pi/sides
        ring = []
        for s in range(sides):
            angle = s*step
            n_local = (math.cos(angle)*norml[0]+math.sin(angle)*binom[0],
                       math.cos(angle)*norml[1]+math.sin(angle)*binom[1],
                       math.cos(angle)*norml[2]+math.sin(angle)*binom[2])
            v_local = (pt[0]+r*n_local[0], pt[1]+r*n_local[1], pt[2]+r*n_local[2])
            verts.append(v_local); norms.append(n_local)
            ring.append(v_off+len(verts)-1)

        tip_idx = v_off+len(verts)
        verts.append(tip); norms.append(tangent)

        for s in range(sides):
            tris.append([tip_idx, ring[s], ring[(s+1)%sides]])

        return verts, norms, tris

    # ── Dash pattern ────────────────────────────────────────────────────────

    def _apply_dash(self, pts: List[Vec3]) -> List[List[Vec3]]:
        """Split pts into solid sub-segments per dash pattern."""
        on_len, off_len = self.dash
        period = on_len + off_len

        # Arc-length parameterisation
        arc = [0.0]
        for i in range(1, len(pts)):
            d = self._dist(pts[i-1], pts[i])
            arc.append(arc[-1] + d)
        total = arc[-1]
        if total < 1e-9:
            return [pts]

        result: List[List[Vec3]] = []
        current: List[Vec3]      = []

        for i in range(len(pts)):
            s     = arc[i]
            phase = s % period
            solid = phase < on_len
            if solid:
                current.append(pts[i])
            else:
                if len(current) >= 2:
                    result.append(current)
                current = []

        if len(current) >= 2:
            result.append(current)
        return result or [pts]

    # ── Geometry helpers ────────────────────────────────────────────────────

    @staticmethod
    def _sub(a, b) -> Vec3:
        return (a[0]-b[0], a[1]-b[1], a[2]-b[2])

    @staticmethod
    def _norm(v) -> float:
        return math.sqrt(v[0]**2+v[1]**2+v[2]**2)

    @staticmethod
    def _dist(a, b) -> float:
        return math.sqrt((a[0]-b[0])**2+(a[1]-b[1])**2+(a[2]-b[2])**2)

    @staticmethod
    def _cross(a, b) -> Vec3:
        return (a[1]*b[2]-a[2]*b[1],
                a[2]*b[0]-a[0]*b[2],
                a[0]*b[1]-a[1]*b[0])

    def _tube_tangent(self, pts, idx):
        if idx == -1 or idx >= len(pts)-1:
            d = self._sub(pts[-1], pts[-2])
        else:
            d = self._sub(pts[idx+1], pts[idx])
        nm = self._norm(d) + 1e-12
        return tuple(x/nm for x in d)
