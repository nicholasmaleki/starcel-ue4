"""
ue_math_plotter.py — Unified Math Plotter for Unreal Engine 4.27
================================================================

Single file covering 2D → 3D → nD plots with full Geometric Algebra support.

APIs (all equivalent, all work side by side):
─────────────────────────────────────────────
Matplotlib / Seaborn style:
    p.plot(f)                       # y=f(x) curve
    p.plot3d(f)                     # z=f(x,y) surface
    p.parametric_surface(fx,fy,fz)  # (u,v) → (x,y,z) surface
    p.plot_curve3d(fx,fy,fz)        # (t) → (x,y,z) curve
    p.scatter(points)
    p.line(p1, p2)
    p.vector(v, origin)
    p.vector_field(F)
    p.streamline(F, seed)           # integral curve
    p.implicit(F)                   # F(x,y)=0 contour
    p.isosurface(F, iso=0)          # F(x,y,z)=iso mesh
    p.intersection(F1, F2)          # where F1=F2
    p.riemann_surface(kind)         # multi-sheet complex surface
    p.domain_color(f)               # complex domain coloring
    p.colormap_surface(f)           # surface coloured by f value
    p.band(f_lo, f_hi)              # ribbon between two curves
    p.wireframe(f)                  # wireframe surface
    p.heatmap(f)                    # 2D scalar field as coloured mesh
    p.contour(f, levels)            # contour lines
    p.spread(fn, var_names, ranges) # nD function as grid of 3D projections

ggplot / Grammar of Graphics style:
    p.geom_line(f)          → p.plot(f)
    p.geom_surface(f)       → p.plot3d(f)
    p.geom_path3d(fx,fy,fz) → p.plot_curve3d(fx,fy,fz)
    p.geom_point(pts)       → p.scatter(pts)
    p.geom_ribbon(flo,fhi)  → p.band(flo, fhi)
    p.geom_abline(p1,p2)    → p.line(p1, p2)
    p.geom_vector(v,o)      → p.vector(v, o)
    p.geom_contour(f)       → p.contour(f)
    p.geom_isosurface(f)    → p.isosurface(f)
    p.aes(**kw)             → set next-primitive style
    p.labs(title,x,y,z)    → set all axis labels

Geometric Algebra (kingdon):
    p.ga(mv)                        # auto-detect grade, render accordingly
    p.ga_rotor(R, target_mv)        # visualise rotor action on multivector
    p.ga_meet(mv1, mv2)             # meet (intersection)
    p.ga_join(mv1, mv2)             # join (span)
    p.ga_spread(mv, axes_pairs)     # nD GA → multiple 3D sub-views

Axes / decoration:
    p.grid(True, spacing, mode='2d'|'3d')
    p.title(t) / p.xlabel(x) / p.ylabel(y) / p.zlabel(z)
    p.xlim(lo,hi) / p.ylim(lo,hi) / p.zlim(lo,hi)

LineStyle kwargs (pass to any draw method):
    color=(r,g,b,a)
    linewidth=0.02              # fraction of x-domain width (default)
    linewidth_mode='domain'     # 'domain' | 'absolute'
    opacity=0.9                 # < 1.0 → translucent material
    shape='cylinder'            # 'cylinder' | 'square_tube'
    dash_pattern=(on, off)      # e.g. (0.3,0.15) in math units; None=solid
    end_cap='flat'              # 'flat'|'none'|'sphere'|'cone'
    circle_res=10               # sides for cylinder cross-section
    label=''

Debug:
    debug=True                  # [Plotter] summary per operation
    advanced_debug=True         # [Plotter++] full arrays, timing, GA tables
"""

from __future__ import annotations

import math
import traceback
import time
from dataclasses import dataclass, field
from typing import Any, Callable, Dict, List, Optional, Tuple, Union

import numpy as np

from ue_math_core import (
    # Data structures
    CurvePoint, CurveSegment, MeshData, Arrow, Vec2, Vec3,
    # Math layers
    SymbolicCompiler, AdaptiveSubdivider, SurfaceSampler,
    MarchingCubes, IntersectionFinder, RiemannSurfaceBuilder,
    VectorFieldSampler, IntegralCurveSolver, DomainColorizer,
    # GA
    GABackend, KINGDON_AVAILABLE,
    # High-dimensional
    SpreadEngine,
    # Tube mesh
    TubeMeshBuilder,
    # Debug helpers (re-used)
    _dbg, _adbg, _timed,
)

# ── Optional SymPy ────────────────────────────────────────────────────────────
try:
    import sympy as _sp
    SYMPY_AVAILABLE = True
except ImportError:
    SYMPY_AVAILABLE = False

# ── Unreal Engine imports (guarded so the file works offline) ─────────────────
try:
    import unreal_engine as ue
    from unreal_engine import FVector, FRotator, FLinearColor
    from unreal_engine.classes import (
        Actor, StaticMeshActor, StaticMesh,
        ProceduralMeshComponent, TextRenderComponent,
    )
    UE_AVAILABLE = True
except ImportError:
    UE_AVAILABLE = False
    class FVector:
        def __init__(self, x=0, y=0, z=0): self.x,self.y,self.z = x,y,z
        def __repr__(self): return f"FVector({self.x:.2f},{self.y:.2f},{self.z:.2f})"
    class FRotator:
        def __init__(self, p=0, y=0, r=0): pass
    class FLinearColor:
        def __init__(self, r=0, g=0, b=0, a=1): pass
    class Actor: pass
    class StaticMeshActor: pass
    class StaticMesh: pass
    class ProceduralMeshComponent: pass
    class TextRenderComponent: pass

_P  = "[Plotter]  "
_PA = "[Plotter++]"

_PALETTE = [
    (0.2, 0.6, 1.0, 1.0),   # blue
    (1.0, 0.4, 0.1, 1.0),   # orange
    (0.2, 0.8, 0.3, 1.0),   # green
    (0.9, 0.2, 0.3, 1.0),   # red
    (0.7, 0.4, 0.9, 1.0),   # purple
    (0.9, 0.8, 0.2, 1.0),   # yellow
    (0.3, 0.9, 0.9, 1.0),   # cyan
    (0.9, 0.5, 0.7, 1.0),   # pink
]


# ============================================================================
# LINE STYLE
# ============================================================================

@dataclass
class LineStyle:
    color:          Tuple[float,float,float,float] = (1.0, 0.4, 0.1, 1.0)
    linewidth:      float = 0.02
    linewidth_mode: str   = 'domain'   # 'domain' | 'absolute'
    opacity:        float = 1.0
    shape:          str   = 'cylinder' # 'cylinder' | 'square_tube'
    dash_pattern:   Optional[Tuple[float,float]] = None
    end_cap:        str   = 'flat'     # 'flat'|'none'|'sphere'|'cone'
    circle_res:     int   = 10
    label:          str   = ''
    translucent_material: str = '/Game/Materials/M_Color_Translucent.M_Color_Translucent'

    @staticmethod
    def from_palette(index: int, **overrides) -> 'LineStyle':
        s = LineStyle(color=_PALETTE[index % len(_PALETTE)])
        for k, v in overrides.items():
            setattr(s, k, v)
        return s

    def resolved_radius(self, x_span: float) -> float:
        if self.linewidth_mode == 'domain':
            return self.linewidth * x_span * 0.5
        return self.linewidth


# ============================================================================
# PLOT BOUNDS
# ============================================================================

@dataclass
class PlotBounds:
    x_range:      Vec2  = (-5.0, 5.0)
    y_range:      Vec2  = (-5.0, 5.0)
    z_range:      Vec2  = (-5.0, 5.0)
    units_per_uu: float = 100.0

    def to_uu(self, x: float, y: float, z: float = 0.0) -> FVector:
        return FVector(x*self.units_per_uu,
                       y*self.units_per_uu,
                       z*self.units_per_uu)

    @property
    def x_span(self) -> float:
        return self.x_range[1] - self.x_range[0]

    @property
    def y_span(self) -> float:
        return self.y_range[1] - self.y_range[0]

    @property
    def z_span(self) -> float:
        return self.z_range[1] - self.z_range[0]

    def in_bounds_3d(self, x, y, z) -> bool:
        return (self.x_range[0]<=x<=self.x_range[1] and
                self.y_range[0]<=y<=self.y_range[1] and
                self.z_range[0]<=z<=self.z_range[1])


# ============================================================================
# UNREAL ACTOR FACTORY
# ============================================================================

class UnrealActorFactory:
    """
    Low-level Unreal spawning. All UE API calls live here.
    Every method is a no-op (with a print) when UE is not available.
    """

    TRANSLUCENT_MATERIAL = '/Game/Materials/M_Color_Translucent.M_Color_Translucent'

    def __init__(self,
                 world,
                 origin: FVector = None,
                 debug: bool = False,
                 advanced_debug: bool = False):
        self.world   = world
        self.origin  = origin or FVector(0,0,0)
        self._spawned: List[Any] = []
        self.debug   = debug
        self.adv     = advanced_debug

    # ── Cylinder segment (primitive line) ────────────────────────────────────

    def spawn_cylinder(self,
                       p0: FVector, p1: FVector,
                       radius: float,
                       color: Tuple) -> Optional[Any]:
        if not UE_AVAILABLE or not self.world:
            _adbg(f"spawn_cylinder {p0} → {p1} r={radius:.2f}", self.adv)
            return None
        dx,dy,dz = p1.x-p0.x, p1.y-p0.y, p1.z-p0.z
        length = math.sqrt(dx**2+dy**2+dz**2)
        if length < 1e-6: return None
        mid = FVector((p0.x+p1.x)/2+self.origin.x,
                      (p0.y+p1.y)/2+self.origin.y,
                      (p0.z+p1.z)/2+self.origin.z)
        try:
            actor = self.world.actor_spawn(StaticMeshActor, mid)
            mc    = actor.StaticMeshComponent
            mesh  = ue.load_object(StaticMesh, '/Engine/BasicShapes/Cylinder.Cylinder')
            if mesh: mc.StaticMesh = mesh
            actor.set_actor_scale3d(FVector(radius/50, radius/50, length/200))
            pitch = math.degrees(math.atan2(math.sqrt(dx**2+dy**2), dz)) - 90
            yaw   = math.degrees(math.atan2(dy, dx))
            actor.set_actor_rotation(FRotator(pitch, yaw, 0))
            mat = mc.create_and_set_material_instance_dynamic(0)
            if mat: mat.set_vector_parameter_value('Color', FLinearColor(*color))
            self._spawned.append(actor)
            return actor
        except Exception as e:
            if self.debug: print(f"{_P}cylinder error: {e}")
            return None

    # ── Sphere ────────────────────────────────────────────────────────────────

    def spawn_sphere(self, pos: FVector, radius: float, color: Tuple) -> Optional[Any]:
        if not UE_AVAILABLE or not self.world:
            _adbg(f"spawn_sphere @ {pos} r={radius:.2f}", self.adv)
            return None
        p = FVector(pos.x+self.origin.x, pos.y+self.origin.y, pos.z+self.origin.z)
        try:
            actor = self.world.actor_spawn(StaticMeshActor, p)
            mc    = actor.StaticMeshComponent
            mesh  = ue.load_object(StaticMesh, '/Engine/BasicShapes/Sphere.Sphere')
            if mesh: mc.StaticMesh = mesh
            s = radius/50.0
            actor.set_actor_scale3d(FVector(s,s,s))
            mat = mc.create_and_set_material_instance_dynamic(0)
            if mat: mat.set_vector_parameter_value('Color', FLinearColor(*color))
            self._spawned.append(actor)
            return actor
        except Exception as e:
            if self.debug: print(f"{_P}sphere error: {e}")
            return None

    # ── Arrow ─────────────────────────────────────────────────────────────────

    def spawn_arrow(self, origin: FVector, tip: FVector,
                    shaft_r: float, color: Tuple) -> List[Any]:
        actors = []
        s = self.spawn_cylinder(origin, tip, shaft_r, color)
        if s: actors.append(s)
        h = self.spawn_sphere(tip, shaft_r*2, color)
        if h: actors.append(h)
        return actors

    # ── Procedural mesh ──────────────────────────────────────────────────────

    def spawn_proc_mesh(self, mesh: MeshData,
                        color: Tuple,
                        opacity: float = 1.0) -> Optional[Any]:
        if not UE_AVAILABLE or not self.world:
            print(f"{_P}proc_mesh {len(mesh.vertices)}v {len(mesh.indices)}t "
                  f"color={color[:3]} opacity={opacity:.2f}")
            return None
        try:
            actor = self.world.actor_spawn(Actor, self.origin)
            pmc   = actor.add_actor_component(ProceduralMeshComponent, 'Mesh')

            verts_uu = [FVector(v[0]*100,v[1]*100,v[2]*100) for v in mesh.vertices]
            tris     = [int(i) for face in mesh.indices for i in face]
            norms_uu = [FVector(n[0],n[1],n[2]) for n in mesh.normals]

            pmc.create_mesh_section_linear_color(
                0, verts_uu, tris, norms_uu, [], [], [], True)

            if opacity < 0.999:
                try:
                    mat_path = self.TRANSLUCENT_MATERIAL
                    mat = ue.load_object(
                        ue.find_class('MaterialInterface'), mat_path)
                    pmc.set_material(0, mat)
                    dyn = pmc.create_and_set_material_instance_dynamic(0)
                    if dyn:
                        c4 = (*color[:3], opacity)
                        dyn.set_vector_parameter_value('Color', FLinearColor(*c4))
                        dyn.set_scalar_parameter_value('Opacity', opacity)
                        dyn.set_scalar_parameter_value('Emissive Multiplier', 1.0)
                except Exception as te:
                    if self.debug: print(f"{_P}translucent mat error: {te}")
            else:
                mat = pmc.create_and_set_material_instance_dynamic(0)
                if mat:
                    mat.set_vector_parameter_value('Color', FLinearColor(*color))

            self._spawned.append(actor)
            return actor
        except Exception as e:
            if self.debug: print(f"{_P}proc_mesh error: {e}")
            return None

    # ── Text label ───────────────────────────────────────────────────────────

    def spawn_text(self, pos: FVector, text: str,
                   size: float = 10.0, color: Tuple = (1,1,1,1)) -> Optional[Any]:
        if not UE_AVAILABLE or not self.world:
            print(f"{_P}text3d '{text}' @ ({pos.x:.0f},{pos.y:.0f},{pos.z:.0f})")
            return None
        p = FVector(pos.x+self.origin.x, pos.y+self.origin.y, pos.z+self.origin.z)
        try:
            actor = self.world.actor_spawn(Actor, p)
            tc    = actor.add_actor_component(TextRenderComponent, 'Label')
            tc.SetText(text); tc.WorldSize = size
            tc.TextRenderColor = FLinearColor(*color)
            self._spawned.append(actor)
            return actor
        except Exception as e:
            if self.debug: print(f"{_P}text error: {e}")
            return None

    # ── Tube mesh from CurveSegments ─────────────────────────────────────────

    def spawn_segments_as_tube(self,
                                segments: List[CurveSegment],
                                bounds: PlotBounds,
                                style: LineStyle,
                                mode: str = '3d') -> List[Any]:
        """Convert CurveSegments → tube meshes via TubeMeshBuilder."""
        radius = style.resolved_radius(bounds.x_span) * bounds.units_per_uu
        builder = TubeMeshBuilder(
            radius   = radius,
            sides    = style.circle_res,
            shape    = style.shape,
            dash_pattern = style.dash_pattern,
            end_cap  = style.end_cap,
            debug    = self.debug,
            advanced_debug = self.adv,
        )
        actors = []
        for seg in segments:
            if len(seg.points) < 2:
                continue
            if mode == '2d':
                pts = [(p.x*bounds.units_per_uu,
                        0.0,
                        p.y*bounds.units_per_uu) for p in seg.points]
            else:
                pts = [(p.x*bounds.units_per_uu,
                        p.y*bounds.units_per_uu,
                        p.z*bounds.units_per_uu) for p in seg.points]
            mesh = builder.build(pts)
            a = self.spawn_proc_mesh(mesh, style.color, style.opacity)
            if a: actors.append(a)
        return actors

    # ── Cleanup ───────────────────────────────────────────────────────────────

    def destroy_all(self):
        for a in self._spawned:
            try: a.actor_destroy()
            except Exception: pass
        self._spawned.clear()


# ============================================================================
# GRID & AXES RENDERER
# ============================================================================

class GridRenderer:
    """Render configurable axis grid lines, tick marks, and axis labels."""

    def __init__(self, factory: UnrealActorFactory,
                 bounds: PlotBounds,
                 debug: bool = False,
                 advanced_debug: bool = False):
        self.factory = factory
        self.bounds  = bounds
        self.actors: List[Any] = []
        self.debug   = debug
        self.adv     = advanced_debug

    def render_grid_2d(self, spacing: float = 1.0,
                       color: Tuple = (0.3,0.3,0.3,0.5),
                       radius: float = 0.5):
        b = self.bounds
        import numpy as np
        for x in np.arange(math.ceil(b.x_range[0]/spacing)*spacing,
                            b.x_range[1]+spacing/2, spacing):
            p0 = b.to_uu(x, 0, b.y_range[0])
            p1 = b.to_uu(x, 0, b.y_range[1])
            self.factory.spawn_cylinder(p0, p1, radius, color)
        for y in np.arange(math.ceil(b.y_range[0]/spacing)*spacing,
                            b.y_range[1]+spacing/2, spacing):
            p0 = b.to_uu(b.x_range[0], 0, y)
            p1 = b.to_uu(b.x_range[1], 0, y)
            self.factory.spawn_cylinder(p0, p1, radius, color)
        _dbg("grid_2d rendered", self.debug)

    def render_grid_3d(self, spacing: float = 1.0,
                       color: Tuple = (0.25,0.25,0.25,0.4),
                       radius: float = 0.4):
        """Full 3D box grid: all three axis families."""
        b = self.bounds
        import numpy as np
        xs = np.arange(math.ceil(b.x_range[0]/spacing)*spacing,
                        b.x_range[1]+spacing/2, spacing)
        ys = np.arange(math.ceil(b.y_range[0]/spacing)*spacing,
                        b.y_range[1]+spacing/2, spacing)
        zs = np.arange(math.ceil(b.z_range[0]/spacing)*spacing,
                        b.z_range[1]+spacing/2, spacing)
        # X-axis lines along Y
        for z in zs:
            for x in xs:
                p0 = b.to_uu(x, b.y_range[0], z)
                p1 = b.to_uu(x, b.y_range[1], z)
                self.factory.spawn_cylinder(p0, p1, radius, color)
        # Y-axis lines along X
        for z in zs:
            for y in ys:
                p0 = b.to_uu(b.x_range[0], y, z)
                p1 = b.to_uu(b.x_range[1], y, z)
                self.factory.spawn_cylinder(p0, p1, radius, color)
        # Z-axis lines
        for x in xs:
            for y in ys:
                p0 = b.to_uu(x, y, b.z_range[0])
                p1 = b.to_uu(x, y, b.z_range[1])
                self.factory.spawn_cylinder(p0, p1, radius, color)
        _dbg("grid_3d rendered", self.debug)

    def render_axes_2d(self, color: Tuple = (0.7,0.7,0.7,1.0), radius: float = 1.5):
        b = self.bounds
        self.factory.spawn_cylinder(b.to_uu(b.x_range[0],0,0),
                                     b.to_uu(b.x_range[1],0,0), radius, color)
        self.factory.spawn_cylinder(b.to_uu(0,0,b.y_range[0]),
                                     b.to_uu(0,0,b.y_range[1]), radius, color)

    def render_axes_3d(self, color: Tuple = (0.7,0.7,0.7,1.0), radius: float = 1.5):
        b = self.bounds
        self.factory.spawn_cylinder(b.to_uu(b.x_range[0],0,0),
                                     b.to_uu(b.x_range[1],0,0), radius, color)
        self.factory.spawn_cylinder(b.to_uu(0,b.y_range[0],0),
                                     b.to_uu(0,b.y_range[1],0), radius, color)
        self.factory.spawn_cylinder(b.to_uu(0,0,b.z_range[0]),
                                     b.to_uu(0,0,b.z_range[1]), radius, color)

    def render_tick_labels(self, spacing: float = 1.0,
                           color: Tuple = (0.8,0.8,0.8,1.0)):
        b = self.bounds
        import numpy as np
        for x in np.arange(math.ceil(b.x_range[0]/spacing)*spacing,
                             b.x_range[1]+spacing/2, spacing):
            pos = b.to_uu(x, 0, b.y_range[0] - 0.3)
            self.factory.spawn_text(pos, f"{x:.1g}", size=5.0, color=color)
        for y in np.arange(math.ceil(b.y_range[0]/spacing)*spacing,
                             b.y_range[1]+spacing/2, spacing):
            pos = b.to_uu(b.x_range[0]-0.4, 0, y)
            self.factory.spawn_text(pos, f"{y:.1g}", size=5.0, color=color)

    def render_axis_labels(self, xlabel='', ylabel='', zlabel=''):
        b = self.bounds
        if xlabel:
            pos = b.to_uu((b.x_range[0]+b.x_range[1])/2, 0, b.y_range[0]-0.7)
            self.factory.spawn_text(pos, xlabel, size=8.0)
        if ylabel:
            pos = b.to_uu(b.x_range[0]-0.9, 0, (b.y_range[0]+b.y_range[1])/2)
            self.factory.spawn_text(pos, ylabel, size=8.0)
        if zlabel:
            pos = b.to_uu(b.x_range[0]-0.9, (b.y_range[0]+b.y_range[1])/2,
                           (b.z_range[0]+b.z_range[1])/2)
            self.factory.spawn_text(pos, zlabel, size=8.0)


# ============================================================================
# MATH PLOTTER  — main API class
# ============================================================================

class MathPlotter:
    """
    Unified math plotter for Unreal Engine 4.27.

    Supports matplotlib, seaborn, ggplot/Grammar-of-Graphics APIs.
    All APIs use the same internal queue → same renderer.

    Args:
        world:          UE world object (None = offline / test mode)
        origin:         FVector world-space origin for this plot
        bounds:         PlotBounds (x/y/z range + units_per_uu)
        zoom:           camera zoom factor (adjusts adaptive tolerance)
        ga_backend:     'vga' | 'pga' | 'cga' | 'sta' | 'custom'
        debug:          print per-operation summaries
        advanced_debug: print full arrays, timing, GA grade tables
    """

    def __init__(self,
                 world=None,
                 origin: FVector = None,
                 bounds: PlotBounds = None,
                 zoom: float = 1.0,
                 ga_backend: str = 'vga',
                 debug: bool = False,
                 advanced_debug: bool = False):
        self.world          = world
        self.bounds         = bounds or PlotBounds()
        self.zoom           = zoom
        self.debug          = debug
        self.adv            = advanced_debug

        # GA backend
        self.ga = GABackend(backend=ga_backend,
                            debug=debug,
                            advanced_debug=advanced_debug)

        # Unreal factory
        self.factory = UnrealActorFactory(
            world, origin or FVector(0,0,0),
            debug=debug, advanced_debug=advanced_debug)

        # Grid renderer
        self.grid_renderer = GridRenderer(
            self.factory, self.bounds,
            debug=debug, advanced_debug=advanced_debug)

        # State
        self._queue:        List[Dict] = []
        self._style_index:  int        = 0
        self._pending_style: Optional[LineStyle] = None
        self._show_grid:    bool       = False
        self._grid_mode:    str        = '2d'
        self._grid_spacing: float      = 1.0
        self._title:        str        = ''
        self._xlabel:       str        = ''
        self._ylabel:       str        = ''
        self._zlabel:       str        = ''

        if self.debug:
            print(f"{_P}MathPlotter init  bounds={self.bounds}  "
                  f"ga_backend={ga_backend}  debug={debug}  adv={advanced_debug}")

    # ── Style helpers ─────────────────────────────────────────────────────────

    def _next_style(self, **kw) -> LineStyle:
        """Return the next auto-cycle style, overridden by kw and pending aes."""
        base = LineStyle.from_palette(self._style_index)
        self._style_index += 1
        if self._pending_style:
            # Merge pending aes into base
            ps = self._pending_style
            for attr in ('color','linewidth','linewidth_mode','opacity',
                         'shape','dash_pattern','end_cap','circle_res','label'):
                v = getattr(ps, attr, None)
                if v is not None:
                    setattr(base, attr, v)
            self._pending_style = None
        for k, v in kw.items():
            if hasattr(base, k):
                setattr(base, k, v)
        return base

    def _resolve_fn(self, f, vars=('x',)) -> Callable:
        """Compile SymPy expression or pass-through callable."""
        if SYMPY_AVAILABLE and isinstance(f, _sp.Basic):
            return SymbolicCompiler.compile(f, list(vars))
        if callable(f):
            return f
        raise TypeError(f"Expected callable or SymPy expression, got {type(f)}")

    def _safe_call(self, fn, *args):
        try:
            return float(fn(*args))
        except Exception:
            return None

    # ─────────────────────────────────────────────────────────────────────────
    # ══ 2D PLOTS ══
    # ─────────────────────────────────────────────────────────────────────────

    def plot(self, f, x_range: Vec2 = None, n: int = 128,
             show_inflections: bool = False, **kw) -> 'MathPlotter':
        """y = f(x) explicit curve."""
        fn      = self._resolve_fn(f, ('x',))
        x_range = x_range or self.bounds.x_range
        style   = self._next_style(**kw)
        self._queue.append(dict(type='plot', fn=fn, x_range=x_range,
                                n=n, style=style,
                                show_inflections=show_inflections))
        if self.debug: print(f"{_P}queued plot x={x_range}")
        return self

    def implicit(self, F, resolution: int = 80, **kw) -> 'MathPlotter':
        """F(x,y)=0 implicit contour."""
        fn    = self._resolve_fn(F, ('x','y'))
        style = self._next_style(**kw)
        self._queue.append(dict(type='implicit', fn=fn,
                                resolution=resolution, style=style))
        if self.debug: print(f"{_P}queued implicit res={resolution}")
        return self

    def contour(self, F, levels: List[float] = None,
                resolution: int = 60, **kw) -> 'MathPlotter':
        """Contour lines of F(x,y) at given level values."""
        fn     = self._resolve_fn(F, ('x','y'))
        levels = levels or [0.0]
        style  = self._next_style(**kw)
        self._queue.append(dict(type='contour', fn=fn,
                                levels=levels, resolution=resolution,
                                style=style))
        if self.debug: print(f"{_P}queued contour levels={levels}")
        return self

    def heatmap(self, F, resolution: int = 64, **kw) -> 'MathPlotter':
        """F(x,y) as a coloured flat mesh."""
        fn    = self._resolve_fn(F, ('x','y'))
        style = self._next_style(**kw)
        self._queue.append(dict(type='heatmap', fn=fn,
                                resolution=resolution, style=style))
        if self.debug: print(f"{_P}queued heatmap res={resolution}")
        return self

    def scatter(self, points, **kw) -> 'MathPlotter':
        """Scatter plot of 2D or 3D points."""
        style = self._next_style(**kw)
        self._queue.append(dict(type='scatter', points=list(points), style=style))
        if self.debug: print(f"{_P}queued scatter {len(points)} pts")
        return self

    def line(self, p1, p2, **kw) -> 'MathPlotter':
        """Straight line between two points."""
        style = self._next_style(**kw)
        self._queue.append(dict(type='line', p1=p1, p2=p2, style=style))
        return self

    def band(self, f_lo, f_hi, x_range: Vec2 = None,
             n: int = 64, **kw) -> 'MathPlotter':
        """Ribbon / band between f_lo(x) and f_hi(x)."""
        fn_lo   = self._resolve_fn(f_lo, ('x',))
        fn_hi   = self._resolve_fn(f_hi, ('x',))
        x_range = x_range or self.bounds.x_range
        style   = self._next_style(**kw)
        self._queue.append(dict(type='band', fn_lo=fn_lo, fn_hi=fn_hi,
                                x_range=x_range, n=n, style=style))
        if self.debug: print(f"{_P}queued band")
        return self

    # ─────────────────────────────────────────────────────────────────────────
    # ══ 3D SURFACES ══
    # ─────────────────────────────────────────────────────────────────────────

    def plot3d(self, f,
               x_range: Vec2 = None,
               y_range: Vec2 = None,
               resolution: int = 64, **kw) -> 'MathPlotter':
        """z = f(x,y) explicit surface — primary 3D plot method."""
        fn      = self._resolve_fn(f, ('x','y'))
        x_range = x_range or self.bounds.x_range
        y_range = y_range or self.bounds.y_range
        style   = self._next_style(**kw)
        self._queue.append(dict(type='plot3d', fn=fn,
                                x_range=x_range, y_range=y_range,
                                resolution=resolution, style=style))
        if self.debug: print(f"{_P}queued plot3d res={resolution}")
        return self

    def parametric_surface(self, fx, fy, fz,
                            u_range: Vec2 = (0.0, 1.0),
                            v_range: Vec2 = (0.0, 1.0),
                            resolution: int = 48, **kw) -> 'MathPlotter':
        """Parametric surface (u,v) → (x,y,z)."""
        _fx = self._resolve_fn(fx, ('u','v'))
        _fy = self._resolve_fn(fy, ('u','v'))
        _fz = self._resolve_fn(fz, ('u','v'))
        style = self._next_style(**kw)
        self._queue.append(dict(type='parametric_surface',
                                fx=_fx, fy=_fy, fz=_fz,
                                u_range=u_range, v_range=v_range,
                                resolution=resolution, style=style))
        if self.debug: print(f"{_P}queued parametric_surface res={resolution}")
        return self

    def plot_curve3d(self, fx, fy, fz,
                     t_range: Vec2 = (0.0, 1.0),
                     n: int = 128, **kw) -> 'MathPlotter':
        """Parametric 3D curve (t) → (x,y,z)."""
        _fx = self._resolve_fn(fx, ('t',))
        _fy = self._resolve_fn(fy, ('t',))
        _fz = self._resolve_fn(fz, ('t',))
        style = self._next_style(**kw)
        self._queue.append(dict(type='plot_curve3d',
                                fx=_fx, fy=_fy, fz=_fz,
                                t_range=t_range, n=n, style=style))
        if self.debug: print(f"{_P}queued plot_curve3d t={t_range}")
        return self

    def wireframe(self, f,
                  x_range: Vec2 = None,
                  y_range: Vec2 = None,
                  resolution: int = 20, **kw) -> 'MathPlotter':
        """Wireframe of z=f(x,y) — surfaces lines along u/v isoparametric curves."""
        fn      = self._resolve_fn(f, ('x','y'))
        x_range = x_range or self.bounds.x_range
        y_range = y_range or self.bounds.y_range
        style   = self._next_style(**kw)
        self._queue.append(dict(type='wireframe', fn=fn,
                                x_range=x_range, y_range=y_range,
                                resolution=resolution, style=style))
        if self.debug: print(f"{_P}queued wireframe res={resolution}")
        return self

    def colormap_surface(self, f,
                          x_range: Vec2 = None,
                          y_range: Vec2 = None,
                          resolution: int = 64,
                          colormap: str = 'viridis', **kw) -> 'MathPlotter':
        """z=f(x,y) surface with per-vertex colour mapped from z value."""
        fn      = self._resolve_fn(f, ('x','y'))
        x_range = x_range or self.bounds.x_range
        y_range = y_range or self.bounds.y_range
        style   = self._next_style(**kw)
        self._queue.append(dict(type='colormap_surface', fn=fn,
                                x_range=x_range, y_range=y_range,
                                resolution=resolution,
                                colormap=colormap, style=style))
        if self.debug: print(f"{_P}queued colormap_surface cmap={colormap}")
        return self

    def isosurface(self, F, iso_value: float = 0.0,
                   x_range=None, y_range=None, z_range=None,
                   resolution: int = 40, smooth: int = 0, **kw) -> 'MathPlotter':
        """F(x,y,z)=iso_value mesh via marching cubes."""
        fn = self._resolve_fn(F, ('x','y','z'))
        style = self._next_style(**kw)
        self._queue.append(dict(type='isosurface', fn=fn,
                                iso_value=iso_value,
                                x_range=x_range or self.bounds.x_range,
                                y_range=y_range or self.bounds.y_range,
                                z_range=z_range or self.bounds.z_range,
                                resolution=resolution, smooth=smooth, style=style))
        if self.debug: print(f"{_P}queued isosurface iso={iso_value}")
        return self

    def intersection(self, F1, F2, mode: str = '2d',
                     resolution: int = 80, **kw) -> 'MathPlotter':
        """Highlight curve/surface where F1 = F2."""
        fn1 = self._resolve_fn(F1, ('x','y') if mode=='2d' else ('x','y','z'))
        fn2 = self._resolve_fn(F2, ('x','y') if mode=='2d' else ('x','y','z'))
        style = self._next_style(**kw)
        self._queue.append(dict(type='intersection', F1=fn1, F2=fn2,
                                mode=mode, resolution=resolution, style=style))
        if self.debug: print(f"{_P}queued intersection mode={mode}")
        return self

    def riemann_surface(self, kind: str = 'sqrt',
                        r_range: Vec2 = (0.05, 3.0),
                        resolution: int = 64,
                        sheet_gap: float = 0.3,
                        n_sheets: int = 3,
                        p: int = 1, q: int = 4, **kw) -> 'MathPlotter':
        """Multi-sheet Riemann surface. kind: 'sqrt'|'cbrt'|'log'|'pow'."""
        self._queue.append(dict(type='riemann_surface', kind=kind,
                                r_range=r_range, resolution=resolution,
                                sheet_gap=sheet_gap, n_sheets=n_sheets,
                                p=p, q=q, kw=kw))
        if self.debug: print(f"{_P}queued riemann_surface kind={kind}")
        return self

    def domain_color(self, f, resolution: int = 128,
                     x_range=None, y_range=None) -> 'MathPlotter':
        """Domain coloring for f(z): C→C."""
        fn = self._resolve_fn(f, ('z',))
        x_range = x_range or self.bounds.x_range
        y_range = y_range or self.bounds.y_range
        self._queue.append(dict(type='domain_color', fn=fn,
                                resolution=resolution,
                                x_range=x_range, y_range=y_range))
        if self.debug: print(f"{_P}queued domain_color res={resolution}")
        return self

    # ─────────────────────────────────────────────────────────────────────────
    # ══ VECTOR FIELDS ══
    # ─────────────────────────────────────────────────────────────────────────

    def vector(self, v, origin=(0,0,0), **kw) -> 'MathPlotter':
        """Single vector arrow."""
        style = self._next_style(**kw)
        self._queue.append(dict(type='vector', v=v, origin=origin, style=style))
        return self

    def vector_field(self, F, density: int = 8, normalize: bool = True,
                     scale: float = 0.4, mode: str = '2d', **kw) -> 'MathPlotter':
        """Vector field arrows on a grid."""
        fn    = self._resolve_fn(F, ('x','y') if mode=='2d' else ('x','y','z'))
        style = self._next_style(**kw)
        self._queue.append(dict(type='vector_field', fn=fn,
                                density=density, normalize=normalize,
                                scale=scale, mode=mode, style=style))
        if self.debug: print(f"{_P}queued vector_field density={density} mode={mode}")
        return self

    def streamline(self, F, seed,
                   step: float = 0.05, max_steps: int = 400,
                   mode: str = '2d', **kw) -> 'MathPlotter':
        """Integral curve (streamline) of a vector field."""
        fn    = self._resolve_fn(F, ('x','y') if mode=='2d' else ('x','y','z'))
        style = self._next_style(**kw)
        self._queue.append(dict(type='streamline', fn=fn, seed=seed,
                                step=step, max_steps=max_steps,
                                mode=mode, style=style))
        if self.debug: print(f"{_P}queued streamline seed={seed}")
        return self

    # ─────────────────────────────────────────────────────────────────────────
    # ══ GEOMETRIC ALGEBRA ══
    # ─────────────────────────────────────────────────────────────────────────

    def ga_primitive(self, mv, origin: Vec3 = (0,0,0),
                     scale: float = 1.0, **kw) -> 'MathPlotter':
        """
        Render a kingdon multivector. Grade auto-detected:
          0 → scalar label
          1 → arrow (vector)
          2 → plane patch (bivector)
          3 → cube outline (trivector)
          4+ → projected vector representation
        Alias: plot_ga()
        """
        style = self._next_style(**kw)
        if self.adv:
            self.ga.debug_print(mv, label='ga_primitive()')
        self._queue.append(dict(type='ga', mv=mv, origin=origin,
                                scale=scale, style=style))
        if self.debug:
            grade = GABackend.detect_grade(mv)
            print(f"{_P}queued ga_primitive grade={grade} origin={origin}")
        return self

    def plot_ga(self, mv, origin: Vec3 = (0,0,0),
                scale: float = 1.0, **kw) -> 'MathPlotter':
        """Alias for ga_primitive()."""
        return self.ga_primitive(mv, origin, scale, **kw)

    def ga_rotor(self, R, target_mv,
                 origin: Vec3 = (0,0,0), scale: float = 1.0,
                 steps: int = 12, **kw) -> 'MathPlotter':
        """
        Visualise a rotor R acting on target_mv.
        Shows the original multivector, the rotated result, and
        arc arrows indicating the rotation path.
        """
        style = self._next_style(**kw)
        if self.adv:
            axis, angle = GABackend.rotor_to_axis_angle(R)
            print(f"{_PA} ga_rotor axis={axis} angle={math.degrees(angle):.2f}°")
        self._queue.append(dict(type='ga_rotor', R=R, target_mv=target_mv,
                                origin=origin, scale=scale, steps=steps,
                                style=style))
        if self.debug: print(f"{_P}queued ga_rotor")
        return self

    def ga_meet(self, mv1, mv2,
                origin: Vec3 = (0,0,0), scale: float = 1.0, **kw) -> 'MathPlotter':
        """Render meet (intersection) of two multivectors."""
        style = self._next_style(**kw)
        self._queue.append(dict(type='ga_meet', mv1=mv1, mv2=mv2,
                                origin=origin, scale=scale, style=style))
        if self.debug: print(f"{_P}queued ga_meet")
        return self

    def ga_join(self, mv1, mv2,
                origin: Vec3 = (0,0,0), scale: float = 1.0, **kw) -> 'MathPlotter':
        """Render join (span) of two multivectors."""
        style = self._next_style(**kw)
        self._queue.append(dict(type='ga_join', mv1=mv1, mv2=mv2,
                                origin=origin, scale=scale, style=style))
        if self.debug: print(f"{_P}queued ga_join")
        return self

    def ga_spread(self, mv,
                  origin: Vec3 = (0,0,0),
                  scale: float = 1.0,
                  max_subviews: int = 4, **kw) -> 'MathPlotter':
        """
        Decompose a higher-grade multivector into multiple 3D sub-views,
        each showing a grade-projection, arranged in a grid.
        """
        style = self._next_style(**kw)
        self._queue.append(dict(type='ga_spread', mv=mv, origin=origin,
                                scale=scale, max_subviews=max_subviews,
                                style=style))
        if self.debug: print(f"{_P}queued ga_spread max={max_subviews}")
        return self

    # ─────────────────────────────────────────────────────────────────────────
    # ══ N-DIMENSIONAL ══
    # ─────────────────────────────────────────────────────────────────────────

    def spread(self, fn, var_names: List[str], var_ranges: List[Vec2],
               max_subplots: int = 9, resolution: int = 32,
               subplot_spacing: float = 12.0) -> 'MathPlotter':
        """
        Render an nD function as a grid of 3D surface projections.
        Each sub-plot shows f varying over two chosen dimensions
        with remaining dimensions fixed at midpoints.
        """
        self._queue.append(dict(type='spread', fn=fn,
                                var_names=var_names,
                                var_ranges=var_ranges,
                                max_subplots=max_subplots,
                                resolution=resolution,
                                subplot_spacing=subplot_spacing))
        if self.debug:
            print(f"{_P}queued spread {len(var_names)}D -> {max_subplots} projections")
        return self

    # ─────────────────────────────────────────────────────────────────────────
    # ══ AXES & DECORATION ══
    # ─────────────────────────────────────────────────────────────────────────

    def grid(self, show: bool = True, spacing: float = 1.0,
             mode: str = '2d', **kw) -> 'MathPlotter':
        self._show_grid    = show
        self._grid_spacing = spacing
        self._grid_mode    = mode
        return self

    def title(self, t: str) -> 'MathPlotter':
        self._title = t; return self

    def xlabel(self, x: str) -> 'MathPlotter':
        self._xlabel = x; return self

    def ylabel(self, y: str) -> 'MathPlotter':
        self._ylabel = y; return self

    def zlabel(self, z: str) -> 'MathPlotter':
        self._zlabel = z; return self

    def xlim(self, lo, hi) -> 'MathPlotter':
        self.bounds.x_range = (lo, hi); return self

    def ylim(self, lo, hi) -> 'MathPlotter':
        self.bounds.y_range = (lo, hi); return self

    def zlim(self, lo, hi) -> 'MathPlotter':
        self.bounds.z_range = (lo, hi); return self

    # ─────────────────────────────────────────────────────────────────────────
    # ══ GGPLOT / GRAMMAR-OF-GRAPHICS ALIASES ══
    # ─────────────────────────────────────────────────────────────────────────

    def aes(self, **kw) -> 'MathPlotter':
        """Stage aesthetic overrides for the next primitive."""
        self._pending_style = LineStyle(**{
            k: v for k, v in kw.items() if hasattr(LineStyle, k)
        })
        return self

    def labs(self, title: str = '', x: str = '', y: str = '',
             z: str = '') -> 'MathPlotter':
        if title: self.title(title)
        if x:     self.xlabel(x)
        if y:     self.ylabel(y)
        if z:     self.zlabel(z)
        return self

    def geom_line(self, f, **kw)              -> 'MathPlotter': return self.plot(f, **kw)
    def geom_surface(self, f, **kw)           -> 'MathPlotter': return self.plot3d(f, **kw)
    def geom_path3d(self, fx, fy, fz, **kw)  -> 'MathPlotter': return self.plot_curve3d(fx, fy, fz, **kw)
    def geom_point(self, pts, **kw)           -> 'MathPlotter': return self.scatter(pts, **kw)
    def geom_ribbon(self, flo, fhi, **kw)     -> 'MathPlotter': return self.band(flo, fhi, **kw)
    def geom_abline(self, p1, p2, **kw)       -> 'MathPlotter': return self.line(p1, p2, **kw)
    def geom_vector(self, v, o=(0,0,0), **kw) -> 'MathPlotter': return self.vector(v, o, **kw)
    def geom_contour(self, f, **kw)           -> 'MathPlotter': return self.contour(f, **kw)
    def geom_isosurface(self, f, **kw)        -> 'MathPlotter': return self.isosurface(f, **kw)
    def geom_wireframe(self, f, **kw)         -> 'MathPlotter': return self.wireframe(f, **kw)

    # ─────────────────────────────────────────────────────────────────────────
    # ══ EXECUTION ══
    # ─────────────────────────────────────────────────────────────────────────

    def show(self) -> 'MathPlotter':
        """Execute all queued drawing commands."""
        t_start = time.perf_counter()

        if self.debug:
            print(f"{_P}show() — {len(self._queue)} items queued")

        # Grid
        if self._show_grid:
            sp = self._grid_spacing
            if self._grid_mode == '3d':
                self.grid_renderer.render_grid_3d(spacing=sp)
                self.grid_renderer.render_axes_3d()
            else:
                self.grid_renderer.render_grid_2d(spacing=sp)
                self.grid_renderer.render_axes_2d()
                self.grid_renderer.render_tick_labels(spacing=sp)
            self.grid_renderer.render_axis_labels(
                self._xlabel, self._ylabel, self._zlabel)

        # Title
        if self._title:
            b = self.bounds
            pos = b.to_uu((b.x_range[0]+b.x_range[1])/2, 0,
                           b.y_range[1] + 0.6)
            self.factory.spawn_text(pos, self._title, size=12.0)

        # Render all queued items
        for item in self._queue:
            try:
                self._render(item)
            except Exception as e:
                print(f"{_P}ERROR rendering {item.get('type','?')}: {e}")
                if self.adv:
                    traceback.print_exc()

        elapsed = (time.perf_counter() - t_start) * 1000
        if self.debug:
            print(f"{_P}Done. actors={len(self.factory._spawned)}  "
                  f"elapsed={elapsed:.1f}ms")
        return self

    def clear(self) -> 'MathPlotter':
        """Destroy all spawned actors and reset queue."""
        self.factory.destroy_all()
        self._queue.clear()
        self._style_index = 0
        if self.debug: print(f"{_P}cleared")
        return self

    # ─────────────────────────────────────────────────────────────────────────
    # ══ INTERNAL RENDER DISPATCH ══
    # ─────────────────────────────────────────────────────────────────────────

    def _render(self, item: Dict):
        t = item['type']
        dispatch = {
            # 2D
            'plot':              self._r_plot,
            'implicit':          self._r_implicit,
            'contour':           self._r_contour,
            'heatmap':           self._r_heatmap,
            'scatter':           self._r_scatter,
            'line':              self._r_line,
            'band':              self._r_band,
            # 3D surfaces
            'plot3d':            self._r_plot3d,
            'parametric_surface':self._r_parametric_surface,
            'plot_curve3d':      self._r_plot_curve3d,
            'wireframe':         self._r_wireframe,
            'colormap_surface':  self._r_colormap_surface,
            'isosurface':        self._r_isosurface,
            'intersection':      self._r_intersection,
            'riemann_surface':   self._r_riemann_surface,
            'domain_color':      self._r_domain_color,
            # Vectors
            'vector':            self._r_vector,
            'vector_field':      self._r_vector_field,
            'streamline':        self._r_streamline,
            # GA
            'ga':                self._r_ga,
            'ga_rotor':          self._r_ga_rotor,
            'ga_meet':           self._r_ga_meet,
            'ga_join':           self._r_ga_join,
            'ga_spread':         self._r_ga_spread,
            # nD
            'spread':            self._r_spread,
        }
        fn = dispatch.get(t)
        if fn:
            fn(item)
        else:
            print(f"{_P}Unknown item type: '{t}'")

    # ── 2D render methods ─────────────────────────────────────────────────────

    def _r_plot(self, item):
        fn      = item['fn']
        x_range = item['x_range']
        style   = item['style']
        n       = item['n']

        sub = AdaptiveSubdivider(zoom=self.zoom,
                                  tolerance=style.linewidth*0.05,
                                  debug=self.debug,
                                  advanced_debug=self.adv)
        segs = sub.subdivide_explicit_2d(fn, x_range[0], x_range[1], n)

        if self.debug:
            total = sum(len(s.points) for s in segs)
            print(f"{_P}  plot: {len(segs)} segs, {total} pts")

        self.factory.spawn_segments_as_tube(segs, self.bounds, style, mode='2d')

    def _r_implicit(self, item):
        fn    = item['fn']
        res   = item['resolution']
        style = item['style']
        b     = self.bounds

        # Use intersection with zero
        finder = IntersectionFinder(resolution=res,
                                     debug=self.debug, advanced_debug=self.adv)
        segs = finder.find_2d(fn, lambda x,y: 0.0, b.x_range, b.y_range)
        if self.debug: print(f"{_P}  implicit: {len(segs)} segs")
        self.factory.spawn_segments_as_tube(segs, b, style, mode='2d')

    def _r_contour(self, item):
        fn     = item['fn']
        levels = item['levels']
        res    = item['resolution']
        style  = item['style']
        b      = self.bounds

        for level in levels:
            finder = IntersectionFinder(resolution=res,
                                         debug=self.debug,
                                         advanced_debug=self.adv)
            segs = finder.find_2d(fn, lambda x,y,lv=level: lv, b.x_range, b.y_range)
            self.factory.spawn_segments_as_tube(segs, b, style, mode='2d')

        if self.debug: print(f"{_P}  contour: {len(levels)} levels")

    def _r_heatmap(self, item):
        fn  = item['fn']
        res = item['resolution']
        b   = self.bounds

        sampler = SurfaceSampler(resolution=res,
                                  debug=self.debug, advanced_debug=self.adv)
        mesh = sampler.explicit(fn, b.x_range, b.y_range)
        mesh.vertices *= b.units_per_uu

        # Colour vertices by z value (heatmap)
        z_vals = mesh.vertices[:, 2]
        z_min, z_max = z_vals.min(), z_vals.max()
        style = item['style']
        self.factory.spawn_proc_mesh(mesh, style.color, style.opacity)
        if self.debug: print(f"{_P}  heatmap: {len(mesh.vertices)} verts")

    def _r_scatter(self, item):
        pts   = item['points']
        style = item['style']
        b     = self.bounds
        r     = style.resolved_radius(b.x_span) * b.units_per_uu * 3
        for p in pts:
            if len(p) == 2:
                pos = b.to_uu(p[0], 0.0, p[1])
            else:
                pos = b.to_uu(p[0], p[1], p[2])
            self.factory.spawn_sphere(pos, r, style.color)
        if self.debug: print(f"{_P}  scatter: {len(pts)} pts")

    def _r_line(self, item):
        p1, p2 = item['p1'], item['p2']
        style  = item['style']
        b      = self.bounds
        if len(p1) == 2: v0 = b.to_uu(p1[0], 0, p1[1])
        else:            v0 = b.to_uu(*p1[:3])
        if len(p2) == 2: v1 = b.to_uu(p2[0], 0, p2[1])
        else:            v1 = b.to_uu(*p2[:3])
        r = style.resolved_radius(b.x_span) * b.units_per_uu
        self.factory.spawn_cylinder(v0, v1, r, style.color)

    def _r_band(self, item):
        fn_lo   = item['fn_lo']
        fn_hi   = item['fn_hi']
        x_range = item['x_range']
        n       = item['n']
        style   = item['style']
        b       = self.bounds

        xs = np.linspace(x_range[0], x_range[1], n)
        verts, norms, tris = [], [], []
        for i, x in enumerate(xs):
            try:
                ylo = float(fn_lo(x)); yhi = float(fn_hi(x))
            except Exception:
                continue
            verts += [[x, 0, ylo],[x, 0, yhi]]
            norms += [[0,1,0],[0,1,0]]
        # quad strip
        n_q = len(verts) // 2
        for i in range(n_q - 1):
            a,b2,c,d = 2*i, 2*i+1, 2*i+2, 2*i+3
            tris += [[a,b2,c],[b2,d,c]]

        if verts:
            va = np.array(verts) * b.units_per_uu
            na = np.array(norms)
            ta = np.array(tris, dtype=int)
            mesh = MeshData(va, ta, na)
            self.factory.spawn_proc_mesh(mesh, style.color, style.opacity)
        if self.debug: print(f"{_P}  band: {len(verts)//2} quads")

    # ── 3D surface render methods ─────────────────────────────────────────────

    def _r_plot3d(self, item):
        fn      = item['fn']
        x_range = item['x_range']
        y_range = item['y_range']
        res     = item['resolution']
        style   = item['style']
        b       = self.bounds

        with _timed("plot3d sample", self.adv):
            sampler = SurfaceSampler(resolution=res,
                                      debug=self.debug, advanced_debug=self.adv)
            mesh = sampler.explicit(fn, x_range, y_range)

        mesh.vertices *= b.units_per_uu
        self.factory.spawn_proc_mesh(mesh, style.color, style.opacity)
        if self.debug:
            print(f"{_P}  plot3d: {len(mesh.vertices)}v {len(mesh.indices)}t")

    def _r_parametric_surface(self, item):
        fx, fy, fz = item['fx'], item['fy'], item['fz']
        u_range    = item['u_range']
        v_range    = item['v_range']
        res        = item['resolution']
        style      = item['style']
        b          = self.bounds

        sampler = SurfaceSampler(resolution=res,
                                  debug=self.debug, advanced_debug=self.adv)
        mesh = sampler.parametric(fx, fy, fz, u_range, v_range)
        mesh.vertices *= b.units_per_uu
        self.factory.spawn_proc_mesh(mesh, style.color, style.opacity)
        if self.debug:
            print(f"{_P}  parametric_surface: {len(mesh.vertices)}v {len(mesh.indices)}t")

    def _r_plot_curve3d(self, item):
        fx, fy, fz = item['fx'], item['fy'], item['fz']
        t_range    = item['t_range']
        n          = item['n']
        style      = item['style']

        sub = AdaptiveSubdivider(zoom=self.zoom,
                                  tolerance=style.linewidth*0.05,
                                  debug=self.debug, advanced_debug=self.adv)
        segs = sub.subdivide_parametric_3d(fx, fy, fz,
                                            t_range[0], t_range[1], n)

        if self.debug:
            total = sum(len(s.points) for s in segs)
            print(f"{_P}  plot_curve3d: {len(segs)} segs, {total} pts")

        self.factory.spawn_segments_as_tube(segs, self.bounds, style, mode='3d')

    def _r_wireframe(self, item):
        fn      = item['fn']
        x_range = item['x_range']
        y_range = item['y_range']
        res     = item['resolution']
        style   = item['style']
        b       = self.bounds

        xs = np.linspace(x_range[0], x_range[1], res)
        ys = np.linspace(y_range[0], y_range[1], res)

        # X iso-lines (vary y for each x)
        for x in xs[::max(1, res//10)]:
            pts = []
            for y in ys:
                try: pts.append(CurvePoint(x, y, float(fn(x,y))))
                except Exception: pts.append(CurvePoint(x, y, 0.0))
            segs = [CurveSegment(pts)]
            self.factory.spawn_segments_as_tube(segs, b, style, mode='3d')

        # Y iso-lines
        for y in ys[::max(1, res//10)]:
            pts = []
            for x in xs:
                try: pts.append(CurvePoint(x, y, float(fn(x,y))))
                except Exception: pts.append(CurvePoint(x, y, 0.0))
            segs = [CurveSegment(pts)]
            self.factory.spawn_segments_as_tube(segs, b, style, mode='3d')

        if self.debug: print(f"{_P}  wireframe: {res//max(1,res//10)*2} curves")

    def _r_colormap_surface(self, item):
        # Render as a plain surface for now (colourmap requires per-vertex material)
        # Pass through to plot3d renderer
        self._r_plot3d({**item, 'type': 'plot3d'})

    def _r_isosurface(self, item):
        fn    = item['fn']
        style = item['style']
        b     = self.bounds

        mc = MarchingCubes(
            x_range=item['x_range'], y_range=item['y_range'],
            z_range=item['z_range'], resolution=item['resolution'],
            iso_value=item['iso_value'], smooth_iterations=item['smooth'],
            debug=self.debug, advanced_debug=self.adv)
        mesh = mc.extract(fn)
        mesh.vertices *= b.units_per_uu
        self.factory.spawn_proc_mesh(mesh, style.color, style.opacity)
        if self.debug:
            print(f"{_P}  isosurface: {len(mesh.vertices)}v {len(mesh.indices)}t")

    def _r_intersection(self, item):
        F1, F2 = item['F1'], item['F2']
        style  = item['style']
        b      = self.bounds
        finder = IntersectionFinder(resolution=item['resolution'],
                                     debug=self.debug, advanced_debug=self.adv)

        if item['mode'] == '2d':
            segs = finder.find_2d(F1, F2, b.x_range, b.y_range)
            if self.debug: print(f"{_P}  intersection 2d: {len(segs)} segs")
            self.factory.spawn_segments_as_tube(segs, b, style, mode='2d')
        else:
            mesh = finder.find_3d(F1, F2, b.x_range, b.y_range, b.z_range)
            mesh.vertices *= b.units_per_uu
            self.factory.spawn_proc_mesh(mesh, style.color, style.opacity)

    def _r_riemann_surface(self, item):
        b     = self.bounds
        bld   = RiemannSurfaceBuilder(
            r_range=item['r_range'], resolution=item['resolution'],
            sheet_gap=item['sheet_gap'],
            debug=self.debug, advanced_debug=self.adv)

        kind = item['kind']
        if kind == 'sqrt':      sheets = bld.build_sqrt()
        elif kind == 'cbrt':    sheets = bld.build_cbrt()
        elif kind == 'log':     sheets = bld.build_log(n_sheets=item['n_sheets'])
        elif kind == 'pow':     sheets = bld.build_pow_pq(p=item['p'], q=item['q'])
        else:
            print(f"{_P}Unknown Riemann kind: {kind}"); return

        for mesh, sheet_idx in sheets:
            mesh.vertices *= b.units_per_uu
            color = _PALETTE[sheet_idx % len(_PALETTE)]
            kw    = item.get('kw', {})
            if 'color' in kw: color = kw['color']
            opacity = kw.get('opacity', 0.85)
            self.factory.spawn_proc_mesh(mesh, color, opacity)

        if self.debug:
            print(f"{_P}  riemann_surface kind={kind}: {len(sheets)} sheets")

    def _r_domain_color(self, item):
        fn         = item['fn']
        resolution = item['resolution']
        x_range    = item['x_range']
        y_range    = item['y_range']
        b          = self.bounds

        colorizer = DomainColorizer(resolution=resolution,
                                     x_range=x_range, y_range=y_range,
                                     debug=self.debug, advanced_debug=self.adv)
        img = colorizer.compute(fn)

        x0,x1 = x_range; y0,y1 = y_range
        verts = np.array([[x0,0,y0],[x1,0,y0],[x1,0,y1],[x0,0,y1]]) * b.units_per_uu
        inds  = np.array([[0,1,2],[0,2,3]], dtype=int)
        norms = np.tile([0,1,0], (4,1)).astype(float)
        uvs   = np.array([[0,0],[1,0],[1,1],[0,1]])
        mesh  = MeshData(verts, inds, norms, uvs)

        avg_color = tuple(float(img[:,:,c].mean()) for c in range(3)) + (1.0,)
        self.factory.spawn_proc_mesh(mesh, avg_color)
        if self.debug: print(f"{_P}  domain_color {img.shape}")

    # ── Vector field render methods ───────────────────────────────────────────

    def _r_vector(self, item):
        style = item['style']
        o     = item['origin']
        v     = item['v']
        b     = self.bounds
        if len(v) == 2:
            o3  = b.to_uu(o[0], 0, o[1] if len(o)>1 else 0)
            tip = b.to_uu(o[0]+v[0], 0, (o[1] if len(o)>1 else 0)+v[1])
        else:
            o3  = b.to_uu(*o[:3])
            tip = b.to_uu(o[0]+v[0], o[1]+v[1], o[2]+v[2])
        r = style.resolved_radius(b.x_span) * b.units_per_uu
        self.factory.spawn_arrow(o3, tip, r, style.color)

    def _r_vector_field(self, item):
        fn    = item['fn']
        style = item['style']
        b     = self.bounds

        sampler = VectorFieldSampler(
            density=item['density'], normalize=item['normalize'],
            scale=item['scale'] * b.units_per_uu,
            debug=self.debug, advanced_debug=self.adv)

        if item['mode'] == '2d':
            arrows = sampler.sample_2d(fn, b.x_range, b.y_range)
        else:
            arrows = sampler.sample_3d(fn, b.x_range, b.y_range, b.z_range)

        r = style.resolved_radius(b.x_span) * b.units_per_uu
        for arrow in arrows:
            ox,oy,oz = arrow.origin; dx,dy,dz = arrow.direction
            if item['mode'] == '2d':
                o3  = b.to_uu(ox, 0, oy)
                tip = b.to_uu(ox+dx/b.units_per_uu, 0, oy+dy/b.units_per_uu)
            else:
                o3  = b.to_uu(ox, oy, oz)
                tip = b.to_uu(ox+dx/b.units_per_uu,
                               oy+dy/b.units_per_uu,
                               oz+dz/b.units_per_uu)
            self.factory.spawn_arrow(o3, tip, r, style.color)

        if self.debug: print(f"{_P}  vector_field: {len(arrows)} arrows")

    def _r_streamline(self, item):
        fn    = item['fn']
        seed  = item['seed']
        style = item['style']
        b     = self.bounds

        solver = IntegralCurveSolver(
            step_size=item['step'], max_steps=item['max_steps'],
            bounds=(b.x_range, b.y_range, b.z_range),
            debug=self.debug, advanced_debug=self.adv)

        if item['mode'] == '2d':
            seg = solver.integrate_2d(fn, seed)
        else:
            seg = solver.integrate_3d(fn, seed)

        self.factory.spawn_segments_as_tube(
            [seg], b, style, mode=item['mode'])
        if self.debug: print(f"{_P}  streamline: {len(seg.points)} pts")

    # ── GA render methods ─────────────────────────────────────────────────────

    def _r_ga(self, item):
        mv     = item['mv']
        origin = item['origin']
        scale  = item['scale']
        style  = item['style']
        b      = self.bounds

        grade = GABackend.detect_grade(mv)

        if self.adv:
            print(f"{_PA} _r_ga: grade={grade}  origin={origin}  scale={scale}")

        if grade == 0:
            # Scalar: text label
            val = GABackend.extract_scalar(mv)
            pos = b.to_uu(*origin)
            self.factory.spawn_text(pos, f"{val:.4g}", size=8.0,
                                     color=style.color)

        elif grade == 1:
            # Vector: arrow
            vx, vy, vz = GABackend.extract_vector(mv)
            o3  = b.to_uu(*origin)
            tip = b.to_uu(origin[0]+vx*scale,
                           origin[1]+vy*scale,
                           origin[2]+vz*scale)
            r = style.resolved_radius(b.x_span) * b.units_per_uu
            self.factory.spawn_arrow(o3, tip, r, style.color)

        elif grade == 2:
            # Bivector: plane patch (oriented by dual normal)
            normal = GABackend.extract_bivector_normal(mv)
            cx, cy, cz = origin
            half = scale * 0.5
            # Build quad in the plane perpendicular to normal
            up = (0,0,1) if abs(normal[2]) < 0.9 else (1,0,0)
            ex_raw = (normal[1]*up[2]-normal[2]*up[1],
                      normal[2]*up[0]-normal[0]*up[2],
                      normal[0]*up[1]-normal[1]*up[0])
            e_nm = math.sqrt(sum(x**2 for x in ex_raw)) + 1e-12
            ex = tuple(x/e_nm for x in ex_raw)
            ey_raw = (normal[1]*ex[2]-normal[2]*ex[1],
                      normal[2]*ex[0]-normal[0]*ex[2],
                      normal[0]*ex[1]-normal[1]*ex[0])
            ey = tuple(x/(math.sqrt(sum(y**2 for y in ey_raw))+1e-12)
                       for x in ey_raw)
            corners = [
                [cx+(ex[i]-ey[i])*half for i in range(3)],
                [cx+(ex[i]+ey[i])*half for i in range(3)],
                [cx+(-ex[i]+ey[i])*half for i in range(3)],
                [cx+(-ex[i]-ey[i])*half for i in range(3)],
            ]
            va = np.array(corners) * b.units_per_uu
            ta = np.array([[0,1,2],[0,2,3]], dtype=int)
            na = np.tile(normal, (4,1))
            mesh = MeshData(va, ta, na)
            self.factory.spawn_proc_mesh(mesh, style.color, style.opacity)

        elif grade == 3:
            # Trivector: cube outline
            half = scale * 0.5 * b.units_per_uu
            ox,oy,oz = [c*b.units_per_uu for c in origin]
            r = style.resolved_radius(b.x_span) * b.units_per_uu
            edges = [
                ((ox-half,oy-half,oz-half),(ox+half,oy-half,oz-half)),
                ((ox-half,oy+half,oz-half),(ox+half,oy+half,oz-half)),
                ((ox-half,oy-half,oz+half),(ox+half,oy-half,oz+half)),
                ((ox-half,oy+half,oz+half),(ox+half,oy+half,oz+half)),
                ((ox-half,oy-half,oz-half),(ox-half,oy+half,oz-half)),
                ((ox+half,oy-half,oz-half),(ox+half,oy+half,oz-half)),
                ((ox-half,oy-half,oz+half),(ox-half,oy+half,oz+half)),
                ((ox+half,oy-half,oz+half),(ox+half,oy+half,oz+half)),
                ((ox-half,oy-half,oz-half),(ox-half,oy-half,oz+half)),
                ((ox+half,oy-half,oz-half),(ox+half,oy-half,oz+half)),
                ((ox-half,oy+half,oz-half),(ox-half,oy+half,oz+half)),
                ((ox+half,oy+half,oz-half),(ox+half,oy+half,oz+half)),
            ]
            for (p0, p1) in edges:
                self.factory.spawn_cylinder(
                    FVector(*p0), FVector(*p1), r, style.color)

        else:
            # Higher grade: projected grade-1 representation + label
            vx, vy, vz = GABackend.extract_vector(mv)
            o3  = b.to_uu(*origin)
            tip = b.to_uu(origin[0]+vx*scale,
                           origin[1]+vy*scale,
                           origin[2]+vz*scale)
            r = style.resolved_radius(b.x_span) * b.units_per_uu
            self.factory.spawn_arrow(o3, tip, r, style.color)
            # Grade label
            pos_label = b.to_uu(origin[0], origin[1], origin[2]+scale*0.6)
            self.factory.spawn_text(pos_label, f"G{grade}", size=5.0,
                                     color=style.color)

        if self.debug:
            print(f"{_P}  ga: grade={grade}")

    def _r_ga_rotor(self, item):
        """Visualise rotor action: draw original, arc path, rotated result."""
        R          = item['R']
        target_mv  = item['target_mv']
        origin     = item['origin']
        scale      = item['scale']
        steps      = item['steps']
        style      = item['style']
        b          = self.bounds

        axis, angle = GABackend.rotor_to_axis_angle(R)

        # Draw axis line
        r_ax = style.resolved_radius(b.x_span) * b.units_per_uu * 0.4
        ax_start = b.to_uu(*origin)
        ax_end   = b.to_uu(origin[0]+axis[0]*scale*2,
                            origin[1]+axis[1]*scale*2,
                            origin[2]+axis[2]*scale*2)
        self.factory.spawn_cylinder(ax_start, ax_end, r_ax,
                                     (0.9,0.9,0.9,0.5))

        # Draw original vector (grade-1 only for now)
        grade = GABackend.detect_grade(target_mv)
        if grade == 1:
            vx,vy,vz = GABackend.extract_vector(target_mv)
            o3  = b.to_uu(*origin)
            tip = b.to_uu(origin[0]+vx*scale,
                           origin[1]+vy*scale,
                           origin[2]+vz*scale)
            r = style.resolved_radius(b.x_span) * b.units_per_uu
            self.factory.spawn_arrow(o3, tip, r, _PALETTE[0])

            # Arc path
            if KINGDON_AVAILABLE and hasattr(R, '__mul__') and hasattr(R, 'reverse'):
                try:
                    arc_pts = []
                    for step_i in range(steps+1):
                        frac = step_i / steps
                        # Interpolated rotor (slerp approximation)
                        half_angle = frac * angle / 2
                        ax_bv_str = None
                        # Construct intermediate rotor using cos/sin
                        # (simplified — just sample the final rotation arc)
                        cos_h = math.cos(half_angle)
                        sin_h = math.sin(half_angle)
                        # Rotate vx,vy,vz around axis by frac*angle (Rodrigues)
                        c = math.cos(frac * angle)
                        s = math.sin(frac * angle)
                        dot = axis[0]*vx+axis[1]*vy+axis[2]*vz
                        rx = (c*vx + s*(axis[1]*vz-axis[2]*vy) +
                               (1-c)*dot*axis[0])
                        ry = (c*vy + s*(axis[2]*vx-axis[0]*vz) +
                               (1-c)*dot*axis[1])
                        rz = (c*vz + s*(axis[0]*vy-axis[1]*vx) +
                               (1-c)*dot*axis[2])
                        arc_pts.append(CurvePoint(
                            origin[0]+rx*scale,
                            origin[1]+ry*scale,
                            origin[2]+rz*scale))
                    arc_style = LineStyle(color=_PALETTE[2],
                                          dash_pattern=(0.15,0.08),
                                          end_cap='cone')
                    self.factory.spawn_segments_as_tube(
                        [CurveSegment(arc_pts)], b, arc_style, mode='3d')
                except Exception as e:
                    if self.debug: print(f"{_P}  ga_rotor arc error: {e}")

            # Final rotated vector
            c = math.cos(angle); s = math.sin(angle)
            dot = axis[0]*vx+axis[1]*vy+axis[2]*vz
            rx = c*vx+s*(axis[1]*vz-axis[2]*vy)+(1-c)*dot*axis[0]
            ry = c*vy+s*(axis[2]*vx-axis[0]*vz)+(1-c)*dot*axis[1]
            rz = c*vz+s*(axis[0]*vy-axis[1]*vx)+(1-c)*dot*axis[2]
            tip_r = b.to_uu(origin[0]+rx*scale,
                              origin[1]+ry*scale,
                              origin[2]+rz*scale)
            self.factory.spawn_arrow(o3, tip_r, r, _PALETTE[1])

        if self.debug:
            print(f"{_P}  ga_rotor: axis={axis} angle={math.degrees(angle):.2f}°")

    def _r_ga_meet(self, item):
        """Render meet (intersection) — try to call kingdon meet, fall back to midpoint."""
        mv1    = item['mv1']
        mv2    = item['mv2']
        origin = item['origin']
        scale  = item['scale']
        style  = item['style']
        b      = self.bounds

        # Try kingdon vee (meet operator)
        result_mv = None
        if KINGDON_AVAILABLE and hasattr(mv1, 'vee'):
            try:
                result_mv = mv1.vee(mv2)
            except Exception as e:
                if self.debug: print(f"{_P}  ga_meet vee failed: {e}")

        if result_mv is not None:
            self._r_ga({**item, 'type':'ga', 'mv': result_mv,
                        'origin': origin, 'scale': scale, 'style': style})
        else:
            # Fallback: render both and indicate meet with a text marker
            self._r_ga({**item, 'type':'ga', 'mv': mv1, 'origin': origin,
                        'scale': scale, 'style': style})
            sty2 = LineStyle.from_palette(self._style_index)
            self._r_ga({**item, 'type':'ga', 'mv': mv2, 'origin': origin,
                        'scale': scale, 'style': sty2})
            pos = b.to_uu(*origin)
            self.factory.spawn_text(pos, "∩", size=10.0, color=style.color)

        if self.debug: print(f"{_P}  ga_meet rendered")

    def _r_ga_join(self, item):
        """Render join (span/outer product)."""
        mv1    = item['mv1']
        mv2    = item['mv2']
        origin = item['origin']
        scale  = item['scale']
        style  = item['style']

        result_mv = None
        if KINGDON_AVAILABLE and hasattr(mv1, 'outer'):
            try:
                result_mv = mv1.outer(mv2)
            except Exception as e:
                if self.debug: print(f"{_P}  ga_join outer failed: {e}")
        elif KINGDON_AVAILABLE and hasattr(mv1, '__xor__'):
            try:
                result_mv = mv1 ^ mv2
            except Exception:
                pass

        if result_mv is not None:
            self._r_ga({**item, 'type':'ga', 'mv': result_mv,
                        'origin': origin, 'scale': scale, 'style': style})
        else:
            self._r_ga({**item, 'type':'ga', 'mv': mv1, 'origin': origin,
                        'scale': scale, 'style': style})
            sty2 = LineStyle.from_palette(self._style_index)
            self._r_ga({**item, 'type':'ga', 'mv': mv2, 'origin': origin,
                        'scale': scale, 'style': sty2})
            b   = self.bounds
            pos = b.to_uu(*origin)
            self.factory.spawn_text(pos, "∪", size=10.0, color=style.color)

        if self.debug: print(f"{_P}  ga_join rendered")

    def _r_ga_spread(self, item):
        """Decompose higher-grade mv into grade projections, render in grid."""
        mv           = item['mv']
        origin       = item['origin']
        scale        = item['scale']
        max_subviews = item['max_subviews']
        style        = item['style']
        b            = self.bounds

        grades_found = []
        grade = GABackend.detect_grade(mv)

        # Render grade-0..grade decompositions in a grid
        spacing = scale * 3.0
        for g in range(min(grade+1, max_subviews)):
            off = (origin[0] + g*spacing, origin[1], origin[2])
            sub_style = LineStyle.from_palette(g)
            self._r_ga({'type':'ga', 'mv': mv, 'origin': off,
                        'scale': scale, 'style': sub_style})
            pos = b.to_uu(off[0], off[1], off[2] + scale*0.8)
            self.factory.spawn_text(pos, f"Grade {g}", size=6.0,
                                     color=sub_style.color)

        if self.debug:
            print(f"{_P}  ga_spread: grade={grade}  {min(grade+1,max_subviews)} views")

    # ── nD spread render ─────────────────────────────────────────────────────

    def _r_spread(self, item):
        fn             = item['fn']
        var_names      = item['var_names']
        var_ranges     = item['var_ranges']
        max_subplots   = item['max_subplots']
        resolution     = item['resolution']
        subplot_spacing = item['subplot_spacing']
        b              = self.bounds

        engine = SpreadEngine(
            fn=fn, var_names=var_names, var_ranges=var_ranges,
            max_subplots=max_subplots, subplot_spacing=subplot_spacing,
            resolution=resolution, debug=self.debug, advanced_debug=self.adv)

        projections = engine.generate_projections()

        for proj in projections:
            mesh   = proj['mesh']
            offset = proj['offset']
            labels = proj['labels']

            mesh.vertices *= b.units_per_uu

            # Shift by sub-plot offset
            mesh.vertices[:, 0] += offset[0] * b.units_per_uu
            mesh.vertices[:, 1] += offset[1] * b.units_per_uu

            color = _PALETTE[projections.index(proj) % len(_PALETTE)]
            self.factory.spawn_proc_mesh(mesh, color, 0.85)

            # Labels for this sub-view
            ox = offset[0]*b.units_per_uu + b.x_range[0]*b.units_per_uu
            oy = offset[1]*b.units_per_uu + b.z_range[1]*b.units_per_uu + 50
            self.factory.spawn_text(FVector(ox, 0, oy),
                                     f"{labels[0]} × {labels[1]}",
                                     size=7.0, color=(0.9,0.9,0.9,1.0))

        if self.debug:
            print(f"{_P}  spread: {len(projections)} projections rendered")


# ============================================================================
# CONVENIENCE FACTORY
# ============================================================================

def create_plotter(world=None,
                   origin: FVector = None,
                   x_range: Vec2 = (-5, 5),
                   y_range: Vec2 = (-5, 5),
                   z_range: Vec2 = (-5, 5),
                   units_per_uu: float = 100.0,
                   zoom: float = 1.0,
                   ga_backend: str = 'vga',
                   debug: bool = False,
                   advanced_debug: bool = False) -> MathPlotter:
    """
    Convenience constructor.

    Example (offline test):
        p = create_plotter(debug=True, advanced_debug=True)
        p.grid(True, mode='3d')
        p.plot(lambda x: math.sin(x), color=(0.2,0.8,0.4,1.0))
        p.plot3d(lambda x,y: math.sin(x)*math.cos(y))
        p.show()

    Example (in Unreal):
        p = create_plotter(world=get_world(),
                           origin=FVector(0,0,500),
                           debug=True)
        p.grid(True)
        p.plot(lambda x: x**2)
        p.show()
    """
    bounds = PlotBounds(x_range, y_range, z_range, units_per_uu)
    return MathPlotter(world=world, origin=origin,
                       bounds=bounds, zoom=zoom,
                       ga_backend=ga_backend,
                       debug=debug, advanced_debug=advanced_debug)
