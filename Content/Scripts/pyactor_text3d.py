import unreal_engine as ue
from unreal_engine import FVector, FRotator, FTransform
from unreal_engine.enums import ECollisionChannel, EInputEvent
from unreal_engine_tools import find_component
from pyactor_global_click import PyActorGlobalClick

# Python component: click + hover for any actor with a Text3DComponent
#
# Blueprint requirements:
#   - A Text3DComponent (any name; first one found is used)
#     NOTE: Text3DComponent does NOT support OnClicked events in UEP —
#     click detection uses a per-tick cursor poll instead.
#     Hover (OnBeginCursorOver / OnEndCursorOver) is attempted via component
#     events and falls back to tick-based polling if unavailable.
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
# class owns it and exposes class methods for callers (typing handler in
# test_spawn, click handler here, selection-highlight code) to position,
# show, and hide it.  Sizing/placement tunables live here as class
# constants — see CURSOR_WIDTH_FRAC / CURSOR_VERTICAL_OFFSET_FRAC /
# CURSOR_DIACRITIC_HEADROOM_FRAC.

class PyActorText3D:
    """
    Hover scale animation + click-to-character-coordinate logging
    for a Text3DComponent-based Blueprint actor.

    Click detection is tick-based (Text3DComponent has no OnClicked event).
    Hover detection tries component events first, falls back to tick polling.

    Class-level cursor singleton: see show_cursor_at / hide_cursor /
    compute_placement.  All callers go through these — no per-instance
    cursor exists.
    """

    HOVER_DELTA = 0.3
    LERP_SPEED  = 8.0

    # Approximate UE units per character at the default Text3D font size (100).
    # Tune to match the actual font size in your Blueprint.
    CHAR_WIDTH  = 50.0
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
    CURSOR_WIDTH_FRAC             = 0.068
    CURSOR_VERTICAL_OFFSET_FRAC   = .9
    CURSOR_DIACRITIC_HEADROOM_FRAC = 0.50
    CURSOR_HEIGHT_MULTIPLIER = 1.1

    # Lifecycle

    def begin_play(self):
        self.uobject.enable_input()
        self.player_controller = self.uobject.get_player_controller()
        self.player_controller.bEnableMouseOverEvents = True
        self.player_controller.bEnableClickEvents     = True
        self.player_controller.CurrentClickTraceChannel = ECollisionChannel.ECC_WorldDynamic

        self.base_scale   = self.uobject.get_actor_scale()
        self.target_scale = self.base_scale

        self._was_mouse_down = False
        self._hovered        = False

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
        a   = min(1.0, self.LERP_SPEED * dt)
        self.uobject.set_actor_scale(FVector(
            cur.x + (tgt.x - cur.x) * a,
            cur.y + (tgt.y - cur.y) * a,
            cur.z + (tgt.z - cur.z) * a,
        ))

        if self.text3d is None:
            return

        # Cursor hit this actor?
        hit        = self.uobject.get_hit_result_under_cursor(ECollisionChannel.ECC_WorldDynamic)
        on_self    = hit is not None and hit.actor == self.uobject

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
        d  = self.HOVER_DELTA
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
        mesh_idx   = None
        mesh_letter = None
        if char_meshes is not None and len(char_meshes) > 0:
            best_idx  = -1
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
                        best_idx  = i
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
            idx    = mesh_idx
            method = 'CharacterMeshes'
        else:
            idx    = col
            lines  = text.split('\n')
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
            yaw   = math.radians(-rot.yaw)
            pitch = math.radians(-rot.pitch)
            roll  = math.radians(-rot.roll)
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

    def _is_mouse_down(self):
        try:
            from unreal_engine import FKey
            return self.player_controller.IsInputKeyDown(FKey('LeftMouseButton'))
        except Exception:
            pass
        try:
            # Alternative: check via input component key state
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
            PyActorGlobalClick.set_focused_actor(self.uobject)
        elif PyActorGlobalClick._focused_actor is self.uobject:
            PyActorGlobalClick.set_focused_actor(None)

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
