"""
ue_spawn.py — Universal spawn() utility for UnrealEnginePython
Runtime-only (editor-only paths are stubbed with pass + comment).

Dependencies:
  - UnrealEnginePython plugin
  - PIL / Pillow          (spawn_image, spawn_video, spawn_icon)
  - trimesh               (3-D format conversion: pip install trimesh)
  - ffmpeg on PATH        (video format conversion)
  - A Blueprint at /Game/Blueprints/BP_SoundSphere (see SoundSphereActor)

Blueprint requirements — BP_SoundSphere:
    • StaticMeshComponent (sphere), Generate Overlap Events ON
    • Mouse Button Clicked enabled in Project Settings > Input
    • Public variable 'Sound' (SoundBase)
"""

import os
import subprocess
import tempfile
import unreal_engine as ue
from unreal_engine import FVector, FRotator, FTransform
from unreal_engine.classes import (
    StaticMeshActor, StaticMesh, Material, Blueprint,
)
from unreal_engine.enums import EComponentMobility


# r.Upscale.Panini.D = 0 or 0.5 for example
# r.Upscale.Panini.S = 0  or 0.05 for example
# r.ScreenPercentage = 100 or 150 for example
#
# is what I saw someone else doing

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def _get_world():
    try:
        return ue.get_world()
    except Exception:
        return ue.get_editor_world()


def _set_transform(actor, location, rotation, scale):
    loc = location if location is not None else FVector(0, 0, 0)
    rot = rotation if rotation is not None else FRotator(0, 0, 0)
    scl = scale    if scale    is not None else FVector(1, 1, 1)
    actor.set_actor_transform(FTransform(loc, rot, scl))


def _exec_console(cmd):
    """Run a console command via the player controller."""
    try:
        pc = ue.get_player_controller(0)
        pc.ConsoleCommand(cmd)
    except Exception as e:
        ue.log_warning(f'_exec_console: failed to run "{cmd}": {e}')


# ---------------------------------------------------------------------------
# Format conversion utilities
# ---------------------------------------------------------------------------

# ---- Image conversion -----------------------------------------------------

IMAGE_NATIVE  = {'.png', '.jpg', '.jpeg', '.bmp', '.tga', '.tiff', '.exr', '.hdr'}
IMAGE_CONVERT = {'.webp', '.ico', '.gif', '.psd', '.svg'}  # -> PNG via Pillow

def _ensure_image(path):
    """
    Return *path* unchanged if natively supported by UE.
    Otherwise convert to a temp PNG via Pillow and return that path.
    """
    ext = os.path.splitext(path)[1].lower()
    if ext in IMAGE_NATIVE:
        return path
    try:
        from PIL import Image as PILImage
        tmp = tempfile.mktemp(suffix='.png')
        with PILImage.open(path) as im:
            im.convert('RGBA').save(tmp)
        ue.log(f'_ensure_image: converted "{ext}" -> PNG ({tmp})')
        return tmp
    except ImportError:
        ue.log_warning('_ensure_image: Pillow not installed. pip install Pillow')
    except Exception as e:
        ue.log_warning(f'_ensure_image: conversion failed for "{path}": {e}')
    return path


# ---- Video conversion -----------------------------------------------------

VIDEO_NATIVE  = {'.mp4', '.avi'}
VIDEO_CONVERT = {'.mov', '.mkv', '.wmv', '.webm', '.flv', '.ts', '.m4v'}

def _ensure_video(path):
    """
    Return *path* unchanged if natively supported.
    Otherwise convert to a temp MP4 via ffmpeg.
    """
    ext = os.path.splitext(path)[1].lower()
    if ext in VIDEO_NATIVE:
        return path
    tmp = tempfile.mktemp(suffix='.mp4')
    try:
        result = subprocess.run(
            ['ffmpeg', '-y', '-i', path,
             '-c:v', 'libx264', '-preset', 'fast', '-crf', '23',
             '-c:a', 'aac', tmp],
            capture_output=True, text=True
        )
        if result.returncode == 0:
            ue.log(f'_ensure_video: converted "{ext}" -> MP4 ({tmp})')
            return tmp
        ue.log_warning(f'_ensure_video: ffmpeg error:\n{result.stderr}')
    except FileNotFoundError:
        ue.log_warning('_ensure_video: ffmpeg not found on PATH. '
                       'Install ffmpeg to auto-convert video formats.')
    return path


# ---- 3-D format conversion ------------------------------------------------

OBJ_NATIVE  = {'.fbx'}
OBJ_TRIMESH = {'.obj', '.ply', '.stl', '.off', '.dae', '.gltf', '.glb'}
OBJ_BLENDER = {'.blend', '.3ds', '.dxf', '.x3d', '.wrl'}

_BLENDER_IMPORT_OPS = {
    '.obj':  'bpy.ops.import_scene.obj(filepath=r"{p}")',
    '.dae':  'bpy.ops.wm.collada_import(filepath=r"{p}")',
    '.gltf': 'bpy.ops.import_scene.gltf(filepath=r"{p}")',
    '.glb':  'bpy.ops.import_scene.gltf(filepath=r"{p}")',
    '.stl':  'bpy.ops.import_mesh.stl(filepath=r"{p}")',
    '.ply':  'bpy.ops.import_mesh.ply(filepath=r"{p}")',
    '.3ds':  'bpy.ops.import_scene.autodesk_3ds(filepath=r"{p}")',
    '.dxf':  'bpy.ops.import_scene.dxf(filepath=r"{p}")',
    '.x3d':  'bpy.ops.import_scene.x3d(filepath=r"{p}")',
    '.wrl':  'bpy.ops.import_scene.x3d(filepath=r"{p}")',
    '.blend':'pass  # .blend is opened directly',
}

def _convert_via_blender(path, tmp_fbx):
    """Try to convert *path* to FBX using Blender CLI. Returns True on success."""
    ext = os.path.splitext(path)[1].lower()
    import_op = _BLENDER_IMPORT_OPS.get(ext, f'# unknown ext {ext}')
    import_op = import_op.format(p=path)

    script = (
        "import bpy\n"
        "bpy.ops.object.select_all(action='SELECT')\n"
        "bpy.ops.object.delete()\n"
        f"{import_op}\n"
        f"bpy.ops.export_scene.fbx(filepath=r'{tmp_fbx}', use_selection=False)\n"
    )
    script_tmp = tempfile.mktemp(suffix='.py')
    with open(script_tmp, 'w') as f:
        f.write(script)

    candidates = [
        'blender', 'blender.exe',
        r'C:\Program Files\Blender Foundation\Blender 4.0\blender.exe',
        r'C:\Program Files\Blender Foundation\Blender 3.6\blender.exe',
        '/usr/bin/blender',
        '/Applications/Blender.app/Contents/MacOS/Blender',
    ]
    for exe in candidates:
        try:
            result = subprocess.run(
                [exe, '--background', '--python', script_tmp],
                capture_output=True, text=True, timeout=120
            )
            if result.returncode == 0 and os.path.exists(tmp_fbx):
                ue.log(f'_ensure_fbx: converted via Blender ({tmp_fbx})')
                return True
        except (FileNotFoundError, subprocess.TimeoutExpired):
            continue
    return False


def _ensure_fbx(path):
    """
    Return *path* if already FBX.
    Otherwise convert to a temp FBX using:
      1. trimesh  (OBJ, PLY, STL, DAE, GLB/glTF)
      2. Blender CLI fallback (all formats including .blend, .3ds, .dxf)
    Returns None if all conversion attempts fail.
    """
    ext = os.path.splitext(path)[1].lower()
    if ext in OBJ_NATIVE:
        return path

    tmp_fbx = tempfile.mktemp(suffix='.fbx')

    # --- trimesh (fast, no external app needed) ---
    if ext in OBJ_TRIMESH:
        try:
            import trimesh
            scene = trimesh.load(path, force='scene')
            scene.export(tmp_fbx)
            ue.log(f'_ensure_fbx: converted "{ext}" -> FBX via trimesh ({tmp_fbx})')
            return tmp_fbx
        except ImportError:
            ue.log_warning('_ensure_fbx: trimesh not installed (pip install trimesh). '
                           'Trying Blender fallback...')
        except Exception as e:
            ue.log_warning(f'_ensure_fbx: trimesh failed: {e}. Trying Blender fallback...')

    # --- Blender CLI fallback ---
    if ext in OBJ_TRIMESH or ext in OBJ_BLENDER:
        if _convert_via_blender(path, tmp_fbx):
            return tmp_fbx

    ue.log_warning(
        f'_ensure_fbx: could not convert "{ext}" to FBX. '
        'Install trimesh (pip install trimesh) or Blender (ensure it is on PATH).'
    )
    return None


# ---------------------------------------------------------------------------
# spawn_image
# ---------------------------------------------------------------------------

def spawn_image(path, location=None, rotation=None, scale=None,
                material_path='/Game/Materials/M_ImagePlane',
                param_name='Texture'):
    """
    Spawn a thin cube scaled to image aspect ratio and textured with *path*.

    Unsupported formats (.webp, .gif, .psd, etc.) are auto-converted to PNG.
    The material at *material_path* must have a TextureSampleParameter2D
    named *param_name*.
    """
    world = _get_world()
    path = _ensure_image(path)

    img_w, img_h = 100.0, 100.0
    try:
        from PIL import Image as PILImage
        with PILImage.open(path) as im:
            img_w, img_h = float(im.width), float(im.height)
    except Exception:
        pass

    actor = world.actor_spawn(StaticMeshActor)
    smc = actor.StaticMeshComponent
    smc.SetStaticMesh(ue.load_object(StaticMesh, '/Engine/BasicShapes/Cube'))
    smc.Mobility = EComponentMobility.Movable

    mat = ue.load_object(Material, material_path)
    if mat:
        try:
            tex = None
            try:
                from unreal_engine.classes import TextureFactory
                tex_name = os.path.splitext(os.path.basename(path))[0]
                tex = TextureFactory().factory_import_object(
                    path, f'/Game/SpawnTextures/{tex_name}')
            except Exception as e:
                ue.log_warning(f'spawn_image: texture import failed: {e}')
            dmi = smc.CreateAndSetMaterialInstanceDynamic(0)
            if tex:
                dmi.SetTextureParameterValue(param_name, tex)
        except Exception as e:
            ue.log_warning(f'spawn_image: material setup failed: {e}')

    img_scale = scale if scale is not None else FVector(img_w / 100.0, img_h / 100.0, 0.01)
    _set_transform(actor, location, rotation, img_scale)
    return actor


# ---------------------------------------------------------------------------
# spawn_video
# ---------------------------------------------------------------------------

def spawn_video(path, location=None, rotation=None, scale=None,
                material_path='/Game/Materials/M_VideoPlane',
                param_name='MediaTexture',
                autoplay=True):
    """
    Spawn a thin cube (like image plane, scaled to video resolution) and
    drive it with a MediaPlayer + MediaTexture at runtime.

    Unsupported video formats (.mov, .mkv, .webm, etc.) are auto-converted
    to MP4 via ffmpeg.

    The material at *material_path* must have a TextureSampleParameter2D
    named *param_name* wired to a MediaTexture.

    Returns (actor, media_player, media_texture) so callers can pause/seek.
    """
    from unreal_engine.classes import MediaPlayer, MediaTexture, FileMediaSource

    world = _get_world()
    path = _ensure_video(path)

    # Read video dimensions for aspect-ratio scale (via ffprobe)
    vid_w, vid_h = 192.0, 108.0  # default 16:9 fallback
    try:
        result = subprocess.run(
            ['ffprobe', '-v', 'error', '-select_streams', 'v:0',
             '-show_entries', 'stream=width,height', '-of', 'csv=p=0', path],
            capture_output=True, text=True
        )
        parts = result.stdout.strip().split(',')
        if len(parts) == 2:
            vid_w, vid_h = float(parts[0]), float(parts[1])
    except Exception:
        pass

    actor = world.actor_spawn(StaticMeshActor)
    smc = actor.StaticMeshComponent
    smc.SetStaticMesh(ue.load_object(StaticMesh, '/Engine/BasicShapes/Cube'))
    smc.Mobility = EComponentMobility.Movable

    # Create runtime media objects
    media_player  = ue.new_object(MediaPlayer)
    media_texture = ue.new_object(MediaTexture)
    media_source  = ue.new_object(FileMediaSource)

    media_texture.set_media_player(media_player)
    media_source.set_file_path(path)

    # Bind MediaTexture to material
    mat = ue.load_object(Material, material_path)
    if mat:
        try:
            dmi = smc.CreateAndSetMaterialInstanceDynamic(0)
            dmi.SetTextureParameterValue(param_name, media_texture)
        except Exception as e:
            ue.log_warning(f'spawn_video: material setup failed: {e}')
    else:
        ue.log_warning(
            f'spawn_video: material not found at "{material_path}". '
            f'Create a material with a TextureSampleParameter2D named "{param_name}".'
        )

    if autoplay:
        media_player.open_source(media_source)
        media_player.play()

    vid_scale = scale if scale is not None else FVector(vid_w / 100.0, vid_h / 100.0, 0.01)
    _set_transform(actor, location, rotation, vid_scale)
    return actor, media_player, media_texture


# ---------------------------------------------------------------------------
# spawn_sound
# ---------------------------------------------------------------------------

def spawn_sound(path, location=None, volume=1.0, pitch=1.0,
                start_time=0.0, as_actor=False):
    """
    Play a sound immediately, or spawn a clickable/proximity sphere.

    *path*: UE asset path ('/Game/Sounds/MySound') or filesystem .wav.
    *as_actor=True*: spawns BP_SoundSphere (see SoundSphereActor below).
    """
    world = _get_world()
    loc = location if location is not None else FVector(0, 0, 0)

    sound = None
    try:
        sound = ue.load_object(ue.find_class('SoundBase'), path)
    except Exception:
        pass
    if sound is None:
        try:
            sound = ue.find_object(os.path.basename(path).split('.')[0])
        except Exception:
            pass

    if as_actor:
        try:
            bp = ue.load_object(Blueprint, '/Game/Blueprints/BP_SoundSphere')
            actor = world.actor_spawn(bp.GeneratedClass)
            _set_transform(actor, loc, None, None)
            if sound:
                actor.Sound = sound
            return actor
        except Exception as e:
            ue.log_warning(f'spawn_sound as_actor failed: {e}. Falling back to play_at_location.')

    if sound:
        world.play_sound_at_location(sound, loc, volume, pitch, start_time)
    else:
        ue.log_warning(f'spawn_sound: could not resolve sound at "{path}"')
    return None


# ---------------------------------------------------------------------------
# spawn_obj
# ---------------------------------------------------------------------------

def spawn_obj(path, location=None, rotation=None, scale=None,
              import_path='/Game/ImportedMeshes'):
    """
    Import any 3-D format and spawn as a StaticMeshActor.

    Conversion pipeline (auto, no user action needed):
      .fbx                   → imported directly
      .obj .ply .stl .dae
      .gltf .glb             → trimesh → FBX, then imported
                               (pip install trimesh)
      .blend .3ds .dxf .wrl
      .x3d                   → Blender CLI → FBX, then imported
    """
    from unreal_engine.classes import PyFbxFactory
    from unreal_engine.enums import EFBXImportType

    world = _get_world()
    fbx_path = _ensure_fbx(path)
    if fbx_path is None:
        return None

    asset_name = os.path.splitext(os.path.basename(path))[0]
    dest = f'{import_path}/{asset_name}'

    fbx_factory = PyFbxFactory()
    fbx_factory.ImportUI.MeshTypeToImport = EFBXImportType.FBXIT_StaticMesh
    fbx_factory.ImportUI.bCreatePhysicsAsset = False
    fbx_factory.ImportUI.bImportMaterials = True
    fbx_factory.ImportUI.bImportTextures = True
    fbx_factory.ImportUI.bImportAnimations = False
    fbx_factory.ImportUI.StaticMeshImportData.bCombineMeshes = True
    fbx_factory.ImportUI.StaticMeshImportData.bConvertScene = True

    mesh_asset = fbx_factory.factory_import_object(fbx_path, dest)
    if mesh_asset is None:
        ue.log_warning(f'spawn_obj: FBX import failed for "{path}"')
        return None

    actor = world.actor_spawn(StaticMeshActor)
    smc = actor.StaticMeshComponent
    smc.SetStaticMesh(mesh_asset)
    smc.Mobility = EComponentMobility.Movable
    _set_transform(actor, location, rotation, scale)
    return actor


# ---------------------------------------------------------------------------
# spawn_primitive
# ---------------------------------------------------------------------------

def spawn_primitive(primitive_type, location=None, rotation=None, scale=None):
    """Spawn a basic UE shape: 'cube' | 'sphere' | 'cylinder' | 'cone' | 'plane'"""
    MESH_MAP = {
        'cube':     '/Engine/BasicShapes/Cube',
        'sphere':   '/Engine/BasicShapes/Sphere',
        'cylinder': '/Engine/BasicShapes/Cylinder',
        'cone':     '/Engine/BasicShapes/Cone',
        'plane':    '/Engine/BasicShapes/Plane',
    }
    world = _get_world()
    mesh_path = MESH_MAP.get(primitive_type.lower())
    if mesh_path is None:
        ue.log_warning(f'spawn_primitive: unknown type "{primitive_type}". '
                       f'Choose from: {list(MESH_MAP.keys())}')
        return None
    actor = world.actor_spawn(StaticMeshActor)
    smc = actor.StaticMeshComponent
    smc.SetStaticMesh(ue.load_object(StaticMesh, mesh_path))
    smc.Mobility = EComponentMobility.Movable
    _set_transform(actor, location, rotation, scale)
    return actor


# ---------------------------------------------------------------------------
# Camera presets
# ---------------------------------------------------------------------------

CAMERA_PRESETS = {
    # Standard / safe default
    'default': {
        'focal_length': 35.0,
        'aperture': 5.6,
        'sensor_width': 36.0,
        'focus_distance': 1000.0,
        'panini': False,
    },
    # Classic cinematic wide angle
    'cinematic': {
        'focal_length': 24.0,
        'aperture': 2.8,
        'sensor_width': 36.0,
        'focus_distance': 800.0,
        'panini': False,
    },
    # Shallow DOF portrait — creamy subject isolation
    'bokeh_portrait': {
        'focal_length': 85.0,
        'aperture': 1.4,
        'sensor_width': 36.0,
        'focus_distance': 300.0,
        'panini': False,
    },
    # Medium telephoto bokeh — compressed background blur
    'bokeh_telephoto': {
        'focal_length': 135.0,
        'aperture': 1.8,
        'sensor_width': 36.0,
        'focus_distance': 500.0,
        'panini': False,
    },
    # Extreme macro bokeh — background nearly invisible
    'bokeh_macro': {
        'focal_length': 50.0,
        'aperture': 0.95,
        'sensor_width': 36.0,
        'focus_distance': 100.0,
        'panini': False,
    },
    # Panini projection — wide angle without barrel distortion
    'panini': {
        'focal_length': 14.0,
        'aperture': 8.0,
        'sensor_width': 36.0,
        'focus_distance': 2000.0,
        'panini': True,
        'panini_d': 1.0,
        'panini_screen_fit': 1.0,
    },
    # CCTV / security camera look
    'cctv': {
        'focal_length': 6.0,
        'aperture': 16.0,
        'sensor_width': 6.4,     # 1/3" CCTV sensor
        'focus_distance': 3000.0,
        'panini': False,
    },
    # Anamorphic-style widescreen
    'anamorphic': {
        'focal_length': 40.0,
        'aperture': 2.0,
        'sensor_width': 54.12,   # 2x anamorphic squeeze on full-frame
        'focus_distance': 600.0,
        'panini': False,
    },
}


def spawn_camera(location=None, rotation=None,
                 camera_type='cine',
                 preset=None,
                 focal_length=None,
                 aperture=None,
                 sensor_width=None,
                 focus_distance=None,
                 panini=False,
                 panini_d=1.0,
                 panini_screen_fit=1.0,
                 min_focal_length=None,
                 max_focal_length=None,
                 min_aperture=None,
                 max_aperture=None,
                 dof_blade_count=None):
    """
    Spawn a CineCameraActor or CameraActor with full lens / DOF / Panini control.

    Parameters
    ----------
    camera_type    : 'cine' (CineCameraActor) | 'standard' (CameraActor)
    preset         : str — one of CAMERA_PRESETS keys (see above)
                     Manual overrides below always take precedence.
    focal_length   : float  mm
    aperture       : float  f-stop (lower = more background blur / bokeh)
    sensor_width   : float  mm  (36 = full-frame, 23.6 = APS-C, 6.4 = CCTV)
    focus_distance : float  UE units (~cm)
    panini         : bool   enable Panini projection via console command
    panini_d       : float  0 = cylindrical, 1 = full Panini
    panini_screen_fit : float
    min/max_focal_length, min/max_aperture : float  lens range limits
    dof_blade_count : int   diaphragm blades (affects bokeh shape)

    Notes on Panini
    ---------------
    Panini is applied via:
        r.Upscale.Panini.D <value>
        r.Upscale.Panini.ScreenFit <value>
    This affects the entire viewport. After spawning, set the camera as the
    view target to take effect:
        ue.get_player_controller(0).SetViewTarget(cam)
    Call disable_panini() to revert.

    Returns
    -------
    actor (CineCameraActor | CameraActor)
    """
    world = _get_world()

    # Build config from preset + manual overrides
    cfg = dict(CAMERA_PRESETS.get('default'))
    if preset and preset in CAMERA_PRESETS:
        cfg.update(CAMERA_PRESETS[preset])
    if focal_length    is not None: cfg['focal_length']    = focal_length
    if aperture        is not None: cfg['aperture']        = aperture
    if sensor_width    is not None: cfg['sensor_width']    = sensor_width
    if focus_distance  is not None: cfg['focus_distance']  = focus_distance
    if panini:                      cfg['panini']          = True
    if panini_d        != 1.0:      cfg['panini_d']        = panini_d
    if panini_screen_fit != 1.0:    cfg['panini_screen_fit'] = panini_screen_fit

    actor = None

    # --- CineCameraActor ---
    if camera_type == 'cine':
        try:
            from unreal_engine.classes import CineCameraActor
            actor = world.actor_spawn(CineCameraActor)
            cam = actor.CameraComponent  # CineCameraComponent

            cam.CurrentFocalLength = cfg['focal_length']
            cam.CurrentAperture    = cfg['aperture']

            try:
                cam.FilmbackSettings.SensorWidth  = cfg['sensor_width']
                cam.FilmbackSettings.SensorHeight = cfg['sensor_width'] * 9.0 / 16.0
            except Exception:
                pass  # FilmbackSettings struct may vary by UE version

            try:
                cam.FocusSettings.ManualFocusDistance = cfg['focus_distance']
                cam.FocusSettings.FocusMethod = 1  # EFocusMethod::Manual
            except Exception:
                pass

            if min_focal_length is not None:
                try: cam.LensSettings.MinFocalLength = min_focal_length
                except Exception: pass
            if max_focal_length is not None:
                try: cam.LensSettings.MaxFocalLength = max_focal_length
                except Exception: pass
            if min_aperture is not None:
                try: cam.LensSettings.MinFStop = min_aperture
                except Exception: pass
            if max_aperture is not None:
                try: cam.LensSettings.MaxFStop = max_aperture
                except Exception: pass
            if dof_blade_count is not None:
                try: cam.LensSettings.DiaphragmBladeCount = dof_blade_count
                except Exception: pass

            try: cam.post_edit_change()
            except Exception: pass

        except Exception as e:
            ue.log_warning(f'spawn_camera (cine): {e}. Trying standard CameraActor...')
            camera_type = 'standard'

    # --- Standard CameraActor ---
    if camera_type == 'standard' or actor is None:
        try:
            from unreal_engine.classes import CameraActor
            actor = world.actor_spawn(CameraActor)
        except Exception as e:
            ue.log_warning(f'spawn_camera (standard): {e}')
            # NOTE: CameraActor spawn may fail at runtime in some UE configurations.
            pass  # editor-only fallback
            return None

    _set_transform(actor, location, rotation, FVector(1, 1, 1))

    # --- Panini projection ---
    if cfg.get('panini', False):
        d  = cfg.get('panini_d', 1.0)
        sf = cfg.get('panini_screen_fit', 1.0)
        _exec_console(f'r.Upscale.Panini.D {d}')
        _exec_console(f'r.Upscale.Panini.ScreenFit {sf}')
        ue.log(f'spawn_camera: Panini ON (D={d}, ScreenFit={sf}). '
               'Set this camera as view target: '
               'ue.get_player_controller(0).SetViewTarget(cam)')
    else:
        _exec_console('r.Upscale.Panini.D 0')

    return actor


def disable_panini():
    """Disable Panini projection."""
    _exec_console('r.Upscale.Panini.D 0')
    _exec_console('r.Upscale.Panini.ScreenFit 1')


# ---------------------------------------------------------------------------
# spawn_class / spawn_blueprint
# ---------------------------------------------------------------------------

def spawn_class(uclass, location=None, rotation=None, scale=None):
    """Spawn an arbitrary UClass."""
    world = _get_world()
    actor = world.actor_spawn(uclass)
    _set_transform(actor, location, rotation, scale)
    return actor


def spawn_blueprint(bp_path, location=None, rotation=None, scale=None):
    """
    Spawn an actor from a Blueprint asset path.
    Example: spawn_blueprint('/Game/Blueprints/BP_MyActor', FVector(0,0,100))
    """
    world = _get_world()
    bp = ue.load_object(Blueprint, bp_path)
    actor = world.actor_spawn(bp.GeneratedClass)
    _set_transform(actor, location, rotation, scale)
    return actor


# ---------------------------------------------------------------------------
# spawn_icon — PIL image → sphere + hover shrink
# ---------------------------------------------------------------------------

def spawn_icon(pil_image, location=None, rotation=None, scale=None,
               material_path='/Game/Materials/M_Icon',
               param_name='Param2D'):
    """
    Spawn a sphere, apply *pil_image* as *param_name* texture, and attach
    a mouse-hover shrink effect (IconHoverComponent).

    Requires Pillow and a material at *material_path* with a
    TextureSampleParameter2D named *param_name*.
    """
    world = _get_world()

    tmp_path = os.path.join(tempfile.gettempdir(), 'ue_icon_tmp.png')
    pil_image.save(tmp_path)

    texture = None
    try:
        from unreal_engine.classes import TextureFactory
        texture = TextureFactory().factory_import_object(
            tmp_path, '/Game/IconTextures/IconTex')
    except Exception as e:
        ue.log_warning(f'spawn_icon: texture import failed: {e}')

    actor = world.actor_spawn(StaticMeshActor)
    smc = actor.StaticMeshComponent
    smc.SetStaticMesh(ue.load_object(StaticMesh, '/Engine/BasicShapes/Sphere'))
    smc.Mobility = EComponentMobility.Movable

    mat = ue.load_object(Material, material_path)
    if mat and texture:
        try:
            dmi = smc.CreateAndSetMaterialInstanceDynamic(0)
            dmi.SetTextureParameterValue(param_name, texture)
        except Exception as e:
            ue.log_warning(f'spawn_icon: texture param failed: {e}')

    scl = scale if scale is not None else FVector(1, 1, 1)
    _set_transform(actor, location, rotation, scl)

    try:
        actor.add_python_component(IconHoverComponent)
    except Exception as e:
        ue.log_warning(f'spawn_icon: could not attach hover component: {e}')

    return actor


# ---------------------------------------------------------------------------
# Python component: hover-shrink for spawn_icon
# ---------------------------------------------------------------------------

class IconHoverComponent:
    """
    Mouse-hover shrink animation for a StaticMeshActor.
    Requires 'Enable Mouse over Events' in Project Settings > Input.
    """
    HOVER_DELTA = 0.1
    LERP_SPEED  = 8.0

    def begin_play(self):
        self.base_scale   = self.uobject.get_actor_scale()
        self.target_scale = self.base_scale
        try:
            smc = self.uobject.StaticMeshComponent
            smc.bind_event('OnBeginCursorOver', self.on_hover_begin)
            smc.bind_event('OnEndCursorOver',   self.on_hover_end)
        except Exception as e:
            ue.log_warning(f'IconHoverComponent: cursor events unavailable: {e}')

    def on_hover_begin(self, mesh):
        d  = self.HOVER_DELTA
        bs = self.base_scale
        self.target_scale = FVector(bs.x - d, bs.y - d, bs.z - d)

    def on_hover_end(self, mesh):
        self.target_scale = self.base_scale

    def tick(self, dt):
        cur = self.uobject.get_actor_scale()
        tgt = self.target_scale
        a   = min(1.0, self.LERP_SPEED * dt)
        self.uobject.set_actor_scale(FVector(
            cur.x + (tgt.x - cur.x) * a,
            cur.y + (tgt.y - cur.y) * a,
            cur.z + (tgt.z - cur.z) * a,
        ))


# ---------------------------------------------------------------------------
# Python component: clickable sound sphere
# ---------------------------------------------------------------------------

class SoundSphereActor:
    """
    Attach to BP_SoundSphere.
    Blueprint needs StaticMeshComponent (sphere) + public Sound (SoundBase).
    """
    def begin_play(self):
        self.sound = getattr(self.uobject, 'Sound', None)
        try:
            smc = self.uobject.StaticMeshComponent
            smc.bind_event('OnClicked', self.on_clicked)
            smc.bind_event('OnComponentBeginOverlap', self.on_overlap)
        except Exception as e:
            ue.log_warning(f'SoundSphereActor: could not bind events: {e}')

    def on_clicked(self, mesh, button):
        self._play()

    def on_overlap(self, *args):
        self._play()

    def _play(self):
        if self.sound is None:
            self.sound = getattr(self.uobject, 'Sound', None)
        if self.sound:
            self.uobject.play_sound_at_location(
                self.sound, self.uobject.get_actor_location())
        else:
            ue.log_warning('SoundSphereActor: no Sound asset assigned.')


# ---------------------------------------------------------------------------
# File-type detection
# ---------------------------------------------------------------------------

IMAGE_EXTS  = {'.png', '.jpg', '.jpeg', '.bmp', '.tga', '.tiff', '.exr',
               '.hdr', '.webp', '.ico', '.gif', '.psd'}
VIDEO_EXTS  = {'.mp4', '.avi', '.mov', '.mkv', '.wmv', '.webm', '.flv',
               '.ts', '.m4v'}
SOUND_EXTS  = {'.wav', '.mp3', '.ogg', '.flac', '.aif', '.aiff'}
OBJ_EXTS    = {'.fbx', '.obj', '.dae', '.collada', '.3ds', '.ply', '.stl',
               '.gltf', '.glb', '.blend', '.dxf', '.x3d', '.wrl', '.off'}
PRIMITIVE_NAMES  = {'cube', 'sphere', 'cylinder', 'cone', 'plane'}
CAMERA_KEYWORDS  = {'camera', 'cam', 'cine', 'cinecamera'}


def _detect_type(path_or_name):
    lower = path_or_name.lower()
    if lower in PRIMITIVE_NAMES:  return 'primitive'
    if lower in CAMERA_KEYWORDS:  return 'camera'
    ext = os.path.splitext(lower)[1]
    if ext in IMAGE_EXTS:         return 'image'
    if ext in VIDEO_EXTS:         return 'video'
    if ext in SOUND_EXTS:         return 'sound'
    if ext in OBJ_EXTS:           return 'obj'
    if lower.startswith('/game/') or lower.startswith('/engine/'):
        return 'blueprint'
    return None


# ---------------------------------------------------------------------------
# Main spawn()
# ---------------------------------------------------------------------------

def spawn(
    path_or_type,
    location=None,
    rotation=None,
    scale=None,
    # Explicit type override
    type=None,
    # Sound options
    volume=1.0,
    pitch=1.0,
    start_time=0.0,
    as_sound_actor=False,
    # Image / Video material
    material_path=None,
    param_name='Texture',
    # Video
    autoplay=True,
    # 3-D import destination
    import_path='/Game/ImportedMeshes',
    # Class spawn
    uclass=None,
    # Primitive shape override
    primitive_type=None,
    # Camera options (all forwarded to spawn_camera)
    camera_type='cine',
    camera_preset=None,
    focal_length=None,
    aperture=None,
    sensor_width=None,
    focus_distance=None,
    panini=False,
    panini_d=1.0,
    panini_screen_fit=1.0,
    min_focal_length=None,
    max_focal_length=None,
    min_aperture=None,
    max_aperture=None,
    dof_blade_count=None,
):
    """
    Universal spawn function for UnrealEnginePython.

    Auto-detects type from extension/keyword, or pass type= explicitly.

    Type detection
    --------------
    image       .png .jpg .tga .exr .webp .gif .psd …  (auto-converts to PNG)
    video       .mp4 .avi .mov .mkv .webm …             (auto-converts to MP4)
    sound       .wav .mp3 .ogg  or  UE asset path
    obj         .fbx .obj .glb .gltf .dae .ply .stl .blend .3ds …
                                                         (auto-converts to FBX)
    primitive   'cube' 'sphere' 'cylinder' 'cone' 'plane'
    camera      'camera' 'cam' 'cine'
    blueprint   '/Game/…' UE content path
    class       pass uclass= parameter

    Camera presets (camera_preset=)
    --------------------------------
    'default'         35mm f/5.6 full-frame
    'cinematic'       24mm f/2.8
    'bokeh_portrait'  85mm f/1.4  — shallow DOF subject isolation
    'bokeh_telephoto' 135mm f/1.8 — compressed background blur
    'bokeh_macro'     50mm f/0.95 — extreme bokeh
    'panini'          14mm + Panini projection ON
    'cctv'            6mm 1/3" sensor
    'anamorphic'      40mm f/2.0 anamorphic sensor

    Returns
    -------
    actor
    (actor, media_player, media_texture)  for video
    None                                  for immediate sound playback
    """
    detected = type if type else _detect_type(path_or_type)

    if detected is None:
        ue.log_warning(
            f'spawn: cannot detect type for "{path_or_type}". '
            'Pass type= explicitly. '
            'Supported: image, video, sound, obj, primitive, camera, class, blueprint.'
        )
        return None

    if detected == 'image':
        kw = {'param_name': param_name}
        if material_path: kw['material_path'] = material_path
        return spawn_image(path_or_type, location, rotation, scale, **kw)

    elif detected == 'video':
        kw = {'param_name': param_name, 'autoplay': autoplay}
        if material_path: kw['material_path'] = material_path
        return spawn_video(path_or_type, location, rotation, scale, **kw)

    elif detected == 'sound':
        return spawn_sound(
            path_or_type, location,
            volume=volume, pitch=pitch, start_time=start_time,
            as_actor=as_sound_actor,
        )

    elif detected == 'obj':
        return spawn_obj(path_or_type, location, rotation, scale,
                         import_path=import_path)

    elif detected == 'primitive':
        ptype = primitive_type or path_or_type.lower()
        return spawn_primitive(ptype, location, rotation, scale)

    elif detected == 'camera':
        return spawn_camera(
            location=location, rotation=rotation,
            camera_type=camera_type,
            preset=camera_preset,
            focal_length=focal_length,
            aperture=aperture,
            sensor_width=sensor_width,
            focus_distance=focus_distance,
            panini=panini,
            panini_d=panini_d,
            panini_screen_fit=panini_screen_fit,
            min_focal_length=min_focal_length,
            max_focal_length=max_focal_length,
            min_aperture=min_aperture,
            max_aperture=max_aperture,
            dof_blade_count=dof_blade_count,
        )

    elif detected == 'class':
        if uclass is None:
            ue.log_warning('spawn: type="class" requires uclass= parameter.')
            return None
        return spawn_class(uclass, location, rotation, scale)

    elif detected == 'blueprint':
        return spawn_blueprint(path_or_type, location, rotation, scale)

    else:
        ue.log_warning(f'spawn: unknown type "{detected}".')
        return None


# ---------------------------------------------------------------------------
# Usage examples
# ---------------------------------------------------------------------------
#
# from ue_spawn import spawn, spawn_icon, disable_panini, CAMERA_PRESETS
# from unreal_engine import FVector, FRotator
#
# # Image plane (JPEG, auto aspect-ratio)
# actor = spawn('C:/photos/sunset.jpg', location=FVector(0, 0, 100))
#
# # Image plane (WebP → auto-converted to PNG)
# actor = spawn('C:/photos/icon.webp', location=FVector(200, 0, 100))
#
# # Video plane (MP4, autoplay)
# actor, player, tex = spawn('C:/videos/clip.mp4', location=FVector(400, 0, 100))
# # Later: player.call('Pause')  /  player.call('Play')
#
# # Video plane (MOV → auto-converted to MP4 via ffmpeg)
# actor, player, tex = spawn('C:/videos/intro.mov', location=FVector(0, 200, 100))
#
# # 3-D mesh (GLB → auto-converted to FBX via trimesh)
# mesh = spawn('C:/models/chair.glb', location=FVector(0, 0, 0))
#
# # 3-D mesh (Blender file → auto-converted via Blender CLI)
# mesh = spawn('C:/models/scene.blend', location=FVector(100, 0, 0))
#
# # Sound (immediate)
# spawn('/Game/Sounds/Explosion', type='sound', location=FVector(0, 0, 0))
#
# # Sound (clickable sphere)
# snd = spawn('/Game/Sounds/Ambient', type='sound',
#             as_sound_actor=True, location=FVector(500, 0, 50))
#
# # Primitive
# cyl = spawn('cylinder', scale=FVector(0.5, 0.5, 3.0), location=FVector(0, 300, 0))
#
# # Camera — bokeh portrait preset
# cam = spawn('camera', camera_preset='bokeh_portrait',
#             location=FVector(-500, 0, 200))
#
# # Camera — extreme bokeh with manual override
# cam = spawn('camera', camera_preset='bokeh_macro',
#             aperture=0.7, focus_distance=80.0)
#
# # Camera — Panini projection
# cam = spawn('camera', camera_preset='panini', location=FVector(0, 0, 100))
# # Set as view target to activate Panini:
# ue.get_player_controller(0).SetViewTarget(cam)
#
# # Camera — standard (non-cine) actor
# cam = spawn('camera', camera_type='standard', location=FVector(-200, 0, 150))
#
# # Disable Panini
# disable_panini()
#
# # Blueprint
# bp_actor = spawn('/Game/Blueprints/BP_Cell', location=FVector(300, 0, 0))
#
# # Icon sphere with hover effect
# from PIL import Image
# img = Image.open('icon.png')
# icon_actor = spawn_icon(img, location=FVector(0, 0, 200))
#
# # Print available camera presets
# print(list(CAMERA_PRESETS.keys()))