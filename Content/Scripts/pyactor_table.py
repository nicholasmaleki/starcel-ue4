"""
pyactor_table.py — PyActor component hosting an UnrealTableRenderer

Spawn via spawn_table_actor(...) in ue_spawn.py. The PyActor owns the
renderer's per-frame tick so drag-to-resize on gridlines works without
any Main.tick forwarding — begin_play creates the renderer + hooks up
the PlayerController, tick(dt) calls renderer.tick_resize(dt).

Pattern mirrors pyactor_gizmo.GizmoController (self-ticking interaction
host) and pyactor_plotter.PyActorPlotter (class-level attribute config).

Usage (PIE console):
    from ue_spawn import spawn_table_actor
    from nd_table.ndtable import Table
    t = Table(shape=(3, 3))
    t[(0, 0)] = 'A'; t[(0, 1)] = 'B'; t[(0, 2)] = 'C'
    actor = spawn_table_actor(t, location=FVector(0, 500, 500))

Change the rendered table at runtime:
    actor.get_py_proxy().set_table(new_table)
"""

import unreal_engine as ue
from unreal_engine_tools import get_world


class PyActorTable:
    """
    PyActor that wraps an UnrealTableRenderer and ticks its resize
    controller. Set attributes post-spawn (orientation, cell_spacing,
    render_gridlines, render_text, enable_resize), then assign a table
    via set_table() to kick off the first render.
    """

    # Class-level defaults — override on the instance after spawn_pyactor
    # returns, before calling set_table().
    orientation      = 'wall_table'
    cell_spacing     = 100.0
    render_gridlines = True
    render_text      = True
    enable_resize    = True
    table            = None

    def begin_play(self):
        self.renderer  = None
        self._table    = self.table        # lock in class attr snapshot
        self._location = self.uobject.get_actor_location()

        # Enable click events for the resize controller's cursor traces.
        self._pc = None
        try:
            self.uobject.enable_input()
            self._pc = self.uobject.get_player_controller()
            if self._pc is not None:
                self._pc.bEnableClickEvents     = True
                self._pc.bEnableMouseOverEvents = True
        except Exception as e:
            ue.log_warning(f'PyActorTable: click setup failed: {e}')

        # If a table was already set as a class-level/instance attribute
        # before begin_play fired, render it now. Otherwise wait for
        # set_table() from the caller.
        if self._table is not None:
            self._render()

    def set_table(self, table, render=True):
        """Swap in a new Table and (optionally) re-render immediately."""
        self._table = table
        self.table  = table
        if render:
            self._render()

    def set_player_controller(self, pc):
        """Wire a PlayerController after the fact (if begin_play didn't
        find one). The resize controller needs it for cursor traces."""
        self._pc = pc
        if self.renderer is not None:
            try:
                self.renderer.set_player_controller(pc)
            except Exception:
                pass

    def rerender(self):
        """Force a rebuild with the current cached table."""
        if self._table is not None:
            self._render()

    def _render(self):
        from nd_table.unreal_integration import UnrealTableRenderer

        # Destroy prior actors on repeat renders
        if self.renderer is not None:
            try:
                from nd_table.unreal_integration import UnrealTableRenderer as _UTR
                for a in list(self.renderer.cell_actors.values()):
                    try:
                        a.actor_destroy()
                    except Exception:
                        pass
                for a in list(self.renderer.gridline_actors):
                    try:
                        a.actor_destroy()
                    except Exception:
                        pass
                self.renderer.cell_actors     = {}
                self.renderer.gridline_actors = []
                self.renderer.gridline_metadata = {}
            except Exception:
                pass
            self.renderer = None

        try:
            self.renderer = UnrealTableRenderer(
                world=get_world(),
                cell_spacing=self.cell_spacing,
                orientation_preset=self.orientation,
                text_mode='3d',
                enable_resize=self.enable_resize,
                player_controller=self._pc,
            )
        except Exception as e:
            ue.log_warning(f'PyActorTable: UnrealTableRenderer init failed: {e}')
            return

        try:
            self.renderer.render_table(
                self._table,
                world_location=self._location,
                render_gridlines=self.render_gridlines,
                render_text=self.render_text,
            )
        except Exception as e:
            ue.log_warning(f'PyActorTable: render_table failed: {e}')

    def tick(self, dt):
        if self.renderer is None:
            return
        # Lazy PC hookup — first tick may succeed when begin_play didn't.
        if self._pc is None:
            try:
                self._pc = self.uobject.get_player_controller()
                if self._pc is not None:
                    self.renderer.set_player_controller(self._pc)
            except Exception:
                pass
        try:
            self.renderer.tick_resize(dt)
        except Exception:
            pass

    # Convenience proxies so callers can treat the PyActor as a renderer

    @property
    def cell_actors(self):
        return self.renderer.cell_actors if self.renderer else {}

    @property
    def gridline_actors(self):
        return self.renderer.gridline_actors if self.renderer else []
