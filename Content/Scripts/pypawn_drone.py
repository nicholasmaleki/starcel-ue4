import unreal_engine as ue
from unreal_engine.classes import KismetMathLibrary
from unreal_engine import FVector, FRotator
from constants import FiniteRepetitionSelector
from input_devices import Keyboard, Mouse, HotkeyManager, TraceHelper

class PyPawnDrone:
    """
    Drone controller for UnrealEnginePython.

    Movement  : W/A/S/D  (forward/left/back/right)  +  E/Q  (up/down)
    Rotation  : Mouse X → yaw (or roll when roll-mode active)
                Mouse Y → pitch
    Roll-mode : Hold Middle Mouse Button to toggle roll (horizontal mouse = roll delta)
    Size      : Ctrl + ScrollUp / ScrollDown
    Speed     : Shift + ScrollUp / ScrollDown
                (speed is applied as direct position delta, not physics velocity)

    The FiniteRepetitionSelector is used to compute the size / speed increments.
    """

    # ── tunables ──────────────────────────────────────────────────────────────
    DEFAULT_MOVE_SPEED     : float = 10.0   # uu per tick (direct position change)
    DEFAULT_ROTATION_SPEED : float = 1.0    # degrees per mouse-unit
    SCROLL_SENSITIVITY     : float = 1.0    # multiplier applied before selector

    def begin_play(self):
        # uobject IS the pawn when the script is attached directly to the Pawn actor
        self.pawn = self.uobject

        # movement / rotation state
        self.move_speed     = self.DEFAULT_MOVE_SPEED
        self.rotation_speed = self.DEFAULT_ROTATION_SPEED
        self.roll_mode      = False   # toggled by middle-mouse hold

        # axis accumulators filled each tick by bind_axis callbacks
        self._axis_forward  = 0.0
        self._axis_right    = 0.0
        self._axis_up       = 0.0
        self._axis_mouse_x  = 0.0
        self._axis_mouse_y  = 0.0

        # selectors for size & speed scaling
        self.size_selector  = FiniteRepetitionSelector(current_operator="+", current_operand=10.0)
        self.speed_selector = FiniteRepetitionSelector(current_operator="+", current_operand=1.0)

        # HotkeyManager setup (same pattern as your existing code)
        self.uobject.get_player_controller().enable_input()
        self.keyboard = Keyboard()
        self.mouse = Mouse()
        self.input = HotkeyManager(self.uobject, self.keyboard, self.mouse)

        self._setup_input()
        ue.log("PyPawnDrone: begin_play OK")

    # ── input setup ───────────────────────────────────────────────────────────

    def _setup_input(self):
        # ── WASD + EQ movement (polled each tick) ────────────────────────────
        self.input.bind_axis("MoveForward", self._on_axis_forward)
        self.input.bind_axis("MoveRight", self._on_axis_right)
        self.input.bind_axis("MoveUp", self._on_axis_up)

        # ── mouse look ───────────────────────────────────────────────────────
        self.input.bind_axis("MouseX", self._on_mouse_x)
        self.input.bind_axis("MouseY", self._on_mouse_y)

        # ── middle mouse button → roll mode ──────────────────────────────────
        self.input.bind_press(  "MiddleMouseButton", self._on_mmb_pressed)
        self.input.bind_release("MiddleMouseButton", self._on_mmb_released)

        # ── Ctrl + scroll → size ─────────────────────────────────────────────
        self.input.bind_press("Ctrl+MouseScrollUp", self._on_ctrl_scroll_up)
        self.input.bind_press("Ctrl+MouseScrollDown", self._on_ctrl_scroll_down)

        # ── Shift + scroll → speed ───────────────────────────────────────────
        self.input.bind_press("Shift+MouseScrollUp", self._on_shift_scroll_up)
        self.input.bind_press("Shift+MouseScrollDown", self._on_shift_scroll_down)

    # ── axis callbacks ────────────────────────────────────────────────────────

    def _on_axis_forward(self, v): self._axis_forward = v
    def _on_axis_right(self,   v): self._axis_right   = v
    def _on_axis_up(self,      v): self._axis_up      = v
    def _on_mouse_x(self,      v): self._axis_mouse_x = v
    def _on_mouse_y(self,      v): self._axis_mouse_y = v

    # ── middle mouse ──────────────────────────────────────────────────────────

    def _on_mmb_pressed(self):
        self.roll_mode = True
        ue.log("PyPawnDrone: roll mode ON")

    def _on_mmb_released(self):
        self.roll_mode = False
        ue.log("PyPawnDrone: roll mode OFF")

    # ── ctrl scroll → size ───────────────────────────────────────────────────

    def _on_ctrl_scroll_up(self):
        s   = self.uobject.get_actor_scale()
        new = self.size_selector.increase_value(s.x)
        self.uobject.set_actor_scale(FVector(new, new, new))
        ue.log(f"PyPawnDrone: scale → {new:.3f}")

    def _on_ctrl_scroll_down(self):
        s   = self.uobject.get_actor_scale()
        new = max(0.01, self.size_selector.decrease_value(s.x))
        self.uobject.set_actor_scale(FVector(new, new, new))
        ue.log(f"PyPawnDrone: scale → {new:.3f}")

    # ── shift scroll → speed ─────────────────────────────────────────────────

    def _on_shift_scroll_up(self):
        self.move_speed = max(0.01, self.speed_selector.increase_value(self.move_speed))
        ue.log(f"PyPawnDrone: move_speed → {self.move_speed:.3f}")

    def _on_shift_scroll_down(self):
        self.move_speed = max(0.01, self.speed_selector.decrease_value(self.move_speed))
        ue.log(f"PyPawnDrone: move_speed → {self.move_speed:.3f}")

    # ── tick ─────────────────────────────────────────────────────────────────

    def tick(self, dt: float):
        if not hasattr(self, "_axis_forward"):
            return   # begin_play didn't complete cleanly; skip until ready
        self._apply_movement(dt)
        self._apply_rotation(dt)

    def _apply_movement(self, dt: float):
        """Direct-position drone movement along local axes."""
        fwd   = self._axis_forward
        right = self._axis_right
        up    = self._axis_up

        if fwd == 0.0 and right == 0.0 and up == 0.0:
            return

        rot          = self.uobject.get_actor_rotation()
        fwd_vec      = KismetMathLibrary.GetForwardVector(rot)
        right_vec    = KismetMathLibrary.GetRightVector(rot)
        up_vec       = KismetMathLibrary.GetUpVector(rot)

        delta = (
            fwd_vec   * (fwd   * self.move_speed) +
            right_vec * (right * self.move_speed) +
            up_vec    * (up    * self.move_speed)
        )

        current = self.uobject.get_actor_location()
        self.uobject.set_actor_location(current + delta)

    def _apply_rotation(self, dt: float):
        """
        Mouse X  →  roll  (when roll_mode)  or  yaw  (normal)
        Mouse Y  →  pitch (always)
        """
        mx = self._axis_mouse_x
        my = self._axis_mouse_y

        if mx == 0.0 and my == 0.0:
            return

        rs    = self.rotation_speed
        pitch = my * rs   # delta pitch  (Y axis of rotation)

        if self.roll_mode:
            # add_actor_local_rotation: roll delta on X, pitch on Y
            delta = FRotator(pitch, 0.0, mx * rs)   # (pitch, yaw, roll)
            self.uobject.add_actor_local_rotation(delta)
        else:
            # yaw in world space, pitch in local space
            yaw_delta   = FRotator(0.0,  mx * rs, 0.0)
            pitch_delta = FRotator(pitch, 0.0,    0.0)
            self.uobject.add_actor_world_rotation(yaw_delta)
            self.uobject.add_actor_local_rotation(pitch_delta)

