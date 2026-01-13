from __future__ import annotations
# generated at 2026-01-12T23:59:35.148595+00:00

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
            print(f"Time: {elapsed:.6f}s")
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
            c = self._node.get("children", {}).get(name)
        if c:
            return _CommandNode(self._cli, node=c)
        raise AttributeError(name)


class CLI:
    def __init__(self):
        for name, t in {'arch': {'cmd': 'arch', 'preset_args': []}, 'awk': {'cmd': 'awk', 'preset_args': []}, 'b2sum': {'cmd': 'b2sum', 'preset_args': []}, 'base32': {'cmd': 'base32', 'preset_args': []}, 'base64': {'cmd': 'base64', 'preset_args': []}, 'basename': {'cmd': 'basename', 'preset_args': []}, 'basenc': {'cmd': 'basenc', 'preset_args': []}, 'bash': {'cmd': 'bash', 'preset_args': []}, 'bunzip2': {'cmd': 'bunzip2', 'preset_args': []}, 'bzcat': {'cmd': 'bzcat', 'preset_args': []}, 'bzip2': {'cmd': 'bzip2', 'preset_args': []}, 'bzip2recover': {'cmd': 'bzip2recover', 'preset_args': []}, 'captoinfo': {'cmd': 'captoinfo', 'preset_args': []}, 'cat': {'cmd': 'cat', 'preset_args': []}, 'chattr': {'cmd': 'chattr', 'preset_args': []}, 'chcon': {'cmd': 'chcon', 'preset_args': []}, 'chgrp': {'cmd': 'chgrp', 'preset_args': []}, 'chmod': {'cmd': 'chmod', 'preset_args': []}, 'chown': {'cmd': 'chown', 'preset_args': []}, 'chroot': {'cmd': 'chroot', 'preset_args': []}, 'cksum': {'cmd': 'cksum', 'preset_args': []}, 'clear': {'cmd': 'clear', 'preset_args': []}, 'cmp': {'cmd': 'cmp', 'preset_args': []}, 'column': {'cmd': 'column', 'preset_args': []}, 'comm': {'cmd': 'comm', 'preset_args': []}, 'cp': {'cmd': 'cp', 'preset_args': []}, 'csplit': {'cmd': 'csplit', 'preset_args': []}, 'cut': {'cmd': 'cut', 'preset_args': []}, 'cygcheck': {'cmd': 'cygcheck', 'preset_args': []}, 'cygpath': {'cmd': 'cygpath', 'preset_args': []}, 'cygwin_console_helper': {'cmd': 'cygwin-console-helper', 'preset_args': []}, 'd2u': {'cmd': 'd2u', 'preset_args': []}, 'dash': {'cmd': 'dash', 'preset_args': []}, 'date': {'cmd': 'date', 'preset_args': []}, 'dd': {'cmd': 'dd', 'preset_args': []}, 'df': {'cmd': 'df', 'preset_args': []}, 'diff': {'cmd': 'diff', 'preset_args': []}, 'diff3': {'cmd': 'diff3', 'preset_args': []}, 'dir': {'cmd': 'dir', 'preset_args': []}, 'dircolors': {'cmd': 'dircolors', 'preset_args': []}, 'dirmngr_client': {'cmd': 'dirmngr-client', 'preset_args': []}, 'dirmngr': {'cmd': 'dirmngr', 'preset_args': []}, 'dirname': {'cmd': 'dirname', 'preset_args': []}, 'dos2unix': {'cmd': 'dos2unix', 'preset_args': []}, 'du': {'cmd': 'du', 'preset_args': []}, 'dumpsexp': {'cmd': 'dumpsexp', 'preset_args': []}, 'echo': {'cmd': 'echo', 'preset_args': []}, 'env': {'cmd': 'env', 'preset_args': []}, 'ex': {'cmd': 'ex', 'preset_args': []}, 'expand': {'cmd': 'expand', 'preset_args': []}, 'expr': {'cmd': 'expr', 'preset_args': []}, 'factor': {'cmd': 'factor', 'preset_args': []}, 'false': {'cmd': 'false', 'preset_args': []}, 'file': {'cmd': 'file', 'preset_args': []}, 'find': {'cmd': 'find', 'preset_args': []}, 'fmt': {'cmd': 'fmt', 'preset_args': []}, 'fold': {'cmd': 'fold', 'preset_args': []}, 'funzip': {'cmd': 'funzip', 'preset_args': []}, 'gawk_5_0_0': {'cmd': 'gawk-5.0.0', 'preset_args': []}, 'gawk': {'cmd': 'gawk', 'preset_args': []}, 'gencat': {'cmd': 'gencat', 'preset_args': []}, 'getconf': {'cmd': 'getconf', 'preset_args': []}, 'getfacl': {'cmd': 'getfacl', 'preset_args': []}, 'getopt': {'cmd': 'getopt', 'preset_args': []}, 'gkill': {'cmd': 'gkill', 'preset_args': []}, 'gmondump': {'cmd': 'gmondump', 'preset_args': []}, 'gpg_agent': {'cmd': 'gpg-agent', 'preset_args': []}, 'gpg_card': {'cmd': 'gpg-card', 'preset_args': []}, 'gpg_connect_agent': {'cmd': 'gpg-connect-agent', 'preset_args': []}, 'gpg_error': {'cmd': 'gpg-error', 'preset_args': []}, 'gpg_mail_tube': {'cmd': 'gpg-mail-tube', 'preset_args': []}, 'gpg_wks_client': {'cmd': 'gpg-wks-client', 'preset_args': []}, 'gpg_wks_server': {'cmd': 'gpg-wks-server', 'preset_args': []}, 'gpg': {'cmd': 'gpg', 'preset_args': []}, 'gpgconf': {'cmd': 'gpgconf', 'preset_args': []}, 'gpgparsemail': {'cmd': 'gpgparsemail', 'preset_args': []}, 'gpgscm': {'cmd': 'gpgscm', 'preset_args': []}, 'gpgsm': {'cmd': 'gpgsm', 'preset_args': []}, 'gpgsplit': {'cmd': 'gpgsplit', 'preset_args': []}, 'gpgtar': {'cmd': 'gpgtar', 'preset_args': []}, 'gpgv': {'cmd': 'gpgv', 'preset_args': []}, 'grep': {'cmd': 'grep', 'preset_args': []}, 'groups': {'cmd': 'groups', 'preset_args': []}, 'gzip': {'cmd': 'gzip', 'preset_args': []}, 'head': {'cmd': 'head', 'preset_args': []}, 'hmac256': {'cmd': 'hmac256', 'preset_args': []}, 'hostid': {'cmd': 'hostid', 'preset_args': []}, 'hostname': {'cmd': 'hostname', 'preset_args': []}, 'iconv': {'cmd': 'iconv', 'preset_args': []}, 'id': {'cmd': 'id', 'preset_args': []}, 'infocmp': {'cmd': 'infocmp', 'preset_args': []}, 'infotocap': {'cmd': 'infotocap', 'preset_args': []}, 'install': {'cmd': 'install', 'preset_args': []}, 'join': {'cmd': 'join', 'preset_args': []}, 'kbxutil': {'cmd': 'kbxutil', 'preset_args': []}, 'kill': {'cmd': 'kill', 'preset_args': []}, 'ldd': {'cmd': 'ldd', 'preset_args': []}, 'ldh': {'cmd': 'ldh', 'preset_args': []}, 'less': {'cmd': 'less', 'preset_args': []}, 'lessecho': {'cmd': 'lessecho', 'preset_args': []}, 'lesskey': {'cmd': 'lesskey', 'preset_args': []}, 'link': {'cmd': 'link', 'preset_args': []}, 'ln': {'cmd': 'ln', 'preset_args': []}, 'locale': {'cmd': 'locale', 'preset_args': []}, 'locate': {'cmd': 'locate', 'preset_args': []}, 'logname': {'cmd': 'logname', 'preset_args': []}, 'ls': {'cmd': 'ls', 'preset_args': []}, 'lsattr': {'cmd': 'lsattr', 'preset_args': []}, 'mac2unix': {'cmd': 'mac2unix', 'preset_args': []}, 'md5sum': {'cmd': 'md5sum', 'preset_args': []}, 'minidumper': {'cmd': 'minidumper', 'preset_args': []}, 'mintty': {'cmd': 'mintty', 'preset_args': []}, 'mkdir': {'cmd': 'mkdir', 'preset_args': []}, 'mkfifo': {'cmd': 'mkfifo', 'preset_args': []}, 'mkgroup': {'cmd': 'mkgroup', 'preset_args': []}, 'mknod': {'cmd': 'mknod', 'preset_args': []}, 'mkpasswd': {'cmd': 'mkpasswd', 'preset_args': []}, 'mktemp': {'cmd': 'mktemp', 'preset_args': []}, 'mount': {'cmd': 'mount', 'preset_args': []}, 'mpicalc': {'cmd': 'mpicalc', 'preset_args': []}, 'mv': {'cmd': 'mv', 'preset_args': []}, 'nano': {'cmd': 'nano', 'preset_args': []}, 'nettle_hash': {'cmd': 'nettle-hash', 'preset_args': []}, 'nettle_lfib_stream': {'cmd': 'nettle-lfib-stream', 'preset_args': []}, 'nettle_pbkdf2': {'cmd': 'nettle-pbkdf2', 'preset_args': []}, 'newgrp': {'cmd': 'newgrp', 'preset_args': []}, 'nice': {'cmd': 'nice', 'preset_args': []}, 'nl': {'cmd': 'nl', 'preset_args': []}, 'nohup': {'cmd': 'nohup', 'preset_args': []}, 'nproc': {'cmd': 'nproc', 'preset_args': []}, 'numfmt': {'cmd': 'numfmt', 'preset_args': []}, 'od': {'cmd': 'od', 'preset_args': []}, 'openssl': {'cmd': 'openssl', 'preset_args': []}, 'p11_kit': {'cmd': 'p11-kit', 'preset_args': []}, 'passwd': {'cmd': 'passwd', 'preset_args': []}, 'paste': {'cmd': 'paste', 'preset_args': []}, 'patch': {'cmd': 'patch', 'preset_args': []}, 'pathchk': {'cmd': 'pathchk', 'preset_args': []}, 'perl': {'cmd': 'perl', 'preset_args': []}, 'perl5_38_2': {'cmd': 'perl5.38.2', 'preset_args': []}, 'pinentry_w32': {'cmd': 'pinentry-w32', 'preset_args': []}, 'pinentry': {'cmd': 'pinentry', 'preset_args': []}, 'pinky': {'cmd': 'pinky', 'preset_args': []}, 'pkcs1_conv': {'cmd': 'pkcs1-conv', 'preset_args': []}, 'pldd': {'cmd': 'pldd', 'preset_args': []}, 'pluginviewer': {'cmd': 'pluginviewer', 'preset_args': []}, 'pr': {'cmd': 'pr', 'preset_args': []}, 'printenv': {'cmd': 'printenv', 'preset_args': []}, 'printf': {'cmd': 'printf', 'preset_args': []}, 'profiler': {'cmd': 'profiler', 'preset_args': []}, 'ps': {'cmd': 'C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe', 'preset_args': []}, 'psl': {'cmd': 'psl', 'preset_args': []}, 'ptx': {'cmd': 'ptx', 'preset_args': []}, 'pwd': {'cmd': 'pwd', 'preset_args': []}, 'readlink': {'cmd': 'readlink', 'preset_args': []}, 'realpath': {'cmd': 'realpath', 'preset_args': []}, 'rebase': {'cmd': 'rebase', 'preset_args': []}, 'regtool': {'cmd': 'regtool', 'preset_args': []}, 'reset': {'cmd': 'reset', 'preset_args': []}, 'rm': {'cmd': 'rm', 'preset_args': []}, 'rmdir': {'cmd': 'rmdir', 'preset_args': []}, 'rnano': {'cmd': 'rnano', 'preset_args': []}, 'runcon': {'cmd': 'runcon', 'preset_args': []}, 'rview': {'cmd': 'rview', 'preset_args': []}, 'rvim': {'cmd': 'rvim', 'preset_args': []}, 'scp': {'cmd': 'scp', 'preset_args': []}, 'sdiff': {'cmd': 'sdiff', 'preset_args': []}, 'sed': {'cmd': 'sed', 'preset_args': []}, 'seq': {'cmd': 'seq', 'preset_args': []}, 'setfacl': {'cmd': 'setfacl', 'preset_args': []}, 'setmetamode': {'cmd': 'setmetamode', 'preset_args': []}, 'sexp_conv': {'cmd': 'sexp-conv', 'preset_args': []}, 'sftp': {'cmd': 'sftp', 'preset_args': []}, 'sh': {'cmd': 'sh', 'preset_args': []}, 'sha1sum': {'cmd': 'sha1sum', 'preset_args': []}, 'sha224sum': {'cmd': 'sha224sum', 'preset_args': []}, 'sha256sum': {'cmd': 'sha256sum', 'preset_args': []}, 'sha384sum': {'cmd': 'sha384sum', 'preset_args': []}, 'sha512sum': {'cmd': 'sha512sum', 'preset_args': []}, 'shred': {'cmd': 'shred', 'preset_args': []}, 'shuf': {'cmd': 'shuf', 'preset_args': []}, 'sleep': {'cmd': 'sleep', 'preset_args': []}, 'sort': {'cmd': 'sort', 'preset_args': []}, 'split': {'cmd': 'split', 'preset_args': []}, 'ssh_add': {'cmd': 'ssh-add', 'preset_args': []}, 'ssh_agent': {'cmd': 'ssh-agent', 'preset_args': []}, 'ssh_keygen': {'cmd': 'ssh-keygen', 'preset_args': []}, 'ssh_keyscan': {'cmd': 'ssh-keyscan', 'preset_args': []}, 'ssh_pageant': {'cmd': 'ssh-pageant', 'preset_args': []}, 'ssh': {'cmd': 'ssh', 'preset_args': []}, 'ssp': {'cmd': 'ssp', 'preset_args': []}, 'stat': {'cmd': 'stat', 'preset_args': []}, 'stdbuf': {'cmd': 'stdbuf', 'preset_args': []}, 'strace': {'cmd': 'strace', 'preset_args': []}, 'stty': {'cmd': 'stty', 'preset_args': []}, 'sum': {'cmd': 'sum', 'preset_args': []}, 'sync': {'cmd': 'sync', 'preset_args': []}, 'tabs': {'cmd': 'tabs', 'preset_args': []}, 'tac': {'cmd': 'tac', 'preset_args': []}, 'tail': {'cmd': 'tail', 'preset_args': []}, 'tar': {'cmd': 'tar', 'preset_args': []}, 'tee': {'cmd': 'tee', 'preset_args': []}, 'test': {'cmd': 'test', 'preset_args': []}, 'tic': {'cmd': 'tic', 'preset_args': []}, 'tig': {'cmd': 'tig', 'preset_args': []}, 'timeout': {'cmd': 'timeout', 'preset_args': []}, 'toe': {'cmd': 'toe', 'preset_args': []}, 'touch': {'cmd': 'touch', 'preset_args': []}, 'tput': {'cmd': 'tput', 'preset_args': []}, 'tr': {'cmd': 'tr', 'preset_args': []}, 'true': {'cmd': 'true', 'preset_args': []}, 'truncate': {'cmd': 'truncate', 'preset_args': []}, 'trust': {'cmd': 'trust', 'preset_args': []}, 'tset': {'cmd': 'tset', 'preset_args': []}, 'tsort': {'cmd': 'tsort', 'preset_args': []}, 'tty': {'cmd': 'tty', 'preset_args': []}, 'tzset': {'cmd': 'tzset', 'preset_args': []}, 'u2d': {'cmd': 'u2d', 'preset_args': []}, 'umount': {'cmd': 'umount', 'preset_args': []}, 'uname': {'cmd': 'uname', 'preset_args': []}, 'unexpand': {'cmd': 'unexpand', 'preset_args': []}, 'uniq': {'cmd': 'uniq', 'preset_args': []}, 'unix2dos': {'cmd': 'unix2dos', 'preset_args': []}, 'unix2mac': {'cmd': 'unix2mac', 'preset_args': []}, 'unlink': {'cmd': 'unlink', 'preset_args': []}, 'unzip': {'cmd': 'unzip', 'preset_args': []}, 'unzipsfx': {'cmd': 'unzipsfx', 'preset_args': []}, 'users': {'cmd': 'users', 'preset_args': []}, 'vdir': {'cmd': 'vdir', 'preset_args': []}, 'view': {'cmd': 'view', 'preset_args': []}, 'vim': {'cmd': 'vim', 'preset_args': []}, 'vimdiff': {'cmd': 'vimdiff', 'preset_args': []}, 'watchgnupg': {'cmd': 'watchgnupg', 'preset_args': []}, 'wc': {'cmd': 'wc', 'preset_args': []}, 'which': {'cmd': 'which', 'preset_args': []}, 'who': {'cmd': 'who', 'preset_args': []}, 'whoami': {'cmd': 'whoami', 'preset_args': []}, 'winpty_agent': {'cmd': 'winpty-agent', 'preset_args': []}, 'winpty_debugserver': {'cmd': 'winpty-debugserver', 'preset_args': []}, 'winpty': {'cmd': 'winpty', 'preset_args': []}, 'xargs': {'cmd': 'xargs', 'preset_args': []}, 'xxd': {'cmd': 'xxd', 'preset_args': []}, 'yat2m': {'cmd': 'yat2m', 'preset_args': []}, 'yes': {'cmd': 'yes', 'preset_args': []}, 'zipinfo': {'cmd': 'zipinfo', 'preset_args': []}, '_': {'cmd': '[', 'preset_args': []}, 'git': {'cmd': 'C:\\Program Files\\Git\\bin\\git.exe', 'preset_args': []}, 'cmd': {'cmd': 'C:\\Windows\\System32\\cmd.exe', 'preset_args': []}, 'powershell': {'cmd': 'C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe', 'preset_args': []}, 'es': {'cmd': 'C:\\Users\\nicho\\Documents\\Unreal Projects\\Starcel9\\Content\\CLITools\\ES-1.1.0.30.x64\\es.exe', 'preset_args': []}, 'search_system': {'cmd': 'C:\\Users\\nicho\\Documents\\Unreal Projects\\Starcel9\\Content\\CLITools\\ES-1.1.0.30.x64\\es.exe', 'preset_args': []}}.items():
            setattr(self, name, _CommandNode(self, cmd=t["cmd"], preset_args=t.get("preset_args", [])))
        for name, node in {'git': {'type': 'group', '_self': {'cmd': 'C:\\Program Files\\Git\\bin\\git.exe', 'preset_args': []}, 'children': {'status': {'type': 'group', '_self': {'cmd': 'C:\\Program Files\\Git\\bin\\git.exe', 'preset_args': ['status']}, 'children': {}}, 'commit': {'type': 'group', '_self': {'cmd': 'C:\\Program Files\\Git\\bin\\git.exe', 'preset_args': ['commit']}, 'children': {}}, 'push': {'type': 'group', '_self': {'cmd': 'C:\\Program Files\\Git\\bin\\git.exe', 'preset_args': ['push']}, 'children': {}}, 'pull': {'type': 'group', '_self': {'cmd': 'C:\\Program Files\\Git\\bin\\git.exe', 'preset_args': ['pull']}, 'children': {}}, 'pullrebase': {'type': 'group', '_self': {'cmd': 'C:\\Program Files\\Git\\bin\\git.exe', 'preset_args': ['pull', '--rebase']}, 'children': {}}, 'add': {'type': 'group', '_self': {'cmd': 'C:\\Program Files\\Git\\bin\\git.exe', 'preset_args': ['add']}, 'children': {}}}}}.items():
            setattr(self, name, _CommandNode(self, node=node))


_default_cli = CLI()
globals().update({k: getattr(_default_cli, k) for k in dir(_default_cli) if not k.startswith("_")})
