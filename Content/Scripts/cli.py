r"""
Auto-generated command wrappers.
Source directories: C:\Program Files\Git\usr\bin
['C:\\Program Files\\Git\\bin\\git.exe', 'C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe', 'C:\\Users\\nicho\\Documents\\Unreal Projects\\Starcel9\\Content\\CLITools\\ES-1.1.0.30.x64\\es.exe']
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
            return "\n".join(lines)
        return "<No output>"


class CLI:
    _BIN_DIR = r"C:\Program Files\Git\usr\bin"

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
    def arch(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('arch', list(args), print_output=print_output)

    def awk(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('awk', list(args), print_output=print_output)

    def b2sum(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('b2sum', list(args), print_output=print_output)

    def base32(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('base32', list(args), print_output=print_output)

    def base64(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('base64', list(args), print_output=print_output)

    def basename(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('basename', list(args), print_output=print_output)

    def basenc(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('basenc', list(args), print_output=print_output)

    def bash(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('bash', list(args), print_output=print_output)

    def bunzip2(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('bunzip2', list(args), print_output=print_output)

    def bzcat(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('bzcat', list(args), print_output=print_output)

    def bzip2(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('bzip2', list(args), print_output=print_output)

    def bzip2recover(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('bzip2recover', list(args), print_output=print_output)

    def captoinfo(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('captoinfo', list(args), print_output=print_output)

    def cat(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('cat', list(args), print_output=print_output)

    def chattr(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('chattr', list(args), print_output=print_output)

    def chcon(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('chcon', list(args), print_output=print_output)

    def chgrp(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('chgrp', list(args), print_output=print_output)

    def chmod(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('chmod', list(args), print_output=print_output)

    def chown(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('chown', list(args), print_output=print_output)

    def chroot(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('chroot', list(args), print_output=print_output)

    def cksum(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('cksum', list(args), print_output=print_output)

    def clear(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('clear', list(args), print_output=print_output)

    def cmp(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('cmp', list(args), print_output=print_output)

    def column(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('column', list(args), print_output=print_output)

    def comm(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('comm', list(args), print_output=print_output)

    def cp(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('cp', list(args), print_output=print_output)

    def csplit(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('csplit', list(args), print_output=print_output)

    def cut(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('cut', list(args), print_output=print_output)

    def cygcheck(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('cygcheck', list(args), print_output=print_output)

    def cygpath(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('cygpath', list(args), print_output=print_output)

    def cygwin_console_helper(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('cygwin-console-helper', list(args), print_output=print_output)

    def d2u(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('d2u', list(args), print_output=print_output)

    def dash(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('dash', list(args), print_output=print_output)

    def date(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('date', list(args), print_output=print_output)

    def dd(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('dd', list(args), print_output=print_output)

    def df(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('df', list(args), print_output=print_output)

    def diff(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('diff', list(args), print_output=print_output)

    def diff3(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('diff3', list(args), print_output=print_output)

    def dir(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('dir', list(args), print_output=print_output)

    def dircolors(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('dircolors', list(args), print_output=print_output)

    def dirmngr(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('dirmngr', list(args), print_output=print_output)

    def dirmngr_client(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('dirmngr-client', list(args), print_output=print_output)

    def dirname(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('dirname', list(args), print_output=print_output)

    def dos2unix(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('dos2unix', list(args), print_output=print_output)

    def du(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('du', list(args), print_output=print_output)

    def dumpsexp(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('dumpsexp', list(args), print_output=print_output)

    def echo(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('echo', list(args), print_output=print_output)

    def env(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('env', list(args), print_output=print_output)

    def es(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('C:\\Users\\nicho\\Documents\\Unreal Projects\\Starcel9\\Content\\CLITools\\ES-1.1.0.30.x64\\es.exe', list(args), print_output=print_output)

    def ex(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('ex', list(args), print_output=print_output)

    def expand(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('expand', list(args), print_output=print_output)

    def expr(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('expr', list(args), print_output=print_output)

    def factor(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('factor', list(args), print_output=print_output)

    def false(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('false', list(args), print_output=print_output)

    def file(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('file', list(args), print_output=print_output)

    def find(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('find', list(args), print_output=print_output)

    def fmt(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('fmt', list(args), print_output=print_output)

    def fold(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('fold', list(args), print_output=print_output)

    def funzip(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('funzip', list(args), print_output=print_output)

    def gawk(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('gawk', list(args), print_output=print_output)

    def gawk_5_0_0(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('gawk-5.0.0', list(args), print_output=print_output)

    def gencat(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('gencat', list(args), print_output=print_output)

    def getconf(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('getconf', list(args), print_output=print_output)

    def getfacl(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('getfacl', list(args), print_output=print_output)

    def getopt(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('getopt', list(args), print_output=print_output)

    def git(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('C:\\Program Files\\Git\\bin\\git.exe', list(args), print_output=print_output)

    def gkill(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('gkill', list(args), print_output=print_output)

    def gmondump(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('gmondump', list(args), print_output=print_output)

    def gpg(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('gpg', list(args), print_output=print_output)

    def gpg_agent(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('gpg-agent', list(args), print_output=print_output)

    def gpg_card(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('gpg-card', list(args), print_output=print_output)

    def gpg_connect_agent(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('gpg-connect-agent', list(args), print_output=print_output)

    def gpg_error(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('gpg-error', list(args), print_output=print_output)

    def gpg_mail_tube(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('gpg-mail-tube', list(args), print_output=print_output)

    def gpg_wks_client(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('gpg-wks-client', list(args), print_output=print_output)

    def gpg_wks_server(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('gpg-wks-server', list(args), print_output=print_output)

    def gpgconf(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('gpgconf', list(args), print_output=print_output)

    def gpgparsemail(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('gpgparsemail', list(args), print_output=print_output)

    def gpgscm(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('gpgscm', list(args), print_output=print_output)

    def gpgsm(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('gpgsm', list(args), print_output=print_output)

    def gpgsplit(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('gpgsplit', list(args), print_output=print_output)

    def gpgtar(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('gpgtar', list(args), print_output=print_output)

    def gpgv(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('gpgv', list(args), print_output=print_output)

    def grep(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('grep', list(args), print_output=print_output)

    def groups(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('groups', list(args), print_output=print_output)

    def gzip(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('gzip', list(args), print_output=print_output)

    def head(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('head', list(args), print_output=print_output)

    def hmac256(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('hmac256', list(args), print_output=print_output)

    def hostid(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('hostid', list(args), print_output=print_output)

    def hostname(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('hostname', list(args), print_output=print_output)

    def iconv(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('iconv', list(args), print_output=print_output)

    def id(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('id', list(args), print_output=print_output)

    def infocmp(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('infocmp', list(args), print_output=print_output)

    def infotocap(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('infotocap', list(args), print_output=print_output)

    def install(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('install', list(args), print_output=print_output)

    def join(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('join', list(args), print_output=print_output)

    def kbxutil(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('kbxutil', list(args), print_output=print_output)

    def kill(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('kill', list(args), print_output=print_output)

    def ldd(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('ldd', list(args), print_output=print_output)

    def ldh(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('ldh', list(args), print_output=print_output)

    def less(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('less', list(args), print_output=print_output)

    def lessecho(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('lessecho', list(args), print_output=print_output)

    def lesskey(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('lesskey', list(args), print_output=print_output)

    def link(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('link', list(args), print_output=print_output)

    def ln(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('ln', list(args), print_output=print_output)

    def locale(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('locale', list(args), print_output=print_output)

    def locate(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('locate', list(args), print_output=print_output)

    def logname(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('logname', list(args), print_output=print_output)

    def ls(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('ls', list(args), print_output=print_output)

    def lsattr(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('lsattr', list(args), print_output=print_output)

    def mac2unix(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('mac2unix', list(args), print_output=print_output)

    def md5sum(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('md5sum', list(args), print_output=print_output)

    def minidumper(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('minidumper', list(args), print_output=print_output)

    def mintty(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('mintty', list(args), print_output=print_output)

    def mkdir(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('mkdir', list(args), print_output=print_output)

    def mkfifo(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('mkfifo', list(args), print_output=print_output)

    def mkgroup(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('mkgroup', list(args), print_output=print_output)

    def mknod(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('mknod', list(args), print_output=print_output)

    def mkpasswd(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('mkpasswd', list(args), print_output=print_output)

    def mktemp(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('mktemp', list(args), print_output=print_output)

    def mount(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('mount', list(args), print_output=print_output)

    def mpicalc(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('mpicalc', list(args), print_output=print_output)

    def mv(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('mv', list(args), print_output=print_output)

    def nano(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('nano', list(args), print_output=print_output)

    def nettle_hash(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('nettle-hash', list(args), print_output=print_output)

    def nettle_lfib_stream(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('nettle-lfib-stream', list(args), print_output=print_output)

    def nettle_pbkdf2(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('nettle-pbkdf2', list(args), print_output=print_output)

    def newgrp(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('newgrp', list(args), print_output=print_output)

    def nice(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('nice', list(args), print_output=print_output)

    def nl(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('nl', list(args), print_output=print_output)

    def nohup(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('nohup', list(args), print_output=print_output)

    def nproc(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('nproc', list(args), print_output=print_output)

    def numfmt(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('numfmt', list(args), print_output=print_output)

    def od(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('od', list(args), print_output=print_output)

    def openssl(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('openssl', list(args), print_output=print_output)

    def p11_kit(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('p11-kit', list(args), print_output=print_output)

    def passwd(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('passwd', list(args), print_output=print_output)

    def paste(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('paste', list(args), print_output=print_output)

    def patch(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('patch', list(args), print_output=print_output)

    def pathchk(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('pathchk', list(args), print_output=print_output)

    def perl(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('perl', list(args), print_output=print_output)

    def perl5_38_2(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('perl5.38.2', list(args), print_output=print_output)

    def pinentry(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('pinentry', list(args), print_output=print_output)

    def pinentry_w32(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('pinentry-w32', list(args), print_output=print_output)

    def pinky(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('pinky', list(args), print_output=print_output)

    def pkcs1_conv(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('pkcs1-conv', list(args), print_output=print_output)

    def pldd(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('pldd', list(args), print_output=print_output)

    def pluginviewer(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('pluginviewer', list(args), print_output=print_output)

    def powershell(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe', list(args), print_output=print_output)

    def pr(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('pr', list(args), print_output=print_output)

    def printenv(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('printenv', list(args), print_output=print_output)

    def printf(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('printf', list(args), print_output=print_output)

    def profiler(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('profiler', list(args), print_output=print_output)

    def ps(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('ps', list(args), print_output=print_output)

    def psl(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('psl', list(args), print_output=print_output)

    def ptx(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('ptx', list(args), print_output=print_output)

    def pwd(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('pwd', list(args), print_output=print_output)

    def readlink(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('readlink', list(args), print_output=print_output)

    def realpath(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('realpath', list(args), print_output=print_output)

    def rebase(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('rebase', list(args), print_output=print_output)

    def regtool(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('regtool', list(args), print_output=print_output)

    def reset(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('reset', list(args), print_output=print_output)

    def rm(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('rm', list(args), print_output=print_output)

    def rmdir(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('rmdir', list(args), print_output=print_output)

    def rnano(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('rnano', list(args), print_output=print_output)

    def runcon(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('runcon', list(args), print_output=print_output)

    def rview(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('rview', list(args), print_output=print_output)

    def rvim(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('rvim', list(args), print_output=print_output)

    def scp(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('scp', list(args), print_output=print_output)

    def sdiff(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('sdiff', list(args), print_output=print_output)

    def sed(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('sed', list(args), print_output=print_output)

    def seq(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('seq', list(args), print_output=print_output)

    def setfacl(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('setfacl', list(args), print_output=print_output)

    def setmetamode(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('setmetamode', list(args), print_output=print_output)

    def sexp_conv(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('sexp-conv', list(args), print_output=print_output)

    def sftp(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('sftp', list(args), print_output=print_output)

    def sh(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('sh', list(args), print_output=print_output)

    def sha1sum(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('sha1sum', list(args), print_output=print_output)

    def sha224sum(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('sha224sum', list(args), print_output=print_output)

    def sha256sum(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('sha256sum', list(args), print_output=print_output)

    def sha384sum(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('sha384sum', list(args), print_output=print_output)

    def sha512sum(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('sha512sum', list(args), print_output=print_output)

    def shred(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('shred', list(args), print_output=print_output)

    def shuf(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('shuf', list(args), print_output=print_output)

    def sleep(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('sleep', list(args), print_output=print_output)

    def sort(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('sort', list(args), print_output=print_output)

    def split(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('split', list(args), print_output=print_output)

    def ssh(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('ssh', list(args), print_output=print_output)

    def ssh_add(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('ssh-add', list(args), print_output=print_output)

    def ssh_agent(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('ssh-agent', list(args), print_output=print_output)

    def ssh_keygen(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('ssh-keygen', list(args), print_output=print_output)

    def ssh_keyscan(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('ssh-keyscan', list(args), print_output=print_output)

    def ssh_pageant(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('ssh-pageant', list(args), print_output=print_output)

    def ssp(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('ssp', list(args), print_output=print_output)

    def stat(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('stat', list(args), print_output=print_output)

    def stdbuf(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('stdbuf', list(args), print_output=print_output)

    def strace(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('strace', list(args), print_output=print_output)

    def stty(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('stty', list(args), print_output=print_output)

    def sum(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('sum', list(args), print_output=print_output)

    def sync(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('sync', list(args), print_output=print_output)

    def tabs(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('tabs', list(args), print_output=print_output)

    def tac(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('tac', list(args), print_output=print_output)

    def tail(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('tail', list(args), print_output=print_output)

    def tar(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('tar', list(args), print_output=print_output)

    def tee(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('tee', list(args), print_output=print_output)

    def test(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('test', list(args), print_output=print_output)

    def tic(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('tic', list(args), print_output=print_output)

    def tig(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('tig', list(args), print_output=print_output)

    def timeout(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('timeout', list(args), print_output=print_output)

    def toe(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('toe', list(args), print_output=print_output)

    def touch(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('touch', list(args), print_output=print_output)

    def tput(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('tput', list(args), print_output=print_output)

    def tr(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('tr', list(args), print_output=print_output)

    def true(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('true', list(args), print_output=print_output)

    def truncate(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('truncate', list(args), print_output=print_output)

    def trust(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('trust', list(args), print_output=print_output)

    def tset(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('tset', list(args), print_output=print_output)

    def tsort(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('tsort', list(args), print_output=print_output)

    def tty(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('tty', list(args), print_output=print_output)

    def tzset(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('tzset', list(args), print_output=print_output)

    def u2d(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('u2d', list(args), print_output=print_output)

    def umount(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('umount', list(args), print_output=print_output)

    def uname(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('uname', list(args), print_output=print_output)

    def unexpand(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('unexpand', list(args), print_output=print_output)

    def uniq(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('uniq', list(args), print_output=print_output)

    def unix2dos(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('unix2dos', list(args), print_output=print_output)

    def unix2mac(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('unix2mac', list(args), print_output=print_output)

    def unlink(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('unlink', list(args), print_output=print_output)

    def unzip(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('unzip', list(args), print_output=print_output)

    def unzipsfx(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('unzipsfx', list(args), print_output=print_output)

    def users(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('users', list(args), print_output=print_output)

    def vdir(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('vdir', list(args), print_output=print_output)

    def view(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('view', list(args), print_output=print_output)

    def vim(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('vim', list(args), print_output=print_output)

    def vimdiff(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('vimdiff', list(args), print_output=print_output)

    def watchgnupg(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('watchgnupg', list(args), print_output=print_output)

    def wc(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('wc', list(args), print_output=print_output)

    def which(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('which', list(args), print_output=print_output)

    def who(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('who', list(args), print_output=print_output)

    def whoami(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('whoami', list(args), print_output=print_output)

    def winpty(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('winpty', list(args), print_output=print_output)

    def winpty_agent(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('winpty-agent', list(args), print_output=print_output)

    def winpty_debugserver(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('winpty-debugserver', list(args), print_output=print_output)

    def xargs(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('xargs', list(args), print_output=print_output)

    def xxd(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('xxd', list(args), print_output=print_output)

    def yat2m(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('yat2m', list(args), print_output=print_output)

    def yes(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('yes', list(args), print_output=print_output)

    def zipinfo(self, *args: str, print_output: bool = True) -> CommandResult:
        return self._run('zipinfo', list(args), print_output=print_output)


__all__ = ["CLI", "CommandResult"]
