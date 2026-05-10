"""
pyactor_main.py — staring_at_sky map controller (StaringAtSkyMap level).

Stripped-down equivalent of Scripts/main.py. On begin_play, scatters
desktop icons as "stars" inside the volume of the Cylinder2
StaticMeshActor placed in StaringAtSkyMap:

    Cylinder2  loc=(0, 0, 5490)
               rot=(0, 0, 0)             # axis-aligned with world Z
               scale=(200, 200, 100)

/Engine/BasicShapes/Cylinder is 100 UU diameter × 100 UU tall centered
on origin, so the scaled bounds are:
    diameter = 20000 UU
    height   = 10000 UU
    Z extent = [490, 10490]   (centered on Z=5490)

No rotation step needed — points are translated by CENTER directly.
Per-icon uniform scale in [ICON_SCALE_MIN, ICON_SCALE_MAX] varies the
apparent star size.

Usage:
    Place a BP_PyActorEmpty in the level, set
        PythonModule = maps.staring_at_sky.pyactor_main
        PythonClass  = Main
"""

import os
import unreal_engine as ue
from unreal_engine import FVector


# Mirrors the Cylinder2 StaticMeshActor in StaringAtSkyMap.
CENTER         = FVector(0.0, 0.0, 4490.0)
DIAMETER       = 20000.0
HEIGHT         = 10000.0

# Star count + per-star uniform scale in [MIN, MAX].
N_STARS        = 50
ICON_SCALE_MIN = 1.0
ICON_SCALE_MAX = 5.0
SEED           = 42


# BP_PyActor can fire BeginPlay twice when the editor reloads modules.
_begin_play_ran = False


class Main:
    """Empty PyActor for staring_at_sky — scatters icons on begin_play."""

    def begin_play(self):
        global _begin_play_ran
        if _begin_play_ran:
            ue.log('staring_at_sky.Main.begin_play: already ran — skipping')
            return
        _begin_play_ran = True

        ue.log('staring_at_sky.Main: begin_play')
        try:
            self._spawn_stars()
        except Exception as e:
            ue.log_warning(f'staring_at_sky.Main: spawn failed: {e}')

    def end_play(self, reason):
        global _begin_play_ran
        _begin_play_ran = False
        ue.log('staring_at_sky.Main: end_play')

    def tick(self, delta_time):
        pass

    def _spawn_stars(self):
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
                f'staring_at_sky.Main: scan "{folder}" failed: {e}')
            return

        paths = list(icons.items())[:N_STARS]
        if not paths:
            ue.log_warning(f'staring_at_sky.Main: no icons in "{folder}"')
            return

        cloud = _cylinder_point_cloud(
            diameter=DIAMETER, height=HEIGHT,
            n_points=len(paths), center_z=True, seed=SEED)

        # Per-star uniform scale — separate RNG so changing the count or
        # cloud seed doesn't reshuffle which star is largest.
        import numpy as np
        scales = np.random.default_rng(SEED + 1).uniform(
            ICON_SCALE_MIN, ICON_SCALE_MAX, len(paths))
        spawned = 0

        for (path, pil_img), (cx, cy, cz), s in zip(paths, cloud, scales):
            # Cylinder is axis-aligned with world Z (rotation=0,0,0), so
            # no rotation step — just translate by CENTER.
            world = FVector(CENTER.x + cx, CENTER.y + cy, CENTER.z + cz)
            scale = FVector(float(s) * 0.8, float(s) * 0.8, float(s))
            try:
                actor = spawn_icon(pil_img, location=world, scale=scale,
                                   source_path=path)
                if actor is not None:
                    spawned += 1
            except Exception as e:
                ue.log_warning(
                    f'staring_at_sky.Main: spawn_icon failed for '
                    f'"{path}": {e}')

        ue.log(f'staring_at_sky.Main: spawned {spawned} stars')
