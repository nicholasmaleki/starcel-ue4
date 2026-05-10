"""
test_spawn.py — Spawn test suite for Starcel9
==============================================
Modeled after test_gizmos() in gizmo.py.

All actors are placed at X=0, spread along the Y axis.  test_spawn_all()
walks the chosen tests in order and gives each one a base_y allocated
sequentially from a running cursor (starting at Y=0), using the per-test
span registered in ``_TEST_Y_SPAN``.  Each test_* function accepts a
``base_y`` kwarg and lays its own actors out within that band.

This means a subset like ``tests=['cameras','earth']`` is packed at the
origin instead of being pushed to the cameras' old fixed Y=2200, and
no two tests ever share a Y band regardless of which subset you pick.

Default Y spans (full-suite layout — see ``_TEST_Y_SPAN``):
  primitives     1500  (5 shapes, stride 200)
  image          1000  (valid + invalid path)
  video          1000
  sound           800
  cameras        4500  (8 presets, stride 500)
  earth          1500  (2 presets, stride 500)
  system_monitor 2800  (multi-line Text3D, long stat lines extend +Y)
  table          1800  (basic + formulas, formulas offset on X)
  desktop_icons  1500
  desktop_icons_cylinder 1000  (D=600, H=1500 cylinder cloud, 20 icons)
  icon            800
  exe_icon        800
  nd_table       4000  (2D 10x10 through 7D)
  plot           2700  (4 plots, stride 600, half-width offset 260)
  file_explorer  3500  (21 rows × 120 cell_spacing)
  3d             2000  (drag row/col/slice gridlines)
  3d_object       800  (Duck.glb → GLTFImporter plugin → spawn StaticMeshActor)
  glb_object_runtime 800 (Duck.glb → glTFRuntime plugin → AglTFRuntimeAssetActor)
  text3d_pyactor 1000  (BP_PyActorEmpty + BP_Cell child via spawn_text3d_pyactor)
  text3d_executor 1000 (Ctrl+Enter exec()s the text via spawn_text3d_executor)
  gizmo           800  (interactive — only with uobject+input_manager)
  text3d_click   1500  (interactive — only with uobject+input_manager)

Usage (PIE Python console):
    from test_spawn import test_spawn_all
    results = test_spawn_all()

    # Manual Text3D click investigation:
    from test_spawn import test_text3d_click
    test_text3d_click()

    # Interactive transform gizmo (needs uobject + input_manager):
    from test_spawn import test_gizmo
    target, handles, tick = test_gizmo(uobject, input_manager)

Per-test elapsed time is emitted to the UE Output Log and returned on each
result entry as ``results[name]['elapsed']``.

Prerequisites summary printed to log at start of test_spawn_all().
"""

import os
import sys
import time
import traceback
import unreal_engine as ue
from unreal_engine import FVector, FRotator
from unreal_engine.enums import ECollisionChannel
from unreal_engine_tools import get_world

# Logging — mirrors gizmo.py crash log pattern
# The log is designed to be copy-pasted back to Claude for diagnosis.
# Each test emits:
#   - section banner + start timestamp
#   - inputs used (paths, locations, parameters)
#   - spawned actor introspection (class, name, location, mobility, mesh, material, components)
#   - full Python traceback on any failure
#   - PASS/FAIL line + per-test elapsed time
# Final summary: env info, per-test table, total pass/fail counts.

DESKTOP = os.path.join(os.path.expanduser('~'), 'Desktop')


def _log(msg):
    ue.log(msg)


def _section(title):
    """Emit a clear visual section delimiter in the log."""
    _log('')
    _log('-' * 70)
    _log(f'  {title}')
    _log('-' * 70)


def _log_exception(label, exc):
    """Log a full traceback, not just the exception message.
    Without this, root causes (wrong arg type, missing asset path, UE crash)
    are invisible and Claude can't diagnose failures from the log."""
    _log(f'  {label} EXCEPTION: {type(exc).__name__}: {exc}')
    try:
        tb = traceback.format_exc()
        for line in tb.rstrip().splitlines():
            _log(f'    {line}')
    except Exception:
        pass


def _describe_actor(actor):
    """Return a one-line summary of a spawned actor's observable state.
    Used to tell apart 'returned None' / 'returned wrong class' /
    'spawned but at wrong location' / 'spawned but mesh never assigned'."""
    if actor is None:
        return 'None'
    parts = []
    try:
        parts.append(f'cls={type(actor).__name__}')
    except Exception:
        pass
    try:
        parts.append(f'name={actor.get_name()}')
    except Exception:
        pass
    try:
        parts.append(f'class_path={actor.get_class().get_name()}')
    except Exception:
        pass
    try:
        loc = actor.get_actor_location()
        parts.append(f'loc=({loc.x:.0f},{loc.y:.0f},{loc.z:.0f})')
    except Exception:
        pass
    try:
        s = actor.get_actor_scale()
        parts.append(f'scale=({s.x:.3f},{s.y:.3f},{s.z:.3f})')
    except Exception:
        pass
    try:
        root = actor.RootComponent
        if root is not None:
            try:
                mob = int(root.Mobility)
                parts.append(f'mobility={["Static","Stationary","Movable"][mob]}')
            except Exception:
                pass
    except Exception:
        pass
    # StaticMeshActor-specific introspection — huge tell for spawn issues
    try:
        smc = getattr(actor, 'StaticMeshComponent', None)
        if smc is not None:
            try:
                mesh = smc.StaticMesh
                parts.append(f'mesh={mesh.get_name() if mesh else "None"}')
            except Exception:
                pass
            try:
                mats = smc.GetMaterials() if hasattr(smc, 'GetMaterials') else None
                if mats is not None:
                    parts.append(f'mats={len(mats)}')
            except Exception:
                pass
    except Exception:
        pass
    try:
        comps = actor.get_actor_components()
        parts.append(f'comps={len(comps)}')
    except Exception:
        pass
    try:
        parts.append(f'pending_kill={bool(actor.is_pending_kill())}')
    except Exception:
        pass
    return ' '.join(parts)


def _result(name, actor_or_value, extra='', expected=None, inputs=None,
            elapsed=None):
    """Log a test outcome with rich context:
      - inputs   : what params/paths were passed in
      - expected : what a passing result should look like
      - actor    : full introspection of the returned actor (class/loc/mesh/etc.)
      - elapsed  : seconds the spawn call took (logged + stored on result dict)
      - status   : PASS/FAIL line
    """
    ok = actor_or_value is not None
    status = 'PASS' if ok else 'FAIL'
    if inputs is not None:
        _log(f'  inputs:   {inputs}')
    if expected is not None:
        _log(f'  expected: {expected}')
    if actor_or_value is not None:
        try:
            _log(f'  actor:    {_describe_actor(actor_or_value)}')
        except Exception as e:
            _log(f'  actor:    <introspection failed: {e}>')
    else:
        _log('  actor:    None  (spawner returned nothing)')
    if elapsed is not None:
        _log(f'  elapsed:  {elapsed:.3f}s')
    suffix = f' — {extra}' if extra else ''
    _log(f'[{status}] {name}{suffix}')
    return {name: {'ok': ok, 'actor': actor_or_value, 'elapsed': elapsed}}


def _skip(name, reason=''):
    _log(f'  skip_reason: {reason}' if reason else '  skip_reason: (unspecified)')
    _log(f'[SKIP] {name}{(" — " + reason) if reason else ""}')
    return {name: {'ok': True, 'actor': None, 'elapsed': None}}   # skips are non-failing


def _log_env():
    """Dump environment info so version/path issues are obvious in the log."""
    _log('=== Environment ===')
    _log(f'  Time:       {time.strftime("%Y-%m-%d %H:%M:%S")}')
    try:
        _log(f'  Python:     {sys.version.split()[0]}  ({sys.executable})')
    except Exception:
        pass
    try:
        _log(f'  Platform:   {sys.platform}')
    except Exception:
        pass
    try:
        _log(f'  CWD:        {os.getcwd()}')
    except Exception:
        pass
    try:
        _log(f'  Scripts:    {os.path.dirname(__file__)}')
    except Exception:
        pass
    try:
        eng_ver = ue.get_engine_version() if hasattr(ue, 'get_engine_version') else None
        _log(f'  UE version: {eng_ver}')
    except Exception as e:
        _log(f'  UE version: <err: {e}>')
    try:
        w = get_world()
        _log(f'  World:      {w.get_name() if w else "None"}')
        if w is not None:
            try:
                actors = w.all_actors()
                _log(f'  Actors in world at start: {len(actors)}')
            except Exception:
                pass
    except Exception as e:
        _log(f'  World:      <err: {e}>')


# Prerequisites check — printed at top of test_spawn_all()

def _check_prerequisites():
    """
    Check which assets / plugins / tools are available and log the status.
    Nothing is blocked — this is informational only so you know what to set up.
    """
    _log('')
    _log('=== Prerequisites ===')

    checks = [
        # (label, check_fn, setup_note)
        ('Material M_VideoTexture_Video',
         lambda: bool(ue.load_object(ue.find_class('Material'),
                                     '/Game/Movies/M_VideoTexture_Video')),
         'Material already exists at /Game/Movies/M_VideoTexture_Video'),

        ('Material M_Icon',
         lambda: bool(ue.load_object(ue.find_class('Material'),
                                     '/Game/Materials/M_Icon')),
         'Create a material at /Game/Materials/M_Icon with a '
         'TextureSampleParameter2D named "Texture"'),

        ('Blueprint BP_Cell',
         lambda: bool(ue.load_object(ue.find_class('Blueprint'),
                                     '/Game/Blueprints/Assets/BP_Cell')),
         'Requires Text3D plugin + BP_Cell Blueprint with Text3DComponent'),

        # BP_Icon, BP_SoundSphere, BP_SysMon, BP_PyCamera now use dynamic
        # PyActor spawning — no Blueprint needed.

        ('Blueprint BP_CesiumEarth',
         lambda: bool(ue.load_object(ue.find_class('Blueprint'),
                                     '/Game/Blueprints/Assets/BP_CesiumEarth')),
         'Requires Cesium for Unreal plugin + BP_CesiumEarth Blueprint'),

        ('Plugin glTFRuntime',
         lambda: ue.find_class('glTFRuntimeAssetActor') is not None,
         'Enable glTFRuntime in Starcel9.uproject and rebuild — '
         'test_glb_object_runtime needs it'),

        ('EverythingAPI DLL',
         lambda: _check_everything_dll(),
         'Install Everything (Voidtools), run it, ensure Everything64.dll '
         'is in Scripts/ or on PATH'),

        ('PIL / Pillow',
         lambda: __import__('PIL') is not None,
         'pip install Pillow'),

        ('ffmpeg on PATH',
         lambda: _check_ffmpeg(),
         'Install ffmpeg and add to system PATH (for video conversion)'),
    ]

    needs_setup = []
    for label, check_fn, note in checks:
        try:
            ok = check_fn()
        except Exception:
            ok = False
        status = 'OK  ' if ok else 'MISSING'
        _log(f'  [{status}] {label}')
        if not ok:
            needs_setup.append((label, note))

    if needs_setup:
        _log('')
        _log('--- Setup needed for failing tests ---')
        for label, note in needs_setup:
            _log(f'  {label}:')
            _log(f'    {note}')
    else:
        _log('  All prerequisites met.')
    _log('')


def _check_everything_dll():
    candidates = [
        'Everything64.dll',
        os.path.join(os.path.dirname(__file__), 'Everything64.dll'),
        r'C:\Program Files\Everything\Everything64.dll',
        r'C:\Program Files (x86)\Everything\Everything64.dll',
    ]
    import ctypes
    for path in candidates:
        try:
            ctypes.WinDLL(path)
            return True
        except Exception:
            continue
    return False


def _check_ffmpeg():
    import subprocess
    try:
        subprocess.run(['ffmpeg', '-version'],
                       capture_output=True, timeout=5,
                       creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0))
        return True
    except Exception:
        return False


# Individual test functions

# Each function returns a dict { test_name: {'ok': bool, 'actor': ...} }
# Actors are kept in the returned dict so Python holds references (prevent GC).

# Per-test Y-span registry (UU along Y).  test_spawn_all() walks this list
# in order and assigns each chosen test a base_y = (running cursor), so a
# subset like tests=['cameras','earth'] is packed sequentially from Y=0
# rather than leaving big gaps.  Each test_* function takes a base_y kwarg
# and lays its own actors out within that band.
#
# Spans are sized with a buffer so even when adjacent tests have content
# that auto-sizes wider than expected (e.g. file_explorer's Name column
# holding long file paths) they don't bleed into the next band.
_TEST_Y_SPAN = {
    'test_primitives':     1500,   # 5 shapes × 200 stride (0..800) + ~100 actor + buffer
    'test_image':          1000,   # 2 spawns at 0 and +400 (image planes are Y-thin)
    'test_video':          1000,   # 1 spawn at +400
    'test_sound':           800,   # 2 spheres at 0 and +200
    'test_cameras':        4500,   # 8 presets × 500 (0..3500) + drone mesh + buffer
    'test_earth':          1500,   # 2 presets × 500 (earths scaled to ~1 UU)
    'test_system_monitor': 2800,   # multi-line Text3D — long stat lines extend far +Y
    'test_table':          1800,   # basic 3-row at 0 + formula 8-row at +400 (~1200 actual)
    'test_desktop_icons':  1500,   # 3-col grid × 150 spacing (~450 actual)
    'test_desktop_icons_cylinder': 1000,  # D=600 cylinder centered at base_y+350 → Y in [+50,+650]
    'test_icon':            800,   # single sphere
    'test_exe_icon':        800,   # single sphere
    'test_nd_table':       4000,   # 2D..6D grid extends to base_y + ~3000 UU
    'test_plot':           2700,   # 4 plots × 600 stride (each plot ~502 UU wide)
    'test_file_explorer':  3500,   # 21 rows × 120 cell_spacing = 2520 actual
    'test_3d_table_resize': 2000,  # 3x3x3 cells (~300) + axis labels can extend past 1000
    'test_3d_object':       800,   # single GLB-loaded duck mesh
    'test_glb_object_runtime': 800, # same Duck.glb via glTFRuntime (runtime parse)
    'test_text3d_pyactor': 1000,   # one BP_Cell text actor (~500 wide) + buffer
    'test_text3d_executor':1000,   # one BP_Cell text actor (~500 wide) + buffer
    'test_gizmo':           800,   # cylinder + handles ±200 from center
    'test_text3d_click':    600,   # one BP_Cell text actor (~500 wide) + buffer
}

_GOOGLE_DRIVE_EXE = r"C:\Users\nicho\Downloads\GoogleDriveSetup.exe"
_BIG_BAD_JOHN_FLAC = r"C:\Users\nicho\Downloads\Big Bad John\Big Bad John.flac"
_DUCK_GLB = os.path.join(
    os.path.abspath(ue.get_content_dir()), 'Models', 'Duck.glb')


def _find_test_image():
    """Find any image for test sizing — Feedback Hub screenshot, Desktop PNG, or generate one."""
    fb_root = os.path.expandvars(
        r'%LOCALAPPDATA%\Packages\Microsoft.WindowsFeedbackHub_8wekyb3d8bbwe'
        r'\LocalState')
    if os.path.isdir(fb_root):
        try:
            for sub in os.listdir(fb_root):
                cand = os.path.join(fb_root, sub, 'Capture0.png')
                if os.path.exists(cand):
                    return cand
        except Exception:
            pass
    try:
        for f in os.listdir(DESKTOP):
            if f.lower().endswith('.png') and not f.startswith('_test_spawn'):
                return os.path.join(DESKTOP, f)
    except Exception:
        pass
    # Generate a small test image
    try:
        from PIL import Image as PILImage
        path = os.path.join(DESKTOP, '_test_spawn_video.png')
        PILImage.new('RGB', (320, 180), color=(30, 30, 30)).save(path)
        return path
    except Exception:
        return None


def test_primitives(base_y=0):
    """Spawn all 5 primitive shapes along Y, starting at *base_y*."""
    from ue_spawn import spawn_primitive
    results = {}
    shapes = ['cube', 'sphere', 'cylinder', 'cone', 'plane']
    for i, shape in enumerate(shapes):
        loc = FVector(0, base_y + i * 200, 100)
        actor = None
        t0 = time.monotonic()
        try:
            actor = spawn_primitive(shape, location=loc)
        except Exception as e:
            _log_exception(f'primitive_{shape}', e)
        elapsed = time.monotonic() - t0
        results.update(_result(f'primitive_{shape}', actor, elapsed=elapsed))
    return results


def test_image(base_y=0):
    """
    Spawn from a test image and verify cube matches image pixel dimensions.
    Lays out two spawns at base_y and base_y+400 along Y.

    Priority order for the test image:
      1. User-specified Feedback Hub screenshot
         (C:\\Users\\...\\WindowsFeedbackHub\\LocalState\\{...}\\Capture0.png)
      2. Any PNG on the Desktop
      3. Freshly created 320×180 (16:9) PIL image so the non-uniform
         scale is visually obvious.
    """
    from ue_spawn import spawn_image
    results = {}

    # 1. find an image path
    img_path = None

    # (a) User-specified Feedback Hub screenshot
    fb_root = os.path.expandvars(
        r'%LOCALAPPDATA%\Packages\Microsoft.WindowsFeedbackHub_8wekyb3d8bbwe'
        r'\LocalState')
    if os.path.isdir(fb_root):
        try:
            for sub in os.listdir(fb_root):
                cand = os.path.join(fb_root, sub, 'Capture0.png')
                if os.path.exists(cand):
                    img_path = cand
                    _log(f'  image_valid: using Feedback Hub screenshot {cand}')
                    break
        except Exception:
            pass

    # (b) Any PNG on the Desktop
    if img_path is None:
        try:
            for f in os.listdir(DESKTOP):
                if f.lower().endswith('.png') and not f.startswith('_test_spawn'):
                    img_path = os.path.join(DESKTOP, f)
                    _log(f'  image_valid: using Desktop PNG {img_path}')
                    break
        except Exception:
            pass

    # (c) Generate a 320x180 (16:9) test image so the rectangle shape is
    #     obvious if the scaling works.
    if img_path is None:
        img_path = os.path.join(DESKTOP, '_test_spawn_img.png')
        try:
            from PIL import Image as PILImage, ImageDraw
            img = PILImage.new('RGB', (320, 180), color=(30, 30, 30))
            d = ImageDraw.Draw(img)
            # red border so we can see the aspect ratio instantly in-world
            d.rectangle([0, 0, 319, 179],      outline=(255, 0, 0), width=6)
            d.rectangle([20, 20, 299, 159],    outline=(0, 255, 0), width=3)
            d.line([(0, 0), (319, 179)],       fill=(0, 180, 255), width=2)
            d.line([(0, 179), (319, 0)],       fill=(0, 180, 255), width=2)
            img.save(img_path)
            _log(f'  image_valid: generated 320x180 test image {img_path}')
        except Exception as e:
            results.update(_skip('image_valid', f'PIL unavailable: {e}'))
            img_path = None

    # 2. log expected cube dimensions
    if img_path and os.path.exists(img_path):
        try:
            from PIL import Image as PILImage
            with PILImage.open(img_path) as probe:
                pw, ph = probe.width, probe.height
            # spawn_image default scale: FVector(w/100, 0.05, h/100)
            # cube is 100 UU per side, so final size = (w, 5, h) UU
            _log(f'  image_valid: src pixels = {pw}×{ph}  '
                 f'→ expected world = {pw}×5×{ph} UU  '
                 f'(scale={pw/100:.2f}, 0.05, {ph/100:.2f})')
        except Exception as e:
            _log(f'  image_valid: could not probe size: {e}')

        actor = None
        t0 = time.monotonic()
        try:
            actor = spawn_image(img_path, location=FVector(0, base_y, 100))
            if actor is not None:
                # Verify the scale UE actually applied
                try:
                    s = actor.get_actor_scale()
                    _log(f'  image_valid: actor scale = '
                         f'({s.x:.3f}, {s.y:.3f}, {s.z:.3f})')
                except Exception as e:
                    _log(f'  image_valid: could not read actor scale: {e}')
        except Exception as e:
            _log_exception('image_valid', e)
        results.update(_result('image_valid', actor,
                               elapsed=time.monotonic() - t0))

    # 3. invalid path — None is the correct result
    bad = None
    t0 = time.monotonic()
    try:
        bad = spawn_image('C:/nonexistent_path/bad.png',
                          location=FVector(0, base_y + 400, 100))
    except Exception:
        pass
    elapsed = time.monotonic() - t0
    results['image_invalid_path'] = {'ok': bad is None, 'actor': bad,
                                     'elapsed': elapsed}
    _log(f'  elapsed: {elapsed:.3f}s')
    _log(f'[{"PASS" if bad is None else "FAIL"}] image_invalid_path')
    return results


def test_video(base_y=0):
    """
    Spawn the loading_screen.mp4 as a vertical picture-frame video plane
    using MP_VideoTexture_Video_Mat, plus run the legacy Desktop-MP4 scan.
    """
    from ue_spawn import spawn_video
    results = {}

    # video cube: plays loading_screen.mp4 via MediaPlayer
    loading_mp4 = (r'C:\Users\nicho\Documents\Unreal Projects\Starcel9\Content\Movies\loading_screen.mp4')
    if os.path.exists(loading_mp4):
        actor = None
        t0 = time.monotonic()
        try:
            actor = spawn_video(
                loading_mp4,
                location=FVector(0, base_y + 400, 100),
            )
        except Exception as e:
            _log_exception('video_cube', e)
        results.update(_result('video_cube', actor,
                               extra='cube playing loading_screen.mp4',
                               elapsed=time.monotonic() - t0))
    else:
        results.update(_skip('video_cube', f'not found: {loading_mp4}'))

    return results


def test_sound(base_y=0):
    """Exercise ue_spawn.spawn_sound with a filesystem audio file, in both
    world-playback and actor-hosted modes."""
    from ue_spawn import spawn_sound
    results = {}

    if os.path.isfile(_BIG_BAD_JOHN_FLAC):
        sw = None
        t0 = time.monotonic()
        try:
            sw = spawn_sound(_BIG_BAD_JOHN_FLAC,
                             location=FVector(0, base_y, 100))
        except Exception as e:
            _log_exception('sound_file_flac', e)
        results.update(_result('sound_file_flac', sw,
                               inputs={'path': _BIG_BAD_JOHN_FLAC},
                               extra='decoded via ffmpeg -> SoundWaveProcedural',
                               elapsed=time.monotonic() - t0))

        actor = None
        t0 = time.monotonic()
        try:
            actor = spawn_sound(_BIG_BAD_JOHN_FLAC,
                                location=FVector(0, base_y + 200, 100),
                                as_actor=True)
        except Exception as e:
            _log_exception('sound_file_flac_as_actor', e)
        results.update(_result('sound_file_flac_as_actor', actor,
                               inputs={'path': _BIG_BAD_JOHN_FLAC,
                                       'as_actor': True},
                               extra='click sphere to play (SoundSphere host)',
                               elapsed=time.monotonic() - t0))
    else:
        results.update(_skip('sound_file_flac',
                             f'not found: {_BIG_BAD_JOHN_FLAC}'))
        results.update(_skip('sound_file_flac_as_actor',
                             f'not found: {_BIG_BAD_JOHN_FLAC}'))
    return results


def test_cameras(base_y=0):
    """Spawn each camera preset along Y. Click the proxy cube to possess."""
    from ue_spawn import spawn_camera_actor, CAMERA_PRESETS
    results = {}
    for i, preset_name in enumerate(CAMERA_PRESETS):
        loc = FVector(0, base_y + i * 500, 300)
        actor = None
        t0 = time.monotonic()
        try:
            actor = spawn_camera_actor(location=loc, camera_type=preset_name)
        except Exception as e:
            _log_exception(f'camera_{preset_name}', e)
        results.update(_result(f'camera_{preset_name}', actor,
                               elapsed=time.monotonic() - t0))
    return results


def test_earth(base_y=0):
    """Spawn Cesium Earth with satellite and night presets."""
    from ue_spawn import spawn_earth
    results = {}
    for i, preset in enumerate(['satellite', 'night']):
        loc = FVector(0, base_y + i * 500, 0)
        actor = None
        t0 = time.monotonic()
        try:
            actor = spawn_earth(location=loc, preset=preset,
                                scale=FVector(0.00001, 0.00001, 0.00001))
        except Exception as e:
            _log_exception(f'earth_{preset}', e)
        results.update(_result(f'earth_{preset}', actor,
                               elapsed=time.monotonic() - t0))
    return results


def test_system_monitor(base_y=0):
    """Spawn a PyActorSysmon dynamically (no Blueprint placeholder).

    Spawned at Z=2500 because the Text3D component renders multi-line stats
    output, with each new line stepping down in -Z; lower spawn heights
    left most rows near the floor or occluded by other test geometry.
    """
    from ue_spawn import spawn_system_monitor
    actor = None
    t0 = time.monotonic()
    try:
        actor = spawn_system_monitor(location=FVector(0, base_y, 2500))
    except Exception as e:
        _log_exception('system_monitor', e)
    return _result('system_monitor', actor, elapsed=time.monotonic() - t0)


def test_table(base_y=0):
    """Spawn two nd_tables: a basic 3×4 file listing and an advanced formula
    spreadsheet that exercises in-cell Python, spreadsheet labels (A–C, AA, AB),
    named cells, and cross-cell dependencies."""
    from ue_spawn import spawn_table
    results = {}

    # Basic table (unchanged)
    renderer = None
    t0 = time.monotonic()
    try:
        from nd_table.ndtable import Table
        t = Table(shape=(3, 4))
        t[(0, 0)] = 'Name';    t[(0, 1)] = 'Size';    t[(0, 2)] = 'Date';    t[(0, 3)] = 'Type'
        t[(1, 0)] = 'file.py'; t[(1, 1)] = '10 KB';   t[(1, 2)] = '2024-01'; t[(1, 3)] = '.py'
        t[(2, 0)] = 'readme';  t[(2, 1)] = '1 KB';    t[(2, 2)] = '2024-01'; t[(2, 3)] = '.md'
        renderer = spawn_table(t, location=FVector(0, base_y, 500))
    except Exception as e:
        _log_exception('table', e)
    n_cells = len(renderer.cell_actors) if renderer and hasattr(renderer, 'cell_actors') else 0
    results.update(_result('table', renderer, extra=f'{n_cells} cells',
                           elapsed=time.monotonic() - t0))

    # Advanced formula spreadsheet
    #  Uses spreadsheet labels A–C and extended AA, AB.
    #  Row 0: headers
    #  Rows 1-5: numeric data + formulas referencing other cells
    adv_renderer = None
    t0 = time.monotonic()
    try:
        from nd_table.ndtable import Table
        adv = Table(shape=(8, 28), lazy_eval=True)  # 8 rows, 28 cols (A..AB)

        # Headers in row 0
        adv['A1'] = 'Item'
        adv['B1'] = 'Qty'
        adv['C1'] = 'Price'
        # Column D = total per row (Qty * Price)
        adv[(0, 3)] = 'Total'
        # Column E = running sum
        adv[(0, 4)] = 'RunSum'
        # Extended label columns
        adv[(0, 26)] = 'AA:Sum'     # col 26 = AA
        adv[(0, 27)] = 'AB:Avg'     # col 27 = AB

        # Data rows  (A=0, B=1, C=2)
        items = [
            ('Widget',   5,  12.50),
            ('Gadget',   3,  27.00),
            ('Bracket', 10,   4.75),
            ('Washer',  50,   0.30),
            ('Bolt',    20,   1.10),
        ]
        for i, (name, qty, price) in enumerate(items, start=2):
            row = i - 1   # row index (0-based)
            adv[(row, 0)] = name
            adv[(row, 1)] = qty
            adv[(row, 2)] = price
            # D = Qty * Price  (formula using spreadsheet labels)
            adv[(row, 3)] = f'=B{i} * C{i}'

        # Running sum in column E  (cumulative formula chain)
        adv[(1, 4)] = '=D2'
        for i in range(3, 7):
            adv[(i - 1, 4)] = f'=E{i - 1} + D{i}'

        # Named cell for grand total
        try:
            adv.name_cell('E6', 'grand_total')
        except Exception:
            pass

        # AA column (col 26): sum of all totals via formula
        adv[(1, 26)] = '=D2 + D3 + D4 + D5 + D6'
        # AB column (col 27): average using Python math in formula
        adv[(1, 27)] = '=(D2 + D3 + D4 + D5 + D6) / 5'

        # Row 7: summary using math functions (use builtins explicitly)
        adv[(6, 0)] = 'sqrt(sum)'
        adv[(6, 3)] = '=math.sqrt(D2 + D3 + D4 + D5 + D6)'
        adv[(6, 4)] = '=max(D2, D3, D4, D5, D6)'

        # Force evaluation to verify formulas work
        formula_ok = True
        try:
            val_d2 = adv['D2']  # should be 5 * 12.50 = 62.50
            val_aa = adv[(1, 26)]  # sum
            val_ab = adv[(1, 27)]  # average
            _log(f'  adv_table formulas: D2={val_d2}, AA2={val_aa}, AB2={val_ab}')
        except Exception as e:
            _log(f'  adv_table formula eval failed: {e}')
            formula_ok = False

        adv_renderer = spawn_table(
            adv, location=FVector(500, base_y + 400, 500))
        if formula_ok:
            _log(f'  adv_table: formulas evaluated successfully')
    except Exception as e:
        _log_exception('adv_table', e)

    n_adv = len(adv_renderer.cell_actors) if adv_renderer and hasattr(adv_renderer, 'cell_actors') else 0
    results.update(_result('table_formulas', adv_renderer,
                           extra=f'{n_adv} cells, labels A-C + AA + AB',
                           elapsed=time.monotonic() - t0))

    return results


def test_desktop_icons(base_y=0):
    """Spawn first 5 desktop shell icons as BP_Icon actors."""
    from ue_spawn import spawn_desktop_icons
    actors = []
    t0 = time.monotonic()
    try:
        actors = spawn_desktop_icons(
            location=FVector(0, base_y, 100),
            max_icons=5,
        )
    except Exception as e:
        _log_exception('desktop_icons', e)

    first = actors[0] if actors else None
    return _result('desktop_icons', first, extra=f'{len(actors)} spawned',
                   elapsed=time.monotonic() - t0)


def _cylinder_point_cloud(diameter, height, n_points,
                          center_z=False, seed=None):
    """Uniform random point cloud inside a Z-axis cylinder.

    Cross-section uniformity needs r = R*sqrt(u) (not R*u — that biases
    toward the axis). Returns a list of (x, y, z) tuples in cylinder-local
    coords; the caller adds the world-space offset.
    """
    import numpy as np
    rng = np.random.default_rng(seed)
    R = diameter / 2.0
    r = R * np.sqrt(rng.random(n_points))
    theta = rng.uniform(0.0, 2.0 * np.pi, n_points)
    x = r * np.cos(theta)
    y = r * np.sin(theta)
    if center_z:
        z = rng.uniform(-height / 2.0, height / 2.0, n_points)
    else:
        z = rng.uniform(0.0, height, n_points)
    return list(zip(x.tolist(), y.tolist(), z.tolist()))


def test_desktop_icons_cylinder(base_y=0):
    """Spawn desktop icons positioned in a uniform cylindrical point cloud.

    UE scaling notes:
      • Icons are ~150 UU spheres (BP_Icon default), so a 600 UU diameter
        gives ~4 icon-widths across — enough to read as a column, not a
        wall. Height 1500 UU (~15 m) makes the cylinder visibly taller
        than wide.
      • 20 points in a ~4.2e8 UU³ volume → ~270 UU mean nearest-neighbour
        spacing, comfortably more than icon diameter.
      • Cylinder axis sits at (X=0, Y=base_y+350, Z=200+H/2) so the whole
        cloud fits inside the test's allocated Y band [base_y, base_y+1000]
        and Z stays clear of the ground.
    """
    from icon_to_image import get_folder_icons
    from ue_spawn import spawn_icon

    DIAMETER = 600.0
    HEIGHT   = 1500.0
    N_POINTS = 20
    Z_BASE   = 200.0
    Y_CENTER = base_y + 350.0
    SEED     = 42

    actors = []
    t0 = time.monotonic()
    folder = os.path.join(os.path.expanduser('~'), 'Desktop')
    try:
        icons = get_folder_icons(folder)
    except Exception as e:
        _log_exception('desktop_icons_cylinder.scan', e)
        icons = {}

    paths = list(icons.items())[:N_POINTS]
    if not paths:
        _log(f'  desktop_icons_cylinder: no icons found in "{folder}"')
        return _result('desktop_icons_cylinder', None,
                       extra='0 icons (empty folder)',
                       elapsed=time.monotonic() - t0)

    try:
        cloud = _cylinder_point_cloud(
            diameter=DIAMETER, height=HEIGHT,
            n_points=len(paths), seed=SEED)
    except Exception as e:
        _log_exception('desktop_icons_cylinder.cloud', e)
        return _result('desktop_icons_cylinder', None,
                       extra='cloud generation failed',
                       elapsed=time.monotonic() - t0)

    for (path, pil_img), (cx, cy, cz) in zip(paths, cloud):
        loc = FVector(cx, Y_CENTER + cy, Z_BASE + cz)
        try:
            actor = spawn_icon(pil_img, location=loc, source_path=path)
            if actor:
                actors.append(actor)
        except Exception as e:
            ue.log_warning(
                f'desktop_icons_cylinder: spawn_icon failed for "{path}": {e}')

    first = actors[0] if actors else None
    return _result(
        'desktop_icons_cylinder', first,
        extra=f'{len(actors)} spawned in D={DIAMETER:.0f}/H={HEIGHT:.0f} cylinder',
        elapsed=time.monotonic() - t0)


def test_icon(base_y=0):
    """Spawn a BP_Icon from a plain PIL image."""
    from ue_spawn import spawn_icon
    actor = None
    t0 = time.monotonic()
    try:
        from PIL import Image as PILImage
        img = PILImage.new('RGBA', (256, 256), (0, 200, 50, 255))
        actor = spawn_icon(img, location=FVector(0, base_y, 100))
        if actor:
            try:
                actor.get_actor_component('Sphere').SetSimulatePhysics(True)
            except Exception as phys_e:
                _log(f'  icon physics: {phys_e}')
    except Exception as e:
        _log_exception('icon_from_pil', e)
    return _result('icon_from_pil', actor, elapsed=time.monotonic() - t0)


def test_exe_icon(base_y=0):
    """Spawn a BP_Icon from GoogleDriveSetup.exe (shell icon + clickable source_path).

    Uses ue_spawn.spawn_icon_from_path, which wraps extract_icon + spawn_icon
    and attaches the .exe path so pyactor_icon.IconSphere.on_clicked can open
    it in Chrome.
    """
    from ue_spawn import spawn_icon_from_path
    actor = None
    t0 = time.monotonic()
    try:
        actor = spawn_icon_from_path(
            _GOOGLE_DRIVE_EXE,
            location=FVector(0, base_y, 400))
    except Exception as e:
        _log_exception('exe_icon', e)
    return _result('exe_icon', actor, elapsed=time.monotonic() - t0)


# nD table grid test — base_location is the upper-left of the grid.

def test_nd_table(base_y=0):
    """Comprehensive nD table rendering (2D 10x10 through 7D)."""
    from nd_table.examples import test_nd_table_grid
    renderer = None
    t0 = time.monotonic()
    try:
        renderer = test_nd_table_grid(
            base_location=FVector(0, base_y, 700))
    except Exception as e:
        _log_exception('nd_table_grid', e)
    n_cells = len(renderer.cell_actors) if renderer and hasattr(renderer, 'cell_actors') else 0
    n_lines = len(renderer.gridline_actors) if renderer and hasattr(renderer, 'gridline_actors') else 0
    return _result('nd_table_grid', renderer,
                   extra=f'{n_cells} cells, {n_lines} gridlines',
                   elapsed=time.monotonic() - t0)


# File explorer test — Spawns a FileExplorer PyActor that builds a
# Name/Size/Date/Type table and a leftmost column of BP_Icons.  BP_Icon's
# IconSphere handles clicks (opens the file with the OS default handler —
# Windows Explorer behavior).

def test_file_explorer(base_y=0):
    """Spawn a FileExplorer PyActor populated via EverythingAPI.

    Spawned at Z=1500 because the wall_table renderer steps each row down
    in -Z; in practice Everything returns ~5-10 files for the default folder
    (~1200 UU tall), so the table sits comfortably above ground. With the
    full MAX_FILES=20 the lowest rows can clip the floor — acceptable
    tradeoff for keeping the visible top close to other tests' altitude.

    Requires Everything (Voidtools) running and Everything64.dll reachable.
    PASS = PyActor spawned; table + icons are rendered asynchronously in
    the component's begin_play and logged to UE output."""
    from ue_spawn import spawn_file_explorer
    actor = None
    t0 = time.monotonic()
    try:
        actor = spawn_file_explorer(
            location=FVector(0, base_y, 1500),
            initial_path=os.path.dirname(
                os.path.abspath(ue.get_content_dir())))
    except Exception as e:
        _log_exception('file_explorer', e)
    return _result('file_explorer', actor,
                   extra='needs Everything daemon + Everything64.dll',
                   elapsed=time.monotonic() - t0)


# 3D resizable table test
# Uses spawn_table_actor so the renderer's gridline resize controller is
# ticked by a PyActor — LMB-drag on any gridline resizes that row (axis 0),
# column (axis 1), or slice/layer (axis 2).

def test_3d_table_resize(base_y=0):
    """Spawn a 3x3x3 resizable table for trying out row/col/slice drag-resize.

    Hover a gridline, then LMB-drag to resize the adjacent row (axis 0),
    column (axis 1), or slice/layer (axis 2). The cursor changes to
    ResizeUpDown / ResizeLeftRight / CardinalCross to indicate the axis.
    """
    from ue_spawn import spawn_table_actor
    actor = None
    t0 = time.monotonic()
    try:
        from nd_table.ndtable import Table
        t = Table(shape=(3, 3, 3))
        for i in range(3):
            for j in range(3):
                for k in range(3):
                    t[i, j, k] = f'r{i}c{j}s{k}'
        actor = spawn_table_actor(
            t,
            location=FVector(0, base_y, 500),
            enable_resize=True,
        )
    except Exception as e:
        _log_exception('3d_table_resize', e)
    extra = 'drag gridlines: row/col/slice resize'
    try:
        if actor is not None:
            proxy = actor.get_py_proxy()
            if proxy is not None and proxy.renderer is not None:
                n_cells = len(proxy.renderer.cell_actors)
                n_lines = len(proxy.renderer.gridline_actors)
                extra = f'{n_cells} cells, {n_lines} gridlines (drag to resize row/col/slice)'
    except Exception:
        pass
    return _result('3d_table_resize', actor, extra=extra, elapsed=time.monotonic() - t0)


# Dynamic 3D object test — runtime GLB import via the GLTFImporter plugin
# (enabled in Starcel9.uproject), then StaticMeshActor + SetStaticMesh.
#
# Why not ue.import_asset(_DUCK_GLB, '/Game/Models')?  AssetTools' ImportAssets
# hardcodes bAutomated=false (UE 4.27 AssetTools.cpp:1298), so GLTFImportFactory
# pops a modal "glTF Import Options" SWindow during PIE.  In gameplay that
# dialog is invisible / unfocusable, so the import never completes and the
# duck never spawns.  Workaround: instantiate UGLTFImportFactory ourselves,
# attach a UAssetImportTask with bAutomated=True, then call
# factory_import_object — IsAutomatedImport() returns true and the modal is
# skipped (defaults: ImportScale=100, bGenerateLightmapUVs=false).
#
# Why not ue_spawn.spawn_obj?  spawn_obj routes GLB through trimesh → FBX →
# PyFbxFactory, but trimesh has no FBX exporter (its exchange formats are
# OBJ/PLY/STL/GLB/GLTF/DAE/3MF — no FBX), so that path returns None even
# with `pip install trimesh`.  The Blender fallback works only if Blender
# is on PATH.

def test_3d_object(base_y=0):
    """Spawn Content/Models/Duck.glb dynamically via the GLTFImporter plugin.

    Pipeline:
      1. ue.load_object('/Game/Models/Duck') if already imported.
      2. Otherwise: GLTFImportFactory + AssetImportTask(bAutomated=True) →
         factory_import_object — bypasses the modal options dialog that
         AssetTools.ImportAssets would otherwise show.
      3. world.actor_spawn(StaticMeshActor) + Mobility=Movable BEFORE
         SetStaticMesh (see feedback_movable_mobility memory).
    """
    from unreal_engine.classes import StaticMesh, StaticMeshActor
    from unreal_engine.enums import EComponentMobility

    if not os.path.isfile(_DUCK_GLB):
        return _skip('3d_object', f'not found: {_DUCK_GLB}')

    t0 = time.monotonic()
    dest_folder = '/Game/Models'
    # GLTFImportFactory writes the mesh under /Game/Models/Duck/<glTF mesh name>.
    # For Duck.glb the mesh name is "LOD3spShape" (prefixed "0_" by the factory).
    # Probe that path FIRST so re-runs hit the cached .uasset and skip the
    # 5-second distance-field rebuild that re-import triggers — and the
    # bare /Game/Models/Duck paths (which always miss for this glTF) never
    # get reached, eliminating their LogLinker miss warnings on every run.
    asset_candidates = [
        '/Game/Models/Duck/0_LOD3spShape',
        '/Game/Models/Duck',
        '/Game/Models/Duck/Duck',
    ]

    def _load_first():
        for p in asset_candidates:
            try:
                obj = ue.load_object(StaticMesh, p)
                if obj is not None:
                    return obj
            except Exception:
                continue
        return None

    def _scan_dest_for_static_mesh():
        """Scan dest_folder via AssetRegistry for any StaticMesh — used after
        factory_import_object returns the outer rather than the mesh itself."""
        try:
            from unreal_engine.classes import AssetRegistryHelpers
            registry = AssetRegistryHelpers.GetAssetRegistry()
        except Exception:
            return None
        assets = None
        for method in ('get_assets_by_path', 'GetAssetsByPath'):
            fn = getattr(registry, method, None)
            if fn is None:
                continue
            try:
                assets = fn(dest_folder, True)
                break
            except Exception:
                continue
        if not assets:
            return None
        for data in assets:
            try:
                loaded = data.get_asset() if hasattr(data, 'get_asset') else None
                if loaded is not None and _is_static_mesh(loaded):
                    return loaded
            except Exception:
                continue
        return None

    def _is_static_mesh(obj):
        try:
            return obj is not None and obj.get_class().get_name() == 'StaticMesh'
        except Exception:
            return False

    # Step 1: load if already imported.
    mesh = _load_first()

    # Step 2: import via UGLTFImportFactory with bAutomated=True so the
    # plugin's options dialog is skipped (see header comment).
    if mesh is None:
        try:
            factory_class = ue.find_class('GLTFImportFactory')
            task_class = ue.find_class('AssetImportTask')
            if factory_class is None or task_class is None:
                raise Exception(
                    'GLTFImportFactory / AssetImportTask class not found — '
                    'is the GLTFImporter plugin enabled in Starcel9.uproject?')
            factory = ue.new_object(factory_class)
            task = ue.new_object(task_class)
            task.bAutomated = True
            task.bReplaceExisting = True
            task.bSave = False
            task.Filename = _DUCK_GLB
            task.DestinationPath = dest_folder
            factory.AssetImportTask = task
            asset = factory.factory_import_object(_DUCK_GLB, dest_folder)
            if _is_static_mesh(asset):
                mesh = asset
            else:
                # factory_import_object can return the package's outer for
                # multi-mesh glTF; fall back to canonical asset paths, then
                # scan the dest folder for any StaticMesh.
                mesh = _load_first() or _scan_dest_for_static_mesh()
        except Exception as e:
            _log_exception('3d_object/factory_import', e)
            mesh = _load_first() or _scan_dest_for_static_mesh()

    if mesh is None:
        return _result('3d_object', None,
                       inputs={'path': _DUCK_GLB, 'dest': dest_folder},
                       extra='import failed — is GLTFImporter plugin enabled?',
                       elapsed=time.monotonic() - t0)

    # Step 3: spawn StaticMeshActor.  Mobility must be Movable BEFORE
    # SetStaticMesh on respawn (project memory: feedback_movable_mobility).
    actor = None
    try:
        world = get_world()
        actor = world.actor_spawn(StaticMeshActor)
        smc = actor.StaticMeshComponent
        smc.Mobility = EComponentMobility.Movable
        smc.SetStaticMesh(mesh)
        actor.set_actor_location(FVector(0, base_y, 100))
        actor.set_actor_scale(FVector(0.01, 0.01, 0.01))
    except Exception as e:
        _log_exception('3d_object/spawn', e)

    return _result('3d_object', actor,
                   inputs={'path': _DUCK_GLB, 'dest': dest_folder},
                   extra=f'mesh={mesh.get_name()} via GLTFImporter',
                   elapsed=time.monotonic() - t0)


# Same Duck.glb, different pipeline:
#   • test_3d_object         → editor-import path. UGLTFImportFactory +
#                              AssetImportTask(bAutomated=True) writes a
#                              .uasset to /Game/Models, then a StaticMeshActor
#                              points at it.
#   • test_glb_object_runtime → ue_spawn.spawn_gltf_runtime. Calls
#                              UglTFRuntimeFunctionLibrary::glTFLoadAssetFromFilename
#                              and spawns AglTFRuntimeAssetActor with Asset as
#                              an ExposeOnSpawn kwarg (must land before BeginPlay
#                              — that's where the plugin walks scenes/nodes to
#                              build the component tree). No .uasset on disk.

def test_glb_object_runtime(base_y=0):
    """Spawn Content/Models/Duck.glb at runtime via the glTFRuntime plugin.

    Side-by-side with test_3d_object so the duck shows up twice in the same
    suite — easy visual confirmation that both pipelines work and produce a
    matching mesh. The glTFRuntime version is the only one that survives in
    a packaged build (editor importers are stripped).
    """
    from ue_spawn import spawn_gltf_runtime

    if not os.path.isfile(_DUCK_GLB):
        return _skip('glb_object_runtime', f'not found: {_DUCK_GLB}')
    if ue.find_class('glTFRuntimeAssetActor') is None:
        return _skip(
            'glb_object_runtime',
            'glTFRuntime plugin not loaded — enable in Starcel9.uproject + rebuild')

    t0 = time.monotonic()
    actor = None
    try:
        actor = spawn_gltf_runtime(
            _DUCK_GLB,
            location=FVector(0, base_y, 100),
            scale=FVector(0.1, 0.1, 0.1))
    except Exception as e:
        _log_exception('glb_object_runtime/spawn', e)

    return _result('glb_object_runtime', actor,
                   inputs={'path': _DUCK_GLB, 'spawner': 'spawn_gltf_runtime'},
                   extra='via glTFRuntime plugin (runtime parse, no .uasset)',
                   elapsed=time.monotonic() - t0)


def test_text3d_executor(base_y=0):
    """Spawn a Ctrl+Enter Python executor Text3D.

    Exercises ue_spawn.spawn_text3d_executor — the convenience wrapper
    around spawn_text3d_pyactor that hardcodes the
    pyactor_text3d_executor.PyActorText3DExecutor proxy.

    Click the spawned text to focus it (requires test_text3d_click typing
    setup), edit the code, then press Ctrl+Enter to exec(). The default
    payload is a one-line ue.log call so a smoke test is visible in the
    Output Log.
    """
    from ue_spawn import spawn_text3d_executor
    actor = None
    t0 = time.monotonic()
    try:
        actor = spawn_text3d_executor(
            text='ue.log("hello from Ctrl+Enter")',
            location=FVector(0, base_y, 200),
        )
    except Exception as e:
        _log_exception('text3d_executor', e)

    child = None
    try:
        child = getattr(actor, 'text3d_actor', None) if actor else None
    except Exception:
        pass
    extra = (f'child={child.get_name()} (Ctrl+Enter to run)'
             if child else 'no child attached')
    return _result('text3d_executor', actor, extra=extra,
                   elapsed=time.monotonic() - t0)


def test_gizmo(uobject=None, input_manager=None, location=None, base_y=0):
    """
    Spawn the interactive transform gizmo (target cylinder + move arrows,
    rotate rings, scale handles, plane squares) and wire up drag interaction.
    Returns (target, handles, pyactor).

    Delegates to ue_spawn.spawn_gizmo so the GizmoController is hosted on a
    BP_PyActorEmpty (the canonical spawn_pyactor default). Omitting uobject
    /input_manager spawns the gizmo statically (no drag / no PyActor).
    """
    from ue_spawn import spawn_gizmo

    if location is None:
        # Z=250 keeps the scale handles (which extend ±175 UU around the
        # target) from sitting underground.
        location = FVector(0, base_y, 250)

    _log('--- test_gizmo ---')
    _log(f'Spawning gizmo target at {location}')

    t0 = time.monotonic()
    try:
        target, handles, pyactor = spawn_gizmo(
            location=location,
            uobject=uobject,
            input_manager=input_manager,
        )
    except Exception as e:
        _log(f'test_gizmo: spawn failed: {e}')
        _result('gizmo', None, extra=str(e),
                elapsed=time.monotonic() - t0)
        return None, None, None

    if handles is not None:
        _log(f'test_gizmo: spawned target + {len(handles)} handles')

    if uobject is not None and input_manager is not None:
        if pyactor is not None:
            _log('test_gizmo: GizmoController PyActor spawned + wired '
                 '(drag LMB on any handle)')
        else:
            _log('test_gizmo: GizmoController setup failed')
    else:
        _log('test_gizmo: WARNING — no uobject/input_manager; '
             'gizmo will be static (no drag). Pass self.uobject and '
             'self.input from Main.begin_play to enable interaction.')

    _result('gizmo', target,
            extra=f'{len(handles) if handles else 0} handles',
            elapsed=time.monotonic() - t0)
    return target, handles, pyactor


def test_plot(base_y=0):
    """
    Four plot tests spread along Y from *base_y*. Each plot's x_range=(-π,π)
    × units_per_uu=80 makes it ~502 UU wide, so origins are stepped by 600
    and shifted by +260 so the leftmost edge of plot 0 sits at ~base_y
    (instead of bleeding −251 UU into the previous test's band):
      base_y +  260 — colormap surface, spheres
      base_y +  860 — colormap surface, sphere_lines
      base_y + 1460 — spherical ripple sphere_lines
      base_y + 2060 — 2D tan(x) curve

    Uses spawn_plot() — a dynamic PyActorPlotter spawned via spawn_pyactor.
    Falls back to create_plotter() directly if spawn_plot errors out.
    """
    import math
    results = {}

    PLOT_HALF_WIDTH = 260   # ≈ π × units_per_uu (80) — covers ±251 UU plot extent
    PLOT_STRIDE     = 600   # one full plot width (~502) + small gutter

    variants = [
        dict(name='plot_spheres',        func='sin(x)+cos(y)',
             plot_type='surface',   mesh_mode='spheres',      orientation='ground_table',
             location=FVector(0, base_y + PLOT_HALF_WIDTH + 0 * PLOT_STRIDE, 0)),
        dict(name='plot_sphere_lines',   func='sin(x)+cos(y)',
             plot_type='surface',   mesh_mode='sphere_lines', orientation='ground_table',
             location=FVector(0, base_y + PLOT_HALF_WIDTH + 1 * PLOT_STRIDE, 0)),
        dict(name='plot_ripple_sphere_lines', func='sin(sqrt(x**2+y**2))',
             plot_type='surface',   mesh_mode='sphere_lines', orientation='ground_table',
             location=FVector(0, base_y + PLOT_HALF_WIDTH + 2 * PLOT_STRIDE, 0)),
    ]

    for v in variants:
        actor = None
        name = v['name']
        t0 = time.monotonic()

        # Primary path: PyActorPlotter via spawn_plot
        try:
            from ue_spawn import spawn_plot
            actor = spawn_plot(
                function_expr = v['func'],
                plot_type = v['plot_type'],
                orientation = v['orientation'],
                resolution = 32,
                location = v['location'],
                mesh_mode = v.get('mesh_mode', 'triangles'),
            )
        except Exception as e:
            _log(f'  {name}: spawn_plot failed ({e}), trying direct plotter...')

        # fallback: create_plotter directly (debug=True shows mesh errors)
        if actor is None:
            try:
                from ue_math_plotter import create_plotter
                p = create_plotter(
                    world = get_world(),
                    origin = v['location'],
                    x_range = (-3.14159, 3.14159),
                    y_range = (-3.14159, 3.14159),
                    z_range = (-2.0,  2.0),
                    units_per_uu = 80.0,
                    orientation = v['orientation'],
                    debug = True,
                )
                p.mesh_mode = v.get('mesh_mode', 'triangles')
                if 'point_mesh' in v:
                    p.point_mesh = v['point_mesh']
                p.labs(title=v['func'], x='x', y='y', z='z')
                p.grid(True, mode='3d')
                fn_expr = v['func']
                fn = lambda x, y, _e=fn_expr: float(eval(
                    compile(_e, '<test>', 'eval'), {"__builtins__": {}},
                    dict(sin=math.sin, cos=math.cos, sqrt=math.sqrt,
                         pi=math.pi, e=math.e, abs=abs, x=x, y=y)))
                if v['plot_type'] == 'heatmap':
                    p.heatmap(fn, resolution=32)
                elif v['plot_type'] == 'wireframe':
                    p.wireframe(fn, resolution=32)
                else:
                    p.colormap_surface(fn, resolution=32)
                p.show()
                actor = p
            except Exception as e2:
                _log(f'  {name} direct plotter also failed: {e2}')

        results.update(_result(name, actor, elapsed=time.monotonic() - t0))

    # 2D curve: tan(x) with asymptote breaks
    plot_2d = None
    t0 = time.monotonic()
    try:
        from ue_math_plotter import create_plotter

        def _tan_safe(x):
            """Return NaN near asymptotes so the curve breaks cleanly."""
            v = math.tan(x)
            if abs(v) > 5.0:
                return float('nan')
            return v

        p = create_plotter(
            world = get_world(),
            origin = FVector(0, base_y + PLOT_HALF_WIDTH + 3 * PLOT_STRIDE, 0),
            x_range = (-3.14159, 3.14159),
            y_range = (-5.0, 5.0),
            z_range = (-5.0, 5.0),
            units_per_uu = 80.0,
            orientation = 'wall_table',
            debug = True,
        )
        p.labs(title='tan(x)', x='x', y='y')
        p.grid(True)
        p.plot(_tan_safe, n=256)
        p.show()
        plot_2d = p
    except Exception as e:
        _log(f'  plot_tan_2d failed: {e}')
    results.update(_result('plot_tan_2d', plot_2d, extra='2D tan(x)',
                           elapsed=time.monotonic() - t0))

    return results


# Aggregator

def test_spawn_all(uobject=None, input_manager=None, tests=None):
    """
    Run all spawn tests.  Modeled after test_gizmos().

    Actors are placed at X=0 and spread along Y.  Each chosen test gets a
    base_y allocated sequentially from a running cursor (starting at Y=0)
    using its registered span in ``_TEST_Y_SPAN`` — so a subset like
    ``tests=['cameras','earth']`` is packed at the origin instead of being
    pushed out to the cameras' fixed Y=2200 like the old layout did, and
    independent tests never share a Y band.

    Runs a prerequisites check first so you know exactly what to set up.

    Parameters
    ----------
    uobject       : PyActor UObject (self.uobject from Main). When provided
                    together with input_manager, the interactive tests
                    test_gizmo and test_text3d_click are also run (they
                    spawn PyActors that own their own ticks — Main.tick
                    does not need to forward anything).
    input_manager : HotkeyManager instance (self.input from Main).
    tests         : Optional iterable of test names to run. Names may be
                    given with or without the ``test_`` prefix
                    (e.g. ``['video']`` or ``['test_video']``). A single
                    string is also accepted. ``None`` (default) runs every
                    test. Unknown names are logged and ignored.

    Returns
    -------
    dict: { test_name: {'ok': bool, 'actor': actor_or_None,
                        'elapsed': seconds_or_None} }

    Call from PIE Python console:
        from test_spawn import test_spawn_all
        results = test_spawn_all()

    Call from Main.begin_play (to also run the interactive tests):
        test_spawn_all(uobject=self.uobject, input_manager=self.input)

    Run only one test:
        test_spawn_all(tests=['video'])

    PASS/FAIL report is written to the UE Output Log.
    """
    run_t0 = time.monotonic()

    _log('=' * 70)
    _log('test_spawn_all')
    _log('=' * 70)

    _log_env()
    _check_prerequisites()

    # TODO: No dict
    # (fn_name, callable_taking_base_y) pairs — order = layout order.
    non_interactive = [
        ('test_primitives',     test_primitives),
        ('test_image',          test_image),
        ('test_video',          test_video),
        ('test_sound',          test_sound),
        ('test_cameras',        test_cameras),
        ('test_earth',          test_earth),
        ('test_system_monitor', test_system_monitor),
        ('test_table',          test_table),
        ('test_desktop_icons',  test_desktop_icons),
        ('test_desktop_icons_cylinder', test_desktop_icons_cylinder),
        ('test_icon',           test_icon),
        ('test_exe_icon',       test_exe_icon),
        ('test_nd_table',       test_nd_table),
        ('test_plot',           test_plot),
        ('test_file_explorer',  test_file_explorer),
        ('test_3d_table_resize', test_3d_table_resize),
        ('test_3d_object',      test_3d_object),
        ('test_glb_object_runtime', test_glb_object_runtime),
        ('test_text3d_executor', test_text3d_executor),
    ]
    interactive = [
        ('test_gizmo',
         lambda by: test_gizmo(uobject=uobject,
                               input_manager=input_manager,
                               base_y=by)),
        ('test_text3d_click',
         lambda by: test_text3d_click(uobject=uobject,
                                      input_manager=input_manager,
                                      base_y=by)),
    ]

    if tests is not None:
        if isinstance(tests, str):
            tests = [tests]
        selected = {t if t.startswith('test_') else f'test_{t}' for t in tests}
        known = {n for n, _ in non_interactive} | {n for n, _ in interactive}
        unknown = selected - known
        if unknown:
            _log(f'WARNING: unknown test names ignored: {sorted(unknown)}')
        non_interactive = [(n, fn) for (n, fn) in non_interactive if n in selected]
        interactive = [(n, c)  for (n, c)  in interactive    if n in selected]

    results = {}
    timings = {}   # fn_name -> seconds (whole-fn wall time)
    layout = {}   # fn_name -> base_y allocated
    errors = {}   # fn_name -> top-level exception if the whole fn blew up
    y_cursor = 0    # next available Y (sequential allocation)

    def _run(fn_name, fn_call):
        nonlocal y_cursor
        base_y = y_cursor
        layout[fn_name] = base_y
        span = _TEST_Y_SPAN.get(fn_name, 1000)
        _section(f'{fn_name}  (base_y={base_y}, span={span})')
        t0 = time.monotonic()
        try:
            out = fn_call(base_y)
            if isinstance(out, dict):
                results.update(out)
        except Exception as e:
            errors[fn_name] = e
            _log_exception(fn_name, e)
        timings[fn_name] = time.monotonic() - t0
        _log(f'  total elapsed: {timings[fn_name]:.2f}s')
        y_cursor += span

    for fn_name, fn in non_interactive:
        _run(fn_name, fn)

    # Interactive tests — need uobject + input_manager from Main. Their own
    # PyActors own the per-frame tick, so Main.tick does not forward anything.
    if uobject is not None and input_manager is not None:
        for fn_name, fn_call in interactive:
            _run(fn_name, fn_call)

    passed = sum(1 for v in results.values() if v['ok'])
    failed = len(results) - passed

    _log('')
    _log('=' * 70)
    _log(f'RESULTS: {passed} PASS / {failed} FAIL  (total {len(results)})')
    _log(f'Total elapsed: {time.monotonic() - run_t0:.2f}s')
    _log('=' * 70)

    # Per-test table — fast scan of what passed/failed, class returned, time taken
    _log('')
    _log('Per-test summary:')
    _log(f'  {"status":<6} {"test":<40} {"elapsed":>8}  {"class":<30}')
    _log(f'  {"-"*6} {"-"*40} {"-"*8}  {"-"*30}')
    for name in sorted(results.keys()):
        r = results[name]
        status = 'PASS' if r['ok'] else 'FAIL'
        cls_str = ''
        if r.get('actor') is not None:
            try:
                cls_str = type(r['actor']).__name__
            except Exception:
                cls_str = '<?>'
        else:
            cls_str = '—'
        secs = r.get('elapsed')
        elapsed_str = f'{secs:7.3f}s' if secs is not None else '       —'
        _log(f'  {status:<6} {name:<40} {elapsed_str}  {cls_str:<30}')

    # Fail-only list — makes it easy to paste only failing tests back
    failing = [n for n, r in results.items() if not r['ok']]
    if failing:
        _log('')
        _log(f'FAILING TESTS ({len(failing)}): ' + ', '.join(failing))

    # Per-fn elapsed times (spot hangs/slow tests) + base_y allocation
    _log('')
    _log('Per-fn timings + Y-band layout:')
    _log(f'  {"elapsed":>8}  {"base_y":>7}  {"span":>5}  test')
    _log(f'  {"-"*8}  {"-"*7}  {"-"*5}  {"-"*40}')
    for name, secs in timings.items():
        marker = '  (fn-level error)' if name in errors else ''
        by = layout.get(name, 0)
        sp = _TEST_Y_SPAN.get(name, 0)
        _log(f'  {secs:7.2f}s  {by:>7}  {sp:>5}  {name}{marker}')

    return results


def test_text3d_click(uobject=None, input_manager=None, location=None, base_y=0):
    """
    Spawn one Text3D actor with the known string "ABCDEFGHIJ" so the
    PyActorText3D click + typing system has a target to focus.  The
    typing/selection state machine itself lives on PyActorText3D
    (class-level) — this function just spawns the actor and registers
    it.  The previous closure-based prototype here, plus its 5x5x5
    test table, was absorbed into pyactor_text3d.PyActorText3D.

    uobject       — kept for back-compat with the test_spawn_all
                    dispatch signature; no longer used.
    input_manager — same; mouse polling is now Win32 (VK_LBUTTON), so
                    no HotkeyManager dependency.
    location      — FVector spawn position. Defaults to FVector(400, base_y, 450).
    base_y        — used only when *location* is None.

    Re-call from PIE console at any position:
        from test_spawn import test_text3d_click
        from unreal_engine import FVector
        a = test_text3d_click(location=FVector(500, 200, 150))

    BP_Cell requirements:
      - Text3DComponent -> Generate Hit Events = ON
      - Collision response to WorldDynamic = Block
    """
    from ue_spawn import spawn_blueprint
    from pyactor_text3d import PyActorText3D

    if location is None:
        location = FVector(400, base_y, 450)

    _log('--- test_text3d_click ---')
    _log(f'Spawning at {location}')
    _log('BP_Cell requirement: Text3DComponent -> Generate Hit Events = ON')

    actor = None
    try:
        actor = spawn_blueprint(
            '/Game/Blueprints/Assets/BP_Cell.BP_Cell',
            location=location,
        )
        if actor is not None:
            t3d = actor.get_actor_component('Text3DComponent')
            if t3d:
                t3d.Text = 'ABCDEFGHIJ'
                try:
                    t3d.SetGenerateOverlapEvents(True)
                except Exception:
                    pass
                try:
                    t3d.bGenerateOverlapEvents = True
                except Exception:
                    pass
                _log('text3d_click: spawned single actor "ABCDEFGHIJ"')
            else:
                _log('text3d_click: WARNING - no Text3DComponent on BP_Cell')
            try:
                actor.SetActorEnableCollision(True)
            except Exception:
                pass
            # Ensure registration even when BP_Cell lacks the PyActorText3D
            # PythonComponent (begin_play wouldn't have fired).  Both calls
            # are idempotent.
            PyActorText3D.register_actor(actor)
            PyActorText3D._ensure_global_typing()
    except Exception as e:
        _log(f'text3d_click: spawn failed: {e}')

    return actor
