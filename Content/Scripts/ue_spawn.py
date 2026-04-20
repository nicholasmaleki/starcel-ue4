"""
ue_spawn.py — Universal spawn() utility for UnrealEnginePython
Runtime-only (editor-only paths are stubbed with pass + comment).

Dependencies:
  - UnrealEnginePython plugin
  - PIL / Pillow          (spawn_image, spawn_video, spawn_icon)
  - trimesh               (3-D format conversion: pip install trimesh)
  - ffmpeg on PATH        (video format conversion)
  - ue_components.py      (SoundSphereActor, IconHoverComponent — kept separate)

Blueprint requirements:
  BP_SoundSphere  (/Game/Blueprints/BP_SoundSphere):
    • StaticMeshComponent (sphere), Generate Overlap Events ON
    • Mouse Button Clicked enabled in Project Settings > Input
    • Public variable 'Sound' (SoundBase)
    • Python component pointing to ue_components.SoundSphereActor

  BP_Icon  (/Game/Blueprints/BP_Icon):
    • StaticMeshComponent (sphere or any mesh)
    • Python component pointing to ue_components.IconHoverComponent
    • Public variable 'IconTexture' (Texture2D) — optional, set via Python
"""

import os
import subprocess
import tempfile
from PIL import Image
import numpy as np
import unreal_engine as ue
from unreal_engine import FVector, FRotator, FTransform
from unreal_engine.classes import (
    StaticMeshActor, StaticMesh, Material, Blueprint,
)
from unreal_engine.enums import EComponentMobility, EPixelFormat
from unreal_engine_tools import pil_image_to_texture, get_world, find_component
from icon_to_image import extract_icon, get_folder_icons

# Helpers

def _get_world():
    try:
        return get_world()
    except Exception as e:
        print("Can't find world", e)


def _set_transform(actor, location, rotation, scale):
    loc = location if location is not None else FVector(0, 0, 0)
    rot = rotation if rotation is not None else FRotator(0, 0, 0)
    scl = scale    if scale    is not None else FVector(1, 1, 1)
    # actor.set_actor_location(loc)
    # actor.set_actor_rotation(rot)
    # actor.set_actor_scale(scl)
    transform = FTransform(loc, rot, scl)
    actor.set_actor_transform(transform)


def spawn_pyactor(python_module, python_class,
                  location=None, rotation=None, scale=None,
                  components=None,
                  bp_path='/Game/Blueprints/Assets/BP_PyActorEmpty.BP_PyActorEmpty',
                  source_path=None,
                  name=None):
    """
    Spawn a PyActor dynamically with the given Python module/class attached.

    *components* is an optional list of dicts, each with:
        class_name : str  — UE component class (e.g. 'StaticMeshComponent')
        name       : str  — component name
        mesh       : str  — optional mesh asset path to SetStaticMesh
        root       : bool — if True, use add_actor_root_component

    *bp_path* — host Blueprint to spawn (default BP_PyActorEmpty).
    *source_path* — optional file path attached as ``actor.source_path``
    so click handlers (e.g. pyactor_icon) can open it.
    *name* — optional editor label (set via set_actor_label). Defaults to
    ``python_class`` so each spawned actor gets a readable outliner name.

    Returns the spawned actor.
    """
    world = _get_world()
    loc = location if location is not None else FVector(0, 0, 0)
    rot = rotation if rotation is not None else FRotator(0, 0, 0)

    bp_pyactor = ue.load_object(Blueprint, bp_path)
    # kwargs route UEP through SpawnActorDeferred -> set props -> FinishSpawning,
    # so PythonModule/PythonClass are bound before BeginPlay fires.
    actor = world.actor_spawn(
        bp_pyactor.GeneratedClass, loc, rot,
        PythonModule=python_module,
        PythonClass=python_class,
    )

    if scale is not None:
        actor.set_actor_transform(FTransform(loc, rot, scale))

    # Components are added after BeginPlay — not visible in begin_play,
    # accessible from first tick onward.
    if components:
        for comp in components:
            cls = ue.find_class(comp['class_name'])
            if comp.get('root', False):
                c = actor.add_actor_root_component(cls, comp['name'])
            else:
                c = actor.add_actor_component(cls, comp['name'])
            if comp.get('mesh'):
                mesh_obj = ue.load_object(StaticMesh, comp['mesh'])
                c.SetStaticMesh(mesh_obj)
                c.Mobility = EComponentMobility.Movable

    if actor is not None and source_path is not None:
        try:
            actor.source_path = source_path
        except Exception as e:
            ue.log_warning(f'spawn_pyactor: could not attach source_path: {e}')

    if actor is not None:
        try:
            actor.set_actor_label(name if name else python_class)
        except Exception:
            pass

    return actor


def _exec_console(cmd):
    """Run a console command via the player controller."""
    # Try world.get_player_controller first (standard UEP path)
    try:
        pc = _get_world().get_player_controller(0)
        pc.ConsoleCommand(cmd)
        return
    except Exception:
        pass
    # Fallback: iterate world actors and find a PlayerController
    try:
        from unreal_engine.classes import PlayerController
        for actor in _get_world().all_actors():
            try:
                if actor.is_a(PlayerController):
                    actor.ConsoleCommand(cmd)
                    return
            except Exception:
                continue
    except Exception as e:
        ue.log_warning(f'_exec_console: failed to run "{cmd}": {e}')


# Format conversion utilities

# Image conversion

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


# Video conversion

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
            capture_output=True, text=True,
            creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0),
        )
        if result.returncode == 0:
            ue.log(f'_ensure_video: converted "{ext}" -> MP4 ({tmp})')
            return tmp
        ue.log_warning(f'_ensure_video: ffmpeg error:\n{result.stderr}')
    except FileNotFoundError:
        ue.log_warning('_ensure_video: ffmpeg not found on PATH. '
                       'Install ffmpeg to auto-convert video formats.')
    return path


# 3-D format conversion

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
                capture_output=True, text=True, timeout=120,
                creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0),
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

    # trimesh (fast, no external app needed)
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

    # Blender CLI fallback
    if ext in OBJ_TRIMESH or ext in OBJ_BLENDER:
        if _convert_via_blender(path, tmp_fbx):
            return tmp_fbx

    ue.log_warning(
        f'_ensure_fbx: could not convert "{ext}" to FBX. '
        'Install trimesh (pip install trimesh) or Blender (ensure it is on PATH).'
    )
    return None


# spawn_image

def spawn_image(path, location=None, rotation=None, scale=None,
                material_path='/Game/Materials/M_TexturePicture',
                param_name='Texture'):
    """
    Spawn a vertical cube textured with the image at *path* (picture frame).

    Uses M_TexturePicture as a MID with a pil_image_to_texture-generated
    texture — no UE asset import required.  The cube is oriented vertically:
    width on X, thin on Y, height on Z, sized to match the image's pixel
    dimensions (1 px = 1 UU).

    Unsupported formats are auto-converted to PNG via PIL.
    """
    from PIL import Image as PILImage
    from unreal_engine_tools import pil_image_to_texture

    world = _get_world()
    path  = _ensure_image(path)

    # load and size the image
    try:
        pil_img = PILImage.open(path).convert('RGBA')
    except Exception as e:
        ue.log_warning(f'spawn_image: cannot open "{path}": {e}')
        return None

    img_w, img_h = float(pil_img.width), float(pil_img.height)

    # spawn cube actor (no location; transform set after)
    actor = world.actor_spawn(StaticMeshActor)
    smc   = actor.StaticMeshComponent
    cube  = ue.load_object(StaticMesh, '/Engine/BasicShapes/Cube.Cube')
    smc.SetStaticMesh(cube)
    smc.Mobility = EComponentMobility.Movable

    # apply M_TexturePicture as MID, set texture parameter
    mat = ue.load_object(Material, material_path + '.' + material_path.split('/')[-1])
    if mat is None:
        mat = ue.load_object(Material, material_path)
    if mat:
        try:
            mid = smc.create_material_instance_dynamic(mat)
            tex = pil_image_to_texture(pil_img)
            if tex:
                mid.set_material_texture_parameter(param_name, tex)
            smc.set_material(0, mid)
        except Exception as e:
            ue.log_warning(f'spawn_image: material/texture setup failed: {e}')
    else:
        ue.log_warning(f'spawn_image: could not load material at "{material_path}"')

    # vertical picture-frame scaling: 1 px → 1 UU
    # Default cube is 100×100×100 UU, so divide by 100 for unit scale.
    # X = width, Z = height (vertical), Y = thin frame depth.
    if scale is None:
        scale = FVector(img_w / 100.0, 0.05, img_h / 100.0)
    ue.log(f'spawn_image: "{os.path.basename(path)}" {int(img_w)}x{int(img_h)} px '
           f'→ scale=({scale.x:.3f}, {scale.y:.3f}, {scale.z:.3f})  '
           f'world size = {int(img_w)}x{int(scale.y*100)}x{int(img_h)} UU')
    _set_transform(actor, location, rotation, scale)
    # Verify UE actually applied the non-uniform scale
    try:
        s = actor.get_actor_scale()
        ue.log(f'spawn_image: actor scale readback = '
               f'({s.x:.3f}, {s.y:.3f}, {s.z:.3f})')
    except Exception:
        pass
    return actor


def spawn_video(video_path, location=None, rotation=None, scale=None,
                     material_path='/Game/Movies/M_VideoTexture_Video',
                     media_player_path='/Game/Movies/MP_VideoTexture'):
    """
    Spawn a thin cube with M_VideoTexture_Video applied directly, and call
    OpenUrl on the MediaPlayer so the material's existing MediaTexture →
    MediaPlayer wiring plays the given video file.
    """
    from unreal_engine.classes import MediaPlayer

    world = _get_world()
    video_path = _ensure_video(video_path)

    # read video dimensions for aspect-ratio scale
    vid_w, vid_h = 1920.0, 1080.0
    try:
        result = subprocess.run(
            ['ffprobe', '-v', 'error', '-select_streams', 'v:0',
             '-show_entries', 'stream=width,height', '-of', 'csv=p=0', video_path],
            capture_output=True, text=True,
            creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0),
        )
        parts = result.stdout.strip().split(',')
        if len(parts) == 2:
            vid_w, vid_h = float(parts[0]), float(parts[1])
    except Exception:
        pass

    actor = world.actor_spawn(StaticMeshActor)
    smc   = actor.StaticMeshComponent
    smc.SetStaticMesh(ue.load_object(StaticMesh, '/Engine/BasicShapes/Cube.Cube'))
    smc.Mobility = EComponentMobility.Movable
    smc.set_material(0, ue.load_object(Material, material_path))

    mp = ue.load_object(MediaPlayer, media_player_path)
    mp.OpenUrl('file://' + os.path.abspath(video_path).replace('\\', '/'))

    if scale is None:
        scale = FVector(vid_w / 100.0, 0.05, vid_h / 100.0)
    _set_transform(actor, location, rotation, scale)
    return actor


# spawn_video_plane — uses BP_VideoSkySphere's SetVideoBackground pattern
#
# NOTE ON VIDEO IN THIS PROJECT:
# The working video path is BP_VideoSkySphere.call_function("SetVideoBackground",
# "file://" + abs_path).  That Blueprint wires MediaPlayer → MediaTexture →
# FileMediaSource → Material internally via its Blueprint graph.  Trying to
# create those objects from Python via ue.new_object() and wire them manually
# does NOT produce a playable result in UE4.27+UEP — the MediaTexture never
# receives frames because the Blueprint event graph (ReceiveTick, OnMediaOpened)
# is what pumps the texture each frame.
#
# spawn_video_plane therefore spawns BP_VideoSkySphere and calls
# SetVideoBackground, then repositions and rescales the actor to act as a
# flat video picture frame instead of a sky sphere.

# def spawn_video_plane(path, location=None, rotation=None, scale=None,
#                       bp_path='/Game/Blueprints/Assets/BP_VideoSkySphere.BP_VideoSkySphere'):
#     """
#     Spawn a BP_VideoSkySphere and call ``SetVideoBackground("file://..." + path)``
#     to play a video — the same proven method used by ``change_background("video", ...)``
#     for the psychedelic sky background.
#
#     The actor is repositioned to *location* and optionally rescaled to *scale*.
#     If *scale* is None, it is left at the Blueprint's default scale (sky sphere
#     sized).  Pass a small scale like ``FVector(0.01, 0.01, 0.01)`` to use it as
#     a room-scale video screen.
#
#     Parameters
#     ----------
#     path    : absolute filesystem path to an MP4 video
#     location: FVector world position (default origin)
#     rotation: FRotator (default identity)
#     scale   : FVector  (default None = Blueprint default)
#     bp_path : package path to the video-capable Blueprint
#
#     Returns
#     -------
#     actor   : the spawned BP_VideoSkySphere actor (holds MediaPlayer internally)
#     """
#     world = _get_world()
#     path  = _ensure_video(path)
#
#     # spawn the Blueprint
#     try:
#         bp = ue.load_object(Blueprint, bp_path)
#     except Exception as e:
#         ue.log_warning(f'spawn_video_plane: could not load "{bp_path}": {e}')
#         return None
#     if bp is None:
#         ue.log_warning(f'spawn_video_plane: Blueprint not found at "{bp_path}"')
#         return None
#
#     try:
#         actor = world.actor_spawn(bp.GeneratedClass)
#     except Exception as e:
#         ue.log_warning(f'spawn_video_plane: actor_spawn failed: {e}')
#         return None
#
#     # position / scale
#     _set_transform(actor, location, rotation, scale)
#
#     # play the video (same call as change_background("video", path))
#     ue_path = "file://" + os.path.abspath(path)
#     try:
#         actor.call_function("SetVideoBackground", ue_path)
#         ue.log(f'spawn_video_plane: SetVideoBackground("{os.path.basename(path)}") '
#                f'on {actor.get_name()}')
#     except Exception as e:
#         ue.log_warning(f'spawn_video_plane: SetVideoBackground failed: {e}')
#
#     return actor


# spawn_video
#
# def spawn_video(path, location=None, rotation=None, scale=None,
#                 material_path='/Game/Movies/M_VideoTexture_Video',
#                 param_name='MediaTexture',
#                 autoplay=True):
#     """
#     Spawn a thin cube (like image plane, scaled to video resolution) and
#     drive it with a MediaPlayer + MediaTexture at runtime.
#
#     Unsupported video formats (.mov, .mkv, .webm, etc.) are auto-converted
#     to MP4 via ffmpeg.
#
#     The material at *material_path* must have a TextureSampleParameter2D
#     named *param_name* wired to a MediaTexture.
#
#     Returns (actor, media_player, media_texture) so callers can pause/seek.
#     """
#     from unreal_engine.classes import MediaPlayer, MediaTexture, FileMediaSource
#
#     world = _get_world()
#     path = _ensure_video(path)
#
#     # Read video dimensions for aspect-ratio scale (via ffprobe)
#     vid_w, vid_h = 192.0, 108.0  # default 16:9 fallback
#     try:
#         result = subprocess.run(
#             ['ffprobe', '-v', 'error', '-select_streams', 'v:0',
#              '-show_entries', 'stream=width,height', '-of', 'csv=p=0', path],
#             capture_output=True, text=True,
#             creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0),
#         )
#         parts = result.stdout.strip().split(',')
#         if len(parts) == 2:
#             vid_w, vid_h = float(parts[0]), float(parts[1])
#     except Exception:
#         pass
#
#     actor = world.actor_spawn(StaticMeshActor)
#     smc = actor.StaticMeshComponent
#     smc.SetStaticMesh(ue.load_object(StaticMesh, '/Engine/BasicShapes/Cube'))
#     smc.Mobility = EComponentMobility.Movable
#
#     # Create runtime media objects
#     media_player  = ue.new_object(MediaPlayer)
#     media_texture = ue.new_object(MediaTexture)
#     media_source  = ue.new_object(FileMediaSource)
#
#     media_texture.set_media_player(media_player)
#     media_source.set_file_path(path)
#
#     # Bind MediaTexture to material
#     mat = ue.load_object(Material, material_path)
#     if mat:
#         try:
#             dmi = smc.CreateAndSetMaterialInstanceDynamic(0)
#             dmi.SetTextureParameterValue(param_name, media_texture)
#         except Exception as e:
#             ue.log_warning(f'spawn_video: material setup failed: {e}')
#     else:
#         ue.log_warning(
#             f'spawn_video: material not found at "{material_path}". '
#             f'Create a material with a TextureSampleParameter2D named "{param_name}".'
#         )
#
#     if autoplay:
#         media_player.open_source(media_source)
#         media_player.play()
#
#     vid_scale = scale if scale is not None else FVector(vid_w / 100.0, vid_h / 100.0, 0.01)
#     _set_transform(actor, location, rotation, vid_scale)
#     return actor, media_player, media_texture


# Audio decode (arbitrary files -> s16le PCM via ffmpeg)

AUDIO_FILE_EXTS = {'.wav', '.flac', '.mp3', '.ogg', '.m4a',
                   '.aac', '.opus', '.wma', '.aif', '.aiff'}

# Keep-alive registry: USoundWaveProcedural is garbage-collected the moment
# no Python ref survives, which cuts playback mid-stream.
_procedural_sounds = []


def _decode_audio_to_pcm(path, target_rate=44100, target_channels=2):
    """Decode any audio file to interleaved 16-bit signed PCM via ffmpeg.

    Returns (pcm_bytes, sample_rate, num_channels) or (None, None, None).
    Uses the same ffmpeg dependency as _ensure_video; no extra pip install.
    """
    if not os.path.isfile(path):
        return None, None, None
    try:
        result = subprocess.run(
            ['ffmpeg', '-hide_banner', '-loglevel', 'error',
             '-i', path,
             '-f', 's16le', '-acodec', 'pcm_s16le',
             '-ar', str(target_rate), '-ac', str(target_channels),
             '-'],
            capture_output=True, timeout=180,
            creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0),
        )
    except FileNotFoundError:
        ue.log_warning('_decode_audio_to_pcm: ffmpeg not found on PATH.')
        return None, None, None
    except subprocess.TimeoutExpired:
        ue.log_warning(f'_decode_audio_to_pcm: ffmpeg timeout on {path}')
        return None, None, None
    if result.returncode != 0:
        ue.log_warning('_decode_audio_to_pcm: ffmpeg error:\n' +
                       result.stderr.decode(errors='replace')[:500])
        return None, None, None
    return result.stdout, target_rate, target_channels


def _play_audio_file(world, path, location, volume, pitch):
    """Decode *path* and play it through a transient USoundWaveProcedural.
    Returns the sound wave (held in _procedural_sounds so playback survives)."""
    from unreal_engine.classes import SoundWaveProcedural
    pcm, rate, channels = _decode_audio_to_pcm(path)
    if not pcm:
        return None
    frames   = len(pcm) // (2 * channels)          # 2 bytes per s16 sample
    duration = frames / float(rate)

    sw = ue.new_object(SoundWaveProcedural)
    sw.SampleRate  = rate
    sw.NumChannels = channels
    sw.Duration    = duration + 1.0                # small safety margin
    sw.SoundGroup  = 0                             # SOUNDGROUP_Default
    sw.bLooping    = False

    sw.queue_audio(pcm)
    world.play_sound_at_location(sw, location, volume, pitch, 0.0)
    _procedural_sounds.append(sw)
    ue.log(f'_play_audio_file: queued {duration:.2f}s '
           f'({len(pcm)} bytes, {rate}Hz x{channels}) from {path}')
    return sw


# spawn_sound

def spawn_sound(path, location=None, volume=1.0, pitch=1.0,
                start_time=0.0, as_actor=False):
    """
    Play a sound immediately, or spawn a clickable/proximity sphere.

    *path*:
      • UE asset path  ('/Game/Sounds/MySound') -> resolved via load_object
      • Filesystem file (.wav/.flac/.mp3/.ogg/.m4a/...) -> decoded via ffmpeg
        into a USoundWaveProcedural and played in place.

    *as_actor=True*: spawns BP_SoundSphere (see SoundSphereActor below).
    Filesystem audio + as_actor is not supported (SoundSphere needs a
    persistent SoundBase asset, not a transient procedural wave).
    """
    world = _get_world()
    loc = location if location is not None else FVector(0, 0, 0)

    # Filesystem audio file: decode and play via SoundWaveProcedural.
    ext = os.path.splitext(path)[1].lower()
    if ext in AUDIO_FILE_EXTS and os.path.isfile(path):
        if as_actor:
            ue.log_warning('spawn_sound: as_actor not supported for filesystem '
                           'audio; playing at location instead.')
        return _play_audio_file(world, path, loc, volume, pitch)

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
            actor = spawn_pyactor(
                'pyactor_sound', 'SoundSphere',
                location=loc,
                components=[dict(class_name='StaticMeshComponent',
                                 name='Sphere', root=True,
                                 mesh='/Engine/BasicShapes/Sphere.Sphere')])
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


# spawn_obj

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


# spawn_primitive

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


# Camera presets

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
    # r.Upscale.Panini.D controls the D warp (0=off, 0.5=moderate, 1=full)
    # r.Upscale.Panini.S controls the vertical screen-fit compression
    # r.ScreenPercentage controls super-sampling (100=native, 150=1.5x)
    'panini': {
        'focal_length': 14.0,
        'aperture': 8.0,
        'sensor_width': 36.0,
        'focus_distance': 2000.0,
        'panini': True,
        'panini_d': 0.5,         # r.Upscale.Panini.D
        'panini_s': 0.05,        # r.Upscale.Panini.S
        'screen_percentage': 150,  # r.ScreenPercentage
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

# TODO: SetProjectionMode ECameraProjectionMode::Perspective/Orthographic
def spawn_camera(location=None, rotation=None,
                 camera_type='cine',
                 preset=None,
                 focal_length=None,
                 aperture=None,
                 sensor_width=None,
                 focus_distance=None,
                 panini=False,
                 panini_d=0.5,
                 panini_s=0.05,
                 screen_percentage=150,
                 min_focal_length=None,
                 max_focal_length=None,
                 min_aperture=None,
                 max_aperture=None,
                 dof_blade_count=None,
                 set_view_target=True,
                 view_blend_time=0.0):
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
    panini            : bool  enable Panini projection via console commands
    panini_d          : float r.Upscale.Panini.D  (0=off, 0.5=moderate, 1=full)
    panini_s          : float r.Upscale.Panini.S  (0=off, 0.05=slight compression)
    screen_percentage : int   r.ScreenPercentage  (100=native, 150=super-sampled)
    min/max_focal_length, min/max_aperture : float  lens range limits
    dof_blade_count   : int   diaphragm blades (affects bokeh shape)
    set_view_target   : bool  automatically view through this camera after spawn
    view_blend_time   : float seconds for SetViewTargetWithBlend (0 = instant)

    Notes on Panini
    ---------------
    Three console commands are issued when panini=True:
        r.Upscale.Panini.D <d>
        r.Upscale.Panini.S <s>
        r.ScreenPercentage <pct>
    This affects the entire viewport. After spawning, set the camera as the
    view target to take effect:
        ue.get_player_controller(0).SetViewTarget(cam)
    Call disable_panini() to revert (D=0, S=0, ScreenPercentage=100).

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
    if panini_d        != 0.5:      cfg['panini_d']        = panini_d
    if panini_s        != 0.05:     cfg['panini_s']        = panini_s
    if screen_percentage != 150:    cfg['screen_percentage'] = screen_percentage

    actor = None

    # CineCameraActor
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

    # Standard CameraActor
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

    # Panini projection
    if cfg.get('panini', False):
        d   = cfg.get('panini_d', 0.5)
        s   = cfg.get('panini_s', 0.05)
        pct = cfg.get('screen_percentage', 150)
        _exec_console(f'r.Upscale.Panini.D {d}')
        _exec_console(f'r.Upscale.Panini.S {s}')
        _exec_console(f'r.ScreenPercentage {pct}')
        ue.log(f'spawn_camera: Panini ON (D={d}, S={s}, ScreenPercentage={pct}). '
               'Set this camera as view target: '
               'ue.get_player_controller(0).SetViewTarget(cam)')
    else:
        _exec_console('r.Upscale.Panini.D 0')
        _exec_console('r.Upscale.Panini.S 0')
        _exec_console('r.ScreenPercentage 100')

    # View through the camera
    if set_view_target:
        try:
            pc = _get_world().get_player_controller(0)
            if view_blend_time > 0:
                pc.SetViewTargetWithBlend(actor, view_blend_time)
            else:
                pc.SetViewTarget(actor)
        except Exception as e:
            ue.log_warning(f'spawn_camera: SetViewTarget failed: {e}')

    return actor


def disable_panini():
    """Disable Panini projection and restore native screen percentage."""
    _exec_console('r.Upscale.Panini.D 0')
    _exec_console('r.Upscale.Panini.S 0')
    _exec_console('r.ScreenPercentage 100')


# spawn_camera_pawn — DefaultPawn + CineCameraComponent (possessable, flyable)

def spawn_camera_pawn(location=None, rotation=None,
                      preset=None,
                      focal_length=None,
                      aperture=None,
                      sensor_width=None,
                      focus_distance=None,
                      min_focal_length=None,
                      max_focal_length=None,
                      min_aperture=None,
                      max_aperture=None,
                      dof_blade_count=None,
                      possess=True,
                      max_speed=1200.0):
    """
    Spawn a DefaultPawn with a CineCameraComponent attached — possessable
    and flyable with standard WASD + mouse-look input.

    Unlike spawn_camera (which spawns a CineCameraActor that can only be a
    ViewTarget), this returns a Pawn that PlayerController.Possess() accepts.
    DefaultPawn ships with a DefaultPawnMovementComponent that provides
    noclip-style flight out of the box.

    Parameters
    ----------
    preset        : str  — one of CAMERA_PRESETS keys
    possess       : bool — auto-possess with player controller 0 after spawn
    max_speed     : float — DefaultPawnMovementComponent MaxSpeed (UE units/sec)
    (remaining lens/DOF params match spawn_camera)

    Returns
    -------
    pawn (DefaultPawn with CineCameraComponent)
    """
    world = _get_world()

    # Build config from preset + manual overrides (mirrors spawn_camera)
    cfg = dict(CAMERA_PRESETS.get('default'))
    if preset and preset in CAMERA_PRESETS:
        cfg.update(CAMERA_PRESETS[preset])
    if focal_length   is not None: cfg['focal_length']   = focal_length
    if aperture       is not None: cfg['aperture']       = aperture
    if sensor_width   is not None: cfg['sensor_width']   = sensor_width
    if focus_distance is not None: cfg['focus_distance'] = focus_distance

    try:
        from unreal_engine.classes import DefaultPawn, CineCameraComponent
    except Exception as e:
        ue.log_warning(f'spawn_camera_pawn: cannot import classes: {e}')
        return None

    try:
        pawn = world.actor_spawn(DefaultPawn)
    except Exception as e:
        ue.log_warning(f'spawn_camera_pawn: actor_spawn(DefaultPawn) failed: {e}')
        return None

    _set_transform(pawn, location, rotation, FVector(1, 1, 1))

    # Attach CineCameraComponent. When the pawn is possessed, the player
    # controller uses this component as the view (bFindCameraComponentWhenViewTarget).
    try:
        cam = pawn.add_actor_component(CineCameraComponent, 'CineCameraComponent')
        cam.CurrentFocalLength = cfg['focal_length']
        cam.CurrentAperture    = cfg['aperture']

        try:
            cam.FilmbackSettings.SensorWidth  = cfg['sensor_width']
            cam.FilmbackSettings.SensorHeight = cfg['sensor_width'] * 9.0 / 16.0
        except Exception:
            pass

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
        ue.log_warning(f'spawn_camera_pawn: attach CineCameraComponent failed: {e}')

    # Tune flight speed on the built-in movement component
    try:
        mc = pawn.get_actor_component_by_type(
            ue.find_class('DefaultPawnMovementComponent'))
        if mc is not None:
            mc.MaxSpeed = max_speed
    except Exception:
        pass

    # Possess with player controller 0 — this auto-sets view target to the pawn
    if possess:
        try:
            pc = world.get_player_controller(0)
            try: pc.UnPossess()
            except Exception: pass
            pc.Possess(pawn)
        except Exception as e:
            ue.log_warning(f'spawn_camera_pawn: Possess failed: {e}')

    return pawn


# spawn_class / spawn_blueprint

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


# spawn_earth — Cesium globe with tile overlay presets

# Ion Asset IDs for CesiumIonRasterOverlay
EARTH_PRESETS = {
    'satellite':        2,     # Bing Maps Aerial (satellite imagery)
    'satellite_labels': 3,     # Bing Maps Aerial with Labels
    'map':              4,     # Bing Maps Road (street map)
    'night':            3812,  # Earth at Night
}

def spawn_earth(location=None, rotation=None, scale=None,
                preset='satellite',
                asset_id=None,
                bp_path='/Game/Blueprints/Assets/BP_CesiumEarth'):
    """
    Spawn a BP_CesiumEarth actor and configure its raster overlay.

    Requires the Cesium for Unreal plugin and a BP_CesiumEarth blueprint
    that wraps a Cesium3DTileset with a CesiumIonRasterOverlay component.

    Parameters
    ----------
    preset    : str  — one of 'satellite', 'satellite_labels', 'map', 'night'
    asset_id  : int  — override preset with a specific Cesium Ion Asset ID
    bp_path   : str  — UE content path to BP_CesiumEarth

    Cesium Ion Asset IDs
    --------------------
    2    Bing Maps Aerial (satellite)
    3    Bing Maps Aerial with Labels
    4    Bing Maps Road (street map)
    3812 Earth at Night
    Any other public/private Cesium Ion asset ID is accepted via asset_id=.

    Returns
    -------
    actor
    """
    world = _get_world()

    resolved_id = asset_id
    if resolved_id is None:
        resolved_id = EARTH_PRESETS.get(preset)
        if resolved_id is None:
            ue.log_warning(
                f'spawn_earth: unknown preset "{preset}". '
                f'Choose from: {list(EARTH_PRESETS.keys())} or pass asset_id=.')
            return None

    try:
        bp = ue.load_object(Blueprint, bp_path)
        actor = world.actor_spawn(bp.GeneratedClass)
    except Exception as e:
        ue.log_warning(f'spawn_earth: could not load BP_CesiumEarth at "{bp_path}": {e}')
        return None

    # Set the raster overlay Ion Asset ID
    try:
        overlay = actor.get_actor_component('CesiumIonRasterOverlay')
        overlay.IonAssetID = resolved_id
        ue.log(f'spawn_earth: set CesiumIonRasterOverlay.IonAssetID = {resolved_id} '
               f'(preset="{preset}")')
    except Exception as e:
        ue.log_warning(
            f'spawn_earth: could not set IonAssetID ({e}). '
            'Make sure BP_CesiumEarth has a CesiumIonRasterOverlay component '
            'named "CesiumIonRasterOverlay".')

    _set_transform(actor, location, rotation, scale)
    return actor


# spawn_table — render an nd_table.Table as Text3D actors

def spawn_table(table, location=None, world_location=None,
                orientation='wall_table', render_gridlines=True,
                render_text=True, cell_spacing=100.0):
    """
    Render an nd_table.Table as Text3D actors in the world.

    Parameters
    ----------
    table           : nd_table.ndtable.Table
    location        : FVector | None  (world origin; alias for world_location)
    orientation     : 'wall_table' | 'ground_table'
    render_gridlines: bool
    render_text     : bool
    cell_spacing    : float  UE units between cells

    Returns
    -------
    UnrealTableRenderer instance  (holds .cell_actors, .gridline_actors)
    """
    from nd_table.unreal_integration import UnrealTableRenderer
    loc = world_location or location or FVector(0, 0, 0)
    renderer = UnrealTableRenderer(
        world=_get_world(),
        cell_spacing=cell_spacing,
        orientation_preset=orientation,
        text_mode='3d',
    )
    renderer.render_table(table, world_location=loc,
                          render_gridlines=render_gridlines,
                          render_text=render_text)
    return renderer


# spawn_table_actor — PyActor-hosted table with per-frame resize tick

def spawn_table_actor(table=None, location=None, rotation=None,
                      orientation='wall_table', cell_spacing=100.0,
                      render_gridlines=True, render_text=True,
                      enable_resize=True, name=None):
    """
    Spawn a PyActorTable that owns an UnrealTableRenderer and ticks its
    gridline-resize controller every frame — no Main.tick forwarding.

    If *table* is supplied it is rendered immediately. Otherwise call
    ``actor.get_py_proxy().set_table(t)`` once the Table is ready.

    Returns the PyActor. Access the underlying renderer via
    ``actor.get_py_proxy().renderer`` or the convenience proxies
    ``cell_actors`` / ``gridline_actors``.
    """
    actor = spawn_pyactor(
        'pyactor_table', 'PyActorTable',
        location=location, rotation=rotation,
        name=name if name else 'Table')
    if actor is None:
        return None
    try:
        proxy = actor.get_py_proxy()
        if proxy is not None:
            proxy.orientation      = orientation
            proxy.cell_spacing     = cell_spacing
            proxy.render_gridlines = render_gridlines
            proxy.render_text      = render_text
            proxy.enable_resize    = enable_resize
            if table is not None:
                proxy.set_table(table)
    except Exception as e:
        ue.log_warning(f'spawn_table_actor: configure failed: {e}')
    return actor


# spawn_nd_table — comprehensive nD table grid (2D 10x10 through 7D)

def spawn_nd_table(location=None, rotation=None, scale=None,
                   source_path=None):
    """
    Spawn the comprehensive nD table grid (2D through 7D).

    Wraps ``nd_table.examples.test_nd_table_grid``.  Mirrors spawn_icon-style
    inputs for consistency (location/rotation/scale ignored beyond
    *location* — the grid lays itself out internally; the renderer is
    returned so callers can post-transform if needed).

    Parameters
    ----------
    location    : FVector  — base location for the grid (default (0, 0, 700))
    source_path : str      — optional path attached to the renderer for
                             downstream identification.

    Returns
    -------
    UnrealTableRenderer (holds .cell_actors, .gridline_actors)
    """
    from nd_table.examples import test_nd_table_grid

    if location is None:
        location = FVector(0, 0, 700)

    renderer = test_nd_table_grid(base_location=location)

    if renderer is not None and source_path is not None:
        try:
            renderer.source_path = source_path
        except Exception:
            pass
    return renderer


# spawn_text3d — Text3D actor (BP_Cell) with arbitrary text

def spawn_text3d(text='', location=None, rotation=None, scale=None,
                 bp_path='/Game/Blueprints/Assets/BP_Cell.BP_Cell',
                 component_name='Text3DComponent',
                 source_path=None,
                 generate_overlap_events=True,
                 enable_collision=True):
    """
    Spawn a BP_Cell actor and set its Text3DComponent text.

    Mirrors the spawn_icon parameter style: payload (text) + location/rotation
    /scale + bp_path + component_name + source_path.

    Parameters
    ----------
    text                    : str  — content for Text3DComponent.Text
    bp_path                 : str  — Blueprint path (default BP_Cell)
    component_name          : str  — Text3D component to find on the actor
    source_path             : str  — optional file path attached as
                                     ``actor.source_path`` for click handlers
    generate_overlap_events : bool — enable overlap events on the Text3D
                                     component (needed for click traces)
    enable_collision        : bool — enable actor collision so the Text3D
                                     bounds can be hit-traced

    Returns
    -------
    actor or None
    """
    actor = spawn_blueprint(bp_path, location, rotation, scale)
    if actor is None:
        ue.log_warning(f'spawn_text3d: spawn_blueprint failed for "{bp_path}"')
        return None

    # Set Text3D content + collision
    try:
        t3d = actor.get_actor_component(component_name)
    except Exception as e:
        ue.log_warning(f'spawn_text3d: get_actor_component("{component_name}") failed: {e}')
        t3d = None

    if t3d is not None:
        try:
            t3d.Text = text
        except Exception as e:
            ue.log_warning(f'spawn_text3d: setting Text failed: {e}')
        if generate_overlap_events:
            try:
                t3d.SetGenerateOverlapEvents(True)
            except Exception:
                pass
            try:
                t3d.bGenerateOverlapEvents = True
            except Exception:
                pass
    else:
        ue.log_warning(
            f'spawn_text3d: no "{component_name}" component on "{bp_path}"')

    if enable_collision:
        try:
            actor.SetActorEnableCollision(True)
        except Exception:
            pass

    if source_path is not None:
        try:
            actor.source_path = source_path
        except Exception as e:
            ue.log_warning(f'spawn_text3d: could not attach source_path: {e}')

    return actor


# spawn_desktop_icons — grid of BP_Icon actors from a folder's shell icons

def spawn_desktop_icons(location=None, desktop_path=None, spacing=150,
                        max_icons=50):
    """
    Scan a folder (default: Windows Desktop) for files, extract their Windows
    shell icons via icon_to_image, and spawn a grid of BP_Icon actors.

    Parameters
    ----------
    location     : FVector  — world origin of the grid bottom-left icon
    desktop_path : str | None  — folder to scan; defaults to user Desktop
    spacing      : float  — UE units between icon centres (default 150)
    max_icons    : int    — cap on number of icons spawned

    Returns
    -------
    list of spawned icon actors
    """
    import math
    from icon_to_image import get_folder_icons

    loc    = location or FVector(0, 0, 0)
    folder = desktop_path or os.path.join(os.path.expanduser('~'), 'Desktop')

    try:
        icons = get_folder_icons(folder)   # {path: PIL Image}
    except Exception as e:
        ue.log_warning(f'spawn_desktop_icons: could not scan "{folder}": {e}')
        return []

    paths  = list(icons.items())[:max_icons]
    cols   = max(1, int(math.ceil(math.sqrt(len(paths)))))
    actors = []

    for i, (path, pil_img) in enumerate(paths):
        col = i % cols
        row = i // cols
        icon_loc = FVector(
            loc.x,
            loc.y + col * spacing,
            loc.z + row * spacing,
        )
        try:
            actor = spawn_icon(pil_img, location=icon_loc, source_path=path)
            if actor:
                actors.append(actor)
        except Exception as e:
            ue.log_warning(f'spawn_desktop_icons: spawn_icon failed for "{path}": {e}')

    ue.log(f'spawn_desktop_icons: spawned {len(actors)} icons from "{folder}"')
    return actors


# spawn_system_monitor — dynamic PyActor hosting a live sysinfo ticker

def spawn_system_monitor(location=None, rotation=None, scale=None,
                         name='SysMon'):
    """
    Spawn a system monitor PyActor with Text3DComponent.
    The Python component updates its text every 2 seconds automatically.

    Requires:
      - sysinfo.py in Scripts/
      - activity_tracker.py daemon running (optional; gracefully skipped)
    """
    actor = spawn_pyactor(
        'pyactor_sysmon', 'PyActorSysmon',
        location=location, rotation=rotation, scale=scale,
        components=[dict(class_name='Text3DComponent',
                         name='Text3DComponent', root=True)],
        name=name)
    # Set default text while waiting for first update
    try:
        t3d = find_component(actor, 'Text3DComponent')
        if t3d:
            t3d.Text = 'Loading...'
    except Exception:
        pass
    return actor


# spawn_camera_actor — dynamic PyActor hosting a CineCameraComponent

def spawn_camera_actor(location=None, rotation=None,
                       camera_type='normal', name=None):
    """
    Spawn a camera PyActor with CineCameraComponent.

    camera_type options:
      'normal'        Standard 35mm full-frame
      'cinematic'     Wide 24mm f/2.8
      'macro'         Extreme bokeh 50mm f/0.95
      'bokeh'         Portrait 85mm f/1.4
      'bokeh_tele'    Telephoto 135mm f/1.8
      'panini'        14mm + Panini projection
      'cctv'          6mm 1/3" sensor
      'anamorphic'    40mm anamorphic
      'orthographic'  Orthographic projection

    Returns the spawned actor; its Python component (PyActorCamera) handles
    lens/DOF settings automatically in begin_play.
    """
    actor = spawn_pyactor(
        'pyactor_camera', 'PyActorCamera',
        location=location, rotation=rotation,
        components=[dict(class_name='CineCameraComponent',
                         name='CineCameraComponent', root=True)],
        name=name if name else f'Camera_{camera_type}')
    if actor is None:
        return None
    try:
        actor.camera_type = camera_type
    except Exception:
        pass
    return actor


# spawn_file_explorer — dynamic PyActor hosting the FileExplorer component

def spawn_file_explorer(location=None, rotation=None,
                        initial_path=None, name=None):
    """
    Spawn a FileExplorer PyActor directly — no Blueprint placeholder required.

    The Python component (FileExplorer) calls refresh() in begin_play,
    which populates a table of files using EverythingAPI + UnrealTableRenderer.

    Requires:
      - Everything (Voidtools) running in background
      - Everything64.dll accessible
    """
    if name is None:
        if initial_path:
            leaf = os.path.basename(initial_path.rstrip('\\/')) or initial_path
            name = f'FileExplorer_{leaf}'
        else:
            name = 'FileExplorer'
    actor = spawn_pyactor(
        'pyactor_file_explorer', 'FileExplorer',
        location=location, rotation=rotation, name=name)
    if actor is None:
        return None
    if initial_path is not None:
        try:
            actor.initial_path = initial_path
        except Exception:
            pass
    return actor


# spawn_plot — dynamic PyActor hosting pyactor_plotter.PyActorPlotter

def spawn_plot(function_expr='sin(x)+cos(y)',
               plot_type='surface',
               mesh_mode='triangles',
               orientation='ground_table',
               resolution=32,
               x_range=(-3.14159, 3.14159),
               y_range=(-3.14159, 3.14159),
               z_range=(-2.0, 2.0),
               units_per_uu=100.0,
               show_grid=True,
               location=None,
               rotation=None,
               name=None):
    """
    Spawn a PyActorPlotter dynamically and render *function_expr* as a 3D plot.
    No Blueprint placeholder required — uses BP_PyActorEmpty via spawn_pyactor.

    Parameters
    ----------
    function_expr : str
        Math expression of x and y, e.g. 'sin(x)+cos(y)', 'x**2-y**2',
        'sin(sqrt(x**2+y**2))'.  Supports sin/cos/tan/sqrt/log/exp/abs/pi/e.
    plot_type : str
        'surface'   — z=f(x,y) colormap mesh  (default)
        'heatmap'   — flat coloured panel
        'contour'   — contour lines
        'wireframe' — wireframe mesh
    mesh_mode : str
        'triangles'    — per-triangle tilted Plane actors (default)
        'spheres'      — sphere at each vertex
        'sphere_lines' — spheres + cylinder edges
    orientation : str
        'ground_table' — horizontal, z rises up  (default)
        'wall_table'   — vertical panel, y down
        'wall_graph'   — vertical panel, y up
    resolution : int
        Grid samples per axis. 32 is fast; 64 is detailed.
    x_range / y_range / z_range : (float, float)
        Math-space axis limits.
    units_per_uu : float
        How many math units fit in 100 UE units (scale).
    show_grid : bool
        Draw axis grid lines.
    location / rotation : FVector / FRotator
        World transform.
    name : str
        Optional editor label. Defaults to ``Plot_<function_expr>``.

    Returns
    -------
    actor | None
    """
    # PyActorPlotter.begin_play calls render() with whatever attributes are
    # set on the instance. Attributes are best applied before the tick — so
    # we patch the proxy immediately after spawn and re-render to guarantee
    # the requested params take effect (begin_play may have already fired
    # with defaults by the time we reach here).
    actor = spawn_pyactor(
        'pyactor_plotter', 'PyActorPlotter',
        location=location, rotation=rotation,
        name=name if name else f'Plot_{function_expr}')
    if actor is None:
        return None

    try:
        proxy = actor.get_py_proxy()
        if proxy is not None:
            proxy.function_expr = function_expr
            proxy.plot_type     = plot_type
            proxy.mesh_mode     = mesh_mode
            proxy.orientation   = orientation
            proxy.resolution    = resolution
            proxy.x_range       = x_range
            proxy.y_range       = y_range
            proxy.z_range       = z_range
            proxy.units_per_uu  = units_per_uu
            proxy.show_grid     = show_grid
            proxy.render()
    except Exception as e:
        ue.log_warning(f'spawn_plot: could not configure PyActorPlotter: {e}')

    return actor


# spawn_gizmo — interactive transform gizmo (target + handles)
#
# The per-frame drag/hover tick now lives on a pyactor_gizmo.GizmoController
# PyActor, so no Main.tick forwarding is required.

def spawn_gizmo(location=None, rotation=None, scale=None,
                uobject=None, input_manager=None,
                source_path=None, name=None):
    """
    Spawn the interactive transform gizmo (target cylinder + move/rotate/
    scale/plane handles) and optionally wire up drag interaction.

    Mirrors spawn_icon-style inputs (location/rotation/scale + source_path).
    The gizmo's geometry pieces are built in code via primitives in
    ``gizmo.py``; the interaction tick is hosted by a GizmoController
    PyActor spawned via spawn_pyactor.

    Parameters
    ----------
    location      : FVector  — target spawn position (default (0, 0, 100))
    rotation      : FRotator — applied to the target after spawn
    scale         : FVector  — applied to the target after spawn
    uobject       : PyActor UObject — required for interactivity (cursor traces)
    input_manager : InputManager   — required for interactivity (LMB binds)
    source_path   : str            — optional path attached to ``target``
    name          : str            — optional editor label on the controller

    Returns
    -------
    (target_actor, handles_dict, gizmo_controller_actor_or_None)
      — the third value is the spawned GizmoController PyActor when
        uobject + input_manager were supplied, else None (static gizmo).
    """
    from gizmo import test_gizmos, _piece_off

    if location is None:
        location = FVector(0, 0, 100)

    target, gizmo_root, handles = test_gizmos(location=location)

    if rotation is not None or scale is not None:
        try:
            _set_transform(target, location, rotation, scale)
        except Exception as e:
            ue.log_warning(f'spawn_gizmo: post-spawn transform failed: {e}')

    if source_path is not None and target is not None:
        try:
            target.source_path = source_path
        except Exception as e:
            ue.log_warning(f'spawn_gizmo: could not attach source_path: {e}')

    pyactor = None
    if uobject is not None and input_manager is not None:
        try:
            pyactor = spawn_pyactor(
                'pyactor_gizmo', 'GizmoController',
                location=location,
                name=name if name else 'GizmoController')
            proxy = pyactor.get_py_proxy()
            proxy.setup(
                uobject=uobject,
                input_manager=input_manager,
                target=target,
                handles=handles,
                piece_offsets=_piece_off,
            )
        except Exception as e:
            ue.log_warning(f'spawn_gizmo: GizmoController setup failed: {e}')

    return target, handles, pyactor


# File-type detection — extended with new types

TABLE_KEYWORDS   = {'table', 'nd_table', 'ndtable'}
SYSMON_KEYWORDS  = {'sysmon', 'system_monitor', 'systemmonitor', 'monitor'}
DESKTOP_KEYWORDS = {'desktop', 'desktop_icons', 'desktopicons'}
PLOT_KEYWORDS    = {'plot', 'math_plot', 'mathplot', 'heatmap', 'surface', 'chart', 'graph'}
GIZMO_KEYWORDS   = {'gizmo', 'transform_gizmo', 'transformgizmo'}
TEXT3D_KEYWORDS  = {'text3d', 'text_3d', 'cell', 'bp_cell'}
NDTABLE_KEYWORDS = {'nd_table_grid', 'ndtablegrid', 'nd_grid'}
PYACTOR_KEYWORDS = {'pyactor', 'py_actor', 'pyactorempty'}

def spawn_icon(pil_image, location=None, rotation=None, scale=None,
               material_path='/Game/Materials/M_Icon.M_Icon',
               param_name='Texture',
               bp_path='/Game/Blueprints/Assets/BP_Icon.BP_Icon',
               component_name = 'Sphere',
               source_path=None):
    """
    Spawn a BP_Icon actor and apply *pil_image* as *param_name* texture.

    BP_Icon should have:
      • A StaticMeshComponent (sphere or any mesh)
      • A Python component pointing to pyactor_icon.IconSphere
        (hover-shrink + click-to-open handled there)

    Requires Pillow and a material at *material_path* with a
    TextureSampleParameter2D named *param_name*.

    Parameters
    ----------
    source_path : str or None
        Filesystem path the icon represents (e.g. the .exe or .png the
        PIL image was extracted from).  If provided, the path is attached
        to the spawned actor as ``actor.source_path`` so that
        ``pyactor_icon.IconSphere.on_clicked`` can open it in Chrome via
        ``cmd /c start chrome "<path>"``.
    """
    if location is None:
        location = FVector(0, 0, 0)
    if rotation is None:
        rotation = FRotator(0, 0, 0)
    if scale is None:
        scale = FVector(1, 1, 1)
    world = _get_world()

    actor = None

    # Spawn BP_Icon (hover/click/physics configured in Blueprint)
    try:
        bp = ue.load_object(Blueprint, bp_path)
        actor = world.actor_spawn(bp.GeneratedClass)
        actor.set_actor_transform(FTransform(location, rotation, scale))
        target_comp = find_component(actor, component_name)
    except Exception as e:
        ue.log_warning(f'spawn_icon: could not load BP_Icon at "{bp_path}": {e}')
        return None

    # Attach the source path to the actor.  Note: world.actor_spawn()
    # already ran BP_Icon's BeginPlay (and therefore IconSphere.begin_play)
    # synchronously, so this assignment happens AFTER begin_play has
    # finished.  That's fine — IconSphere reads source_path lazily via
    # _get_source_path() every time the user clicks, so it picks up the
    # value whenever it arrives.
    if source_path is not None:
        try:
            actor.source_path = source_path
        except Exception as e:
            ue.log_warning(f'spawn_icon: could not attach source_path: {e}')

    try:
        tex = pil_image_to_texture(pil_image)
    except Exception as e:
        ue.log_warning(f'spawn_icon: could not convert that pil_image to texture: {e}')
        return None


    if tex:
        mat = ue.load_object(Material, "/Game/Materials/M_Icon.M_Icon")
        if not mat:
            ue.log_warning(f"Material not found: {material_path}")

        mid = target_comp.create_material_instance_dynamic(mat)

        mid.set_material_texture_parameter(param_name, tex)
        target_comp.set_material(0, mid)
    else:
        ue.log_warning(f"Could not load texture for param: {param_name}")

    # tmp_path = os.path.join(tempfile.gettempdir(), 'ue_icon_tmp.png')
    # pil_image.save(tmp_path)
    #
    # texture = None
    # try:
    #     from unreal_engine.classes import TextureFactory
    #     tex_name = 'IconTex_' + str(abs(hash(tmp_path)))[:8]
    #     texture = TextureFactory().factory_import_object(
    #         tmp_path, f'/Game/IconTextures/{tex_name}')
    # except Exception as e:
    #     ue.log_warning(f'spawn_icon: texture import failed: {e}')

    # Apply material + texture via dynamic material instance
    # mat = ue.load_object(Material, material_path)
    # if mat and texture:
    #     try:
    #         smc = actor.StaticMeshComponent
    #         dmi = smc.CreateAndSetMaterialInstanceDynamic(0)
    #         dmi.SetTextureParameterValue(param_name, texture)
    #     except Exception as e:
    #         ue.log_warning(f'spawn_icon: texture param failed: {e}')
    _set_transform(actor, location, rotation, scale)
    return actor


def spawn_icon_from_path(path, location=None, rotation=None, scale=None,
                         material_path='/Game/Materials/M_Icon.M_Icon',
                         param_name='Texture',
                         bp_path='/Game/Blueprints/Assets/BP_Icon.BP_Icon',
                         component_name='Sphere',
                         source_path=None,
                         simulate_physics=True):
    """Extract the Windows shell icon from *path* and spawn a BP_Icon for it.

    Wraps ``extract_icon + spawn_icon``.  All spawn_icon-style parameters
    (material_path, param_name, bp_path, component_name) are forwarded so
    callers can swap the host Blueprint or its texture parameter.

    The spawned actor gets ``source_path`` attached (defaults to *path*) so
    pyactor_icon.IconSphere can open the file in Chrome on click.

    Parameters
    ----------
    path             : str       filesystem path (e.g. an .exe)
    simulate_physics : bool      enable physics on the *component_name*
                                 component.  Note: enabling this can break
                                 click/hover detection in some BPs.
    source_path      : str|None  override what gets attached as
                                 ``actor.source_path`` (defaults to *path*).
    """
    from icon_to_image import extract_icon
    info = extract_icon(path, preview=True, return_info=True)
    actor = spawn_icon(info["image"],
                       location=location, rotation=rotation, scale=scale,
                       material_path=material_path,
                       param_name=param_name,
                       bp_path=bp_path,
                       component_name=component_name,
                       source_path=source_path if source_path is not None else path)
    if actor and simulate_physics:
        try:
            actor.get_actor_component(component_name).SetSimulatePhysics(True)
        except Exception as e:
            ue.log_warning(
                f'spawn_icon_from_path: SetSimulatePhysics failed: {e}')
    return actor


# File-type detection

IMAGE_EXTS  = {'.png', '.jpg', '.jpeg', '.bmp', '.tga', '.tiff', '.exr',
               '.hdr', '.webp', '.ico', '.gif', '.psd'}
VIDEO_EXTS  = {'.mp4', '.avi', '.mov', '.mkv', '.wmv', '.webm', '.flv',
               '.ts', '.m4v'}
SOUND_EXTS  = {'.wav', '.mp3', '.ogg', '.flac', '.aif', '.aiff'}
OBJ_EXTS    = {'.fbx', '.obj', '.dae', '.collada', '.3ds', '.ply', '.stl',
               '.gltf', '.glb', '.blend', '.dxf', '.x3d', '.wrl', '.off'}
PRIMITIVE_NAMES  = {'cube', 'sphere', 'cylinder', 'cone', 'plane'}
CAMERA_KEYWORDS  = {'camera', 'cam', 'cine', 'cinecamera'}
CAMERA_PAWN_KEYWORDS = {'camera_pawn', 'campawn', 'flycam', 'flycamera',
                        'pawn_camera', 'possessable_camera'}
EARTH_KEYWORDS   = {'earth', 'globe', 'cesium', 'cesiumearth'}


def _detect_type(path_or_name):
    lower = path_or_name.lower()
    if lower in PRIMITIVE_NAMES:  return 'primitive'
    if lower in CAMERA_PAWN_KEYWORDS: return 'camera_pawn'
    if lower in CAMERA_KEYWORDS:  return 'camera'
    if lower in EARTH_KEYWORDS:   return 'earth'
    if lower in NDTABLE_KEYWORDS: return 'nd_table'
    if lower in TABLE_KEYWORDS:   return 'table'
    if lower in SYSMON_KEYWORDS:  return 'sysmon'
    if lower in DESKTOP_KEYWORDS: return 'desktop'
    if lower in GIZMO_KEYWORDS:   return 'gizmo'
    if lower in TEXT3D_KEYWORDS:  return 'text3d'
    if lower in PYACTOR_KEYWORDS: return 'pyactor'
    ext = os.path.splitext(lower)[1]
    if ext in IMAGE_EXTS:         return 'image'
    if ext in VIDEO_EXTS:         return 'video'
    if ext in SOUND_EXTS:         return 'sound'
    if ext in OBJ_EXTS:           return 'obj'
    if lower.startswith('/game/') or lower.startswith('/engine/'):
        return 'blueprint'
    return None


# Main spawn()

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
    panini_d=0.5,
    panini_s=0.05,
    screen_percentage=150,
    min_focal_length=None,
    max_focal_length=None,
    min_aperture=None,
    max_aperture=None,
    dof_blade_count=None,
    # Earth / Cesium options
    earth_preset='satellite',
    earth_asset_id=None,
    earth_bp_path='/Game/Blueprints/Assets/BP_CesiumEarth',
    # Table options
    table_data=None,
    orientation='wall_table',
    render_gridlines=True,
    render_text=True,
    cell_spacing=100.0,
    # Desktop icon options
    desktop_path=None,
    icon_spacing=150,
    max_icons=50,
    # Text3D / BP_Cell
    text='',
    text3d_bp_path='/Game/Blueprints/Assets/BP_Cell.BP_Cell',
    text3d_component_name='Text3DComponent',
    # PyActor
    python_module=None,
    python_class=None,
    pyactor_components=None,
    pyactor_bp_path='/Game/Blueprints/Assets/BP_PyActorEmpty.BP_PyActorEmpty',
    # Gizmo
    gizmo_uobject=None,
    gizmo_input_manager=None,
    # Common — applies to spawn_icon-style functions
    component_name=None,
    source_path=None,
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
    camera      'camera' 'cam' 'cine'       (CineCameraActor — view target only)
    camera_pawn 'camera_pawn' 'flycam'      (DefaultPawn + CineCameraComponent,
                                             possessable and flyable)
    earth       'earth' 'globe' 'cesium'  (Cesium globe via BP_CesiumEarth)
    blueprint   '/Game/…' UE content path
    class       pass uclass= parameter

    Camera presets (camera_preset=)
    --------------------------------
    'default'         35mm f/5.6 full-frame
    'cinematic'       24mm f/2.8
    'bokeh_portrait'  85mm f/1.4  — shallow DOF subject isolation
    'bokeh_telephoto' 135mm f/1.8 — compressed background blur
    'bokeh_macro'     50mm f/0.95 — extreme bokeh
    'panini'          14mm + Panini ON (D=0.5, S=0.05, ScreenPercentage=150)
    'cctv'            6mm 1/3" sensor
    'anamorphic'      40mm f/2.0 anamorphic sensor

    Earth presets (earth_preset=)
    ------------------------------
    'satellite'        Ion ID 2  — Bing Maps Aerial
    'satellite_labels' Ion ID 3  — Bing Maps Aerial with Labels
    'map'              Ion ID 4  — Bing Maps Road
    'night'            Ion ID 3812 — Earth at Night

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
            'Supported: image, video, sound, obj, primitive, camera, earth, '
            'table, sysmon, desktop, class, blueprint.'
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
            panini_s=panini_s,
            screen_percentage=screen_percentage,
            min_focal_length=min_focal_length,
            max_focal_length=max_focal_length,
            min_aperture=min_aperture,
            max_aperture=max_aperture,
            dof_blade_count=dof_blade_count,
        )

    elif detected == 'camera_pawn':
        return spawn_camera_pawn(
            location=location, rotation=rotation,
            preset=camera_preset,
            focal_length=focal_length,
            aperture=aperture,
            sensor_width=sensor_width,
            focus_distance=focus_distance,
            min_focal_length=min_focal_length,
            max_focal_length=max_focal_length,
            min_aperture=min_aperture,
            max_aperture=max_aperture,
            dof_blade_count=dof_blade_count,
        )

    elif detected == 'earth':
        return spawn_earth(
            location=location, rotation=rotation, scale=scale,
            preset=earth_preset,
            asset_id=earth_asset_id,
            bp_path=earth_bp_path,
        )

    elif detected == 'table':
        if table_data is None:
            ue.log_warning('spawn: type="table" requires table_data= parameter.')
            return None
        return spawn_table(table_data, location=location,
                           orientation=orientation,
                           render_gridlines=render_gridlines,
                           render_text=render_text,
                           cell_spacing=cell_spacing)

    elif detected == 'sysmon':
        return spawn_system_monitor(location, rotation, scale)

    elif detected == 'desktop':
        return spawn_desktop_icons(location, desktop_path=desktop_path,
                                   spacing=icon_spacing, max_icons=max_icons)

    elif detected == 'class':
        if uclass is None:
            ue.log_warning('spawn: type="class" requires uclass= parameter.')
            return None
        return spawn_class(uclass, location, rotation, scale)

    elif detected == 'blueprint':
        return spawn_blueprint(path_or_type, location, rotation, scale)

    elif detected == 'gizmo':
        return spawn_gizmo(location=location, rotation=rotation, scale=scale,
                           uobject=gizmo_uobject,
                           input_manager=gizmo_input_manager,
                           source_path=source_path)

    elif detected == 'text3d':
        return spawn_text3d(text=text,
                            location=location, rotation=rotation, scale=scale,
                            bp_path=text3d_bp_path,
                            component_name=component_name or text3d_component_name,
                            source_path=source_path)

    elif detected == 'pyactor':
        if python_module is None or python_class is None:
            ue.log_warning(
                'spawn: type="pyactor" requires python_module= and python_class= parameters.')
            return None
        return spawn_pyactor(python_module, python_class,
                             location=location, rotation=rotation, scale=scale,
                             components=pyactor_components,
                             bp_path=pyactor_bp_path,
                             source_path=source_path)

    elif detected == 'nd_table':
        return spawn_nd_table(location=location, rotation=rotation, scale=scale,
                              source_path=source_path)

    else:
        ue.log_warning(f'spawn: unknown type "{detected}".')
        return None


# Usage examples
#
# from ue_spawn import spawn, spawn_icon, spawn_earth, disable_panini
# from ue_spawn import CAMERA_PRESETS, EARTH_PRESETS
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
# # Video (MOV → auto-converted to MP4 via ffmpeg)
# actor, player, tex = spawn('C:/videos/intro.mov', location=FVector(0, 200, 100))
#
# # 3-D mesh (GLB → auto-converted to FBX via trimesh)
# mesh = spawn('C:/models/chair.glb', location=FVector(0, 0, 0))
#
# # 3-D mesh (Blender file → Blender CLI conversion)
# mesh = spawn('C:/models/scene.blend', location=FVector(100, 0, 0))
#
# # Sound (immediate playback)
# spawn('/Game/Sounds/Explosion', type='sound', location=FVector(0, 0, 0))
#
# # Sound (clickable sphere actor)
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
# # Camera — Panini projection (D=0.5, S=0.05, ScreenPercentage=150)
# cam = spawn('camera', camera_preset='panini', location=FVector(0, 0, 100))
# ue.get_player_controller(0).SetViewTarget(cam)  # activate Panini
#
# # Camera — Panini with custom values
# cam = spawn('camera', panini=True, panini_d=0.5, panini_s=0.0,
#             screen_percentage=100, location=FVector(0, 0, 100))
#
# # Disable Panini
# disable_panini()
#
# # Camera — standard (non-cine) actor
# cam = spawn('camera', camera_type='standard', location=FVector(-200, 0, 150))
#
# # Earth — satellite imagery (default)
# earth = spawn('earth', location=FVector(0, 0, 0))
#
# # Earth — night preset
# earth = spawn('earth', earth_preset='night')
#
# # Earth — explicit Cesium Ion asset ID
# earth = spawn('earth', earth_asset_id=2)
#
# # Earth — via spawn_earth directly with preset string
# earth = spawn_earth(preset='satellite_labels', location=FVector(0, 0, 0))
#
# # Blueprint
# bp_actor = spawn('/Game/Blueprints/BP_Cell', location=FVector(300, 0, 0))
#
# # Icon (BP_Icon + PIL image, hover effect from BP's Python component)
# from PIL import Image
# img = Image.open('icon.png')
# icon_actor = spawn_icon(img, location=FVector(0, 0, 200))
#
# # Print available presets
# print('Camera presets:', list(CAMERA_PRESETS.keys()))
# print('Earth presets: ', list(EARTH_PRESETS.keys()))
