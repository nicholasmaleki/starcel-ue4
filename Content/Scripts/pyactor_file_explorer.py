import os
import subprocess
import unreal_engine as ue
from unreal_engine import FVector, FRotator, FTransform
from unreal_engine_tools import get_world

try:
    from unreal_engine.classes import StaticMeshActor, StaticMesh, Material
    from unreal_engine.enums import EComponentMobility, ECollisionChannel
except Exception:
    StaticMeshActor    = None
    StaticMesh         = None
    Material           = None
    EComponentMobility = None
    ECollisionChannel  = None

# ---------------------------------------------------------------------------
# Python component: file browser backed by EverythingAPI + nd_table
#
# Blueprint requirements (BP_FileExplorer):
#   - Python component → pyactor_file_explorer.FileExplorer
#   - No mesh required; actor is a Python host only
#   - Project Settings → Input → Enable Click Events = ON
#
# Dependencies:
#   everything_api.py       EverythingAPI — requires Everything daemon + DLL
#   nd_table/               Table + UnrealTableRenderer
#   icon_to_image.py        extract_icon (per-file shell icon → PIL)
#   unreal_engine_tools.py  pil_image_to_texture
#
# Layout (head-on view, looking -X):
#
#     Icon | Name  | Size | Date | Type     ← header row (Z=0)
#     [📄] file1   10 KB  ...    .txt       ← each file = one horizontal row
#     [📁] folder  —      ...    folder
#     [🖼 ] pic.png 2 MB   ...    .png
#     ↑
#   leftmost icon column (one icon per file row)
#
# Click detection follows the gizmo pattern:
#   - Icon cubes have collision enabled (SetActorEnableCollision(True))
#   - tick() polls get_hit_result_under_cursor every frame
#   - Rising-edge on LeftMouseButton opens the file via `cmd /c start chrome`
#
# Usage:
#   actor = spawn_file_explorer(location=FVector(0, 0, 0))
# ---------------------------------------------------------------------------


def _human_bytes(n):
    """Convert byte count to human-readable string."""
    try:
        n = float(n)
    except (TypeError, ValueError):
        return '?'
    for unit in ('B', 'KB', 'MB', 'GB', 'TB'):
        if n < 1024.0:
            return f'{n:.1f} {unit}'
        n /= 1024.0
    return f'{n:.1f} PB'


def _open_with_chrome(path):
    """
    Open *path* in Chrome via `cmd /c start chrome "<path>"`.
    Chrome will render URLs/HTML/images directly; for other file types it
    falls through to its configured handler.
    """
    try:
        subprocess.Popen(
            ['cmd', '/c', 'start', 'chrome', path],
            shell=False,
            creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0),
        )
        ue.log(f'FileExplorer: cmd /c start chrome "{path}"')
    except Exception as e:
        ue.log_warning(f'FileExplorer: cmd chrome launch failed: {e}')


class FileExplorer:
    """
    File browser PyActor component.

    Renders a table of files with one row per file, columns laid out as
    ``[icon] Name | Size | Date | Type`` in a normal spreadsheet layout.
    Each icon cube is clickable (gizmo-style tick cursor-trace) and opens
    the file/folder with Chrome via the Windows shell ``start`` command.
    """

    DEFAULT_FOLDER = os.path.expanduser('~')
    MAX_FILES      = 50

    # Icon column tuning
    ICON_SIZE_UU      = 80.0   # edge length of the icon quad in world units
    ICON_LEFT_OFFSET  = 120.0  # how far left of the Name column the icon sits
    ICON_MATERIAL     = '/Game/Materials/M_Icon.M_Icon'
    ICON_PARAM        = 'Texture'

    def begin_play(self):
        self.api          = None
        self.renderer     = None
        self._results     = []
        self._icon_actors = []           # hold refs so GC doesn't eat them
        self._click_map   = {}           # icon_actor → file item dict
        self._was_mouse_down = False

        self.location = self.uobject.get_actor_location()

        # ---- Player controller: enable click events ----------------------
        try:
            self.uobject.enable_input()
            self.player_controller = self.uobject.get_player_controller()
            if self.player_controller is not None:
                self.player_controller.bEnableMouseOverEvents = True
                self.player_controller.bEnableClickEvents     = True
                if ECollisionChannel is not None:
                    self.player_controller.CurrentClickTraceChannel = \
                        ECollisionChannel.ECC_WorldDynamic
        except Exception as e:
            ue.log_warning(f'FileExplorer: click setup failed: {e}')
            self.player_controller = None

        # ---- EverythingAPI -----------------------------------------------
        try:
            from everything_api import EverythingAPI
            self.api = EverythingAPI()
            ue.log(f'FileExplorer: EverythingAPI ready on {self.uobject.get_name()}')
        except Exception as e:
            ue.log_warning(
                f'FileExplorer: EverythingAPI unavailable ({e}). '
                'Make sure Everything (Voidtools) is running and '
                'Everything64.dll is accessible.')

        # ---- Table renderer ----------------------------------------------
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

        # ---- Initial listing ---------------------------------------------
        self.current_folder = self.DEFAULT_FOLDER
        self.refresh()

    # -----------------------------------------------------------------------
    # Tick — gizmo-style cursor trace for icon clicks
    # -----------------------------------------------------------------------

    def tick(self, dt):
        if not self._click_map or self.player_controller is None:
            return

        try:
            hit = self.uobject.get_hit_result_under_cursor(
                ECollisionChannel.ECC_WorldDynamic)
        except Exception:
            return

        hit_actor = hit.actor if hit else None

        # Rising-edge click detection
        mouse_down = self._is_mouse_down()
        if mouse_down and not self._was_mouse_down:
            if hit_actor is not None and hit_actor in self._click_map:
                item = self._click_map[hit_actor]
                self._on_file_click(item)
        self._was_mouse_down = mouse_down

    def _is_mouse_down(self):
        try:
            from unreal_engine import FKey
            return self.player_controller.IsInputKeyDown(FKey('LeftMouseButton'))
        except Exception:
            pass
        try:
            return self.player_controller.IsInputKeyDown('LeftMouseButton')
        except Exception:
            return False

    # -----------------------------------------------------------------------
    # Public navigation API
    # -----------------------------------------------------------------------

    def navigate_to(self, folder):
        """Navigate into *folder* and re-render the table."""
        self.current_folder = folder
        self.refresh()

    def search(self, query, max_results=None):
        """
        Run an EverythingAPI query and render results as a table.
        query can be a folder path or any Everything search expression.
        """
        if self.api is None:
            ue.log_warning('FileExplorer.search: EverythingAPI not available.')
            return
        n = max_results or self.MAX_FILES
        try:
            results = self.api.search(query, max_results=n)
        except Exception as e:
            ue.log_warning(f'FileExplorer.search("{query}"): {e}')
            results = []
        self._results = results
        self._render(results)

    def refresh(self):
        """Re-scan current_folder."""
        self.search(self.current_folder)

    # -----------------------------------------------------------------------
    # Rendering — files as rows, fields as columns (head-on spreadsheet)
    # -----------------------------------------------------------------------

    def _render(self, results):
        if self.renderer is None:
            return

        from nd_table.ndtable import Table

        headers = ['Name', 'Size', 'Date', 'Type']
        rows    = len(results)

        # wall_table axis mapping:
        #   axis 0 → +Y (right)  = file rows (0=header, 1..N)
        #   axis 1 → -Z (down)   = columns (Name, Size, Date, Type)
        # So shape = (rows+1, num_columns).
        # Cell (row, col): row 0 = header; col 0 = Name column (leftmost).
        t = Table(shape=(rows + 1, len(headers)))

        # Header row
        for ci, h in enumerate(headers):
            t[(0, ci)] = h

        # Data rows
        for ri, item in enumerate(results):
            name = item.get('name', '')
            size = _human_bytes(item.get('size', 0))
            date = ''   # EverythingAPI default flags don't include date_modified
            ext  = 'folder' if item.get('is_folder') else \
                   os.path.splitext(name)[1] or '?'
            t[(ri + 1, 0)] = name
            t[(ri + 1, 1)] = size
            t[(ri + 1, 2)] = date
            t[(ri + 1, 3)] = ext

        try:
            self.renderer.render_table(t, world_location=self.location)
            ue.log(f'FileExplorer: rendered {rows} items at {self.location}')
        except Exception as e:
            ue.log_warning(f'FileExplorer._render: renderer failed: {e}')
            return

        self._spawn_row_icons(results)

    # -----------------------------------------------------------------------
    # Icon column
    # -----------------------------------------------------------------------

    def _spawn_row_icons(self, results):
        """
        Extract a shell-icon PIL image for every row and spawn a clickable
        cube to the LEFT of each file row's Name cell, forming a vertical
        icon column.

        Layout (head-on):
            [icon_0]  file0_name  file0_size  file0_date  file0_type
            [icon_1]  file1_name  file1_size  ...
            [icon_2]  file2_name  ...
               ↑
          icon_x = name_x - ICON_LEFT_OFFSET
          icon_z = name_z (one icon per file row)
        """
        # Free any previously-spawned icons (re-render case)
        for a in self._icon_actors:
            try:
                a.actor_destroy()
            except Exception:
                pass
        self._icon_actors = []
        self._click_map   = {}

        if not hasattr(self.renderer, 'cell_actors'):
            return
        if StaticMeshActor is None:
            ue.log_warning('FileExplorer: StaticMeshActor class unavailable — '
                           'cannot spawn icon column.')
            return

        try:
            from icon_to_image import extract_icon
        except Exception as e:
            ue.log_warning(f'FileExplorer: icon_to_image unavailable: {e}')
            return

        try:
            from unreal_engine_tools import pil_image_to_texture
        except Exception as e:
            ue.log_warning(f'FileExplorer: pil_image_to_texture unavailable: {e}')
            return

        # Load the material once
        mat = None
        try:
            mat = ue.load_object(Material, self.ICON_MATERIAL)
        except Exception:
            mat = None
        if mat is None:
            ue.log_warning(
                f'FileExplorer: material "{self.ICON_MATERIAL}" not found; '
                'icons will be untextured.')

        # Cube mesh for the picture-frame quad
        try:
            cube_mesh = ue.load_object(StaticMesh, '/Engine/BasicShapes/Cube.Cube')
        except Exception as e:
            ue.log_warning(f'FileExplorer: could not load Cube mesh: {e}')
            return

        world = get_world()
        spawned = 0

        for idx, cell_actor in self.renderer.cell_actors.items():
            # Table shape is (rows+1, cols).  idx = (row, col).
            # Name cells are at col=0, rows 1..N (row 0 is the header).
            if not isinstance(idx, tuple) or len(idx) < 2:
                continue
            row_idx, col_idx = idx[0], idx[1]
            if col_idx != 0 or row_idx == 0:
                continue
            if row_idx - 1 >= len(results):
                continue

            item = results[row_idx - 1]
            full = item.get('full_path') or item.get('name')
            if not full:
                continue

            # 1) Get icon as PIL image
            pil_img = None
            try:
                info = extract_icon(full)   # dict with 'image' PIL key
                if info:
                    pil_img = info.get('image') or info.get('pil_image')
            except Exception as e:
                if self.renderer.debug:
                    ue.log_warning(
                        f'FileExplorer: extract_icon("{full}"): {e}')

            if pil_img is None:
                continue

            # 2) Convert to transient texture
            try:
                tex = pil_image_to_texture(pil_img)
            except Exception as e:
                ue.log_warning(
                    f'FileExplorer: pil_image_to_texture failed for '
                    f'"{full}": {e}')
                continue
            if tex is None:
                continue

            # 3) Place the icon to the LEFT of the Name cell
            try:
                name_loc = cell_actor.get_actor_location()
            except Exception:
                continue
            scale_xy = self.ICON_SIZE_UU / 100.0
            icon_loc = FVector(
                name_loc.x,
                name_loc.y - self.ICON_LEFT_OFFSET,  # LEFT on Y (wall_table)
                name_loc.z,                           # same row as Name cell
            )
            icon_scale = FVector(0.05, scale_xy, scale_xy)

            # 4) Spawn a cube, set mesh, mobility, MID with texture, collision
            try:
                actor = world.actor_spawn(StaticMeshActor)
                smc   = actor.StaticMeshComponent
                smc.SetStaticMesh(cube_mesh)
                if EComponentMobility is not None:
                    smc.Mobility = EComponentMobility.Movable
                if mat is not None:
                    try:
                        mid = smc.create_material_instance_dynamic(mat)
                        mid.set_material_texture_parameter(self.ICON_PARAM, tex)
                        smc.set_material(0, mid)
                    except Exception as e:
                        ue.log_warning(
                            f'FileExplorer: MID setup failed for '
                            f'"{full}": {e}')
                actor.set_actor_transform(
                    FTransform(icon_loc, FRotator(0, 0, 0), icon_scale))
                # Gizmo-style click: collision must be enabled for cursor trace
                try:
                    actor.SetActorEnableCollision(True)
                except Exception:
                    pass
                self._icon_actors.append(actor)
                self._click_map[actor] = item
                spawned += 1
            except Exception as e:
                ue.log_warning(
                    f'FileExplorer: icon spawn failed for "{full}": {e}')

        ue.log(f'FileExplorer: spawned {spawned} row icons')

    # -----------------------------------------------------------------------
    # Click handler — open with cmd /c start chrome "<path>"
    # -----------------------------------------------------------------------

    def _on_file_click(self, item):
        full = item.get('full_path') or item.get('name', '')
        if not full:
            return
        if item.get('is_folder'):
            ue.log(f'FileExplorer: navigating to "{full}"')
            # Still open in Chrome (file://) AND navigate the in-world table
            _open_with_chrome(full)
            self.navigate_to(full)
        else:
            ue.log(f'FileExplorer: opening file "{full}"')
            _open_with_chrome(full)
