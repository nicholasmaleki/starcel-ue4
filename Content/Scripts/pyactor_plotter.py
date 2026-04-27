"""
pyactor_plotter.py — PyActor component for MathPlotter
=======================================================
Spawn via spawn_plot(...) in ue_spawn.py — dynamic PyActor, no Blueprint
placeholder required. Everything is configured in Python on the proxy.

The actor's world location is used as the plot origin.

Usage from PIE console:
    from ue_spawn import spawn_plot
    actor = spawn_plot('sin(x)+cos(y)', location=FVector(0, 500, 0))

Change function at runtime (keep a reference to the returned actor):
    actor.get_py_proxy().set_function('x**2 - y**2')
    actor.get_py_proxy().set_function('sin(sqrt(x**2+y**2))', plot_type='heatmap')
"""

import unreal_engine as ue
from unreal_engine import FVector
from unreal_engine_tools import get_world
import math


# Expression compiler

_SAFE_MATH = {
    'sin': math.sin, 'cos': math.cos, 'tan': math.tan,
    'sqrt': math.sqrt, 'log': math.log, 'exp': math.exp,
    'abs': abs, 'pi': math.pi, 'e': math.e,
    'sinh': math.sinh, 'cosh': math.cosh, 'tanh': math.tanh,
    'asin': math.asin, 'acos': math.acos, 'atan': math.atan,
    'atan2': math.atan2, 'pow': pow, 'min': min, 'max': max,
}


def _compile(expr):
    """Compile a string expression into a callable f(x, y)."""
    try:
        code = compile(expr, '<plot>', 'eval')
        def fn(x, y):
            ns = dict(_SAFE_MATH, x=x, y=y)
            try:
                return float(eval(code, {"__builtins__": {}}, ns))
            except Exception:
                return 0.0
        fn.__name__ = expr
        return fn
    except Exception as exc:
        ue.log_warning(f'PyActorPlotter: bad expression "{expr}": {exc}')
        return lambda x, y: math.sin(x) + math.cos(y)


# PyActor component

class PyActorPlotter:
    """
    Self-contained plotter PyActor component.
    Set attributes, then call render() or set_function() to (re-)draw.

    Attributes
    ----------
    function_expr : str    — math expression, default 'sin(x)+cos(y)'
    plot_type     : str    — 'surface' | 'heatmap' | 'contour' | 'wireframe'
    mesh_mode     : str    — 'triangles' | 'spheres' | 'sphere_lines' | 'curvable_plane'
    orientation   : str    — 'ground_table' | 'wall_table' | 'wall_graph'
    resolution    : int    — grid samples per axis
    x_range       : tuple  — (x_min, x_max)
    y_range       : tuple  — (y_min, y_max)
    z_range       : tuple  — (z_min, z_max)
    units_per_uu  : float  — math units per 100 UE units
    show_grid     : bool
    """

    # Defaults
    function_expr = 'sin(x)+cos(y)'
    plot_type = 'surface'
    mesh_mode = 'triangles'
    orientation = 'ground_table'
    resolution = 32
    x_range = (-math.pi, math.pi)
    y_range = (-math.pi, math.pi)
    z_range = (-2.0,  2.0)
    units_per_uu = 100.0
    show_grid = True

    def begin_play(self):
        self._plotter = None
        self.render()

    # #

    def render(self):
        """Create plotter from current attributes and render."""
        from ue_math_plotter import create_plotter

        # Destroy previous render actors
        if self._plotter is not None:
            try:
                self._plotter.clear()
            except Exception:
                pass
            self._plotter = None

        origin = self.uobject.get_actor_location()
        fn = _compile(self.function_expr)

        try:
            p = create_plotter(
                world = get_world(),
                origin = origin,
                x_range = self.x_range,
                y_range = self.y_range,
                z_range = self.z_range,
                units_per_uu = self.units_per_uu,
                orientation = self.orientation,
            )
        except Exception as exc:
            ue.log_warning(f'PyActorPlotter: create_plotter failed: {exc}')
            return

        p.mesh_mode = self.mesh_mode
        p.labs(title=self.function_expr, x='x', y='y', z='z')

        if self.show_grid:
            grid_mode = '3d' if self.plot_type in ('surface', 'wireframe') else '2d'
            p.grid(True, mode=grid_mode)

        pt = self.plot_type.lower().strip()
        try:
            if pt == 'heatmap':
                p.heatmap(fn, resolution=self.resolution)
            elif pt == 'contour':
                p.contour(fn)
            elif pt == 'wireframe':
                p.wireframe(fn, resolution=self.resolution)
            else:
                p.colormap_surface(fn, resolution=self.resolution)
        except Exception as exc:
            ue.log_warning(f'PyActorPlotter: {pt} failed: {exc}, trying plot3d fallback')
            try:
                p.plot3d(fn, resolution=max(8, self.resolution // 2))
            except Exception as exc2:
                ue.log_warning(f'PyActorPlotter: plot3d fallback failed: {exc2}')
                return

        try:
            p.show()
        except Exception as exc:
            ue.log_warning(f'PyActorPlotter: show() failed: {exc}')
            return

        self._plotter = p
        ue.log(f'PyActorPlotter: rendered "{self.function_expr}" as {pt} '
               f'res={self.resolution} @ {origin}')

    # #

    def set_function(self, expr, plot_type=None, resolution=None):
        """
        Change the plotted function and re-render immediately.

        Examples (PIE console):
            pc = actor.get_component('Python')
            pc.set_function('x**2 - y**2')
            pc.set_function('sin(sqrt(x**2+y**2))', plot_type='heatmap', resolution=48)
        """
        self.function_expr = expr
        if plot_type  is not None: self.plot_type = plot_type
        if resolution is not None: self.resolution = resolution
        self.render()

    def refresh(self):
        """Re-render with current settings."""
        self.render()
