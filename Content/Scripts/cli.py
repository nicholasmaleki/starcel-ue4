from __future__ import annotations
# generated at 2026-05-09T17:19:21.702020+00:00
# debug mode: False

import os
import sys
import subprocess
import json
import time
from typing import List

INTERACTIVE_COMMANDS = {"ps", "cmd", "powershell"}

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
        print(f"Time: {elapsed:.6f}s")
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
    def __init__(self, cli, node=None, cmd=None, preset_args=None, arg_prefix="", arg_suffix="", no_window=False):
        object.__setattr__(self, '_cli', cli)
        object.__setattr__(self, '_node', node)
        object.__setattr__(self, '_cmd', cmd)
        object.__setattr__(self, '_preset_args', preset_args or [])
        object.__setattr__(self, '_arg_prefix', arg_prefix)
        object.__setattr__(self, '_arg_suffix', arg_suffix)
        object.__setattr__(self, '_no_window', no_window)

    def _debug(self, label, **kwargs):
        pass

    def __call__(self, *args):
        if self._node and "_self" in self._node:
            cmd = self._node["_self"]["cmd"]
            args_list = self._node["_self"].get("preset_args", []) + list(args)
            self._debug("node call", cmd=cmd, preset_args=self._node["_self"].get("preset_args", []), user_args=list(args))
        elif self._cmd:
            cmd = self._cmd
            args_list = self._preset_args + list(args)
            self._debug("cmd call", cmd=cmd, preset_args=self._preset_args, user_args=list(args))
        else:
            raise TypeError("This node is a group")

        self._debug("args before prefix/suffix", args_list=args_list, arg_prefix=self._arg_prefix, arg_suffix=self._arg_suffix)

        if self._arg_prefix or self._arg_suffix:
            skip_next = False
            prefix_idx = None
            for i, a in enumerate(args_list):
                if skip_next:
                    skip_next = False
                    continue
                if a.startswith('--'):
                    skip_next = True
                    continue
                if a.startswith('-') and len(a) == 2:
                    continue
                if a.startswith('-'):
                    skip_next = True
                    continue
                prefix_idx = i
                break
            if prefix_idx is not None:
                target = args_list[prefix_idx]
                args_list = args_list[:prefix_idx] + [self._arg_prefix + target + self._arg_suffix] + args_list[prefix_idx+1:]
            else:
                args_list = args_list + [self._arg_prefix + self._arg_suffix]

        self._debug("final command", full_cmd=[cmd] + list(args_list), no_window=self._no_window)

        start = time.perf_counter()
        exe_name = os.path.basename(cmd).lower()
        flags = subprocess.CREATE_NO_WINDOW if self._no_window else 0

        # Interactive commands — still hidden unless no_window is explicitly False
        if exe_name in INTERACTIVE_COMMANDS:
            return_code = subprocess.run([cmd] + list(args_list),
                                         creationflags=flags).returncode
            elapsed = time.perf_counter() - start
            print(f"Time: {elapsed:.6f}s")
            return CommandResult("", "", return_code)
        else:
            p = subprocess.run([cmd] + list(args_list), text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, creationflags=flags)
            elapsed = time.perf_counter() - start
            self._debug("result", returncode=p.returncode, elapsed=elapsed, stdout_len=len(p.stdout or ""), stderr_len=len(p.stderr or ""))
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
            c = self._node.get("children", {}).get(name)
        if c:
            return _CommandNode(self._cli, node=c)
        raise AttributeError(name)


class CLI:
    def __init__(self):
        for name, t in {'cmd': {'cmd': 'C:\\Windows\\System32\\cmd.exe', 'preset_args': [], 'arg_prefix': '', 'arg_suffix': '', 'no_window': True}, 'powershell': {'cmd': 'C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe', 'preset_args': [], 'arg_prefix': '', 'arg_suffix': '', 'no_window': True}, 'es': {'cmd': 'C:\\Users\\nicho\\Documents\\Unreal Projects\\Starcel9\\Content\\CLITools\\ES-1.1.0.30.x64\\es.exe', 'preset_args': [], 'arg_prefix': '', 'arg_suffix': '', 'no_window': True}, 'bash': {'cmd': 'C:\\Program Files\\Git\\usr\\bin\\bash.exe', 'preset_args': [], 'arg_prefix': '', 'arg_suffix': '', 'no_window': True}, 'ps': {'cmd': 'C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe', 'preset_args': [], 'arg_prefix': '', 'arg_suffix': '', 'no_window': False}, 'search_system': {'cmd': 'C:\\Users\\nicho\\Documents\\Unreal Projects\\Starcel9\\Content\\CLITools\\ES-1.1.0.30.x64\\es.exe', 'preset_args': [], 'arg_prefix': '', 'arg_suffix': '', 'no_window': False}}.items():
            setattr(self, name, _CommandNode(self, cmd=t["cmd"], preset_args=t.get("preset_args", []), arg_prefix=t.get("arg_prefix", ""), arg_suffix=t.get("arg_suffix", ""), no_window=t.get("no_window", False)))
        for name, node in {}.items():
            setattr(self, name, _CommandNode(self, node=node))


_default_cli = CLI()
globals().update({k: getattr(_default_cli, k) for k in dir(_default_cli) if not k.startswith("_")})
