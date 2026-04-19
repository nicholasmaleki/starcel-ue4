import unreal_engine as ue
from unreal_engine import FVector, FRotator, FTransform
from unreal_engine.enums import ECollisionChannel, EInputEvent
from unreal_engine_tools import find_component


class PyActorText3DGlobal:
    """Singleton PyActor that runs one tick for ALL Text3D actors in the scene.

    Replaces the per-frame closure that used to be returned by
    test_spawn.test_text3d_click — global keyboard poll for typing, caret
    blink, click rising-edge, focus management, highlight rendering.

    Call set_tick_fn(fn) after spawn with the tick closure built by
    test_text3d_click (which still owns the state machine via closures — a
    future refactor could migrate that state onto this class directly).
    """

    def begin_play(self):
        self._tick_fn = None
        ue.log('PyActorText3DGlobal: ready (awaiting set_tick_fn)')

    def set_tick_fn(self, fn):
        self._tick_fn = fn
        ue.log('PyActorText3DGlobal: tick function attached')

    def tick(self, dt):
        fn = self._tick_fn
        if fn is None:
            return
        try:
            fn(dt)
        except Exception as e:
            try:
                ue.log_warning(f'PyActorText3DGlobal tick error: {e}')
            except Exception:
                pass

try:
    from unreal_engine.classes import StaticMeshActor, StaticMesh, Material
    from unreal_engine.enums import EComponentMobility
except Exception:
    StaticMeshActor = StaticMesh = Material = EComponentMobility = None

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
# Override _on_char_click(col, row) in a subclass or replace after spawn.

class PyActorText3D:
    """
    Hover scale animation + click-to-character-coordinate logging
    for a Text3DComponent-based Blueprint actor.

    Click detection is tick-based (Text3DComponent has no OnClicked event).
    Hover detection tries component events first, falls back to tick polling.
    """

    HOVER_DELTA = 0.3
    LERP_SPEED  = 8.0

    # Approximate UE units per character at the default Text3D font size (100).
    # Tune to match the actual font size in your Blueprint.
    CHAR_WIDTH  = 50.0
    CHAR_HEIGHT = 50.0

    TEXT_COMPONENT_NAME = 'Text3DComponent'

    # Insertion cursor settings
    CURSOR_BLINK_RATE = 1.0        # seconds per blink cycle
    CURSOR_COLOR      = (1, 1, 1, 0.6)
    CURSOR_MAT_PATH   = '/Game/Materials/M_Color_Translucent.M_Color_Translucent'

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

        # Insertion cursor state
        self._cursor_actor   = None
        self._cursor_mid     = None
        self._cursor_visible = False
        self._cursor_timer   = 0.0
        self._cursor_char_idx = -1

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

        self._spawn_cursor()

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

    # Insertion cursor

    def _spawn_cursor(self):
        """Spawn a thin translucent cube as a blinking insertion point."""
        if StaticMeshActor is None or self.text3d is None:
            return
        world = None
        try:
            world = self.uobject.get_world()
        except Exception:
            pass
        if world is None:
            return

        try:
            actor = world.actor_spawn(StaticMeshActor)
            smc   = actor.StaticMeshComponent
            cube  = ue.load_object(StaticMesh, '/Engine/BasicShapes/Cube.Cube')
            smc.SetStaticMesh(cube)
            smc.SetMobility(EComponentMobility.Movable)

            mat = ue.load_object(Material, self.CURSOR_MAT_PATH)
            mid = smc.create_material_instance_dynamic(mat)
            smc.set_material(0, mid)

            # Scale: thin bar, quarter-char width, full char height.
            # Cube is 100 UU base → divide by 100.
            cw = self.CHAR_WIDTH  / 100.0 * 0.25
            ch = self.CHAR_HEIGHT / 100.0
            cd = 0.01
            actor.set_actor_scale(FVector(cd, cw, ch))

            actor.attach_to_component(self.text3d)
            actor.SetActorHiddenInGame(True)

            try:
                actor.SetActorLabel('TextCursor')
            except Exception:
                pass

            self._cursor_actor = actor
        except Exception as e:
            ue.log_warning(f'PyActorText3D: cursor spawn failed: {e}')

    def _move_cursor_to(self, char_index):
        """Snap the cursor to the discrete position after the clicked character.

        Uses CharacterKernings for the exact glyph-relative position (discrete),
        falls back to CharacterMeshes bounds, then to fixed-width grid.
        """
        if self._cursor_actor is None or self.text3d is None:
            return
        self._cursor_char_idx = char_index
        self._cursor_timer    = 0.0
        self._cursor_visible  = True

        placed = False
        next_idx = char_index + 1  # cursor goes AFTER the clicked char

        # Strategy 1: CharacterKernings — discrete per-glyph relative positions
        kernings = None
        try:
            kernings = self.text3d.CharacterKernings
        except Exception:
            pass

        if kernings is not None:
            ue.log(f'PyActorText3D cursor: kernings available, len={len(kernings)}, '
                   f'char_index={char_index}, next_idx={next_idx}')
            if next_idx < len(kernings) and kernings[next_idx] is not None:
                try:
                    rel = kernings[next_idx].get_relative_location()
                    ue.log(f'PyActorText3D cursor: kerning[{next_idx}] rel=({rel.x:.1f}, {rel.y:.1f}, {rel.z:.1f})')
                    self._cursor_actor.K2_SetActorRelativeLocation(rel)
                    placed = True
                except Exception as e:
                    ue.log_warning(f'PyActorText3D cursor: kerning strategy failed: {e}')
            elif char_index < len(kernings) and kernings[char_index] is not None:
                try:
                    rel = kernings[char_index].get_relative_location()
                    offset_rel = FVector(rel.x, rel.y + self.CHAR_WIDTH, rel.z)
                    ue.log(f'PyActorText3D cursor: last char, kerning[{char_index}]+CHAR_WIDTH rel=({offset_rel.x:.1f}, {offset_rel.y:.1f}, {offset_rel.z:.1f})')
                    self._cursor_actor.K2_SetActorRelativeLocation(offset_rel)
                    placed = True
                except Exception as e:
                    ue.log_warning(f'PyActorText3D cursor: last-char kerning failed: {e}')
        else:
            ue.log(f'PyActorText3D cursor: no kernings available')

        # Strategy 2: CharacterMeshes bounds — discrete right edge
        if not placed:
            char_meshes = None
            try:
                char_meshes = self.text3d.CharacterMeshes
            except Exception:
                pass

            if char_meshes is not None and 0 <= char_index < len(char_meshes):
                mesh = char_meshes[char_index]
                if mesh is not None:
                    try:
                        rel = mesh.get_relative_location()
                        # Offset by one full glyph width for "after character"
                        self._cursor_actor.K2_SetActorRelativeLocation(
                            FVector(rel.x, rel.y + self.CHAR_WIDTH, rel.z))
                        placed = True
                    except Exception:
                        pass

        # Strategy 3: fixed-width grid
        if not placed:
            y = next_idx * self.CHAR_WIDTH
            try:
                self._cursor_actor.K2_SetActorRelativeLocation(FVector(0, y, 0))
            except Exception:
                pass

        self._cursor_actor.SetActorHiddenInGame(False)

    def _tick_cursor(self, dt):
        """Blink the insertion cursor."""
        if self._cursor_actor is None or self._cursor_char_idx < 0:
            return
        self._cursor_timer += dt
        half = self.CURSOR_BLINK_RATE * 0.5
        should_show = (self._cursor_timer % self.CURSOR_BLINK_RATE) < half
        if should_show != self._cursor_visible:
            self._cursor_visible = should_show
            self._cursor_actor.SetActorHiddenInGame(not should_show)

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

        self._tick_cursor(dt)

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
            self._move_cursor_to(char_index)
