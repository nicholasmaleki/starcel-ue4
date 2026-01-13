import os
import re
import keyword
import json
from datetime import datetime, timezone
from typing import Dict, Any, List

# -----------------------------
# Config
# -----------------------------
BIN_DIR = r"C:\Program Files\Git\usr\bin"
OUTPUT_FILE = "cli.py"
STUB_FILE = "cli.pyi"

extra_exes = [
    r"C:\Program Files\Git\bin\git.exe",
    r"C:\Windows\System32\cmd.exe",
    r"C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe",
    os.path.join(os.path.dirname(os.getcwd()), "CLITools", "ES-1.1.0.30.x64", "es.exe"),
]

ALIASES = {
    "ps": {"target": "powershell", "args": []},
    "search_system": {"target": "es", "args": []},
}

COMMAND_GROUPS = {
    "git": {
        "_cmd": "git",
        "status": {"_cmd": "git", "_args": ["status"]},
        "commit": {"_cmd": "git", "_args": ["commit"]},
        "push": {"_cmd": "git", "_args": ["push"]},
        "pull": {"_cmd": "git", "_args": ["pull"]},
        "pullrebase": {"_cmd": "git", "_args": ["pull", "--rebase"]},
        "add": {"_cmd": "git", "_args": ["add"]},
    }
}

# -----------------------------
# Helpers
# -----------------------------
def sanitize(name: str) -> str:
    name = name.replace("-", "_")
    name = re.sub(r"[^0-9a-zA-Z_]", "_", name)
    if name and name[0].isdigit():
        name = "_" + name
    if keyword.iskeyword(name):
        name += "_"
    return name

def is_exe(name: str) -> bool:
    return name.lower().endswith(".exe")

# -----------------------------
# Discover commands
# -----------------------------
tools: Dict[str, Dict[str, Any]] = {}

if os.path.isdir(BIN_DIR):
    for fname in os.listdir(BIN_DIR):
        if is_exe(fname):
            cmd = fname[:-4]
            tools[sanitize(cmd)] = {"cmd": cmd, "preset_args": []}

for path in extra_exes:
    if os.path.isfile(path):
        cmd = os.path.basename(path)[:-4]
        tools[sanitize(cmd)] = {"cmd": path, "preset_args": []}

for alias, spec in ALIASES.items():
    t = sanitize(spec["target"])
    if t in tools:
        tools[sanitize(alias)] = {
            "cmd": tools[t]["cmd"],
            "preset_args": spec.get("args", []),
        }

# -----------------------------
# Normalize groups
# -----------------------------
def normalize(node):
    if isinstance(node, dict):
        result = {}
        if "_cmd" in node:
            cmd = sanitize(node["_cmd"])
            if cmd in tools:
                result["_self"] = {
                    "cmd": tools[cmd]["cmd"],
                    "preset_args": node.get("_args", []),
                }
        children = {}
        for k, v in node.items():
            if k.startswith("_"):
                continue
            c = normalize(v)
            if c:
                children[sanitize(k)] = c
        if result or children:
            return {"type": "group", **result, "children": children}
    return None

GROUP_TREE = {}
for name, node in COMMAND_GROUPS.items():
    n = normalize(node)
    if n:
        GROUP_TREE[sanitize(name)] = n

TOP_LEVEL_COMMANDS = tools
generated_at = datetime.now(timezone.utc).isoformat()

# -----------------------------
# Write cli.py
# -----------------------------
with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
    f.write(f'''from __future__ import annotations
# generated at {generated_at}

import os
import sys
import subprocess
import json
import time
from typing import List

INTERACTIVE_COMMANDS = {{"ps", "cmd", "powershell"}}

class CommandResult:
    def __init__(self, stdout: str, stderr: str, returncode: int):
        self.stdout = stdout
        self.stderr = stderr
        self.returncode = returncode

    def __repr__(self):
        return ""  # hide by default

    def json(self):
        if not self.stdout:
            return None
        try:
            return json.loads(self.stdout)
        except json.JSONDecodeError:
            return None

    def pipe(self, cmd: str, *args: str):
        return _Pipeline([(cmd, list(args))], self.stdout)

    def time(self, elapsed: float):
        print(f"Time: {{elapsed:.6f}}s")
        return elapsed


class _Pipeline:
    def __init__(self, cmds, input_text=None):
        self._cmds = cmds
        self._input = input_text

    def pipe(self, cmd: str, *args: str):
        self._cmds.append((cmd, list(args)))
        return self

    def run(self):
        prev = None
        for i, (cmd, args) in enumerate(self._cmds):
            p = subprocess.Popen(
                [cmd] + args,
                stdin=subprocess.PIPE if prev else None,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
            )
            if prev:
                out, _ = prev.communicate()
                p.stdin.write(out)
                p.stdin.close()
            prev = p
        out, err = prev.communicate()
        if out:
            print(out, end="")
        if err:
            print(err, end="", file=sys.stderr)
        return CommandResult(out, err, prev.returncode)


class _CommandNode:
    def __init__(self, cli, node=None, cmd=None, preset_args=None):
        self._cli = cli
        self._node = node
        self._cmd = cmd
        self._preset_args = preset_args or []

    def __call__(self, *args):
        if self._node and "_self" in self._node:
            cmd = self._node["_self"]["cmd"]
            args_list = self._node["_self"].get("preset_args", []) + list(args)
        elif self._cmd:
            cmd = self._cmd
            args_list = self._preset_args + list(args)
        else:
            raise TypeError("This node is a group")

        start = time.perf_counter()
        exe_name = os.path.basename(cmd).lower()
        # Interactive commands run directly in console
        if exe_name in INTERACTIVE_COMMANDS:
            return_code = subprocess.run([cmd] + list(args_list)).returncode
            elapsed = time.perf_counter() - start
            print(f"Time: {{elapsed:.6f}}s")
            return CommandResult("", "", return_code)
        else:
            p = subprocess.run([cmd] + list(args_list), text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            elapsed = time.perf_counter() - start
            if p.stdout:
                print(p.stdout, end="")
            if p.stderr:
                print(p.stderr, end="", file=sys.stderr)
            result = CommandResult(p.stdout, p.stderr, p.returncode)
            # attach helpers
            result.time = lambda: CommandResult.time(result, elapsed)
            return result

    def __getattr__(self, name):
        c = None
        if self._node:
            c = self._node.get("children", {{}}).get(name)
        if c:
            return _CommandNode(self._cli, node=c)
        raise AttributeError(name)


class CLI:
    def __init__(self):
        for name, t in {TOP_LEVEL_COMMANDS!r}.items():
            setattr(self, name, _CommandNode(self, cmd=t["cmd"], preset_args=t.get("preset_args", [])))
        for name, node in {GROUP_TREE!r}.items():
            setattr(self, name, _CommandNode(self, node=node))


_default_cli = CLI()
globals().update({{k: getattr(_default_cli, k) for k in dir(_default_cli) if not k.startswith("_")}})
''')

print(f"Generated {OUTPUT_FILE}")

# -----------------------------
# Generate cli.pyi
# -----------------------------
def write_stub_group(f, name: str, node: Dict[str, Any], indent: str = ""):
    f.write(f"{indent}class {name}:\n")
    if "_self" in node:
        f.write(f"{indent}    def __call__(self, *args: str) -> 'CommandResult': ...\n")
    children = node.get("children", {})
    if not children and "_self" not in node:
        f.write(f"{indent}    pass\n")
    for k, v in children.items():
        if v.get("type") == "group":
            write_stub_group(f, k, v, indent + "    ")
        else:
            f.write(f"{indent}    def {k}(self, *args: str) -> 'CommandResult': ...\n")

with open(STUB_FILE, "w", encoding="utf-8") as f:
    f.write(f"""# generated at {generated_at}
from __future__ import annotations
from typing import Any
from {OUTPUT_FILE[:-3]} import CommandResult

""")
    for name in sorted(TOP_LEVEL_COMMANDS.keys()):
        f.write(f"def {name}(*args: str) -> CommandResult: ...\n")
    f.write("\n")
    for group_name, group_node in GROUP_TREE.items():
        write_stub_group(f, group_name, group_node)

print(f"Generated {STUB_FILE}")
