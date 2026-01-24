import unreal_engine as ue
from unreal_engine.classes import Material, Texture, Texture2D, TextureCube
from unreal_engine.enums import EPixelFormat
import os, itertools
import windowtool
from PIL import Image
import numpy as np



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
                        mid.set_material_texture_parameter(pname, cube[0])
                        target_comp.set_material(material_index, mid)
                    else:
                        ue.log_warning(f"Failed to convert HDR to cubemap: {v}")

                convert_hdr_to_cubemap(bp_helper, v, on_cube_ready)

            else:
                tex = load_texture_any(v)
                if tex:
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


def change_background(background="white"):
    # TODO: Add transparency and green screen defaults https://github.com/historia-Inc/WindowTransparency https://www.fab.com/listings/a967c271-f440-4bc2-93f8-3699122f0f7b https://forums.unrealengine.com/t/transparent-window/123446
    # --- grab actors ---
    # SkySpheres
    # BP_SkySphere: Rendering -> Actor Hidden in Game = True
    # SM_SkySphere: Materials -> Element 0: M_SkyBox. Rendering -> Visible = True
    # M_SkyBox Emissive Multiplier = 0.5
    # M_SkyBox With ParamCube Parameter Name = Texture. SkyBoxTexture = starmap_g8k
    # SM_SkySpherePureWhite Rendering -> Visible = False
    # SM_SkySpherePureWhiteManualExposure: M_SkyBoxWhiteForManualExposure
    sky = find_actor("SM_SkySphere_2")  # IDK why it got the name _2
    sky_white = find_actor("SM_SkySpherePureWhiteManualExposure")
    # sky_white_autoexposure = find_actor("SM_SkySpherePureWhite")
    sky_sun_time = find_actor("BP_SkySphere")
    sky_spheres = [sky, sky_white]  # , sky_white_autoexposure]

    # Fog
    fogblack = find_actor("ExponentialHeightFogBlack")
    fogs = [fogblack]

    # sky_light = find_actor("SkyLight") # Need to set Visible True in editor
    # sky_light = find_actor("SkyLight5NoLowerHemisphere") # Need to set Visible True in editor
    sky_light = find_actor("SkyLight5")  # Lower Hemisphere is Solid Color = True # Lower Hemisphere Color = 0,0,0,1
    sky_lights = [sky_light]

    pp_camera = find_actor("PostProcessVolumeExposureCamera")  # Manual Exposure Compensation = True, 9.5
    pp_nobloom = find_actor("PostProcessVolumeDisableBloom")  # BP_SkySphere needs to be disabled
    pp_novignette = find_actor("PostProcessVolumeDisableVignette")
    pp_white = find_actor("PostProcessVolumeWhite")  # TODO: Tune this for the dark backgrounds
    pp_gray = find_actor("PostProcessVolumeGray")
    pp_black = find_actor("PostProcessVolumeBlack")
    post_processing_volumes = [pp_camera, pp_nobloom, pp_novignette, pp_white, pp_gray, pp_black]

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

    # sky_light.set_property("IntensityScale", 5.0)
    sky_light.SetActorHiddenInGame(False)
    pp_camera.set_property("bEnabled", True)
    pp_gray.set_property("bEnabled", True)
    # mat = ue.load_object(Material, "/Game/Materials/M_SkyBoxWhiteForManualExposure")
    # find_component(sky_white, "").set_material(0, mat)

    # sky_light.set_property("bLowerHemisphereIsSolidColor", False)
    # sky_light.set_property("LowerHemisphereColor", (0,0,0,1))
    py_actor.call_function("DisableWindowTransparent")
    modes = ["white", "black", "white_no_bloom", "white_no_emissive", "stars", "sky", "transparent"]
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
    else:  # set image mode
        if os.path.exists(background):
            py_actor = find_actor("BP_PyActor")
            print(py_actor)
            apply_material(
                actor_name="SM_SkySphere_2",
                material_path="/Game/Materials/M_SkyBox",
                bp_helper=py_actor,
                params={
                    "Emissive Multiplier": 1.0,
                    "Texture": background,
                }
            )
            sky_sun_time.ManuallySetSunPosition = False
            sky_sun_time.SetActorHiddenInGame(False)
            sky.SetActorHiddenInGame(False)
        else:
            ue.log_warning("image mode requires working path")