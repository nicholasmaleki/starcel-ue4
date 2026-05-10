import unreal_engine as ue
from unreal_engine import FVector, FRotator, FTransform
from unreal_engine.enums import ECollisionChannel, EInputEvent
from unreal_engine_tools import find_component, get_world
from pyactor_global_click import PyActorGlobalClick

# Python component: click + hover + typing for any actor with a Text3DComponent
#
# Per-instance behaviour (one PyActorText3D per actor):
#   - hover-scale animation
#   - tick-based cursor poll for click detection (Text3DComponent has no
#     OnClicked event; OnBeginCursorOver / OnEndCursorOver are tried first
#     and fall back to tick-based polling)
#   - logs the clicked character (column/row + flat index when
#     CharacterMeshes is available)
#
# Class-level "typing system" (one set of state for the whole scene,
# absorbed from the previous test_text3d_click closure-based prototype):
#   - tracks every PyActorText3D-bearing actor in the world via _watched
#     (begin_play auto-registers itself; external callers can also use
#     PyActorText3D.register_actor for non-PyActorText3D actors).
#   - owns the singleton PyActorCursor (insertion caret) and the highlight-
#     box pool used to render multi-line selections.
#   - drives a Win32 keyboard poll (GetAsyncKeyState + ToUnicode) so the
#     focused actor types like notepad: layout-correct characters, Shift
#     selection, Ctrl shortcuts (A/C/X/V/Tab, arrows, Home/End), and
#     Ctrl+V image paste via PIL ImageGrab.
#   - mouse polling is also Win32 (VK_LBUTTON) so callers don't have to
#     thread an input_manager / HotkeyManager through.
#   - mirrors focus to PyActorGlobalClick.set_focused_actor so other
#     systems (PyPawnDrone WASD, PyActorText3DExecutor) can read it.
#
# Bootstrap is lazy: the FIRST actor whose begin_play runs spawns the
# PyActorGlobalClick singleton, attaches the global tick, and initialises
# ctypes. Subsequent PyActorText3D.begin_plays just register themselves.
#
# Blueprint requirements:
#   - A Text3DComponent (any name; first one found is used)
#   - A Python component pointing to pyactor_text3d.PyActorText3D
#
# Project Settings -> Input:
#   - Enable Mouse Over Events = ON
#   - Enable Click Events      = ON
#
# Character coordinate system (default font size / wall_table orientation):
#   Y axis = character advance (left -> right), col = local_y / CHAR_WIDTH
#   Z axis = line descent      (up  ->  down),  row = -local_z / CHAR_HEIGHT
#
# Insertion cursor architecture
# ------------------------------
# A single PyActorCursor is spawned lazily on first use and shared across
# all Text3D actors in the scene (only one caret is ever visible).  This
# class owns it and exposes class methods for callers to position / show /
# hide it.  Sizing/placement tunables live here as class constants — see
# CURSOR_WIDTH_FRAC / CURSOR_VERTICAL_OFFSET_FRAC / CURSOR_DIACRITIC_HEADROOM_FRAC.

class PyActorText3D:
    """
    Hover + click + scene-global typing for a Text3DComponent-based actor.

    Click detection is tick-based (Text3DComponent has no OnClicked event).
    Hover detection tries component events first, falls back to tick polling.

    Class-level cursor singleton: see show_cursor_at / hide_cursor /
    compute_placement.  Class-level typing system: see register_actor /
    _ensure_global_typing / _global_tick.
    """

    HOVER_DELTA = 0.3
    LERP_SPEED = 8.0

    # Approximate UE units per character at the default Text3D font size (100).
    # Tune to match the actual font size in your Blueprint.
    CHAR_WIDTH = 50.0
    CHAR_HEIGHT = 50.0

    TEXT_COMPONENT_NAME = 'Text3DComponent'

    # Cursor visual tunables (used by compute_placement)
    # CURSOR_WIDTH_FRAC      — caret bar thickness as fraction of glyph width.
    # CURSOR_VERTICAL_OFFSET_FRAC — how far the caret is shifted DOWN from the
    #     bounds-vertical-center, expressed as a fraction of glyph height.
    #     1.0 drops the caret by one full row (corrects for Text3D bounds
    #     reporting the top of the line, not its center).
    # CURSOR_DIACRITIC_HEADROOM_FRAC — extra height added above the bounds top
    #     (fraction of tight bounds) so accents/^ aren't clipped.
    CURSOR_WIDTH_FRAC = 0.068
    CURSOR_VERTICAL_OFFSET_FRAC = .9
    CURSOR_DIACRITIC_HEADROOM_FRAC = 0.50
    CURSOR_HEIGHT_MULTIPLIER = 1.2

    # ---- Class-level typing-system state ----
    # Set of all actors participating in the typing system.  begin_play
    # auto-adds self.uobject; external code can call register_actor for
    # other actors (e.g. table cells without a PyActorText3D component).
    _watched = set()
    # Optional table renderer per actor for refit-on-unfocus.  Populated
    # only by callers that pass renderer= to register_actor.
    _watched_renderer = {}
    # Caret state (caret==anchor means no selection, anchor!=caret = range).
    _string_idx = 0
    _anchor = 0
    # Pool of translucent boxes used to render multi-segment selection
    # highlights — grown lazily, hidden between uses.
    _highlight_actors = []
    # Inline image actors pasted via Ctrl+V; tuples of
    # (host_actor, image_actor, placeholder_start, placeholder_len, w_uu, h_uu).
    _inline_images = []
    # Win32 ctypes handles + state, populated by _ensure_global_typing.
    _ctypes = None
    _user32 = None
    _kernel32 = None
    _WIN32_TYPING_OK = False
    # 256-byte rising-edge tracker for the keyboard poll.
    _prev_vk_down = bytearray(256)
    # Rising-edge tracker for the LMB poll (replaces input_manager).
    _prev_lbutton_down = False
    # The PyActorGlobalClick singleton holding the global tick.
    _global_actor = None
    # _ensure_global_typing idempotency flag.
    _typing_initialized = False

    _CF_UNICODETEXT = 13   # standard Windows clipboard format ID

    # Lifecycle

    def begin_play(self):
        self.uobject.enable_input()
        self.player_controller = self.uobject.get_player_controller()
        self.player_controller.bEnableMouseOverEvents = True
        self.player_controller.bEnableClickEvents = True
        self.player_controller.CurrentClickTraceChannel = ECollisionChannel.ECC_WorldDynamic

        self.base_scale = self.uobject.get_actor_scale()
        self.target_scale = self.base_scale

        self._was_mouse_down = False
        self._hovered = False

        # Find Text3DComponent
        self.text3d = None
        try:
            self.text3d = find_component(self.uobject, self.TEXT_COMPONENT_NAME)
        except Exception:
            pass
        if self.text3d is None:
            ue.log_warning(
                f'PyActorText3D: could not find "{self.TEXT_COMPONENT_NAME}" '
                f'on {self.uobject.get_name()}')
            return

        # Try to bind cursor-over events (may work depending on UEP build)
        self._component_hover = False
        try:
            self.text3d.bind_event('OnBeginCursorOver', self._comp_hover_begin)
            self.text3d.bind_event('OnEndCursorOver',   self._comp_hover_end)
            self._component_hover = True
            ue.log(f'PyActorText3D: cursor-over events bound on {self.uobject.get_name()}')
        except Exception as e:
            ue.log(
                f'PyActorText3D: cursor-over bind failed ({e}), '
                'using tick-based hover detection')

        # OnClicked is NOT supported on Text3DComponent — tick-based only
        ue.log(
            f'PyActorText3D: click detection is tick-based '
            f'on {self.uobject.get_name()}')

        # Add self to the scene-wide typing system + bootstrap it.
        # register_actor is idempotent and _ensure_global_typing
        # short-circuits after the first caller.
        PyActorText3D.register_actor(self.uobject)
        PyActorText3D._ensure_global_typing()

    # ---------------- Cursor singleton (class-level) ----------------
    #
    # Single shared PyActorCursor for the whole scene — only one caret
    # ever exists.  Spawned lazily on first show_cursor_at() call.

    _cursor_pyactor = None

    @classmethod
    def _get_or_spawn_cursor(cls, world_provider):
        """Return the singleton PyActorCursor proxy, spawning if needed.
        ``world_provider`` is any actor (used only to fetch a UWorld)."""
        if cls._cursor_pyactor is not None:
            try:
                proxy = cls._cursor_pyactor.get_py_proxy()
                if proxy is not None:
                    return proxy
            except Exception:
                pass
            cls._cursor_pyactor = None  # stale handle — respawn

        try:
            from ue_spawn import spawn_pyactor
            cls._cursor_pyactor = spawn_pyactor(
                'pyactor_cursor', 'PyActorCursor',
                components=[dict(class_name='StaticMeshComponent',
                                 name='Cube', root=True,
                                 mesh='/Engine/BasicShapes/Cube.Cube')],
                name='TextCursor')
        except Exception as e:
            ue.log_warning(f'PyActorText3D: cursor spawn failed: {e}')
            return None

        if cls._cursor_pyactor is None:
            return None
        try:
            return cls._cursor_pyactor.get_py_proxy()
        except Exception:
            return None

    @classmethod
    def show_cursor_at(cls, actor, target_glyph):
        """Move the singleton cursor to ``target_glyph`` on ``actor``.
        Returns True on success."""
        if actor is None:
            return False
        placement = cls.compute_placement(actor, target_glyph)
        if placement is None:
            return False
        proxy = cls._get_or_spawn_cursor(actor)
        if proxy is None:
            return False
        world_pt, scale_vec, rot = placement
        proxy.move_to(world_pt, scale_vec, rot)
        return True

    @classmethod
    def hide_cursor(cls):
        if cls._cursor_pyactor is None:
            return
        try:
            proxy = cls._cursor_pyactor.get_py_proxy()
        except Exception:
            return
        if proxy is not None:
            proxy.hide()

    @classmethod
    def compute_placement(cls, actor, target_glyph):
        """Compute (world_pt, scale_vec, rotation) for the caret at the
        left edge of glyph ``target_glyph`` on ``actor``.  ``target_glyph``
        may equal the glyph count (cursor sits one width past the last
        glyph).  Returns None on failure.

        The selection-highlight code uses this too, so it lives here as
        the single source of truth for caret/highlight geometry.
        """
        if actor is None:
            return None
        try:
            t3d = actor.get_actor_component(cls.TEXT_COMPONENT_NAME)
        except Exception:
            return None
        if t3d is None:
            return None

        kernings = None
        try:
            kernings = t3d.CharacterKernings
        except Exception:
            pass
        meshes = None
        try:
            meshes = t3d.CharacterMeshes
        except Exception:
            pass

        if not kernings or len(kernings) == 0:
            return None

        glyph_h = cls.CHAR_HEIGHT
        glyph_w = cls.CHAR_WIDTH

        # Read glyph dimensions from the reference mesh (target, clamped).
        ref_idx = target_glyph
        if ref_idx >= len(kernings):
            ref_idx = len(kernings) - 1
        if ref_idx < 0:
            ref_idx = 0
        if (meshes is not None
                and 0 <= ref_idx < len(meshes)
                and meshes[ref_idx] is not None):
            try:
                _, e = meshes[ref_idx].GetComponentBounds()
                glyph_h = e.z * 2.0
                glyph_w = e.y * 2.0
            except Exception:
                pass

        # target_rel = left edge of target glyph, or one width past the last.
        target_rel = None
        if 0 <= target_glyph < len(kernings) and kernings[target_glyph] is not None:
            try:
                target_rel = kernings[target_glyph].get_relative_location()
            except Exception:
                pass
        elif len(kernings) > 0 and kernings[-1] is not None:
            try:
                r = kernings[-1].get_relative_location()
                target_rel = FVector(r.x, r.y + glyph_w, r.z)
            except Exception:
                pass
        if target_rel is None:
            return None

        # Full vertical extent for caret height/center.
        full_top = None
        full_bot = None
        if meshes is not None:
            for m in meshes:
                if m is None:
                    continue
                try:
                    o, e = m.GetComponentBounds()
                    t = o.z + e.z
                    b = o.z - e.z
                    if full_top is None or t > full_top:
                        full_top = t
                    if full_bot is None or b < full_bot:
                        full_bot = b
                except Exception:
                    continue
        try:
            o, e = t3d.GetComponentBounds()
            t = o.z + e.z
            b = o.z - e.z
            if full_top is None or t > full_top:
                full_top = t
            if full_bot is None or b < full_bot:
                full_bot = b
        except Exception:
            pass

        actor_loc = actor.get_actor_location()
        actor_rot = actor.get_actor_rotation()

        if full_top is not None and full_bot is not None:
            tight = full_top - full_bot
            full_top += tight * cls.CURSOR_DIACRITIC_HEADROOM_FRAC
            cursor_h = full_top - full_bot
            cursor_z = (full_top + full_bot) * 0.5
        else:
            cursor_h = glyph_h
            cursor_z = actor_loc.z + target_rel.z

        world_pt = FVector(
            actor_loc.x + target_rel.x,
            actor_loc.y + target_rel.y,
            cursor_z - glyph_h * cls.CURSOR_VERTICAL_OFFSET_FRAC,
        )
        scale_vec = FVector(
            0.01,
            glyph_w * cls.CURSOR_WIDTH_FRAC / 100.0,
            (cursor_h / 100.0) * cls.CURSOR_HEIGHT_MULTIPLIER,
        )
        return world_pt, scale_vec, actor_rot

    def tick(self, dt):
        # Scale lerp
        cur = self.uobject.get_actor_scale()
        tgt = self.target_scale
        a = min(1.0, self.LERP_SPEED * dt)
        self.uobject.set_actor_scale(FVector(
            cur.x + (tgt.x - cur.x) * a,
            cur.y + (tgt.y - cur.y) * a,
            cur.z + (tgt.z - cur.z) * a,
        ))

        if self.text3d is None:
            return

        # Cursor hit this actor?
        hit = self.uobject.get_hit_result_under_cursor(ECollisionChannel.ECC_WorldDynamic)
        on_self = hit is not None and hit.actor == self.uobject

        # Tick-based hover fallback
        if not self._component_hover:
            if on_self and not self._hovered:
                self._hovered = True
                self.on_hover_begin(self.text3d)
            elif not on_self and self._hovered:
                self._hovered = False
                self.on_hover_end(self.text3d)

        # Click detection (rising-edge on left mouse button)
        mouse_down = self._is_mouse_down()
        if mouse_down and not self._was_mouse_down:
            if on_self:
                self._process_click(hit.impact_point)
        self._was_mouse_down = mouse_down

    # Hover callbacks (called by component events or tick fallback)

    def _comp_hover_begin(self, component):
        self._hovered = True
        self.on_hover_begin(component)

    def _comp_hover_end(self, component):
        self._hovered = False
        self.on_hover_end(component)

    def on_hover_begin(self, component):
        d = self.HOVER_DELTA
        bs = self.base_scale
        self.target_scale = FVector(bs.x + d, bs.y + d, bs.z + d)

    def on_hover_end(self, component):
        self.target_scale = self.base_scale

    # Click processing — world hit -> local coords -> character col/row

    def _process_click(self, world_pt):
        text = ''
        char_meshes = None
        if self.text3d is not None:
            try:
                text = str(self.text3d.Text or '')
            except Exception:
                pass
            try:
                char_meshes = self.text3d.CharacterMeshes
            except Exception:
                pass

        # Strategy 1: CharacterMeshes (proportional fonts)
        mesh_idx = None
        mesh_letter = None
        if char_meshes is not None and len(char_meshes) > 0:
            best_idx = -1
            best_dist = float('inf')
            for i, mesh in enumerate(char_meshes):
                if mesh is None:
                    continue
                try:
                    origin, extent = mesh.GetComponentBounds()
                    lo_y = origin.y - extent.y
                    hi_y = origin.y + extent.y
                    lo_z = origin.z - extent.z
                    hi_z = origin.z + extent.z
                    in_y = lo_y <= world_pt.y <= hi_y
                    in_z = lo_z <= world_pt.z <= hi_z
                    if in_y and in_z:
                        best_idx = i
                        break
                    mid_y = (lo_y + hi_y) / 2.0
                    d = abs(world_pt.y - mid_y)
                    if d < best_dist:
                        best_dist = d
                        best_idx = i
                except Exception:
                    continue
            if best_idx >= 0:
                flat = text.replace('\n', '')
                mesh_idx = best_idx
                mesh_letter = flat[best_idx] if best_idx < len(flat) else '?'

        # Strategy 2: fixed-width grid fallback
        local_pt = self._world_to_local(world_pt)
        col = -1
        row = -1
        if local_pt is not None:
            col = int(local_pt.y / self.CHAR_WIDTH)
            row = int(-local_pt.z / self.CHAR_HEIGHT)

        # Pick best result
        if mesh_idx is not None:
            letter = mesh_letter
            idx = mesh_idx
            method = 'CharacterMeshes'
        else:
            idx = col
            lines = text.split('\n')
            if 0 <= row < len(lines) and 0 <= col < len(lines[row]):
                letter = lines[row][col]
            else:
                letter = '?'
            method = 'fixed-width'

        local_str = ''
        if local_pt is not None:
            local_str = (f'local=({local_pt.x:.1f}, {local_pt.y:.1f}, '
                         f'{local_pt.z:.1f})  ')

        ue.log(
            f'PyActorText3D click: letter="{letter}"  index={idx}  '
            f'method={method}  '
            f'actor={self.uobject.get_name()}  '
            f'{local_str}'
            f'world=({world_pt.x:.1f}, {world_pt.y:.1f}, {world_pt.z:.1f})'
        )
        self._on_char_click(col, row, letter=letter, char_index=idx)

    def _world_to_local(self, world_pt):
        actor_transform = self.uobject.get_actor_transform()
        try:
            from unreal_engine.classes import KismetMathLibrary
            return KismetMathLibrary.InverseTransformLocation(actor_transform, world_pt)
        except Exception:
            pass
        # Manual fallback
        try:
            import math
            loc = self.uobject.get_actor_location()
            rot = self.uobject.get_actor_rotation()
            delta = FVector(world_pt.x - loc.x,
                            world_pt.y - loc.y,
                            world_pt.z - loc.z)
            yaw = math.radians(-rot.yaw)
            pitch = math.radians(-rot.pitch)
            roll = math.radians(-rot.roll)
            cy, sy = math.cos(yaw), math.sin(yaw)
            x1 =  cy * delta.x + sy * delta.y
            y1 = -sy * delta.x + cy * delta.y
            z1 = delta.z
            cp, sp = math.cos(pitch), math.sin(pitch)
            x2 =  cp * x1 - sp * z1
            y2 = y1
            z2 =  sp * x1 + cp * z1
            cr, sr = math.cos(roll), math.sin(roll)
            return FVector(x2, cr * y2 + sr * z2, -sr * y2 + cr * z2)
        except Exception as e:
            ue.log_warning(f'PyActorText3D._world_to_local fallback failed: {e}')
            return None

    @classmethod
    def _world_to_local_cls(cls, actor, world_pt):
        """Class-level world→local for the global click path (no self)."""
        try:
            actor_transform = actor.get_actor_transform()
        except Exception:
            return None
        try:
            from unreal_engine.classes import KismetMathLibrary
            return KismetMathLibrary.InverseTransformLocation(actor_transform, world_pt)
        except Exception:
            pass
        try:
            import math
            loc = actor.get_actor_location()
            rot = actor.get_actor_rotation()
            delta = FVector(world_pt.x - loc.x,
                            world_pt.y - loc.y,
                            world_pt.z - loc.z)
            yaw = math.radians(-rot.yaw)
            pitch = math.radians(-rot.pitch)
            roll = math.radians(-rot.roll)
            cy, sy = math.cos(yaw), math.sin(yaw)
            x1 =  cy * delta.x + sy * delta.y
            y1 = -sy * delta.x + cy * delta.y
            z1 = delta.z
            cp, sp = math.cos(pitch), math.sin(pitch)
            x2 =  cp * x1 - sp * z1
            y2 = y1
            z2 =  sp * x1 + cp * z1
            cr, sr = math.cos(roll), math.sin(roll)
            return FVector(x2, cr * y2 + sr * z2, -sr * y2 + cr * z2)
        except Exception:
            return None

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

    # Focus state — proxies the global registry on PyActorGlobalClick so
    # callers can read/write `actor.focused` per instance while a single
    # source of truth remains class-level (only one Text3D can be focused
    # at a time across the scene).

    @property
    def focused(self):
        return PyActorGlobalClick._focused_actor is self.uobject

    @focused.setter
    def focused(self, value):
        if value:
            PyActorText3D._set_focused_actor(self.uobject)
        elif PyActorGlobalClick._focused_actor is self.uobject:
            PyActorText3D._set_focused_actor(None)

    # Override point

    def _on_char_click(self, col, row, letter=None, char_index=None):
        """
        Called after every click with the character position.

        Parameters
        ----------
        col        : int   — column (0-indexed from left) via fixed-width grid
        row        : int   — row (0-indexed from top) via fixed-width grid
        letter     : str   — the resolved character ('A', 'z', ' ', etc.)
        char_index : int   — flat index into the text string (accounts for
                             proportional glyph widths when CharacterMeshes
                             is available)

        Override in a subclass or monkey-patch after spawn.
        """
        if char_index is not None and char_index >= 0:
            PyActorText3D.show_cursor_at(self.uobject, char_index + 1)

    # ============================================================
    # Typing system (class-level) — absorbed from test_text3d_click
    # ============================================================

    @classmethod
    def register_actor(cls, actor, renderer=None):
        """Register *actor* as a typing target.  Idempotent.

        ``renderer`` is an optional table renderer that will get
        recompute_layout() called on it when *actor* loses focus (for
        auto-sizing tables that should refit after a text edit)."""
        if actor is None:
            return
        cls._watched.add(actor)
        if renderer is not None:
            cls._watched_renderer[actor] = renderer

    @classmethod
    def _ensure_global_typing(cls):
        """One-shot init of ctypes + PyActorGlobalClick + global tick.
        Safe to call repeatedly — short-circuits after the first time."""
        if cls._typing_initialized:
            return
        cls._typing_initialized = True

        # ctypes / Win32 setup (keyboard, clipboard).  Mouse uses VK_LBUTTON
        # via the same GetAsyncKeyState path so we don't need an
        # input_manager dependency.
        try:
            import ctypes
            user32 = ctypes.WinDLL('user32', use_last_error=True)
            kernel32 = ctypes.WinDLL('kernel32', use_last_error=True)
            user32.GetAsyncKeyState.argtypes = [ctypes.c_int]
            user32.GetAsyncKeyState.restype = ctypes.c_short
            user32.GetKeyState.argtypes = [ctypes.c_int]
            user32.GetKeyState.restype = ctypes.c_short
            user32.MapVirtualKeyW.argtypes = [ctypes.c_uint, ctypes.c_uint]
            user32.MapVirtualKeyW.restype = ctypes.c_uint
            user32.ToUnicode.argtypes = [
                ctypes.c_uint, ctypes.c_uint,
                ctypes.POINTER(ctypes.c_ubyte), ctypes.c_wchar_p,
                ctypes.c_int, ctypes.c_uint,
            ]
            user32.ToUnicode.restype = ctypes.c_int
            user32.OpenClipboard.argtypes = [ctypes.c_void_p]
            user32.OpenClipboard.restype = ctypes.c_int
            user32.CloseClipboard.argtypes = []
            user32.CloseClipboard.restype = ctypes.c_int
            user32.EmptyClipboard.argtypes = []
            user32.EmptyClipboard.restype = ctypes.c_int
            user32.GetClipboardData.argtypes = [ctypes.c_uint]
            user32.GetClipboardData.restype = ctypes.c_void_p
            user32.SetClipboardData.argtypes = [ctypes.c_uint, ctypes.c_void_p]
            user32.SetClipboardData.restype = ctypes.c_void_p
            user32.IsClipboardFormatAvailable.argtypes = [ctypes.c_uint]
            user32.IsClipboardFormatAvailable.restype = ctypes.c_int
            kernel32.GlobalAlloc.argtypes = [ctypes.c_uint, ctypes.c_size_t]
            kernel32.GlobalAlloc.restype = ctypes.c_void_p
            kernel32.GlobalLock.argtypes = [ctypes.c_void_p]
            kernel32.GlobalLock.restype = ctypes.c_void_p
            kernel32.GlobalUnlock.argtypes = [ctypes.c_void_p]
            kernel32.GlobalUnlock.restype = ctypes.c_int
            kernel32.GlobalSize.argtypes = [ctypes.c_void_p]
            kernel32.GlobalSize.restype = ctypes.c_size_t
            cls._ctypes = ctypes
            cls._user32 = user32
            cls._kernel32 = kernel32
            cls._WIN32_TYPING_OK = True
        except Exception as e:
            cls._WIN32_TYPING_OK = False
            ue.log_warning(f'PyActorText3D: ctypes typing unavailable ({e})')

        # Spawn PyActorGlobalClick + attach the global tick.  Hook the
        # renderer-refit-on-unfocus behaviour via add_unfocus_handler so
        # focus state stays single-sourced on PyActorGlobalClick.
        try:
            from ue_spawn import spawn_pyactor
            cls._global_actor = spawn_pyactor(
                'pyactor_global_click', 'PyActorGlobalClick',
                location=FVector(0, 0, 0),
                name='PyActorGlobalClick')
            proxy = cls._global_actor.get_py_proxy()
            proxy.set_tick_fn(cls._global_tick)
            PyActorGlobalClick.add_unfocus_handler(cls._on_actor_unfocus)
            ue.log('PyActorText3D: typing system online '
                   '(PyActorGlobalClick + Win32 keyboard/mouse)')
        except Exception as e:
            ue.log_warning(
                f'PyActorText3D: typing-system bootstrap failed: {e}')

    @classmethod
    def _on_actor_unfocus(cls, prev_actor):
        """Refit the previous actor's table renderer (if any) so an
        auto-sizing table snaps back after a text edit.  Registered with
        PyActorGlobalClick.add_unfocus_handler from _ensure_global_typing."""
        renderer = cls._watched_renderer.get(prev_actor)
        if renderer is None:
            return
        if not getattr(renderer, 'auto_size', True):
            return
        try:
            renderer.recompute_layout()
        except Exception as e:
            ue.log_warning(f'PyActorText3D: recompute_layout failed: {e}')

    # ---- Focus + selection helpers ----

    @classmethod
    def _set_focused_actor(cls, actor):
        """Single mutation point for focus.  Delegates to PyActorGlobalClick
        which fires unfocus handlers; this class registered _on_actor_unfocus
        to handle table refit."""
        PyActorGlobalClick.set_focused_actor(actor)

    @classmethod
    def _get_focused(cls):
        return PyActorGlobalClick.get_focused_actor()

    @classmethod
    def _sel_range(cls):
        """Return (start, end) of the selection sorted.  start==end means none."""
        a = cls._anchor
        c = cls._string_idx
        return (a, c) if a <= c else (c, a)

    @classmethod
    def _has_sel(cls):
        return cls._anchor != cls._string_idx

    @classmethod
    def _set_caret(cls, idx, extend_selection=False):
        cls._string_idx = idx
        if not extend_selection:
            cls._anchor = idx

    @staticmethod
    def _string_idx_to_glyph(text, sidx):
        """Count visible (non-space, non-newline) chars in text[:sidx]."""
        sidx = max(0, min(sidx, len(text)))
        return sum(1 for c in text[:sidx] if c not in ' \n')

    @staticmethod
    def _glyph_to_string_idx(text, tg):
        """Return the string index of the tg-th visible char (or len(text))."""
        count = 0
        for i, c in enumerate(text):
            if count == tg:
                return i
            if c not in ' \n':
                count += 1
        return len(text)

    # ---- Selection-highlight pool ----

    @classmethod
    def _spawn_highlight_box(cls):
        """Spawn one translucent cube used as a selection-highlight bar.
        Caret blink is owned by the PyActorCursor singleton — these boxes
        are only for selection ranges (no blink, multiple coexist)."""
        try:
            from unreal_engine.classes import StaticMeshActor, StaticMesh, Material
            from unreal_engine.enums import EComponentMobility

            world = get_world()
            actor = world.actor_spawn(StaticMeshActor)
            smc = actor.StaticMeshComponent
            cube = ue.load_object(StaticMesh, '/Engine/BasicShapes/Cube.Cube')
            smc.SetStaticMesh(cube)
            smc.SetMobility(EComponentMobility.Movable)

            mid = None
            for mat_path in ('/Game/Materials/M_Color_Translucent.M_Color_Translucent',
                             '/Game/Materials/M_TextureUnlit.M_TextureUnlit',
                             '/Game/Materials/M_Icon.M_Icon'):
                try:
                    mat = ue.load_object(Material, mat_path)
                    mid = smc.create_material_instance_dynamic(mat)
                    break
                except Exception:
                    continue
            if mid is not None:
                smc.set_material(0, mid)

            actor.set_actor_scale(FVector(0.01, 0.025, 0.5))
            try:
                actor.SetActorEnableCollision(False)
            except Exception:
                pass
            actor.SetActorHiddenInGame(True)
            return actor
        except Exception as e:
            ue.log_warning(f'PyActorText3D: highlight spawn failed: {e}')
            return None

    @classmethod
    def _ensure_highlight(cls, i):
        """Lazily grow the highlight pool to at least i+1 actors."""
        while len(cls._highlight_actors) <= i:
            a = cls._spawn_highlight_box()
            if a is None:
                return None
            try:
                a.SetActorLabel(f'TextSelHighlight_{len(cls._highlight_actors)}')
            except Exception:
                pass
            cls._highlight_actors.append(a)
        return cls._highlight_actors[i]

    @classmethod
    def _hide_highlights(cls):
        for a in cls._highlight_actors:
            try:
                a.SetActorHiddenInGame(True)
            except Exception:
                pass

    @classmethod
    def _unfocus(cls):
        cls._set_focused_actor(None)
        cls._string_idx = 0
        cls._anchor = 0
        cls.hide_cursor()
        cls._hide_highlights()

    @classmethod
    def _render_highlight_segment(cls, pool_idx, actor, text, seg_start, seg_end):
        """Render one highlight box for string range [seg_start, seg_end).
        Assumes the segment is on a single line."""
        box = cls._ensure_highlight(pool_idx)
        if box is None:
            return
        sg = cls._string_idx_to_glyph(text, seg_start)
        eg = cls._string_idx_to_glyph(text, seg_end)
        left = cls.compute_placement(actor, sg)
        right = cls.compute_placement(actor, eg)
        if left is None or right is None:
            try:
                box.SetActorHiddenInGame(True)
            except Exception:
                pass
            return
        lwp, lscale, lrot = left
        rwp, _, _ = right
        dy = rwp.y - lwp.y
        dx = rwp.x - lwp.x
        span_uu = (dx * dx + dy * dy) ** 0.5
        if span_uu < 1.0:
            try:
                box.SetActorHiddenInGame(True)
            except Exception:
                pass
            return
        mid_wp = FVector(
            (lwp.x + rwp.x) * 0.5,
            (lwp.y + rwp.y) * 0.5,
            (lwp.z + rwp.z) * 0.5,
        )
        try:
            box.set_actor_scale(FVector(0.01, span_uu / 100.0, lscale.z))
        except Exception:
            pass
        box.set_actor_location(mid_wp)
        box.set_actor_rotation(lrot)
        box.SetActorHiddenInGame(False)

    @classmethod
    def _update_highlight(cls):
        """Rebuild highlight boxes from current selection."""
        cls._hide_highlights()
        actor = cls._get_focused()
        if actor is None or not cls._has_sel():
            return
        try:
            t3d = actor.get_actor_component(cls.TEXT_COMPONENT_NAME)
        except Exception:
            return
        if t3d is None:
            return
        try:
            text = str(t3d.Text or '')
        except Exception:
            return
        start, end = cls._sel_range()
        pool_idx = 0
        s = start
        while s < end:
            nl = text.find('\n', s, end)
            seg_end = end if nl == -1 else nl
            if seg_end > s:
                cls._render_highlight_segment(pool_idx, actor, text, s, seg_end)
                pool_idx += 1
            s = seg_end + 1 if nl != -1 else end

    @classmethod
    def _position_cursor(cls, hit_actor, hit):
        """Derive target_glyph from a click hit, move cursor, set focus."""
        if hit_actor is None:
            return

        t3d = None
        try:
            t3d = hit_actor.get_actor_component(cls.TEXT_COMPONENT_NAME)
        except Exception:
            pass

        text = ''
        if t3d is not None:
            try:
                text = str(t3d.Text or '')
            except Exception:
                pass

        kernings = None
        meshes = None
        if t3d is not None:
            try:
                kernings = t3d.CharacterKernings
            except Exception:
                pass
            try:
                meshes = t3d.CharacterMeshes
            except Exception:
                pass

        # No kernings — drop the caret directly at the click point via
        # the singleton cursor (skipping placement math entirely).
        if not kernings or len(kernings) == 0:
            cursor_proxy = cls._get_or_spawn_cursor(hit_actor)
            if cursor_proxy is not None:
                try:
                    cursor_proxy.move_to(
                        hit.impact_point,
                        FVector(0.01, 0.04, 0.5),
                        hit_actor.get_actor_rotation())
                except Exception:
                    pass
            cls._set_focused_actor(hit_actor)
            cls._string_idx = len(text)
            cls._anchor = len(text)
            cls._hide_highlights()
            return

        local_pt = cls._world_to_local_cls(hit_actor, hit.impact_point)
        clicked_glyph = 0
        side = 'right'

        if local_pt is not None:
            glyph_edges = []
            for i in range(len(kernings)):
                if kernings[i] is not None:
                    try:
                        rel = kernings[i].get_relative_location()
                        glyph_edges.append((rel.y, i))
                    except Exception:
                        pass
            glyph_edges.sort(key=lambda e: e[0])
            if glyph_edges:
                clicked_glyph = glyph_edges[0][1]
                for edge_y, gi in glyph_edges:
                    if local_pt.y >= edge_y:
                        clicked_glyph = gi
                    else:
                        break

            glyph_w_local = 50.0
            if (meshes is not None
                    and 0 <= clicked_glyph < len(meshes)
                    and meshes[clicked_glyph] is not None):
                try:
                    _, e = meshes[clicked_glyph].GetComponentBounds()
                    glyph_w_local = e.y * 2.0
                except Exception:
                    pass

            if (0 <= clicked_glyph < len(kernings)
                    and kernings[clicked_glyph] is not None):
                try:
                    r = kernings[clicked_glyph].get_relative_location()
                    mid_y = r.y + glyph_w_local / 2.0
                    side = 'left' if local_pt.y < mid_y else 'right'
                except Exception:
                    pass

        target_glyph = clicked_glyph if side == 'left' else clicked_glyph + 1

        if not cls.show_cursor_at(hit_actor, target_glyph):
            return

        cls._set_focused_actor(hit_actor)
        new_idx = cls._glyph_to_string_idx(text, target_glyph)
        cls._string_idx = new_idx
        cls._anchor = new_idx
        cls._hide_highlights()
        # If the previous focus was an auto-sizing table cell, that table
        # just refit and may have shifted hit_actor.  Re-show the cursor.
        cls.show_cursor_at(hit_actor, target_glyph)

    # ---- Text mutation ----

    @classmethod
    def _handle_typed_char(cls, ch):
        """Insert/delete at cursor.  ch='\\b'=backspace, '\\n'=newline, else literal."""
        actor = cls._get_focused()
        if actor is None:
            return
        try:
            t3d = actor.get_actor_component(cls.TEXT_COMPONENT_NAME)
        except Exception:
            return
        if t3d is None:
            return

        try:
            text = str(t3d.Text or '')
        except Exception:
            text = ''

        if cls._has_sel():
            start, end = cls._sel_range()
            text = text[:start] + text[end:]
            idx = start
            cls._string_idx = idx
            cls._anchor = idx
            if ch == '\b':
                # Selection-backspace just deletes the selection.
                try:
                    t3d.Text = text
                except Exception as e:
                    ue.log_warning(f'PyActorText3D: failed to set text: {e}')
                    return
                cls.show_cursor_at(actor, cls._string_idx_to_glyph(text, idx))
                cls._update_highlight()
                return

        idx = max(0, min(cls._string_idx, len(text)))

        if ch == '\b':
            if idx == 0:
                return
            text = text[:idx - 1] + text[idx:]
            idx -= 1
        else:
            text = text[:idx] + ch + text[idx:]
            idx += 1

        try:
            t3d.Text = text
        except Exception as e:
            ue.log_warning(f'PyActorText3D: failed to set text: {e}')
            return

        cls._string_idx = idx
        cls._anchor = idx

        target_glyph = cls._string_idx_to_glyph(text, idx)
        cls.show_cursor_at(actor, target_glyph)
        cls._update_highlight()

    # ---- Modifier-key probes ----

    @classmethod
    def _build_kb_state(cls):
        """256-byte keyboard state for ToUnicode.  High bit=down, low bit=toggle."""
        buf = (cls._ctypes.c_ubyte * 256)()
        for vk in range(256):
            if cls._user32.GetAsyncKeyState(vk) & 0x8000:
                buf[vk] = 0x80
        for tvk in (0x14, 0x90, 0x91):   # Caps / Num / Scroll lock
            if cls._user32.GetKeyState(tvk) & 0x0001:
                buf[tvk] |= 0x01
        return buf

    @classmethod
    def _ctrl_down(cls):
        return cls._WIN32_TYPING_OK and bool(cls._user32.GetAsyncKeyState(0x11) & 0x8000)

    @classmethod
    def _shift_held(cls):
        return cls._WIN32_TYPING_OK and bool(cls._user32.GetAsyncKeyState(0x10) & 0x8000)

    @classmethod
    def _alt_down(cls):
        return cls._WIN32_TYPING_OK and bool(cls._user32.GetAsyncKeyState(0x12) & 0x8000)

    @classmethod
    def _win_down(cls):
        if not cls._WIN32_TYPING_OK:
            return False
        return (bool(cls._user32.GetAsyncKeyState(0x5B) & 0x8000)
                or bool(cls._user32.GetAsyncKeyState(0x5C) & 0x8000))

    # ---- Caret navigation ----

    @staticmethod
    def _is_word_char(c):
        return c.isalnum() or c == '_'

    @classmethod
    def _word_boundary(cls, text, idx, direction):
        """Move idx to the next word boundary in `direction` (+1 or -1)."""
        n = len(text)
        idx = max(0, min(idx, n))
        if direction > 0:
            while idx < n and not cls._is_word_char(text[idx]):
                idx += 1
            while idx < n and cls._is_word_char(text[idx]):
                idx += 1
        else:
            idx = max(0, idx - 1)
            while idx > 0 and not cls._is_word_char(text[idx]):
                idx -= 1
            while idx > 0 and cls._is_word_char(text[idx - 1]):
                idx -= 1
        return idx

    @staticmethod
    def _line_edge(text, idx, direction):
        """Move idx to start (-1) or end (+1) of its line."""
        n = len(text)
        idx = max(0, min(idx, n))
        if direction < 0:
            nl = text.rfind('\n', 0, idx)
            return 0 if nl == -1 else nl + 1
        nl = text.find('\n', idx)
        return n if nl == -1 else nl

    @classmethod
    def _line_delta(cls, text, idx, direction):
        """Move idx up (-1) or down (+1) one line, preserving column."""
        n = len(text)
        idx = max(0, min(idx, n))
        line_start = cls._line_edge(text, idx, -1)
        col = idx - line_start
        if direction < 0:
            if line_start == 0:
                return 0
            prev_end = line_start - 1
            prev_start = cls._line_edge(text, prev_end, -1)
            return min(prev_start + col, prev_end)
        line_end = cls._line_edge(text, idx, +1)
        if line_end == n:
            return n
        next_start = line_end + 1
        next_end = cls._line_edge(text, next_start, +1)
        return min(next_start + col, next_end)

    @classmethod
    def _move_caret_to(cls, new_idx, extend):
        """Set caret, optionally extending selection; refresh cursor + highlight."""
        actor = cls._get_focused()
        if actor is None:
            return
        t3d = None
        try:
            t3d = actor.get_actor_component(cls.TEXT_COMPONENT_NAME)
        except Exception:
            pass
        text = ''
        if t3d is not None:
            try:
                text = str(t3d.Text or '')
            except Exception:
                pass
        new_idx = max(0, min(new_idx, len(text)))
        cls._set_caret(new_idx, extend_selection=extend)
        cls.show_cursor_at(actor, cls._string_idx_to_glyph(text, new_idx))
        cls._update_highlight()

    # ---- Clipboard ----

    @classmethod
    def _clipboard_get_text(cls):
        if not cls._WIN32_TYPING_OK:
            return None
        try:
            if not cls._user32.OpenClipboard(0):
                return None
            try:
                if not cls._user32.IsClipboardFormatAvailable(cls._CF_UNICODETEXT):
                    return None
                h = cls._user32.GetClipboardData(cls._CF_UNICODETEXT)
                if not h:
                    return None
                p = cls._kernel32.GlobalLock(h)
                if not p:
                    return None
                try:
                    return cls._ctypes.c_wchar_p(p).value
                finally:
                    cls._kernel32.GlobalUnlock(h)
            finally:
                cls._user32.CloseClipboard()
        except Exception as e:
            ue.log_warning(f'PyActorText3D: clipboard read failed: {e}')
            return None

    @classmethod
    def _clipboard_set_text(cls, text):
        if not cls._WIN32_TYPING_OK or text is None:
            return False
        try:
            if not cls._user32.OpenClipboard(0):
                return False
            try:
                cls._user32.EmptyClipboard()
                GMEM_MOVEABLE = 0x0002
                data = text.encode('utf-16-le') + b'\x00\x00'
                size = len(data)
                h = cls._kernel32.GlobalAlloc(GMEM_MOVEABLE, size)
                if not h:
                    return False
                p = cls._kernel32.GlobalLock(h)
                if not p:
                    return False
                cls._ctypes.memmove(p, data, size)
                cls._kernel32.GlobalUnlock(h)
                # After SetClipboardData, the system owns the handle.
                return bool(cls._user32.SetClipboardData(cls._CF_UNICODETEXT, h))
            finally:
                cls._user32.CloseClipboard()
        except Exception as e:
            ue.log_warning(f'PyActorText3D: clipboard write failed: {e}')
            return False

    @classmethod
    def _clipboard_get_image(cls):
        try:
            from PIL import ImageGrab, Image as PILImage
            img = ImageGrab.grabclipboard()
            if isinstance(img, PILImage.Image):
                return img
            return None
        except Exception as e:
            ue.log_warning(f'PyActorText3D: ImageGrab failed: {e}')
            return None

    # ---- Edit actions ----

    @classmethod
    def _delete_selection(cls):
        """Delete selected text in focused actor.  Returns True if anything deleted."""
        actor = cls._get_focused()
        if actor is None or not cls._has_sel():
            return False
        try:
            t3d = actor.get_actor_component(cls.TEXT_COMPONENT_NAME)
        except Exception:
            return False
        if t3d is None:
            return False
        try:
            text = str(t3d.Text or '')
        except Exception:
            return False
        start, end = cls._sel_range()
        new_text = text[:start] + text[end:]
        try:
            t3d.Text = new_text
        except Exception as e:
            ue.log_warning(f'PyActorText3D: delete_selection failed: {e}')
            return False
        cls._string_idx = start
        cls._anchor = start
        cls.show_cursor_at(actor, cls._string_idx_to_glyph(new_text, start))
        cls._update_highlight()
        return True

    @classmethod
    def _select_all(cls):
        actor = cls._get_focused()
        if actor is None:
            return
        try:
            t3d = actor.get_actor_component(cls.TEXT_COMPONENT_NAME)
        except Exception:
            return
        if t3d is None:
            return
        try:
            text = str(t3d.Text or '')
        except Exception:
            return
        cls._anchor = 0
        cls._string_idx = len(text)
        cls.show_cursor_at(actor, cls._string_idx_to_glyph(text, len(text)))
        cls._update_highlight()

    @classmethod
    def _copy(cls):
        if not cls._has_sel():
            return
        actor = cls._get_focused()
        if actor is None:
            return
        try:
            t3d = actor.get_actor_component(cls.TEXT_COMPONENT_NAME)
        except Exception:
            return
        if t3d is None:
            return
        try:
            text = str(t3d.Text or '')
        except Exception:
            return
        s, e = cls._sel_range()
        cls._clipboard_set_text(text[s:e])

    @classmethod
    def _cut(cls):
        if not cls._has_sel():
            return
        cls._copy()
        cls._delete_selection()

    @classmethod
    def _paste(cls):
        if cls._get_focused() is None:
            return
        # Image first — if clipboard has a bitmap, inline-paste it.
        img = cls._clipboard_get_image()
        if img is not None:
            cls._paste_image(img)
            return
        # Otherwise paste text at caret, replacing any selection.
        clip = cls._clipboard_get_text()
        if not clip:
            return
        if cls._has_sel():
            cls._delete_selection()
        for c in clip:
            if c == '\r':
                continue   # CRLF → LF
            cls._handle_typed_char(c)

    @classmethod
    def _delete_forward(cls):
        actor = cls._get_focused()
        if actor is None:
            return
        if cls._has_sel():
            cls._delete_selection()
            return
        try:
            t3d = actor.get_actor_component(cls.TEXT_COMPONENT_NAME)
        except Exception:
            return
        if t3d is None:
            return
        try:
            text = str(t3d.Text or '')
        except Exception:
            return
        idx = cls._string_idx
        if idx >= len(text):
            return
        new_text = text[:idx] + text[idx + 1:]
        try:
            t3d.Text = new_text
        except Exception:
            return
        cls.show_cursor_at(actor, cls._string_idx_to_glyph(new_text, idx))
        cls._update_highlight()

    @classmethod
    def _cycle_focus(cls, direction=1):
        """Ctrl+Tab — move focus to the next (or previous) registered actor."""
        if not cls._watched:
            return
        ordered = list(cls._watched)
        current = cls._get_focused()
        if current in ordered:
            i = (ordered.index(current) + direction) % len(ordered)
        else:
            i = 0
        new_actor = ordered[i]
        new_text = ''
        try:
            t3d = new_actor.get_actor_component(cls.TEXT_COMPONENT_NAME)
            if t3d is not None:
                new_text = str(t3d.Text or '')
        except Exception:
            pass
        cls._set_focused_actor(new_actor)
        cls._string_idx = len(new_text)
        cls._anchor = len(new_text)
        cls.show_cursor_at(new_actor, cls._string_idx_to_glyph(new_text, len(new_text)))
        cls._hide_highlights()

    # ---- Inline image paste ----

    @classmethod
    def _paste_image(cls, pil_img):
        """Inline-paste a PIL image into the focused Text3D at the caret.
        The image is scaled so its height matches the text's line height,
        then space characters are inserted to reserve horizontal room and
        the image actor is placed over the reserved spaces."""
        actor = cls._get_focused()
        if actor is None:
            return
        try:
            t3d = actor.get_actor_component(cls.TEXT_COMPONENT_NAME)
        except Exception:
            return
        if t3d is None:
            return
        try:
            text = str(t3d.Text or '')
        except Exception:
            text = ''

        text_h = 50.0
        try:
            o, e = t3d.GetComponentBounds()
            text_h = max(text_h, e.z * 2.0 * 0.8)
        except Exception:
            pass
        glyph_w = 50.0
        try:
            meshes = t3d.CharacterMeshes
            if meshes is not None:
                for m in meshes:
                    if m is None:
                        continue
                    try:
                        _, e = m.GetComponentBounds()
                        glyph_w = e.y * 2.0
                        break
                    except Exception:
                        continue
        except Exception:
            pass

        iw, ih = float(pil_img.width), float(pil_img.height)
        if ih <= 0:
            return
        img_h_uu = text_h
        img_w_uu = iw / ih * img_h_uu
        n_spaces = max(1, int(round(img_w_uu / glyph_w)))

        if cls._has_sel():
            cls._delete_selection()
            try:
                text = str(t3d.Text or '')
            except Exception:
                text = ''

        idx = cls._string_idx
        placeholder = ' ' * n_spaces
        new_text = text[:idx] + placeholder + text[idx:]
        try:
            t3d.Text = new_text
        except Exception as e:
            ue.log_warning(f'PyActorText3D: paste_image set text failed: {e}')
            return

        image_actor = None
        try:
            import tempfile, os, time
            from ue_spawn import spawn_image
            tmpdir = os.path.join(tempfile.gettempdir(), 'ue_clipboard_images')
            try:
                os.makedirs(tmpdir, exist_ok=True)
            except Exception:
                pass
            tmp_path = os.path.join(tmpdir, f'clip_{int(time.time()*1000)}.png')
            pil_img.convert('RGBA').save(tmp_path, 'PNG')
            img_scale = FVector(img_w_uu / 100.0, 0.05, img_h_uu / 100.0)
            image_actor = spawn_image(tmp_path, scale=img_scale)
        except Exception as e:
            ue.log_warning(f'PyActorText3D: spawn_image failed: {e}')

        if image_actor is not None:
            try:
                mid_idx = idx + n_spaces // 2
                mid_glyph = cls._string_idx_to_glyph(new_text, mid_idx)
                placement = cls.compute_placement(actor, mid_glyph)
                if placement is not None:
                    world_pt, _, rot = placement
                    image_actor.set_actor_location(world_pt)
                    image_actor.set_actor_rotation(rot)
                    image_actor.attach_to_actor(actor)
            except Exception as e:
                ue.log_warning(f'PyActorText3D: image position failed: {e}')
            cls._inline_images.append(
                (actor, image_actor, idx, n_spaces, img_w_uu, img_h_uu))

        new_idx = idx + n_spaces
        cls._string_idx = new_idx
        cls._anchor = new_idx
        cls.show_cursor_at(actor, cls._string_idx_to_glyph(new_text, new_idx))
        cls._update_highlight()

    # ---- Keyboard rising-edge dispatch ----

    @classmethod
    def _on_vk_rise(cls, vk):
        """Rising-edge handler.  Dispatches shortcuts, then falls through to
        ToUnicode for ordinary character entry (notepad's WM_CHAR semantics)."""
        if cls._get_focused() is None:
            return

        ctrl = cls._ctrl_down()
        shift = cls._shift_held()
        alt = cls._alt_down()
        win = cls._win_down()

        # Notepad parity: Alt+key (Alt+Tab/Enter/F4/Backspace) and Win+key
        # are never text input.  AltGr on European layouts reports
        # Alt+Ctrl together AND produces characters through ToUnicode, so
        # the `not ctrl` clause keeps that path open.
        if (alt and not ctrl) or win:
            return

        if ctrl:
            if vk == 0x41:    # A
                cls._select_all(); return
            if vk == 0x43:    # C
                cls._copy(); return
            if vk == 0x58:    # X
                cls._cut(); return
            if vk == 0x56:    # V
                cls._paste(); return
            if vk == 0x09:    # Tab
                cls._cycle_focus(-1 if shift else +1); return
            actor = cls._get_focused()
            t3d = actor.get_actor_component(cls.TEXT_COMPONENT_NAME) if actor else None
            text = str(t3d.Text or '') if t3d else ''
            idx = cls._string_idx
            if vk == 0x25:    # Ctrl+Left  — prev word
                cls._move_caret_to(cls._word_boundary(text, idx, -1), shift); return
            if vk == 0x27:    # Ctrl+Right — next word
                cls._move_caret_to(cls._word_boundary(text, idx, +1), shift); return
            if vk == 0x24:    # Ctrl+Home  — doc start
                cls._move_caret_to(0, shift); return
            if vk == 0x23:    # Ctrl+End   — doc end
                cls._move_caret_to(len(text), shift); return

        if vk in (0x25, 0x27, 0x26, 0x28, 0x24, 0x23):
            actor = cls._get_focused()
            t3d = actor.get_actor_component(cls.TEXT_COMPONENT_NAME) if actor else None
            text = str(t3d.Text or '') if t3d else ''
            idx = cls._string_idx
            if vk == 0x25:    # Left
                if cls._has_sel() and not shift:
                    cls._move_caret_to(cls._sel_range()[0], False); return
                cls._move_caret_to(max(0, idx - 1), shift); return
            if vk == 0x27:    # Right
                if cls._has_sel() and not shift:
                    cls._move_caret_to(cls._sel_range()[1], False); return
                cls._move_caret_to(min(len(text), idx + 1), shift); return
            if vk == 0x26:    # Up
                cls._move_caret_to(cls._line_delta(text, idx, -1), shift); return
            if vk == 0x28:    # Down
                cls._move_caret_to(cls._line_delta(text, idx, +1), shift); return
            if vk == 0x24:    # Home
                cls._move_caret_to(cls._line_edge(text, idx, -1), shift); return
            if vk == 0x23:    # End
                cls._move_caret_to(cls._line_edge(text, idx, +1), shift); return

        if vk == 0x08:        # VK_BACK
            cls._handle_typed_char('\b'); return
        if vk == 0x2E:        # VK_DELETE
            cls._delete_forward(); return
        if vk == 0x0D:        # VK_RETURN
            cls._handle_typed_char('\n'); return
        if vk == 0x09:        # VK_TAB
            cls._handle_typed_char('\t'); return
        if vk == 0x1B:        # VK_ESCAPE
            cls._unfocus(); return

        # Suppress Ctrl+letter producing control chars (e.g. Ctrl+B → 0x02).
        if ctrl:
            return
        try:
            kb_state = cls._build_kb_state()
            scan_code = cls._user32.MapVirtualKeyW(vk, 0)
            outbuf = cls._ctypes.create_unicode_buffer(8)
            result = cls._user32.ToUnicode(
                vk, scan_code, kb_state, outbuf, len(outbuf), 0)
        except Exception:
            return
        if result > 0:
            for c in outbuf.value[:result]:
                if c and ord(c) >= 0x20:
                    cls._handle_typed_char(c)

    @classmethod
    def _poll_keyboard(cls):
        """Call each tick.  Fires character events on rising edges while focused."""
        if not cls._WIN32_TYPING_OK:
            return
        curr = bytearray(256)
        for vk in range(256):
            if cls._user32.GetAsyncKeyState(vk) & 0x8000:
                curr[vk] = 1
        if cls._get_focused() is not None:
            for vk in range(256):
                if curr[vk] and not cls._prev_vk_down[vk]:
                    cls._on_vk_rise(vk)
        for i in range(256):
            cls._prev_vk_down[i] = curr[i]

    # ---- Mouse rising-edge → focus + cursor placement ----

    @classmethod
    def _poll_mouse_click(cls):
        """LMB rising-edge: hit-test against _watched and _position_cursor on
        the matched actor.  Off-click unfocuses."""
        if not cls._WIN32_TYPING_OK:
            return
        # VK_LBUTTON = 0x01 — system-wide mouse state, doesn't need foreground.
        down = bool(cls._user32.GetAsyncKeyState(0x01) & 0x8000)
        prev = cls._prev_lbutton_down
        cls._prev_lbutton_down = down
        if not (down and not prev):
            return

        # Need a UObject for get_hit_result_under_cursor; use the global
        # actor's uobject (ticking already guarantees it).
        trace_obj = None
        try:
            if cls._global_actor is not None:
                trace_obj = cls._global_actor
        except Exception:
            pass
        pc = None
        try:
            pc = ue.get_player_controller(0)
        except Exception:
            pass

        hit = None
        for channel in (ECollisionChannel.ECC_Visibility,
                        ECollisionChannel.ECC_WorldDynamic):
            for src in (trace_obj, pc):
                if src is None:
                    continue
                try:
                    h = src.get_hit_result_under_cursor(channel)
                    if h is not None:
                        hit = h
                        break
                except Exception:
                    continue
            if hit is not None:
                break

        hit_actor = hit.actor if hit is not None else None
        matched = None
        if hit_actor is not None:
            for w in cls._watched:
                try:
                    if w == hit_actor:
                        matched = w
                        break
                except Exception:
                    pass

        if matched is None:
            cls._unfocus()
            return

        cls._position_cursor(matched, hit)

    @classmethod
    def _global_tick(cls, dt):
        """The tick attached to PyActorGlobalClick by _ensure_global_typing."""
        cls._poll_keyboard()
        cls._poll_mouse_click()
