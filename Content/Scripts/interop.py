# UNTESTED.
# I will work on this more at request. https://chatgpt.com/share/6973cc22-253c-800f-9696-056963926fed

# interop.py (3.9)
import sys, pickle, traceback, importlib, types
import numpy as np
from multiprocessing import shared_memory

legacy = importlib.import_module("legacy39")


def read_exact(n):
    buf = b""
    while len(buf) < n:
        chunk = sys.stdin.buffer.read(n - len(buf))
        if not chunk:
            return None
        buf += chunk
    return buf


while True:
    header = read_exact(8)
    if not header:
        break

    size = int.from_bytes(header, "big")
    payload = read_exact(size)
    msg = pickle.loads(payload)

    try:
        op = msg["op"]

        # normal calls (strings, small stuff)
        if op == "call":
            fn = getattr(legacy, msg["name"])
            result = fn(*msg["args"], **msg["kwargs"])

            data = pickle.dumps(("ok", result))
            sys.stdout.buffer.write(len(data).to_bytes(8, "big"))
            sys.stdout.buffer.write(data)

        # numpy calls
        elif op == "call_numpy":
            fn = getattr(legacy, msg["name"])

            shm = shared_memory.SharedMemory(name=msg["shm"])
            arr = np.ndarray(msg["shape"], dtype=np.dtype(msg["dtype"]), buffer=shm.buf)

            result = fn(arr)

            data = pickle.dumps(("ok", result))
            sys.stdout.buffer.write(len(data).to_bytes(8, "big"))
            sys.stdout.buffer.write(data)

        # hot reload
        elif op == "reload":
            legacy = importlib.reload(legacy)
            data = pickle.dumps(("ok", True))
            sys.stdout.buffer.write(len(data).to_bytes(8, "big"))
            sys.stdout.buffer.write(data)

    except Exception as e:
        data = pickle.dumps(("err", repr(e), traceback.format_exc()))
        sys.stdout.buffer.write(len(data).to_bytes(8, "big"))
        sys.stdout.buffer.write(data)

    sys.stdout.buffer.flush()


# legacy_proxy.py (Python 3.14 Proxy (fast + numpy aware))
# import subprocess, pickle, threading, asyncio, atexit
# import numpy as np
# from multiprocessing import shared_memory
#
#
# class LegacyError(Exception):
#     pass
#
#
# class LegacyProxy:
#     def __init__(self, py39_path, worker_path):
#         self.lock = threading.Lock()
#
#         self.p = subprocess.Popen(
#             [py39_path, worker_path],
#             stdin=subprocess.PIPE,
#             stdout=subprocess.PIPE,
#         )
#
#         atexit.register(self.close)
#
#     def close(self):
#         if self.p:
#             self.p.terminate()
#             self.p = None
#
#     def _read_exact(self, n):
#         buf = b""
#         while len(buf) < n:
#             buf += self.p.stdout.read(n - len(buf))
#         return buf
#
#     def _call(self, msg):
#         payload = pickle.dumps(msg)
#
#         with self.lock:
#             self.p.stdin.write(len(payload).to_bytes(8, "big"))
#             self.p.stdin.write(payload)
#             self.p.stdin.flush()
#
#             size = int.from_bytes(self._read_exact(8), "big")
#             data = self._read_exact(size)
#
#         return pickle.loads(data)
#
# # string / normal
#     def call(self, name, *args, **kwargs):
#         status, *rest = self._call({
#             "op": "call",
#             "name": name,
#             "args": args,
#             "kwargs": kwargs
#         })
#
#         if status == "ok":
#             return rest[0]
#         else:
#             msg, tb = rest
#             raise LegacyError(f"{msg}\n{tb}")
#
# # numpy
#     def call_numpy(self, name, arr: np.ndarray):
#         shm = shared_memory.SharedMemory(create=True, size=arr.nbytes)
#         shm_arr = np.ndarray(arr.shape, dtype=arr.dtype, buffer=shm.buf)
#         shm_arr[:] = arr
#
#         try:
#             status, *rest = self._call({
#                 "op": "call_numpy",
#                 "name": name,
#                 "shm": shm.name,
#                 "shape": arr.shape,
#                 "dtype": str(arr.dtype),
#             })
#         finally:
#             shm.close()
#             shm.unlink()
#
#         if status == "ok":
#             return rest[0]
#         else:
#             raise LegacyError(rest)
#
#     async def acall(self, name, *a, **k):
#         loop = asyncio.get_running_loop()
#         return await loop.run_in_executor(None, self.call, name, *a, **k)
#
#     def reload(self):
#         return self._call({"op": "reload"})
#
#     def __getattr__(self, name):
#         def f(*a, **k):
#             return self.call(name, *a, **k)
#
#         f.numpy = lambda arr: self.call_numpy(name, arr)
#         f.async_ = lambda *a, **k: self.acall(name, *a, **k)
#         return f





# UnrealEnginePython Interop
# # ue_actor.py  (Python 3.9 in Unreal)
# import unreal_engine as ue
# from legacy_proxy_client import BridgeClient
#
# class MyActor:
#
#     def begin_play(self):
#         ue.log("BeginPlay (3.9)")
#         self.bridge = BridgeClient()
#         self.bridge.call("on_begin_play")
#
#     def tick(self, delta_time):
#         self.bridge.call("on_tick", delta_time)

# # legacy_proxy_client.py (runs in Unreal 3.9)
# import socket, pickle
#
# class BridgeClient:
#     def __init__(self):
#         self.sock = socket.create_connection(("127.0.0.1", 5010))
#
#     def call(self, name, *args):
#         data = pickle.dumps((name, args))
#         self.sock.sendall(len(data).to_bytes(8, "big") + data)
#
#         size = int.from_bytes(self.sock.recv(8), "big")
#         return pickle.loads(self.sock.recv(size))

# # controller314.py
# import socket, pickle
#
# handlers = {}
#
# def on_begin_play():
#     print("BeginPlay in 3.14")
#
# def on_tick(dt):
#     print("Tick in 3.14:", dt)
#
# handlers["on_begin_play"] = on_begin_play
# handlers["on_tick"] = on_tick
#
#
# sock = socket.socket()
# sock.bind(("127.0.0.1", 5010))
# sock.listen(1)
#
# conn, _ = sock.accept()
#
# while True:
#     size = int.from_bytes(conn.recv(8), "big")
#     data = conn.recv(size)
#     name, args = pickle.loads(data)
#
#     result = handlers[name](*args)
#
#     payload = pickle.dumps(result)
#     conn.sendall(len(payload).to_bytes(8, "big") + payload)



# # bridge_client.py (3.9)
# import socket, pickle
#
# class BridgeClient:
#     def __init__(self):
#         self.sock = socket.create_connection(("127.0.0.1", 6000))
#
#     def call(self, name, *args):
#         payload = pickle.dumps((name, args))
#         self.sock.sendall(len(payload).to_bytes(8, "big") + payload)
#
#         size = int.from_bytes(self.sock.recv(8), "big")
#         return pickle.loads(self.sock.recv(size))
#

# # ue_override.py (Global hook installer (3.9))
# import inspect
# from bridge_client import BridgeClient
#
# bridge = BridgeClient()
#
#
# def install_override(cls):
#     if hasattr(cls, "begin_play"):
#         orig = cls.begin_play
#
#         def begin_play_wrap(self, *a, **k):
#             bridge.call(f"{cls.__name__}.begin_play", self.__dict__)
#             return orig(self, *a, **k)
#
#         cls.begin_play = begin_play_wrap
#
#     if hasattr(cls, "tick"):
#         orig = cls.tick
#
#         def tick_wrap(self, dt):
#             bridge.call(f"{cls.__name__}.tick", dt, self.__dict__)
#             return orig(self, dt)
#
#         cls.tick = tick_wrap
#
#
# def install_module(module):
#     for _, obj in inspect.getmembers(module, inspect.isclass):
#         install_override(obj)
#

# import my_actor
# from ue_override import install_module
#
# install_module(my_actor)

# # controller314.py
# import socket, pickle
#
# def handle(name, *args):
#     print("314 override:", name, args)
#
# sock = socket.socket()
# sock.bind(("127.0.0.1", 6000))
# sock.listen(1)
#
# conn, _ = sock.accept()
#
# while True:
#     size = int.from_bytes(conn.recv(8), "big")
#     data = conn.recv(size)
#     name, args = pickle.loads(data)
#     handle(name, *args)
#     conn.sendall(len(pickle.dumps(None)).to_bytes(8, "big") + pickle.dumps(None))

# bridge.call(...)   # blocking every tick
# bridge.push_state(mesh_data)
# bridge.poll_results()

# def tick(self, dt):
#     bridge.send_mesh(self.mesh)
#     result = bridge.try_recv()
#     if result:
#         self.apply(result)
