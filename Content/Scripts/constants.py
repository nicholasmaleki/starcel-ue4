class Constants:
    def __init__(self):
        self.default_alphabet = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r",
                            "s", "t", "u", "v", "w", "x", "y", "z"]
        self.default_alphabet_capital = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q",
                                    "R", "S", "T", "U", "V", "W", "X", "Y", "Z"]
        self.default_metric_prefixes = [
            ["quetta","ronna","yotta","zetta","exa","peta","tera","giga","mega","kilo","hecto","deka","X","deci","centi","milli","micro","nano","pico","femto","atto","zepto","yocto","ronto","quecto"],
            ["Q","R","Y","Z","E","P","T","G","M","k","h","da","X","d","c","m","μ","n","p","f","a","z","y","r","q"],
            ["10^30","10^27","10^24","10^21","10^18","10^15","10^12","10^9","10^6","10^3","10^2","10^1","10^0","10^(-1)","10^(-2)","10^(-3)","10^(-6)","10^(-9)","10^(-12)","10^(-15)","10^(-18)","10^(-21)","10^(-24)","10^(-27)","10^(-30)"],
            ["E+30","E+27","E+24","E+21","E+18","E+15","E+12","E+9","E+6","E+3","E+2","E+1","E0","E-1","E-2","E-3","E-6","E-9","E-12","E-15","E-18","E-21","E-24","E-27","E-30"],
            ["nonillion","octillion","septillion","sextillion","quintillion","quadrillion","trillion","billion","million","thousand","hundred","ten","one","tenth","hundredth","thousandth","millionth","billionth","trillionth","quadrillionth","quintillionth","sextillionth","septillionth","octillionth","nonillionth"]
        ]
        self.keyboard_wootingtwohe = [
            ["Esc", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "PrtSc", "Pause", "ScrLk", "M1", "M2", "M3", "MR"],
            ["`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "Backspace", "Ins", "Home", "PgUp", "Num", "/", "*", "-"],
            ["Tab", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "\\","Del","End","PgDn","7","8","9","+"],
            ["Caps", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "Enter", "null", "null", "null", "4", "5", "6", "+"],
            ["LeftShift", "z", "x", "c", "v", "b", "n", "m", "", "", ".", "/", "RightShift", "null", "UP", "null", "1", "2", "3", "Enter"],
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
# `, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -, =, Backspace
# Tab, q, w, e, r, t, y, u, i, o, p, [, ], \
# Caps, a, s, d, f, g, h, j, k, l,;, ',Enter
# LeftShift, z, x, c, v, b, n, m,, , ., /, RightShift
# LeftCtrl, Win, LeftAlt, Space, RightAlt, Win, Menu, RightCtrl
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
        self.quotes = [
        "Why, where are you now?",
        "You'd be nowhere",
        "Their heads are gone",
        "Visit either you like",
        "You wouldn't have come here",
        "Oh, you can't help that”, “We're all mad here. I'm mad.You're mad.",
        "That depends a good deal on where you want to get to",
        "Then it doesn't matter which way you go",
        "If you only walk long enough.",
        "Oh, you're sure to do that",

        "what did that to you?",
        "well, I better have a look",
        "at least let me find it for you",
        "what do you call yourself",
        "you best be on your way",
        "fine",
        "but, that's the end of it",
        "Coming?",
        "Times up.",
        "bloody big head",
        "what happened that day was not my fault",
        "uh oh",
        "goodbye",
        "I've always admired that hat",
        "since you won't be needing it anymore",
        "it is a pity about all this",
        "I was looking forward to see you-",
        "I really do love that hat. I would wear it to all the finest occasions",
        "good morning everyone",
        "not impossible, merely unpossible",
        "and do try not to break the past present or future",
        "I'm right on time",

        "Lose something?",
        "that depends on where you want to get to",
        "then it really doesn't matter which way you go",
        "you may have noticed that I am not all there myself",

        "Take this REPL, brother, and may it serve you well.",
        "This could be the start of a beautiful program.",

        "Unbounded thinking",
        "Thinking about thinking",
        "Fixing broken things, breaking working things",
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
        "Someone's entire life: memories, worries, hopes, dreams, fears, and decisions are all contained within the brain.",
        "Almost all of your neurons form before your birth and may survive after your death. Treat them well.",
        "\"Our unalterable resolution should be to be free.\" - Samuel Adams",

        "Donate on Patreon, Paypal, or with Crypto!",
        "Nick Maleki For President 2048"
        ]

# atoms
# 10m world size
#
# electrons
# 1m world size
#
# photons
# 1nm world size
#
# planck and high frequency/small wavelength photons
# 10^(-13)nm world size
#
#
#
# 8800000000000*.001nm = 8.8m Max world size
#
# 10^16 unreal magnitude window
# 127,560,000cm Earth diameter
#
#
#
# 0.001 nanometers atoms 8.8m world size
# 0.00000282nm electrons. 24 816 000 nanometers .024816m world size
# 0.000000000000000000000000282nm (10^(-35)m) smallest photons by idiot math using electrons weight and size. 2.4816 × 10-21 meters. 2.4816 × 10-12nm world size
# 10^-35m planck. 1.4*10^(-22)m 1.4*10^(-13)nm world size
# 0.0000000000282nm visible photon idiot math. 2.4816 × 10-7 meters. 250nm world size
# 0.00000000000000000000282nm AM radio idiot math. 2.4816 × 10-17 meters. 1.4*10^(-8)nm world size
#
# 10^26m observable universe
#
#
# 88000000 kilometers =
# 88000000000 meters
#
# 88000000000 meters =
# 8800000000000 centimeters
#
# 1cm is 1 unit
# 8800000000000 units
#
# if 1unit is 10nm
#
# 88000000000000 nanometers =
# 88000 meters Max world size for a 10nm world
#
#
#
# 9.1093837 × 10-31 kilograms electron
# 9.52* 10^{-46} (up to -50) kilograms smallest photon
# 4.42* 10^{-36}kg normal photon
# 2.21 10-17kg gamma ray photon
#
# 1.0 × 10-11 nanometers gamma rays wavelength
# 1.0 × 10-16 nanometers smallest gamma rays wavelength
#
#
# 1nm EUV wavelength
# 100km radio wave
# 100000km man made radio wave