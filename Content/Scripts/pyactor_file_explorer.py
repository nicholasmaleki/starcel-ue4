import os
import unreal_engine as ue
from unreal_engine import FVector

from unreal_engine_tools import get_world
from utils import human_size

# Python component: file browser backed by EverythingAPI + nd_table.
#
# Layout (head-on view, wall_table orientation):
#
#         Name      Size     Date     Type    <- header row (Z = 0)
#   [i]   file1     10 KB    ...      .txt    <- each file is a row going down
#   [i]   folder    -        ...      folder
#   [i]   pic.png   2 MB     ...      .png
#   ^
#   icon column: a real (empty-headered) column 0 in the table; icons sit at
#   the cell center, so spacing matches the rest of the grid exactly.
#
# BP_Icon hosts pyactor_icon.IconSphere, which handles hover-shrink and
# click-to-open via the OS default handler (same as Windows Explorer
# double-click).  The PyActor owns no tick — IconSphere owns its own.


class FileExplorer:
    """PyActor that renders a file browser table with a BP_Icon column."""

    DEFAULT_FOLDER    = os.path.join(os.path.expanduser('~'), 'Desktop')
    MAX_FILES         = 20
    ICON_COL          = 0      # leading empty column reserved for icons
    ICON_COL_WIDTH    = 120.0  # UU; cell width — icon size derives from this
    ICON_FILL         = 0.336  # icon diameter as fraction of min(row_h, col_w)
    SPHERE_BASE_DIAM  = 100.0  # /Engine/BasicShapes/Sphere natural diameter

    def begin_play(self):
        self.api          = None
        self.renderer     = None
        self._icon_actors = []    # hold refs so GC doesn't eat them

        self.location = self.uobject.get_actor_location()
        self.current_folder = getattr(self.uobject, 'initial_path',
                                      None) or self.DEFAULT_FOLDER

        try:
            from everything_api import EverythingAPI
            self.api = EverythingAPI()
        except Exception as e:
            ue.log_warning(
                f'FileExplorer: EverythingAPI unavailable ({e}). '
                'Make sure Everything (Voidtools) is running and '
                'Everything64.dll is accessible.')
            return

        try:
            from nd_table.unreal_integration import UnrealTableRenderer
            self.renderer = UnrealTableRenderer(
                world=get_world(),
                cell_spacing=120.0,
                orientation_preset='wall_table',
                text_mode='3d',
            )
        except Exception as e:
            ue.log_warning(f'FileExplorer: UnrealTableRenderer unavailable: {e}')
            return

        self.refresh()

    def refresh(self):
        """Scan current_folder via Everything and render the table + icons."""
        results = self._query_folder(self.current_folder)
        self._render(results)

    def _query_folder(self, folder):
        """Run a scoped Everything query — quoted path limits to that folder.

        Mirrors the pattern used in sysinfo.py on master:
            api.count(r'"C:\\Users\\you\\Downloads"')
        """
        query = f'"{folder}"'
        try:
            return self.api.search(query, max_results=self.MAX_FILES)
        except Exception as e:
            ue.log_warning(f'FileExplorer.search({query!r}): {e}')
            return []

    def _render(self, results):
        from nd_table.ndtable import Table

        # Free previously-spawned icons if we're re-rendering.
        for a in self._icon_actors:
            try:
                a.actor_destroy()
            except Exception:
                pass
        self._icon_actors = []

        # Column 0 is the icon column. Each cell in it is set to an empty
        # string so the renderer spawns a (text-less) cell actor we can use as
        # a position anchor for the icon. The auto-sizer would otherwise shrink
        # the column to ~20UU since empty Text3D measures near zero, so we
        # override the column width with set_user_size below.
        headers = ['', 'Name', 'Size', 'Date', 'Type']
        n_cols  = len(headers)
        n_rows  = len(results) + 1   # header + N files

        # wall_table: axis 0 -> +Y (right), axis 1 -> -Z (down).
        # So axis 0 = columns (go across), axis 1 = rows (go down).
        # Shape is (cols, rows); indexing is t[col, row].
        t = Table(shape=(n_cols, n_rows))

        for ci, h in enumerate(headers):
            t[(ci, 0)] = h

        for ri, item in enumerate(results):
            name = item.get('name', '')
            full = item.get('full_path') or name
            is_folder = item.get('is_folder', False)
            ext = 'folder' if is_folder else (os.path.splitext(name)[1] or '?')
            t[(self.ICON_COL, ri + 1)] = ''
            t[(1, ri + 1)] = name
            t[(2, ri + 1)] = '-' if is_folder else (human_size(item.get('size')) or '?')
            t[(3, ri + 1)] = self._mtime_str(full)
            t[(4, ri + 1)] = ext

        # Reserve a fixed width for the icon column. axis 0 in this table is
        # the column axis (shape=(n_cols, n_rows)), and the renderer maps
        # axis 0 -> cell_width_per_row (the Y-extent of each column slot).
        self.renderer.set_user_size(0, self.ICON_COL, self.ICON_COL_WIDTH)

        try:
            self.renderer.render_table(t, world_location=self.location)
            ue.log(f'FileExplorer: rendered {len(results)} items from '
                   f'"{self.current_folder}"')
        except Exception as e:
            ue.log_warning(f'FileExplorer._render: renderer failed: {e}')
            return

        self._spawn_icon_column(results)

    def _mtime_str(self, path):
        try:
            ts = os.path.getmtime(path)
        except OSError:
            return ''
        import datetime
        return datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d')

    def _spawn_icon_column(self, results):
        """Spawn one BP_Icon per file at the center of its reserved cell in the
        leftmost (empty-headered) column.

        Uses spawn_icon_from_path so each icon is a BP_Icon with IconSphere
        attached — hover-shrink + click-to-open-with-default-app come for free.
        """
        if not hasattr(self.renderer, 'cell_actors'):
            return

        try:
            from ue_spawn import spawn_icon_from_path
        except Exception as e:
            ue.log_warning(f'FileExplorer: spawn_icon_from_path unavailable: {e}')
            return

        spawned = 0

        for ri, item in enumerate(results):
            full = item.get('full_path') or item.get('name')
            if not full:
                continue

            icon_cell = self.renderer.cell_actors.get((self.ICON_COL, ri + 1))
            if icon_cell is None:
                continue

            try:
                cell_loc = icon_cell.get_actor_location()
            except Exception:
                continue

            # Cell actor location is the Text3D pivot — top-left corner of
            # the cell in wall_table orientation (axis 0 = +Y, axis 1 = -Z).
            # The sphere mesh is center-pivoted, so to land it in the cell
            # center we shift +width/2 along Y and -height/2 along Z.
            row_h = self.renderer.get_effective_size(1, ri + 1)
            col_w = self.renderer.get_effective_size(0, self.ICON_COL)
            icon_loc = FVector(
                cell_loc.x,
                cell_loc.y + col_w / 2.0,
                cell_loc.z - row_h / 2.0,
            )

            target = max(8.0, min(row_h, col_w) * self.ICON_FILL)
            s = target / self.SPHERE_BASE_DIAM
            scale_vec = FVector(s, s, s)

            try:
                actor = spawn_icon_from_path(
                    full,
                    location=icon_loc,
                    scale=scale_vec,
                    simulate_physics=False,   # stay put on the row
                )
            except Exception as e:
                ue.log_warning(
                    f'FileExplorer: spawn_icon_from_path failed for '
                    f'"{full}": {e}')
                continue

            if actor is not None:
                self._icon_actors.append(actor)
                spawned += 1

        ue.log(f'FileExplorer: spawned {spawned} icons in leftmost column')
