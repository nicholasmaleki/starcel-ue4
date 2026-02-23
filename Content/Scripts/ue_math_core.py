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
    Recursive midpoint refinement for smooth curves.
    Works on explicit y=f(x), parametric (x(t),y(t)), and 3D (x,y,z)(t).
    """

    def __init__(self,
                 zoom: float = 1.0,
                 tolerance: float = 0.01,
                 max_depth: int = 8,
                 debug: bool = False,
                 advanced_debug: bool = False):
        self.tol   = tolerance / max(zoom, 1e-6)
        self.depth = max_depth
        self.debug = debug
        self.adv   = advanced_debug

    # ── Explicit 2D: y = f(x) ───────────────────────────────────────────────

    def subdivide_explicit_2d(self,
                               fn: ScalarFn1,
                               x0: float, x1: float,
                               n: int = 128) -> List[CurveSegment]:
        """Returns segments; each segment is a continuous branch."""
        xs = np.linspace(x0, x1, n)
        raw = []
        for x in xs:
            try:
                y = float(fn(x))
                raw.append((x, y, True))
            except Exception:
                raw.append((x, 0.0, False))

        segments: List[CurveSegment] = []
        current:  List[CurvePoint]   = []

        def _refine(xa, ya, xb, yb, depth):
            if depth >= self.depth:
                return
            xm = (xa + xb) * 0.5
            try:
                ym = float(fn(xm))
            except Exception:
                return
            err = abs(ym - (ya + yb) * 0.5)
            if err < self.tol:
                return
            _refine(xa, ya, xm, ym, depth+1)
            current.append(CurvePoint(xm, ym))
            _refine(xm, ym, xb, yb, depth+1)

        for i in range(len(raw)-1):
            xa, ya, va = raw[i]
            xb, yb, vb = raw[i+1]
            if not va or not vb:
                if current:
                    segments.append(CurveSegment(list(current)))
                    current.clear()
                continue
            if not current:
                current.append(CurvePoint(xa, ya))
            _refine(xa, ya, xb, yb, 0)
            current.append(CurvePoint(xb, yb))

        if current:
            segments.append(CurveSegment(current))

        _adbg(f"explicit_2d: {len(segments)} segs, "
              f"{sum(len(s.points) for s in segments)} pts", self.adv)
        return segments

    # ── Parametric 3D: (x,y,z)(t) ───────────────────────────────────────────

    def subdivide_parametric_3d(self,
                                 fx, fy, fz,
                                 t0: float, t1: float,
                                 n: int = 128) -> List[CurveSegment]:
        ts   = np.linspace(t0, t1, n)
        raw  = []
        for t in ts:
            try:
                raw.append((float(fx(t)), float(fy(t)), float(fz(t)), True))
            except Exception:
                raw.append((0.0, 0.0, 0.0, False))

        valid = [p[:3] for p in raw if p[3]]
        if valid:
            arr  = np.array(valid)
            diag = np.linalg.norm(arr.max(0) - arr.min(0)) + 1e-12
            tol  = max(self.tol, 0.002 * diag)
        else:
            tol = self.tol

        segments: List[CurveSegment] = []
        current:  List[CurvePoint]   = []

        def _refine3(t_a, p_a, t_b, p_b, depth):
            if depth >= self.depth:
                return [p_a, p_b]
            tm = (t_a + t_b) * 0.5
            try:
                pm = (float(fx(tm)), float(fy(tm)), float(fz(tm)))
            except Exception:
                return [p_a, p_b]
            lin_m = tuple((p_a[i]+p_b[i])/2 for i in range(3))
            err   = math.sqrt(sum((pm[i]-lin_m[i])**2 for i in range(3)))
            if err < tol:
                return [p_a, p_b]
            L = _refine3(t_a, p_a, tm, pm, depth+1)
            R = _refine3(tm, pm, t_b, p_b, depth+1)
            return L[:-1] + R

        dt = (t1 - t0) / (n - 1)
        for i in range(len(raw)-1):
            x0,y0,z0,v0 = raw[i]
            x1,y1,z1,v1 = raw[i+1]
            if not v0 or not v1:
                if current:
                    segments.append(CurveSegment(list(current)))
                    current.clear()
                continue
            ta = t0 + i*dt
            tb = ta + dt
            refined = _refine3(ta, (x0,y0,z0), tb, (x1,y1,z1), 0)
            if not current:
                current.append(CurvePoint(*refined[0]))
            for p in refined[1:]:
                current.append(CurvePoint(*p))

        if current:
            segments.append(CurveSegment(current))

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
        with _timed("surface.explicit sample", self.adv):
            N  = self.res
            xs = np.linspace(x_range[0], x_range[1], N)
            ys = np.linspace(y_range[0], y_range[1], N)
            XX, YY = np.meshgrid(xs, ys)
            ZZ = np.zeros_like(XX)
            bad = 0
            for i in range(N):
                for j in range(N):
                    try:
                        ZZ[i, j] = float(fn(float(XX[i,j]), float(YY[i,j])))
                    except Exception:
                        ZZ[i, j] = 0.0
                        bad += 1

        _dbg(f"explicit surface {N}×{N}, {bad} eval errors", self.debug)

        verts, uvs = [], []
        for i in range(N):
            for j in range(N):
                verts.append([xs[j], ys[i], ZZ[i,j]])
                uvs.append([j/(N-1), i/(N-1)])

        verts_arr = np.array(verts)
        uvs_arr   = np.array(uvs)
        normals   = self._normals_grid(verts_arr, N, N)
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
            vol = np.zeros((N, N, N))
            for ix in range(N):
                for iy in range(N):
                    for iz in range(N):
                        try:
                            vol[ix,iy,iz] = fn(xs[ix], ys[iy], zs[iz])
                        except Exception:
                            vol[ix,iy,iz] = 0.0

        with _timed("marching_cubes mesh extraction", self.adv):
            verts_out, faces_out = self._march(vol - self.iso, xs, ys, zs)

        if not verts_out:
            _dbg("marching_cubes: no surface found", self.debug)
            return MeshData(np.zeros((1,3)), np.zeros((0,3),int), np.zeros((1,3)))

        va = np.array(verts_out)
        fa = np.array(faces_out, dtype=int)
        na = self._approx_normals(va, vol, xs, ys, zs)

        _dbg(f"marching_cubes: {len(va)} verts, {len(fa)} tris", self.debug)
        return MeshData(va, fa, na)

    def _march(self, vol, xs, ys, zs):
        """Iterate over all cubes and extract interface triangles."""
        # Edge table for the 256 cube configurations (simplified version)
        verts_out = []
        faces_out = []
        vert_idx: Dict[Tuple, int] = {}

        N = self.res

        def interp(p0, p1, v0, v1):
            if abs(v1 - v0) < 1e-9:
                return p0
            t = -v0 / (v1 - v0)
            return (p0[0]+t*(p1[0]-p0[0]),
                    p0[1]+t*(p1[1]-p0[1]),
                    p0[2]+t*(p1[2]-p0[2]))

        def get_or_add(pt):
            key = (round(pt[0],7), round(pt[1],7), round(pt[2],7))
            if key not in vert_idx:
                vert_idx[key] = len(verts_out)
                verts_out.append(pt)
            return vert_idx[key]

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
                    # Generate triangles from sign-change edges
                    edges = [
                        (0,1),(1,2),(2,3),(3,0),
                        (4,5),(5,6),(6,7),(7,4),
                        (0,4),(1,5),(2,6),(3,7),
                    ]
                    edge_pts = {}
                    for ei,(a,b) in enumerate(edges):
                        if (vals[a] >= 0) != (vals[b] >= 0):
                            edge_pts[ei] = interp(corners[a], corners[b],
                                                   vals[a], vals[b])
                    if len(edge_pts) >= 3:
                        ep_list = list(edge_pts.values())
                        n = len(ep_list)
                        c = tuple(sum(ep_list[i][k] for i in range(n))/n
                                  for k in range(3))
                        ci = get_or_add(c)
                        for i in range(n):
                            ia = get_or_add(ep_list[i])
                            ib = get_or_add(ep_list[(i+1)%n])
                            faces_out.append((ci, ia, ib))

        return verts_out, faces_out

    def _approx_normals(self, verts, vol, xs, ys, zs):
        N  = len(xs)
        normals = np.zeros_like(verts)
        for k, (x,y,z) in enumerate(verts):
            xi = int(np.clip((x-xs[0])/(xs[-1]-xs[0]+1e-12)*(N-1), 1, N-2))
            yi = int(np.clip((y-ys[0])/(ys[-1]-ys[0]+1e-12)*(N-1), 1, N-2))
            zi = int(np.clip((z-zs[0])/(zs[-1]-zs[0]+1e-12)*(N-1), 1, N-2))
            nx = vol[min(xi+1,N-1),yi,zi] - vol[max(xi-1,0),yi,zi]
            ny = vol[xi,min(yi+1,N-1),zi] - vol[xi,max(yi-1,0),zi]
            nz = vol[xi,yi,min(zi+1,N-1)] - vol[xi,yi,max(zi-1,0)]
            nm = math.sqrt(nx**2+ny**2+nz**2) + 1e-12
            normals[k] = [nx/nm, ny/nm, nz/nm]
        return normals


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
    """Runge-Kutta-4 integration of a vector field."""

    def __init__(self,
                 step_size: float = 0.05,
                 max_steps: int = 500,
                 bounds=None,
                 debug: bool = False,
                 advanced_debug: bool = False):
        self.step  = step_size
        self.max   = max_steps
        self.bounds = bounds   # ((x0,x1),(y0,y1),(z0,z1)) or None
        self.debug = debug
        self.adv   = advanced_debug

    def integrate_2d(self, F: VectorFn2, seed: Vec2) -> CurveSegment:
        pts = [CurvePoint(seed[0], seed[1])]
        x, y = float(seed[0]), float(seed[1])
        for _ in range(self.max):
            if self.bounds and not self._in_bounds_2d(x,y):
                break
            try:
                vx,vy = F(x,y)
            except Exception:
                break
            k1x,k1y = float(vx)*self.step, float(vy)*self.step
            try:
                vx2,vy2 = F(x+k1x/2, y+k1y/2)
            except Exception:
                break
            k2x,k2y = float(vx2)*self.step, float(vy2)*self.step
            x += k2x; y += k2y
            pts.append(CurvePoint(x, y))
        _dbg(f"integral_curve_2d: {len(pts)} pts", self.debug)
        return CurveSegment(pts)

    def integrate_3d(self, F: VectorFn3, seed) -> CurveSegment:
        pts = [CurvePoint(*seed[:3])]
        x,y,z = float(seed[0]),float(seed[1]),float(seed[2])
        for _ in range(self.max):
            if self.bounds and not self._in_bounds_3d(x,y,z):
                break
            try:
                vx,vy,vz = F(x,y,z)
            except Exception:
                break
            k1x,k1y,k1z = (float(vx)*self.step,
                             float(vy)*self.step,
                             float(vz)*self.step)
            try:
                vx2,vy2,vz2 = F(x+k1x/2, y+k1y/2, z+k1z/2)
            except Exception:
                break
            x+=float(vx2)*self.step; y+=float(vy2)*self.step; z+=float(vz2)*self.step
            pts.append(CurvePoint(x,y,z))
        _dbg(f"integral_curve_3d: {len(pts)} pts", self.debug)
        return CurveSegment(pts)

    def _in_bounds_2d(self, x, y):
        if not self.bounds: return True
        xb,yb = self.bounds[:2]
        return xb[0]<=x<=xb[1] and yb[0]<=y<=yb[1]

    def _in_bounds_3d(self, x, y, z):
        if not self.bounds: return True
        xb,yb,zb = self.bounds[:3]
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
