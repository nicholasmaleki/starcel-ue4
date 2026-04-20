import unreal_engine as ue
from unreal_engine.enums import EMouseCursor, ECollisionChannel
from unreal_engine.classes import StarcelHelper, InputSettings
import time


def _clean(s: str):
    return s.replace(" ", "").replace("_", "").lower()


def _load_project_input_names():
    """Read axis/action mapping names from Project Settings > Input.
    Returns (axis_map, action_map): lowercase token -> canonical name."""
    axis_map, action_map = {}, {}
    try:
        settings = ue.get_mutable_default(InputSettings)
        for n in settings.GetAxisNames():
            name = str(n)
            axis_map[_clean(name)] = name
        for n in settings.GetActionNames():
            name = str(n)
            action_map[_clean(name)] = name
    except Exception as e:
        ue.log_warning(f'input_devices: could not read project input settings: {e}')
    return axis_map, action_map


class Keyboard:
    def __init__(self):
        self.ue_keys = ["AnyKey",
                        "MouseX", "MouseY", "Mouse2D", "MouseScrollUp", "MouseScrollDown", "MouseWheelAxis",
                        "LeftMouseButton", "RightMouseButton", "MiddleMouseButton", "ThumbMouseButton", "ThumbMouseButton2",
                        "BackSpace", "Tab", "Enter", "Pause",
                        "CapsLock", "Escape", "SpaceBar", "PageUp", "PageDown", "End", "Home",
                        "Left", "Up", "Right", "Down",
                        "Insert", "Delete",
                        "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
                        "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
                        "NumPadZero", "NumPadOne", "NumPadTwo", "NumPadThree", "NumPadFour", "NumPadFive", "NumPadSix", "NumPadSeven", "NumPadEight", "NumPadNine",
                        "Multiply", "Add", "Subtract", "Decimal", "Divide",
                        "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
                        "NumLock",
                        "ScrollLock",
                        "LeftShift", "RightShift", "LeftControl", "RightControl", "LeftAlt", "RightAlt", "LeftCommand", "RightCommand",
                        "Semicolon", "Equals", "Comma", "Underscore", "Hyphen", "Period", "Slash", "Tilde", "LeftBracket", "Backslash", "RightBracket", "Apostrophe",
                        "Ampersand", "Asterix", "Caret", "Colon", "Dollar", "Exclamation", "LeftParantheses", "RightParantheses", "Quote"
                        ]

        self.LEGEND_TO_UE = {
            # letters
            **{chr(i): chr(i).upper() for i in range(ord('a'), ord('z') + 1)},
            **{chr(i).upper(): chr(i).upper() for i in range(ord('a'), ord('z') + 1)},

            # numbers
            "0": "Zero", "1": "One", "2": "Two", "3": "Three", "4": "Four", "5": "Five", "6": "Six", "7": "Seven", "8": "Eight", "9": "Nine",

            # numpad
            "NumPadZero": "NumPadZero",
            "NumPadOne": "NumPadOne",
            "NumPadTwo": "NumPadTwo",
            "NumPadThree": "NumPadThree",
            "NumPadFour": "NumPadFour",
            "NumPadFive": "NumPadFive",
            "NumPadSix": "NumPadSix",
            "NumPadSeven": "NumPadSeven",
            "NumPadEight": "NumPadEight",
            "NumPadNine": "NumPadNine",

            # control keys
            "Esc": "Escape",
            "Tab": "Tab",
            "Caps": "CapsLock",
            "Enter": "Enter",
            "Backspace": "BackSpace",
            "Space": "SpaceBar",

            "LeftShift": "LeftShift",
            "RightShift": "RightShift",
            "LeftCtrl": "LeftControl",
            "RightCtrl": "RightControl",
            "LeftAlt": "LeftAlt",
            "RightAlt": "RightAlt",
            "Win": "Win",
            "Menu": "Menu",

            # arrows
            "Left": "Left",
            "Right": "Right",
            "Up": "Up",
            "Down": "Down",

            # navigation
            "Ins": "Insert",
            "Del": "Delete",
            "Home": "Home",
            "End": "End",
            "PgUp": "PageUp",
            "PgDn": "PageDown",

            # symbols
            "`": "Tilde",
            "~": "Tilde",
            "-": "Hyphen",
            "_": "Underscore",
            "=": "Equals",
            "+": "Add",
            "[": "LeftBracket",
            "]": "RightBracket",
            "\\": "Backslash",
            "|": "Backslash",
            ";": "Semicolon",
            ":": "Colon",
            "'": "Apostrophe",
            "\"": "Quote",
            ",": "Comma",
            ".": "Period",
            "/": "Slash",
            "?": "Slash",

            "!": "Exclamation",
            "@": "At",
            "#": "Hash",
            "$": "Dollar",
            "%": "Percent",
            "^": "Caret",
            "&": "Ampersand",
            "*": "Asterix",
            "(": "LeftParantheses",
            ")": "RightParantheses",
        }

        self.keyboard_wootingtwohe = [
            ["Esc", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "PrtSc", "Pause", "ScrLk", "M1", "M2", "M3", "MR"],
            ["`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "Backspace", "Ins", "Home", "PgUp", "Num", "/", "*", "-"],
            ["Tab", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "\\", "Del", "End", "PgDn", "NumPadSeven", "NumPadEight", "NumPadNine", "+"],
            ["Caps", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "Enter", None, None, None, "NumPadFour", "NumPadFive", "NumPadSix", "+"],
            ["LeftShift", "z", "x", "c", "v", "b", "n", "m", "", "", ".", "/", "RightShift", None, "Up", None, "NumPadOne", "NumPadTwo", "NumPadThree", "Enter"],
            ["LeftCtrl", "Win", "LeftAlt", "Space", "RightAlt", "Menu", "Fn", "RightCtrl", "Left", "Down", "Right", "NumPadZero", "NumPadZero", ".", "Enter"]
        ]
        self.keyboard_wootingtwohe_shift = [
            ["Esc", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "PrtSc", "Pause", "ScrLk", "M1", "M2", "M3", "MR"],
            ["~", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+", "Backspace", "Ins", "Home", "PgUp", "Num", "/", "*", "-"],
            ["Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}", "|", "Del", "End", "PgDn", "NumPadSeven", "NumPadEight", "NumPadNine", "+"],
            ["Caps", "A", "S", "D", "F", "G", "H", "J", "K", "L", ":", "\"", "Enter", None, None, None, "NumPadFour", "NumPadFive", "NumPadSix", "+"],
            ["LeftShift", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?", "RightShift", None, "Up", None, "NumPadOne", "NumPadTwo", "NumPadThree", "Enter"],
            ["LeftCtrl", "Win", "LeftAlt", "Space", "RightAlt", "Menu", "Fn", "RightCtrl", "Left", "Down", "Right", "NumPadZero", "NumPadZero", ".", "Enter"]
        ]
        self.keyboard_razerblade152019 = [
            ["Esc", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "Ins", "Delete"],
            ["`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "Backspace"],
            ["Tab", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "\\"],
            ["Caps", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "Enter"],
            ["LeftShift", "z", "x", "c", "v", "b", "n", "m", "", "", ".", "/", "Up", "RightShift"],
            ["LeftCtrl", "Fn", "Win", "LeftAlt", "Space", "RightAlt", "RightCtrl", "Left", "Down", "Right", "Fn"]
        ]
        self.keyboard_razerblade152019_shift = [
            ["Esc", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "Ins", "Delete"],
            ["~", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+", "Backspace"],
            ["Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}", "|"],
            ["Caps", "A", "S", "D", "F", "G", "H", "J", "K", "L", ":", "\"", "Enter"],
            ["LeftShift", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?", "Up", "RightShift"],
            ["LeftCtrl", "Fn", "Win", "LeftAlt", "Space", "RightAlt", "RightCtrl", "Left", "Down", "Right", "Fn"]
        ]
        self.keyboard_ANSI = [
            ["`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "Backspace"],
            ["Tab", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "\\"],
            ["Caps", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "Enter"],
            ["LeftShift", "z", "x", "c", "v", "b", "n", "m", "", "", ".", "/", "RightShift"],
            ["LeftCtrl", "Win", "LeftAlt", "Space", "RightAlt", "Win", "Menu", "RightCtrl"]
        ]
        self.keyboard_ANSI_shift = [
            ["~", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+", "Backspace"],
            ["Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}", "|"],
            ["Caps", "A", "S", "D", "F", "G", "H", "J", "K", "L", ":", "\"", "Enter"],
            ["LeftShift", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?", "RightShift"],
            ["LeftCtrl", "Win", "LeftAlt", "Space", "RightAlt", "Win", "Menu", "RightCtrl"]
        ]

        self.ue_ansi = self.keyboard_to_ue_keyboard(self.keyboard_ANSI)
        self.ue_ansi_shift = self.keyboard_to_ue_keyboard(self.keyboard_ANSI_shift)
        self.ue_wooting = self.keyboard_to_ue_keyboard(self.keyboard_wootingtwohe)
        self.ue_wooting_shift = self.keyboard_to_ue_keyboard(self.keyboard_wootingtwohe_shift)
        self.ue_razerblade152019 = self.keyboard_to_ue_keyboard(self.keyboard_razerblade152019)
        self.ue_razerblade152019_shift = self.keyboard_to_ue_keyboard(self.keyboard_razerblade152019_shift)

        # user-defined aliases
        self.ALIASES = {
            "ctrl": "LeftControl",
            "control": "LeftControl",
            "shift": "LeftShift",
            "alt": "LeftAlt",
            "cmd": "LeftCommand",
            "command": "LeftCommand",
            "win": "LeftCommand",
            "esc": "Escape",
            "space": "SpaceBar",
            "bksp": "BackSpace",
            "del": "Delete",
        }

        self._build_normalize_map()

    def _build_normalize_map(self):
        self.normalize_map = {}
        for k, v in self.LEGEND_TO_UE.items():
            self.normalize_map[_clean(k)] = v
        for k in self.ue_keys:
            self.normalize_map[_clean(k)] = k
        for k, v in self.ALIASES.items():
            self.normalize_map[_clean(k)] = v

    def normalize(self, token):
        if not token:
            return None
        t = token.strip().lower()

        # check aliases first
        if t in self.ALIASES:
            return self.ALIASES[t]

        # check LEGEND_TO_UE
        if token in self.LEGEND_TO_UE:
            return self.LEGEND_TO_UE[token]
        for k, v in self.LEGEND_TO_UE.items():
            if k.lower() == t:
                return v

        # fallback: UE native keys
        if token in self.ue_keys:
            return token
        for k in self.ue_keys:
            if k.lower() == t:
                return k

        print(f"{token} not registered in input_devices")
        return None

    def keyboard_to_ue_keyboard(self, keyboard_layout):
        ue_keyboard = []

        for row in keyboard_layout:
            ue_row = []
            for key in row:
                if key is None or key == "":
                    ue_row.append(None)
                    continue

                ue_key = self.LEGEND_TO_UE.get(key)

                # fallback: already a UE key?
                if ue_key is None and key in self.LEGEND_TO_UE.values():
                    ue_key = key

                ue_row.append(ue_key)
            ue_keyboard.append(ue_row)

        return ue_keyboard


class Mouse:
    def __init__(self):
        self.ue_keys = ["AnyKey",
                        "MouseX", "MouseY", "Mouse2D", "MouseScrollUp", "MouseScrollDown", "MouseWheelAxis",
                        "LeftMouseButton", "RightMouseButton", "MiddleMouseButton", "ThumbMouseButton", "ThumbMouseButton2",
                        "BackSpace", "Tab", "Enter", "Pause",
                        "CapsLock", "Escape", "SpaceBar", "PageUp", "PageDown", "End", "Home",
                        "Left", "Up", "Right", "Down",
                        "Insert", "Delete",
                        "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
                        "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
                        "NumPadZero", "NumPadOne", "NumPadTwo", "NumPadThree", "NumPadFour", "NumPadFive", "NumPadSix", "NumPadSeven", "NumPadEight", "NumPadNine",
                        "Multiply", "Add", "Subtract", "Decimal", "Divide",
                        "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
                        "NumLock",
                        "ScrollLock",
                        "LeftShift", "RightShift", "LeftControl", "RightControl", "LeftAlt", "RightAlt", "LeftCommand", "RightCommand",
                        "Semicolon", "Equals", "Comma", "Underscore", "Hyphen", "Period", "Slash", "Tilde", "LeftBracket", "Backslash", "RightBracket", "Apostrophe",
                        "Ampersand", "Asterix", "Caret", "Colon", "Dollar", "Exclamation", "LeftParantheses", "RightParantheses", "Quote"
                        ]

        self.mouse = ["Left", "Right", "Middle", "ThumbUp", "ThumbDown", "ScrollUp", "ScrollDown", "MouseX", "MouseY", "Mouse2D", "MouseWheelAxis"]

        self.LEGEND_TO_UE = {
            "Left": "LeftMouseButton",
            "Right": "RightMouseButton",
            "Middle": "MiddleMouseButton",
            "ThumbUp": "ThumbUpMouseButton",
            "ThumbDown": "ThumbDownMouseButton",
            "ScrollUp": "MouseScrollUp",
            "ScrollDown": "MouseScrollDown",
            "MouseX": "MouseX",
            "MouseY": "MouseY",
            "Mouse2D": "Mouse2D",
            "MouseWheelAxis": "MouseWheelAxis",
        }

        self.ALIASES = {
            "lmb": "LeftMouseButton",
            "rmb": "RightMouseButton",
            "mmb": "MiddleMouseButton",
            "left": "LeftMouseButton",
            "right": "RightMouseButton",
            "middle": "MiddleMouseButton",
            "wheel": "MouseWheelAxis",
            "scrollup": "MouseScrollUp",
            "scrolldown": "MouseScrollDown",
        }
        self._build_normalize_map()

    def _build_normalize_map(self):
        self.normalize_map = {}
        for k, v in self.LEGEND_TO_UE.items():
            self.normalize_map[_clean(k)] = v
        for k in self.ue_keys:
            self.normalize_map[_clean(k)] = k
        for k, v in self.ALIASES.items():
            self.normalize_map[_clean(k)] = v

    def normalize(self, token):
        if not token:
            return None
        t = token.strip().lower()

        if t in self.ALIASES:
            return self.ALIASES[t]
        if token in self.LEGEND_TO_UE:
            return self.LEGEND_TO_UE[token]
        for k, v in self.LEGEND_TO_UE.items():
            if k.lower() == t:
                return v
        if token in self.ue_keys:
            return token
        for k in self.ue_keys:
            if k.lower() == t:
                return k

        return None  # just return None, no warning


class TraceHelper:
    def __init__(self, uobject):
        self.uobject = uobject
        self.pc = uobject.get_player_controller()

    def trace_forward(self, dist=1000):
        """Trace from camera forward direction"""
        start = self.pc.get_pawn().get_actor_location()
        end = start + self.pc.get_control_rotation().get_forward_vector() * dist
        hit = self.uobject.line_trace_single_by_channel(start, end, ECollisionChannel.ECC_Visibility)
        return hit

    def trace_cursor(self, channel=ECollisionChannel.ECC_Visibility):
        """Trace from cursor position into the world
        Returns: dict with hit information or None if no hit
        """
        return self.uobject.get_hit_result_under_cursor(channel)

    def trace_line(self, start, end, channel=ECollisionChannel.ECC_Visibility):
        """Generic line trace between two points"""
        return self.uobject.line_trace_single_by_channel(start, end, channel)

    def deproject_screen(self, x, y):
        """Convert screen coordinates to world position and direction"""
        success, world_pos, world_dir = self.pc.DeprojectScreenPositionToWorld(x, y)
        if success:
            return world_pos, world_dir
        return None, None


class HotkeyManager:
    def __init__(self, uobject, keyboard, mouse, poll_rate=0.02):
        self.uobject = uobject
        self.keyboard = keyboard
        self.mouse = mouse
        self.sequence_bindings = []
        self.sequence_progress = {}
        self._axis_handlers = {}
        self._last_axis_values = {}
        self._cursor_visible = True
        self.poll_rate = poll_rate
        self._repeat_bindings = []
        self._pollers = []
        self._key_registry = {}  # For future keyboard visualization
        self._is_shutting_down = False

        self._axis_names, self._action_names = _load_project_input_names()

        self.player_controller = self.uobject.get_player_controller()

    def resolve_axis_name(self, token):
        """Look up token case-insensitively in project axis mappings.
        Returns the canonical axis name, or None (with warning) on typo."""
        if not token:
            return None
        canonical = self._axis_names.get(_clean(token))
        if canonical is None:
            ue.log_warning(
                f"bind_axis: '{token}' is not a defined axis mapping. "
                f"Check Project Settings > Input > Axis Mappings.")
        return canonical

    def resolve_action_name(self, token):
        """Look up token case-insensitively in project action mappings."""
        if not token:
            return None
        canonical = self._action_names.get(_clean(token))
        if canonical is None:
            ue.log_warning(
                f"bind_action: '{token}' is not a defined action mapping. "
                f"Check Project Settings > Input > Action Mappings.")
        return canonical

    # Shutdown
    def shutdown(self):
        """Call this in uObject_EndPlay to clean up properly"""
        self._is_shutting_down = True

        # Stop all pollers
        for ticker in self._pollers:
            try:
                if ticker and hasattr(ticker, 'is_valid') and ticker.is_valid():
                    ue.remove_ticker(ticker)
            except:
                pass

        for ticker in self._repeat_bindings:
            try:
                if ticker and hasattr(ticker, 'is_valid') and ticker.is_valid():
                    ue.remove_ticker(ticker)
            except:
                pass

        self._pollers.clear()
        self._repeat_bindings.clear()
        ue.log("HotkeyManager shutdown complete")

    # Cursor
    def enable_mouse_events(self, click=True, over=True):
        """Enable mouse click and mouse-over events"""
        try:
            self.player_controller.bEnableClickEvents = click
            self.player_controller.bEnableMouseOverEvents = over
        except:
            ue.log_warning("Mouse event flags not supported")

    def show_cursor(self, visible=True):
        """Show or hide mouse cursor"""
        try:
            self.player_controller.bShowMouseCursor = visible
            self._cursor_visible = visible
        except:
            ue.log_warning("show cursor failed")

    def set_cursor(self, cursor_type=EMouseCursor.Default):
        """Set cursor type
        Options: None, Default, TextEditBeam, ResizeLeftRight, ResizeUpDown,
                 ResizeSouthEast, ResizeSouthWest, CardinalCross, Crosshairs,
                 Hand, GrabHand, GrabHandClosed, SlashedCircle, EyeDropper
        """
        try:
            self.player_controller.CurrentMouseCursor = cursor_type
            ue.log(f"Mouse cursor set to: {cursor_type}")
        except Exception as e:
            ue.log_warning(f"Failed to set cursor: {e}")

    def toggle_cursor(self):
        """Toggle cursor visibility"""
        self.show_cursor(not self._cursor_visible)
        print("attempting to force a click")
        StarcelHelper.ClickLMB() # force a click
        print("attempt to force a click finished")

    def print_cursor_info(self):
        """Print cursor configuration information"""
        pc = self.player_controller
        ue.log(f"ClickEventKeys = {getattr(pc, 'ClickEventKeys', None)}")
        ue.log(f"DefaultMouseCursor = {getattr(pc, 'DefaultMouseCursor', None)}")
        ue.log(f"CurrentMouseCursor = {getattr(pc, 'CurrentMouseCursor', None)}")

    def get_cursor_info(self):
        """Get cursor screen position, world position, and direction
        Returns: dict with keys: 'screen_x', 'screen_y', 'world_pos', 'world_dir'
        """
        pos_data = self.get_mouse_position(deproject=True)
        if not pos_data:
            return None

        x, y, world, direction = pos_data
        return {
            'screen_x': x,
            'screen_y': y,
            'world_pos': world,
            'world_dir': direction
        }

    # Normalize
    def normalize_input_token(self, token):
        """Normalize input token to UE format"""
        k = self.keyboard.normalize(token)
        if k:
            return k
        m = self.mouse.normalize(token)
        if m:
            return m
        return token

    def parse_chord(self, chord):
        """Parse chord string into tuple of normalized keys"""
        if isinstance(chord, str):
            parts = chord.split("+")
        else:
            parts = chord
        return tuple(self.normalize_input_token(p) for p in parts)

    # Key Registry (for future visualization)
    def _register_binding(self, keys, binding_type, callback_name=None):
        """Register a binding for future keyboard visualization"""
        key_tuple = keys if isinstance(keys, tuple) else (keys,)

        for key in key_tuple:
            if key not in self._key_registry:
                self._key_registry[key] = []

            self._key_registry[key].append({
                'type': binding_type,
                'keys': key_tuple,
                'callback': callback_name or str(callback_name)
            })

    def get_key_bindings(self, key=None):
        """Get all bindings for a specific key, or all bindings if key is None"""
        if key is None:
            return self._key_registry
        return self._key_registry.get(self.normalize_input_token(key), [])

    # Chords
    def bind_chord_event(self, chord, event_type, callback):
        """Bind a chord (key combination) to a callback"""
        primary = chord[-1]
        modifiers = set(chord[:-1])

        def _handler(method=None):
            for m in modifiers:
                if not self.uobject.is_input_key_down(m):
                    return
            callback()

        self.uobject.bind_key(primary, event_type, _handler)
        self._register_binding(chord, f"chord_{event_type}", callback.__name__ if hasattr(callback, '__name__') else None)

    def bind_sequence(self, sequence, callback, timeout=1.0):
        """Bind a sequence of key presses to a callback"""
        seq_parsed = []

        for step in sequence:
            if isinstance(step, dict) and "axis" in step:
                seq_parsed.append(("AXIS", step["axis"], id(step), step["condition"]))
            else:
                release = False
                if isinstance(step, str) and step.endswith(":release"):
                    step = step.replace(":release", "")
                    release = True

                chord = self.parse_chord(step)
                seq_parsed.append(("KEY", chord, release))

        self.sequence_bindings.append({
            "sequence": seq_parsed,
            "callback": callback,
            "timeout": timeout
        })

        self._bind_sequence_step(seq_parsed[0], seq_parsed, 0)

    def _bind_sequence_step(self, step, sequence, index):
        """Internal: bind a single step in a sequence"""
        kind = step[0]

        if kind == "AXIS":
            _, axis_name, step_id, condition_fn = step

            def _axis_callback(v=None):
                self._advance_sequence_dynamic(sequence, index)

            self.bind_axis_for_sequence(axis_name, condition_fn, _axis_callback)

        elif kind == "KEY":
            _, chord, release = step

            primary = chord[-1]
            modifiers = set(chord[:-1])
            event = ue.IE_RELEASED if release else ue.IE_PRESSED

            def _chord_callback(method=None):
                for m in modifiers:
                    if not self.uobject.is_input_key_down(m):
                        return
                self._advance_sequence_dynamic(sequence, index)

            self.uobject.bind_key(primary, event, _chord_callback)

    def _advance_sequence_dynamic(self, sequence, index_triggered):
        """Internal: advance through a sequence when a step is triggered"""
        now = time.time()

        key = tuple(
            id(step) if step[0] == "AXIS" else (tuple(step[1]), step[2])
            for step in sequence
        )

        progress = self.sequence_progress.get(key, {"index": 0, "last_time": 0})

        timeout = 1.0
        for seq in self.sequence_bindings:
            if seq["sequence"] == sequence:
                timeout = seq["timeout"]
                break

        if now - progress["last_time"] > timeout:
            progress = {"index": 0, "last_time": 0}

        expected = sequence[progress["index"]]

        if expected == sequence[index_triggered]:
            progress["index"] += 1
            progress["last_time"] = now

            if progress["index"] < len(sequence):
                self._bind_sequence_step(sequence[progress["index"]], sequence, progress["index"])
            else:
                for seq in self.sequence_bindings:
                    if seq["sequence"] == sequence:
                        seq["callback"]()
                        break

                progress = {"index": 0, "last_time": 0}

        else:
            progress = {"index": 0, "last_time": 0}

        self.sequence_progress[key] = progress

    def bind_press(self, chord, callback):
        """Bind key press event"""
        parsed_chord = self.parse_chord(chord)
        self.bind_chord_event(parsed_chord, ue.IE_PRESSED, callback)

    def bind_release(self, chord, callback):
        """Bind key release event"""
        parsed_chord = self.parse_chord(chord)
        self.bind_chord_event(parsed_chord, ue.IE_RELEASED, callback)

    def bind_double_click(self, chord, callback):
        """Bind double click event"""
        parsed_chord = self.parse_chord(chord)
        self.bind_chord_event(parsed_chord, ue.IE_DOUBLE_CLICK, callback)

    # Repeat (poll based)
    def bind_repeat(self, chord, callback):
        """Bind a key to repeat while held down (uses polling)"""
        chord = self.parse_chord(chord)

        def poll(delta):
            if self._is_shutting_down:
                return False
            if not self.uobject or not self.uobject.is_valid():
                return False

            primary = chord[-1]
            mods = chord[:-1]
            if self.uobject.is_input_key_down(primary):
                for m in mods:
                    if not self.uobject.is_input_key_down(m):
                        return True
                callback()
            return True

        ticker = ue.add_ticker(poll, self.poll_rate)
        self._repeat_bindings.append(ticker)
        self._register_binding(chord, "repeat", callback.__name__ if hasattr(callback, '__name__') else None)

    # Poll (non-binding check)
    def bind_poll(self, chord, callback, rate=None):
        """Poll a key state continuously without overriding engine bindings
        This checks key state without binding, so it won't interfere with actions like Jump
        """
        chord = self.parse_chord(chord)
        poll_rate = rate if rate is not None else self.poll_rate

        def poll(delta):
            if self._is_shutting_down:
                return False
            if not self.uobject or not self.uobject.is_valid():
                return False

            primary = chord[-1]
            mods = chord[:-1]

            # Check if all keys are down
            all_down = self.uobject.is_input_key_down(primary)
            if all_down:
                for m in mods:
                    if not self.uobject.is_input_key_down(m):
                        all_down = False
                        break

            if all_down:
                callback()

            return True

        ticker = ue.add_ticker(poll, poll_rate)
        self._pollers.append(ticker)
        self._register_binding(chord, "poll", callback.__name__ if hasattr(callback, '__name__') else None)

    def is_key_down(self, key):
        """Check if a key is currently pressed (non-binding check)"""
        normalized = self.normalize_input_token(key)
        return self.uobject.is_input_key_down(normalized)

    def is_chord_down(self, chord):
        """Check if all keys in a chord are currently pressed"""
        parsed = self.parse_chord(chord)
        for key in parsed:
            if not self.uobject.is_input_key_down(key):
                return False
        return True

    # Axis
    def bind_axis(self, axis_name, callback, deadzone=0.0, poll=True):
        """Bind an axis input to a callback
        Note: For MouseX/MouseY, use bind_axis_poll instead as bind_axis may not work reliably
        """
        axis = self.resolve_axis_name(axis_name)
        if axis is None:
            return

        def _handler(v):
            if abs(v) < deadzone:
                v = 0.0
            last = self._last_axis_values.get(axis)
            if last == v:
                return
            self._last_axis_values[axis] = v
            callback(v)

        self.uobject.bind_axis(axis, _handler)
        self._register_binding((axis,), "axis", callback.__name__ if hasattr(callback, '__name__') else None)

        if poll:
            def poller(dt):
                if self._is_shutting_down:
                    return False
                if not self.uobject or not self.uobject.is_valid():
                    return False
                v = self.uobject.get_input_axis(axis)
                _handler(v)
                return True

            ticker = ue.add_ticker(poller, self.poll_rate)
            self._pollers.append(ticker)

    def bind_axis_poll(self, axis_name, callback, deadzone=0.0, rate=None):
        """Bind an axis using only polling (more reliable for MouseX/MouseY)
        Use this for mouse movement tracking
        """
        axis = self.resolve_axis_name(axis_name)
        if axis is None:
            return
        poll_rate = rate if rate is not None else self.poll_rate

        def poller(dt):
            if self._is_shutting_down:
                return False
            if not self.uobject or not self.uobject.is_valid():
                return False

            v = self.uobject.get_input_axis(axis)

            if abs(v) < deadzone:
                v = 0.0

            last = self._last_axis_values.get(axis)
            if last != v:
                self._last_axis_values[axis] = v
                if v != 0:  # Only callback if non-zero
                    callback(v)

            return True

        ticker = ue.add_ticker(poller, poll_rate)
        self._pollers.append(ticker)
        self._register_binding((axis,), "axis_poll", callback.__name__ if hasattr(callback, '__name__') else None)

    def get_input_axis(self, axis):
        """Get current value of an axis"""
        return self.uobject.get_input_axis(axis)

    def bind_input_axis(self, axis, callback):
        """Bind an input axis directly (alternative method)"""
        self.uobject.bind_input_axis(axis, callback)

    def bind_axis_for_sequence(self, axis_name, condition_fn, callback):
        """Internal: bind axis for sequence detection"""
        axis = self.resolve_axis_name(axis_name)
        if axis is None:
            return

        def _handler(v):
            if condition_fn(v):
                callback(v)

        self.uobject.bind_axis(axis, _handler)

    # Actions
    def bind_action(self, name, pressed_cb=None, released_cb=None):
        """Bind an action defined in project input settings"""
        action = self.resolve_action_name(name)
        if action is None:
            return
        if pressed_cb:
            self.uobject.bind_action(action, ue.IE_PRESSED, pressed_cb)
        if released_cb:
            self.uobject.bind_action(action, ue.IE_RELEASED, released_cb)
        self._register_binding((action,), "action", pressed_cb.__name__ if pressed_cb and hasattr(pressed_cb, '__name__') else None)

    def is_action_pressed(self, name):
        """Check if action is currently pressed"""
        return self.uobject.is_action_pressed(name)

    def is_action_released(self, name):
        """Check if action is currently released"""
        return self.uobject.is_action_released(name)

    def get_engine_defined_action_mappings(self):
        """Get list of engine-defined action mappings"""
        return ue.get_engine_defined_action_mappings()

    # Key State
    def was_pressed(self, key):
        """Check if key was just pressed this frame"""
        return self.player_controller.WasInputKeyJustPressed(key)

    def was_released(self, key):
        """Check if key was just released this frame"""
        return self.player_controller.WasInputKeyJustReleased(key)

    # Mouse
    def get_mouse_position(self, deproject=False):
        """Get mouse position in screen coordinates
        If deproject=True, also returns world position and direction
        Returns: (x, y) or (x, y, world_pos, world_dir) if deproject=True
        """
        ok, x, y = self.player_controller.GetMousePosition()
        if not ok:
            return None

        if deproject:
            success, world, direction = self.player_controller.DeprojectScreenPositionToWorld(x, y)
            if success:
                return x, y, world, direction

        return x, y

    def set_mouse_position(self, x, y):
        """Set mouse position in screen coordinates"""
        self.player_controller.SetMouseLocation(x, y)

    def deproject_mouse(self):
        """Get world position and direction from current mouse position
        Returns: (success, world_pos, world_dir)
        """
        success, world_pos, world_dir = self.player_controller.DeprojectMousePositionToWorld()
        return success, world_pos, world_dir

    # Mouse Delta (Timer)
    def log_mouse_delta_timer(self, rate=0.05):
        """Start logging mouse delta at specified rate"""

        def tick():
            if self._is_shutting_down:
                return
            dx, dy = self.player_controller.GetInputMouseDelta()
            if dx or dy:
                ue.log(f"MouseDelta {dx:.3f}, {dy:.3f}")

        self.uobject.set_timer(rate, tick, True)
