import unreal_engine as ue
from unreal_engine_tools import *
import numpy as np
import os, sys, subprocess, importlib, urllib.request, socket, math, sympy, fast_autocomplete, numba, kingdon #numba_cuda
from unreal_engine import FVector, FRotator, FTransform, FHitResult, CLASS_CONFIG, CLASS_DEFAULT_CONFIG, CPF_CONFIG, CPF_GLOBAL_CONFIG, CPF_EXPOSE_ON_SPAWN, CPF_NET, CPF_REP_NOTIFY
from unreal_engine.classes import Actor, Character, PlayerController, StaticMeshActor, KismetMathLibrary, KismetSystemLibrary, Object, StrProperty, IntProperty, Blueprint, Material, Texture, LargeStringAsync, LargeStringRPCActor
from unreal_engine.enums import EInputEvent, ETraceTypeQuery, EDrawDebugTrace
from constants import Constants, WorldSize, LargeStringAsyncStandalone
import constants, windowtool
from languages import *
from cli import *
from hotreload import *
import hotreload, unreal_engine_tools
import asyncio, time


RPC_ACTOR = None
HELPER = None


ue.log('Hello i am a Python module')


global world
world = get_world()
# print(world)

# Use this if you want to rebuild the unreal_engine intellisense(.pyi, etc.) and cli
# rebuild_generated_modules()

# TODO: FBXFactory
# reload_all_modules()

# # Client → Server only
# helper.send_string(mode="client_to_server")
#
# # Client → Server → Multicast to all clients
# helper.send_string(mode="client_to_server_multicast")
#
# # Client → Server → Specific client
# helper.send_string(mode="client_to_server_target", target_client=SomePlayerController)
#
# # Server → Client(s)
# helper.send_string(mode="server_to_client", target_client=SomePlayerController)

# ---- Helper callbacks ----
def client_on_full_string_received(full_string):
    ue.log_warning("[CLIENT CALLBACK] Full string received!")
    ue.log_warning(f"Length: {len(full_string)}")
    ue.log_warning(f"Preview: {full_string[:200]}")

def server_on_full_string_received(full_string):
    ue.log_warning("[SERVER CALLBACK] Full string received!")
    ue.log_warning(f"Length: {len(full_string)}")
    ue.log_warning(f"Preview: {full_string[:200]}")

def progress_callback(current, total):
    ue.log(f"[PROGRESS] Chunk {current}/{total}")


# ---- Actor creation ----
def find_rpc_actor():
    ue.log("Making a LargeStringRPCActor...")
    try:
        actor = world.actor_spawn(LargeStringRPCActor)
        actor.LargeString = ue.new_object(LargeStringAsync)  # Outer = actor
        ue.log("Created new LargeStringAsync instance")
        return actor
    except Exception as e:
        ue.log_warning(f"Actor creation error: {e}")

    ue.log_error("LargeStringRPCActor NOT FOUND")
    return None



class Main:
    def test_kingdon(self):
        from kingdon import Algebra
        alg = Algebra(3, 0, 1)
        locals().update(alg.blades)
        b = alg.bivector(name='b')
        ue.log(b)

    def test_cylinder(self): #use instanced static meshes for the gridlines
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

    # this is called on game start
    def begin_play(self):
        ue.log('Begin Play on Main class')

        apply_material(
            actor_name="TestSphere", # M_Color is default
            params = {
                "Color": (0.95, 0.2, 0.1, 1),
                "Metallic": 0.8,
                "Specular": 0.5,
                "Roughness": 0.2,
                "Anisotropy": 0.1,
                "Emissive Multiplier": 10.0,
                "Ambient Occlusion": 1.0,
            }
        )

        apply_material(
            actor_name="StickManCharacter_C_0",  # runtime instance name (check via print)
            component_name="SkeletalMeshOutline",
            material_path="/Game/Materials/M_Outline.M_Outline",
            params={
                "Outline": 5.0,
                "Color": (1, 1, 1, 1),
            }
        )

        # bp_class = ue.load_object(Blueprint, '/Game/Blueprints/Assets/BP_TestSphere.BP_TestSphere')
        # actor = world.actor_spawn(bp_class.GeneratedClass, FVector(0, 0, 0), FRotator(0, 0, 0))
        #
        # print("Spawned actor:", actor)
        # for comp in actor.get_components():
        #     print(comp.get_name(), "is_registered =", comp.component_is_registered())

        # print(ue.get_editor_world().all_actors())
        #
        # print_all_actors()
        # for level in world.get_levels():  # iterate all levels in the world
        #     print("Level:", level.get_name())
        #     #
        #     # for actor in level.all_actors():  # get actors from this level
        #     #     print("  ", actor.get_name(), actor)
        # print("UOBJECT STUFF")
        # for a in self.uobject.all_actors():
        #     print(a.get_name())
        # for a in self.uobject.all_objects():
        #     print(a.get_name())

        # print("WORLD STUFF")
        # for a in world.all_actors():
        #     print(a.get_name())
        # # for a in world.all_objects():
        # #     print(a.get_name())
        #

        if KismetSystemLibrary.IsDedicatedServer():
            ue.log("BeginPlay on DEDICATED SERVER")
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
            player_controller = self.uobject.get_player_controller()
            pawn = player_controller.get_pawn()
            print(player_controller)
            print(pawn)
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

        if KismetSystemLibrary.IsDedicatedServer():
            ue.log("hello from server")
            # print("hello from server" + self.uobject.get_uproperty('StringHelloWorldProperty'))
            # print("hello from server" + self.uobject.get_uproperty('StringHelloWorldProperty2'))  # .set_metadata('Category', 'CategoryTest001')
        else:
            ue.log("hello from client")
            self.uobject.enable_input()
            self.uobject.bind_key('K', ue.IE_PRESSED, self.you_pressed_K)  # IE_AXIS, IE_DOUBLE_CLICK, IE_PRESSED, IE_RELEASED, IE_REPEAT
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

    # ------------------------------------------------------------------------
    # KEY PRESS EVENT
    # ------------------------------------------------------------------------
    def get_cube(self, filepath):
        self.uobject.call_function("ConvertImageToCubemap", filepath)
        #while(bool_unfinished)
        # then assign
        # TODO: figure out some kind of async await
        cube = self.uobject.call_function("GetCubemap")
        return cube

    def you_pressed_K(self):
        ue.log_warning("=== YOU PRESSED K ===")
        def convert_image_to_cubemap(filepath):
            if not filepath:
                return None
            cube = self.get_cube(filepath)
            # cube = self.uobject.get_property('TextureCube')
            print(cube)
            if not cube:
                ue.log_warning("Failed to convert Texture2D to TextureCube")
                return None

            return cube

        def load_image_as_texture2d(path):
            """
            Load any image type from disk into a transient Texture2D
            """
            if not os.path.exists(path):
                ue.log_warning(f"File not found: {path}")
                return None

            try:
                img = Image.open(path).convert("RGBA")
                width, height = img.size
                img_np = np.array(img, dtype=np.uint8)

                # force opaque alpha
                if img_np.shape[2] == 4:
                    img_np[:, :, 3] = 255

                data = img_np.flatten().tobytes()

                tex2d = ue.create_transient_texture(width, height, EPixelFormat.PF_R8G8B8A8)
                tex2d.texture_set_data(data)
                return tex2d

            except Exception as e:
                ue.log_warning(f"Failed to load texture: {e}")
                return None


        def change_background(mode="white"):
            # --- grab actors ---
            # SkySpheres
            # BP_SkySphere: Rendering -> Actor Hidden in Game = True
            # SM_SkySphere: Materials -> Element 0: M_SkyBox. Rendering -> Visible = True
            # M_SkyBox Emissive Multiplier = 0.5
            # M_SkyBox With ParamCube Parameter Name = Texture. SkyBoxTexture = starmap_g8k
            # SM_SkySpherePureWhite Rendering -> Visible = False
            # SM_SkySpherePureWhiteManualExposure: M_SkyBoxWhiteForManualExposure
            background = find_actor("SM_SkySphere_2") #IDK why it got the name _2
            sky_white = find_actor("SM_SkySpherePureWhiteManualExposure")
            # sky_white_autoexposure = find_actor("SM_SkySpherePureWhite")
            sky_sun_time = find_actor("BP_SkySphere")
            sky_spheres = [background, sky_white] # , sky_white_autoexposure]

            # Fog
            fogblack = find_actor("ExponentialHeightFogBlack")
            fogs = [fogblack]

            # sky_light = find_actor("SkyLight") # Need to set Visible True in editor
            # sky_light = find_actor("SkyLight5NoLowerHemisphere") # Need to set Visible True in editor
            sky_light = find_actor("SkyLight5") # Lower Hemisphere is Solid Color = True # Lower Hemisphere Color = 0,0,0,1
            sky_lights = [sky_light]

            pp_camera = find_actor("PostProcessVolumeExposureCamera") # Manual Exposure Compensation = True, 9.5
            pp_nobloom = find_actor("PostProcessVolumeRemoveBloom")  # BP_SkySphere needs to be disabled
            pp_white = find_actor("PostProcessVolumeWhite") # TODO: Tune this for the dark backgrounds
            pp_gray = find_actor("PostProcessVolumeGray")
            pp_black = find_actor("PostProcessVolumeBlack")
            post_processing_volumes = [pp_camera, pp_nobloom, pp_white, pp_gray, pp_black]

            # Reset
            sky_sun_time.SetActorHiddenInGame(True)  # Can't use Visible on this one unless targeting components
            # iterate over tne background actors
            for a in itertools.chain(sky_spheres, fogs, sky_lights, post_processing_volumes):
                if a in sky_spheres:
                    a.SetActorHiddenInGame(True)
                elif a in fogs:
                    a.SetActorHiddenInGame(True)
                elif a in sky_lights:
                    a.SetActorHiddenInGame(True)
                elif a in post_processing_volumes:
                    a.set_property("bEnabled", False)

            #sky_light.set_property("IntensityScale", 5.0)
            sky_light.SetActorHiddenInGame(False)
            pp_camera.set_property("bEnabled", True)
            pp_gray.set_property("bEnabled", True)
            # mat = ue.load_object(Material, "/Game/Materials/M_SkyBoxWhiteForManualExposure")
            # find_component(sky_white, "").set_material(0, mat)

            # sky_light.set_property("bLowerHemisphereIsSolidColor", False)
            # sky_light.set_property("LowerHemisphereColor", (0,0,0,1))
            modes = ["white", "black", "white_no_bloom", "white_no_emissive", "stars", "sky"]
            if mode in modes:
                if mode == "white":
                    sky_sun_time.SetActorHiddenInGame(False)
                    sky_white.SetActorHiddenInGame(False)
                elif mode == "black":
                    # fog.set_property("FogInscatteringColor", (0, 0, 0, 1))
                    # fogblack.SetActorHiddenInGame(False)
                    apply_material(
                        actor_name="SM_SkySphere_2",
                        material_path="/Game/Materials/M_SkyBox.M_SkyBox",
                        params={
                            "Emissive Multiplier": 0.0,
                        }
                    )
                    sky_sun_time.SetActorHiddenInGame(False)
                    background.SetActorHiddenInGame(False)
                    # pp_gray.set_property("bEnabled", False)
                    # pp_white.set_property("bEnabled", True) # make this a little darker for the black case
                elif mode == "white_no_bloom":
                    sky_sun_time.SetActorHiddenInGame(False)
                    sky_white.SetActorHiddenInGame(False)
                    pp_nobloom.set_property("bEnabled", True)
                elif mode == "white_no_emissive":
                    mat = ue.load_object(Material, "/Game/Materials/M_SkyBoxWhiteNoEmissive")
                    find_component(sky_white, "").set_material(0, mat)
                    sky_sun_time.SetActorHiddenInGame(False)
                    sky_white.SetActorHiddenInGame(False)
                elif mode == "stars":
                    mat = ue.load_object(Material, "/Game/Materials/M_SkyBox")
                    find_component(background, "").set_material(0, mat)
                    sky_sun_time.SetActorHiddenInGame(False)
                    background.SetActorHiddenInGame(False)
                    # pp_gray.set_property("bEnabled", False)
                    # pp_white.set_property("bEnabled", True)
                elif mode == "sky":
                    sky_sun_time.SetActorHiddenInGame(False)
            else:  # set image mode
                if os.path.exists(mode):
                    cubemap = convert_image_to_cubemap(mode)
                    apply_material(
                        actor_name="SM_SkySphere_2",
                        material_path="/Game/Materials/M_SkyBox",
                        params={
                            "Emissive Multiplier": 1.0,
                            "Texture": cubemap,
                        }
                    )
                    sky_sun_time.SetActorHiddenInGame(False)
                    background.SetActorHiddenInGame(False)
                else:
                    ue.log_warning("image mode requires working path")

        # change_background("sky")
        change_background(r"C:\Users\nicho\Documents\Unreal Projects\Starcel9\Images\duck.hdr")



        # reset_pyactor()
        # print(world)
        # print_all_actors()

        # <3
        # ue.log(f"World: {world}")
        #
        # global RPC_ACTOR, HELPER
        #
        # # Spawn or get the RPC actor
        # if not RPC_ACTOR:
        #     RPC_ACTOR = find_rpc_actor()
        #     if not RPC_ACTOR:
        #         ue.log_error("RPC_ACTOR not created, aborting test")
        #         return
        #
        # # Set up the helper if it doesn't exist
        # if not HELPER:
        #     HELPER = LargeStringAsyncStandalone(
        #         large_string_obj=RPC_ACTOR.LargeString,
        #         rpc_actor=RPC_ACTOR,
        #         on_received_callback=client_on_full_string_received,
        #         on_server_received_callback=server_on_full_string_received,
        #         on_progress_callback=progress_callback,
        #         auto_send=True
        #     )
        #     ue.log("Created LargeStringAsyncStandalone helper")
        #
        # # Test string
        # test_string = "Hello Unreal Async RPC! " * 100
        # ue.log_warning(f"Starting async build, length={len(test_string)}")
        #
        # try:
        #     RPC_ACTOR.LargeString.SetFromStringAsync(test_string)
        # except Exception as e:
        #     ue.log_error(f"SetFromStringAsync failed: {e}")
        #
        # # Client → Server only
        # HELPER.send_string(mode="server_only")
        #
        # # Server → All clients (multicast)
        # HELPER.send_string(mode="multicast")
        #
        # # Server → Specific client (replace `target_pc` with your player controller)
        # target_pc = self.uobject.get_player_controller()
        # HELPER.send_string(mode="client", target_client=target_pc)
        #
        # # Server → Single client (server_to_client)
        # HELPER.send_string(mode="server_to_client", target_client=target_pc)
        # <3
    # def you_pressed_K(self):
    #     ue.log_warning("=== YOU PRESSED K ===")
    #
    #     world = ue.all_worlds()[0]
    #     ue.log(f"World: {world}")
    #
    #     global RPC_ACTOR, HELPER
    #
    #     if not RPC_ACTOR:
    #         RPC_ACTOR = find_rpc_actor()
    #         if not RPC_ACTOR:
    #             return
    #
    #     if not HELPER:
    #         HELPER = setup_helper(RPC_ACTOR)
    #         if not HELPER:
    #             return
    #
    #     # TEST STRING (scale this to 1GB when ready)
    #     test_string = "Hello Unreal Async RPC! " * 100
    #     ue.log_warning(
    #         f"Starting async build, length={len(test_string)}"
    #     )
    #
    #     try:
    #         RPC_ACTOR.LargeString.SetFromStringAsync(test_string)
    #     except Exception as e:
    #         ue.log_error(f"SetFromStringAsync failed: {e}")

        # self.uobject.get_player_controller().ClientTravel("10.10.1.123:7777", ue.ETravelType.TRAVEL_Absolute)
        # ue.log_warning('travel completed')
        # ue.log("hello from client")
        # self.server_event()
        # print("hello from client" + self.uobject.get_uproperty('StringHelloWorldProperty'))
        # print("hello from client" + self.uobject.get_uproperty('StringHelloWorldProperty2'))  # .set_metadata('Category', 'CategoryTest001')


    def move_forward(self, amount):
        ue.print_string('axis value: ' + str(amount))

#
# def on_string_received(full_string):
#     print("Standalone helper received string!")
#     print("Length:", len(full_string))
#     print("Chunks received:", helper.large_string.GetChunkCount())
#     print("Preview:", full_string[:200])
#
# # Create a standalone ULargeStringAsync
# large_string = LargeStringAsync()
#
# # Example loopback send function
# def send_chunk(chunk, index, total_chunks):
#     helper.receive_chunk(chunk, index, total_chunks)
#
# # Create the helper (auto-waits for chunks)
# helper = LargeStringAsyncStandalone(
#     large_string_obj=large_string,
#     send_chunk_callback=send_chunk,
#     on_received_callback=on_string_received
# )
#
# # Start async string build
# large_string.SetFromStringAsync("Hello Unreal Standalone!" * 100000)
#
# # Now send all chunks
# helper.send_string()


# # 1GB String Test
# large_string = LargeStringAsync()
# N = 1_000_000_000 // len("X")  # Number of repeats to reach ~1GB
# test_string = "X" * N
#
# large_string.SetFromStringAsync(test_string)
#
# def on_received(full_string):
#     print("Received string!")
#     print("Length (chars):", len(full_string))
#     print("Chunk count:", helper.large_string.GetChunkCount())
#     print("Preview:", full_string[:200])  # small preview
#
# helper = LargeStringAsyncStandalone(
#     large_string_obj=large_string,
#     send_chunk_callback=lambda c,i,t: helper.receive_chunk(c,i,t),
#     on_received_callback=on_received
# )
#
# helper.send_string()
#
# #AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
# # ------------------------------------------------------------------------
# # CALLBACK: when full string is received
# # ------------------------------------------------------------------------
# def on_string_received(full_string):
#     print("[Standalone] Received full string!")
#     print("Length:", len(full_string))
#     print("Chunks received:", helper.large_string.GetChunkCount())
#     print("Preview:", full_string[:200])
#
#
# # ------------------------------------------------------------------------
# # CLIENT RPC: receive a chunk from server
# # ------------------------------------------------------------------------
# def client_receive_chunk(chunk, index, total_chunks):
#     """Client-side RPC: forward chunk to helper"""
#     helper.receive_chunk(chunk, index, total_chunks)
#
#
# # ------------------------------------------------------------------------
# # CREATE HELPER
# # ------------------------------------------------------------------------
# large_string = LargeStringAsync()
#
# helper = LargeStringAsyncStandalone(
#     large_string_obj=large_string,
#     send_chunk_callback=None,  # will be bound below
#     on_received_callback=on_string_received
# )
#
#
# # ------------------------------------------------------------------------
# # SEND CHUNK CALLBACK
# # ------------------------------------------------------------------------
# def send_chunk(chunk, index, total_chunks):
#     """Called by helper when sending chunks"""
#     if KismetSystemLibrary.IsDedicatedServer(None):
#         # Server: manually multicast to all clients
#         for pc in ue.get_editor_world().all_actors():
#             if hasattr(pc, "Client_ReceiveChunk"):
#                 pc.Client_ReceiveChunk(chunk, index, total_chunks)
#     else:
#         # Client: send to server RPC
#         if hasattr(helper.large_string, "Server_ReceiveChunk"):
#             helper.large_string.Server_ReceiveChunk(chunk, index, total_chunks)
#
# # Bind it
# helper.send_chunk_callback = send_chunk
#
#
# # ------------------------------------------------------------------------
# # START ASYNC STRING BUILD
# # ------------------------------------------------------------------------
# print("Starting LargeStringAsyncStandalone test...")
# large_string.SetFromStringAsync("Hello Unreal Standalone!" * 100)  # ~multi-MB
#
# # ------------------------------------------------------------------------
# # MANUAL SEND TRIGGER (if chunks already built)
# # ------------------------------------------------------------------------
# # Only call send_string() after chunks exist
# if hasattr(helper.large_string, "Chunks") and len(helper.large_string.Chunks) > 0:
#     print("Chunks exist, sending...")
#     helper.send_string()