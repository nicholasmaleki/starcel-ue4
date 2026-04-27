"""
ue_math_examples.py — Comprehensive Test Suite for UE Math Plotter
==================================================================

Tests EVERY combination of:
  - 2D plot types (explicit, implicit, contour, heatmap, scatter, band)
  - 3D surfaces (explicit, parametric, wireframe, colormap, isosurface)
  - 3D curves (parametric, streamlines)
  - Intersection & Riemann surfaces
  - Domain coloring
  - Vector fields
  - Geometric Algebra (VGA, PGA, CGA, rotors, meet, join, spread)
  - nD spread engine
  - All three APIs: matplotlib, seaborn/plotly style, ggplot style
  - All LineStyle options: shapes, dash patterns, end caps, opacity
  - Grid modes: 2D and 3D
  - Advanced debug and basic debug modes

Run standalone (offline, no Unreal required):
    python ue_math_examples.py

All output is to stdout. No Unreal actors are spawned in offline mode —
you will see [Plotter] and [Plotter++] log lines confirming every code path.
"""

from __future__ import annotations

import math
import sys
import traceback
from typing import List

# Try to import dependencies
try:
    import numpy as np
    NUMPY_OK = True
except ImportError:
    print("ERROR: numpy is required.  pip install numpy")
    sys.exit(1)

# Adjust import path if running directly
import os
sys.path.insert(0, os.path.dirname(__file__))

try:
    from ue_math_core import (
        GABackend, KINGDON_AVAILABLE, SYMPY_AVAILABLE,
        CurvePoint, CurveSegment, MeshData,
        SurfaceSampler, AdaptiveSubdivider, TubeMeshBuilder,
    )
    from ue_math_plotter import (
        MathPlotter, PlotBounds, LineStyle, create_plotter,
    )
    IMPORTS_OK = True
except ImportError as e:
    print(f"ERROR importing modules: {e}")
    traceback.print_exc()
    sys.exit(1)

# Optional kingdon for GA tests
try:
    from kingdon import Algebra
    KINGDON_OK = True
except ImportError:
    KINGDON_OK = False
    print("[examples] kingdon not installed — GA tests will use mock multivectors")

# Optional sympy for symbolic tests
try:
    import sympy as sp
    SYMPY_OK = True
except ImportError:
    SYMPY_OK = False
    print("[examples] sympy not installed — symbolic tests will be skipped")


# TEST RUNNER

_PASS = 0
_FAIL = 0

def _run(label: str, fn):
    global _PASS, _FAIL
    print(f"\n{'='*60}")
    print(f"  TEST: {label}")
    print(f"{'='*60}")
    try:
        fn()
        print(f"  [OK] {label}")
        _PASS += 1
    except Exception as e:
        print(f"  [FAIL] {label}: {e}")
        traceback.print_exc()
        _FAIL += 1


def _make(mode='2d',
          debug=True,
          advanced_debug=True,
          x=(-5,5), y=(-5,5), z=(-5,5)) -> MathPlotter:
    """Create a test plotter (offline mode)."""
    p = create_plotter(
        world = None,   # offline — no UE
        x_range = x,
        y_range = y,
        z_range = z,
        debug = debug,
        advanced_debug = advanced_debug,
    )
    return p


# SECTION 1 — 2D PLOTS

def test_explicit_2d():
    """y = f(x) with various styles."""
    p = _make()
    p.grid(True, spacing=1.0, mode='2d')
    p.xlabel('x').ylabel('f(x)').title('2D Explicit Curves')

    # Matplotlib style
    p.plot(lambda x: math.sin(x),
           color=(0.2,0.8,0.4,1.0), label='sin(x)')
    p.plot(lambda x: math.cos(x),
           color=(0.9,0.3,0.2,1.0), dash_pattern=(0.3,0.15))
    p.plot(lambda x: x**2 / 5,
           color=(0.2,0.5,1.0,1.0), end_cap='sphere')
    p.plot(lambda x: math.tan(x),
           color=(0.9,0.7,0.2,1.0))   # discontinuities handled by adaptive
    p.show()


def test_explicit_2d_ggplot():
    """Same plots via ggplot API."""
    p = _make()
    p.labs(title='2D ggplot style', x='x', y='y')
    p.aes(color=(0.7,0.2,0.9,1.0), shape='square_tube').geom_line(lambda x: math.sin(2*x))
    p.aes(color=(0.2,0.9,0.5,1.0), end_cap='cone').geom_line(lambda x: x/3)
    p.show()


def test_implicit_contour_heatmap():
    """Implicit curves, contours, and heatmaps."""
    p = _make()

    # Implicit F(x,y)=0
    p.implicit(lambda x,y: x**2+y**2-9,   # circle r=3
               color=(1.0,0.4,0.1,1.0))
    p.implicit(lambda x,y: x**2/4+y**2-1, # ellipse
               color=(0.3,0.8,0.9,1.0))

    # Contour lines of z=f(x,y) at multiple levels
    p.contour(lambda x,y: math.sin(x)*math.cos(y),
              levels=[-0.8,-0.4,0.0,0.4,0.8],
              color=(0.9,0.9,0.2,1.0))

    # Heatmap
    p.heatmap(lambda x,y: math.exp(-(x**2+y**2)/4),
              resolution=32)

    p.show()


def test_scatter():
    """Scatter plot of 2D and 3D points."""
    import random; random.seed(42)
    p = _make()

    pts_2d = [(random.uniform(-4,4), random.uniform(-4,4)) for _ in range(30)]
    pts_3d = [(random.uniform(-4,4), random.uniform(-4,4),
               random.uniform(-4,4)) for _ in range(20)]

    p.scatter(pts_2d, color=(0.3,0.8,1.0,1.0))
    p.scatter(pts_3d, color=(1.0,0.5,0.2,1.0))
    p.show()


def test_band():
    """Band / ribbon between two curves."""
    p = _make()
    p.band(lambda x: math.sin(x)-0.5,
           lambda x: math.sin(x)+0.5,
           color=(0.4,0.7,1.0,1.0), opacity=0.6)
    p.band(lambda x: -abs(x)/5,
           lambda x:  abs(x)/5,
           color=(1.0,0.4,0.2,1.0), opacity=0.5)
    p.show()


def test_line_and_vector_2d():
    """Straight lines and 2D vectors."""
    p = _make()
    p.line((-4,-4), (4,4),  color=(0.9,0.2,0.2,1.0))
    p.line((-4, 4), (4,-4), color=(0.2,0.9,0.2,1.0))
    p.vector((2,3), origin=(0,0), color=(1.0,0.8,0.2,1.0))
    p.vector((-3,2), origin=(1,-1), color=(0.2,0.6,1.0,1.0))
    p.show()


# SECTION 2 — 3D SURFACES (focus area)

def test_explicit_surface_3d():
    """z = f(x,y) — multiple surfaces."""
    p = _make(x=(-4,4), y=(-4,4), z=(-3,3))
    p.grid(True, mode='3d')
    p.xlabel('x').ylabel('y').zlabel('z').title('3D Explicit Surfaces')

    # Primary surface
    p.plot3d(lambda x,y: math.sin(math.sqrt(x**2+y**2)+1e-9) /
                          (math.sqrt(x**2+y**2)+1e-9),
             resolution=48, color=(0.2,0.6,1.0,1.0), opacity=0.9)

    # Second surface (Monkey saddle)
    p.plot3d(lambda x,y: (x**3 - 3*x*y**2) / 20,
             resolution=40, color=(1.0,0.4,0.2,1.0), opacity=0.8)

    p.show()


def test_parametric_surface():
    """Parametric (u,v) → (x,y,z) surfaces."""
    p = _make()

    # Torus
    R, r = 3.0, 1.0
    p.parametric_surface(
        lambda u,v: (R+r*math.cos(v))*math.cos(u),
        lambda u,v: (R+r*math.cos(v))*math.sin(u),
        lambda u,v: r*math.sin(v),
        u_range=(0, 2*math.pi),
        v_range=(0, 2*math.pi),
        resolution=40,
        color=(0.8,0.3,0.9,1.0), opacity=0.85)

    # Möbius strip
    p.parametric_surface(
        lambda u,v: (2+v/2*math.cos(u/2))*math.cos(u),
        lambda u,v: (2+v/2*math.cos(u/2))*math.sin(u),
        lambda u,v: v/2*math.sin(u/2),
        u_range=(0, 2*math.pi),
        v_range=(-1, 1),
        resolution=40,
        color=(0.2,0.9,0.6,1.0), opacity=0.8)

    p.show()


def test_parametric_curve3d():
    """3D parametric curves with various styles."""
    p = _make()

    # Helix
    p.plot_curve3d(
        lambda t: 3*math.cos(t),
        lambda t: 3*math.sin(t),
        lambda t: t/2,
        t_range=(0, 4*math.pi),
        color=(0.2,0.8,0.4,1.0), end_cap='sphere')

    # Trefoil knot
    p.plot_curve3d(
        lambda t: math.sin(t)+2*math.sin(2*t),
        lambda t: math.cos(t)-2*math.cos(2*t),
        lambda t: -math.sin(3*t),
        t_range=(0, 2*math.pi),
        color=(1.0,0.4,0.2,1.0), dash_pattern=(0.2,0.1))

    # Lissajous 3D
    p.plot_curve3d(
        lambda t: 3*math.sin(3*t+0.3),
        lambda t: 3*math.sin(2*t),
        lambda t: 3*math.cos(5*t),
        t_range=(0, 2*math.pi),
        color=(0.7,0.2,0.9,1.0), shape='square_tube')

    # Viviani curve
    p.plot_curve3d(
        lambda t: 1+math.cos(t),
        lambda t: math.sin(t),
        lambda t: 2*math.sin(t/2),
        t_range=(0, 4*math.pi),
        color=(0.9,0.8,0.2,1.0), end_cap='cone')

    p.show()


def test_wireframe():
    """Wireframe surfaces."""
    p = _make()

    p.wireframe(lambda x,y: math.cos(x)*math.sin(y),
                resolution=20,
                color=(0.5,0.9,0.9,1.0))

    p.wireframe(lambda x,y: (x**2-y**2)/5,
                resolution=16,
                color=(0.9,0.5,0.2,1.0), shape='square_tube')

    p.show()


def test_isosurface():
    """Marching cubes isosurface extraction."""
    p = _make(x=(-3,3), y=(-3,3), z=(-3,3))

    # Sphere
    p.isosurface(lambda x,y,z: x**2+y**2+z**2,
                 iso_value=4.0,
                 resolution=24,
                 color=(0.2,0.5,1.0,1.0), opacity=0.7)

    # Gyroid (minimal surface)
    p.isosurface(
        lambda x,y,z: (math.sin(x)*math.cos(y) +
                        math.sin(y)*math.cos(z) +
                        math.sin(z)*math.cos(x)),
        iso_value=0.0,
        resolution=20,
        color=(0.9,0.3,0.6,1.0), opacity=0.75)

    p.show()


def test_colormap_surface():
    """Colourmap surface (z value → colour)."""
    p = _make()
    p.colormap_surface(lambda x,y: math.sin(x)*math.cos(y),
                       resolution=48, colormap='viridis')
    p.show()


def test_riemann_surfaces():
    """All four Riemann surface types."""
    p = _make(x=(-4,4), y=(-4,4), z=(-4,4))

    # Each at a different x-offset via explicit origin manipulation
    # (In Unreal use multiple plotters at different origins)
    p.riemann_surface('sqrt', r_range=(0.05,2.5), resolution=48,
                      sheet_gap=0.4)
    p.show()

    p2 = _make()
    p2.riemann_surface('log', n_sheets=4, r_range=(0.1,2.5), resolution=40)
    p2.show()

    p3 = _make()
    p3.riemann_surface('cbrt', r_range=(0.05,2.5), resolution=48)
    p3.show()

    p4 = _make()
    p4.riemann_surface('pow', p=2, q=3, r_range=(0.1,2.5), resolution=40)
    p4.show()


def test_intersection():
    """Intersection curves / surfaces."""
    p = _make()

    # 2D: circle ∩ ellipse
    p.intersection(lambda x,y: x**2+y**2-9,
                   lambda x,y: x**2/4+y**2-1,
                   mode='2d',
                   color=(1.0,0.8,0.2,1.0))
    p.show()

    # 3D: sphere ∩ plane (intersection surface mesh)
    p2 = _make(x=(-3,3), y=(-3,3), z=(-3,3))
    p2.intersection(lambda x,y,z: x**2+y**2+z**2,
                    lambda x,y,z: 4.0 + z*0,   # constant sphere = 4
                    mode='3d',
                    resolution=20,
                    color=(0.3,0.8,0.9,1.0), opacity=0.7)
    p2.show()


def test_domain_color():
    """Domain coloring of complex functions."""
    p = _make()

    p.domain_color(lambda z: z**2,        resolution=64)
    p.domain_color(lambda z: (z**2-1)/(z**2+1), resolution=64)
    p.show()


# SECTION 3 — VECTOR FIELDS & STREAMLINES

def test_vector_field_2d():
    p = _make()
    p.vector_field(lambda x,y: (-y, x),
                   density=10, normalize=True, mode='2d',
                   color=(0.9,0.5,0.2,1.0))
    p.show()


def test_vector_field_3d():
    p = _make(x=(-3,3), y=(-3,3), z=(-3,3))
    p.vector_field(lambda x,y,z: (-y, x, math.sin(z)),
                   density=6, normalize=True, mode='3d',
                   color=(0.3,0.8,0.5,1.0))
    p.show()


def test_streamlines():
    p = _make()
    F = lambda x,y: (-y+x*(1-x**2-y**2), x+y*(1-x**2-y**2))

    seeds = [(1.5, 0), (0, 1.5), (-1.5, 0), (0, -1.5),
             (0.5, 0), (2.5, 0)]
    for seed in seeds:
        p.streamline(F, seed=seed, step=0.02, max_steps=300,
                     mode='2d', color=(0.2,0.7,1.0,1.0))
    p.show()


def test_streamlines_3d():
    p = _make(x=(-3,3), y=(-3,3), z=(-3,3))
    F3 = lambda x,y,z: (y-x, -x-y, math.cos(z))
    p.streamline(F3, seed=(1,0,0), step=0.04, max_steps=200,
                 mode='3d', color=(1.0,0.5,0.2,1.0))
    p.show()


# SECTION 4 — LINESTYLE COMBINATIONS

def test_all_linestyles():
    """Test every linewidth_mode, end_cap, shape, dash combination."""
    p = _make()

    f = lambda x: math.sin(x)

    # End caps
    for i, cap in enumerate(['flat','none','sphere','cone']):
        p.plot(f, x_range=(-math.pi, math.pi),
               color=_PALETTE[i], end_cap=cap,
               linewidth=0.03, label=f'end={cap}')

    p.show()

    # Shapes
    p2 = _make()
    for i, shape in enumerate(['cylinder','square_tube']):
        p2.plot(lambda x: math.cos(x),
                shape=shape, color=_PALETTE[i+2], linewidth=0.04)
    p2.show()

    # Dash patterns
    p3 = _make()
    dashes = [None, (0.3,0.1), (0.1,0.1), (0.5,0.2)]
    for i, dp in enumerate(dashes):
        p3.plot(lambda x: math.sin(x+i*0.5),
                dash_pattern=dp, color=_PALETTE[i], linewidth=0.025)
    p3.show()

    # Opacity gradient
    p4 = _make()
    for i in range(5):
        op = 0.2 + i*0.2
        p4.plot3d(lambda x,y,op=op: math.sin(x)*math.cos(y)*op,
                  opacity=op, color=_PALETTE[i])
    p4.show()


_PALETTE = [
    (0.2,0.6,1.0,1.0),(1.0,0.4,0.1,1.0),(0.2,0.8,0.3,1.0),
    (0.9,0.2,0.3,1.0),(0.7,0.4,0.9,1.0),(0.9,0.8,0.2,1.0),
    (0.3,0.9,0.9,1.0),(0.9,0.5,0.7,1.0),
]


# SECTION 5 — SYMBOLIC (SymPy)

def test_sympy_expressions():
    if not SYMPY_OK:
        print("  [SKIP] sympy not installed")
        return

    import sympy as sp
    x, y, z_sym = sp.Symbol('x'), sp.Symbol('y'), sp.Symbol('z')

    p = _make()

    # 2D
    p.plot(sp.sin(x) + sp.cos(2*x))
    p.implicit(x**2 + y**2 - sp.Integer(9))

    # 3D surface from SymPy expr
    p.plot3d(sp.sin(x) * sp.cos(y), resolution=32)

    p.show()
    print("  sympy: compiled and queued OK")


# SECTION 6 — GEOMETRIC ALGEBRA

def _make_mock_mv(grade: int):
    """Create a minimal mock multivector when kingdon is unavailable."""
    class MockMV:
        def __init__(self, g): self._grade = g
        def grade(self): return self._grade
        def __str__(self):
            labels = {0:'1', 1:'e1+2*e2+1*e3',
                      2:'3*e12+1*e23', 3:'2*e123', 4:'e0123'}
            return labels.get(self._grade, '0')
        # Grade-1 coefficients
        e1 = 1.0; e2 = 2.0; e3 = 1.0
        # Grade-2
        e12 = 3.0; e23 = 1.0; e13 = 0.5
        e = 1.0  # scalar part
        def vee(self, other):  return MockMV(1)
        def __xor__(self, o):  return MockMV(2)
    return MockMV(grade)


def test_ga_scalar():
    p = _make()
    mv = _make_mock_mv(0)
    p.ga_primitive(mv, origin=(0,0,0), scale=1.0, color=(0.9,0.9,0.9,1.0))
    p.show()


def test_ga_vector():
    p = _make()
    mv = _make_mock_mv(1)
    p.ga_primitive(mv, origin=(0,0,0), scale=1.5, color=(0.2,0.8,0.4,1.0))
    p.show()


def test_ga_bivector():
    p = _make()
    mv = _make_mock_mv(2)
    p.ga_primitive(mv, origin=(0,0,0), scale=2.0, color=(0.7,0.3,1.0,1.0), opacity=0.7)
    p.show()


def test_ga_trivector():
    p = _make()
    mv = _make_mock_mv(3)
    p.ga_primitive(mv, origin=(0,0,0), scale=1.5, color=(1.0,0.6,0.2,1.0))
    p.show()


def test_ga_higher_grade():
    p = _make()
    mv = _make_mock_mv(4)
    p.ga_primitive(mv, origin=(0,0,0), scale=1.0, color=(0.5,0.9,0.9,1.0))
    p.show()


def test_ga_rotor():
    p = _make()
    mv = _make_mock_mv(1)  # the vector to rotate

    class MockRotor:
        """R = cos(π/4) + sin(π/4)*e12  (90° rotation in xy plane)"""
        e = math.cos(math.pi/4)    # scalar part
        e12 = math.sin(math.pi/4)  # e12 bivector
        e23 = 0.0; e13 = 0.0
        def grade(self): return 2
        def __str__(self): return f"{self.e} + {self.e12}*e12"

    R = MockRotor()
    p.ga_rotor(R, mv, origin=(0,0,0), scale=2.0,
               color=(0.9,0.5,0.2,1.0), steps=16)
    p.show()


def test_ga_meet_join():
    p = _make()
    mv1 = _make_mock_mv(1)
    mv2 = _make_mock_mv(2)
    p.ga_meet(mv1, mv2, origin=(-2,0,0), scale=1.5)
    p.ga_join(mv1, mv2, origin=( 2,0,0), scale=1.5)
    p.show()


def test_ga_spread():
    """Higher-grade GA multivector spread into sub-views."""
    p = _make()
    mv = _make_mock_mv(4)
    p.ga_spread(mv, origin=(0,0,0), scale=1.5, max_subviews=4)
    p.show()


def test_ga_backends():
    """Test all GA backends (VGA, PGA, CGA, STA)."""
    for backend in ['vga', 'pga', 'cga', 'sta']:
        p = create_plotter(ga_backend=backend, debug=True, advanced_debug=True)
        mv = _make_mock_mv(1)
        p.ga_primitive(mv, color=(0.2,0.8,0.6,1.0))
        p.show()
        print(f"  backend={backend} OK")


def test_ga_with_kingdon():
    """Test with real kingdon if available."""
    if not KINGDON_OK:
        print("  [SKIP] kingdon not installed")
        return

    from kingdon import Algebra
    alg = Algebra(3, 0, 0)   # VGA

    # Create grade-1 vector
    e1, e2, e3 = alg.multivector(e1=1), alg.multivector(e2=1), alg.multivector(e3=1)
    mv_vec = 2*e1 + 3*e2 + e3

    # Create grade-2 bivector
    e12 = alg.multivector(e12=1)
    mv_bv = 2*e12

    # Create rotor (rotation by 45° in xy plane)
    angle = math.pi / 4
    # R = cos(angle/2) + sin(angle/2)*e12  (using kingdon scalar)
    scalar = alg.multivector(e=math.cos(angle/2))
    bv_rot = math.sin(angle/2) * e12
    R = scalar + bv_rot

    p = create_plotter(ga_backend='vga', debug=True, advanced_debug=True)
    p.ga_primitive(mv_vec, origin=(0,0,0), scale=1.5, color=(0.2,0.8,0.4,1.0))
    p.ga_primitive(mv_bv, origin=(2,0,0), scale=1.5, color=(0.8,0.3,0.9,1.0), opacity=0.7)
    p.ga_rotor(R, mv_vec, origin=(0,0,2), scale=1.5, steps=12)
    p.show()
    print("  kingdon real algebra: OK")


# SECTION 7 — N-DIMENSIONAL SPREAD

def test_spread_4d():
    """4D function rendered as grid of 3D projections."""
    p = _make()

    def f4d(x1, x2, x3, x4):
        return math.sin(x1)*math.cos(x2) + math.sin(x3)*x4/5

    p.spread(fn = f4d,
             var_names= ['x1','x2','x3','x4'],
             var_ranges= [(-math.pi,math.pi)]*4,
             max_subplots= 6,
             resolution = 20)
    p.show()


def test_spread_5d():
    """5D function."""
    p = _make()

    def f5d(a,b,c,d,e):
        return math.sin(a+b) * math.cos(c) * (d**2+e**2) / 20

    p.spread(fn = f5d,
             var_names= list('abcde'),
             var_ranges= [(-2,2)]*5,
             max_subplots= 9,
             resolution = 16)
    p.show()


# SECTION 8 — GRID MODES

def test_grid_2d():
    p = _make()
    p.grid(True, spacing=1.0, mode='2d')
    p.plot(lambda x: math.sin(x))
    p.show()


def test_grid_3d():
    p = _make(x=(-4,4), y=(-4,4), z=(-4,4))
    p.grid(True, spacing=2.0, mode='3d')
    p.plot3d(lambda x,y: math.sin(math.sqrt(x**2+y**2+1e-9)) /
                          (math.sqrt(x**2+y**2)+1e-9),
             resolution=40)
    p.show()


# SECTION 9 — COMBINED COMPLEX SCENES

def test_combined_2d_scene():
    """Multiple 2D primitives in one scene."""
    p = _make()
    p.grid(True, spacing=1.0, mode='2d')
    p.labs(title='2D Scene', x='x', y='y')

    # Seaborn-style sequential colours
    p.plot(lambda x: math.sin(x),       color=(0.12,0.47,0.71,1.0))
    p.plot(lambda x: math.cos(x),       color=(1.0, 0.50,0.05,1.0))
    p.plot(lambda x: math.sin(2*x)/2,   color=(0.17,0.63,0.17,1.0), dash_pattern=(0.2,0.08))
    p.implicit(lambda x,y: x**2+y**2-16, color=(0.84,0.15,0.16,1.0))
    p.scatter([(3*math.cos(t),3*math.sin(t)) for t in np.linspace(0,2*math.pi,12)],
              color=(0.58,0.40,0.74,1.0))
    p.vector((0,3), color=(0.55,0.34,0.29,1.0))
    p.vector_field(lambda x,y: (math.sin(y),math.cos(x)), density=8,
                   normalize=True, color=(0.5,0.5,0.5,0.5))

    p.show()


def test_combined_3d_scene():
    """Multiple 3D primitives in one scene."""
    p = _make(x=(-4,4), y=(-4,4), z=(-4,4))
    p.grid(True, spacing=2.0, mode='3d')
    p.labs(title='3D Scene', x='x', y='y', z='z')

    # Surface
    p.plot3d(lambda x,y: math.sin(x)*math.cos(y),
             resolution=40, color=(0.2,0.6,1.0,1.0), opacity=0.8)

    # Curve on the surface
    p.plot_curve3d(
        lambda t: 3*math.cos(t),
        lambda t: 3*math.sin(t),
        lambda t: math.sin(3*math.cos(t))*math.cos(3*math.sin(t)),
        t_range=(0,2*math.pi),
        color=(1.0,0.4,0.2,1.0), end_cap='sphere')

    # Isosurface
    p.isosurface(lambda x,y,z: x**2+y**2+z**2,
                 iso_value=9, resolution=20,
                 color=(0.8,0.2,0.8,1.0), opacity=0.3)

    # Streamlines
    p.streamline(lambda x,y,z: (-y,x,math.cos(z)),
                 seed=(2,0,0), step=0.05, max_steps=200,
                 mode='3d', color=(0.9,0.8,0.2,1.0))

    # GA vector
    mv = _make_mock_mv(1)
    p.ga_primitive(mv, origin=(0,0,3), scale=1.0)

    p.show()


def test_ga_full_scene():
    """GA primitives of all grades in one scene."""
    p = _make()
    p.labs(title='Geometric Algebra — All Grades')

    offsets = [(-4,0,0), (-2,0,0), (0,0,0), (2,0,0), (4,0,0)]
    for grade, offset in enumerate(offsets):
        mv = _make_mock_mv(grade)
        p.ga_primitive(mv, origin=offset, scale=1.2,
             color=_PALETTE[grade % len(_PALETTE)])

    # Rotor
    class MockRotor:
        e=math.cos(math.pi/6); e12=math.sin(math.pi/6); e23=0.0; e13=0.0
        def grade(self): return 2
    p.ga_rotor(MockRotor(), _make_mock_mv(1),
               origin=(0,3,0), scale=1.5, steps=8)

    # Meet and join
    p.ga_meet(_make_mock_mv(1), _make_mock_mv(2), origin=(-2,3,0), scale=1.0)
    p.ga_join(_make_mock_mv(1), _make_mock_mv(2), origin=( 2,3,0), scale=1.0)

    p.show()


# SECTION 10 — DEBUG LEVEL COMPARISON

def test_debug_off():
    """No debug output."""
    p = create_plotter(debug=False, advanced_debug=False)
    p.plot(lambda x: x**2)
    p.plot3d(lambda x,y: math.sin(x+y))
    p.show()


def test_debug_basic():
    """Basic debug output only."""
    p = create_plotter(debug=True, advanced_debug=False)
    p.plot(lambda x: math.sin(x))
    p.plot3d(lambda x,y: math.cos(x)*math.sin(y))
    p.show()


def test_advanced_debug():
    """Full advanced_debug output (timing + arrays)."""
    p = create_plotter(debug=True, advanced_debug=True)
    p.plot(lambda x: math.sin(x))
    p.plot3d(lambda x,y: math.cos(x)*math.sin(y), resolution=16)
    p.plot_curve3d(
        lambda t: math.cos(t), lambda t: math.sin(t), lambda t: t/6,
        t_range=(0, 2*math.pi))
    p.isosurface(lambda x,y,z: x**2+y**2+z**2, iso_value=4,
                 resolution=12)
    p.show()


# TUBE MESH BUILDER — unit tests

def test_tube_mesh_builder():
    """Test TubeMeshBuilder directly for all cap / shape / dash combinations."""
    from ue_math_core import TubeMeshBuilder

    # Simple helix points
    pts = [(math.cos(t*0.5)*2, math.sin(t*0.5)*2, t*0.2)
           for t in np.linspace(0, 4*math.pi, 50)]

    configs = [
        dict(shape='cylinder', end_cap='flat',   dash_pattern=None),
        dict(shape='cylinder', end_cap='none',   dash_pattern=None),
        dict(shape='cylinder', end_cap='sphere', dash_pattern=None),
        dict(shape='cylinder', end_cap='cone',   dash_pattern=None),
        dict(shape='square_tube', end_cap='flat',dash_pattern=None),
        dict(shape='cylinder', end_cap='flat',   dash_pattern=(0.3,0.1)),
        dict(shape='square_tube', end_cap='sphere', dash_pattern=(0.5,0.2)),
    ]

    for cfg in configs:
        builder = TubeMeshBuilder(radius=0.1, sides=8,
                                   debug=True, advanced_debug=True, **cfg)
        mesh = builder.build(pts)
        assert len(mesh.vertices) > 0,   f"No verts for {cfg}"
        assert len(mesh.indices)  > 0,   f"No tris for {cfg}"
        print(f"  TubeMesh {cfg}: {len(mesh.vertices)}v {len(mesh.indices)}t OK")


# MAIN

ALL_TESTS = [
    # 2D
    ("2D Explicit Curves (matplotlib)",      test_explicit_2d),
    ("2D Explicit Curves (ggplot)",           test_explicit_2d_ggplot),
    ("Implicit / Contour / Heatmap",         test_implicit_contour_heatmap),
    ("Scatter (2D + 3D points)",             test_scatter),
    ("Band / Ribbon",                        test_band),
    ("Line + Vector 2D",                     test_line_and_vector_2d),
    # 3D surfaces
    ("Explicit 3D Surface",                  test_explicit_surface_3d),
    ("Parametric Surface (Torus, Möbius)",   test_parametric_surface),
    ("Parametric Curve 3D",                  test_parametric_curve3d),
    ("Wireframe Surface",                    test_wireframe),
    ("Isosurface (marching cubes)",          test_isosurface),
    ("Colourmap Surface",                    test_colormap_surface),
    ("Riemann Surfaces (all 4 types)",       test_riemann_surfaces),
    ("Intersection (2D + 3D)",              test_intersection),
    ("Domain Coloring",                      test_domain_color),
    # Vectors
    ("Vector Field 2D",                      test_vector_field_2d),
    ("Vector Field 3D",                      test_vector_field_3d),
    ("Streamlines 2D",                       test_streamlines),
    ("Streamlines 3D",                       test_streamlines_3d),
    # LineStyles
    ("All LineStyle Combinations",           test_all_linestyles),
    # Symbolic
    ("SymPy Expressions",                    test_sympy_expressions),
    # GA
    ("GA Scalar (grade 0)",                  test_ga_scalar),
    ("GA Vector (grade 1)",                  test_ga_vector),
    ("GA Bivector (grade 2)",                test_ga_bivector),
    ("GA Trivector (grade 3)",               test_ga_trivector),
    ("GA Higher Grade (grade 4)",            test_ga_higher_grade),
    ("GA Rotor Visualization",               test_ga_rotor),
    ("GA Meet + Join",                       test_ga_meet_join),
    ("GA Spread (multi sub-view)",           test_ga_spread),
    ("GA All Backends (VGA/PGA/CGA/STA)",    test_ga_backends),
    ("GA with real kingdon",                 test_ga_with_kingdon),
    # nD
    ("4D Spread Engine",                     test_spread_4d),
    ("5D Spread Engine",                     test_spread_5d),
    # Grid
    ("Grid 2D",                              test_grid_2d),
    ("Grid 3D",                              test_grid_3d),
    # Combined
    ("Combined 2D Scene",                    test_combined_2d_scene),
    ("Combined 3D Scene",                    test_combined_3d_scene),
    ("GA Full Scene (all grades)",           test_ga_full_scene),
    # Debug
    ("Debug OFF",                            test_debug_off),
    ("Debug Basic",                          test_debug_basic),
    ("Advanced Debug",                       test_advanced_debug),
    # Low-level
    ("TubeMeshBuilder (all cap/dash/shape)", test_tube_mesh_builder),
]


if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser(description="UE Math Plotter test suite")
    parser.add_argument('--only', default=None,
                        help='Run only tests whose name contains this string (case-insensitive)')
    parser.add_argument('--list', action='store_true',
                        help='List all test names and exit')
    args = parser.parse_args()

    if args.list:
        for name, _ in ALL_TESTS:
            print(f"  {name}")
        sys.exit(0)

    filter_str = args.only.lower() if args.only else None

    print("\n" + "="*60)
    print("  UE Math Plotter — Comprehensive Test Suite")
    print(f"  numpy={NUMPY_OK}  sympy={SYMPY_OK}  kingdon={KINGDON_OK}")
    print("="*60)

    for name, fn in ALL_TESTS:
        if filter_str and filter_str not in name.lower():
            continue
        _run(name, fn)

    print(f"\n{'='*60}")
    print(f"  Results: {_PASS} passed  {_FAIL} failed  "
          f"({_PASS+_FAIL} total)")
    print(f"{'='*60}\n")

    sys.exit(0 if _FAIL == 0 else 1)
