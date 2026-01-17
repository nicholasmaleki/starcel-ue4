import unreal_engine as ue
from unreal_engine.classes import Material, Texture, Texture2D, TextureCube



def get_world():
    scmaps = []
    global world

    if not world:
        for _world in ue.all_worlds():
            if _world.get_name() == "StarcelExampleMap":
                scmaps.append(_world)

        if len(scmaps) == 1:
            world = scmaps[0]
        else:
            world = scmaps[len(scmaps) - 1]
            ue.log_warning("There is more than one StarcelExampleMap world, using the last one found")

        if not world:
            world = ue.all_worlds()[0]
            ue.log_warning("Can't find world, assigning the first existing world, " + world.get_name())

    return world

def find_actor(name):
    for a in world.all_actors():
        if a.get_name() == name:
            return a
    return None


def set_actor_hidden(name, hidden=True):
    a = find_actor(name)
    if not a:
        return None

    a.set_property("bHidden", hidden)
    return a


def set_actor_enabled(name, enabled=True):
    a = find_actor(name)
    if not a:
        return None

    a.set_property("bActorEnableCollision", enabled)
    a.set_property("bCanBeDamaged", enabled)
    return a


def set_components_visible(actor, visible=True):
    if not actor:
        return

    for c in actor.get_components():
        try:
            c.set_property("bVisible", visible)
        except Exception:
            pass


def _load_texture_any(path):
    if not path:
        return None

    # Asset path
    if isinstance(path, str) and path.startswith("/Game"):
        return ue.load_object(Texture, path)

    # File path (hdr, png, exr, etc)
    if isinstance(path, str):
        return ue.load_texture(path)

    return path


def apply_material(
    actor_name=None,
    component_name=None,
    material_path="/Game/Materials/M_Color.M_Color",
    material_index=0,
    params=None,
):
    """
    Apply a material and set parameters by value type.

    params example:
        {
            "Emissive Multiplier": 1.0,
            "Color": (1,1,1),
            "Texture": "C:/sky.hdr"
        }
    """

    params = params or {}

    # --- find actor ---
    actor = None
    for a in world.all_actors():
        if actor_name is None or a.get_name() == actor_name:
            actor = a
            break

    if not actor:
        raise Exception(f"Actor not found: {actor_name or '(any)'}")

    # --- find component ---
    target_comp = None
    if component_name:
        for comp in actor.get_components():
            if comp.get_name() == component_name:
                target_comp = comp
                break
    else:
        for comp in actor.get_components():
            if comp.get_class().get_name().endswith("MeshComponent"):
                target_comp = comp
                break

    if not target_comp:
        raise Exception(f"Mesh component not found on actor '{actor.get_name()}'")

    # --- load material ---
    mat = ue.load_object(Material, material_path)
    if not mat:
        raise Exception(f"Material not found: {material_path}")

    # --- create MID ---
    mid = target_comp.create_material_instance_dynamic(mat)

    # --- set params ---
    for pname, v in params.items():

        # scalar
        if isinstance(v, (int, float)):
            mid.set_material_scalar_parameter(pname, float(v))

        # vector
        elif isinstance(v, (tuple, list)) and len(v) >= 3:
            mid.set_material_vector_parameter(pname, ue.FVector(v[0], v[1], v[2]))

        # texture / cubemap / hdr
        elif isinstance(v, (str, Texture, Texture2D, TextureCube)):
            tex = _load_texture_any(v)
            if tex:
                mid.set_material_texture_parameter(pname, tex)

        else:
            ue.log_warning(f"Unsupported material param type: {pname} = {type(v)}")

    # --- assign ---
    target_comp.set_material(material_index, mid)

    return mid


def change_background(mode="white", image_path=None):
    """
    Background presets:
        white
        black
        white_no_bloom
        stars
        sky
        image
    """

    # --- grab actors ---
    sky = find_actor("SM_SkySphere")
    sky_white = find_actor("SM_SkySpherePureWhite")
    sky_bp = find_actor("BP_SkySphere")

    pp_bloom = find_actor("PostProcessVolumeRemoveBloom")

    # --- reset ---
    for a in (sky, sky_white):
        set_actor_hidden(a.get_name(), True)
        set_actor_enabled(a.get_name(), False)
        set_components_visible(a, False)

    if pp_bloom:
        set_actor_hidden(pp_bloom.get_name(), True)

    # ---------------- WHITE ----------------
    if mode == "white":
        set_actor_hidden("SM_SkySpherePureWhite", False)
        set_actor_enabled("SM_SkySpherePureWhite", True)
        set_components_visible(sky_white, True)

        apply_material(
            actor_name="SM_SkySpherePureWhite",
            material_path="/Game/Materials/M_SkyBoxWhiteForManualExposure.M_SkyBoxWhiteForManualExposure",
            params=dict(
                emissive_multiplier=1.0,
            )
        )

    # ---------------- BLACK ----------------
    elif mode == "black":
        set_actor_hidden("SM_SkySphere", False)
        set_actor_enabled("SM_SkySphere", True)
        set_components_visible(sky, True)

        apply_material(
            actor_name="SM_SkySphere",
            material_path="/Game/Materials/M_SkyBox.M_SkyBox",
            params=dict(
                emissive_multiplier=0.05,
                color=(0, 0, 0),
            )
        )

    # ---------------- WHITE NO BLOOM ----------------
    elif mode == "white_no_bloom":
        set_actor_hidden("SM_SkySpherePureWhite", False)
        set_actor_enabled("SM_SkySpherePureWhite", True)
        set_components_visible(sky_white, True)

        if pp_bloom:
            set_actor_hidden(pp_bloom.get_name(), False)

        apply_material(
            actor_name="SM_SkySpherePureWhite",
            material_path="/Game/Materials/M_SkyBoxWhiteForManualExposure.M_SkyBoxWhiteForManualExposure",
            params=dict(
                emissive_multiplier=1.0,
            )
        )

    # ---------------- STARS ----------------
    elif mode == "stars":
        set_actor_hidden("SM_SkySphere", False)
        set_actor_enabled("SM_SkySphere", True)
        set_components_visible(sky, True)

        apply_material(
            actor_name="SM_SkySphere",
            material_path="/Game/Materials/M_SkyBox.M_SkyBox",
            params=dict(
                emissive_multiplier=0.5,
                texture="/Game/Textures/starmap_g8k.starmap_g8k",
            )
        )

    # ---------------- SKY ----------------
    elif mode == "sky":
        set_actor_hidden("SM_SkySphere", False)
        set_actor_enabled("SM_SkySphere", True)
        set_components_visible(sky, True)

        apply_material(
            actor_name="SM_SkySphere",
            material_path="/Game/Materials/M_SkyBox.M_SkyBox",
            params=dict(
                emissive_multiplier=1.0,
            )
        )

    # ---------------- IMAGE ----------------
    elif mode == "image":
        if not image_path:
            raise Exception("image mode requires image_path")

        set_actor_hidden("SM_SkySphere", False)
        set_actor_enabled("SM_SkySphere", True)
        set_components_visible(sky, True)

        apply_material(
            actor_name="SM_SkySphere",
            material_path="/Game/Materials/M_SkyBox.M_SkyBox",
            params=dict(
                emissive_multiplier=1.0,
                texture=image_path,
            )
        )

    else:
        raise Exception(f"Unknown background mode: {mode}")
