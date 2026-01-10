import os
import keyword
import re

BIN_DIR = r"C:\Program Files\Git\usr\bin"
OUTPUT_FILE = "cli.py"
# Add extra full-path executables
extra_exes = [
    r"C:\Program Files\Git\bin\git.exe",
    r"C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe",
    os.path.join(os.path.dirname(os.getcwd()), "CLITools", "ES-1.1.0.30.x64", "es.exe"),
]
# content_path = KismetSystemLibrary.GetProjectContentDirectory()
# "yt-dlp"
# "ffmpeg"

def is_exe(name: str) -> bool:
    return name.lower().endswith(".exe")


def sanitize(name: str) -> str:
    """
    Convert executable name to a valid Python method name.
    """
    name = name.replace("-", "_")
    name = re.sub(r"[^0-9a-zA-Z_]", "_", name)
    if name[0].isdigit():
        name = "_" + name
    if keyword.iskeyword(name):
        name += "_"
    return name


tools = {}
# Add standard usr/bin executables
for filename in os.listdir(BIN_DIR):
    if not is_exe(filename):
        continue

    cmd = filename[:-4]
    method = sanitize(cmd)

    if method in tools:
        method = f"{method}_cmd"

    if method in {"_"}:  # skip weird commands like '['
        continue

    tools[method] = cmd


for path in extra_exes:
    if not os.path.isfile(path):
        continue
    cmd = os.path.basename(path)[:-4]  # remove .exe
    method = sanitize(cmd)
    if method in tools:
        method = f"{method}_cmd"

    tools[method] = path  # store full path


with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
    f.write(f'''r"""
Auto-generated command wrappers.
Source directories: {BIN_DIR}
{extra_exes}
"""

from __future__ import annotations
import subprocess
import os
from dataclasses import dataclass
from typing import List


@dataclass
class CommandResult:
    stdout: str
    stderr: str
    returncode: int

    def __repr__(self):
        if self.stdout or self.stderr:
            lines = []
            if self.stdout:
                lines.append(self.stdout.rstrip())
            if self.stderr:
                lines.append(self.stderr.rstrip())
            return "\\n".join(lines)
        return "<No output>"


class CLI:
    _BIN_DIR = r"{BIN_DIR}"

    def __init__(self, cwd: str | None = None, env: dict | None = None):
        self.cwd = cwd
        self.env = env

    def _run(self, cmd: str, args: List[str], print_output: bool = True) -> CommandResult:
        exe = cmd if os.path.isabs(cmd) else os.path.join(self._BIN_DIR, cmd + ".exe")
        completed = subprocess.run(
            [exe, *args],
            cwd=self.cwd,
            env=self.env,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE
        )
        if print_output:
            if completed.stdout:
                print(completed.stdout, end="", flush=True)
            if completed.stderr:
                print(completed.stderr, end="", file=os.sys.stderr, flush=True)
        return CommandResult(
            stdout=completed.stdout,
            stderr=completed.stderr,
            returncode=completed.returncode
        )

    def run_pipeline(self, commands: List[List[str]], print_output: bool = True) -> CommandResult:
        if not commands:
            raise ValueError("No commands to run")

        procs = []
        prev_proc = None

        for cmd_args in commands:
            exe = cmd_args[0]
            exe_path = exe if os.path.isabs(exe) else os.path.join(self._BIN_DIR, exe + ".exe")
            args = [exe_path, *cmd_args[1:]]

            stdin = prev_proc.stdout if prev_proc else None
            proc = subprocess.Popen(
                args,
                stdin=stdin,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True
            )
            if prev_proc:
                prev_proc.stdout.close()
            prev_proc = proc
            procs.append(proc)

        stdout, stderr = procs[-1].communicate()

        if print_output:
            if stdout:
                print(stdout, end="", flush=True)
            if stderr:
                print(stderr, end="", file=os.sys.stderr, flush=True)

        return CommandResult(stdout=stdout, stderr=stderr, returncode=procs[-1].returncode)
''')

    methods_str = "\n".join(
        f"    def {method}(self, *args: str, print_output: bool = True) -> CommandResult:\n"
        f"        return self._run({repr(cmd)}, list(args), print_output=print_output)\n"
        for method, cmd in sorted(tools.items())
    )

    f.write(methods_str)
    f.write("\n\n__all__ = [\"CLI\", \"CommandResult\"]\n")

print(f"Generated {OUTPUT_FILE} with {len(tools)} methods.")
