"""
pyactor_main.py — pine_tree map controller (BlueprintOffice level).

Stripped-down equivalent of Scripts/main.py.
On begin_play, scatters desktop icons as "apples" inside a cylindrical
point cloud aligned with the tilted plane Cube already placed in the
level:

    Cube  loc=(180, -70, 850)
          rot=(X=27.206261 roll, Y=39.442719 pitch, Z=-6.455316 yaw)
          scale=(10, 10, 0.1)   # flat in local Z — that's the plane normal

The cylinder is generated in cylinder-local coords (axis along Z),
rotated by the cube's FRotator so its axis follows the plane normal,
then translated to the cube's location. center_z=True makes the plane
cut through the middle of the cylinder, so apples scatter both above
and below it.

Usage:
    Place a BP_PyActorEmpty in the level, set
        PythonModule = maps.pine_tree.pyactor_main
        PythonClass  = Main
"""

import os
import unreal_engine as ue
from unreal_engine import FVector, FRotator
from unreal_engine.enums import ECollisionChannel


# Editor display order is X=Roll, Y=Pitch, Z=Yaw; FRotator constructor
# takes (Pitch, Yaw, Roll). Mirrors the Cube StaticMeshActor — if the
# Cube moves, update these (or look it up by name at begin_play).
PLANE_LOCATION = FVector(180.0, -70.0, 850.0)
PLANE_ROTATION = FRotator(39.442719, -6.455316, 27.206261)

# Cylinder shape — sized for the ~1000 UU canopy. 30 icons in a
# 4.0e8 UU³ volume → ~210 UU mean spacing; icons are ~60–120 UU
# (BP_Icon Sphere ≈150 UU × scale ∈ [0.4, 0.8]) so a few neighbours can
# overlap, which reads naturally as a cluster of apples.
DIAMETER       = 800.0
HEIGHT         = 800.0
N_APPLES       = 30
ICON_SCALE_MIN = 0.4
ICON_SCALE_MAX = 0.8
SEED           = 1337  # bumped from 42 to reshuffle apple positions

# Drop the cloud below the canopy, then raycast each apple straight up
# until it hits the tree — apples land on the underside of the branches
# instead of floating in the canopy volume.
CLOUD_X_OFFSET    = -150.0
CLOUD_Z_OFFSET    = -300.0
APPLE_TRACE_UP_UU = 2000.0


# BP_PyActor can fire BeginPlay twice when the editor reloads modules.
_begin_play_ran = False


class Main:
    """Empty PyActor for pine_tree — scatters icons on begin_play."""

    def begin_play(self):
        global _begin_play_ran
        if _begin_play_ran:
            ue.log('pine_tree.Main.begin_play: already ran — skipping')
            return
        _begin_play_ran = True

        ue.log('pine_tree.Main: begin_play')
        try:
            self._spawn_apples()
        except Exception as e:
            ue.log_warning(f'pine_tree.Main: spawn failed: {e}')

    def end_play(self, reason):
        global _begin_play_ran
        _begin_play_ran = False
        ue.log('pine_tree.Main: end_play')

    def tick(self, delta_time):
        pass

    def _spawn_apples(self):
        # Lazy imports — keep module-level cost low; UE Python loads this
        # file at engine init.
        from icon_to_image import get_folder_icons
        from ue_spawn import spawn_icon
        from test_spawn import _cylinder_point_cloud

        folder = os.path.join(os.path.expanduser('~'), 'Desktop')
        try:
            icons = get_folder_icons(folder)
        except Exception as e:
            ue.log_warning(
                f'pine_tree.Main: scan "{folder}" failed: {e}')
            return

        paths = list(icons.items())[:N_APPLES]
        if not paths:
            ue.log_warning(f'pine_tree.Main: no icons in "{folder}"')
            return

        cloud = _cylinder_point_cloud(
            diameter=DIAMETER, height=HEIGHT,
            n_points=len(paths), center_z=True, seed=SEED)

        # Per-apple uniform scale — separate RNG so changing the count or
        # cloud seed doesn't reshuffle which apple is largest.
        import numpy as np
        scales = np.random.default_rng(SEED + 1).uniform(
            ICON_SCALE_MIN, ICON_SCALE_MAX, len(paths))
        # Per-apple random rotation in [0, 360) on each axis — third RNG
        # so tweaking position/scale doesn't reshuffle orientations.
        rots = np.random.default_rng(SEED + 2).uniform(
            0.0, 360.0, (len(paths), 3))
        spawned = 0

        for (path, pil_img), (cx, cy, cz), s, (pitch, yaw, roll) in zip(
                paths, cloud, scales, rots):
            # FRotator * FVector → FRotator::RotateVector via UEPython's
            # nb_multiply. Avoids the FQuat-arg crash documented in
            # memory (matches gizmo._rotate_local).
            local = FVector(cx, cy, cz)
            world = PLANE_LOCATION + PLANE_ROTATION * local
            world = FVector(world.x + CLOUD_X_OFFSET, world.y,
                            world.z + CLOUD_Z_OFFSET)

            # Raise the apple straight up in world Z until it hits the
            # tree mesh; if the trace misses, leave it in the cloud.
            trace_end = FVector(world.x, world.y,
                                world.z + APPLE_TRACE_UP_UU)
            hit = self.uobject.line_trace_single_by_channel(
                world, trace_end, ECollisionChannel.ECC_Visibility)
            if hit is not None and hit.actor is not None:
                world = hit.impact_point

            scale = FVector(float(s), float(s), float(s))
            rot = FRotator(float(pitch), float(yaw), float(roll))
            try:
                actor = spawn_icon(pil_img, location=world, rotation=rot,
                                   scale=scale, source_path=path)
                if actor is not None:
                    spawned += 1
            except Exception as e:
                ue.log_warning(
                    f'pine_tree.Main: spawn_icon failed for '
                    f'"{path}": {e}')

        ue.log(f'pine_tree.Main: spawned {spawned} apples')
