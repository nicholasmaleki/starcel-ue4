import unreal_engine as ue

def _clean(s: str):
    return s.replace(" ", "").replace("_", "").lower()

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
                        "Ampersand", "Asterix", "Caret", "Colon", "Dollar", "Exclamation", "LeftParantheses", "RightParantheses", "Quote"  # I think Parantheses is a typo
                        ]

        self.LEGEND_TO_UE = {
            # letters
            **{chr(i): chr(i).upper() for i in range(ord('a'), ord('z') + 1)}, # TODO: Same as default_alphabet
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
            "Win": "Win",  # "LeftCommand",
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
            ["Caps", "A", "S", "D", "F", "G", "H", "J", "K", "L", ":", "\"" "Enter"],
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

    def _clean(self, t: str):
        return t.replace(" ", "").replace("_", "").lower()

    def _build_normalize_map(self):
        self.normalize_map = {}
        for k, v in self.LEGEND_TO_UE.items():
            self.normalize_map[self._clean(k)] = v
        for k in self.ue_keys:
            self.normalize_map[self._clean(k)] = k
        for k, v in self.ALIASES.items():
            self.normalize_map[self._clean(k)] = v

    def normalize(self, token):
        raw = str(token)
        if len(raw) == 1 and raw.isalpha():
            return raw.upper()
        key = self._clean(raw)
        return self.normalize_map.get(key, None)



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
                        "Ampersand", "Asterix", "Caret", "Colon", "Dollar", "Exclamation", "LeftParantheses", "RightParantheses", "Quote"  # I think Parantheses is a typo
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

    def _clean(self, t: str):
        return t.replace(" ", "").replace("_", "").lower()

    def _build_normalize_map(self):
        self.normalize_map = {}
        for k, v in self.LEGEND_TO_UE.items():
            self.normalize_map[self._clean(k)] = v
        for k in self.ue_keys:
            self.normalize_map[self._clean(k)] = k
        for k, v in self.ALIASES.items():
            self.normalize_map[self._clean(k)] = v

    def normalize(self, token):
        raw = str(token)
        key = self._clean(raw)
        return self.normalize_map.get(key, None)


class HotkeyManager:
    def __init__(self, uobject, keyboard: Keyboard, mouse: Mouse):
        self.uobject = uobject
        self.keyboard = keyboard
        self.mouse = mouse

        self.bindings = {}
        self.active_chords = set()

    # ---------------------------
    # Cursor
    # ---------------------------
    def show_cursor(self, visible=True):
        try:
            self.uobject.show_mouse_cursor(visible)
        except Exception:
            ue.log_warning("show_mouse_cursor not supported")

    def capture_mouse(self):
        self.show_cursor(False)

    def release_mouse(self):
        self.show_cursor(True)

    # ---------------------------
    # Normalize token using devices
    # ---------------------------
    def normalize_input_token(self, token):
        k = self.keyboard.normalize(token)
        if k:
            return k
        m = self.mouse.normalize(token)
        if m:
            return m
        raise ValueError(f"Unknown input token: {token}")

    # ---------------------------
    # Parse chord
    # ---------------------------
    def parse_chord(self, chord):
        if isinstance(chord, str):
            parts = chord.split("+")
        else:
            parts = chord
        return tuple(self.normalize_input_token(p) for p in parts)

    # ---------------------------
    # Conflict detection
    # ---------------------------
    def detect_conflict(self, chord):
        return chord in self.bindings

    # ---------------------------
    # Modifier polling
    # ---------------------------
    def _modifiers_active(self, modifiers):
        for m in modifiers:
            if not self.uobject.is_input_key_down(m):
                return False
        return True

    # ---------------------------
    # Generic chord event
    # ---------------------------
    def bind_chord_event(self, chord, event_type, callback, override=False):
        ue_chord = self.parse_chord(chord)
        if self.detect_conflict(ue_chord) and not override:
            raise RuntimeError(f"Hotkey conflict: {ue_chord}")

        if ue_chord not in self.bindings:
            self.bindings[ue_chord] = {}
        self.bindings[ue_chord][event_type] = callback

        primary = ue_chord[-1]
        modifiers = set(ue_chord[:-1])

        def _handler(method=None):
            if not self._modifiers_active(modifiers):
                return
            if event_type == ue.IE_PRESSED:
                if ue_chord in self.active_chords:
                    return
                self.active_chords.add(ue_chord)
            if event_type == ue.IE_RELEASED:
                if ue_chord not in self.active_chords:
                    return
                self.active_chords.remove(ue_chord)
            callback()

        self.uobject.bind_key(primary, event_type, _handler)

    # ---------------------------
    # Wrappers
    # ---------------------------
    def bind_press(self, chord, callback, override=False):
        self.bind_chord_event(chord, ue.IE_PRESSED, callback, override)

    def bind_release(self, chord, callback, override=False):
        self.bind_chord_event(chord, ue.IE_RELEASED, callback, override)

    def bind_repeat(self, chord, callback, override=False):
        self.bind_chord_event(chord, ue.IE_REPEAT, callback, override)

    def bind_double_click(self, chord, callback, override=False):
        self.bind_chord_event(chord, ue.IE_DOUBLE_CLICK, callback, override)

    # ---------------------------
    # Axis binding with math / filters
    # ---------------------------
    def bind_axis(self, axis_name, callback,
                  scale=1.0,
                  deadzone=0.0,
                  min_value=None,
                  max_value=None,
                  abs_value=False,
                  condition=None):
        ue_axis = self.normalize_input_token(axis_name)

        def _axis_handler(value):
            v = value
            if abs(v) < deadzone:
                return
            if abs_value:
                v = abs(v)
            v *= scale
            if min_value is not None and v < min_value:
                return
            if max_value is not None and v > max_value:
                return
            if condition and not condition(v):
                return
            callback(v)

        self.uobject.bind_axis(ue_axis, _axis_handler)