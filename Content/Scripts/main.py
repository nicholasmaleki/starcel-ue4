import unreal_engine as ue
import unreal_engine.classes
from unreal_engine_tools import *
import numpy as np
import os, sys, subprocess, importlib, urllib.request, socket, math, sympy, fast_autocomplete, numba, kingdon #numba_cuda
from unreal_engine import FVector, FRotator, FTransform, FHitResult, CLASS_CONFIG, CLASS_DEFAULT_CONFIG, CPF_CONFIG, CPF_GLOBAL_CONFIG, CPF_EXPOSE_ON_SPAWN, CPF_NET, CPF_REP_NOTIFY
from unreal_engine.classes import Actor, Character, PlayerController, StaticMeshActor, KismetMathLibrary, KismetSystemLibrary, Object, StrProperty, IntProperty, Blueprint, Material, Texture, LargeStringAsync, LargeStringRPCActor, StaticMesh, StaticMeshActor
from unreal_engine.enums import EInputEvent, ETraceTypeQuery, EDrawDebugTrace, EComponentMobility, EMouseCursor, ECollisionChannel
from constants import Constants, WorldSize
import constants, windowtool
from languages import *
from cli import *
from hotreload import *
import hotreload, unreal_engine_tools
import asyncio, time
from typing import List, Dict, Union, Optional

from nd_table.examples import example_unreal_rendering
from input_devices import Keyboard, Mouse, HotkeyManager, TraceHelper

ue.log('Hello i am a Python module.')
# Code placed outside the Main class will not run when connecting to a server.

# TODO: Cleanup 0,0,0. Merge all dfb PR branches: https://github.com/dfb/UnrealEnginePython/tree/modus

# # Keep track of the current index
# current_bg_index = 0

change_background("white")


# Stop the background music
# find_actor("CellDriftLoop").SetActorHiddenInGame(True)

# Use this if you want to rebuild the unreal_engine intellisense(.pyi, etc.) and cli
# rebuild_generated_modules()

# reload_all_modules() # TODO: Unstable. look into ue.load_package() or get_or_create()

# reset_pyactor()


# ret = ue.message_dialog_open(ue.APP_MSG_TYPE_YES_NO, "Do you want to shot ?")
# if ret == ue.APP_RETURN_TYPE_YES:
#     ue.log('You choose "YES"')


# help_cmd("ls")


# Global Vars
RPC_ACTOR = None
SERVER_HELPER = None  # Server-side helper
CLIENT_HELPER = None  # Client-side helper

class Main:
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
            self.input.release_mouse()
        if hasattr(self, 'input'):
            self.input.shutdown()

    # def say_hi(self):
    #     ue.log("Pressed G")
    #
    # def ctrl_shift_b(self):
    #     ue.log("Pressed Ctrl+Shift+B")
    #
    # def left_click(self):
    #     ue.log("Left mouse button")
    #
    # def mouse_wheel(self, value):
    #     ue.log("Wheel: {}".format(value))
    #
    # def sequence_action(self):
    #     ue.log("Sequence fired: Ctrl+K → MouseX → Click")
    #
    # def print_mouse_world(self):
    #     data = self.input.get_mouse_position(deproject=True)
    #     if not data:
    #         return
    #     x, y, world, dir = data
    #     ue.log(f"Mouse {x},{y}")
    #     ue.log(f"World {world} Dir {dir}")
    def on_move_forward(self, value):
        """Handle analog movement input"""
        if value != 0:
            ue.log(f"Moving forward: {value:.2f}")
            # Add movement code here

    def interact(self):
        """Interaction bound to multiple keys"""
        ue.log("Interact!")
        # Perform interaction

    def shift_click(self):
        """Shift + Click action"""
        ue.log("Shift + Click")
        # Multi-select logic, etc.

    def on_ctrl_shift_b(self):
        ue.log("Pressed Ctrl+Shift+B")

    def on_left_click(self):
        ue.log("Left mouse button clicked")

    def check_key_states(self):
        """Example of manually checking key states without binding"""
        if self.input.is_key_down("W"):
            ue.log("W is currently down")
        if self.input.is_key_down("LeftControl"):
            ue.log("Left Control is currently down")
        if self.input.is_chord_down("Ctrl+Shift"):
            ue.log("Ctrl+Shift combo is down")

    def print_mouse_world(self):
        """Print mouse screen position and world projection"""
        data = self.input.get_mouse_position(deproject=True)
        if not data:
            ue.log("Could not get mouse position")
            return

        x, y, world, direction = data
        ue.log(f"Mouse Screen: ({x:.1f}, {y:.1f})")
        ue.log(f"World Pos: {world}")
        ue.log(f"World Dir: {direction}")

    def print_cursor_and_trace(self):
        """Get and print cursor info using the new get_cursor_info() method"""
        # Method 1: Using get_cursor_info()
        cursor_info = self.input.get_cursor_info()
        if cursor_info:
            ue.log("=== CURSOR INFO ===")
            ue.log(f"Screen X: {cursor_info['screen_x']:.1f}")
            ue.log(f"Screen Y: {cursor_info['screen_y']:.1f}")
            ue.log(f"World Pos: {cursor_info['world_pos']}")
            ue.log(f"World Dir: {cursor_info['world_dir']}")

        # Method 2: Trace to see what we're pointing at
        hit = self.trace.trace_cursor()
        if hit:
            ue.log(f"Hit Actor: {hit.get('actor')}")
            ue.log(f"Hit Location: {hit.get('location')}")
        else:
            ue.log("No hit under cursor")

    def trace_from_cursor(self):
        """Trace from cursor into the world"""
        ue.log("=== CURSOR TRACE ===")
        hit = self.trace.trace_cursor(ECollisionChannel.ECC_Visibility)

        if hit:
            actor = hit.get('actor')
            location = hit.get('location')
            normal = hit.get('normal')

            ue.log(f"Hit Actor: {actor.get_name() if actor else 'None'}")
            ue.log(f"Hit Location: {location}")
            ue.log(f"Hit Normal: {normal}")
        else:
            ue.log("Nothing hit under cursor")

    def trace_from_camera(self):
        """Trace forward from camera/pawn"""
        ue.log("=== FORWARD TRACE ===")
        hit = self.trace.trace_forward(dist=5000)

        if hit:
            actor = hit.get('actor')
            location = hit.get('location')

            ue.log(f"Hit Actor: {actor.get_name() if actor else 'None'}")
            ue.log(f"Hit Location: {location}")
            ue.log(f"Distance: {hit.get('distance', 0):.1f}")
        else:
            ue.log("Nothing hit in forward trace")

    def print_key_registry(self, key):
        """Print all bindings registered for a specific key"""
        bindings = self.input.get_key_bindings(key)
        ue.log(f"=== Bindings for '{key}' ===")
        for binding in bindings:
            ue.log(f"  Type: {binding['type']}, Keys: {binding['keys']}, Callback: {binding['callback']}")

    # this is called on game start
    def begin_play(self):
        ue.log('Begin Play on Main class')
        #change_background("video", os.path.join(os.path.abspath(ue.get_content_dir()),"Movies", "psychedelic.mp4"))
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

        # self.uobject.enable_input()
        #
        # self.keyboard = Keyboard()
        # self.mouse = Mouse()
        #
        # self.input = HotkeyManager(self.uobject, self.keyboard, self.mouse)
        # self.trace = TraceHelper(self.uobject)
        #
        # # Enable mouse features
        # self.input.enable_mouse_events(True, True)
        # # self.input.show_cursor(True)
        # # self.input.set_cursor(EMouseCursor.GrabHand)
        # print("CURSOR INFO:")
        #
        #
        # pc = self.uobject.get_player_controller()
        # pc.bind_axis("TurnRate", lambda v: v != 0 and ue.log(f"TurnRate {v}"))
        # pc.bind_axis("LookUpRate", lambda v: v != 0 and ue.log(f"LookUpRate {v}"))
        #
        # pc.bind_axis("MouseX", lambda v: v != 0 and ue.log(f"MouseX {v}"))
        # pc.bind_axis("MouseY", lambda v: v != 0 and ue.log(f"MouseY {v}"))
        # pc.bind_axis("MouseWheelAxis", lambda v: v != 0 and ue.log(f"MouseWheel {v}"))
        #
        # # Mouse delta via timer
        # self.input.log_mouse_delta_timer()
        #
        # # self.uobject.bind_key('K', ue.IE_PRESSED, self.you_pressed_K)
        #
        # # Hotkeys
        # self.input.bind_press("Ctrl+Shift+B", lambda: ue.log("Ctrl+Shift+B"))
        # self.input.bind_press("Ctrl+Shift+A", lambda: ue.log("Ctrl+Shift+A"))
        #
        # self.input.bind_press("M", self.input.toggle_cursor)
        #
        # # Repeat
        # self.input.bind_repeat("W", lambda: ue.log("Holding W"))
        #
        # # Actions
        # self.input.bind_action(
        #     "Jump",
        #     pressed_cb=lambda: ue.log("Jump pressed"),
        #     released_cb=lambda: ue.log("Jump released")
        # )
        #
        # # Mouse helpers
        # self.input.bind_press("G", self.print_mouse_world)
        # self.input.bind_press("H", lambda: self.input.set_mouse_position(200, 200))
        self.uobject.enable_input()

        self.keyboard = Keyboard()
        self.mouse = Mouse()
        self.input = HotkeyManager(self.uobject, self.keyboard, self.mouse)
        self.trace = TraceHelper(self.uobject)

        # Analog movement with deadzone
        # self.input.bind_axis_poll(
        #     "MoveForward",
        #     self.on_move_forward,
        #     deadzone=0.1,
        #     rate=0.016  # ~60 FPS
        # )

        # Multiple keys to same action
        self.input.bind_press("F", self.interact)
        self.input.bind_press("E", self.interact)

        # Complex chord
        self.input.bind_press("Ctrl+Alt+Delete", lambda: ue.log("The forbidden combo!"))

        # Mouse button combinations
        self.input.bind_press("Shift+LeftMouseButton", self.shift_click)



        # ============== CURSOR SETUP ==============
        self.input.enable_mouse_events(True, True)
        # self.input.show_cursor(True)
        # self.input.set_cursor(EMouseCursor.GrabHand)

        print("=== CURSOR INFO ===")
        self.input.print_cursor_info()

        # ============== MOUSE AXIS TRACKING ==============
        # IMPORTANT: Use bind_axis_poll for MouseX/MouseY as bind_axis may not work reliably
        # These will now properly track mouse movement
        # self.input.bind_axis_poll("MouseX", lambda v: ue.log(f"MouseX: {v:.3f}"))
        # self.input.bind_axis_poll("MouseY", lambda v: ue.log(f"MouseY: {v:.3f}"))
        # self.input.bind_axis_poll("MouseWheelAxis", lambda v: ue.log(f"MouseWheel: {v:.3f}"))
        #
        # # These might work depending on your project's input settings
        # # If you have TurnRate and LookUpRate defined in your Input Settings, these should work
        # try:
        #     self.input.bind_axis_poll("TurnRate", lambda v: ue.log(f"TurnRate: {v:.3f}"))
        #     self.input.bind_axis_poll("LookUpRate", lambda v: ue.log(f"LookUpRate: {v:.3f}"))
        # except:
        #     ue.log_warning("TurnRate/LookUpRate axes not available in project settings")

        # Mouse delta logging (uses timer)
        self.input.log_mouse_delta_timer(rate=0.1)

        # ============== BASIC KEY BINDINGS ==============
        # Simple press bindings
        # self.input.bind_press("K", self.on_key_k_pressed)
        self.input.bind_press("L", lambda: ue.log("Pressed L"))

        # Chord bindings (key combinations)
        self.input.bind_press("Ctrl+Shift+B", self.on_ctrl_shift_b)
        self.input.bind_press("Ctrl+G", self.print_mouse_world)

        # Toggle cursor with M key
        self.input.bind_press("M", self.input.toggle_cursor)

        # ============== MOUSE BINDINGS ==============
        self.input.bind_press("LeftMouseButton", self.on_left_click)
        self.input.bind_press("RightMouseButton", lambda: ue.log("Right click"))
        self.input.bind_double_click("LeftMouseButton", lambda: ue.log("Double click!"))

        # ============== REPEAT BINDINGS ==============
        # These fire repeatedly while key is held
        self.input.bind_repeat("W", lambda: ue.log("Holding W"))
        self.input.bind_repeat("Ctrl+R", lambda: ue.log("Ctrl+R held"))

        # ============== POLL-BASED CHECKING ==============
        # IMPORTANT: Use bind_poll for keys that have engine actions (like SpaceBar for Jump)
        # This checks key state without binding, so it won't override Jump
        self.input.bind_poll("SpaceBar", lambda: ue.log("Space is down (non-binding)"), rate=0.1)

        # You can also manually check key states
        self.input.bind_press("P", self.check_key_states)

        # ============== ENGINE ACTIONS ==============
        # Bind to actions defined in your project's Input Settings
        # This WON'T override the Jump action
        self.input.bind_action(
            "Jump",
            pressed_cb=lambda: ue.log("Jump action pressed"),
            released_cb=lambda: ue.log("Jump action released")
        )

        # ============== MOUSE POSITION BINDINGS ==============
        # Get cursor info with world projection
        self.input.bind_press("G", self.print_cursor_and_trace)

        # Set mouse position
        self.input.bind_press("H", lambda: self.input.set_mouse_position(960, 540))

        # ============== TRACE EXAMPLES ==============
        # Trace from cursor
        self.input.bind_press("T", self.trace_from_cursor)

        # Trace forward from camera
        self.input.bind_press("F", self.trace_from_camera)

        # ============== SEQUENCE BINDINGS ==============
        # Execute callback after a sequence of keys
        # self.input.bind_sequence(
        #     ["Ctrl+K", "C"],
        #     lambda: ue.log("Sequence completed: Ctrl+K then C"),
        #     timeout=2.0
        # )

        # ============== KEY REGISTRY ==============
        # Print all registered bindings for a specific key
        self.input.bind_press("F1", lambda: self.print_key_registry("W"))

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
                # Spawn drone pawn and possess it
                bp_drone = ue.load_object(Blueprint, '/Game/Blueprints/Assets/BP_DroneCharacter.BP_DroneCharacter')
                player = world.actor_spawn(bp_drone.GeneratedClass)
                transform = FTransform(FVector(0, 0, 0), FRotator(0, 0, 0), FVector(1, 1, 1))
                player.set_actor_transform(transform)
                # player.get_actor_component('Text3DComponent').Text = "HI"

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
        #     ue.log(hit_result)

        self.test_kingdon()
        # self.test_cylinder()
        # self.test_text()
        print("Testing unreal rendering:")
        # example_unreal_rendering()

    # this is called at every 'tick'
    def tick(self, delta_time):
        # get current location
        location = self.uobject.get_actor_location()
        # increase Z honouring delta_time
        location.z += 100 * delta_time
        # set new location
        self.uobject.set_actor_location(location)

        # self.input.print_cursor_info()


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


# https://github.com/kprimo/UEPyTutorials/blob/main/Content/Scripts/Basic/DynamicTexture/dynamic_texture.py
# https://github.com/kprimo/UEPyTutorials/blob/main/Content/Scripts/Advanced/StableDiffusion/RuntimeImage/runtime_image.py