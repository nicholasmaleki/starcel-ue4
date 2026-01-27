import unreal_engine as ue
from unreal_engine_tools import *
import numpy as np
import os, sys, subprocess, importlib, urllib.request, socket, math, sympy, fast_autocomplete, numba, kingdon #numba_cuda
from unreal_engine import FVector, FRotator, FTransform, FHitResult, CLASS_CONFIG, CLASS_DEFAULT_CONFIG, CPF_CONFIG, CPF_GLOBAL_CONFIG, CPF_EXPOSE_ON_SPAWN, CPF_NET, CPF_REP_NOTIFY
from unreal_engine.classes import Actor, Character, PlayerController, StaticMeshActor, KismetMathLibrary, KismetSystemLibrary, Object, StrProperty, IntProperty, Blueprint, Material, Texture, LargeStringAsync, LargeStringRPCActor
from unreal_engine.enums import EInputEvent, ETraceTypeQuery, EDrawDebugTrace
from constants import Constants, WorldSize
import constants, windowtool
from languages import *
from cli import *
from hotreload import *
import hotreload, unreal_engine_tools
import asyncio, time
from typing import List, Dict, Union, Optional


ue.log('Hello i am a Python module.')
# Code placed outside the Main class will not run when connecting to a server.

# TODO: Cleanup 0,0,0. Merge all dfb PR branches: https://github.com/dfb/UnrealEnginePython/tree/modus

# # Keep track of the current index
# current_bg_index = 0

# change_background("transparent")

# Stop the background music
# find_actor("CellDriftLoop").SetActorHiddenInGame(True)

# Use this if you want to rebuild the unreal_engine intellisense(.pyi, etc.) and cli
# rebuild_generated_modules()

# reload_all_modules()

# reset_pyactor()


# Global Vars
RPC_ACTOR = None
SERVER_HELPER = None  # Server-side helper
CLIENT_HELPER = None  # Client-side helper

class Main:
    def test_kingdon(self):
        ue.log("testing kingdon:")
        from kingdon import Algebra
        alg = Algebra(3, 0, 1)
        locals().update(alg.blades)
        b = alg.bivector(name='b')
        ue.log(b)

    def test_cylinder(self): #use instanced static meshes for the gridlines
        ue.log("testing cylinder:")
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

    # # ------------------------------------------------------------
    # # MULTICAST FLAG TEST
    # # ------------------------------------------------------------
    # def test_multicast_flag(self, msg):
    #     """
    #     If .multicast works, this should run on:
    #     - Dedicated Server
    #     - All connected Clients
    #
    #     In practice (UE4Python), this usually runs server-only.
    #     """
    #     if KismetSystemLibrary.IsDedicatedServer():
    #         ue.log(f"[multicast flag] SERVER executed: {msg}")
    #     else:
    #         ue.log(f"[multicast flag] CLIENT executed: {msg}")
    #
    # # Register as RPC
    # test_multicast_flag.event = True
    # test_multicast_flag.multicast = True
    # test_multicast_flag.reliable = True
    #
    # # ------------------------------------------------------------
    # # SERVER RPC – MANUAL MULTICAST
    # # ------------------------------------------------------------
    # def server_manual_multicast(self, msg):
    #     """
    #     Authoritative server RPC.
    #     Explicitly calls a client RPC on every PlayerController.
    #     """
    #     ue.log("[manual multicast] SERVER executing")
    #
    #     for pc in self.uobject.get_world().all_actors():
    #         if pc:
    #             pc.client_receive_manual(msg)
    #
    # # Register as Server RPC
    # server_manual_multicast.event = True
    # server_manual_multicast.server = True
    # server_manual_multicast.reliable = True
    #
    # # ------------------------------------------------------------
    # # CLIENT RPC – MANUAL MULTICAST TARGET
    # # ------------------------------------------------------------
    # def client_receive_manual(self, msg):
    #     """
    #     Should only ever run on clients.
    #     """
    #     if KismetSystemLibrary.IsDedicatedServer():
    #         ue.log("[manual multicast] ERROR: executed on server")
    #     else:
    #         ue.log(f"[manual multicast] CLIENT executed: {msg}")
    #
    # # Register as Client RPC
    # client_receive_manual.event = True
    # client_receive_manual.client = True
    # client_receive_manual.reliable = True

    def set_global_time_dilation(self, time_dilation = 1):
        self.uobject.TimeDilation = time_dilation
        self.uobject.call_function('EventRunBlueprintFunctions')

    def end_play(self, reason):
        ue.log("Ending play")
        for i, ticker in enumerate(tickers):
            ue.remove_ticker(ticker)
            del tickers[i]
            print(ticker, "stopped.")


    # this is called on game start
    def begin_play(self):
        ue.log('Begin Play on Main class')

        global world
        world = get_world()
        print("begin_play found world", world)
        unreal_engine_tools.world = world
        # print(world)
        global tickers
        tickers = []

        global RPC_ACTOR, CLIENT_HELPER

        RPC_ACTOR = None
        CLIENT_HELPER = None

        if KismetSystemLibrary.IsDedicatedServer():
            ue.log("BeginPlay on DEDICATED SERVER")
            print("using world", world.get_name())
            # print(world.all_actors())
            # for actor in world.all_actors():
            #     print(actor.get_class().get_name())
            gm = find_actor("StarcelGameMode")
            print("Gamemode", gm)

            def on_player_joined(player_controller):
                ue.log_warning(f"[SERVER PY] Player joined: {player_controller}") # START HERE
                global RPC_ACTOR, SERVER_HELPER

                if not RPC_ACTOR:
                    print("RPC_ACTOR not found, making one")
                    try:
                        ue.log("Server making a LargeStringRPCActor.")
                        RPC_ACTOR = world.actor_spawn(LargeStringRPCActor)
                        RPC_ACTOR.SetOwner(player_controller)
                        RPC_ACTOR.LargeString = ue.new_object(LargeStringAsync)  # attach ULargeStringAsync
                        print("Created new LargeStringAsync instance", RPC_ACTOR, RPC_ACTOR.LargeString)

                        # BIND THE C++ EVENT MANUALLY AFTER CREATING LARGESTRING
                        try:
                            RPC_ACTOR.LargeString.bind_event('OnFullyReceived', RPC_ACTOR.Server_OnFullStringReceived)
                            ue.log_warning("[SERVER] Manually bound OnFullyReceived to Server_OnFullStringReceived")
                        except Exception as e:
                            ue.log_error(f"Failed to bind OnFullyReceived: {e}")

                    except Exception as e:
                        ue.log_error(f"Actor creation error: {e}")
                        return
                else:
                    ue.log_warning(f"[SERVER PY] LargeStringRPCActor already created")

                # Create SERVER helper with SERVER callback
                if not SERVER_HELPER:
                    ue.log_warning("[SERVER] Creating SERVER helper")
                    SERVER_HELPER = LargeStringAsyncStandalone(
                        large_string_obj=RPC_ACTOR.LargeString,
                        rpc_actor=RPC_ACTOR,
                        on_received_callback=None,  # Server doesn't need client callback
                        on_server_received_callback=server_on_full_string_received,  # THIS is the key
                        on_progress_callback=None,
                        auto_send=False  # Server doesn't auto-send from OnChunksBuilt
                    )
                    ue.log_warning("[SERVER] Server rpc helper created and bound")

                # rpc_actors = find_actors("LargeStringRPCActor")
                # if rpc_actors:
                #     for rpc_actor in rpc_actors:
                #         print("Blueprint binding server_string_received event: ", rpc_actor)
                #         rpc_actor.bind_event('OnServerStringReceived', server_on_full_string_received)

            if gm:
                gm.bind_event("OnPlayerJoined", on_player_joined)
                ue.log_warning("[SERVER] Bound OnPlayerJoined")

            hostname = socket.gethostname()
            local_ip = socket.gethostbyname(hostname)
            ue.log(f"Server LAN IP: {local_ip}")
            try:
                public_ip = urllib.request.urlopen('https://api.ipify.org').read().decode('utf-8')
                ue.log(f"Public IP: {public_ip}")
            except Exception as e:
                ue.log(f"Could not fetch public IP: {e}")
            ue.log("If you correctly port forwarded the LAN IP, the server is on the public IP: " + public_ip)
            # # Server-originated multicast test
            # ue.log("Calling test_multicast_flag() from server")
            # self.test_multicast_flag("hello via multicast flag")

        else:
            ue.log("BeginPlay on CLIENT")
            if world.AuthorityGameMode:
                ue.log("SERVER (AuthorityGameMode exists). Client likely connected to internal server. ")
            else:
                ue.log("CLIENT (no AuthorityGameMode) Client likely connected to dedicated server. ")

            self.uobject.enable_input()
            self.uobject.bind_key('K', ue.IE_PRESSED, self.you_pressed_K)  # IE_AXIS, IE_DOUBLE_CLICK, IE_PRESSED, IE_RELEASED, IE_REPEAT
            player_controller = self.uobject.get_player_controller()
            pawn = player_controller.get_pawn()
            print(player_controller)
            print(pawn)
            apply_material(
                actor_name="TestSphere",  # M_Color is default
                material_path="/Game/Materials/M_Color.M_Color",
                params = {
                    "Color": (0, 1, 0, 1),
                    "Metallic": 0.5,
                    "Specular": 0.5,
                    "Roughness": 0.2,
                    "Anisotropy": 0.1,
                    "Emissive Multiplier": 10.0,
                    "Ambient Occlusion": 1.0,
                }
            )

            apply_material(
                actor_name="StickManCharacter_C",  # runtime instance name (check via print)
                component_name="SkeletalMeshOutline",
                material_path="/Game/Materials/M_Outline.M_Outline",
                params={
                    "Outline": 5.0,
                    "Color": (1, 1, 1, 1),
                }
            )
            # pawn = player_controller.get_controlled_pawn()

            # Client → Server → Clients
            # ue.log("Calling server_manual_multicast() from client")
            # self.server_manual_multicast("hello via manual multicast")

        # ue.exec('Script.py') # run a Python script file by passing its name
        # ue.log(self.uobject.get_world().call_function('IsDedicatedServer')) # ('GetNetMode'))
        # if (self.uobject.get_world().IsServer()):
        #     ue.log("hello from server")
        # elif (self.uobject.get_world().IsClient()):
        #     ue.log("hello from client")

        # self.uobject.get_player_controller().ClientTravel()

        # if KismetSystemLibrary.IsDedicatedServer():
        #     ue.log("hello from server")
        #
        #     # print("hello from server" + self.uobject.get_uproperty('StringHelloWorldProperty'))
        #     # print("hello from server" + self.uobject.get_uproperty('StringHelloWorldProperty2'))  # .set_metadata('Category', 'CategoryTest001')
        # else:
        #     ue.log("hello from client")

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

        self.test_kingdon()
        self.test_cylinder()

    # this is called at every 'tick'
    def tick(self, delta_time):
        # get current location
        location = self.uobject.get_actor_location()
        # increase Z honouring delta_time
        location.z += 100 * delta_time
        # set new location
        self.uobject.set_actor_location(location)


    def you_pressed_K(self):
        ue.log_warning("=== YOU PRESSED K ===")
        global RPC_ACTOR, CLIENT_HELPER
        if not RPC_ACTOR:
            print("Pressed k didn't have an rpc actor")
            RPC_ACTOR = find_actor("LargeStringRPCActor")
            print("pressed k found rpc actor", RPC_ACTOR)
        else:
            print("pressed k already has an rpc actor", RPC_ACTOR)

        print("Found LargeStringRPCActors in pressed k", find_actors("LargeStringRPCActor"))
        if not RPC_ACTOR.LargeString:
            ue.log_warning("Creating LargeString on client")
            RPC_ACTOR.LargeString = ue.new_object(LargeStringAsync)
            ue.log_warning("Created LargeString on client")
        else:
            ue.log_warning("LargeString already exists in RPC_ACTOR")


        # Create helper if not exists
        if not CLIENT_HELPER:
            CLIENT_HELPER = LargeStringAsyncStandalone(
                large_string_obj=RPC_ACTOR.LargeString,
                rpc_actor=RPC_ACTOR,
                on_received_callback=client_on_full_string_received,
                on_server_received_callback=None, # Client doesn't need server callback
                on_progress_callback=progress_callback,
                auto_send=True
            )
            ue.log("Created LargeStringAsyncStandalone helper")
        else:
            print("pressed k already has a helper actor", CLIENT_HELPER)


        # Prepare test string
        test_string = "U" * 1 * 1024 * 1024 # 100 * 1024 * 1024  # 100MB
        ue.log_warning(f"Starting async build, length={len(test_string)}")

        # Build chunks asynchronously
        try:
            RPC_ACTOR.LargeString.SetFromStringAsync(test_string)
        except Exception as e:
            ue.log_error(f"SetFromStringAsync failed: {e}")



        # Send the string through various modes

        # # Client → Server only
        # CLIENT_HELPER.send_string(mode="server_only")

        # # Server → Multicast to All clients
        # CLIENT_HELPER.send_string(mode="multicast")
        #
        # # Server → Specific client
        # target_pc = self.uobject.get_player_controller()
        # CLIENT_HELPER.send_string(mode="client", target_client=target_pc)
        #
        # # Server → Single client (Explicit)
        # CLIENT_HELPER.send_string(mode="server_to_client", target_client=target_pc)
        #
        # Client → Server → Multicast to All Clients
        CLIENT_HELPER.send_string(mode="client_to_server_then_multicast")


        # # Background swapping
        # # Define the list of background types
        # backgrounds = ["white", "black", "white_no_bloom", "white_no_emissive", "stars", "sky", "transparent", r"C:\Users\nicho\Documents\Unreal Projects\Starcel9\Images\duck.hdr"]
        #
        # global current_bg_index  # needed to modify the variable outside the function
        #
        # bg = backgrounds[current_bg_index]
        # print(bg)
        # change_background(bg)
        #
        # # Move to the next index, loop back to 0 if at the end
        # current_bg_index += 1
        # if current_bg_index >= len(backgrounds):
        #     current_bg_index = 0


        # self.uobject.get_player_controller().ClientTravel("10.10.1.123:7777", ue.ETravelType.TRAVEL_Absolute)
        # ue.log_warning('travel completed')
        # ue.log("hello from client")
        # self.server_event()
        # print("hello from client" + self.uobject.get_uproperty('StringHelloWorldProperty'))
        # print("hello from client" + self.uobject.get_uproperty('StringHelloWorldProperty2'))  # .set_metadata('Category', 'CategoryTest001')


    def move_forward(self, amount):
        ue.print_string('axis value: ' + str(amount))


# https://github.com/kprimo/UEPyTutorials/blob/main/Content/Scripts/Basic/DynamicTexture/dynamic_texture.py
# https://github.com/kprimo/UEPyTutorials/blob/main/Content/Scripts/Advanced/StableDiffusion/RuntimeImage/runtime_image.py


class Axis:
    def __init__(self, x="x", y="y", z="z"):
        self.x = x
        self.y = y
        self.z = z

    def swap_axis(self, input):
        # for i in range(input[0]):
        #     input[0][i] = input[1][i]
        return [input[1],input[0]]

    def get_render_order(self, axis_list=None):
        return axis_list or [self.x, self.y, self.z]

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
        # self.swap_axis()


class Table2:
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


class Table:
    def __init__(self,
                 axis_ranges: List[tuple],
                 axis_labels: Optional[Dict[int,List[str]]]=None,
                 skip_axes: Optional[List[int]]=None,
                 skip_zero: bool=False,
                 width:int=100, height:int=100, depth:int=100,
                 axis_obj:Axis=None,
                 mode:str='normal'):
        self.axis_ranges = axis_ranges
        self.ndim = len(axis_ranges)
        self.skip_axes = skip_axes or []
        self.skip_zero = skip_zero
        self.axis_obj = axis_obj or Axis()
        self.mode = mode

        # General nD cell sizes
        self.cell_size = [width, height, depth] + [100]*(self.ndim-3)

        # PGA mode
        self.pga_alg = None
        if self.mode=='projective_geometric_algebra':
            try:
                from kingdon import Algebra
                self.pga_alg = Algebra(3,0,1)
                locals().update(self.pga_alg.blades)
            except ImportError:
                ue.log("Kingdon module not installed, using normal mode")
                self.mode='normal'

        # --------- Array initialization ---------
        self.shape=[]
        self.axis_indices=[]
        for i,(min_v,max_v) in enumerate(axis_ranges):
            if i in self.skip_axes:
                self.shape.append(0)
                self.axis_indices.append([])
                continue
            indices = list(range(min_v,max_v+1))
            if skip_zero and 0 in indices:
                indices.remove(0)
            self.axis_indices.append(indices)
            self.shape.append(len(indices))

        final_shape = [s for i,s in enumerate(self.shape) if i not in self.skip_axes]
        self.array = np.full(final_shape, None, dtype=object)

        # --------- Axis labels ---------
        self.axis_labels={}
        for axis,indices in enumerate(self.axis_indices):
            if axis in self.skip_axes: continue
            if axis_labels and axis in axis_labels:
                self.axis_labels[axis] = self._repeat_labels(axis_labels[axis], len(indices))
            else:
                self.axis_labels[axis] = self._spreadsheet_labels(len(indices))
        self._update_locals_labels()

        # --------- Render actors ---------
        self.cylinders=[]
        self.text_actors=[]

    # --------- Label helpers ---------
    def _spreadsheet_labels(self,length:int)->List[str]:
        labels=[]
        n = len(constants.default_alphabet_capital)
        for i in range(length):
            quotient,remainder = divmod(i,n)
            if quotient==0:
                labels.append(constants.default_alphabet_capital[remainder])
            else:
                prefix = constants.default_alphabet_capital[quotient-1]
                labels.append(prefix + constants.default_alphabet_capital[remainder])
        return labels

    def _repeat_labels(self,custom_labels:List[str],length:int)->List[str]:
        repeated=[]
        n=len(custom_labels)
        for i in range(length):
            quotient,remainder=divmod(i,n)
            repeated.append(custom_labels[remainder]*(quotient+1))
        return repeated

    def _update_locals_labels(self):
        """Expose labels in locals() for scripting/autocomplete"""
        for axis, labels in self.axis_labels.items():
            for label, idx in zip(labels, self.axis_indices[axis]):
                locals()[label] = idx

    # --------- nD Index iteration ---------
    def _iterate_nd_indices(self):
        """Yield all combinations of indices for nD array"""
        def recurse(current_axis, current_idx):
            if current_axis >= self.ndim:
                yield current_idx
            else:
                if current_axis in self.skip_axes:
                    yield from recurse(current_axis+1, current_idx)
                else:
                    for idx in self.axis_indices[current_axis]:
                        yield from recurse(current_axis+1, current_idx + [idx])
        yield from recurse(0, [])

    def _translate_index(self,idxs:Union[int,str,List[Union[int,str]]])->tuple:
        """Translate label(s) or indices to internal array indices"""
        if isinstance(idxs,int) or isinstance(idxs,str):
            idxs=[idxs]
        if len(idxs)<self.ndim:
            idxs += [0]*(self.ndim-len(idxs))
        translated=[]
        for axis,idx in enumerate(idxs):
            if axis in self.skip_axes: continue
            indices=self.axis_indices[axis]
            labels=self.axis_labels[axis]
            if isinstance(idx,str):
                if idx not in labels:
                    raise KeyError(f"Label {idx} not found on axis {axis}")
                idx=labels.index(idx)
            else:
                if idx not in indices:
                    raise IndexError(f"Index {idx} not valid for axis {axis}")
                idx=indices.index(idx)
            translated.append(idx)
        return tuple(translated)

    def __getitem__(self,idxs):
        return self.array[self._translate_index(idxs)]

    def __setitem__(self,idxs,value):
        self.array[self._translate_index(idxs)] = value

    # --------- Compute positions ---------
    def compute_point_position(self,indices:List[int])->FVector:
        """Map first three axes to FVector for rendering; higher axes ignored"""
        x = indices[0]*self.cell_size[0] if len(indices)>0 else 0
        y = indices[1]*self.cell_size[1] if len(indices)>1 else 0
        z = indices[2]*self.cell_size[2] if len(indices)>2 else 0
        if self.mode=='projective_geometric_algebra' and self.pga_alg:
            P = self.pga_alg.point(x,y,z)
            return FVector(P.x,P.y,P.z)
        return FVector(x,y,z)

    # --------- Rendering ---------
    def spawn_cylinder(self,point:FVector,target_point:FVector=None):
        actor=ue.get_editor_world().actor_spawn(StaticMeshActor,point)
        actor.set_actor_scale3d(FVector(self.cell_size[0]/50,
                                        self.cell_size[1]/50,
                                        self.cell_size[2]/100))
        if target_point:
            direction=target_point-point
            midpoint=(point+target_point)/2
            normalized=direction.normalized()
            default_axis=FVector(0,0,1)
            rot_axis=default_axis.cross(normalized)
            if rot_axis.length()==0: rot_axis=FVector(1,0,0)
            angle=math.degrees(math.acos(default_axis.dot(normalized)))
            rotator=KismetMathLibrary.RotatorFromAxisAndAngle(rot_axis,angle)
            actor.set_actor_location(midpoint)
            actor.set_actor_rotation(rotator)
        self.cylinders.append(actor)
        return actor

    def spawn_text3d(self,point:FVector,text:str):
        pass
        # actor=ue.get_editor_world().actor_spawn(TextRenderActor,point)
        # actor.set_text(text)
        # self.text_actors.append(actor)
        # return actor

    def render_grid(self,connect_lines=False,display_values=True,render_order=None):
        render_order = render_order or self.axis_obj.get_render_order()
        for idxs in self._iterate_nd_indices():
            pos = self.compute_point_position(idxs)
            target=None
            if connect_lines:
                # connect next index along first axis
                next_idxs=idxs.copy()
                next_axis = 0
                if next_axis not in self.skip_axes and idxs[0]!=self.axis_indices[0][-1]:
                    next_idxs[0] = self.axis_indices[0][self.axis_indices[0].index(idxs[0])+1]
                    target=self.compute_point_position(next_idxs)
            self.spawn_cylinder(pos,target_point=target)
            if display_values:
                val=self[idxs]
                if val is not None:
                    self.spawn_text3d(pos,str(val))

    # --------- Spread ---------
    def spread_table(self,directions:List[FVector],repeats:int):
        """Spread nD table along multiple vector directions recursively"""
        def recursive_spread(current_pos:FVector, dir_idx:int):
            if dir_idx>=len(directions): return
            dir_vec = directions[dir_idx]
            for r in range(1,repeats+1):
                offset = dir_vec*r
                for idxs in self._iterate_nd_indices():
                    base_pos = self.compute_point_position(idxs)
                    pos = base_pos + offset + current_pos
                    self.spawn_cylinder(pos)
                    val = self[idxs]
                    if val is not None:
                        self.spawn_text3d(pos,str(val))
                recursive_spread(current_pos+offset,dir_idx+1)
        recursive_spread(FVector(0,0,0),0)