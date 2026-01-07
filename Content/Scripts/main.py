import unreal_engine as ue
import numpy as np
import os, sys, subprocess, urllib.request, socket, math, sympy, cmdix, fast_autocomplete, numba, kingdon, dill #numba_cuda
from unreal_engine import FVector, FRotator, FTransform, FHitResult, CLASS_CONFIG, CLASS_DEFAULT_CONFIG, CPF_CONFIG, CPF_GLOBAL_CONFIG, CPF_EXPOSE_ON_SPAWN, CPF_NET, CPF_REP_NOTIFY
from unreal_engine.classes import Actor, Character, PlayerController, KismetMathLibrary, KismetSystemLibrary, Object, StrProperty, IntProperty
from unreal_engine.enums import EInputEvent, ETraceTypeQuery, EDrawDebugTrace
from constants import Constants, WorldSize

ue.log('Hello i am a Python module')

#use instanced static meshes for the gridlines
# def write(self, buf):
#     if not buf:
#         return
#     try:
#         text = str(buf)
#     except Exception:
#         text = "<unprintable>"
#         self.logger(text)
#
# if (!PyArg_ParseTuple(args, "0:log", &py_message) || !py_message))
# {
#     return PyErr_Format(PyExc_TypeError, "log() received invalid message");
# }
class Axis:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    def swap_axis(self, input):
        input[0] = input[1]
        # for i in range(input[0]):
        #     input[0][i] = input[1][i]
        return [input[1],input[0]]

    def setup_axis(self):
        default_16d_axis = ["x", "y", "z", "w", "v", "u", "t", "s", "r", "q", "p", "o", "n", "m", "l", "k"]

        default_3d_axis = default_16d_axis[:3] # 48 possible orientations for the 3 axis and their negatives in orthogonal(90 degree) space. 3! * 2^3
        default_0d_axis = 0 # or [] # 1 orientation in nD
        default_1d_axis = default_16d_axis[:1] # 2 in 1d. 4 in 2d. 12 in 3D
        default_2d_axis = default_16d_axis[:2] # 8 in 2d. 24 in 3D
        default_4d_axis = default_16d_axis[:4] # 384 possible orientations for the 4 axis and their negatives in orthogonal(90 degree) space. 4! * 2^4

        unreal_default_axis = default_3d_axis # on start, unreal has z up, y right, and x away from camera
        unreal_default_walltable_axis = [unreal_default_axis[1], -unreal_default_axis[2], unreal_default_axis[0]] # best for 2D and 3D tables on screens
        unreal_default_groundtable_axis = [unreal_default_axis[1], -unreal_default_axis[0], -unreal_default_axis[2]]
        unreal_default_groundtable_axis_zup = [unreal_default_axis[1], -unreal_default_axis[0], unreal_default_axis[2]]
        unreal_default_wallgraph_axis = [unreal_default_axis[1], unreal_default_axis[2], unreal_default_axis[0]] # usually used for 2D graphs on screens. not usually used in 3D
        unreal_default_groundgraph_axis = [unreal_default_axis[1], unreal_default_axis[0], unreal_default_axis[2]]
        self.swap_axis()

class Table:
    def __init__(self, table, axis=["x","y","z","w"]):
        self.table = table
        self.axis = axis


    def create_letter_labels(self, default_letter_axis='x'): # or default_label_target_dimension
        pass
        # X(A1) -> default_letter_axis(A1) -> A1
        # Y(A1)

    def test_multidimensional_table(self):
        def setup_lengths(lengths):
            for i in range(len(lengths)):
                (lengths[i][0], lengths[i][1])

            xlen = lengths[0]
            ylen = lengths[1]
            zlen = lengths[2]
            wlen = lengths[3]

    def array_setup(self):
        custom_table_labels = ["ha","haha","hahaha"]
        custom_table_lettering = [["ha",["bla", "blablabla", "blablabla"]],["haha", ["ja","jaja","jajaja"]]]
        nozero=["x", "y"]
        letter_start_offset=[["x",1],["y",-1]]

        # Create a 3D array of shape (2, 2, 3) - 2 "pages", each with 2 rows and 3 columns
        arr_3d = np.array([
            [[1, 2, 3], [4, 5, 6]],
            [[7, 8, 9], [10, 11, 12]]
        ])

        print(arr_3d)
        print(f"Shape: {arr_3d.shape}")
        print(f"Dimensions (ndim): {arr_3d.ndim}")


class Main:
    def test_kingdon(self):
        from kingdon import Algebra
        alg = Algebra(3, 0, 1)
        locals().update(alg.blades)
        b = alg.bivector(name='b')
        ue.log(b)

    def test_cylinder(self):
        point1 = FVector(0, 0, 0)
        point2 = FVector(100, 100, 100)
        direction_vector = point2 - point1
        midpoint = (point1 + point2) / 2
        print(midpoint)

        normalized_direction_vector = direction_vector / direction_vector.length()
        print(normalized_direction_vector)
        normalized_direction_vector = direction_vector.normalized()
        print(normalized_direction_vector)

        default_axis = FVector(0, 0, 1)

        rotation_axis = default_axis.cross(normalized_direction_vector)

        print(rotation_axis)

        rotation_angle = math.degrees(math.acos(default_axis.dot(normalized_direction_vector)))

        print(rotation_angle)

        print(KismetMathLibrary.RotatorFromAxisAndAngle(rotation_axis, rotation_angle))  # returns FRotator

        print(KismetMathLibrary.FindLookAtRotation(point1, point2))  # returns FRotator

    # # this event will be run on the server and in reliable mode
    # def server_event(self):
    #     ue.log('server event called')
    #     ue.log("hello from server")
    #     print("hello from server" + self.uobject.get_uproperty('StringHelloWorldProperty'))
    #     print("hello from server" + self.uobject.get_uproperty(
    #         'StringHelloWorldProperty2'))  # .set_metadata('Category', 'CategoryTest001')
    # server_event.event = True # expose event
    # server_event.server = True
    # server_event.reliable = True
    # server_event.multicast = True # you can also simulate multicast like below:
    # server_event.static = True # static methods will be available to blueprints
    # server_event.pure = True # pure methods will be available to blueprints

    # FooWorld = [IntProperty]
    # FooWorld = [17, 22, 30]

    # ------------------------------------------------------------
    # MULTICAST FLAG TEST
    # ------------------------------------------------------------
    def test_multicast_flag(self, msg):
        """
        If .multicast works, this should run on:
        - Dedicated Server
        - All connected Clients

        In practice (UE4Python), this usually runs server-only.
        """
        if KismetSystemLibrary.IsDedicatedServer():
            ue.log(f"[multicast flag] SERVER executed: {msg}")
        else:
            ue.log(f"[multicast flag] CLIENT executed: {msg}")

    # Register as RPC
    test_multicast_flag.event = True
    test_multicast_flag.multicast = True
    test_multicast_flag.reliable = True

    # ------------------------------------------------------------
    # SERVER RPC – MANUAL MULTICAST
    # ------------------------------------------------------------
    def server_manual_multicast(self, msg):
        """
        Authoritative server RPC.
        Explicitly calls a client RPC on every PlayerController.
        """
        ue.log("[manual multicast] SERVER executing")

        for pc in self.uobject.get_world().all_actors():
            if pc:
                pc.client_receive_manual(msg)

    # Register as Server RPC
    server_manual_multicast.event = True
    server_manual_multicast.server = True
    server_manual_multicast.reliable = True

    # ------------------------------------------------------------
    # CLIENT RPC – MANUAL MULTICAST TARGET
    # ------------------------------------------------------------
    def client_receive_manual(self, msg):
        """
        Should only ever run on clients.
        """
        if KismetSystemLibrary.IsDedicatedServer():
            ue.log("[manual multicast] ERROR: executed on server")
        else:
            ue.log(f"[manual multicast] CLIENT executed: {msg}")

    # Register as Client RPC
    client_receive_manual.event = True
    client_receive_manual.client = True
    client_receive_manual.reliable = True

    # this is called on game start
    def begin_play(self):
        ue.log('Begin Play on Main class')

        if KismetSystemLibrary.IsDedicatedServer():
            ue.log("=== BeginPlay on DEDICATED SERVER ===")
            hostname = socket.gethostname()
            local_ip = socket.gethostbyname(hostname)
            ue.log(f"Server LAN IP: {local_ip}")
            try:
                public_ip = urllib.request.urlopen('https://api.ipify.org').read().decode('utf-8')
                ue.log(f"Public IP: {public_ip}")
            except Exception as e:
                ue.log(f"Could not fetch public IP: {e}")
            ue.log("If you correctly port forwarded the LAN IP, the server is on the public IP: " + public_ip)

            # Server-originated multicast test
            ue.log("Calling test_multicast_flag() from server")
            self.test_multicast_flag("hello via multicast flag")

        else:
            ue.log("=== BeginPlay on CLIENT ===")
            # Client → Server → Clients
            ue.log("Calling server_manual_multicast() from client")
            self.server_manual_multicast("hello via manual multicast")

        # ue.exec('Script.py') # run a Python script file by passing its name
        # ue.log(self.uobject.get_world().call_function('IsDedicatedServer')) # ('GetNetMode'))
        # if (self.uobject.get_world().IsServer()):
        #     ue.log("hello from server")
        # elif (self.uobject.get_world().IsClient()):
        #     ue.log("hello from client")

        # self.uobject.get_player_controller().ClientTravel()

        if KismetSystemLibrary.IsDedicatedServer():
            ue.log("hello from server")
            # print("hello from server" + self.uobject.get_uproperty('StringHelloWorldProperty'))
            # print("hello from server" + self.uobject.get_uproperty('StringHelloWorldProperty2'))  # .set_metadata('Category', 'CategoryTest001')
        else:
            ue.log("hello from client")
            # self.uobject.StringHelloWorldProperty = StrProperty()
            # self.uobject.StringHelloWorldProperty2 = StrProperty()
            # KismetSystemLibrary.SetStringPropertyByName(self.uobject, 'StringHelloWorldProperty', 'Hello World 001')
            # KismetSystemLibrary.SetStringPropertyByName(self.uobject, 'StringHelloWorldProperty2', 'Hello World 002')
            #
            # # CPF_REP_NOTIFY # requires CPF_Net to also be set
            # self.uobject.add_property_flags('StringHelloWorldProperty', CPF_NET)
            # #self.uobject.StringHelloWorldProperty = 'Hello World 001'
            # self.uobject.add_property_flags('StringHelloWorldProperty2', CPF_NET)
            # #self.uobject.set_property('StringHelloWorldProperty2', 'Hello World 002')
            # print("hello from client" + self.uobject.get_uproperty('StringHelloWorldProperty'))
            # print("hello from client" + self.uobject.get_uproperty('StringHelloWorldProperty2'))  # .set_metadata('Category', 'CategoryTest001')



        # is_hitting_something, hit_result = KismetSystemLibrary.LineTraceSingle_NEW(self.actor, self.actor.get_actor_location(),FVector(300, 300, 300), ETraceTypeQuery.TraceTypeQuery1,DrawDebugType=EDrawDebugTrace.ForOneFrame)
        # if is_hitting_something:
        #     ue.log(hit_result)x

        # def get_world_from_uobject(obj):
        #     # Walk up the outer chain to find a World
        #     current = obj
        #     while current:
        #         if current.is_a(ue.find_class('World')):
        #             return current
        #         current = current.get_outer()
        #     return None
        #
        # ActorClass = ue.find_class('Actor')
        #
        # def get_actor_from_uobject(obj):
        #     current = obj
        #     while current:
        #         if current.is_a(ActorClass):
        #             return current
        #         current = current.get_outer()
        #     return None
        #
        # world = get_world_from_uobject(self.uobject)
        # actor = get_actor_from_uobject(self.uobject)

        # ue.log(self.uobject.__getattribute__("server"))
        # ue.log(self.uobject.__getattribute__("client"))

        # if not world:
        #     ue.log("No world found")
        # if not actor:
        #     ue.log("No actor found")
        # else:
        #     if actor.HasAuthority():
        #         ue.log("hello from server")
        #     else:
        #         ue.log("hello from client")

            # # UE4 NetMode numeric values
            # NM_Standalone = 0
            # NM_DedicatedServer = 1
            # NM_ListenServer = 2
            # NM_Client = 3
            #
            # if net_mode == NM_DedicatedServer:
            #     ue.log("Running on a DEDICATED SERVER")
            # elif net_mode == NM_ListenServer:
            #     ue.log("Running on a LISTEN SERVER")
            # elif net_mode == NM_Client:
            #     ue.log("Running on a CLIENT")
            # elif net_mode == NM_Standalone:
            #     ue.log("Running in STANDALONE (no networking)")


        self.test_kingdon()
        ue.log("testing cylinder:")
        self.test_cylinder()

        # self.uobject.bind_event('OnActorBeginOverlap', self.manage_overlap)
        # self.uobject.bind_action('Jump', ue.IE_PRESSED, self.uobject.jump)
        self.uobject.enable_input()
        self.uobject.bind_key('K', ue.IE_PRESSED, self.you_pressed_K) # IE_AXIS, IE_DOUBLE_CLICK, IE_PRESSED, IE_RELEASED, IE_REPEAT
        # self.uobject.bind_axis('MoveForward', self.move_forward)
        # text_render_component = ue.find_class('TextRenderComponent')
        # spawn a new PyActor
        # new_actor = self.uobject.actor_spawn(ue.find_class('PyActor'), Fvector(0, 0, 0),FRotator(0, 0, 90))
        # # add a sphere component as the root one
        # static_mesh = new_actor.add_actor_root_component(ue.find_class('StaticMeshComponent'), 'SphereMesh')
        # # set the mesh as the Sphere asset
        # static_mesh.call('SetStaticMesh /Engine/EngineMeshes/Sphere.Sphere')
        # # set the python module
        # new_actor.set_property('PythonModule', 'gameclasses')
        # # set the python class
        # new_actor.set_property('PythonClass', 'Vertical')
        # world = ue.get_editor_world()
        # actor000 = world.actor_spawn(Actor, FVector(0, 0, 0), FRotator(0, 0, 0))
        # character000 = world.actor_spawn(Character, FVector(100, 100, 100), FRotator(0, 0, 0))

    # this is called at every 'tick'
    def tick(self, delta_time):
        # get current location
        location = self.uobject.get_actor_location()
        # increase Z honouring delta_time
        location.z += 100 * delta_time
        # set new location
        self.uobject.set_actor_location(location)

    # def on_actor_begin_overlap(self, me, other_actor):
    #     pass
    #
    # def on_actor_end_overlap(self, me, other_actor):
    #     pass
    #
    # def on_actor_hit(self, me, other_actor, normal_impulse, hit_result):
    #     pass
    #
    # def manage_overlap(self, me, other):
    #     ue.print_string('overlapping ' + other.get_name())

    def you_pressed_K(self):
        ue.log_warning('you pressed K')
        self.uobject.get_player_controller().ClientTravel("10.10.1.123:7777", ue.ETravelType.TRAVEL_Absolute)
        ue.log_warning('travel completed')
        ue.log("hello from client")
        self.server_event()
        print("hello from client" + self.uobject.get_uproperty('StringHelloWorldProperty'))
        print("hello from client" + self.uobject.get_uproperty('StringHelloWorldProperty2'))  # .set_metadata('Category', 'CategoryTest001')


    def move_forward(self, amount):
        ue.print_string('axis value: ' + str(amount))