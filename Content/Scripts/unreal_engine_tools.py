import unreal_engine as ue
from unreal_engine.classes import Material, Texture, Texture2D, TextureCube, Blueprint
from unreal_engine.enums import EPixelFormat, EComponentMobility
import os, itertools, time, json
import windowtool
from PIL import Image
import numpy as np
try:
    from unreal_engine.enums import EWorldType
except ImportError:
    # Not implemented yet - for some reason EWorldType isn't a UENUM so the automagic importer can't work
    class EWorldType:
        NONE, Game, Editor, PIE, EditorPreview, GamePreview, Inactive = range(7)


class LargeStringAsyncStandalone: # The default settings will not work if your network is poor or your cpu is slow. If my laptop is unplugged, for example, I need less aggressive settings.
    """
    Standalone helper for LargeStringAsync with multiple send modes.
    Uses ticker-based sending with conservative rate limiting.
    Supports configurable chunk size.
    """
    def __init__(
            self,
            large_string_obj=None,
            rpc_actor=None,
            on_received_callback=None,
            on_server_received_callback=None,
            on_progress_callback=None,
            auto_send=True,
            chunks_per_tick=1,  # Send N chunks per tick
            ticks_between_sends=2,  # Wait N ticks between sends
            chunk_size=8*1024  # Chunk size in bytes (None = use default 63KB)
    ):
        self.large_string_obj = large_string_obj
        self.rpc_actor = rpc_actor
        self.on_received_callback = on_received_callback
        self.on_server_received_callback = on_server_received_callback
        self.on_progress_callback = on_progress_callback
        self.auto_send = auto_send
        self.pending_mode = None
        self.pending_target_client = None
        self.chunks_per_tick = chunks_per_tick
        self.ticks_between_sends = ticks_between_sends

        # Send state
        self.current_chunk_index = 0
        self.total_chunks = 0
        self.current_send_mode = None
        self.is_sending = False
        self.ticker = None
        self.tick_counter = 0

        # Set chunk size if specified
        if chunk_size is not None and self.large_string_obj:
            self.large_string_obj.SetChunkSize(chunk_size)
            ue.log(f"Set chunk size to {chunk_size} bytes")

        # Bind to OnChunksBuilt if auto_send is enabled
        if self.auto_send and self.large_string_obj:
            try:
                self.large_string_obj.bind_event('OnChunksBuilt', self._on_chunks_built)
            except Exception as e:
                ue.log_error(f"Failed to bind OnChunksBuilt: {e}")

        # Bind to server and client received callbacks
        if self.rpc_actor:
            try:
                self.rpc_actor.bind_event('OnServerStringReceived', self._on_server_string_received)
            except Exception as e:
                ue.log_error(f"Failed to bind OnServerStringReceived: {e}")

            try:
                self.rpc_actor.bind_event('OnClientStringReceived', self._on_client_string_received)
            except Exception as e:
                ue.log_error(f"Failed to bind OnClientStringReceived: {e}")

    def _on_chunks_built(self):
        """Called when chunks are ready"""
        chunk_size = self.large_string_obj.GetChunkSize()
        chunk_count = self.large_string_obj.GetChunkCount()
        ue.log(f"Chunks built: {chunk_count} chunks @ {chunk_size} bytes each")

        if self.auto_send and self.pending_mode:
            self._execute_send()

    def _on_server_string_received(self, full_string):
        """Called when server receives the full string"""
        ue.log_warning(f"[PYTHON SERVER CALLBACK] Received full string: {len(full_string)} chars")

        # Call user's server callback
        if self.on_server_received_callback:
            self.on_server_received_callback(full_string)

        # Handle client_to_server_then_multicast mode
        if self.pending_mode == "client_to_server_then_multicast":
            ue.log_warning("[PYTHON] Triggering multicast after server receipt")
            self.pending_mode = None
            self.pending_target_client = None
            self._start_send("multicast")

    def _on_client_string_received(self, full_string):
        """Called when client receives the full string"""
        ue.log_warning(f"[PYTHON CLIENT CALLBACK] Received full string: {len(full_string)} chars")

        # Call user's received callback
        if self.on_received_callback:
            self.on_received_callback(full_string)

    def _ticker_callback(self, delta_time):
        """Ticker callback - sends chunks progressively"""
        if not self.is_sending:
            return False  # Stop ticker

        # Increment tick counter
        self.tick_counter += 1

        # Only send every N ticks
        if self.tick_counter < self.ticks_between_sends:
            return True  # Continue ticking but don't send yet

        # Reset tick counter
        self.tick_counter = 0

        # Send a batch of chunks this tick
        end_index = min(self.current_chunk_index + self.chunks_per_tick, self.total_chunks)

        for i in range(self.current_chunk_index, end_index):
            chunk = self.large_string_obj.GetChunk(i)

            # Verify chunk size is under 64KB
            chunk_size = len(chunk)
            if chunk_size > 65536:
                ue.log_error(f"Chunk {i} is {chunk_size} bytes - exceeds 64KB RPC limit!")
                continue

            try:
                if self.current_send_mode == "server":
                    self.rpc_actor.Server_ReceiveChunk(chunk, i, self.total_chunks)
                elif self.current_send_mode == "multicast":
                    self.rpc_actor.Multicast_ReceiveChunk(chunk, i, self.total_chunks)
                elif self.current_send_mode == "client":
                    self.rpc_actor.Client_ReceiveChunk(chunk, i, self.total_chunks)
            except Exception as e:
                ue.log_error(f"Failed to send chunk {i}: {e}")
                # On error, stop sending to avoid further issues
                self.is_sending = False
                return False

        # Update progress
        if self.on_progress_callback:
            self.on_progress_callback(end_index, self.total_chunks)

        # Log progress periodically
        if end_index % 100 == 0 or end_index == self.total_chunks:
            ue.log_warning(f"[PYTHON] Sent {end_index}/{self.total_chunks} chunks ({(end_index * 100.0 / self.total_chunks):.1f}%)")

        self.current_chunk_index = end_index

        # Check if done
        if self.current_chunk_index >= self.total_chunks:
            ue.log_warning(f"[PYTHON] Send complete: {self.total_chunks} chunks")
            self.is_sending = False
            self.current_send_mode = None
            self.ticker = None
            return False  # Stop ticker

        return True  # Continue ticking

    def send_string(self, mode="server_only", target_client=None):
        """
        Send the large string using specified mode

        Args:
            mode: Send mode - one of:
                - "server_only": Client → Server
                - "multicast": Server → All Clients
                - "client": Server → Specific Client
                - "server_to_client": Server → Single Client (explicit)
                - "client_to_server_then_multicast": Client → Server → All Clients
            target_client: Required for "client" and "server_to_client" modes
        """
        if not self.large_string_obj or not self.rpc_actor:
            ue.log_error("LargeStringAsync or RPC Actor not set")
            return

        if self.is_sending:
            ue.log_warning("Already sending chunks, ignoring new send request")
            return

        self.pending_mode = mode
        self.pending_target_client = target_client

        # Validate target_client for modes that need it
        if mode in ["client", "server_to_client"] and not target_client:
            ue.log_error(f"Mode '{mode}' requires target_client parameter")
            return

        # If chunks are already built, send immediately
        if self.large_string_obj.GetChunkCount() > 0:
            self._execute_send()
        else:
            ue.log("Waiting for chunks to be built...")

    def _execute_send(self):
        """Execute the actual send operation based on pending mode"""
        mode = self.pending_mode
        target_client = self.pending_target_client

        ue.log_warning(f"[PYTHON] Executing send with mode: {mode}")

        if mode == "server_only":
            self._start_send("server")
        elif mode == "multicast":
            self._start_send("multicast")
        elif mode in ["client", "server_to_client"]:
            self._start_send("client")
        elif mode == "client_to_server_then_multicast":
            # First send to server, multicast will be triggered in callback
            self._start_send("server")
            # Don't clear pending_mode yet - we need it for the callback
            return
        else:
            ue.log_error(f"Unknown send mode: {mode}")
            return

        # Clear pending mode (except for client_to_server_then_multicast)
        if mode != "client_to_server_then_multicast":
            self.pending_mode = None
            self.pending_target_client = None

    def _start_send(self, mode):
        """Start sending chunks via ticker"""
        self.current_chunk_index = 0
        self.total_chunks = self.large_string_obj.GetChunkCount()
        self.current_send_mode = mode
        self.is_sending = True
        self.tick_counter = 0

        chunk_size = self.large_string_obj.GetChunkSize()
        ue.log_warning(f"[PYTHON] Starting send: {self.total_chunks} chunks @ {chunk_size} bytes, mode={mode}, "
                       f"{self.chunks_per_tick} chunks every {self.ticks_between_sends} ticks")

        # Start ticker - IMPORTANT: store reference to prevent GC
        self.ticker = ue.add_ticker(self._ticker_callback)
        ue.log("Ticker started")

    def stop_sending(self):
        """Stop sending chunks"""
        self.is_sending = False
        self.current_send_mode = None
        self.ticker = None
        ue.log("Sending stopped")

    def unbind_events(self):
        """Unbind all events"""
        # Stop any active sending
        self.stop_sending()

        if self.large_string_obj:
            try:
                self.large_string_obj.unbind_event('OnChunksBuilt', self._on_chunks_built)
            except:
                pass

        if self.rpc_actor:
            try:
                self.rpc_actor.unbind_event('OnServerStringReceived', self._on_server_string_received)
            except:
                pass
            try:
                self.rpc_actor.unbind_event('OnClientStringReceived', self._on_client_string_received)
            except:
                pass

    def reset(self):
        """Reset the helper state"""
        self.stop_sending()
        self.pending_mode = None
        self.pending_target_client = None
        self.current_chunk_index = 0
        self.total_chunks = 0
        ue.log("LargeStringAsyncStandalone reset")




# Example client/server callbacks
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


global tickers
tickers = []

def get_world():
    scmaps = []
    world = None
    if not world:
        for _world in ue.all_worlds():
            if _world.get_name() == "StarcelExampleMap":
                scmaps.append(_world)

        if len(scmaps) > 1:
            ue.log_warning("Found more than one StarcelExampleMap:")
            print([w.get_name() for w in scmaps])

        if len(scmaps) == 1:
            world = scmaps[0]
        else:
            ue.log_warning("Using the first world found")
            world = scmaps[0] # len(scmaps) - 1

        if not world:
            world = ue.all_worlds()[0]
            ue.log_warning("Can't find world, assigning the first existing world, " + world.get_name())

    return world


def _GetWorld(): # alternative from https://github.com/dfb/UnrealEnginePython/tree/modus
    '''Returns the best guess of what the "current" world to use is'''
    worlds = {} # worldType -> *first* world of that type
    for w in ue.all_worlds():
        t = w.get_world_type()
        if worlds.get(t) is None:
            worlds[t] = w
        # print(w, w.get_world_type()) # seems to return number instead of enum

    return worlds.get(EWorldType.Game) or worlds.get(EWorldType.PIE) or worlds.get(EWorldType.Editor)


global world
world = get_world()
print("ue tools world", world)


def find_actor(name):
    print("Finding actor by name", name)
    actor_list = []
    for a in world.all_actors():
        if a.get_name() == name:
            actor_list.append(a)
    if not actor_list:
        print("No exact match found, finding any actor with name that contains", name)
        for a in world.all_actors():
            if name in a.get_name():
                actor_list.append(a)

    # print(type(actor))
    # print(actor.__class__.__name__)
    if not actor_list or actor_list.__class__.__name__ == 'NoneType':
        ue.log_error(f"Actor not found: {name}: {[a.get_name() for a in actor_list]}")
        return None
    else:
        if len(actor_list) > 1:
            ue.log_warning(f"Found more than one actor: {[a.get_name() for a in actor_list]}")

        return actor_list[0]


global py_actor
py_actor = find_actor("BP_PyActor")
print("ue tools pyactor", world)


def find_actors(name):
    print("Finding actors by name", name)
    actor_list = []
    for a in world.all_actors():
        if a.get_name() == name:
            actor_list.append(a)
    if not actor_list:
        print("No exact matches found, finding any actors with name that contains", name)
        for a in world.all_actors():
            if name in a.get_name():
                actor_list.append(a)
    # print(type(actor))
    # print(actor.__class__.__name__)
    if not actor_list or actor_list.__class__.__name__ == 'NoneType': # (actor_list[0].__class__.__name__ == 'NoneType')
        ue.log_warning(f"Actor not found: {name}: {[a.get_name() for a in actor_list]}")
        return None
    else:
        print("Found actors:", actor_list)
        return actor_list



def find_component(actor, name):
    print("Finding component by name", name, "in actor", actor)
    if actor is None: # or (actor.__class__.__name__ == 'NoneType')
        ue.log_warning(f"Actor not found: {actor}")
        return None
    elif actor.__class__.__name__ == 'NoneType':
            ue.log_warning(f"Actor not found: {actor}")
            return None

    component_list = []
    if name:
        for component in actor.get_components():
            if component.get_name() == name:
                component_list.append(component)
        if not component_list:
            print("Looking for any component name that contains", name)
            for component in actor.get_components():
                if name in component.get_name():
                    component_list.append(component)
    else:
        print("Defaulting to search for a MeshComponent")
        for component in actor.get_components():
            if "MeshComponent" in component.get_class().get_name():
                component_list.append(component)

    if not component_list or component_list.__class__.__name__ == 'NoneType':
        print(f"Component not found on actor {name}: {actor.get_name()}")
        return None
    else:
        if len(component_list) > 1:
            ue.log_warning(f"Found more than one actor: {[c.get_name() for c in component_list]}")

        return component_list[0]


def print_all_actors():
    actors = world.all_actors()
    for a in actors:
        print(a.get_name())

def get_content_folder():
    return os.path.abspath(ue.get_content_dir())

def get_game_folder():
    return os.path.abspath(ue.get_content_dir())

def get_scripts_folder():
    return os.path.join(os.path.abspath(ue.get_content_dir()), "Scripts")


def restore_from_desktop_background():
    py_actor.call_function('RestoreFromDesktopBackground')

def embed_as_desktop_background():
    py_actor.call_function('SetWindowAsDesktopBackground')

def fullscreen():
    py_actor.call_function('SetFullscreen')

def windowed():
    py_actor.call_function('SetWindowed')

def windowed_fullscreen():
    py_actor.call_function('SetWindowedFullscreen')

def set_starcel_as_desktop(disable_animations=None):
    windowed_fullscreen()
    windowtool.stop_all_background_hooks_systemwide()
    windowtool.start_background_hook("../../../Starcel9Client.exe", expand_to_screen=True, custom_rect=(-10, 0, 1940, 1085))  # , monitor_number=0)
    # OPTIONAL: Disable Windows animations so you don't have to wait for the window to maximize
    if disable_animations is not None:
        windowtool.set_global_window_animations(disable_animations)


# relevant editor access https://github.com/20tab/UnrealEnginePython/issues/655 https://github.com/20tab/UnrealEnginePython/issues/363
# for c in actor.get_components():
# for c in actor.get_components_by_type():
# for c in actor.get_components_by_tag():


def convert_image_to_hdr(filepath, output_dir=None):
    """
    Converts any image (PNG/JPG/WebP/etc.) to HDR format (.hdr)
    using Pillow. Returns path to HDR file.
    """
    if not os.path.exists(filepath):
        ue.log_warning(f"File not found: {filepath}")
        return None

    img = Image.open(filepath).convert("RGB")
    width, height = img.size

    if output_dir is None:
        output_dir = os.path.dirname(filepath)

    base_name = os.path.splitext(os.path.basename(filepath))[0]
    hdr_path = os.path.join(output_dir, base_name + ".hdr")

    try:
        img.save(hdr_path, format="HDR")
        return hdr_path
    except Exception as e:
        ue.log_warning(f"Failed to convert {filepath} to HDR: {e}")
        return None


def convert_hdr_to_cubemap(bp_helper, hdr_path, callback):
    """
    Convert HDR file to TextureCube using BP_HDRToCubemap.
    Calls `callback(cube)` when finished.
    """
    if not bp_helper or not hdr_path:
        return

    bp_helper.call_function("ConvertImageToCubemap", hdr_path)

    def poll(delta_time):
        if bp_helper.CubemapFinished:
            cube = bp_helper.call_function("GetCubemap")
            bp_helper.CubemapFinished = False
            if callback:
                callback(cube)
            return False  # stop ticker
        return True  # continue ticking

    tickers.append(ue.add_ticker(poll)) # assignment required or gc will destroy



def load_texture_any(path_or_obj):
    """
    Load a texture from:
      - Unreal asset path: /Game/Textures/T_Example.T_Example
      - Filesystem path: any image type (png, jpg, webp, exr, etc.)
      - Already-loaded UE object (Texture, Texture2D, TextureCube)
      - HDR file path (returned as string for cubemap conversion)
    Returns a Texture, Texture2D, TextureCube, or HDR path usable in apply_material.
    """
    if not path_or_obj:
        return None

    # Already a UE object
    if hasattr(path_or_obj, "get_class") and "Texture" in path_or_obj.get_class().get_name():
        return path_or_obj

    # String paths
    if isinstance(path_or_obj, str):
        # HDR file — just pass path
        if path_or_obj.lower().endswith(".hdr"):
            if os.path.exists(path_or_obj):
                return path_or_obj
            else:
                ue.log_warning(f"HDR path does not exist: {path_or_obj}")
                return None

        # Unreal asset path
        if path_or_obj.startswith("/Game"):
            tex = ue.load_object(Texture, path_or_obj)
            if not tex:
                ue.log_warning(f"Failed to load Unreal asset texture: {path_or_obj}")
            return tex

        # Filesystem image path (PNG, JPG, WebP, EXR, etc.)
        if os.path.exists(path_or_obj):
            try:
                img = Image.open(path_or_obj).convert("RGBA")
                width, height = img.size
                data = np.array(img, dtype=np.uint8).flatten().tobytes()
                texture = ue.create_transient_texture(width, height, EPixelFormat.PF_R8G8B8A8)
                texture.texture_set_data(data)
                return texture
            except Exception as e:
                ue.log_warning(f"Exception loading texture '{path_or_obj}': {e}")
                return None
        else:
            ue.log_warning(f"Path does not exist: {path_or_obj}")
            return None

    ue.log_warning(f"Unsupported texture input: {path_or_obj} ({type(path_or_obj)})")
    return None



def apply_material(
    actor = None,
    actor_name=None,
    component_name=None,
    material_path="/Game/Materials/M_Color.M_Color",
    material_index=0,
    params=None,
    bp_helper=find_actor("BP_PyActor"),  # optional Blueprint actor for cubemap conversion
):
    """
    Apply a material and set parameters by type.
    params example:
        {
            "Emissive Multiplier": 1.0,
            "Color": (1,1,1),
            "Texture": "C:/sky.png"       # any image type
            "Cube": "/Game/Textures/myCube"  # TextureCube asset
        }
    """
    params = params or {}

    if actor is None and (actor_name is None or not actor_name):
        ue.log_warning("No actor or actor name set")

    if actor is None:
        actor = find_actor(actor_name)

    target_comp = find_component(actor, component_name)

    mat = ue.load_object(Material, material_path)
    if not mat:
        ue.log_warning(f"Material not found: {material_path}")

    mid = target_comp.create_material_instance_dynamic(mat)

    for pname, v in params.items(): # pname is parameter name, v is value

        # --- Scalar ---
        if isinstance(v, (int, float)):
            mid.set_material_scalar_parameter(pname, float(v))

        # --- Vector ---
        elif isinstance(v, (tuple, list)) and len(v) >= 3:
            mid.set_material_vector_parameter(pname, ue.FVector(v[0], v[1], v[2]))

        # --- String path ---
        elif isinstance(v, str):

            # HDR → convert to TextureCube asynchronously
            if v.lower().endswith(".hdr") and bp_helper:
                def on_cube_ready(cube):
                    if cube:
                        print("Created cubemap, applying it to material")
                        print(cube)
                        mid.set_material_texture_parameter(pname, cube[0])
                        target_comp.set_material(material_index, mid)
                    else:
                        ue.log_warning(f"Failed to convert HDR to cubemap: {v}")

                convert_hdr_to_cubemap(bp_helper, v, on_cube_ready)

            else:
                tex = load_texture_any(v)
                if tex:
                    mat = ue.load_object(Material, "/Game/Materials/M_SkyBoxImage.M_SkyBoxImage")
                    if not mat:
                        ue.log_warning(f"Material not found: {material_path}")

                    mid = target_comp.create_material_instance_dynamic(mat)

                    mid.set_material_texture_parameter(pname, tex)
                    target_comp.set_material(material_index, mid)  # assign immediately
                else:
                    ue.log_warning(f"Could not load texture for param: {pname}")

        # --- Already-loaded UE texture ---
        elif hasattr(v, "get_class") and "Texture" in v.get_class().get_name():
            mid.set_material_texture_parameter(pname, v)
            target_comp.set_material(material_index, mid)  # assign immediately

        else:
            ue.log_warning(f"Unsupported material param type: {pname} = {type(v)}")

    # Assign the MID if no HDR parameters (they handle assignment asynchronously)
    if not any(isinstance(v, str) and v.lower().endswith(".hdr") for v in params.values()):
        target_comp.set_material(material_index, mid)

    return mid


def reset_backgrounds():
    global py_actor
    try:
        print(py_actor.is_valid())
    except Exception as e:
        print("Error with pyactor", e)
        py_actor = find_actor("BP_PyActor")
        print(py_actor)

    # grab actors for background
    sky = find_actor("SM_SkySphere_2")  # IDK why it got the name _2
    sky_white = find_actor("SM_SkySpherePureWhiteManualExposure")
    # sky_white_autoexposure = find_actor("SM_SkySpherePureWhite")
    sky_video = find_actor("BP_VideoSkySphere_8")  # IDK why it got the name _8
    sky_sun_time = find_actor("BP_SkySphere")
    sky_spheres = [sky, sky_white, sky_video, sky_sun_time]  # , sky_white_autoexposure]

    # Fog
    fogblack = find_actor("ExponentialHeightFogBlack")
    fogs = [fogblack]

    # sky_light = find_actor("SkyLight") # Need to set Visible True in editor
    # sky_light = find_actor("SkyLight5NoLowerHemisphere") # Need to set Visible True in editor
    sky_light = find_actor("SkyLight5")  # Lower Hemisphere is Solid Color = True # Lower Hemisphere Color = 0,0,0,1
    sky_light_15 = find_actor("BP_SkyLight_2")
    sky_lights = [sky_light, sky_light_15]

    pp_camera = find_actor("PostProcessVolumeExposureCamera")  # Manual Exposure Compensation = True, 9.5
    pp_nobloom = find_actor("PostProcessVolumeDisableBloom")  # BP_SkySphere needs to be disabled
    pp_novignette = find_actor("PostProcessVolumeDisableVignette")
    pp_white = find_actor("PostProcessVolumeWhite")  # TODO: Tune this for the dark backgrounds
    pp_gray = find_actor("PostProcessVolumeGray")
    pp_black = find_actor("PostProcessVolumeBlack")
    post_processing_volumes = [pp_camera, pp_nobloom, pp_novignette, pp_white, pp_gray, pp_black]

    # Reset
    # sky_sun_time.SetActorHiddenInGame(True)  # Can't use Visible on this one unless targeting components
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

    # sky_light.set_property("IntensityScale", 5.0)
    sky_light.SetActorHiddenInGame(False)
    pp_camera.set_property("bEnabled", True)
    pp_gray.set_property("bEnabled", True)
    # mat = ue.load_object(Material, "/Game/Materials/M_SkyBoxWhiteForManualExposure")
    # find_component(sky_white, "").set_material(0, mat)

    # sky_light.set_property("bLowerHemisphereIsSolidColor", False)
    # sky_light.set_property("LowerHemisphereColor", (0,0,0,1))
    py_actor.call_function("DisableWindowTransparent")


def change_background(background="white", path="file://"):
    global py_actor
    try:
        print(py_actor.is_valid())
    except Exception as e:
        print("Error with pyactor", e)
        py_actor = find_actor("BP_PyActor")
        print(py_actor)

    # grab actors for background
    sky = find_actor("SM_SkySphere_2")  # IDK why it got the name _2
    sky_white = find_actor("SM_SkySpherePureWhiteManualExposure")
    # sky_white_autoexposure = find_actor("SM_SkySpherePureWhite")
    sky_video = find_actor("BP_VideoSkySphere_8")  # IDK why it got the name _8
    sky_sun_time = find_actor("BP_SkySphere")
    sky_spheres = [sky, sky_white, sky_video, sky_sun_time]  # , sky_white_autoexposure]

    # Fog
    fogblack = find_actor("ExponentialHeightFogBlack")
    fogs = [fogblack]

    # sky_light = find_actor("SkyLight") # Need to set Visible True in editor
    # sky_light = find_actor("SkyLight5NoLowerHemisphere") # Need to set Visible True in editor
    sky_light = find_actor("SkyLight5")  # Lower Hemisphere is Solid Color = True # Lower Hemisphere Color = 0,0,0,1
    sky_light_15 = find_actor("BP_SkyLight_2")
    sky_lights = [sky_light, sky_light_15]

    pp_camera = find_actor("PostProcessVolumeExposureCamera")  # Manual Exposure Compensation = True, 9.5
    pp_nobloom = find_actor("PostProcessVolumeDisableBloom")  # BP_SkySphere needs to be disabled
    pp_novignette = find_actor("PostProcessVolumeDisableVignette")
    pp_white = find_actor("PostProcessVolumeWhite")  # TODO: Tune this for the dark backgrounds
    pp_gray = find_actor("PostProcessVolumeGray")
    pp_black = find_actor("PostProcessVolumeBlack")
    post_processing_volumes = [pp_camera, pp_nobloom, pp_novignette, pp_white, pp_gray, pp_black]

    # Reset
    # sky_sun_time.SetActorHiddenInGame(True)  # Can't use Visible on this one unless targeting components
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

    # sky_light.set_property("IntensityScale", 5.0)
    sky_light.SetActorHiddenInGame(False)
    pp_camera.set_property("bEnabled", True)
    pp_gray.set_property("bEnabled", True)
    # mat = ue.load_object(Material, "/Game/Materials/M_SkyBoxWhiteForManualExposure")
    # find_component(sky_white, "").set_material(0, mat)

    # sky_light.set_property("bLowerHemisphereIsSolidColor", False)
    # sky_light.set_property("LowerHemisphereColor", (0,0,0,1))
    py_actor.call_function("DisableWindowTransparent")

    # TODO: Add transparency and green screen defaults https://github.com/historia-Inc/WindowTransparency https://www.fab.com/listings/a967c271-f440-4bc2-93f8-3699122f0f7b https://forums.unrealengine.com/t/transparent-window/123446
    modes = ["white", "black", "white_no_bloom", "white_no_emissive", "stars", "sky", "image", "video", "transparent"]
    if background in modes:
        if background == "white":
            mat = ue.load_object(Material, "/Game/Materials/M_SkyBoxWhiteForManualExposure")
            find_component(sky_white, "").set_material(0, mat)
            sky_sun_time.ManuallySetSunPosition = True
            sky_sun_time.SetActorHiddenInGame(False)
            sky_white.SetActorHiddenInGame(False)
        elif background == "black":
            # fog.set_property("FogInscatteringColor", (0, 0, 0, 1))
            # fogblack.SetActorHiddenInGame(False)
            apply_material(
                actor_name="SM_SkySphere_2",
                material_path="/Game/Materials/M_SkyBox.M_SkyBox",
                params={
                    "Color": (0,0,0,1),
                    "Emissive Multiplier": 0.0,
                }
            )
            sky_sun_time.ManuallySetSunPosition = True
            sky_sun_time.SetActorHiddenInGame(False)
            sky.SetActorHiddenInGame(False)
            # pp_gray.set_property("bEnabled", False)
            # pp_white.set_property("bEnabled", True) # make this a little darker for the black case
        elif background == "white_no_bloom":
            mat = ue.load_object(Material, "/Game/Materials/M_SkyBoxWhiteForManualExposure")
            find_component(sky_white, "").set_material(0, mat)
            sky_sun_time.ManuallySetSunPosition = True
            sky_sun_time.SetActorHiddenInGame(False)
            sky_white.SetActorHiddenInGame(False)
            pp_nobloom.set_property("bEnabled", True)
            pp_novignette.set_property("bEnabled", True)
        elif background == "white_no_emissive":
            mat = ue.load_object(Material, "/Game/Materials/M_SkyBoxWhiteNoEmissive")
            find_component(sky_white, "").set_material(0, mat)
            sky_sun_time.ManuallySetSunPosition = True
            sky_sun_time.SetActorHiddenInGame(False)
            sky_white.SetActorHiddenInGame(False)
        elif background == "stars":
            mat = ue.load_object(Material, "/Game/Materials/M_SkyBox")
            find_component(sky, "").set_material(0, mat)
            sky_sun_time.ManuallySetSunPosition = True
            sky_sun_time.SetActorHiddenInGame(False)
            sky.SetActorHiddenInGame(False)
            # pp_gray.set_property("bEnabled", False)
            # pp_white.set_property("bEnabled", True)
        elif background == "sky":
            sky_sun_time.ManuallySetSunPosition = False
            sky_sun_time.SetActorHiddenInGame(False)
        elif background == "image":  # TODO: Make video and image auto detect
            if os.path.exists(path):
                py_actor = find_actor("BP_PyActor")
                # print(py_actor)
                apply_material(
                    actor_name="SM_SkySphere_2",
                    material_path="/Game/Materials/M_SkyBox",
                    bp_helper=py_actor,
                    params={
                        "Emissive Multiplier": 1.0,
                        "Texture": path,
                    }
                )
                sky_sun_time.ManuallySetSunPosition = False
                sky_sun_time.SetActorHiddenInGame(False)
                sky.SetActorHiddenInGame(False)
            else:
                ue.log_warning("image mode requires working path")
        elif background == "video":  # TODO: HISPlayer Unreal Engine plugin for faster playback
            if os.path.exists(path):
                ue_path = "file://" + path
                sky_light.SetActorHiddenInGame(True)
                # light_bp = ue.load_object(Blueprint, '/Game/Blueprints/Assets/BP_SkyLight.BP_SkyLight')
                # sky_light_15 = world.actor_spawn(light_bp.GeneratedClass)
                sky_light_15.SetActorHiddenInGame(False)
                sky_light_15.call_function("SetIntensity", 15) # required to actually get the light to activate
                # location = sky_light_15.get_actor_location()
                # location.z += 10
                # sky_light_15.set_actor_location(location)
                # sky_light_15.get_actor_component("SkyLightComponent0").Visible.Mobility = EComponentMobility.Movable
                # sky_light_15.get_actor_component("SkyLightComponent0").Visible = True # sky_light_15.get_actor_component("SkyLightComponent0").Visible = False  force the light to reload
                sky_sun_time.ManuallySetSunPosition = True
                sky_sun_time.SetActorHiddenInGame(False)
                sky_video.SetActorHiddenInGame(False)
                sky_video.call_function("SetVideoBackground", ue_path)
            else:
                ue.log_warning("video mode requires working path")
        elif background == "transparent":
            # mat = ue.load_object(Material, "/Game/Materials/M_SkyBoxWhiteForManualExposure")
            # find_component(sky_white, "").set_material(0, mat)
            # sky_sun_time.ManuallySetSunPosition = True
            # sky_sun_time.SetActorHiddenInGame(False)
            # sky_white.SetActorHiddenInGame(False)
            # apply_material(
            #     actor_name="SM_SkySphere_2",
            #     material_path="/Game/Materials/M_Color.M_Color",
            #     params={
            #         "Color": (0,1,0,1),
            #         "Emissive Multiplier": 1.0,
            #     }
            # )
            mat = ue.load_object(Material, "/Game/Materials/M_SkyBoxGreen")
            find_component(sky, "").set_material(0, mat)
            pp_novignette.set_property("bEnabled", True)
            py_actor.call_function("SetWindowTransparent")
            sky_sun_time.ManuallySetSunPosition = True
            sky_sun_time.SetActorHiddenInGame(False)
            sky.SetActorHiddenInGame(False)

    else:
        print("mode not found")