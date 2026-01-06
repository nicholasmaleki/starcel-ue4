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

        self.ue.keys = ["AnyKey",
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

        self.keyboard_wootingtwohe = [
            ["Esc", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "PrtSc", "Pause", "ScrLk", "M1", "M2", "M3", "MR"],
            ["`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "Backspace", "Ins", "Home", "PgUp", "Num", "/", "*", "-"],
            ["Tab", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "\\", "Del", "End", "PgDn", "7", "8", "9", "+"],
            ["Caps", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "Enter", None, None, None, "4", "5", "6", "+"],
            ["LeftShift", "z", "x", "c", "v", "b", "n", "m", "", "", ".", "/", "RightShift", None, "UP", None, "1", "2", "3", "Enter"],
            ["LeftCtrl", "Win", "LeftAlt", "Space", "RightAlt", "Menu", "Fn", "RightCtrl", "LEFT", "DOWN", "RIGHT", "0", "0", ".", "Enter"]
        ]
        self.keyboard_wootingtwohe_shift = [
            ["Esc", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "PrtSc", "Pause", "ScrLk", "M1", "M2", "M3", "MR"],
            ["~", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+", "Backspace", "Ins", "Home", "PgUp", "Num", "/", "*", "-"],
            ["Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}", "|", "Del", "End", "PgDn", "7", "8", "9", "+"],
            ["Caps", "A", "S", "D", "F", "G", "H", "J", "K", "L", ":", "\"", "Enter", None, None, None, "4", "5", "6", "+"],
            ["LeftShift", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?", "RightShift", None, "UP", None, "1", "2", "3", "Enter"],
            ["LeftCtrl", "Win", "LeftAlt", "Space", "RightAlt", "Menu", "Fn", "RightCtrl", "LEFT", "DOWN", "RIGHT", "0", "0", ".", "Enter"]
        ]
        # Esc, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, PrtSc, Pause, ScrLk, M1, M2, M3, MR
        # `, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -, =, Backspace, Ins, Home, PgUp, Num, /, *, -
        # Tab, q, w, e, r, t, y, u, i, o, p, [, ], \, Del, End, PgDn, 7, 8, 9, +
        # Caps, a, s, d, f, g, h, j, k, l,;, ',Enter, "", "", "", 4, 5, 6, ""
        # LeftShift, z, x, c, v, b, n, m,, , ., /, RightShift, "", UP, "", 1, 2, 3, Enter
        # LeftCtrl, Win, LeftAlt, Space, RightAlt, Menu, Fn, RightCtrl, LEFT, DOWN, RIGHT, 0, "",., ""
        self.keyboard_razerblade152019 = [
            ["Esc", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "Ins", "Delete"],
            ["`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "Backspace"],
            ["Tab", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "\\"],
            ["Caps", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "Enter"],
            ["LeftShift", "z", "x", "c", "v", "b", "n", "m", "", "", ".", "/", "UP", "RightShift"],
            ["LeftCtrl", "Fn", "Win", "LeftAlt", "Space", "RightAlt", "RightCtrl", "LEFT", "DOWN", "RIGHT", "Fn"]
        ]
        self.keyboard_razerblade152019_shift = [
            ["Esc", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "Ins", "Delete"],
            ["~", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+", "Backspace"],
            ["Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}", "|"],
            ["Caps", "A", "S", "D", "F", "G", "H", "J", "K", "L", ":", "\"", "Enter"],
            ["LeftShift", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?", "UP", "RightShift"],
            ["LeftCtrl", "Fn", "Win", "LeftAlt", "Space", "RightAlt", "RightCtrl", "LEFT", "DOWN", "RIGHT", "Fn"]
        ]
        # Esc, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, Ins, Delete
        # `, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -, =, Backspace
        # Tab, q, w, e, r, t, y, u, i, o, p, [, ], \
        #     Caps, a, s, d, f, g, h, j, k, l,;, ',Enter
        # LeftShift, z, x, c, v, b, n, m,, , ., /, UP, RightShift
        # LeftCtrl, Fn, Win, LeftAlt, Space, RightAlt, RightCtrl, LEFT, DOWN, RIGHT, Fn
        self.keyboard_ANSI_QWERTY_US = [
            ["`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "Backspace"],
            ["Tab", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "\\"],
            ["Caps", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "Enter"],
            ["LeftShift", "z", "x", "c", "v", "b", "n", "m", "", "", ".", "/", "RightShift"],
            ["LeftCtrl", "Win", "LeftAlt", "Space", "RightAlt", "Win", "Menu", "RightCtrl"]
        ]
        self.keyboard_ANSI_QWERTY_shift = [
            ["~", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+", "Backspace"],
            ["Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}", "|"],
            ["Caps", "A", "S", "D", "F", "G", "H", "J", "K", "L", ":", "\"" "Enter"],
            ["LeftShift", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?", "RightShift"],
            ["LeftCtrl", "Win", "LeftAlt", "Space", "RightAlt", "Win", "Menu", "RightCtrl"]
        ]
        # `, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -, =, Backspace
        # Tab, q, w, e, r, t, y, u, i, o, p, [, ], \
        # Caps, a, s, d, f, g, h, j, k, l,;, ',Enter
        # LeftShift, z, x, c, v, b, n, m,, , ., /, RightShift
        # LeftCtrl, Win, LeftAlt, Space, RightAlt, Win, Menu, RightCtrl

        self.quotes = [
            "Why, where are you now?",
            "You'd be nowhere",
            "Their heads are gone",
            "Visit either you like",
            "You wouldn't have come here",
            "Oh, you can't help that”, “We're all mad here. I'm mad. You're mad.",
            "That depends a good deal on where you want to get to",
            "Then it doesn't matter which way you go",
            "If you only walk long enough",
            "Oh, you're sure to do that",

            "What did that to you?",
            "Well, I better have a look",
            "At least let me find it for you",
            "What do you call yourself",
            "You best be on your way",
            "Fine",
            "But, that's the end of it",
            "Coming?",
            "Times up.",
            "Bloody big head",
            "What happened that day was not my fault",
            "Uh oh",
            "Goodbye",
            "I've always admired that hat",
            "Since you won't be needing it anymore",
            "It is a pity about all this",
            "I was looking forward to see you-",
            "I really do love that hat. I would wear it to all the finest occasions",
            "Good morning everyone",
            "Not impossible, merely unpossible",
            "and do try not to break the past present or future",
            "I'm right on time",

            "Lose something?",
            "That depends on where you want to get to",
            "Then it really doesn't matter which way you go",
            "You may have noticed that I am not all there myself",

            "Take this REPL, brother, and may it serve you well.",
            "This could be the start of a beautiful program.",

            "Unbounded thinking",
            "Thinking about thinking",
            "Observe observations"
            "Fixing broken things, breaking working things",
            "Fixing broken things, bre-"
            "Sequent Calculus: True and False!",
            "Neither True nor False",
            "Challenging paradoxes",
            "The self-application of self-application",
            "The clock is ticking",
            "Both infinity and zero are infinitely certain",
            "Introducing infinity from a finite perspective",
            "You don't know where you are without being relative to something",
            "\"I would rather regret something I did, than something I didn't.\"",
            "\"Steal from the best, invent the rest.\" - Micheal Corsetto",
            "\"You will never get younger than now.\"",
            "\"There are no differences but differences of degree between different degrees of difference and no difference.\" - William James",
            "\"Time is the most valuable thing a person can spend.\" - Theophrastus",
            "\"Sooner or later, everything old is new again.\" - Steven King",
            "\"That which can be destroyed by the truth should be.\" - Patricia Christine Hodgell",
            "\"Life itself is an exercise in exceptions.\" - Jean-Luc Picard",
            "\"It is okay to make mistakes as long as things are happening.\"",
            "\"The inventors of the alphabet were unable to read until after they created letters.\" - SirHerald",
            "\"Because Nothing was, therefore All Things are.\" - Edgar Allen Poe",
            "\"Space and duration are one.\" - Edgar Allen Poe",
            "\"Rhythmic Balanced Interchange\" - Walter Russell",
            "\"We can't talk about how reality functions without sounding crazy.\"",
            "\"Our unalterable resolution should be to be free.\" - Samuel Adams",
            "Someone's entire life: memories, worries, hopes, dreams, fears, and decisions are all contained within the brain.",
            "Almost all of your neurons form before your birth and may survive after your death. Treat them well.",

            "Donate on Patreon, Paypal, or with Crypto!",
            "Please Donate to keep this project running!",
            "Buy me a coffee!",
            "Donate for more Starcel",
            "Donate to make my hair longer",
            "pls donate",

            "Nick Maleki For President 2048"
        ]


class WorldSize():
    def __init__(self):  # most large world sizes require origin rebasing
        # all in meters
        self.ue4_world_max = 20971  # disable World Bounds Checks to exceed, change UE_USE_UE4_WORLD_MAX located in the EngineDefines.h, then recompile the engine. WORLD_MAX is the constant that is set to 2097152.0 Unreal Units(UU/cm)
        self.MAX = 16655451  # using 1024 4033x4033 tiles: https://youtu.be/uesmtsQZ3lI?si=wkfQtAVbnlrK-1i-&t=386
        self.earth_size = 12756000  # includes bulge at the equator. Notice that it fits into the tiled ue4 world
        self.editor_precision = .001
        self.ue4_precision = .0000001  # check IEEE754 for more info. ~7 sig figs
        self.ue5_precision = .000000000000001  # ~15-16 sig figs
        # self.ue4_world_max = 88000000000 # bEnableLargeWorlds = true, UE_USE_UE4_WORLD_MAX=0. Although, this reports larger: https://old.reddit.com/r/unrealengine/comments/1axhmhm/is_the_88_million_km_max_world_size_total_area_or/kro5la5/

        # all in meters
        self.observable_universe = 10 ^ 26
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
