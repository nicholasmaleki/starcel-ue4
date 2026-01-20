import unreal_engine as ue
from unreal_engine.classes import Material, Texture, Texture2D, TextureCube
from unreal_engine.enums import EPixelFormat
import os, itertools
import windowtool
from PIL import Image
import numpy as np

def get_world():
    scmaps = []
    world = None
    if not world:
        for _world in ue.all_worlds():
            if _world.get_name() == "StarcelExampleMap":
                scmaps.append(_world)

        if len(scmaps) == 1:
            world = scmaps[0]
        else:
            world = scmaps[0] # len(scmaps) - 1
            ue.log_warning("There is more than one StarcelExampleMap world, using the first one found")

        if not world:
            world = ue.all_worlds()[0]
            ue.log_warning("Can't find world, assigning the first existing world, " + world.get_name())

    return world

global world
world = get_world()

def find_actor(name):
    actor_list = []
    for a in world.all_actors():
        if a.get_name() == name:
            actor_list.append(a)
    if not actor_list:
        print("Looking for actors with inputted name in the actor name")
        for a in world.all_actors():
            if name in a.get_name():
                actor_list.append(a)

    # print(type(actor))
    # print(actor.__class__.__name__)
    if len(actor_list) > 1:
        ue.log_warning(f"Found more than one actor: {actor_list}")

    if (actor_list is None) or (actor_list[0].__class__.__name__ == 'NoneType'):
        ue.log_warning(f"Actor not found: {actor_list}")

    return actor_list[0]

def find_component(actor, name):
    if (actor is None) or (actor.__class__.__name__ == 'NoneType'):
        ue.log_warning(f"Actor not found: {actor}")
        return None
    target_component = None
    if name:
        for component in actor.get_components():
            if component.get_name() == name:
                target_component = component
    else:
        for component in actor.get_components():
            if component.get_class().get_name().endswith("MeshComponent"):
                target_component = component

    if not target_component:
        print(f"Mesh component not found on actor '{actor.get_name()}'")
        return None
    else:
        return target_component

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


def fullscreen():
    py_actor = find_actor("BP_PyActor")
    py_actor.call_function('SetFullscreen')

def windowed():
    py_actor = find_actor("BP_PyActor")
    py_actor.call_function('SetWindowed')

def windowed_fullscreen():
    py_actor = find_actor("BP_PyActor")
    py_actor.call_function('SetWindowedFullscreen')

def set_starcel_as_desktop(disable_animations=None):
    windowed_fullscreen()
    windowtool.stop_all_background_hooks_systemwide()
    windowtool.start_background_hook("../../../Starcel9Client.exe", expand_to_screen=True, custom_rect=(-10, 0, 1940, 1085))  # , monitor_number=0)
    # OPTIONAL: Disable Windows animations so you don't have to wait for the window to maximize
    if disable_animations is not None:
        windowtool.set_global_window_animations(disable_animations)


# def set_actor_hidden_in_game(actor, hidden=True): # Certain blueprints like BP_SkySphere
#     if not actor:
#         return None
#
#     out = actor.set_property("bActorHiddenInGame", hidden)
#     return out
#
#
# def set_actor_enabled(actor, enabled=True): # post process
#     if not actor:
#         return None
#
#     out = actor.set_property("bEnabled", enabled)
#     return out
#
# def set_actor_visible(actor, visible=True):
#     if not actor:
#         return None
#
#     out = actor.set_property("bActorHiddenInGame", visible)
#     return out

# relevant editor access https://github.com/20tab/UnrealEnginePython/issues/655 https://github.com/20tab/UnrealEnginePython/issues/363
# if not actor:
#     return
#
# for c in actor.get_components():
# for c in actor.get_components_by_type():
# for c in actor.get_components_by_tag():
#     try:
#         c.set_property("Visible", visible)
#     except Exception:
#         pass


def load_texture_any(path_or_obj):
    """
    Load a texture from:
      - Unreal asset path: /Game/Textures/T_Example.T_Example
      - Filesystem path: any image type (png, jpg, hdr, exr, webp)
      - Already-loaded UE object (Texture, Texture2D, TextureCube)
    Returns a Texture or Texture2D object usable in apply_material.
    """
    if not path_or_obj:
        return None

    # Already a UE object
    if type(path_or_obj).__name__ in ("Texture", "Texture2D", "TextureCube"):
        return path_or_obj

    # String paths
    if isinstance(path_or_obj, str):

        # Unreal asset path
        if path_or_obj.startswith("/Game"):
            tex = ue.load_object(Texture, path_or_obj)
            if not tex:
                ue.log_warning(f"Failed to load Unreal asset texture: {path_or_obj}")
            return tex

        # Filesystem image path
        if os.path.exists(path_or_obj):
            try:
                # load image with PIL
                img = Image.open(path_or_obj).convert("RGBA")
                width, height = img.size

                # convert to bytes
                data = np.array(img, dtype=np.uint8).flatten().tobytes()

                # create transient texture
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
    actor_name=None,
    component_name=None,
    material_path="/Game/Materials/M_Color.M_Color",
    material_index=0,
    params=None,
):
    """
    Apply a material and set parameters by type.
    params example:
        {
            "Emissive Multiplier": 1.0,
            "Color": (1,1,1),
            "Texture": "C:/sky.png"
        }
    """

    params = params or {}

    actor = find_actor(actor_name)
    print("Setting Actor Material:", actor, actor_name)
    target_comp = find_component(actor, component_name)

    mat = ue.load_object(Material, material_path)
    if not mat:
        ue.log_warning(f"Material not found: {material_path}")

    mid = target_comp.create_material_instance_dynamic(mat)

    for pname, v in params.items():

        # scalar
        if isinstance(v, (int, float)):
            mid.set_material_scalar_parameter(pname, float(v))

        # vector
        elif isinstance(v, (tuple, list)) and len(v) >= 3:
            mid.set_material_vector_parameter(pname, ue.FVector(v[0], v[1], v[2]))

        # texture / cubemap / HDR / filesystem image
        elif isinstance(v, str) or type(v).__name__ in ("Texture", "Texture2D", "TextureCube"):
            tex = load_texture_any(v)
            if tex:
                mid.set_material_texture_parameter(pname, tex)
            else:
                ue.log_warning(f"Could not load texture for param: {pname}")

        else:
            ue.log_warning(f"Unsupported material param type: {pname} = {type(v)}")

    target_comp.set_material(material_index, mid)
    return mid
