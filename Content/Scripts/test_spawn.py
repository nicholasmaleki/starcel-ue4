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
  primitives     1000  (5 shapes, stride 200)
  image           600  (valid + invalid path)
  video           600
  sound           400
  cameras        4000  (8 presets, stride 500)
  earth          1000  (2 presets, stride 500)
  system_monitor  500
  table          1000  (basic + formulas, formulas offset on X)
  desktop_icons  1000
  icon            500
  exe_icon        500
  nd_table       2000  (2D 10x10 through 7D)
  plot           2000  (4 plots, stride 500)
  file_explorer  1000  (Everything-backed)
  3d             1000  (drag row/col/slice gridlines)
  gizmo          1000  (interactive — only with uobject+input_manager)
  text3d_click   1000  (interactive — only with uobject+input_manager)

Usage (PIE Python console):
    from test_spawn import test_spawn_all
    results = test_spawn_all()

    # Manual Text3D click investigation:
    from test_spawn import test_text3d_click
    test_text3d_click()

    # Interactive transform gizmo (needs uobject + input_manager):
    from test_spawn import test_gizmo
    target, handles, tick = test_gizmo(uobject, input_manager)

Per-test elapsed time is logged to Desktop/test_spawn_log.txt and
returned on each result entry as ``results[name]['elapsed']``.

Prerequisites summary printed to log at start of test_spawn_all().
Log file: Desktop/test_spawn_log.txt
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

DESKTOP   = os.path.join(os.path.expanduser('~'), 'Desktop')
_LOG_PATH = os.path.join(DESKTOP, 'test_spawn_log.txt')
_log_file = open(_LOG_PATH, 'w', buffering=1, encoding='utf-8')


def _log(msg):
    ue.log(msg)
    _log_file.write(msg + '\n')


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
    ok     = actor_or_value is not None
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
    _log(f'  Log path:   {_LOG_PATH}')


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
_TEST_Y_SPAN = {
    'test_primitives':     1000,   # 5 shapes × 200 stride                  (0..800)
    'test_image':           600,   # valid at 0, invalid at +400
    'test_video':           600,
    'test_sound':           400,   # at 0 and +200
    'test_cameras':        4000,   # 8 presets × 500 stride                 (0..3500)
    'test_earth':          1000,   # 2 presets × 500
    'test_system_monitor':  500,
    'test_table':          1000,   # basic + formulas (formulas offset on X)
    'test_desktop_icons':  1000,
    'test_icon':            500,
    'test_exe_icon':        500,
    'test_nd_table':       2000,
    'test_plot':           2000,   # 4 plots × 500 stride
    'test_file_explorer':  1000,
    'test_3d':             1000,
    'test_gizmo':          1000,
    'test_text3d_click':   1000,
}

_GOOGLE_DRIVE_EXE = r"C:\Users\nicho\Downloads\GoogleDriveSetup.exe"
_BIG_BAD_JOHN_FLAC = r"C:\Users\nicho\Downloads\Big Bad John\Big Bad John.flac"


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
        loc   = FVector(0, base_y + i * 200, 100)
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
            d   = ImageDraw.Draw(img)
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
        loc   = FVector(0, base_y + i * 500, 300)
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
        loc   = FVector(0, base_y + i * 500, 0)
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
    """Spawn a PyActorSysmon dynamically (no Blueprint placeholder)."""
    from ue_spawn import spawn_system_monitor
    actor = None
    t0 = time.monotonic()
    try:
        actor = spawn_system_monitor(location=FVector(0, base_y, 100))
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

    Requires Everything (Voidtools) running and Everything64.dll reachable.
    PASS = PyActor spawned; table + icons are rendered asynchronously in
    the component's begin_play and logged to UE output."""
    from ue_spawn import spawn_file_explorer
    actor = None
    t0 = time.monotonic()
    try:
        actor = spawn_file_explorer(
            location=FVector(0, base_y, 100))
    except Exception as e:
        _log_exception('file_explorer', e)
    return _result('file_explorer', actor,
                   extra='needs Everything daemon + Everything64.dll',
                   elapsed=time.monotonic() - t0)


# 3D resizable table test
# Uses spawn_table_actor so the renderer's gridline resize controller is
# ticked by a PyActor — LMB-drag on any gridline resizes that row (axis 0),
# column (axis 1), or slice/layer (axis 2).

def test_3d(base_y=0):
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
        _log_exception('3d', e)
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
    return _result('3d', actor, extra=extra, elapsed=time.monotonic() - t0)


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
        location = FVector(0, base_y, 100)

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
    Four plot tests spread along Y from *base_y*:
      base_y      — colormap surface, spheres (reference)
      base_y + 500  — colormap surface, sphere_lines
      base_y + 1000 — spherical ripple sphere_lines
      base_y + 1500 — 2D tan(x) curve

    Uses spawn_plot() — a dynamic PyActorPlotter spawned via spawn_pyactor.
    Falls back to create_plotter() directly if spawn_plot errors out.
    """
    import math
    results = {}

    variants = [
        dict(name='plot_spheres',        func='sin(x)+cos(y)',
             plot_type='surface',   mesh_mode='spheres',      orientation='ground_table',
             location=FVector(0, base_y,        0)),
        dict(name='plot_sphere_lines',   func='sin(x)+cos(y)',
             plot_type='surface',   mesh_mode='sphere_lines', orientation='ground_table',
             location=FVector(0, base_y + 500,  0)),
        dict(name='plot_ripple_sphere_lines', func='sin(sqrt(x**2+y**2))',
             plot_type='surface',   mesh_mode='sphere_lines', orientation='ground_table',
             location=FVector(0, base_y + 1000, 0)),
    ]

    for v in variants:
        actor = None
        name  = v['name']
        t0    = time.monotonic()

        # Primary path: PyActorPlotter via spawn_plot
        try:
            from ue_spawn import spawn_plot
            actor = spawn_plot(
                function_expr = v['func'],
                plot_type     = v['plot_type'],
                orientation   = v['orientation'],
                resolution    = 32,
                location      = v['location'],
                mesh_mode     = v.get('mesh_mode', 'triangles'),
            )
        except Exception as e:
            _log(f'  {name}: spawn_plot failed ({e}), trying direct plotter...')

        # fallback: create_plotter directly (debug=True shows mesh errors)
        if actor is None:
            try:
                from ue_math_plotter import create_plotter
                p = create_plotter(
                    world        = get_world(),
                    origin       = v['location'],
                    x_range      = (-3.14159, 3.14159),
                    y_range      = (-3.14159, 3.14159),
                    z_range      = (-2.0,  2.0),
                    units_per_uu = 80.0,
                    orientation  = v['orientation'],
                    debug        = True,
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
            world        = get_world(),
            origin       = FVector(0, base_y + 1500, 0),
            x_range      = (-3.14159, 3.14159),
            y_range      = (-5.0, 5.0),
            z_range      = (-5.0, 5.0),
            units_per_uu = 80.0,
            orientation  = 'wall_table',
            debug        = True,
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

    Open Desktop/test_spawn_log.txt for the PASS/FAIL report.
    """
    run_t0 = time.monotonic()

    _log('=' * 70)
    _log('test_spawn_all')
    _log('=' * 70)

    _log_env()
    _check_prerequisites()

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
        ('test_icon',           test_icon),
        ('test_exe_icon',       test_exe_icon),
        ('test_nd_table',       test_nd_table),
        ('test_plot',           test_plot),
        ('test_file_explorer',  test_file_explorer),
        ('test_3d',             test_3d),
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
        interactive    = [(n, c)  for (n, c)  in interactive    if n in selected]

    results  = {}
    timings  = {}   # fn_name -> seconds (whole-fn wall time)
    layout   = {}   # fn_name -> base_y allocated
    errors   = {}   # fn_name -> top-level exception if the whole fn blew up
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
    _log(f'Log:     {_LOG_PATH}')
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


# Text3D click investigation (manual — call, then click the spawned text)

def _resolve_char_from_meshes(actor, hit):
    """
    Identify which character the hit point landed on by transforming the
    world-space hit into the actor's local space and walking the
    CharacterKernings Y positions (character advance axis in Text3D CPP).

    The Text3DComponent.cpp layout:
      • Characters advance along **local Y**
      • Lines descend along **local -Z**
      • Collision comes from a single UBoxComponent ("Text3D_Bounds")
        that blocks ECC_Visibility — individual glyph meshes ignore
        all channels.
      • Spaces (bIsVisible=false) are skipped in CharacterMeshes /
        CharacterKernings, so glyph index != string index when spaces
        are present.

    Returns (char_index, letter) or (None, None).
    """
    t3d = None
    try:
        t3d = actor.get_actor_component('Text3DComponent')
    except Exception:
        return None, None
    if t3d is None:
        return None, None

    text = ''
    try:
        text = str(t3d.Text or '')
    except Exception:
        pass

    # Get glyph kerning components (one per visible character)
    kernings = None
    try:
        kernings = t3d.CharacterKernings
    except Exception:
        pass

    char_meshes = None
    try:
        char_meshes = t3d.CharacterMeshes
    except Exception:
        pass

    n_glyphs = 0
    if kernings is not None:
        n_glyphs = len(kernings)
    elif char_meshes is not None:
        n_glyphs = len(char_meshes)
    if n_glyphs == 0:
        return None, None

    # Transform hit point into actor local space
    local_pt = _world_to_local(actor, hit.impact_point)
    if local_pt is None:
        return None, None

    # Collect the left-edge Y of each glyph from CharacterKernings.
    # CPP sets: GlyphLocation = Location; Location.Y += GetAdvanced(...)
    # So kerning[i].RelativeLocation.Y is the LEFT EDGE of glyph i.
    glyph_edges = []  # (left_y, glyph_index)
    for i in range(n_glyphs):
        glyph_y = None
        if kernings is not None and i < len(kernings) and kernings[i] is not None:
            try:
                rel = kernings[i].get_relative_location()
                glyph_y = rel.y
            except Exception:
                pass
        if glyph_y is None and char_meshes is not None and i < len(char_meshes):
            try:
                mesh_world = char_meshes[i].get_world_location()
                mesh_local = _world_to_local(actor, mesh_world)
                if mesh_local:
                    glyph_y = mesh_local.y
            except Exception:
                pass
        if glyph_y is not None:
            glyph_edges.append((glyph_y, i))

    if not glyph_edges:
        return None, None

    # Sort by Y so we can do interval lookup
    glyph_edges.sort(key=lambda e: e[0])

    # A click between edge[i] and edge[i+1] belongs to glyph i.
    # A click past the last edge belongs to the last glyph.
    # A click before the first edge belongs to the first glyph.
    best_idx = glyph_edges[0][1]  # default: first glyph
    for j in range(len(glyph_edges)):
        if local_pt.y >= glyph_edges[j][0]:
            best_idx = glyph_edges[j][1]
        else:
            break

    if best_idx < 0:
        return None, None

    # Map glyph index → string index.  Spaces (bIsVisible=false) are
    # skipped in CharacterKernings/Meshes, so we count visible chars.
    visible_idx = 0
    flat = text.replace('\n', '')
    letter = '?'
    for ch_pos, ch in enumerate(flat):
        if ch == ' ':
            continue  # spaces have no kerning component
        if visible_idx == best_idx:
            letter = ch
            best_idx = ch_pos  # return string index, not glyph index
            break
        visible_idx += 1

    return best_idx, letter


def _resolve_char_fixed_width(local_pt, text_content):
    """
    Fallback: fixed-width grid (CHAR_WIDTH=50, CHAR_HEIGHT=50).
    Returns (char_index, letter, col, row).
    """
    CHAR_WIDTH  = 50.0
    CHAR_HEIGHT = 50.0
    col = int(local_pt.y / CHAR_WIDTH)
    row = int(-local_pt.z / CHAR_HEIGHT)

    letter = '?'
    char_index = -1
    if text_content:
        lines = text_content.split('\n')
        if 0 <= row < len(lines):
            line = lines[row]
            if 0 <= col < len(line):
                letter = line[col]
                # Flat index across all lines
                char_index = sum(len(lines[r]) for r in range(row)) + col
    return char_index, letter, col, row


def _world_to_local(actor, world_pt):
    """Transform *world_pt* into *actor*'s local space."""
    import math
    try:
        from unreal_engine.classes import KismetMathLibrary
        return KismetMathLibrary.InverseTransformLocation(
            actor.get_actor_transform(), world_pt)
    except Exception:
        pass
    try:
        loc = actor.get_actor_location()
        rot = actor.get_actor_rotation()
        delta = FVector(world_pt.x - loc.x,
                        world_pt.y - loc.y,
                        world_pt.z - loc.z)
        yaw   = math.radians(-rot.yaw)
        pitch = math.radians(-rot.pitch)
        roll  = math.radians(-rot.roll)
        cy, sy = math.cos(yaw), math.sin(yaw)
        x1 =  cy * delta.x + sy * delta.y
        y1 = -sy * delta.x + cy * delta.y
        z1 = delta.z
        cp, sp = math.cos(pitch), math.sin(pitch)
        x2 =  cp * x1 - sp * z1
        y2 = y1
        z2 =  sp * x1 + cp * z1
        cr, sr = math.cos(roll), math.sin(roll)
        return FVector(x2, cr * y2 + sr * z2, -sr * y2 + cr * z2)
    except Exception as e:
        _log(f'text3d_click: _world_to_local failed: {e}')
        return None


def _log_click_on_actor_from_hit(actor, hit, text_content=None):
    """
    Given a pre-resolved FHitResult on *actor*, resolve the clicked
    character and log it.

    Two strategies, tried in order:
      1. **CharacterMeshes** — use Text3DComponent.CharacterMeshes (one
         child mesh per glyph) for pixel-accurate hit detection on
         proportional fonts.
      2. **Fixed-width grid** — fall back to CHAR_WIDTH=50 / CHAR_HEIGHT=50
         monospace approximation.

    Both produce a per-letter log entry including the exact letter, its
    index in the string, and local-space coordinates (useful for
    computing cursor insertion position).
    """
    import math

    world_pt = hit.impact_point

    # Read text from the actor if not passed in
    if text_content is None:
        try:
            t3d = actor.get_actor_component('Text3DComponent')
            if t3d:
                text_content = str(t3d.Text or '')
        except Exception:
            text_content = ''

    # Strategy 1: CharacterMeshes (proportional-accurate)
    mesh_idx, mesh_letter = _resolve_char_from_meshes(actor, hit)

    # Strategy 2: fixed-width fallback
    local_pt = _world_to_local(actor, world_pt)
    fw_idx, fw_letter, fw_col, fw_row = (-1, '?', -1, -1)
    if local_pt is not None:
        fw_idx, fw_letter, fw_col, fw_row = _resolve_char_fixed_width(
            local_pt, text_content)

    # Pick the best result
    if mesh_idx is not None and mesh_idx >= 0:
        method = 'CharacterMeshes'
        letter = mesh_letter
        idx    = mesh_idx
    else:
        method = 'fixed-width'
        letter = fw_letter
        idx    = fw_idx

    local_str = ''
    if local_pt is not None:
        local_str = f'local=({local_pt.y:.1f},{local_pt.z:.1f})  '

    _log(
        f'text3d_click: letter="{letter}"  index={idx}  '
        f'method={method}  '
        f'actor={actor.get_name()}  text="{text_content}"  '
        f'{local_str}'
        f'world=({world_pt.x:.1f},{world_pt.y:.1f},{world_pt.z:.1f})'
    )


def _spawn_highlight_box(world):
    """Spawn a translucent cube used as a selection-highlight rectangle.

    The blinking insertion caret is owned by PyActorText3D's singleton
    PyActorCursor — see pyactor_cursor.py.  This helper is only for the
    selection-highlight pool (multiple coexisting boxes, no blink)."""
    try:
        from unreal_engine.classes import StaticMeshActor, StaticMesh, Material
        from unreal_engine.enums import EComponentMobility

        actor = world.actor_spawn(StaticMeshActor)
        smc   = actor.StaticMeshComponent
        cube  = ue.load_object(StaticMesh, '/Engine/BasicShapes/Cube.Cube')
        smc.SetStaticMesh(cube)
        smc.SetMobility(EComponentMobility.Movable)

        # Try translucent material, fall back to any available
        mid = None
        for mat_path in ('/Game/Materials/M_Color_Translucent.M_Color_Translucent',
                         '/Game/Materials/M_TextureUnlit.M_TextureUnlit',
                         '/Game/Materials/M_Icon.M_Icon'):
            try:
                mat = ue.load_object(Material, mat_path)
                mid = smc.create_material_instance_dynamic(mat)
                break
            except Exception:
                continue
        if mid is not None:
            smc.set_material(0, mid)

        # Thin vertical bar: width=2.5 UU, height=50 UU, depth=1 UU
        actor.set_actor_scale(FVector(0.01, 0.025, 0.5))
        # Disable collision so click-traces pass through the cursor itself
        try:
            actor.SetActorEnableCollision(False)
        except Exception:
            pass
        actor.SetActorHiddenInGame(True)
        return actor, mid
    except Exception as e:
        _log(f'text3d_click: cursor spawn failed: {e}')
        return None, None


def test_text3d_click(uobject=None, input_manager=None, location=None, base_y=0):
    """
    Spawn a Text3D actor with known string "ABCDEFGHIJ" and a 3x3 test table.
    Returns (single_actor, table_renderer).

    uobject       — the PyActor UObject (self.uobject from Main); used for
                    get_hit_result_under_cursor traces.
    input_manager — self.input from Main; used for bind_press/bind_release
                    on LeftMouseButton.
    location      — FVector spawn position. Defaults to FVector(400, base_y, 150).
    base_y        — used only when *location* is None; lets the test_spawn_all
                    dispatcher place this band sequentially.

    A PyActorGlobalClick singleton is spawned to own the per-frame work
    (keyboard poll, caret blink, click dispatch). Main.tick does NOT need to
    forward delta_time anywhere.

    Re-call from PIE console at any position:
        from test_spawn import test_text3d_click
        from unreal_engine import FVector
        a, t = test_text3d_click(uobject, input_manager, FVector(500, 200, 150))

    BP_Cell requirements:
      - Text3DComponent -> Generate Hit Events = ON
      - Collision response to WorldDynamic = Block
    """
    from ue_spawn import spawn_blueprint, spawn_table_actor

    if location is None:
        location = FVector(400, base_y, 150)

    _log('--- test_text3d_click ---')
    _log(f'Spawning at {location}  (table at Y+400)')
    _log('BP_Cell requirement: Text3DComponent -> Generate Hit Events = ON')

    # Single-string actor: "ABCDEFGHIJ"
    single_actor = None
    try:
        single_actor = spawn_blueprint(
            '/Game/Blueprints/Assets/BP_Cell.BP_Cell',
            location=location,
        )
        if single_actor:
            t3d = single_actor.get_actor_component('Text3DComponent')
            if t3d:
                t3d.Text = 'ABCDEFGHIJ'
                # Enable collision for trace detection
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
                _log('text3d_click: WARNING - no Text3DComponent found on BP_Cell actor')
            # Also try enabling collision on the actor root
            try:
                single_actor.SetActorEnableCollision(True)
            except Exception:
                pass
    except Exception as e:
        _log(f'text3d_click: single actor spawn failed: {e}')

    # 3x3x3 test table — uses spawn_table_actor so the renderer's gridline
    # resize controller is ticked every frame (LMB-drag a gridline to resize
    # row/col/slice; cursor changes on hover).
    SLICE_SPACING = 600.0
    table_renderer = None
    try:
        from nd_table.ndtable import Table
        t = Table(shape=(3, 3, 3))
        for i in range(3):
            for j in range(3):
                for k in range(3):
                    t[(i, j, k)] = f'r{i}c{j}s{k}'
        # Front slice (k=0) keeps the original "Col A / Hello / Click" content
        # used by the typing test for click-to-edit.
        t[(0, 0, 0)] = 'Col A'; t[(0, 1, 0)] = 'Col B'; t[(0, 2, 0)] = 'Col C'
        t[(1, 0, 0)] = 'Hello'; t[(1, 1, 0)] = 'World'; t[(1, 2, 0)] = '123'
        t[(2, 0, 0)] = 'Click'; t[(2, 1, 0)] = 'Me';    t[(2, 2, 0)] = '!'

        table_actor = spawn_table_actor(
            t,
            location=FVector(location.x, location.y + 400, location.z),
            enable_resize=True,
        )
        if table_actor is not None:
            proxy = table_actor.get_py_proxy()
            if proxy is not None and proxy.renderer is not None:
                # Large slice (depth/layer) spacing — push k=0,1,2 apart
                # along the depth axis so each layer is clearly visible.
                proxy.renderer.min_depth = SLICE_SPACING
                proxy.renderer.recompute_layout()
                table_renderer = proxy.renderer
        if table_renderer is not None:
            _log(f'text3d_click: spawned 3D resizable table '
                 f'({len(table_renderer.cell_actors)} cells, '
                 f'slice spacing={SLICE_SPACING:.0f})')
    except Exception as e:
        _log(f'text3d_click: table spawn failed: {e}')

    # Build watched dict: actor → text content
    watched = {}   # actor → str (text shown by that actor's Text3DComponent)
    # Reverse-lookup: cell actor → owning table renderer. Used on unfocus
    # to call renderer.recompute_layout() so the table refits the new
    # text content (skipped when the renderer's auto_size is False).
    watched_renderer = {}
    if single_actor:
        watched[single_actor] = 'ABCDEFGHIJ'
    if table_renderer and hasattr(table_renderer, 'cell_actors'):
        for idx, cell_actor in table_renderer.cell_actors.items():
            cell_text = ''
            try:
                t3d = cell_actor.get_actor_component('Text3DComponent')
                if t3d:
                    cell_text = str(t3d.Text)
            except Exception:
                cell_text = f'cell{idx}'
            watched[cell_actor] = cell_text
            watched_renderer[cell_actor] = table_renderer

    # Configure player controller for click traces
    # Use ECC_Visibility (same as gizmo) — most objects respond to it by default.
    # ECC_WorldDynamic requires explicit collision response on the BP_Cell.
    _pc = None
    try:
        _pc = ue.get_player_controller(0)
    except Exception:
        pass
    if _pc is None and uobject is not None:
        try:
            _pc = uobject.get_player_controller()
        except Exception:
            pass
    if _pc is not None:
        try:
            _pc.bEnableClickEvents     = True
            _pc.bEnableMouseOverEvents = True
            _pc.CurrentClickTraceChannel = ECollisionChannel.ECC_Visibility
            _log('text3d_click: player controller configured '
                 '(ClickEvents=ON, MouseOverEvents=ON, '
                 'TraceChannel=ECC_Visibility)')
        except Exception as e:
            _log(f'text3d_click: WARNING — could not configure player controller: {e}')
    else:
        _log('text3d_click: WARNING — no player controller found')

    # Mouse state via input_manager.bind_press (same as gizmo)
    # FKey doesn't exist in this UEP build — use the HotkeyManager binding.
    _state = {'down': False}

    if input_manager is not None:
        def _press():   _state['down'] = True
        def _release(): _state['down'] = False
        input_manager.bind_press('LeftMouseButton',   _press)
        input_manager.bind_release('LeftMouseButton', _release)
        _log('text3d_click: mouse bindings registered via input_manager')
    else:
        _log('text3d_click: WARNING — no input_manager provided; pass self.input from Main.begin_play')

    # trace_obj is used for get_hit_result_under_cursor (must be a UObject
    # with that method — same as gizmo uses self.uobject)
    _trace_obj = uobject

    # Insertion cursor — single shared PyActorCursor managed by
    # PyActorText3D (class-level singleton).  See pyactor_cursor.py.
    from pyactor_text3d import PyActorText3D as _PyActorText3D

    # Focus / typing state
    # actor: the Text3D actor currently being edited (None when unfocused)
    # string_idx: insertion index within the actor's full text string (caret)
    # anchor: other end of selection; anchor == string_idx means no selection
    _focus_state = {'actor': None, 'string_idx': 0, 'anchor': 0}

    # Mirror focus changes to PyActorGlobalClick so other systems (e.g.
    # PyPawnDrone WASD) can suppress their input while typing. Imported
    # here rather than at module load to avoid hard-failing test_spawn if
    # the pyactor_global_click module has issues during dev iteration.
    try:
        from pyactor_global_click import PyActorGlobalClick as _PyActorGlobalClick
    except Exception:
        _PyActorGlobalClick = None

    def _set_focused_actor(actor):
        """Single mutation point for _focus_state['actor']. Refits the
        previous actor's table when leaving focus (skipped when the
        renderer's auto_size is False), then mirrors the new value to
        PyActorGlobalClick so PyPawnDrone (WASD) and friends can
        suppress their input while typing."""
        prev = _focus_state['actor']
        _focus_state['actor'] = actor
        if prev is not None and prev is not actor:
            renderer = watched_renderer.get(prev)
            if renderer is not None and getattr(renderer, 'auto_size', True):
                try:
                    renderer.recompute_layout()
                except Exception as e:
                    _log(f'text3d_click: recompute_layout failed: {e}')
        if _PyActorGlobalClick is not None:
            _PyActorGlobalClick.set_focused_actor(actor)

    def _sel_range():
        """Return (start, end) of the selection sorted. start==end means no sel."""
        a = _focus_state['anchor']
        c = _focus_state['string_idx']
        return (a, c) if a <= c else (c, a)

    def _has_sel():
        return _focus_state['anchor'] != _focus_state['string_idx']

    def _collapse_sel():
        _focus_state['anchor'] = _focus_state['string_idx']

    def _set_caret(idx, extend_selection=False):
        """Move caret to idx. If extend_selection=False, anchor follows caret."""
        _focus_state['string_idx'] = idx
        if not extend_selection:
            _focus_state['anchor'] = idx

    def _string_idx_to_glyph(text, sidx):
        """Count visible (non-space, non-newline) chars in text[:sidx]."""
        sidx = max(0, min(sidx, len(text)))
        return sum(1 for c in text[:sidx] if c not in ' \n')

    def _glyph_to_string_idx(text, tg):
        """Return the string index of the tg-th visible char (or len(text))."""
        count = 0
        for i, c in enumerate(text):
            if count == tg:
                return i
            if c not in ' \n':
                count += 1
        return len(text)

    def _hide_cursor():
        _PyActorText3D.hide_cursor()

    # Pool of translucent boxes used to render multi-segment selection highlights.
    _highlight_actors = []

    def _ensure_highlight(i):
        """Lazily grow the highlight pool to at least i+1 actors."""
        while len(_highlight_actors) <= i:
            a, _ = _spawn_highlight_box(get_world())
            if a is None:
                return None
            try:
                a.SetActorLabel(f'TextSelHighlight_{len(_highlight_actors)}')
            except Exception:
                pass
            _highlight_actors.append(a)
        return _highlight_actors[i]

    def _hide_highlights():
        for a in _highlight_actors:
            try:
                a.SetActorHiddenInGame(True)
            except Exception:
                pass

    def _unfocus():
        _set_focused_actor(None)
        _focus_state['string_idx'] = 0
        _focus_state['anchor']     = 0
        _hide_cursor()
        _hide_highlights()

    def _get_cursor_placement(actor, target_glyph):
        """Delegate to PyActorText3D.compute_placement (single source of
        truth for caret/highlight geometry)."""
        return _PyActorText3D.compute_placement(actor, target_glyph)

    def _show_cursor_at_glyph(actor, target_glyph):
        """Move the singleton caret to target_glyph. Returns True on success."""
        return _PyActorText3D.show_cursor_at(actor, target_glyph)

    def _render_highlight_segment(pool_idx, actor, text, seg_start, seg_end):
        """Render one highlight box for string range [seg_start, seg_end).
        Assumes the segment is on a single line."""
        box = _ensure_highlight(pool_idx)
        if box is None:
            return
        sg = _string_idx_to_glyph(text, seg_start)
        eg = _string_idx_to_glyph(text, seg_end)
        left  = _get_cursor_placement(actor, sg)
        right = _get_cursor_placement(actor, eg)
        if left is None or right is None:
            try:
                box.SetActorHiddenInGame(True)
            except Exception:
                pass
            return
        lwp, lscale, lrot = left
        rwp, _, _ = right
        # Width between the two caret positions.  Expand the box scale Y so
        # it covers that span; keep X (depth) thin and Z (height) same as caret.
        dy = rwp.y - lwp.y
        dx = rwp.x - lwp.x
        span_uu = (dx * dx + dy * dy) ** 0.5
        if span_uu < 1.0:
            try:
                box.SetActorHiddenInGame(True)
            except Exception:
                pass
            return
        # Center box between left and right, along the actor's local Y.
        mid_wp = FVector(
            (lwp.x + rwp.x) * 0.5,
            (lwp.y + rwp.y) * 0.5,
            (lwp.z + rwp.z) * 0.5,
        )
        try:
            # Cube is 100 UU base.  Scale.y = span_uu/100 gives correct width.
            box.set_actor_scale(FVector(0.01, span_uu / 100.0, lscale.z))
        except Exception:
            pass
        box.set_actor_location(mid_wp)
        box.set_actor_rotation(lrot)
        box.SetActorHiddenInGame(False)

    def _update_highlight():
        """Rebuild highlight boxes based on current selection."""
        _hide_highlights()
        actor = _focus_state['actor']
        if actor is None or not _has_sel():
            return
        t3d = None
        try:
            t3d = actor.get_actor_component('Text3DComponent')
        except Exception:
            return
        if t3d is None:
            return
        try:
            text = str(t3d.Text or '')
        except Exception:
            return
        start, end = _sel_range()
        # Split selection by newlines so each line-segment gets its own box.
        pool_idx = 0
        s = start
        while s < end:
            nl = text.find('\n', s, end)
            seg_end = end if nl == -1 else nl
            if seg_end > s:
                _render_highlight_segment(pool_idx, actor, text, s, seg_end)
                pool_idx += 1
            s = seg_end + 1 if nl != -1 else end

    def _position_cursor(hit_actor, hit):
        """Derive target_glyph from a click hit, move cursor, set focus."""
        if hit_actor is None:
            return

        t3d = None
        try:
            t3d = hit_actor.get_actor_component('Text3DComponent')
        except Exception:
            pass

        text = ''
        if t3d is not None:
            try:
                text = str(t3d.Text or '')
            except Exception:
                pass

        kernings = None
        meshes   = None
        if t3d is not None:
            try:
                kernings = t3d.CharacterKernings
            except Exception:
                pass
            try:
                meshes = t3d.CharacterMeshes
            except Exception:
                pass

        # No kernings — drop the caret directly at the click point via
        # the singleton cursor's move_to (skipping placement math entirely).
        if not kernings or len(kernings) == 0:
            cursor_proxy = _PyActorText3D._get_or_spawn_cursor(hit_actor)
            if cursor_proxy is not None:
                try:
                    cursor_proxy.move_to(
                        hit.impact_point,
                        FVector(0.01, 0.04, 0.5),
                        hit_actor.get_actor_rotation())
                except Exception:
                    pass
            _set_focused_actor(hit_actor)
            _focus_state['string_idx'] = len(text)
            _focus_state['anchor']     = len(text)
            _hide_highlights()
            return

        # Compute clicked glyph + left/right side from the hit.
        local_pt = _world_to_local(hit_actor, hit.impact_point)
        clicked_glyph = 0
        side = 'right'

        if local_pt is not None:
            glyph_edges = []
            for i in range(len(kernings)):
                if kernings[i] is not None:
                    try:
                        rel = kernings[i].get_relative_location()
                        glyph_edges.append((rel.y, i))
                    except Exception:
                        pass
            glyph_edges.sort(key=lambda e: e[0])
            if glyph_edges:
                clicked_glyph = glyph_edges[0][1]
                for edge_y, gi in glyph_edges:
                    if local_pt.y >= edge_y:
                        clicked_glyph = gi
                    else:
                        break

            glyph_w_local = 50.0
            if (meshes is not None
                    and 0 <= clicked_glyph < len(meshes)
                    and meshes[clicked_glyph] is not None):
                try:
                    _, e = meshes[clicked_glyph].GetComponentBounds()
                    glyph_w_local = e.y * 2.0
                except Exception:
                    pass

            if (0 <= clicked_glyph < len(kernings)
                    and kernings[clicked_glyph] is not None):
                try:
                    r = kernings[clicked_glyph].get_relative_location()
                    mid_y = r.y + glyph_w_local / 2.0
                    side  = 'left' if local_pt.y < mid_y else 'right'
                except Exception:
                    pass

        target_glyph = clicked_glyph if side == 'left' else clicked_glyph + 1

        if not _show_cursor_at_glyph(hit_actor, target_glyph):
            return

        _set_focused_actor(hit_actor)
        new_idx = _glyph_to_string_idx(text, target_glyph)
        _focus_state['string_idx'] = new_idx
        _focus_state['anchor']     = new_idx
        _hide_highlights()
        # If the previous focus was in an auto-sizing table, that table
        # just refit and may have shifted hit_actor's position. Re-show
        # the cursor so it tracks the new cell location.
        _show_cursor_at_glyph(hit_actor, target_glyph)
        _log(f'text3d_click: cursor snap clicked={clicked_glyph} '
             f'side={side} → {target_glyph}  '
             f'focus string_idx={new_idx}')

    def _handle_typed_char(ch):
        """Insert/delete at cursor. ch='\\b'=backspace, '\\n'=newline, else=literal."""
        actor = _focus_state['actor']
        if actor is None:
            return
        t3d = None
        try:
            t3d = actor.get_actor_component('Text3DComponent')
        except Exception:
            return
        if t3d is None:
            return

        try:
            text = str(t3d.Text or '')
        except Exception:
            text = ''

        # If there is a selection, replace it (delete it; then insert if not backspace).
        if _has_sel():
            start, end = _sel_range()
            text = text[:start] + text[end:]
            idx = start
            _focus_state['string_idx'] = idx
            _focus_state['anchor']     = idx
            if ch == '\b':
                # Selection-backspace just deletes the selection, no further delete.
                try:
                    t3d.Text = text
                except Exception as e:
                    _log(f'text3d_click: failed to set text: {e}')
                    return
                watched[actor] = text
                _show_cursor_at_glyph(actor, _string_idx_to_glyph(text, idx))
                _update_highlight()
                return

        idx = max(0, min(_focus_state['string_idx'], len(text)))

        if ch == '\b':
            if idx == 0:
                return
            text = text[:idx - 1] + text[idx:]
            idx -= 1
        else:
            text = text[:idx] + ch + text[idx:]
            idx += 1

        try:
            t3d.Text = text
        except Exception as e:
            _log(f'text3d_click: failed to set text: {e}')
            return

        watched[actor] = text
        _focus_state['string_idx'] = idx
        _focus_state['anchor']     = idx

        target_glyph = _string_idx_to_glyph(text, idx)
        _show_cursor_at_glyph(actor, target_glyph)
        _update_highlight()

    # Notepad-style typing via direct Windows keyboard poll
    # Bypasses UE's input routing so we get layout-correct translation
    # (Shift, CapsLock, AltGr, dead keys) exactly like notepad.exe.
    # Runs alongside HotkeyManager bindings in main.py without disturbing them.
    try:
        import ctypes as _ctypes
        _user32 = _ctypes.WinDLL('user32', use_last_error=True)
        _kernel32 = _ctypes.WinDLL('kernel32', use_last_error=True)
        _user32.GetAsyncKeyState.argtypes = [_ctypes.c_int]
        _user32.GetAsyncKeyState.restype  = _ctypes.c_short
        _user32.GetKeyState.argtypes      = [_ctypes.c_int]
        _user32.GetKeyState.restype       = _ctypes.c_short
        _user32.MapVirtualKeyW.argtypes   = [_ctypes.c_uint, _ctypes.c_uint]
        _user32.MapVirtualKeyW.restype    = _ctypes.c_uint
        _user32.ToUnicode.argtypes = [
            _ctypes.c_uint, _ctypes.c_uint,
            _ctypes.POINTER(_ctypes.c_ubyte), _ctypes.c_wchar_p,
            _ctypes.c_int, _ctypes.c_uint,
        ]
        _user32.ToUnicode.restype = _ctypes.c_int
        # Clipboard API
        _user32.OpenClipboard.argtypes    = [_ctypes.c_void_p]
        _user32.OpenClipboard.restype     = _ctypes.c_int
        _user32.CloseClipboard.argtypes   = []
        _user32.CloseClipboard.restype    = _ctypes.c_int
        _user32.EmptyClipboard.argtypes   = []
        _user32.EmptyClipboard.restype    = _ctypes.c_int
        _user32.GetClipboardData.argtypes = [_ctypes.c_uint]
        _user32.GetClipboardData.restype  = _ctypes.c_void_p
        _user32.SetClipboardData.argtypes = [_ctypes.c_uint, _ctypes.c_void_p]
        _user32.SetClipboardData.restype  = _ctypes.c_void_p
        _user32.IsClipboardFormatAvailable.argtypes = [_ctypes.c_uint]
        _user32.IsClipboardFormatAvailable.restype  = _ctypes.c_int
        _kernel32.GlobalAlloc.argtypes  = [_ctypes.c_uint, _ctypes.c_size_t]
        _kernel32.GlobalAlloc.restype   = _ctypes.c_void_p
        _kernel32.GlobalLock.argtypes   = [_ctypes.c_void_p]
        _kernel32.GlobalLock.restype    = _ctypes.c_void_p
        _kernel32.GlobalUnlock.argtypes = [_ctypes.c_void_p]
        _kernel32.GlobalUnlock.restype  = _ctypes.c_int
        _kernel32.GlobalSize.argtypes   = [_ctypes.c_void_p]
        _kernel32.GlobalSize.restype    = _ctypes.c_size_t
        _WIN32_TYPING_OK = True
    except Exception as _win_err:
        _WIN32_TYPING_OK = False
        _user32 = None
        _kernel32 = None
        _ctypes = None
        _log(f'text3d_click: ctypes typing unavailable ({_win_err})')

    _prev_vk_down = bytearray(256)

    # Standard Windows clipboard format IDs
    _CF_UNICODETEXT = 13

    def _build_kb_state():
        """256-byte keyboard state for ToUnicode. High bit=down, low bit=toggle."""
        buf = (_ctypes.c_ubyte * 256)()
        for vk in range(256):
            if _user32.GetAsyncKeyState(vk) & 0x8000:
                buf[vk] = 0x80
        # Toggle bits for CapsLock / NumLock / ScrollLock
        for tvk in (0x14, 0x90, 0x91):
            if _user32.GetKeyState(tvk) & 0x0001:
                buf[tvk] |= 0x01
        return buf

    def _ctrl_down():
        if not _WIN32_TYPING_OK:
            return False
        return (_user32.GetAsyncKeyState(0x11) & 0x8000) != 0   # VK_CONTROL

    def _shift_held():
        if not _WIN32_TYPING_OK:
            return False
        return (_user32.GetAsyncKeyState(0x10) & 0x8000) != 0   # VK_SHIFT

    def _alt_down():
        if not _WIN32_TYPING_OK:
            return False
        return (_user32.GetAsyncKeyState(0x12) & 0x8000) != 0   # VK_MENU

    def _win_down():
        if not _WIN32_TYPING_OK:
            return False
        return ((_user32.GetAsyncKeyState(0x5B) & 0x8000) != 0   # VK_LWIN
                or (_user32.GetAsyncKeyState(0x5C) & 0x8000) != 0)  # VK_RWIN

    # ---------------- Navigation ----------------

    def _is_word_char(c):
        return c.isalnum() or c == '_'

    def _word_boundary(text, idx, direction):
        """Move idx to the next word boundary in `direction` (+1 or -1)."""
        n = len(text)
        idx = max(0, min(idx, n))
        if direction > 0:
            # Skip any whitespace/punct, then skip word chars
            while idx < n and not _is_word_char(text[idx]):
                idx += 1
            while idx < n and _is_word_char(text[idx]):
                idx += 1
        else:
            idx = max(0, idx - 1)
            while idx > 0 and not _is_word_char(text[idx]):
                idx -= 1
            while idx > 0 and _is_word_char(text[idx - 1]):
                idx -= 1
        return idx

    def _line_edge(text, idx, direction):
        """Move idx to start (-1) or end (+1) of its line."""
        n = len(text)
        idx = max(0, min(idx, n))
        if direction < 0:
            nl = text.rfind('\n', 0, idx)
            return 0 if nl == -1 else nl + 1
        nl = text.find('\n', idx)
        return n if nl == -1 else nl

    def _line_delta(text, idx, direction):
        """Move idx up (-1) or down (+1) one line, preserving column."""
        n = len(text)
        idx = max(0, min(idx, n))
        line_start = _line_edge(text, idx, -1)
        col = idx - line_start
        if direction < 0:
            if line_start == 0:
                return 0
            prev_end   = line_start - 1
            prev_start = _line_edge(text, prev_end, -1)
            return min(prev_start + col, prev_end)
        # direction > 0
        line_end = _line_edge(text, idx, +1)
        if line_end == n:
            return n
        next_start = line_end + 1
        next_end   = _line_edge(text, next_start, +1)
        return min(next_start + col, next_end)

    def _move_caret_to(new_idx, extend):
        """Set caret, optionally extending selection; then refresh cursor + highlight."""
        actor = _focus_state['actor']
        if actor is None:
            return
        t3d = None
        try:
            t3d = actor.get_actor_component('Text3DComponent')
        except Exception:
            pass
        text = ''
        if t3d is not None:
            try:
                text = str(t3d.Text or '')
            except Exception:
                pass
        new_idx = max(0, min(new_idx, len(text)))
        _set_caret(new_idx, extend_selection=extend)
        _show_cursor_at_glyph(actor, _string_idx_to_glyph(text, new_idx))
        _update_highlight()

    # ---------------- Clipboard ----------------

    def _clipboard_get_text():
        if not _WIN32_TYPING_OK:
            return None
        try:
            if not _user32.OpenClipboard(0):
                return None
            try:
                if not _user32.IsClipboardFormatAvailable(_CF_UNICODETEXT):
                    return None
                h = _user32.GetClipboardData(_CF_UNICODETEXT)
                if not h:
                    return None
                p = _kernel32.GlobalLock(h)
                if not p:
                    return None
                try:
                    return _ctypes.c_wchar_p(p).value
                finally:
                    _kernel32.GlobalUnlock(h)
            finally:
                _user32.CloseClipboard()
        except Exception as e:
            _log(f'text3d_click: clipboard read failed: {e}')
            return None

    def _clipboard_set_text(text):
        if not _WIN32_TYPING_OK or text is None:
            return False
        try:
            if not _user32.OpenClipboard(0):
                return False
            try:
                _user32.EmptyClipboard()
                GMEM_MOVEABLE = 0x0002
                data = text.encode('utf-16-le') + b'\x00\x00'
                size = len(data)
                h = _kernel32.GlobalAlloc(GMEM_MOVEABLE, size)
                if not h:
                    return False
                p = _kernel32.GlobalLock(h)
                if not p:
                    return False
                _ctypes.memmove(p, data, size)
                _kernel32.GlobalUnlock(h)
                # After SetClipboardData, the system owns the handle.
                return bool(_user32.SetClipboardData(_CF_UNICODETEXT, h))
            finally:
                _user32.CloseClipboard()
        except Exception as e:
            _log(f'text3d_click: clipboard write failed: {e}')
            return False

    def _clipboard_get_image():
        try:
            from PIL import ImageGrab, Image as PILImage
            img = ImageGrab.grabclipboard()
            if isinstance(img, PILImage.Image):
                return img
            return None
        except Exception as e:
            _log(f'text3d_click: ImageGrab failed: {e}')
            return None

    # ---------------- Actions ----------------

    def _delete_selection():
        """Delete selected text in focused actor. Returns True if anything deleted."""
        actor = _focus_state['actor']
        if actor is None or not _has_sel():
            return False
        t3d = None
        try:
            t3d = actor.get_actor_component('Text3DComponent')
        except Exception:
            return False
        if t3d is None:
            return False
        try:
            text = str(t3d.Text or '')
        except Exception:
            return False
        start, end = _sel_range()
        new_text = text[:start] + text[end:]
        try:
            t3d.Text = new_text
        except Exception as e:
            _log(f'text3d_click: delete_selection failed: {e}')
            return False
        watched[actor] = new_text
        _focus_state['string_idx'] = start
        _focus_state['anchor']     = start
        _show_cursor_at_glyph(actor, _string_idx_to_glyph(new_text, start))
        _update_highlight()
        return True

    def _select_all():
        actor = _focus_state['actor']
        if actor is None:
            return
        t3d = None
        try:
            t3d = actor.get_actor_component('Text3DComponent')
        except Exception:
            return
        if t3d is None:
            return
        try:
            text = str(t3d.Text or '')
        except Exception:
            return
        _focus_state['anchor']     = 0
        _focus_state['string_idx'] = len(text)
        _show_cursor_at_glyph(actor, _string_idx_to_glyph(text, len(text)))
        _update_highlight()

    def _copy():
        if not _has_sel():
            return
        actor = _focus_state['actor']
        if actor is None:
            return
        t3d = None
        try:
            t3d = actor.get_actor_component('Text3DComponent')
        except Exception:
            return
        if t3d is None:
            return
        try:
            text = str(t3d.Text or '')
        except Exception:
            return
        s, e = _sel_range()
        _clipboard_set_text(text[s:e])

    def _cut():
        if not _has_sel():
            return
        _copy()
        _delete_selection()

    def _paste():
        if _focus_state['actor'] is None:
            return
        # Image first — if clipboard has a bitmap, inline-paste it.
        img = _clipboard_get_image()
        if img is not None:
            _paste_image(img)
            return
        # Otherwise paste text at caret, replacing any selection.
        clip = _clipboard_get_text()
        if not clip:
            return
        if _has_sel():
            _delete_selection()
        # Feed characters one-by-one so the existing path (which updates
        # text, caret, cursor, watched) does the heavy lifting.
        for c in clip:
            if c == '\r':
                continue   # CRLF → LF
            _handle_typed_char(c)

    def _delete_forward():
        actor = _focus_state['actor']
        if actor is None:
            return
        if _has_sel():
            _delete_selection()
            return
        t3d = None
        try:
            t3d = actor.get_actor_component('Text3DComponent')
        except Exception:
            return
        if t3d is None:
            return
        try:
            text = str(t3d.Text or '')
        except Exception:
            return
        idx = _focus_state['string_idx']
        if idx >= len(text):
            return
        new_text = text[:idx] + text[idx + 1:]
        try:
            t3d.Text = new_text
        except Exception:
            return
        watched[actor] = new_text
        _show_cursor_at_glyph(actor, _string_idx_to_glyph(new_text, idx))
        _update_highlight()

    def _cycle_focus(direction=1):
        """Ctrl+Tab — move focus to the next (or previous) watched text actor."""
        if not watched:
            return
        ordered = list(watched.keys())
        current = _focus_state['actor']
        if current in ordered:
            i = (ordered.index(current) + direction) % len(ordered)
        else:
            i = 0
        new_actor = ordered[i]
        new_text  = watched.get(new_actor, '')
        _set_focused_actor(new_actor)
        _focus_state['string_idx'] = len(new_text)
        _focus_state['anchor']     = len(new_text)
        _show_cursor_at_glyph(new_actor, _string_idx_to_glyph(new_text, len(new_text)))
        _hide_highlights()

    # ---------------- Inline image paste ----------------

    # Track inline images spawned into each actor so they can be repositioned
    # after text edits.  Each entry: (actor, image_actor, placeholder_start,
    # placeholder_len, img_w_uu, img_h_uu).
    _inline_images = []

    def _paste_image(pil_img):
        """Inline-paste a PIL image into the focused Text3D at the caret.
        Image is scaled so its height matches the text's line height, then
        space characters are inserted to reserve horizontal room.  The image
        actor is placed over the reserved spaces."""
        actor = _focus_state['actor']
        if actor is None:
            return
        t3d = None
        try:
            t3d = actor.get_actor_component('Text3DComponent')
        except Exception:
            return
        if t3d is None:
            return
        try:
            text = str(t3d.Text or '')
        except Exception:
            text = ''

        # Measure the text's vertical extent for target image height.
        text_h = 50.0
        try:
            o, e = t3d.GetComponentBounds()
            text_h = max(text_h, e.z * 2.0 * 0.8)
        except Exception:
            pass
        # Measure average glyph width for space count.
        glyph_w = 50.0
        try:
            meshes = t3d.CharacterMeshes
            if meshes is not None:
                for m in meshes:
                    if m is None:
                        continue
                    try:
                        _, e = m.GetComponentBounds()
                        glyph_w = e.y * 2.0
                        break
                    except Exception:
                        continue
        except Exception:
            pass

        # Scale image to text height, preserving aspect ratio.
        iw, ih = float(pil_img.width), float(pil_img.height)
        if ih <= 0:
            return
        img_h_uu = text_h
        img_w_uu = iw / ih * img_h_uu
        n_spaces = max(1, int(round(img_w_uu / glyph_w)))

        # Replace any existing selection, insert placeholder spaces, set text.
        if _has_sel():
            _delete_selection()
            try:
                text = str(t3d.Text or '')
            except Exception:
                text = ''

        idx = _focus_state['string_idx']
        placeholder = ' ' * n_spaces
        new_text = text[:idx] + placeholder + text[idx:]
        try:
            t3d.Text = new_text
        except Exception as e:
            _log(f'text3d_click: paste_image set text failed: {e}')
            return
        watched[actor] = new_text

        # Spawn the image via ue_spawn.spawn_image.  It needs a file path, so
        # write the PIL buffer to a temp PNG.
        image_actor = None
        try:
            import tempfile, os as _os
            from ue_spawn import spawn_image
            tmpdir = _os.path.join(tempfile.gettempdir(), 'ue_clipboard_images')
            try:
                _os.makedirs(tmpdir, exist_ok=True)
            except Exception:
                pass
            # Unique-ish filename so we don't stomp repeated pastes.
            import time as _t
            tmp_path = _os.path.join(tmpdir, f'clip_{int(_t.time()*1000)}.png')
            pil_img.convert('RGBA').save(tmp_path, 'PNG')
            # Scale (width/100, thin, height/100) — spawn_image uses 1 px = 1 UU.
            # Override to match our target dimensions in UU.
            img_scale = FVector(img_w_uu / 100.0, 0.05, img_h_uu / 100.0)
            image_actor = spawn_image(tmp_path, scale=img_scale)
        except Exception as e:
            _log(f'text3d_click: spawn_image failed: {e}')

        # Position the image over the placeholder spaces.
        if image_actor is not None:
            try:
                mid_idx = idx + n_spaces // 2
                mid_glyph = _string_idx_to_glyph(new_text, mid_idx)
                placement = _get_cursor_placement(actor, mid_glyph)
                if placement is not None:
                    world_pt, _, rot = placement
                    image_actor.set_actor_location(world_pt)
                    image_actor.set_actor_rotation(rot)
                    image_actor.attach_to_actor(actor)
            except Exception as e:
                _log(f'text3d_click: image position failed: {e}')
            _inline_images.append(
                (actor, image_actor, idx, n_spaces, img_w_uu, img_h_uu))

        # Advance caret past the reserved spaces.
        new_idx = idx + n_spaces
        _focus_state['string_idx'] = new_idx
        _focus_state['anchor']     = new_idx
        _show_cursor_at_glyph(actor, _string_idx_to_glyph(new_text, new_idx))
        _update_highlight()

    def _on_vk_rise(vk):
        """Rising-edge handler. Dispatches shortcuts, then falls through to
        ToUnicode for ordinary character entry (notepad's WM_CHAR semantics)."""
        if _focus_state['actor'] is None:
            return

        ctrl  = _ctrl_down()
        shift = _shift_held()
        alt   = _alt_down()
        win   = _win_down()

        # Notepad parity: Alt+key (Alt+Tab window switch, Alt+Enter properties,
        # Alt+F4 close, Alt+Backspace undo, etc.) and Win+key (shell shortcuts)
        # are never text input. AltGr on European layouts reports Alt+Ctrl
        # together and DOES produce characters through ToUnicode, so the
        # `not ctrl` clause keeps that path open.
        if (alt and not ctrl) or win:
            return

        # ----- Ctrl+key shortcuts -----
        if ctrl:
            if vk == 0x41:    # A
                _select_all(); return
            if vk == 0x43:    # C
                _copy(); return
            if vk == 0x58:    # X
                _cut(); return
            if vk == 0x56:    # V
                _paste(); return
            if vk == 0x09:    # Tab
                _cycle_focus(-1 if shift else +1); return
            # Ctrl+arrow / home / end: word & doc navigation
            actor = _focus_state['actor']
            t3d = actor.get_actor_component('Text3DComponent') if actor else None
            text = str(t3d.Text or '') if t3d else ''
            idx  = _focus_state['string_idx']
            if vk == 0x25:    # Ctrl+Left  — prev word
                _move_caret_to(_word_boundary(text, idx, -1), shift); return
            if vk == 0x27:    # Ctrl+Right — next word
                _move_caret_to(_word_boundary(text, idx, +1), shift); return
            if vk == 0x24:    # Ctrl+Home  — doc start
                _move_caret_to(0, shift); return
            if vk == 0x23:    # Ctrl+End   — doc end
                _move_caret_to(len(text), shift); return

        # ----- Caret movement without Ctrl -----
        if vk in (0x25, 0x27, 0x26, 0x28, 0x24, 0x23):
            actor = _focus_state['actor']
            t3d = actor.get_actor_component('Text3DComponent') if actor else None
            text = str(t3d.Text or '') if t3d else ''
            idx  = _focus_state['string_idx']
            if vk == 0x25:    # Left
                if _has_sel() and not shift:
                    _move_caret_to(_sel_range()[0], False); return
                _move_caret_to(max(0, idx - 1), shift); return
            if vk == 0x27:    # Right
                if _has_sel() and not shift:
                    _move_caret_to(_sel_range()[1], False); return
                _move_caret_to(min(len(text), idx + 1), shift); return
            if vk == 0x26:    # Up
                _move_caret_to(_line_delta(text, idx, -1), shift); return
            if vk == 0x28:    # Down
                _move_caret_to(_line_delta(text, idx, +1), shift); return
            if vk == 0x24:    # Home
                _move_caret_to(_line_edge(text, idx, -1), shift); return
            if vk == 0x23:    # End
                _move_caret_to(_line_edge(text, idx, +1), shift); return

        # ----- Editing keys -----
        if vk == 0x08:        # VK_BACK
            _handle_typed_char('\b'); return
        if vk == 0x2E:        # VK_DELETE
            _delete_forward(); return
        if vk == 0x0D:        # VK_RETURN
            _handle_typed_char('\n'); return
        if vk == 0x09:        # VK_TAB
            _handle_typed_char('\t'); return
        if vk == 0x1B:        # VK_ESCAPE
            _unfocus(); return

        # ----- Regular character via OS keyboard layout -----
        # Ctrl+letter would otherwise produce control chars (e.g. Ctrl+B → 0x02);
        # we already handled the shortcuts we care about, so suppress the rest.
        if ctrl:
            return
        try:
            kb_state  = _build_kb_state()
            scan_code = _user32.MapVirtualKeyW(vk, 0)
            outbuf    = _ctypes.create_unicode_buffer(8)
            result    = _user32.ToUnicode(
                vk, scan_code, kb_state, outbuf, len(outbuf), 0)
        except Exception:
            return
        if result > 0:
            for c in outbuf.value[:result]:
                if c and ord(c) >= 0x20:
                    _handle_typed_char(c)

    def _poll_keyboard():
        """Call each tick. Fires character events on rising edges while focused."""
        if not _WIN32_TYPING_OK:
            return
        curr = bytearray(256)
        for vk in range(256):
            if _user32.GetAsyncKeyState(vk) & 0x8000:
                curr[vk] = 1
        if _focus_state['actor'] is not None:
            for vk in range(256):
                if curr[vk] and not _prev_vk_down[vk]:
                    _on_vk_rise(vk)
        for i in range(256):
            _prev_vk_down[i] = curr[i]

    _log('text3d_click: ctypes keyboard poll ready'
         if _WIN32_TYPING_OK else
         'text3d_click: typing disabled (ctypes unavailable)')

    # Tick function: event-driven press state + cursor hit test
    _state['fired'] = False  # ensure we fire once per press

    def tick_fn(dt):
        # Typing poll (fires char events via Win32 ToUnicode when focused)
        _poll_keyboard()

        # Caret blink is owned by the PyActorCursor singleton (its own tick).

        if _trace_obj is None and _pc is None:
            return

        currently_down = _state['down']
        fired          = _state['fired']

        if currently_down and not fired:
            # Rising edge — check which watched actor the cursor is over
            _state['fired'] = True
            hit = None
            # Try ECC_Visibility first (like gizmo), then WorldDynamic
            for channel in (ECollisionChannel.ECC_Visibility,
                            ECollisionChannel.ECC_WorldDynamic):
                for trace_src in (_trace_obj, _pc):
                    if trace_src is None:
                        continue
                    try:
                        hit = trace_src.get_hit_result_under_cursor(channel)
                        if hit is not None:
                            break
                    except Exception:
                        continue
                if hit is not None:
                    break

            hit_actor = hit.actor if hit is not None else None
            matched_actor = None
            matched_text  = None
            if hit_actor is not None:
                for w_actor, w_text in watched.items():
                    try:
                        if w_actor == hit_actor:
                            matched_actor = w_actor
                            matched_text  = w_text
                            break
                    except Exception:
                        pass

            if matched_actor is None:
                # Click off any watched text actor — unfocus + hide cursor.
                if hit_actor is not None:
                    _log(f'global_click: off-click — hit '
                         f'"{hit_actor.get_name()}" (not watched), unfocusing')
                else:
                    _log('global_click: off-click — nothing under cursor, unfocusing')
                _unfocus()
                return

            _log_click_on_actor_from_hit(matched_actor, hit, text_content=matched_text)
            _position_cursor(matched_actor, hit)

        elif not currently_down:
            _state['fired'] = False

    _log(f'text3d_click: log -> {_LOG_PATH}')

    # Hand tick_fn off to a singleton PyActor so it runs per-frame without
    # Main.tick forwarding anything. Per-text3d actors stay tick-free at the
    # global level (the per-instance PyActorText3D animation ticks are a
    # separate concern).
    try:
        from ue_spawn import spawn_pyactor
        global_actor = spawn_pyactor(
            'pyactor_global_click', 'PyActorGlobalClick',
            location=FVector(0, 0, 0),
            name='PyActorGlobalClick')
        global_actor.get_py_proxy().set_tick_fn(tick_fn)
        _log('global_click: PyActorGlobalClick spawned + tick attached')
    except Exception as e:
        _log(f'global_click: PyActorGlobalClick spawn failed: {e}')

    return single_actor, table_renderer
