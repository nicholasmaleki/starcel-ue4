import os
import sys
import requests
import inspect
from typing import Any, Dict, List, Optional

PISTON_URL = "https://emkc.org/api/v2/piston"
__all__ = ["langs"]

def _make_language_function(alias: str, language: str, langs_instance):
    def lang_fn(
        code: str,
        *,
        version="*",
        stdin="",
        args=None,
        log=False,
        verbose=False,
        **limits
    ):
        if args is None:
            args = []

        output = langs_instance._run(
            language,
            code,
            version=version,
            stdin=stdin,
            args=args,
            log=log,
            verbose=verbose,
            keep_trailing_newline=True,  # always preserve for consistent assignment
            **limits
        )

        return output

    # allow calling .run() explicitly
    lang_fn.run = lang_fn
    # allow fetching the version
    lang_fn.version = lambda: langs_instance.version(alias)
    # metadata
    lang_fn.__name__ = alias
    lang_fn.__qualname__ = alias
    lang_fn.__doc__ = f"Run {language} code via Piston"
    return lang_fn

def _rebuild_language_functions(langs_instance):
    module_globals = sys.modules[__name__].__dict__
    caller_globals = inspect.currentframe().f_back.f_globals

    for alias, language in langs_instance._aliases.items():
        if not alias.isidentifier():
            continue
        fn = _make_language_function(alias, language, langs_instance)
        module_globals[alias] = fn
        caller_globals[alias] = fn
        if alias not in __all__:
            __all__.append(alias)

def _generate_pyi(langs_instance):
    path = os.path.join(os.path.dirname(__file__), "languages.pyi")
    lines = [
        "from typing import Any, Dict, List",
        "",
        "class Langs:",
        "    def refresh(self) -> None: ...",
        "    def add_alias(self, alias: str, language: str) -> None: ...",
        "    def list_languages(self) -> Dict[str, str]: ...",
        "    def version(self, alias: str) -> str: ...",
        "    def set_logger(self, func) -> None: ...",
        "",
        "langs: Langs",
        "",
    ]
    for alias in sorted(langs_instance._aliases):
        if not alias.isidentifier():
            continue
        lines.append(
            f"def {alias}("
            "code: str, *, version: str = '*', stdin: str = '', "
            "args: List[str] = ..., log: bool = False, verbose: bool = False, "
            "**limits: Any) -> str: ..."
        )
    with open(path, "w", encoding="utf-8") as f:
        f.write("\n".join(lines))

class Langs:
    def __init__(self):
        self._languages: Dict[str, str] = {}
        self._aliases: Dict[str, str] = {}
        self._logger: Optional[Any] = None
        self.refresh()

    def _run(
        self,
        language: str,
        code: str,
        *,
        version="*",
        stdin="",
        args=None,
        log=False,
        verbose=False,
        keep_trailing_newline=False,
        **limits
    ):
        if args is None:
            args = []

        if version == "*":
            version = self._languages.get(language, "*")

        payload = {
            "language": language,
            "version": version,
            "files": [{"content": code}],
            "stdin": stdin,
            "args": args,
            "compile_timeout": limits.get("compile_timeout", 10000),
            "run_timeout": limits.get("run_timeout", 3000),
            "compile_cpu_time": limits.get("compile_cpu_time", 10000),
            "run_cpu_time": limits.get("run_cpu_time", 3000),
            "compile_memory_limit": limits.get("compile_memory_limit", -1),
            "run_memory_limit": limits.get("run_memory_limit", -1),
        }

        if log or self._logger:
            msg = f"[piston] {language}@{version}"
            if self._logger:
                self._logger(msg)
            else:
                print(msg)

        r = requests.post(f"{PISTON_URL}/execute", json=payload)
        r.raise_for_status()
        result = r.json()

        if verbose:
            return result

        output = result["run"]["stdout"]
        if keep_trailing_newline:
            return output
        return output.rstrip("\n")

    def refresh(self):
        r = requests.get(f"{PISTON_URL}/runtimes")
        r.raise_for_status()
        self._languages.clear()
        self._aliases.clear()
        for entry in r.json():
            lang = entry["language"]
            ver = entry.get("version", "*")
            self._languages[lang] = ver
            for a in entry.get("aliases", []):
                self._aliases[a] = lang
            self._aliases[lang] = lang

        _rebuild_language_functions(self)
        _generate_pyi(self)

    def add_alias(self, alias: str, language: str):
        self._aliases[alias] = language
        fn = _make_language_function(alias, language, self)
        sys.modules[__name__].__dict__[alias] = fn
        caller_globals = inspect.currentframe().f_back.f_globals
        caller_globals[alias] = fn

    def list_languages(self) -> Dict[str, str]:
        result = {}
        for alias, lang in self._aliases.items():
            result[alias] = self._languages.get(lang, "*")
        return result

    def version(self, alias: str) -> str:
        lang = self._aliases.get(alias)
        return self._languages.get(lang, "*") if lang else "*"

    def set_logger(self, func):
        self._logger = func

# Global instance
langs = Langs()

# Add an alias for C (so both 'C' and 'clang' work)
langs.add_alias("C", "c")
langs.add_alias("clang", "c")