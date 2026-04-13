"""Screen overlay utilities for attaching 2D elements to a Screen component.

Provides helpers for spawning and managing actors attached to a character's
Screen component — crosshairs, debug info, icons, HUD-like 2D UI elements.

All overlays are separate StaticMeshActor cubes textured via MID, attached
to the Screen component so they stay fixed in the character's view.
"""
from __future__ import annotations

import os

try:
    import unreal_engine as ue
    from unreal_engine import FVector, FRotator, FTransform
except ImportError:
    ue = None
    FVector = FRotator = FTransform = None

try:
    from unreal_engine.classes import StaticMeshActor, StaticMesh, Material
    from unreal_engine.enums import EComponentMobility
except Exception:
    StaticMeshActor = StaticMesh = Material = EComponentMobility = None

try:
    from unreal_engine_tools import find_component, pil_image_to_texture, get_world
except ImportError:
    find_component = pil_image_to_texture = get_world = None


# ── Material loading ──────────────────────────────────────────────────────

def try_load_material(material_paths):
    """Try loading a Material from a list of asset paths.

    For each path, attempts both ``path.Name`` and bare ``path`` forms.
    Returns (Material, matched_path_name) or (None, None).
    """
    for mp in material_paths:
        name = mp.split('/')[-1]
        for path in (f'{mp}.{name}', mp):
            try:
                mat = ue.load_object(Material, path)
                return mat, name
            except Exception:
                pass
    return None, None


# ── Textured plane spawning ──────────────────────────────────────────────

def spawn_textured_plane(uobject, pil_image, material_paths, param_name='Texture',
                         scale=None, caller_tag='screen_overlay'):
    """Spawn a StaticMeshActor cube textured with a PIL image.

    Parameters
    ----------
    uobject : UObject
        The owning actor (used to get world).
    pil_image : PIL.Image
        RGBA image to apply as texture.
    material_paths : tuple[str, ...]
        Ordered list of material asset paths to try.
    param_name : str
        Texture parameter name in the material.
    scale : FVector or None
        Actor scale. If None, defaults to image pixel dimensions (1px = 1UU).
    caller_tag : str
        Label for log messages.

    Returns
    -------
    (actor, img_w, img_h) or (None, 0, 0) on failure.
    """
    if StaticMeshActor is None:
        return None, 0, 0

    img_w, img_h = float(pil_image.width), float(pil_image.height)

    mat, mat_name = try_load_material(material_paths)
    if mat is None:
        if ue:
            ue.log_warning(f'{caller_tag}: no usable material')
        return None, 0, 0

    tex = pil_image_to_texture(pil_image)
    if tex is None:
        if ue:
            ue.log_warning(f'{caller_tag}: texture conversion failed')
        return None, 0, 0

    world = uobject.get_world() if uobject else None
    if world is None and get_world is not None:
        world = get_world()

    actor = world.actor_spawn(StaticMeshActor)
    smc   = actor.StaticMeshComponent
    cube  = ue.load_object(StaticMesh, '/Engine/BasicShapes/Cube.Cube')
    smc.SetStaticMesh(cube)
    smc.SetMobility(EComponentMobility.Movable)

    mid = smc.create_material_instance_dynamic(mat)
    mid.set_material_texture_parameter(param_name, tex)
    smc.set_material(0, mid)

    if scale is None:
        scale = FVector(img_w / 100.0, 0.01, img_h / 100.0)
    actor.set_actor_transform(
        FTransform(FVector(0, 0, 0), FRotator(0, 0, 0), scale))

    return actor, img_w, img_h


# ── Crosshair overlay ────────────────────────────────────────────────────

DEFAULT_CROSSHAIR_MATS = (
    '/Game/Materials/M_Crosshair',
    '/Game/Materials/M_TextureUnlit',
    '/Game/Materials/M_TexturePicture',
)


def spawn_crosshair(uobject, crosshair_path, screen_component_name='Screen',
                    material_paths=None, param_name='Texture',
                    viewport_size=(1920.0, 1080.0), caller_tag='crosshair'):
    """Spawn a crosshair image plane and attach it to the Screen component.

    Parameters
    ----------
    uobject : UObject
        The owning character/pawn actor.
    crosshair_path : str
        Filesystem path to the crosshair PNG.
    screen_component_name : str
        Name of the Screen StaticMeshComponent to attach to.
    material_paths : tuple or None
        Material asset paths to try. Defaults to DEFAULT_CROSSHAIR_MATS.
    param_name : str
        Texture parameter name.
    viewport_size : tuple[float, float]
        (width, height) of the viewport the Screen maps to.
    caller_tag : str
        Label for log messages.

    Returns
    -------
    actor or None.
    """
    if material_paths is None:
        material_paths = DEFAULT_CROSSHAIR_MATS

    screen = find_component(uobject, screen_component_name)
    if screen is None:
        if ue:
            ue.log_warning(f'{caller_tag}: no "{screen_component_name}" component')
        return None

    if not os.path.exists(crosshair_path):
        if ue:
            ue.log_warning(f'{caller_tag}: crosshair not found: "{crosshair_path}"')
        return None

    try:
        from PIL import Image as PILImage
        pil_img = PILImage.open(crosshair_path).convert('RGBA')
    except Exception as e:
        if ue:
            ue.log_warning(f'{caller_tag}: cannot open crosshair: {e}')
        return None

    img_w, img_h = float(pil_img.width), float(pil_img.height)
    vp_w, vp_h = viewport_size
    scale = FVector(img_w / vp_w, 0.001, img_h / vp_h)

    actor, _, _ = spawn_textured_plane(
        uobject, pil_img, material_paths, param_name,
        scale=scale, caller_tag=caller_tag,
    )
    if actor is None:
        return None

    actor.attach_to_component(screen)
    actor.K2_SetActorRelativeLocation(FVector(0, -1.0, 0))

    if ue:
        ue.log(f'{caller_tag}: crosshair {int(img_w)}x{int(img_h)} px '
               f'attached to "{screen_component_name}"')
    return actor


# ── Debug text overlay (placeholder for future use) ──────────────────────

def spawn_debug_text(uobject, screen_component_name='Screen',
                     offset=None, caller_tag='debug_text'):
    """Placeholder for spawning a debug text overlay on the Screen component.

    Future implementation: spawn a TextRenderActor or Text3D attached to
    the Screen component for displaying debug info (FPS, position, etc.).
    """
    pass


# ── Generic icon overlay ─────────────────────────────────────────────────

def spawn_icon_overlay(uobject, pil_image, screen_component_name='Screen',
                       material_paths=None, param_name='Texture',
                       viewport_size=(1920.0, 1080.0),
                       position=None, caller_tag='icon_overlay'):
    """Spawn a small icon image plane and attach it to the Screen component.

    Similar to spawn_crosshair but allows custom positioning on the screen.

    Parameters
    ----------
    position : FVector or None
        Relative position on the Screen. If None, centers the icon.
    """
    if material_paths is None:
        material_paths = DEFAULT_CROSSHAIR_MATS

    screen = find_component(uobject, screen_component_name)
    if screen is None:
        if ue:
            ue.log_warning(f'{caller_tag}: no "{screen_component_name}" component')
        return None

    img_w, img_h = float(pil_image.width), float(pil_image.height)
    vp_w, vp_h = viewport_size
    scale = FVector(img_w / vp_w, 0.001, img_h / vp_h)

    actor, _, _ = spawn_textured_plane(
        uobject, pil_image, material_paths, param_name,
        scale=scale, caller_tag=caller_tag,
    )
    if actor is None:
        return None

    actor.attach_to_component(screen)
    if position is None:
        position = FVector(0, -1.0, 0)
    actor.K2_SetActorRelativeLocation(position)

    return actor
