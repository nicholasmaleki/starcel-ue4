import pickle

class LargeStringAsyncStandalone:
    """
    Python helper for ULargeStringAsync without an actor.
    Handles:
    - Chunked sending and receiving
    - Async reassembly
    - Callback when full string is received
    """

    def __init__(self, large_string_obj, send_chunk_callback, on_received_callback=None):
        """
        :param large_string_obj: ULargeStringAsync instance
        :param send_chunk_callback: Python callable to send a chunk
                                    Signature: func(chunk: TArray[uint8], index: int, total_chunks: int)
        :param on_received_callback: Python callable when full string is received
        """
        self.large_string = large_string_obj
        self.send_chunk_callback = send_chunk_callback
        self.on_received_callback = on_received_callback
        self.received_chunks = []

        # Bind to C++ async event
        self.large_string.OnFullyReceived.add_callable(self._on_fully_received)

    def _on_fully_received(self):
        """Called when full string is reassembled in C++"""
        if self.on_received_callback:
            self.on_received_callback(self.large_string.ToString())

    def send_string(self):
        """Send all chunks using the provided callback"""
        total_chunks = self.large_string.GetChunkCount()
        for i in range(total_chunks):
            chunk = self.large_string.GetChunk(i)
            self.send_chunk_callback(chunk, i, total_chunks)

    def receive_chunk(self, chunk, index, total_chunks):
        """Receive a chunk from remote source"""
        if len(self.received_chunks) < total_chunks:
            self.received_chunks.extend([None] * (total_chunks - len(self.received_chunks)))
        self.received_chunks[index] = chunk

        # Forward chunk to C++ async object
        self.large_string.ReceiveChunk(chunk, index, total_chunks)


class Constants:
    def __init__(self):
        self.default_alphabet = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r",
                                 "s", "t", "u", "v", "w", "x", "y", "z"]
        self.default_alphabet_capital = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q",
                                         "R", "S", "T", "U", "V", "W", "X", "Y", "Z"]
        self.default_metric_prefixes = [
            ["quetta", "ronna", "yotta", "zetta", "exa", "peta", "tera", "giga", "mega", "kilo", "hecto", "deka", None, "deci", "centi", "milli", "micro", "nano", "pico", "femto", "atto", "zepto",
             "yocto", "ronto", "quecto"],
            ["Q", "R", "Y", "Z", "E", "P", "T", "G", "M", "k", "h", "da", None, "d", "c", "m", "μ", "n", "p", "f", "a", "z", "y", "r", "q"],
            ["10^30", "10^27", "10^24", "10^21", "10^18", "10^15", "10^12", "10^9", "10^6", "10^3", "10^2", "10^1", "10^0", "10^(-1)", "10^(-2)", "10^(-3)", "10^(-6)", "10^(-9)", "10^(-12)",
             "10^(-15)", "10^(-18)", "10^(-21)", "10^(-24)", "10^(-27)", "10^(-30)"],
            ["E+30", "E+27", "E+24", "E+21", "E+18", "E+15", "E+12", "E+9", "E+6", "E+3", "E+2", "E+1", "E0", "E-1", "E-2", "E-3", "E-6", "E-9", "E-12", "E-15", "E-18", "E-21", "E-24", "E-27",
             "E-30"],
            ["nonillion", "octillion", "septillion", "sextillion", "quintillion", "quadrillion", "trillion", "billion", "million", "thousand", "hundred", "ten", "one", "tenth", "hundredth",
             "thousandth", "millionth", "billionth", "trillionth", "quadrillionth", "quintillionth", "sextillionth", "septillionth", "octillionth", "nonillionth"]
        ]

        self.utf8_common_symbols = ["+", "−", "±", "∓", "×", "÷", "·", "∙", "/", "^", "%", "‰", "°",
                                    "=", "≠", "≡", "≈", "≃", "≅", "∼", "∝", "<", ">", "≤", "≥", "≦", "≧", "≨", "≩", "≪", "≫",
                                    "∞", "√", "∛", "∜", "∘", "⊙", "⊕", "⊖", "⊗", "⊘", "⨀", "⨁", "⨂",
                                    "⌊", "⌋", "⌈", "⌉", "⟨", "⟩", "|", "∥", "⊥", "≜",

                                    "∑", "∏", "∐", "∫", "∬", "∭", "∮", "∯", "∰", "∂", "∇", "∆", "δ",
                                    "ℓ", "ℱ", "ℒ", "ℰ",

                                    "→", "←", "↑", "↓", "↔", "⇔", "⇒", "⇐", "↦", "↣", "⇵", "⤼", "⤽", "♆",

                                    "∀", "∃", "∄", "∈", "∉", "∋", "∌", "∅", "∁", "∖",
                                    "∩", "∪", "⊆", "⊂", "⊄", "⊊", "⊇", "⊃", "⊅", "⊋", "⊖",
                                    "ℕ", "ℤ", "ℚ", "ℝ", "ℂ", "ℵ", "ℶ", "ℷ", "ℸ", "𝓟",

                                    "¬", "∨", "∧", "⊕", "⊢", "⊣", "⊨", "⫤", "⊤", "⊥", "∴", "∵",

                                    "∠", "∟", "△", "⌒", "∥", "⟂", "⫛",

                                    "⊲", "⊳", "⋀", "⋁", "⋂", "⋃", "⨋", "⨌", "⨘", "⨛",

                                    "@",

                                    "α", "β", "γ", "δ", "ε", "ϵ", "ζ", "η", "θ", "ϑ", "ι", "κ", "λ", "μ", "ν", "ξ", "ο", "π",
                                    "ρ", "σ", "τ", "υ", "φ", "ϕ", "χ", "ψ", "ω",
                                    "Α", "Β", "Γ", "Δ", "Ε", "Ζ", "Η", "Θ", "Ι", "Κ", "Λ", "Μ", "Ν", "Ξ", "Ο", "Π", "Ρ", "Σ",
                                    "Τ", "Υ", "Φ", "Χ", "Ψ", "Ω",

                                    "𝛢", "𝛼", "𝛣", "𝛽", "𝛤", "𝛾", "𝛥", "𝛿", "𝛦", "𝜀", "𝜖", "𝛧", "𝜁", "𝛨", "𝜂",
                                    "𝛩", "𝜃", "𝜗", "𝛪", "𝜄", "𝛫", "𝜅", "𝛬", "𝜆", "𝛭", "𝜇",
                                    "𝛮", "𝜈", "𝛯", "𝜉", "𝛰", "𝜊", "𝛱", "𝜋", "𝛲", "𝜌",
                                    "𝛴", "𝜎", "𝛵", "𝜏", "𝛶", "𝜐", "𝛷", "𝜙", "𝜑",
                                    "𝛸", "𝜒", "𝛹", "𝜓", "𝛺", "𝜔",

                                    "𝒜", "ℬ", "𝒞", "𝒟", "ℰ", "ℱ", "𝒢", "ℋ", "ℐ", "𝒥", "𝒦", "ℒ", "ℳ", "𝒩", "𝒪", "𝒫", "𝒬", "ℛ",
                                    "𝒮", "𝒯", "𝒰", "𝒱", "𝒲", "𝒳", "𝒴", "𝒵",

                                    "𝔸", "𝔹", "ℂ", "𝔻", "𝔼", "𝔽", "𝔾", "ℍ", "𝕀", "𝕁", "𝕂", "𝕃", "𝕄", "ℕ", "𝕆", "ℙ", "ℚ", "ℝ",
                                    "𝕊", "𝕋", "𝕌", "𝕍", "𝕎", "𝕏", "𝕐", "ℤ",

                                    "𝖕", "𝖖", "𝖗"]

        file_path = "quotes.pkl"
        self.quotes = None
        try:
            with open(file_path, 'rb') as file:
                loaded_quotes_hex = pickle.load(file)
                self.quotes = [bytes.fromhex(h).decode('utf-8') for h in loaded_quotes_hex]
            print("Successfully unpickled quotes")
        except:
            print("Failed to unpickle quotes")


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


class WorldSize():
    def __init__(self):  # most large world sizes require origin rebasing
        # all in meters
        self.ue4_world_max = 20971  # disable World Bounds Checks to exceed, change UE_USE_UE4_WORLD_MAX located in the EngineDefines.h, then recompile the engine. WORLD_MAX is the constant that is set to 2097152.0 Unreal Units(UU/cm)
        self.MAX = 16655451  # using 1024 4033x4033 tiles: https://youtu.be/uesmtsQZ3lI?si=wkfQtAVbnlrK-1i-&t=386
        self.editor_precision = .001
        self.ue4_precision = .0000001  # check IEEE754 for more info. ~7 sig figs
        self.ue5_precision = .000000000000001  # ~15-16 sig figs
        # self.ue4_world_max = 88000000000 # bEnableLargeWorlds = true, UE_USE_UE4_WORLD_MAX=0. Although, this reports larger: https://old.reddit.com/r/unrealengine/comments/1axhmhm/is_the_88_million_km_max_world_size_total_area_or/kro5la5/

        # all in meters
        self.observable_universe = 8.8*10 ^ 26
        self.milky_way_galaxy = 9 * 10 ^ 20
        self.solar_system = 3 * 10 ^ 13
        self.au = 1.496*10^11
        self.earth_size = 12756000  # includes bulge at the equator. Notice that it fits into the tiled ue4 world
        self.usa = 4500000
        self.usa_state = 800000
        self.usa_city = 30000
        self.office_building = 50
        self.home = 15
        self.human = 1.7
        self.hand = .2

        self.large_manmade_radiowave_wavelength = 100000000
        self.max_visible_wavelength = 7.8 * 10 ^ (-7)
        self.min_visible_wavelength = 3.8 * 10 ^ (-7)
        self.euv_wavelength = 10 ^ (-8)
        self.smallest_observed_wavelength = 10 ^ (-23)  # smallest wavelength gamma ray
        self.planck_length = 1.616 * 10 ^ (-35)

        # diameters in nm
        self.good_particle_physics__size = 0.000005
        self.electron = 0.000000002
        self.electron_compton_wavelength = 0.00242
        self.electron_smallest_bound = 0.00000000000002
        self.neutron = 0.00000168
        self.neutron_compton_wavelength = 0.00000132
        self.proton = 0.00000168
        self.proton_compton_wavelength = 0.00000132
        self.hydrogen_atom = 0.074
        self.hydrogen_nucleus = 0.00000175
        self.uranium_atom = 0.196
        self.uranium_nucleus = 0.0000117
        self.nist_siliconkg = 93600000

        # in kg
        self.electron_weight = 9.1093837 * 10 ^ (-31)
        self.photon_am_weight = 9.52 * 10 ^ (-50)  # AM Radio. Using Planck's constant.
        # 2.09024042 × 10^(-28)nm particle width by idiot math using electrons weight and size, 2 orders of magnitude difference between this and planck length
        self.photon_visible_weight = 4.42 * 10 ^ (-36)  # 9.70468767*10^(-15)nm by idiot math
        self.photon_gamma_weight = 2.21 * 10 ^ (-19)  # 485.234384nm by idiot math

class FiniteRepetitionSelector():
    # +1
    # 1     2     3     4     5     6
    # +2
    # 0     2     4     6     8     10     12
    #
    # *2
    # 2 + 2     4 + 4     8 + 8     16 + 16    32 + 32
    #
    # ^ 2
    # 2 * 2     4 * 4     16 * 16     256 * 256
    #
    # ↑2
    # 2 ^ 2 = 4     4 ^ 4     256 ^ 256
    #
    # ↑↑2
    # 2↑2 = 4     4↑4 = 4 ^ 4 ^ 4 ^ 4
    #
    # 2↑↑2 = 2↑2 = 4
    #
    # 2↑↑↑↑2 = 2↑↑↑2 = 2↑↑2
    #
    # auto(negate/direction)?
    # auto(negate/direction) threshold: 1
    def __init__(self, current_operator = "+", current_operand = 2):
        self.operators = ["C/S", "+", "*", "^", "↑", "↑↑"] # Counting/Successor
        self.current_operator = current_operator
        self.current_operand = current_operand
        self.autonegate_threshold = 0.0
        self.autonegate = False

    def autonegate_value(self, value):
        if self.autonegate:
            if self.autonegate_threshold > value > -1 * self.autonegate_threshold:
                return -1 * value
        return value

    def basic_tetration(self, a, b):
        # a is the first input value and b is the second input value
        total = a
        for i in range(1, round(b)):
            total = a ^ total
        return total

    def decrease_value(self, value):
        value = self.autonegate_value(value)
        if self.current_operator == self.operators[1]:
            return value - self.current_operand
        if self.current_operator == self.operators[2]:
            return value / self.current_operand
        if self.current_operator == self.operators[3]:
            return pow(value, (1 / self.current_operand))
        if self.current_operator == self.operators[4]:
            return self.basic_tetration(value,self.current_operand)
        return value

    def increase_value(self, value):
        value = self.autonegate_value(value)
        if self.current_operator == self.operators[1]:
            return value + self.current_operand
        if self.current_operator == self.operators[2]:
            return value * self.current_operand
        if self.current_operator == self.operators[3]:
            return pow(value, self.current_operand)
        return value

class SpatialDimensionSelector():
    def __init__(self):
        Line2 = [[-1.000000, 0.000000, 0.000000], [1.000000, 0.000000, 0.000000]]
        Plane4 = [[0.000000, 1.000000, 0.000000], [1.000000, 0.000000, 0.000000], [0.000000, -1.000000, 0.000000],
                  [-1.000000, 0.000000, 0.000000]]
        Optimal6 = [[1.000000, 0.000000, 0.000000], [-1.000000, 0.000000, 0.000000], [0.000000, 1.000000, 0.000000],
                    [0.000000, -1.000000, 0.000000], [0.000000, 0.000000, 1.000000], [0.000000, 0.000000, -1.000000]]
        Optimal4 = [[0.577350, 0.577350, 0.577350], [-0.577350, -0.577350, 0.577350], [-0.577350, 0.577350, -0.577350],
                    [0.577350, -0.577350, -0.577350]]
        Wolfram5 = [[-1.000000, 0.000000, 0.000000], [1.000000, 0.000000, 0.000000], [0.000000, -0.866025, -0.500000],
                    [0.000000, 0.866025, -0.500000], [0.000000, 0.000000, 1.000000]]
        Optimal6_0 = [[1.000000, 0.000000, 0.000000], [-1.000000, 0.000000, 0.000000], [0.000000, 1.000000, 0.000000],
                      [0.000000, -1.000000, 0.000000], [0.000000, 0.000000, 1.000000], [0.000000, 0.000000, -1.000000]]
        Wolfram7 = [[0.000000, 0.000000, -1.000000], [0.000000, 0.000000, 1.000000], [1.000000, 0.000000, 0.000000],
                    [0.309017, -0.951057, 0.000000], [0.309017, 0.951057, 0.000000], [-0.809017, -0.587785, 0.000000],
                    [-0.809017, 0.587785, 0.000000]]
        Optimal8 = [[0.859533, 0.000000, 0.511081], [-0.859533, 0.000000, 0.511081], [0.000000, 0.859533, 0.511081],
                    [0.000000, -0.859533, 0.511081], [0.607781, 0.607781, -0.511081], [0.607781, -0.607781, -0.511081],
                    [-0.607781, 0.607781, -0.511081], [-0.607781, -0.607781, -0.511081]]
        Cube8 = [[0.577350, 0.577350, 0.577350], [-0.577350, 0.577350, 0.577350], [0.577350, -0.577350, 0.577350],
                 [-0.577350, -0.577350, 0.577350], [0.577350, 0.577350, -0.577350], [-0.577350, 0.577350, -0.577350],
                 [0.577350, -0.577350, -0.577350], [-0.577350, -0.577350, -0.577350]]
        Wolfram9 = [[-0.37796447300922725, -0.6546536707079771, -0.6546536707079771],
                    [-0.37796447300922725, -0.6546536707079771, 0.6546536707079771],
                    [-0.37796447300922725, 0.6546536707079771, -0.6546536707079771],
                    [-0.37796447300922725, 0.6546536707079771, 0.6546536707079771],
                    [0.7559289460184545, 0., -0.6546536707079771], [0.7559289460184545, 0., 0.6546536707079771],
                    [-1., 0., 0.], [0.5, -0.8660254037844386, 0.], [0.5, 0.8660254037844386, 0.]]
        Wolfram10 = [[-0.8944271909999157, 0., -0.44721359549995787], [0.8944271909999157, 0., 0.44721359549995787],
                     [-0.7236067977499789, -0.5257311121191336, 0.44721359549995787],
                     [-0.7236067977499789, 0.5257311121191336, 0.44721359549995787],
                     [-0.276393202250021, -0.85065080835204, -0.44721359549995787],
                     [-0.276393202250021, 0.85065080835204, -0.44721359549995787],
                     [0.276393202250021, -0.85065080835204, 0.44721359549995787],
                     [0.276393202250021, 0.85065080835204, 0.44721359549995787],
                     [0.7236067977499789, -0.5257311121191336, -0.44721359549995787],
                     [0.7236067977499789, 0.5257311121191336, -0.44721359549995787]]
        Wolfram11 = [[0., 0., 1.], [-0.8944271909999157, 0., -0.44721359549995787],
                     [0.8944271909999157, 0., 0.44721359549995787],
                     [-0.276393202250021, -0.85065080835204, -0.44721359549995787],
                     [-0.276393202250021, 0.85065080835204, -0.44721359549995787],
                     [0.276393202250021, -0.85065080835204, 0.44721359549995787],
                     [0.276393202250021, 0.85065080835204, 0.44721359549995787],
                     [-0.7236067977499789, -0.5257311121191336, 0.44721359549995787],
                     [-0.7236067977499789, 0.5257311121191336, 0.44721359549995787],
                     [0.7236067977499789, -0.5257311121191336, -0.44721359549995787],
                     [0.7236067977499789, 0.5257311121191336, -0.44721359549995787]]
        Optimal12 = [[0.850651, 0.000000, -0.525731], [0.525731, -0.850651, 0.000000], [0.000000, -0.525731, 0.850651],
                     [0.850651, 0.000000, 0.525731], [-0.525731, -0.850651, 0.000000], [0.000000, 0.525731, -0.850651],
                     [-0.850651, 0.000000, -0.525731], [-0.525731, 0.850651, 0.000000], [0.000000, 0.525731, 0.850651],
                     [-0.850651, 0.000000, 0.525731], [0.525731, 0.850651, 0.000000], [0.000000, -0.525731, -0.850651]]


class Keyboards:
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

    # def build_ue_lookup(self, keyboard_layout):
    #     lookup = {}
    #     lookup_ue = {}
    #     for row in keyboard_layout:
    #         for key in row:
    #             if not key:
    #                 continue
    #             ue_key = self.LEGEND_TO_UE.get(key)
    #             if ue_key:
    #                 lookup[key] = ue_key
    #                 lookup_ue[ue_key] = key
    #     return lookup, lookup_ue
    #
    # def key_to_ue_key(self, key: str,keyboard,keyboard_shifted=None,shifted=False):
    #     layout = keyboard_shifted if shifted and keyboard_shifted else keyboard
    #     lookup, lookup_ue = self.build_ue_lookup(layout)
    #
    # label = self.key_to_ue_label(
    #     ue_key="LeftShift",
    #     keyboard=self.keyboard_ANSI,
    #     keyboard_shifted=self.keyboard_ANSI_shift,
    #     shifted=False
    # )
    # print(label)

# class Cylinder():
#     def __init__(self, line_start, line_end, line_thickness, reparent_to):
#         self.line_start = np.array(line_start)
#         self.line_end = np.array(line_end)
#         self.line_thickness = line_thickness
#         self.line_midpoint = (np.array(line_start) + np.array(line_end)) / 2.0
#         self.model = loader.loadModel("models/Cylinder.bam")
#         self.model.reparent_to(reparent_to)
#         euler_angles = look_at_rotation(self.line_midpoint, self.line_end)
#         euler_angles = [x + 180 for x in euler_angles]
#         self.model.setPosHprScale(self.line_midpoint[0], self.line_midpoint[1], self.line_midpoint[2], euler_angles[2]+90, euler_angles[1]+270, euler_angles[0], line_thickness, line_thickness, float(np.sqrt((self.line_end - self.line_start).dot((self.line_end - self.line_start))))/2)
#
#     def update(self, line_start, line_end, line_thickness):
#         self.line_start = np.array(line_start)
#         self.line_end = np.array(line_end)
#         self.line_thickness = line_thickness
#         self.line_midpoint = (np.array(line_start) + np.array(line_end)) / 2.0
#         euler_angles = look_at_rotation(self.line_midpoint, self.line_end)
#         euler_angles = [x + 180 for x in euler_angles] #[x + 360 if x < 0 else x for x in euler_angles]
#         print(euler_angles) # roll, pitch, yaw
#         self.model.setPosHprScale(self.line_midpoint[0], self.line_midpoint[1], self.line_midpoint[2], euler_angles[2]+90, euler_angles[1]+270, euler_angles[0], line_thickness, line_thickness, float(np.sqrt((self.line_end - self.line_start).dot((self.line_end - self.line_start))))/2)
#
#
# class StdoutHandler:
#     def __init__(self):
#         self.last_output = ""
#
#     def start(self):
#         self._handled_stdout = sys.stdout
#         sys.stdout = self
#
#     def write(self, data: str):
#         # write(data="") is called for the end kwarg in print(..., end="")
#         if data:
#             # print("does this work?")
#             self.last_output += data
#             self._handled_stdout.write(data)
#
#     def end(self):
#         sys.stdout = self._handled_stdout
#
#     def flush(self):
#         self._handled_stdout.flush()
#
#
#
#     def autocomplete(search_word):
#         autocomplete = fast_autocomplete.AutoComplete(words=words)
#         ac_output = []
#         if search_word:
#             ac_output = autocomplete.search(word=search_word[0])
#         #print(ac_output)
#         #return [''.join(x) for x in ac_output]
#         return ['_autocomplete'] + ac_output
#
#     def plot(_):
#         x, y, z = np.pi*np.mgrid[-1:1:7j, -1:1:7j, -1:1:7j]
#         vol = np.cos(x) + np.cos(y) + np.cos(z)
#         iso_val=0.0
#         verts, faces, normals, values = marching_cubes(vol, iso_val, spacing=(0.4, 0.4, 0.4))
#         return ("_vertices", [["X=%.3f"%x[0] + " Y=%.3f"%x[1] + " Z=%.3f"%x[2]]for x in verts] , "_faces", [["X=%s"%x[0] + " Y=%s"%x[1] + " Z=%s"%x[2]]for x in faces] , "_normals", [["X=%.3f"%x[0] + " Y=%.3f"%x[1] + " Z=%.3f"%x[2]]for x in normals])
#
#
#
#     # Linux Commands
#     def ls(args):
#         windows_command="dir /b /ogn"
#         if not args or args is None:
#             # cmdix.runcommandline(windows_command + " ".join(args))
#             print(subprocess.check_output(windows_command.split(" "), shell=True, cwd=os.getcwd(), text=True))
#             #return subprocess.run(windows_command.split(" "), capture_output=True, text=True, shell=True,cwd=os.path.dirname(os.path.realpath(__file__))).stdout
#             #return subprocess.Popen(windows_command.split(" "), stdout=subprocess.PIPE, shell=True, cwd=os.path.dirname(os.path.realpath(__file__))).communicate()[0].decode('utf-8')
#             #subprocess.check_output(windows_command.split(" "))
#             #subprocess.run(windows_command.split(" "), capture_output=True, shell=True,cwd=os.getcwd()).stdout.decode('utf-8')
#             # op = subprocess.Popen(windows_command.split(" "), stderr=subprocess.PIPE, stdout=subprocess.PIPE)
#             # if op:
#             #     o, e = op.communicate()
#             #     # print(op.stdout.read())
#             #     #print('Error: '  + e.decode('ascii'))
#             #     #print('code: ' + str(proc.returncode))
#             #     return o.decode('ascii')
#         else:
#             print(subprocess.check_output(windows_command.split(" ").append(args), shell=True, cwd=os.getcwd(), text=True))
#             #return subprocess.run(windows_command.split(" ").append(args), capture_output=True, text=True).stdout
#             #return subprocess.Popen(windows_command.split(" ").append(args), stdout=subprocess.PIPE, shell=True, cwd = os.path.dirname(os.path.realpath(__file__))).communicate()[0].decode('utf-8')
#             # subprocess.check_output(windows_command.split(" ").append(args))
#             #subprocess.run(windows_command.split(" ").append(args), shell=True)
#             # op = subprocess.Popen(windows_command.split(" ").append(args), stderr=subprocess.PIPE, stdout=subprocess.PIPE)
#             # if op:
#             #     o, e = op.communicate()
#             #     #print('Error: '  + e.decode('ascii'))
#             #     #print('code: ' + str(proc.returncode))
#             #     return o.decode('ascii')
#
#     def man(args):
#         print((subprocess.run(["help"], shell=True, capture_output=True, text=True).stdout))
#
# self.stdout_handler.last_output = ""
#             input_text = text
#             print(text)
#             parsed = input_text.strip().split(' ')
#             print(locals().keys())
#             if parsed[0] in list(cmdix.listcommands()):  # linux commands
#                 output = cmdix.runcommandline(input_text)
#             elif ((parsed[0]) in locals().keys()):  # functions defined in this file
#                 print("customfunc called")
#                 output = locals()[parsed[0]](parsed[1:])  # TODO: Support for no argument functions
#             else:
#                 # print("eval called")
#                 try:
#                     output = exec(
#                         input_text)  # Executing of receieved statement. Exec relies on the stdout print statements to receive output whereas when this is switched to eval, output is sent back over the socket
#                     # output = repr(self.stdout_handler.last_output)
#                     # print(self.stdout_handler.last_output)
#                 except Exception as e:
#                     output = e
#
#             try:
#                 if not str(output) or output is None or output == "":
#                     # print("FFFF" + stdout_handler.last_output)
#                     output = repr(self.stdout_handler.last_output)
#                     # t.start()
#                     # if output is None or output == "":
#                     # output = self.tempoutput
#             except:
#                 pass
#
#
### Begin Command Processing ###
# list(cmdix.listcommands()): arch, base64, basename, bunzip2, bzip2, cal, cat, cp, crond, diff, dirname, env, expand, gunzip, gzip, httpd, init, kill, ln, logger, ls, md5sum, mkdir, mktemp, more, mv, nl, pwd, rm, rmdir, sendmail, seq, sh, sha1sum, sha224sum, sha256sum, sha384sum, sha512sum, shred, shuf, sleep, sort, tail, tar, touch, uname, uuidgen, wc, wget, yes, zip
# you can also get all of these from GitBash(C:\Program Files\Git\usr\bin): arch, awk, b2sum, base32, base64, basename, basenc, bash, bunzip2, bzcat, bzip2, bzip2recover, captoinfo, cat, chattr, chcon, chgrp, chmod, chown, chroot, cksum, clear, cmp, column, comm, cp, csplit, cut, cygcheck, cygpath, cygwin-console-helper, d2u, dash, date, dd, df, diff, diff3, dir, dircolors, dirmngr-client, dirmngr, dirname, dos2unix, du, dumpsexp, echo, env, ex, expand, expr, factor, false, file, find, fmt, fold, funzip, gawk-5.0.0, gawk, gencat, getconf, getfacl, getopt, gkill, gmondump, gpg-agent, gpg-card, gpg-connect-agent, gpg-error, gpg-mail-tube, gpg-wks-client, gpg-wks-server, gpg, gpgconf, gpgparsemail, gpgscm, gpgsm, gpgsplit, gpgtar, gpgv, grep, groups, gzip, head, hmac256, hostid, hostname, iconv, id, infocmp, infotocap, install, join, kbxutil, kill, ldd, ldh, less, lessecho, lesskey, link, ln, locale, locate, logname, ls, lsattr, mac2unix, md5sum, minidumper, mintty, mkdir, mkfifo, mkgroup, mknod, mkpasswd, mktemp, mount, mpicalc, mv, nano, nettle-hash, nettle-lfib-stream, nettle-pbkdf2, newgrp, nice, nl, nohup, nproc, numfmt, od, openssl, p11-kit, passwd, paste, patch, pathchk, perl, perl5.38.2, pinentry-w32, pinentry, pinky, pkcs1-conv, pldd, pluginviewer, pr, printenv, printf, profiler, ps, psl, ptx, pwd, readlink, realpath, rebase, regtool, reset, rm, rmdir, rnano, runcon, rview, rvim, scp, sdiff, sed, seq, setfacl, setmetamode, sexp-conv, sftp, sh, sha1sum, sha224sum, sha256sum, sha384sum, sha512sum, shred, shuf, sleep, sort, split, ssh-add, ssh-agent, ssh-keygen, ssh-keyscan, ssh-pageant, ssh, ssp, stat, stdbuf, strace, stty, sum, sync, tabs, tac, tail, tar, tee, test, tic, tig, timeout, toe, touch, tput, tr, true, truncate, trust, tset, tsort, tty, tzset, u2d, umount, uname, unexpand, uniq, unix2dos, unix2mac, unlink, unzip, unzipsfx, users, vdir, view, vim, vimdiff, watchgnupg, wc, which, who, whoami, winpty-agent, winpty-debugserver, winpty, xargs, xxd, yat2m, yes, zipinfo

# cmd = ['echo', 'I like potatos']
# proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# o, e = proc.communicate()

# print('Output: ' + o.decode('ascii'))
# print('Error: '  + e.decode('ascii'))
# print('code: ' + str(proc.returncode))



# /** Handles image2D update**/
# int32 AGACube::GetTexture2DDynamicWidth(UTexture2DDynamic* InTexture2DDynamicReference)
# {
# 	if (!InTexture2DDynamicReference)
# 	{
# 		return -1;
# 	}
# 	return InTexture2DDynamicReference->SizeX;
# }
#
# int32 AGACube::GetTexture2DDynamicHeight(UTexture2DDynamic* InTexture2DDynamicReference)
# {
# 	if (!InTexture2DDynamicReference)
# 	{
# 		return -1;
# 	}
# 	return InTexture2DDynamicReference->SizeY;
# }
#
# FVector2D AGACube::GetGameViewportSize()
# {
# 	FVector2D Result = FVector2D( 1, 1 );
#
# 	if ( GEngine && GEngine->GameViewport )
# 	{
# 		GEngine->GameViewport->GetViewportSize( /*out*/Result );
# 	}
#
# 	return Result;
# }
#
# FVector2D AGACube::GetGameResolution()
# {
# 	FVector2D Result = FVector2D( 1, 1 );
#
# 	Result.X = GSystemResolution.ResX;
# 	Result.Y = GSystemResolution.ResY;
#
# 	return Result;
# }
#
# /**https://forums.unrealengine.com/t/how-to-inject-simulate-mouse-clicks/25602/7**/
# void AGACube::ClickLMB()
# {
# 	FSlateApplication& SlateApp = FSlateApplication::Get();
# 	FPointerEvent MouseDownEvent(
# 		0,
# 		SlateApp.CursorPointerIndex,
# 		SlateApp.GetCursorPos(),
# 		SlateApp.GetLastCursorPos(),
# 		SlateApp.GetPressedMouseButtons(),
# 		EKeys::LeftMouseButton,
# 		0,
# 		SlateApp.GetPlatformApplication()->GetModifierKeys()
# 	);
# 	TSharedPtr<FGenericWindow> GenWindow;
# 	SlateApp.ProcessMouseButtonDownEvent(GenWindow, MouseDownEvent);
# }

# 	UFUNCTION(BlueprintCallable, Category = "Starcel")
# 	FVector2D GetGameViewportSize();
#
# 	UFUNCTION(BlueprintCallable, Category = "Starcel")
# 	FVector2D GetGameResolution();
#
# 	UFUNCTION(BlueprintCallable, Category = "Starcel")
# 	void ClickLMB();
#
# 	UFUNCTION(BlueprintCallable)
# 	int32 GetTexture2DDynamicWidth(UTexture2DDynamic* InTexture2DDynamicReference);
#
# 	UFUNCTION(BlueprintCallable)
# 	int32 GetTexture2DDynamicHeight(UTexture2DDynamic* InTexture2DDynamicReference);