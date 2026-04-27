import unreal_engine as ue
from unreal_engine.enums import EMouseCursor, ECollisionChannel
from unreal_engine.classes import StarcelHelper, InputSettings
import time


def _clean(s: str):
    return s.replace(" ", "").replace("_", "").lower()


def _load_project_input_names():
    """Read axis/action mapping names from Project Settings > Input.
    Returns (axis_map, action_map): lowercase token -> canonical name.

    Tries GetAxisNames/GetActionNames first, then falls back to iterating
    the AxisMappings/ActionMappings UPROPERTY arrays. UnrealEnginePython's
    binding for the output-param Get*Names variants can return empty on UE 4.27.
    """
    axis_map, action_map = {}, {}
    try:
        settings = ue.get_mutable_default(InputSettings)
    except Exception as e:
        ue.log_warning(f'input_devices: could not read project input settings: {e}')
        return axis_map, action_map

    def _add(m, name):
        if name:
            m[_clean(name)] = name

    # Preferred: GetAxisNames / GetActionNames (may be empty on 4.27).
    try:
        for n in (settings.GetAxisNames() or []):
            _add(axis_map, str(n))
    except Exception:
        pass
    try:
        for n in (settings.GetActionNames() or []):
            _add(action_map, str(n))
    except Exception:
        pass

    # Fallback: iterate mapping arrays directly.
    if not axis_map:
        try:
            for m in (settings.AxisMappings or []):
                _add(axis_map, str(getattr(m, 'AxisName', '') or ''))
        except Exception:
            pass
    if not action_map:
        try:
            for m in (settings.ActionMappings or []):
                _add(action_map, str(getattr(m, 'ActionName', '') or ''))
        except Exception:
            pass

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
        self.poll_rate = poll_rate
        self._repeat_bindings = []
        self._pollers = []
        self._key_registry = {}  # For future keyboard visualization
        self._is_shutting_down = False

        self._axis_names, self._action_names = _load_project_input_names()

        self.player_controller = self.uobject.get_player_controller()

        # Seed from PC so toggle_cursor() doesn't no-op on first call when
        # bShowMouseCursor is False but our flag would default to True.
        try:
            self._cursor_visible = bool(self.player_controller.bShowMouseCursor)
        except Exception:
            self._cursor_visible = False

    def resolve_axis_name(self, token):
        """Return the canonical axis name for *token*.

        Always returns the token (or its canonical-case form) so that
        UE's own bind_axis can resolve it — unknown tokens are silently
        ignored by UE, matching the pre-validation behavior. The local
        _axis_names table is only used for case-normalization; on UE 4.27
        the InputSettings reflection is unreliable, so a missing entry
        is not treated as an error."""
        if not token:
            return None
        if self._axis_names:
            canonical = self._axis_names.get(_clean(token))
            if canonical is not None:
                return canonical
        return token

    def resolve_action_name(self, token):
        """Return the canonical action name for *token*. Same fallback
        behavior as resolve_axis_name."""
        if not token:
            return None
        if self._action_names:
            canonical = self._action_names.get(_clean(token))
            if canonical is not None:
                return canonical
            ue.log_warning(
                f"bind_action: '{token}' is not a defined action mapping. "
                f"Check Project Settings > Input > Action Mappings.")
        return token

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
        vw, vh = ue.get_viewport_size()
        self.set_mouse_position(vw / 2, vh / 2)
        def _delayed_click(delta):
            StarcelHelper.ClickLMB()
            ue.log("LMB click fired")
            return False

        # UEP GCs the ticker if no reference is held — see unreal_engine_tools.py:584
        # ('assignment required or gc will destroy'). Store on self to keep alive.
        if not hasattr(self, '_click_tickers'):
            self._click_tickers = []
        self._click_tickers.append(ue.add_ticker(_delayed_click, 0.02))

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


# Binding doc generator
#
# rebuild_generated_modules() in unreal_engine_tools.py invokes this to write
# a Markdown index of every input binding in the codebase. The output file is
# chmod'd read-only so a stale hand-edit can't drift from the source.

_NATIVE_KEY_EVENT = {"bind_key", "bind_chord_event"}
_HM_KEY_EVENT = {"bind_press", "bind_release", "bind_double_click",
                 "bind_repeat", "bind_poll"}
_BIND_AXIS = {"bind_axis", "bind_axis_poll", "bind_input_axis"}
_BIND_ACTION = {"bind_action"}
_BIND_SEQUENCE = {"bind_sequence"}
_KEY_CHECK = {"is_input_key_down", "is_key_down", "is_chord_down",
              "was_pressed", "was_released",
              "WasInputKeyJustPressed", "WasInputKeyJustReleased"}
_ALL_BIND_NAMES = (_NATIVE_KEY_EVENT | _HM_KEY_EVENT | _BIND_AXIS
                   | _BIND_ACTION | _BIND_SEQUENCE | _KEY_CHECK)

_MOUSE_TOKENS = {
    "leftmousebutton", "rightmousebutton", "middlemousebutton",
    "thumbmousebutton", "thumbmousebutton2",
    "mousex", "mousey", "mouse2d",
    "mousescrollup", "mousescrolldown", "mousewheelaxis",
}

_SCAN_SKIP_DIRS = {"__pycache__", "unreal_engine"}
_SCAN_SKIP_FILES = {"input_devices.py", "gen_cli.py"}


def _is_mouse_token(token):
    if not token:
        return False
    for piece in str(token).split("+"):
        if _clean(piece) in _MOUSE_TOKENS:
            return True
    return False


def _ast_literal_key(node):
    """Return the literal string from a key/chord/axis arg, or None for dynamic."""
    import ast
    if isinstance(node, ast.Constant) and isinstance(node.value, str):
        return node.value
    if isinstance(node, ast.List):
        parts = []
        for el in node.elts:
            if isinstance(el, ast.Constant) and isinstance(el.value, str):
                parts.append(el.value)
            else:
                parts.append("<dynamic>")
        return " -> ".join(parts) if parts else None
    return None


def _ast_unparse(node):
    import ast
    try:
        return ast.unparse(node).strip()
    except Exception:
        return f"<{type(node).__name__}>"


def _ast_extract_call(method, args, keywords):
    """Return (key_node, callback_node) for a binding call."""
    if not args:
        return None, None
    key_node = args[0]
    cb = None
    if method in _NATIVE_KEY_EVENT:
        # bind_key(key, event, callback) / bind_chord_event(chord, event, callback)
        if len(args) > 2:
            cb = args[2]
    elif method in _BIND_ACTION:
        if len(args) >= 3:
            # native: bind_action(name, event, callback)
            cb = args[2]
        else:
            # HotkeyManager: bind_action(name, pressed_cb=, released_cb=)
            for kw in keywords:
                if kw.arg in ("pressed_cb", "released_cb", "callback"):
                    cb = kw.value
                    break
    elif method in (_HM_KEY_EVENT | _BIND_AXIS | _BIND_SEQUENCE):
        if len(args) > 1:
            cb = args[1]
        else:
            for kw in keywords:
                if kw.arg in ("callback", "cb"):
                    cb = kw.value
                    break
    return key_node, cb


def _ast_find_purpose(tree, callback_node):
    """Find a one-line purpose string for *callback_node* by looking up its
    function definition in *tree* and returning its first docstring line."""
    import ast
    if callback_node is None:
        return ""
    if isinstance(callback_node, ast.Lambda):
        body = _ast_unparse(callback_node.body)
        return f"lambda: {body}" if body else "lambda"
    name = None
    if isinstance(callback_node, ast.Attribute):
        name = callback_node.attr
    elif isinstance(callback_node, ast.Name):
        name = callback_node.id
    if not name:
        return ""
    for n in ast.walk(tree):
        if isinstance(n, (ast.FunctionDef, ast.AsyncFunctionDef)) and n.name == name:
            doc = ast.get_docstring(n)
            if doc:
                return doc.splitlines()[0].strip()
            return ""
    return ""


def _md_cell(s):
    if s is None:
        s = ""
    s = s.replace("|", r"\|").replace("\n", " ").strip()
    return s or "—"


def generate_input_bindings_doc(scripts_dir=None, output_path=None):
    """Scan the Scripts tree for input bindings and write a read-only Markdown index.

    Walks every .py file under *scripts_dir* (skipping __pycache__,
    unreal_engine/ stubs, and the binding-defining files themselves) and
    collects each call to:

        Native UE   : bind_key, bind_axis, bind_action, bind_input_axis,
                      is_input_key_down, WasInputKeyJustPressed,
                      WasInputKeyJustReleased
        HotkeyManager: bind_press, bind_release, bind_double_click,
                       bind_repeat, bind_poll, bind_chord_event,
                       bind_sequence, bind_axis, bind_axis_poll,
                       bind_action, is_key_down, is_chord_down,
                       was_pressed, was_released

    Each call site contributes a row recording the key/chord/axis/action,
    the bound callback, the callback's first docstring line if available,
    and the file:line. The output is chmod'd read-only so a hand-edit
    can't drift from source — regenerate via rebuild_generated_modules().
    """
    import ast
    import os
    import stat
    from datetime import datetime, timezone

    if scripts_dir is None:
        scripts_dir = os.path.join(os.path.abspath(ue.get_content_dir()), "Scripts")
    if output_path is None:
        output_path = os.path.join(scripts_dir, "input_bindings.md")

    files_scanned = 0
    parse_errors = []
    bind_rows = []
    check_rows = []

    for root, dirs, files in os.walk(scripts_dir):
        dirs[:] = [d for d in dirs if d not in _SCAN_SKIP_DIRS]
        for fname in files:
            if not fname.endswith(".py"):
                continue
            if fname in _SCAN_SKIP_FILES:
                continue
            full = os.path.join(root, fname)
            try:
                with open(full, "r", encoding="utf-8") as f:
                    src = f.read()
            except Exception as e:
                parse_errors.append((full, str(e)))
                continue
            try:
                tree = ast.parse(src, filename=full)
            except SyntaxError as e:
                parse_errors.append((full, f"SyntaxError: {e}"))
                continue
            files_scanned += 1

            rel = os.path.relpath(full, scripts_dir).replace("\\", "/")

            for node in ast.walk(tree):
                if not isinstance(node, ast.Call):
                    continue
                method = None
                if isinstance(node.func, ast.Attribute):
                    method = node.func.attr
                elif isinstance(node.func, ast.Name):
                    method = node.func.id
                if method not in _ALL_BIND_NAMES:
                    continue

                key_node, cb_node = _ast_extract_call(method, node.args, node.keywords)
                key_str = _ast_literal_key(key_node) if key_node is not None else None
                if key_str is None:
                    # Non-literal key: render the source expression with an
                    # <expr> marker so it's clearly distinguishable from a
                    # literal key in the output.
                    if key_node is None:
                        key_str = "<no-arg>"
                    else:
                        key_str = f"<expr: {_ast_unparse(key_node)}>"
                callback = _ast_unparse(cb_node) if cb_node is not None else "—"
                purpose = _ast_find_purpose(tree, cb_node)

                if method in _BIND_AXIS:
                    category = "axis"
                elif method in _BIND_ACTION:
                    category = "action"
                elif method in _BIND_SEQUENCE:
                    category = "sequence"
                elif method in _KEY_CHECK:
                    category = "check"
                else:
                    category = "mouse" if _is_mouse_token(key_str) else "key"

                row = {
                    "key": key_str,
                    "method": method,
                    "callback": callback,
                    "purpose": purpose,
                    "location": f"{rel}:{node.lineno}",
                    "category": category,
                }
                if category == "check":
                    check_rows.append(row)
                else:
                    bind_rows.append(row)

    bind_rows.sort(key=lambda r: (r["category"], r["key"].lower(), r["location"]))
    check_rows.sort(key=lambda r: (r["key"].lower(), r["location"]))

    generated_at = datetime.now(timezone.utc).isoformat(timespec="seconds")

    section_titles = [
        ("key",      "Keyboard / Chord Bindings"),
        ("mouse",    "Mouse Bindings"),
        ("axis",     "Axis Bindings"),
        ("action",   "Action Bindings"),
        ("sequence", "Sequence Bindings"),
    ]

    lines = []
    lines.append("# Input Bindings (auto-generated)")
    lines.append("")
    lines.append(f"_Generated at {generated_at}_")
    lines.append("")
    lines.append("This file is regenerated by `input_devices.generate_input_bindings_doc()` "
                 "from `unreal_engine_tools.rebuild_generated_modules()`. "
                 "**Do not edit by hand** — the file is set read-only and any local edits "
                 "will be overwritten on the next rebuild.")
    lines.append("")
    lines.append(f"- Files scanned: **{files_scanned}**")
    lines.append(f"- Bindings found: **{len(bind_rows)}**")
    lines.append(f"- State checks found: **{len(check_rows)}**")
    lines.append("")

    for cat_id, cat_title in section_titles:
        rows = [r for r in bind_rows if r["category"] == cat_id]
        if not rows:
            continue
        first_col = "Name" if cat_id in ("axis", "action", "sequence") else "Key / Chord"
        lines.append(f"## {cat_title}")
        lines.append("")
        lines.append(f"| {first_col} | Method | Callback | Purpose | Location |")
        lines.append("| --- | --- | --- | --- | --- |")
        for r in rows:
            lines.append(
                f"| `{_md_cell(r['key'])}` "
                f"| `{_md_cell(r['method'])}` "
                f"| `{_md_cell(r['callback'])}` "
                f"| {_md_cell(r['purpose'])} "
                f"| {_md_cell(r['location'])} |"
            )
        lines.append("")

    if check_rows:
        lines.append("## Key State Checks (non-binding)")
        lines.append("")
        lines.append("Read-only queries — these check whether a key is currently down or was "
                     "just pressed/released, but don't bind a callback.")
        lines.append("")
        lines.append("| Key | Method | Location |")
        lines.append("| --- | --- | --- |")
        for r in check_rows:
            lines.append(
                f"| `{_md_cell(r['key'])}` "
                f"| `{_md_cell(r['method'])}` "
                f"| {_md_cell(r['location'])} |"
            )
        lines.append("")

    if parse_errors:
        lines.append("## Files Skipped Due to Parse Errors")
        lines.append("")
        for path, err in parse_errors:
            lines.append(f"- `{os.path.basename(path)}`: {err}")
        lines.append("")

    content = "\n".join(lines)

    # Clear read-only bit if the file already exists, write fresh content,
    # then re-apply read-only. Windows honors only S_IWRITE/S_IREAD.
    if os.path.exists(output_path):
        try:
            os.chmod(output_path, stat.S_IWRITE | stat.S_IREAD)
        except OSError:
            pass
    with open(output_path, "w", encoding="utf-8") as f:
        f.write(content)
    try:
        os.chmod(output_path, stat.S_IREAD)
    except OSError:
        pass

    print(f"Generated {output_path} "
          f"({files_scanned} files scanned, "
          f"{len(bind_rows)} bindings, {len(check_rows)} checks)")
    return output_path
