HELLO_WORLD = {
    # Core / Western
    "en": "Hello World!",
    "fr": "Salut le monde!",
    "de": "Hallo Welt!",
    "es": "¡Hola mundo!",
    "it": "Ciao mondo!",
    "pt": "Olá, mundo!",
    "nl": "Hallo, wereld!",
    "sv": "Hallå världen!",
    "no": "Hallo verden!",
    "da": "Hej, verden!",
    "fi": "Hei maailma!",
    "is": "Halló heimur!",
    "af": "Hallo, wêreld!",
    "fy": "Hallo, wrâld!",
    "lb": "Moien Welt!",
    "ga": "Dia dhuit, a dhomhain!",
    "cy": "S'mae byd!",

    # Eastern Europe
    "pl": "Witaj świecie!",
    "cs": "Ahoj světe!",
    "sk": "Ahoj svet!",
    "sl": "Pozdravljen svet!",
    "hr": "Bok svijete!",
    "sr": "Zdravo svete!",
    "bs": "Zdravo svijete!",
    "hu": "Helló világ!",
    "ro": "Salut lume!",
    "bg": "Здравей, свят!",
    "uk": "Привіт, світе!",
    "be": "Прывітанне свет!",
    "ru": "Здравствуй, мир!",
    "lt": "Sveikas, pasauli!",
    "lv": "Sveika, pasaule!",

    # Middle East
    "ar": "أهلاً بالعالم",
    "he": "שלום עולם",
    "fa": "سلام دنیا",
    "ur": "ہیلو دنیا",

    # South Asia
    "hi": "नमस्ते दुनिया",
    "bn": "স্বাগতম পৃথিবী!",
    "pa": "ਸਤਿ ਸ੍ਰੀ ਅਕਾਲ ਦੁਨਿਆ!",
    "ta": "ஹலோ உலகம்!",
    "te": "హలో వరల్డ్!",
    "ml": "നമസ്കാരം ലോകമേ!",
    "kn": "ಹಲೋ ವರ್ಲ್ಡ್",
    "mr": "नमस्कार जग",

    # East Asia
    "ja": "こんにちは、世界！",
    "ko": "안녕 세상!",
    "zh-hans": "你好，世界！",   # Simplified Chinese
    "zh-hant": "你好，世界！",   # Traditional Chinese

    # Southeast Asia
    "th": "สวัสดีโลก!",
    "vi": "Xin chào thế giới!",
    "id": "Halo Dunia!",
    "ms": "Halo Dunia!",
    "tl": "Kamusta mundo!",
    "lo": "ສະບາຍດີ ໂລກ!",
    "km": "ជំរាបសួរ ពិភពលោក!",

    # Africa
    "sw": "Habari dunia!",
    "zu": "Sawubona Mhlaba!",
    "xh": "Molo hlabathi!",
    "yo": "Pẹlẹ o, ayé!",
    "ig": "Ndewo Ụwa!",
    "am": "ሰላም ዓለም",

    # Indigenous / regional
    "chr": "ᎣᏏᏲ ᎡᎶᎯ",
    "qu": "Allin p'unchay pacha!",

    # Classical / dev culture
    "la": "Ave Munde!",
    "eo": "Saluton mondo!",
    "yi": "העלא וועלט!",
    "haw": "Aloha Honua",
    "gd": "Halò a shaoghail!",

    # Fun / tech
    "tlh": "nuqneH", # Klingon
    "jbo": "coi ro lo munje", # Lojban
}

import requests


def normalize_lang(lang):
    """
    Normalize locale strings:
    - en-US / en_US → en
    - ja-JP → ja (forced)
    - ko-KR → ko (forced)
    - zh-Hans / zh-Hant preserved
    """
    lang = lang.lower().replace("_", "-")

    if lang.startswith("ja"):
        return "ja"

    if lang.startswith("ko"):
        return "ko"

    if lang.startswith("zh"):
        if "hant" in lang:
            return "zh-hant"
        return "zh-hans"

    return lang.split("-")[0]


def parse_accept_language(header = None):
    """
    Parse Accept-Language header with q-values.
    Returns ordered list of normalized language codes.
    """
    if not header:
        return []

    langs = []

    for part in header.split(","):
        part = part.strip()
        if ";q=" in part:
            lang, q = part.split(";q=", 1)
            try:
                q = float(q)
            except ValueError:
                q = 1.0
        else:
            lang = part
            q = 1.0

        langs.append((normalize_lang(lang), q))

    # Sort by descending q-value
    langs.sort(key=lambda x: x[1], reverse=True)

    return [lang for lang, _ in langs]


def detect_lang_from_ip():
    """
    Last-resort IP-based detection.
    """
    try:
        info = requests.get("https://ipinfo.io/json", timeout=2).json()
        country = info.get("country", "").lower()

        country_lang_map = {
            "us": "en", "gb": "en", "ca": "en",
            "fr": "fr", "de": "de", "es": "es",
            "it": "it", "pt": "pt", "br": "pt",
            "ru": "ru", "jp": "ja", "kr": "ko",
            "cn": "zh-hans", "tw": "zh-hant",
            "hk": "zh-hant", "mo": "zh-hant",
            "il": "he", "sa": "ar", "eg": "ar",
            "in": "hi",
        }

        return country_lang_map.get(country, "en")
    except Exception:
        return "en"


def hello_world(lang = None, accept_language = None):
    """
    Resolution order:
    1. Explicit lang
    2. Accept-Language (q-values respected)
    3. IP-based detection
    4. English fallback
    """

    # 1. Explicit language
    if lang:
        lang = normalize_lang(lang)
        return HELLO_WORLD.get(lang, HELLO_WORLD["en"])

    # 2. Accept-Language
    for candidate in parse_accept_language(accept_language):
        if candidate in HELLO_WORLD:
            return HELLO_WORLD[candidate]

    # 3. IP fallback
    lang = detect_lang_from_ip()
    return HELLO_WORLD.get(lang, HELLO_WORLD["en"])
