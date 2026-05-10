import os
import unreal_engine as ue
from unreal_engine.classes import KismetMathLibrary
from unreal_engine import FVector, FRotator, FQuat, FTransform
from constants import FiniteRepetitionSelector
from input_devices import Keyboard, Mouse, HotkeyManager, TraceHelper
import math

try:
    from unreal_engine.classes import StaticMeshActor, StaticMesh, Material
    from unreal_engine.enums import EComponentMobility
except Exception:
    StaticMeshActor = None
    StaticMesh = None
    Material = None
    EComponentMobility = None

# TYPING REFERENCE (never changes):
#   FVector  -> .x  .y  .z
#   FRotator -> .roll  .pitch  .yaw   (constructor order: roll, pitch, yaw)


class PyPawnDrone:
    """
    Drone controller for UnrealEnginePython.

    Movement       : W/A/S/D (forward/left/back/right) + E/Q (up/down)
    Rotation       : Mouse X -> yaw (or roll when MMB held)
                     Mouse Y -> pitch
    Roll-mode      : Hold MMB -> horizontal = roll, vertical = pitch
    Size           : Ctrl + Scroll  (x2 / /2, lerped)   [Ctrl beats Alt]
    Speed          : Shift + Scroll (x2 / /2)
    Spring arm     : Alt + Scroll   (scroll up = shorter, scroll down = longer, lerped)
    Free look      : Hold Alt (without Ctrl) -> FreeLookCamera active
                     Release -> FirstPersonCameraCenter active
    continuous_tilt: True  -> full local rotation (default)
                     False -> screen-space: world yaw + clamped world pitch,
                              mouse-up always moves camera up regardless of roll
    """

    DEFAULT_MOVE_SPEED = 10.0
    DEFAULT_ROTATION_SPEED = 1.0
    SCALE_LERP_SPEED = 20.0
    DEBUG = False

    # #
    #  Lifecycle                                                           #
    # #

    def begin_play(self):
        self.pawn = self.uobject
        self.move_speed = self.DEFAULT_MOVE_SPEED
        self.rotation_speed = self.DEFAULT_ROTATION_SPEED
        self.roll_mode = False
        self.continuous_tilt = True # keep true as gimbal lock/traditional mode is broken
        self.legacy_mode = True # keep true as quat mode is broken

        rot = self.uobject.get_actor_rotation()   # FRotator
        self._yaw = rot.yaw
        self._pitch = rot.pitch
        self._roll = rot.roll

        self._axis_forward = 0.0
        self._axis_right = 0.0
        self._axis_up = 0.0
        self._axis_mouse_x = 0.0
        self._axis_mouse_y = 0.0

        self._target_scale = self.uobject.get_actor_scale()  # FVector
        self._target_arm_length = None   # init from component on first tick

        self.size_selector = FiniteRepetitionSelector(current_operator="*", current_operand=2.0)
        self.speed_selector = FiniteRepetitionSelector(current_operator="*", current_operand=2.0)
        self.arm_selector = FiniteRepetitionSelector(current_operator="*", current_operand=2.0)

        self.keyboard = Keyboard()
        self.mouse = Mouse()
        self.input = HotkeyManager(self.uobject, self.keyboard, self.mouse)

        # Crosshair image plane attached to Screen component
        self.crosshair_actor = None
        self._spawn_crosshair()

        self._dbg("PyPawnDrone: begin_play OK")

    # #
    #  Crosshair — tiny image plane attached to Screen cube center        #
    # #

    CROSSHAIR_PATH = r'C:\Users\nicho\Documents\Unreal Projects\Starcel9\Content\Materials\crosshair.png'
    CROSSHAIR_MATS = (
        '/Game/Materials/M_TexturePicture',
        '/Game/Materials/M_TextureUnlit',
    )
    CROSSHAIR_PARAM = 'Texture'
    CROSSHAIR_SCALE = .0285   # multiplier so tiny PNGs are visible at distance
    SCREEN_NAME = 'Screen'

    def _spawn_crosshair(self):
        """Add a StaticMeshComponent (cube) to the owning actor, attach it
        to the Screen component, and texture it with crosshair.png.

        This does NOT spawn a separate actor or touch the Screen's own
        material — it creates a new component on the same actor."""
        from unreal_engine_tools import find_component
        from unreal_engine.classes import StaticMeshComponent

        screen = find_component(self.uobject, self.SCREEN_NAME)
        if screen is None:
            self._dbg(f'PyPawnDrone: no "{self.SCREEN_NAME}" component — '
                      'crosshair skipped')
            return

        if not os.path.exists(self.CROSSHAIR_PATH):
            ue.log_warning(f'PyPawnDrone: crosshair not found: '
                           f'"{self.CROSSHAIR_PATH}"')
            return

        try:
            from PIL import Image as PILImage
            from unreal_engine_tools import pil_image_to_texture

            pil_img = PILImage.open(self.CROSSHAIR_PATH).convert('RGBA')
            img_w, img_h = float(pil_img.width), float(pil_img.height)

            # Load material
            mat = None
            mat_name = None
            for mp in self.CROSSHAIR_MATS:
                if mat is not None:
                    break
                for path in (mp + '.' + mp.split('/')[-1], mp):
                    try:
                        mat = ue.load_object(Material, path)
                        mat_name = mp.split('/')[-1]
                        break
                    except Exception:
                        pass

            if mat is None:
                ue.log_warning(f'PyPawnDrone: no usable crosshair material '
                               f'(tried {[m.split("/")[-1] for m in self.CROSSHAIR_MATS]}) '
                               '— skipping crosshair')
                return

            tex = pil_image_to_texture(pil_img)
            if tex is None:
                ue.log_warning('PyPawnDrone: pil_image_to_texture returned None')
                return

            # Spawn a SEPARATE actor (add_actor_component crashes BP actors
            # with construction scripts during begin_play)
            from unreal_engine_tools import get_world
            world = self.uobject.get_world() or get_world()
            actor = world.actor_spawn(StaticMeshActor)
            # Disable collision so the Screen's SpringArm probe doesn't trip
            # on the crosshair and collapse the arm to the drone center.
            actor.SetActorEnableCollision(False)
            smc = actor.StaticMeshComponent
            smc.Mobility = EComponentMobility.Movable
            cube = ue.load_object(StaticMesh, '/Engine/BasicShapes/Cube.Cube')
            smc.SetStaticMesh(cube)

            mid = smc.create_material_instance_dynamic(mat)
            mid.set_material_texture_parameter(self.CROSSHAIR_PARAM, tex)
            smc.set_material(0, mid)

            # attach_to_component defaults are SnapToTarget(loc) / KeepWorld(rot) /
            # SnapToTarget(scale), which wipes the relative transform on attach.
            # Pass all-KeepRelative (0) so post-attach SetRelative* calls stick.
            actor.attach_to_component(screen, '', 0, 0, 0, False)

            # Mark scale absolute so parent (Screen / pawn) scale changes
            # after spawn don't stretch the cube. The Screen's world scale
            # reads as (1,1,1) at begin_play but ends up non-uniform later;
            # without this the cube inherits that stretch.
            try:
                smc.SetAbsolute(False, False, True)
            except Exception:
                try:
                    smc.bAbsoluteScale = True
                except Exception:
                    pass

            tgt = (img_w * self.CROSSHAIR_SCALE / 100.0)
            actor.set_actor_scale(FVector(0.001, tgt, tgt))

            # y_rel = -(50.0 + 0.5 / py)
            actor.K2_SetActorRelativeLocation(FVector(0, 0, 0))

            self.crosshair_actor = actor  # keep ref for cleanup
            ue.log(f'PyPawnDrone: crosshair {int(img_w)}x{int(img_h)} px '
                   f'component attached to "{self.SCREEN_NAME}" (mat={mat_name})')
        except Exception as e:
            ue.log_warning(f'PyPawnDrone: crosshair spawn failed: {e}')

    def end_play(self, reason):
        if hasattr(self, 'crosshair_actor') and self.crosshair_actor:
            try:
                self.crosshair_actor.DestroyComponent()
            except Exception:
                try:
                    self.crosshair_actor.actor_destroy()
                except Exception:
                    pass
        if hasattr(self, 'input') and self.input:
            self.input.shutdown()

    # #
    #  Input setup                                                         #
    # #

    def _setup_input(self):
        self._dbg("PyPawnDrone: _setup_input")
        pc = self.uobject.get_player_controller()
        if pc is None:
            ue.log_warning("PyPawnDrone: _setup_input called before Possess; aborting")
            return
        # APawn::EnableInput is a no-op override (just toggles bInputEnabled)
        # and does NOT create the pawn's InputComponent, so pawn.bind_axis
        # raises "no input manager for this uobject". Bind through the PC's
        # InputComponent instead — InitInputSystem guarantees it exists.
        self.input = HotkeyManager(pc, self.keyboard, self.mouse)
        self.input.bind_axis("MoveForward", self._on_axis_forward)
        self.input.bind_axis("MoveRight",   self._on_axis_right)
        self.input.bind_axis("MoveUp",      self._on_axis_up)
        self.input.bind_axis("MouseX",      self._on_mouse_x)
        self.input.bind_axis("MouseY",      self._on_mouse_y)
        self.input.bind_press("MiddleMouseButton",   self._on_mmb_pressed)
        self.input.bind_release("MiddleMouseButton", self._on_mmb_released)
        self.input.bind_press("LeftAlt",    self._on_alt_pressed)
        self.input.bind_release("LeftAlt",  self._on_alt_released)
        self.input.bind_press("MouseScrollUp",   self._on_scroll_up)
        self.input.bind_press("MouseScrollDown", self._on_scroll_down)

    # #
    #  Helpers                                                             #
    # #

    def _get_component(self, name):
        try:
            return self.uobject.get_actor_component(name)
        except Exception as e:
            ue.log_warning(f"PyPawnDrone: could not find component '{name}': {e}")
            return None

    def _set_mesh_owner_no_see(self, enabled):
        try:
            self._get_component('SkeletalMesh').bOwnerNoSee = enabled
            self._get_component('SkeletalMeshOutline').bOwnerNoSee = enabled
            # mesh.MarkRenderStateDirty()
            self._dbg(f"PyPawnDrone: Mesh bOwnerNoSee -> {enabled}")
        except Exception as e:
            ue.log_warning(f"PyPawnDrone: could not set bOwnerNoSee: {e}")

    def toggle_continuous_tilt(self):
        self.continuous_tilt = not self.continuous_tilt
        if not self.continuous_tilt:
            rot = self.uobject.get_actor_rotation()
            self._yaw = rot.yaw
            self._pitch = rot.pitch
            self._roll = rot.roll
        self._dbg(f"PyPawnDrone: continuous_tilt={'ON' if self.continuous_tilt else 'OFF'}")

    def toggle_debug(self):
        self.DEBUG = not self.DEBUG
        ue.log(f"PyPawnDrone: debug={'ON' if self.DEBUG else 'OFF'}")

    def _dbg(self, msg):
        if self.DEBUG:
            ue.log(f"[DBG] {msg}")

    def _is_typing(self):
        """True when a Text3D actor is focused for typing — drone input
        (movement, rotation, scroll modes, MMB roll, Alt freelook) should
        be suppressed so 'w', mouse moves, AltGr, etc. don't double as
        drone controls. Release handlers stay ungated so any state set
        before typing started still gets cleaned up on key release."""
        try:
            from pyactor_global_click import PyActorGlobalClick
            return PyActorGlobalClick.is_any_focused()
        except Exception:
            return False

    # #
    #  Axis handlers                                                       #
    # #

    # Axis setters belt-and-brace _apply_movement / _apply_rotation: storing
    # 0.0 while typing means a stale class or any other reader of these
    # attributes (Blueprint, future tick path, hot-reloaded duplicate) still
    # sees no input.
    def _on_axis_forward(self, v): self._axis_forward = 0.0 if self._is_typing() else v
    def _on_axis_right(self, v):   self._axis_right = 0.0 if self._is_typing() else v
    def _on_axis_up(self, v):      self._axis_up = 0.0 if self._is_typing() else v
    def _on_mouse_x(self, v):      self._axis_mouse_x = 0.0 if self._is_typing() else v
    def _on_mouse_y(self, v):      self._axis_mouse_y = 0.0 if self._is_typing() else v

    def _on_mmb_pressed(self):
        if self._is_typing():
            return
        self.roll_mode = True
        self._dbg("PyPawnDrone: roll mode ON")

    def _on_mmb_released(self):
        self.roll_mode = False
        self._dbg("PyPawnDrone: roll mode OFF")

    # #
    #  Alt (free-look) -- only fires when Ctrl is NOT held                #
    # #

    def _on_alt_pressed(self):
        if self._is_typing():
            return
        if self.input.is_key_down("Ctrl"):
            self._dbg("PyPawnDrone: alt+ctrl pressed -> size mode, no freelook")
            return
        try:
            self._set_mesh_owner_no_see(False)
            flc = self._get_component('FreeLookCamera')
            fpc = self._get_component('FirstPersonCameraCenter')
            self._dbg(f"PyPawnDrone: alt pressed -> FreeLook ON  (flc={flc}, fpc={fpc})")
            if flc:
                flc.SetActive(True, False)
                self._dbg(f"  FreeLookCamera.bIsActive after SetActive(True)  = {getattr(flc, 'bIsActive', '?')}")
            if fpc:
                fpc.SetActive(False, False)
                self._dbg(f"  FirstPersonCameraCenter.bIsActive after SetActive(False) = {getattr(fpc, 'bIsActive', '?')}")
        except Exception as e:
            ue.log_warning(f"PyPawnDrone: alt pressed error: {e}")

    def _on_alt_released(self):
        try:
            self._set_mesh_owner_no_see(True)
            flc = self._get_component('FreeLookCamera')
            fpc = self._get_component('FirstPersonCameraCenter')
            self._dbg(f"PyPawnDrone: alt released -> FirstPerson ON (flc={flc}, fpc={fpc})")
            if flc:
                flc.SetActive(False, False)
                self._dbg(f"  FreeLookCamera.bIsActive after SetActive(False) = {getattr(flc, 'bIsActive', '?')}")
            if fpc:
                fpc.SetActive(True, False)
                self._dbg(f"  FirstPersonCameraCenter.bIsActive after SetActive(True)  = {getattr(fpc, 'bIsActive', '?')}")
        except Exception as e:
            ue.log_warning(f"PyPawnDrone: alt released error: {e}")

    # #
    #  Scroll -- Ctrl > Alt > Shift priority                              #
    # #

    def _on_scroll_up(self):
        if self._is_typing():
            return
        if self.input.is_key_down("Ctrl"):
            self._on_ctrl_scroll_up()
        elif self.input.is_key_down("LeftAlt"):
            self._on_alt_scroll_up()
        elif self.input.is_key_down("Shift"):
            self._on_shift_scroll_up()

    def _on_scroll_down(self):
        if self._is_typing():
            return
        if self.input.is_key_down("Ctrl"):
            self._on_ctrl_scroll_down()
        elif self.input.is_key_down("LeftAlt"):
            self._on_alt_scroll_down()
        elif self.input.is_key_down("Shift"):
            self._on_shift_scroll_down()

    def _on_ctrl_scroll_up(self):
        new = max(0.0, self.size_selector.increase_value(self._target_scale.x))
        self._target_scale = FVector(new, new, new)
        self._dbg(f"PyPawnDrone: size target -> {new:.3f}")

    def _on_ctrl_scroll_down(self):
        new = max(0.0, self.size_selector.decrease_value(self._target_scale.x))
        self._target_scale = FVector(new, new, new)
        self._dbg(f"PyPawnDrone: size target -> {new:.3f}")

    def _on_shift_scroll_up(self):
        self.move_speed = max(0.0, self.speed_selector.increase_value(self.move_speed))
        self._dbg(f"PyPawnDrone: move_speed -> {self.move_speed:.3f}")

    def _on_shift_scroll_down(self):
        self.move_speed = max(0.0, self.speed_selector.decrease_value(self.move_speed))
        self._dbg(f"PyPawnDrone: move_speed -> {self.move_speed:.3f}")

    # Scroll UP = shorter arm (decrease), scroll DOWN = longer arm (increase)
    def _on_alt_scroll_up(self):
        sa = self._get_component('FreeLookSpringArm')
        if not sa:
            return
        try:
            base = self._target_arm_length if self._target_arm_length is not None else sa.TargetArmLength
            self._target_arm_length = max(0.0, self.arm_selector.decrease_value(base))
            self._dbg(f"PyPawnDrone: arm target -> {self._target_arm_length:.3f}")
        except Exception as e:
            ue.log_warning(f"PyPawnDrone: arm scroll error: {e}")

    def _on_alt_scroll_down(self):
        sa = self._get_component('FreeLookSpringArm')
        if not sa:
            return
        try:
            base = self._target_arm_length if self._target_arm_length is not None else sa.TargetArmLength
            self._target_arm_length = max(0.0, self.arm_selector.increase_value(base))
            self._dbg(f"PyPawnDrone: arm target -> {self._target_arm_length:.3f}")
        except Exception as e:
            ue.log_warning(f"PyPawnDrone: arm scroll error: {e}")

    # #
    #  Tick                                                                #
    # #

    def tick(self, dt):
        if not hasattr(self, "_axis_forward"):
            return
        self._apply_movement(dt)
        self._apply_rotation(dt)
        self._apply_scale_lerp(dt)
        self._apply_arm_lerp(dt)

    # #
    #  Scale lerp -- FVector uses .x .y .z                               #
    # #

    def _apply_scale_lerp(self, dt):
        cur = self.uobject.get_actor_scale()   # FVector: .x .y .z
        tgt = self._target_scale               # FVector: .x .y .z
        a = min(1.0, self.SCALE_LERP_SPEED * dt)
        self.uobject.set_actor_scale(FVector(
            cur.x + (tgt.x - cur.x) * a,
            cur.y + (tgt.y - cur.y) * a,
            cur.z + (tgt.z - cur.z) * a,
        ))

    # #
    #  Arm lerp                                                            #
    # #

    def _apply_arm_lerp(self, dt):
        sa = self._get_component('FreeLookSpringArm')
        if not sa:
            return
        try:
            actual = sa.TargetArmLength
            if self._target_arm_length is None:
                self._target_arm_length = actual
                self._dbg(f"PyPawnDrone: arm lerp initialized to {actual:.3f}")
                return
            diff = self._target_arm_length - actual
            if abs(diff) < 0.01:
                self.uobject.call_function('SetFreeLookArmLength', self._target_arm_length)
                return
            a = min(1.0, self.SCALE_LERP_SPEED * dt)
            self.uobject.call_function('SetFreeLookArmLength', actual + diff * a)
            self._dbg(f"arm lerp {actual:.1f} -> {self._target_arm_length:.1f}")
        except Exception as e:
            ue.log_warning(f"PyPawnDrone: arm lerp error: {e}")

    # #
    #  Movement                                                            #
    # #

    def _apply_movement(self, dt):
        if self._is_typing():
            return
        fwd = self._axis_forward
        right = self._axis_right
        up = self._axis_up
        if fwd == 0.0 and right == 0.0 and up == 0.0:
            return
        rot = self.uobject.get_actor_rotation()
        fwd_vec = KismetMathLibrary.GetForwardVector(rot)
        right_vec = KismetMathLibrary.GetRightVector(rot)
        up_vec = KismetMathLibrary.GetUpVector(rot)
        delta = (
            fwd_vec   * (fwd   * self.move_speed) +
            right_vec * (right * self.move_speed) +
            up_vec    * (up    * self.move_speed)
        )
        self.uobject.set_actor_location(self.uobject.get_actor_location() + delta)

    # #
    #  Rotation                                                            #
    # #

    def _apply_rotation(self, dt):
        if self._is_typing():
            return
        # FRotator attrs: .roll .pitch .yaw  (constructor: roll, pitch, yaw)
        mx = self._axis_mouse_x
        my = self._axis_mouse_y
        rs = self.rotation_speed

        alt_held = self.input.is_key_down("LeftAlt")
        ctrl_held = self.input.is_key_down("Ctrl")

        # Ctrl+Alt -> size-only mode, skip all rotation
        if alt_held and ctrl_held:
            return

        # Alt only -> free-look: rotate FreeLookSpringArm component
        if alt_held:
            sa = self._get_component('FreeLookSpringArm')
            if sa:
                if self.roll_mode:
                    if mx != 0.0:
                        sa.AddLocalRotation(FRotator(mx * rs, 0.0, 0.0))
                    if my != 0.0:
                        sa.AddLocalRotation(FRotator(0.0, my * rs, 0.0))
                else:
                    if mx != 0.0:
                        sa.AddLocalRotation(FRotator(0.0, 0.0, mx * rs))
                    if my != 0.0:
                        sa.AddLocalRotation(FRotator(0.0, my * rs, 0.0))
            return

        if self.continuous_tilt:
            cur_q = self.uobject.get_actor_rotation().quaternion()

            if self.legacy_mode:
                if self.roll_mode:
                    if mx != 0.0:
                        self.uobject.add_actor_local_rotation(FRotator(mx * rs, 0.0, 0.0))
                    if my != 0.0:
                        self.uobject.add_actor_local_rotation(FRotator(0.0, my * rs, 0.0))
                else:
                    if mx != 0.0:
                        self.uobject.add_actor_local_rotation(FRotator(0.0, 0.0, mx * rs))
                    if my != 0.0:
                        self.uobject.add_actor_local_rotation(FRotator(0.0, my * rs, 0.0))
            else:
                pass
                # if self.roll_mode:
                #     if mx != 0.0 or my != 0.0:
                #         fwd = KismetMathLibrary.GetForwardVector(self.uobject.get_actor_rotation())
                #         right = KismetMathLibrary.GetRightVector(self.uobject.get_actor_rotation())
                #         ax = fwd.x * mx * rs - right.x * my * rs
                #         ay = fwd.y * mx * rs - right.y * my * rs
                #         az = fwd.z * mx * rs - right.z * my * rs
                #         angle = math.sqrt(ax * ax + ay * ay + ay * ay)
                #         if angle > 0.0:
                #             angle_r = math.radians(angle)
                #             s = math.sin(angle_r / 2) / angle
                #             dq = FQuat(ax * s, ay * s, az * s, math.cos(angle_r / 2))
                #             cur_q = cur_q * dq
                #             self.uobject.set_actor_rotation(cur_q)
                # else:
                #     if mx != 0.0 or my != 0.0:
                #         up = KismetMathLibrary.GetUpVector(self.uobject.get_actor_rotation())
                #         right = KismetMathLibrary.GetRightVector(self.uobject.get_actor_rotation())
                #         # combined axis: weighted sum of up and right, then normalize
                #         ax = up.x * mx * rs - right.x * my * rs
                #         ay = up.y * mx * rs - right.y * my * rs
                #         az = up.z * mx * rs - right.z * my * rs
                #         angle = math.sqrt(ax*ax + ay*ay + az*az)
                #         if angle > 0.0:
                #             angle_r = math.radians(angle)
                #             s = math.sin(angle_r/2) / angle
                #             dq = FQuat(ax * s, ay * s, az * s, math.cos(angle_r/2))
                #             cur_q = cur_q * dq
                #             self.uobject.set_actor_rotation(cur_q)

        else:
            # Gimbal lock singularity avoidance:
            # near poles, blend yaw into roll so we never fully lock
            self._pitch += my * rs
            self._pitch = max(-90.0, min(90.0, self._pitch))

            if self.roll_mode:
                self._roll += mx * rs
            else:
                pole_proximity = abs(self._pitch) / 90.0
                yaw_component = mx * rs * (1.0 - pole_proximity)
                roll_component = mx * rs * pole_proximity
                self._yaw += yaw_component
                self._roll += roll_component

            # FRotator(roll, pitch, yaw)
            self.uobject.set_actor_rotation(FRotator(self._roll, self._pitch, self._yaw))