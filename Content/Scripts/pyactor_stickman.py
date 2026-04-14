"""
pyactor_stickman.py — Crosshair overlay for StickManCharacter
==============================================================
Spawns a tiny image plane (same pattern as spawn_image) textured with
crosshair.png and attaches it to the center of the Screen component.

The Screen cube represents the physical display — its size maps 1:1 to
the monitor when fullscreen.  The crosshair is a separate actor parented
to Screen so it stays centered regardless of camera movement.

Blueprint requirements (StickManCharacter):
  • Python component → pyactor_stickman.PyActorStickMan
  • A StaticMeshComponent named `Screen` parented to the first-person
    camera (already exists)

Material note:
  Uses M_TexturePicture (or M_Icon as fallback) for the crosshair plane.
  For best transparency, create M_Crosshair (Translucent, Unlit,
  Texture→Opacity) and set material_path below.
"""

import os
import unreal_engine as ue
from unreal_engine import FVector, FRotator, FTransform

try:
    from unreal_engine.classes import StaticMeshActor, StaticMesh, Material
    from unreal_engine.enums import EComponentMobility
except Exception:
    StaticMeshActor    = None
    StaticMesh         = None
    Material           = None
    EComponentMobility = None

from unreal_engine_tools import find_component


def _spawn_crosshair_plane(world, crosshair_path, material_path, fallback_mat,
                           param_name):
    """
    Spawn a StaticMeshActor cube textured with the crosshair PNG,
    scaled to the image's pixel size (1 px = 1 UU).  Same pattern as
    ue_spawn.spawn_image.

    Returns (actor, img_w, img_h) or (None, 0, 0).
    """
    from PIL import Image as PILImage
    from unreal_engine_tools import pil_image_to_texture

    if not os.path.exists(crosshair_path):
        ue.log_warning(f'PyActorStickMan: crosshair not found: "{crosshair_path}"')
        return None, 0, 0

    try:
        pil_img = PILImage.open(crosshair_path).convert('RGBA')
    except Exception as e:
        ue.log_warning(f'PyActorStickMan: cannot open crosshair: {e}')
        return None, 0, 0

    img_w, img_h = float(pil_img.width), float(pil_img.height)

    # Spawn cube actor
    actor = world.actor_spawn(StaticMeshActor)
    smc   = actor.StaticMeshComponent
    cube  = ue.load_object(StaticMesh, '/Engine/BasicShapes/Cube.Cube')
    smc.SetStaticMesh(cube)
    smc.Mobility = EComponentMobility.Movable

    # Load material (try primary, then fallbacks)
    mat = None
    mat_paths = [p for p in (material_path, fallback_mat) if p is not None]
    # Also try M_TextureUnlit as extra fallback
    if '/Game/Materials/M_TextureUnlit' not in mat_paths:
        mat_paths.append('/Game/Materials/M_TextureUnlit')
    for mp in mat_paths:
        if mat is not None:
            break
        for path in (mp + '.' + mp.split('/')[-1], mp):
            try:
                mat = ue.load_object(Material, path)
                break
            except Exception:
                pass

    # Apply MID with crosshair texture — destroy actor on failure to avoid
    # leaving a black untextured cube that covers the Screen.
    if mat is None:
        ue.log_warning('PyActorStickMan: no usable material — destroying crosshair '
                       'to avoid black screen')
        actor.actor_destroy()
        return None, 0, 0

    try:
        tex = pil_image_to_texture(pil_img)
        if tex is None:
            ue.log_warning('PyActorStickMan: texture conversion failed — '
                           'destroying crosshair')
            actor.actor_destroy()
            return None, 0, 0
        mid = smc.create_material_instance_dynamic(mat)
        mid.set_material_texture_parameter(param_name, tex)
        smc.set_material(0, mid)
    except Exception as e:
        ue.log_warning(f'PyActorStickMan: MID setup failed: {e} — '
                       'destroying crosshair')
        actor.actor_destroy()
        return None, 0, 0

    # Scale: vertical picture frame, 1 px = 1 UU
    # Cube default = 100 UU per side → divide by 100
    scale = FVector(img_w / 100.0, 0.01, img_h / 100.0)
    actor.set_actor_transform(
        FTransform(FVector(0, 0, 0), FRotator(0, 0, 0), scale))

    return actor, img_w, img_h


class PyActorStickMan:
    """
    Adds a StaticMeshComponent (crosshair cube) to the owning actor and
    attaches it to the Screen component.  Does NOT touch Screen's material.
    """

    crosshair_path = r'C:\Users\nicho\Documents\Unreal Projects\Starcel9\Content\Materials\crosshair.png'
    material_paths = (
        '/Game/Materials/M_Crosshair',
        '/Game/Materials/M_TexturePicture',
        '/Game/Materials/M_TextureUnlit',
    )
    param_name     = 'Texture'
    component_name = 'Screen'

    def begin_play(self):
        self.crosshair_comp = None

        from unreal_engine.classes import StaticMeshComponent

        screen = find_component(self.uobject, self.component_name)
        if screen is None:
            ue.log_warning(
                f'PyActorStickMan: no "{self.component_name}" component on '
                f'{self.uobject.get_name()}')
            return

        if not os.path.exists(self.crosshair_path):
            ue.log_warning(f'PyActorStickMan: crosshair not found: '
                           f'"{self.crosshair_path}"')
            return

        try:
            from PIL import Image as PILImage
            from unreal_engine_tools import pil_image_to_texture

            pil_img = PILImage.open(self.crosshair_path).convert('RGBA')
            img_w, img_h = float(pil_img.width), float(pil_img.height)

            # Load material
            mat = None
            mat_name = None
            for mp in self.material_paths:
                if mat is not None:
                    break
                for path in (mp + '.' + mp.split('/')[-1], mp):
                    try:
                        mat = ue.load_object(Material, path)
                        mat_name = mp.split('/')[-1]
                        break
                    except Exception:
                        pass
            if mat is None:
                ue.log_warning('PyActorStickMan: no usable crosshair material')
                return

            tex = pil_image_to_texture(pil_img)
            if tex is None:
                ue.log_warning('PyActorStickMan: texture conversion failed')
                return

            # Spawn a SEPARATE actor for the crosshair (add_actor_component
            # crashes BP actors with construction scripts during begin_play)
            from unreal_engine_tools import get_world
            world = self.uobject.get_world() or get_world()
            actor = world.actor_spawn(StaticMeshActor)
            smc   = actor.StaticMeshComponent
            cube  = ue.load_object(StaticMesh, '/Engine/BasicShapes/Cube.Cube')
            smc.SetStaticMesh(cube)
            smc.Mobility = EComponentMobility.Movable

            mid = smc.create_material_instance_dynamic(mat)
            mid.set_material_texture_parameter(self.param_name, tex)
            smc.set_material(0, mid)

            # Attach first, then set relative scale (so it's relative to Screen)
            actor.attach_to_component(screen)
            # Scale: img pixels / viewport pixels (so the crosshair occupies
            # that fraction of the Screen's visible area)
            try:
                actor.set_actor_relative_scale(
                    FVector(img_w / 1920.0, 0.01, img_h / 1080.0))
            except Exception:
                actor.set_actor_scale(
                    FVector(img_w / 1920.0, 0.01, img_h / 1080.0))
            actor.K2_SetActorRelativeLocation(FVector(0, -55.0, 0))

            self.crosshair_comp = actor
            ue.log(f'PyActorStickMan: crosshair {int(img_w)}x{int(img_h)} px '
                   f'actor attached to "{self.component_name}" (mat={mat_name})')
        except Exception as e:
            ue.log_warning(f'PyActorStickMan: crosshair spawn failed: {e}')

    def set_crosshair(self, path):
        """Swap the crosshair image at runtime."""
        self.crosshair_path = path
        if self.crosshair_comp is not None:
            try:
                self.crosshair_comp.DestroyComponent()
            except Exception:
                pass
            self.crosshair_comp = None
        self.begin_play()
