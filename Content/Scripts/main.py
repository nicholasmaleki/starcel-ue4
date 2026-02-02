import unreal_engine as ue
import unreal_engine.classes
from unreal_engine_tools import *
import numpy as np
import os, sys, subprocess, importlib, urllib.request, socket, math, sympy, fast_autocomplete, numba, kingdon #numba_cuda
from unreal_engine import FVector, FRotator, FTransform, FHitResult, CLASS_CONFIG, CLASS_DEFAULT_CONFIG, CPF_CONFIG, CPF_GLOBAL_CONFIG, CPF_EXPOSE_ON_SPAWN, CPF_NET, CPF_REP_NOTIFY
from unreal_engine.classes import Actor, Character, PlayerController, StaticMeshActor, KismetMathLibrary, KismetSystemLibrary, Object, StrProperty, IntProperty, Blueprint, Material, Texture, LargeStringAsync, LargeStringRPCActor, StaticMesh, StaticMeshActor
from unreal_engine.enums import EInputEvent, ETraceTypeQuery, EDrawDebugTrace, EComponentMobility
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

change_background("video", "C:/Users/nicho/Documents/Unreal Projects/Starcel9/Content/Movies/psychedelic.mp4")

# Stop the background music
# find_actor("CellDriftLoop").SetActorHiddenInGame(True)

# Use this if you want to rebuild the unreal_engine intellisense(.pyi, etc.) and cli
# rebuild_generated_modules()

# reload_all_modules() # TODO: look into ue.load_package() or get_or_create()

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

    def test_cylinder(self): # TODO: use instanced static meshes for the gridlines
        ue.log("testing cylinder:")
        # new_actor = world.actor_spawn(Actor)
        # new_actor.set_actor_label('Test Actor')
        # new_actor.add_actor_root_component(InstancedStaticMeshComponent, 'Root')
        # instanced_component = actor.get_component_by_type(InstancedStaticMeshComponent)
        # instanced_component.StaticMesh = mesh
        # instanced_component.PerInstanceSMData = [
        #     InstancedStaticMeshInstanceData(Transform=FTransform(FVector(0, 0, 200), FRotator(90, 90, 0)).get_matrix()),
        #     InstancedStaticMeshInstanceData(Transform=FTransform(FVector(0, 0, 0), FRotator(90, 90, 45)).get_matrix()),
        # ]
        # instanced_component = actor.get_component_by_type(InstancedStaticMeshComponent # if you need to access the component again, you need to retrieve it back as the old instance will be garbaged

        point1 = FVector(0, 0, 0)
        point2 = FVector(100, 100, 100)
        midpoint = (point1 + point2) / 2
        distance_between_points = KismetMathLibrary.Vector_Distance(point1, point2)
        cylinder_rotation = KismetMathLibrary.FindLookAtRotation(point1, point2)  # returns FRotator
        cylinder_rotation.pitch += 90
        cylinder = world.actor_spawn(StaticMeshActor)
        cylinder_mesh = ue.load_object(StaticMesh, '/Engine/BasicShapes/Cylinder')
        smc = cylinder.StaticMeshComponent
        smc.SetStaticMesh(cylinder_mesh)
        smc.Mobility = EComponentMobility.Movable
        transform = FTransform(midpoint, cylinder_rotation, FVector(.1, .1, distance_between_points/100))
        # print(transform)
        cylinder.set_actor_transform(transform)
        # FTransform().get_matrix() # if needed

    def test_text(self):
        ue.log("testing text:")
        bp_cell = ue.load_object(Blueprint, '/Game/Blueprints/Assets/BP_Cell.BP_Cell')
        cell_actor = world.actor_spawn(bp_cell.GeneratedClass)
        transform = FTransform(FVector(0, 0, 0), FRotator(0, 0, 0), FVector(1, 1, 1))
        cell_actor.set_actor_transform(transform)
        cell_actor.get_actor_component('Text3DComponent').Text = "HI"



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
        # self.test_cylinder()
        # self.test_text()

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