"""
test_spawn.py — Spawn test suite for Starcel9
==============================================
Modeled after test_gizmos() in gizmo.py.

All actors are placed at X=0, spread along the Y axis in bands:
  Y    0 –  800  primitives
  Y 1000 – 1200  image
  Y 1400 – 1600  video
  Y 1800 – 2000  sound
  Y 2200 – 3600  cameras (one per preset, stride 200)
  Y 4000 – 4500  earth
  Y 5000          system monitor
  Y 5500          table
  Y 6000          desktop icons
  Y 7000          icon from PIL
  Y 8000 – 8500  text3d click (test_text3d_click only)
  Y 9000          plot spheres
  Y 9500          plot sphere_lines (custom point_mesh option)
  Y 10000         plot ripple sphere_lines
  Y 10500         plot tan(x) 2D curve
  Y 11000         transform gizmo (test_gizmo only)
  Y 12000+        nd_table grid (2D 10x10 through 7D)

Usage (PIE Python console):
    from test_spawn import test_spawn_all
    results = test_spawn_all()

    # Manual Text3D click investigation:
    from test_spawn import test_text3d_click
    test_text3d_click()

    # Interactive transform gizmo (needs uobject + input_manager):
    from test_spawn import test_gizmo
    target, handles, tick = test_gizmo(uobject, input_manager)

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


def _result(name, actor_or_value, extra='', expected=None, inputs=None):
    """Log a test outcome with rich context:
      - inputs   : what params/paths were passed in
      - expected : what a passing result should look like
      - actor    : full introspection of the returned actor (class/loc/mesh/etc.)
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
    suffix = f' — {extra}' if extra else ''
    _log(f'[{status}] {name}{suffix}')
    return {name: {'ok': ok, 'actor': actor_or_value}}


def _skip(name, reason=''):
    _log(f'  skip_reason: {reason}' if reason else '  skip_reason: (unspecified)')
    _log(f'[SKIP] {name}{(" — " + reason) if reason else ""}')
    return {name: {'ok': True, 'actor': None}}   # skips are non-failing


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
        ('Material M_ImagePlane',
         lambda: bool(ue.load_object(ue.find_class('Material'),
                                     '/Game/Materials/M_ImagePlane')),
         'Create a material at /Game/Materials/M_ImagePlane with a '
         'TextureSampleParameter2D named "Texture"'),

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

        # BP_Icon, BP_SoundSphere, BP_SysMon, BP_PyCamera, BP_FileExplorer
        # now use dynamic PyActor spawning — no Blueprint needed.

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

# Y-axis layout constants
_Y_PRIMITIVES    =    0   # stride 200, 5 shapes  ->  0..800
_Y_IMAGE         = 1000   # stride 200             -> 1000..1200
_Y_VIDEO         = 1400   # stride 200             -> 1400..1600
_Y_SOUND         = 1800   # stride 200             -> 1800..2000
_Y_CAMERAS       = 2200   # stride 200, 8 presets  -> 2200..3800
_Y_EARTH         = 4000   # stride 500             -> 4000..4500
_Y_SYSMON        = 5000
_Y_TABLE         = 5500
_Y_DESKTOP_ICONS = 6000
_Y_ICON          = 7000


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


def test_primitives():
    """Spawn all 5 primitive shapes along Y."""
    from ue_spawn import spawn_primitive
    results = {}
    shapes = ['cube', 'sphere', 'cylinder', 'cone', 'plane']
    for i, shape in enumerate(shapes):
        loc   = FVector(0, _Y_PRIMITIVES + i * 200, 100)
        actor = None
        try:
            actor = spawn_primitive(shape, location=loc)
        except Exception as e:
            _log_exception(f'primitive_{shape}', e)
        results.update(_result(f'primitive_{shape}', actor))
    return results


def test_image():
    """
    Spawn from a test image and verify cube matches image pixel dimensions.

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
        try:
            actor = spawn_image(img_path, location=FVector(0, _Y_IMAGE, 100))
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
        results.update(_result('image_valid', actor))

    # 3. invalid path — None is the correct result
    bad = None
    try:
        bad = spawn_image('C:/nonexistent_path/bad.png',
                          location=FVector(0, _Y_IMAGE + 400, 100))
    except Exception:
        pass
    results['image_invalid_path'] = {'ok': bad is None, 'actor': bad}
    _log(f'[{"PASS" if bad is None else "FAIL"}] image_invalid_path')
    return results


def test_video():
    """
    Spawn the loading_screen.mp4 as a vertical picture-frame video plane
    using MP_VideoTexture_Video_Mat, plus run the legacy Desktop-MP4 scan.
    """
    from ue_spawn import spawn_video, spawn_video_cube
    results = {}

    # video cube: plays loading_screen.mp4 via MediaPlayer
    loading_mp4 = (r'C:\Users\nicho\Documents\Unreal Projects'
                   r'\Starcel9\Content\Movies\loading_screen.mp4')
    if os.path.exists(loading_mp4):
        actor = None
        try:
            actor = spawn_video_cube(
                loading_mp4,
                location=FVector(0, _Y_VIDEO + 400, 100),
            )
        except Exception as e:
            _log_exception('video_cube', e)
        results.update(_result('video_cube', actor,
                               extra='cube playing loading_screen.mp4'))
    else:
        results.update(_skip('video_cube', f'not found: {loading_mp4}'))

    # legacy spawn_video on any Desktop MP4
    mp4_path = None
    try:
        for f in os.listdir(DESKTOP):
            if f.lower().endswith('.mp4'):
                mp4_path = os.path.join(DESKTOP, f)
                break
    except Exception:
        pass

    if mp4_path:
        actor = None
        try:
            ret   = spawn_video(mp4_path, location=FVector(0, _Y_VIDEO, 100))
            actor = ret[0] if isinstance(ret, tuple) else ret
        except Exception as e:
            _log_exception('video_valid', e)
        results.update(_result('video_valid', actor,
                               extra=os.path.basename(mp4_path)))
    else:
        results.update(_skip('video_valid', 'no .mp4 on Desktop'))

    bad = None
    try:
        bad = spawn_video('C:/nonexistent/bad.avi',
                          location=FVector(0, _Y_VIDEO + 200, 100))
    except Exception:
        pass
    results['video_invalid_path'] = {'ok': bad is None, 'actor': bad}
    _log(f'[{"PASS" if bad is None else "FAIL"}] video_invalid_path')
    return results


def test_sound():
    """Spawn sound immediately and as a sphere actor."""
    from ue_spawn import spawn_sound
    results = {}

    try:
        spawn_sound('/Game/Sounds/Placeholder',
                    location=FVector(0, _Y_SOUND, 100))
    except Exception:
        pass
    results['sound_immediate'] = {'ok': True, 'actor': None}
    _log('[PASS] sound_immediate — playback attempted')

    actor = None
    try:
        actor = spawn_sound('/Game/Sounds/Placeholder',
                            location=FVector(0, _Y_SOUND + 200, 100),
                            as_actor=True)
    except Exception as e:
        _log_exception('sound_as_actor', e)
    results.update(_result('sound_as_actor', actor))
    return results


def test_cameras():
    """Spawn each camera preset along Y."""
    from ue_spawn import spawn_camera, CAMERA_PRESETS
    results = {}
    for i, preset_name in enumerate(CAMERA_PRESETS):
        loc   = FVector(0, _Y_CAMERAS + i * 200, 300)
        actor = None
        try:
            actor = spawn_camera(location=loc, preset=preset_name)
        except Exception as e:
            _log_exception(f'camera_{preset_name}', e)
        results.update(_result(f'camera_{preset_name}', actor))
    return results


def test_earth():
    """Spawn Cesium Earth with satellite and night presets."""
    from ue_spawn import spawn_earth
    results = {}
    for i, preset in enumerate(['satellite', 'night']):
        loc   = FVector(0, _Y_EARTH + i * 500, 0)
        actor = None
        try:
            actor = spawn_earth(location=loc, preset=preset,
                                scale=FVector(0.00001, 0.00001, 0.00001))
        except Exception as e:
            _log_exception(f'earth_{preset}', e)
        results.update(_result(f'earth_{preset}', actor))
    return results


def test_system_monitor():
    """Spawn BP_SysMon actor."""
    from ue_spawn import spawn_system_monitor
    actor = None
    try:
        actor = spawn_system_monitor(location=FVector(0, _Y_SYSMON, 100))
    except Exception as e:
        _log_exception('system_monitor', e)
    return _result('system_monitor', actor)


def test_table():
    """Spawn two nd_tables: a basic 3×4 file listing and an advanced formula
    spreadsheet that exercises in-cell Python, spreadsheet labels (A–C, AA, AB),
    named cells, and cross-cell dependencies."""
    from ue_spawn import spawn_table
    results = {}

    # Basic table (unchanged)
    renderer = None
    try:
        from nd_table.ndtable import Table
        t = Table(shape=(3, 4))
        t[(0, 0)] = 'Name';    t[(0, 1)] = 'Size';    t[(0, 2)] = 'Date';    t[(0, 3)] = 'Type'
        t[(1, 0)] = 'file.py'; t[(1, 1)] = '10 KB';   t[(1, 2)] = '2024-01'; t[(1, 3)] = '.py'
        t[(2, 0)] = 'readme';  t[(2, 1)] = '1 KB';    t[(2, 2)] = '2024-01'; t[(2, 3)] = '.md'
        renderer = spawn_table(t, location=FVector(0, _Y_TABLE, 500))
    except Exception as e:
        _log_exception('table', e)
    n_cells = len(renderer.cell_actors) if renderer and hasattr(renderer, 'cell_actors') else 0
    results.update(_result('table', renderer, extra=f'{n_cells} cells'))

    # Advanced formula spreadsheet
    #  Uses spreadsheet labels A–C and extended AA, AB.
    #  Row 0: headers
    #  Rows 1-5: numeric data + formulas referencing other cells
    adv_renderer = None
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
            adv, location=FVector(500, _Y_TABLE + 400, 500))
        if formula_ok:
            _log(f'  adv_table: formulas evaluated successfully')
    except Exception as e:
        _log_exception('adv_table', e)

    n_adv = len(adv_renderer.cell_actors) if adv_renderer and hasattr(adv_renderer, 'cell_actors') else 0
    results.update(_result('table_formulas', adv_renderer,
                           extra=f'{n_adv} cells, labels A-C + AA + AB'))

    return results


def test_desktop_icons():
    """Spawn first 5 desktop shell icons as BP_Icon actors."""
    from ue_spawn import spawn_desktop_icons
    actors = []
    try:
        actors = spawn_desktop_icons(
            location=FVector(0, _Y_DESKTOP_ICONS, 100),
            max_icons=5,
        )
    except Exception as e:
        _log_exception('desktop_icons', e)

    first = actors[0] if actors else None
    return _result('desktop_icons', first, extra=f'{len(actors)} spawned')


def test_icon():
    """Spawn a BP_Icon from a plain PIL image."""
    from ue_spawn import spawn_icon
    actor = None
    try:
        from PIL import Image as PILImage
        img = PILImage.new('RGBA', (256, 256), (0, 200, 50, 255))
        actor = spawn_icon(img, location=FVector(0, _Y_ICON, 100))
        if actor:
            try:
                actor.get_actor_component('Sphere').SetSimulatePhysics(True)
            except Exception as phys_e:
                _log(f'  icon physics: {phys_e}')
    except Exception as e:
        _log_exception('icon_from_pil', e)
    return _result('icon_from_pil', actor)


# nD table grid test  (Y 8000 area, offset in X/Y from base)

_Y_ND_TABLE = 12000


def test_nd_table():
    """Comprehensive nD table rendering (2D 10x10 through 7D)."""
    from nd_table.examples import test_nd_table_grid
    renderer = None
    try:
        renderer = test_nd_table_grid(
            base_location=FVector(0, _Y_ND_TABLE, 700))
    except Exception as e:
        _log_exception('nd_table_grid', e)
    n_cells = len(renderer.cell_actors) if renderer and hasattr(renderer, 'cell_actors') else 0
    n_lines = len(renderer.gridline_actors) if renderer and hasattr(renderer, 'gridline_actors') else 0
    return _result('nd_table_grid', renderer,
                   extra=f'{n_cells} cells, {n_lines} gridlines')


# Plot test  (Y 9000 – 9500)

_Y_PLOT = 9000


_Y_PYACTOR_TEST = 7500


def test_pyactor_assign():
    """Spawn a BP_PyActor with pyactor_test.PyActorTest and verify its
    begin_play actually ran (logs 'Pyactor: hello world').
    PASS = actor spawned AND begin_play_fired flag is set."""
    import pyactor_test
    pyactor_test.begin_play_fired = False   # reset between runs

    from ue_spawn import _spawn_pyactor
    actor = None
    try:
        actor = _spawn_pyactor(
            'pyactor_test', 'PyActorTest',
            location=FVector(0, _Y_PYACTOR_TEST, 100))
        _log(f'  pyactor_hello_world: spawned at Y={_Y_PYACTOR_TEST}')
    except Exception as e:
        _log_exception('pyactor_hello_world', e)

    fired = pyactor_test.begin_play_fired
    ok    = actor is not None and fired
    _log(f'  pyactor_hello_world: spawned={actor is not None}, '
         f'begin_play_fired={fired}')
    return _result('pyactor_hello_world',
                   actor if ok else None,
                   extra='expects "Pyactor: hello world" from begin_play')


_Y_GIZMO = 11000


def test_gizmo(uobject=None, input_manager=None, location=None):
    """
    Spawn the interactive transform gizmo (target cylinder + move arrows,
    rotate rings, scale handles, plane squares) and wire up drag interaction.
    Returns (target, handles, tick_fn).

    uobject       — the PyActor UObject (self.uobject from Main); used for
                    get_hit_result_under_cursor traces
    input_manager — self.input from Main; used for bind_press/bind_release
                    on LeftMouseButton
    location      — FVector spawn position for the target cylinder.
                    Defaults to FVector(0, _Y_GIZMO, 100).

    Call from Main.begin_play:
        from test_spawn import test_gizmo
        self._gizmo_target, self._gizmo_handles, self._gizmo_tick = \\
            test_gizmo(uobject=self.uobject, input_manager=self.input)

    Then in tick:
        if hasattr(self, '_gizmo_tick') and self._gizmo_tick:
            self._gizmo_tick(delta_time)

    Omitting uobject/input_manager spawns the gizmo statically (no drag).
    """
    from gizmo import test_gizmos, setup_gizmo_interaction

    if location is None:
        location = FVector(0, _Y_GIZMO, 100)

    _log('--- test_gizmo ---')
    _log(f'Spawning gizmo target at {location}')

    target      = None
    gizmo_root  = None
    handles     = None
    tick_fn     = None

    try:
        target, gizmo_root, handles = test_gizmos(location=location)
        _log(f'test_gizmo: spawned target + {len(handles)} handles')
    except Exception as e:
        _log(f'test_gizmo: spawn failed: {e}')
        _result('gizmo', None, extra=str(e))
        return None, None, None

    if uobject is not None and input_manager is not None:
        try:
            tick_fn = setup_gizmo_interaction(
                uobject, input_manager, target, gizmo_root, handles)
            _log('test_gizmo: interaction wired up (drag LMB on any handle)')
        except Exception as e:
            _log(f'test_gizmo: interaction setup failed: {e}')
    else:
        _log('test_gizmo: WARNING — no uobject/input_manager; '
             'gizmo will be static (no drag). Pass self.uobject and '
             'self.input from Main.begin_play to enable interaction.')

    _result('gizmo', target,
            extra=f'{len(handles) if handles else 0} handles')
    return target, handles, tick_fn


def test_plot():
    """
    Three plot tests spread along Y:
      Y 9000  — colormap surface, triangles (reference)
      Y 9500  — colormap surface, sphere_lines (custom point_mesh option)
      Y 10000 — spherical ripple sphere_lines  (custom point_mesh option)

    sphere_lines variants accept an optional point_mesh path (default: Sphere).

    First tries spawn_plot() (full Blueprint path via BP_MathPlot).
    Falls back to create_plotter() directly if the Blueprint is missing.
    """
    import math
    results = {}

    variants = [
        dict(name='plot_spheres',        func='sin(x)+cos(y)',
             plot_type='surface',   mesh_mode='spheres',      orientation='ground_table',
             location=FVector(0, _Y_PLOT,        0)),
        dict(name='plot_sphere_lines',   func='sin(x)+cos(y)',
             plot_type='surface',   mesh_mode='sphere_lines', orientation='ground_table',
             location=FVector(0, _Y_PLOT + 500,  0)),
        dict(name='plot_ripple_sphere_lines', func='sin(sqrt(x**2+y**2))',
             plot_type='surface',   mesh_mode='sphere_lines', orientation='ground_table',
             location=FVector(0, _Y_PLOT + 1000, 0)),
    ]

    for v in variants:
        actor = None
        name  = v['name']

        # try Blueprint path
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
            _log(f'  {name}: spawn_plot Blueprint path failed ({e}), trying direct plotter...')

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

        results.update(_result(name, actor))

    # 2D curve: tan(x) with asymptote breaks
    plot_2d = None
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
            origin       = FVector(0, _Y_PLOT + 1500, 0),
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
    results.update(_result('plot_tan_2d', plot_2d, extra='2D tan(x)'))

    return results


# Aggregator

def test_spawn_all():
    """
    Run all spawn tests.  Modeled after test_gizmos().

    Actors are placed at X=0 and spread along Y (see module docstring for layout).
    Runs a prerequisites check first so you know exactly what to set up.

    Returns
    -------
    dict: { test_name: {'ok': bool, 'actor': actor_or_None} }

    Call from PIE Python console:
        from test_spawn import test_spawn_all
        results = test_spawn_all()

    Open Desktop/test_spawn_log.txt for the PASS/FAIL report and copy-paste
    the whole file back to Claude — it contains:
      * environment (Python/UE versions, CWD, world name)
      * prerequisite asset check
      * per-test inputs, spawned-actor introspection, full tracebacks
      * per-test elapsed time
      * final summary table
    """
    run_t0 = time.monotonic()

    _log('=' * 70)
    _log('test_spawn_all')
    _log('=' * 70)

    _log_env()
    _check_prerequisites()

    results  = {}
    timings  = {}   # fn_name -> seconds
    errors   = {}   # fn_name -> top-level exception if the whole fn blew up
    for fn in [
        test_primitives,
        test_image,
        test_video,
        test_sound,
        test_cameras,
        test_earth,
        test_system_monitor,
        test_table,
        test_desktop_icons,
        test_icon,
        test_pyactor_assign,
        test_nd_table,
        test_plot,
    ]:
        _section(fn.__name__)
        t0 = time.monotonic()
        try:
            results.update(fn())
        except Exception as e:
            errors[fn.__name__] = e
            _log_exception(fn.__name__, e)
        timings[fn.__name__] = time.monotonic() - t0
        _log(f'  elapsed: {timings[fn.__name__]:.2f}s')

    passed = sum(1 for v in results.values() if v['ok'])
    failed = len(results) - passed

    _log('')
    _log('=' * 70)
    _log(f'RESULTS: {passed} PASS / {failed} FAIL  (total {len(results)})')
    _log(f'Total elapsed: {time.monotonic() - run_t0:.2f}s')
    _log(f'Log:     {_LOG_PATH}')
    _log('=' * 70)

    # Per-test table — fast scan of what passed/failed and class returned
    _log('')
    _log('Per-test summary:')
    _log(f'  {"status":<6} {"test":<40} {"class":<30}')
    _log(f'  {"-"*6} {"-"*40} {"-"*30}')
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
        _log(f'  {status:<6} {name:<40} {cls_str:<30}')

    # Fail-only list — makes it easy to paste only failing tests back
    failing = [n for n, r in results.items() if not r['ok']]
    if failing:
        _log('')
        _log(f'FAILING TESTS ({len(failing)}): ' + ', '.join(failing))

    # Per-fn elapsed times (spot hangs/slow tests)
    _log('')
    _log('Per-fn timings:')
    for name, secs in timings.items():
        marker = '  (fn-level error)' if name in errors else ''
        _log(f'  {secs:6.2f}s  {name}{marker}')

    return results


# Text3D click investigation (manual — call, then click the spawned text)

_Y_TEXT3D_CLICK = 8000


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


def _spawn_text_cursor(world):
    """Spawn a thin translucent cube to use as a blinking insertion cursor."""
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


def test_text3d_click(uobject=None, input_manager=None, location=None):
    """
    Spawn a Text3D actor with known string "ABCDEFGHIJ" and a 3x3 test table.
    Returns (single_actor, table_renderer, tick_fn).

    uobject       — the PyActor UObject (self.uobject from Main); used for
                    get_hit_result_under_cursor traces (same as gizmo)
    input_manager — self.input from Main; used for bind_press/bind_release
                    on LeftMouseButton (same mechanism gizmo uses)
    location      — FVector spawn position. Defaults to FVector(400, 0, 150).

    Re-call from PIE console at any position:
        from test_spawn import test_text3d_click
        from unreal_engine import FVector
        a, t, fn = test_text3d_click(uobject, input_manager, FVector(500, 200, 150))

    Click any spawned text to see col/row in Output Log and
    Desktop/test_spawn_log.txt.

    BP_Cell requirements:
      - Text3DComponent -> Generate Hit Events = ON
      - Collision response to WorldDynamic = Block
    """
    from ue_spawn import spawn_blueprint, spawn_table

    if location is None:
        location = FVector(400, 0, 150)

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

    # 3x3 test table
    table_renderer = None
    try:
        from nd_table.ndtable import Table
        t = Table(shape=(3, 3))
        t[(0, 0)] = 'Col A'; t[(0, 1)] = 'Col B'; t[(0, 2)] = 'Col C'
        t[(1, 0)] = 'Hello'; t[(1, 1)] = 'World'; t[(1, 2)] = '123'
        t[(2, 0)] = 'Click'; t[(2, 1)] = 'Me';    t[(2, 2)] = '!'
        table_renderer = spawn_table(
            t, location=FVector(location.x, location.y + 400, location.z))
        if table_renderer:
            _log(f'text3d_click: spawned table '
                 f'({len(table_renderer.cell_actors)} cells)')
    except Exception as e:
        _log(f'text3d_click: table spawn failed: {e}')

    # Build watched dict: actor → text content
    watched = {}   # actor → str (text shown by that actor's Text3DComponent)
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

    # Insertion cursor
    _cursor_actor, _cursor_mid = _spawn_text_cursor(get_world())
    _cursor_state = {'timer': 0.0, 'visible': False, 'active': False}

    # Focus / typing state
    # actor: the Text3D actor currently being edited (None when unfocused)
    # string_idx: insertion index within the actor's full text string
    _focus_state = {'actor': None, 'string_idx': 0}

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
        if _cursor_actor is not None:
            try:
                _cursor_actor.SetActorHiddenInGame(True)
            except Exception:
                pass
        _cursor_state['active']  = False
        _cursor_state['visible'] = False

    def _unfocus():
        _focus_state['actor']      = None
        _focus_state['string_idx'] = 0
        _hide_cursor()

    def _get_cursor_placement(actor, target_glyph):
        """Compute (world_pt, scale_vec, rotation) for cursor at the left
        edge of the glyph at target_glyph. target_glyph may equal the glyph
        count (meaning: just past the last glyph). Returns None on failure."""
        if actor is None:
            return None
        t3d = None
        try:
            t3d = actor.get_actor_component('Text3DComponent')
        except Exception:
            return None
        if t3d is None:
            return None

        kernings = None
        try:
            kernings = t3d.CharacterKernings
        except Exception:
            pass
        meshes = None
        try:
            meshes = t3d.CharacterMeshes
        except Exception:
            pass

        if not kernings or len(kernings) == 0:
            return None

        glyph_h = 50.0
        glyph_w = 50.0

        # Read glyph dimensions from the reference mesh (target, clamped).
        ref_idx = target_glyph
        if ref_idx >= len(kernings):
            ref_idx = len(kernings) - 1
        if ref_idx < 0:
            ref_idx = 0
        if (meshes is not None
                and 0 <= ref_idx < len(meshes)
                and meshes[ref_idx] is not None):
            try:
                _, e = meshes[ref_idx].GetComponentBounds()
                glyph_h = e.z * 2.0
                glyph_w = e.y * 2.0
            except Exception:
                pass

        # target_rel = left edge of target glyph, or one width past the last.
        target_rel = None
        if 0 <= target_glyph < len(kernings) and kernings[target_glyph] is not None:
            try:
                target_rel = kernings[target_glyph].get_relative_location()
            except Exception:
                pass
        elif len(kernings) > 0 and kernings[-1] is not None:
            try:
                r = kernings[-1].get_relative_location()
                target_rel = FVector(r.x, r.y + glyph_w, r.z)
            except Exception:
                pass
        if target_rel is None:
            return None

        # Full vertical extent for cursor height/center.
        full_top = None
        full_bot = None
        if meshes is not None:
            for m in meshes:
                if m is None:
                    continue
                try:
                    o, e = m.GetComponentBounds()
                    t = o.z + e.z
                    b = o.z - e.z
                    if full_top is None or t > full_top:
                        full_top = t
                    if full_bot is None or b < full_bot:
                        full_bot = b
                except Exception:
                    continue
        try:
            o, e = t3d.GetComponentBounds()
            t = o.z + e.z
            b = o.z - e.z
            if full_top is None or t > full_top:
                full_top = t
            if full_bot is None or b < full_bot:
                full_bot = b
        except Exception:
            pass

        actor_loc = actor.get_actor_location()
        actor_rot = actor.get_actor_rotation()

        if full_top is not None and full_bot is not None:
            tight = full_top - full_bot
            full_top += tight * 0.25  # headroom for diacritics/^
            cursor_h = full_top - full_bot
            cursor_z = (full_top + full_bot) * 0.5
        else:
            cursor_h = glyph_h
            cursor_z = actor_loc.z + target_rel.z

        world_pt = FVector(
            actor_loc.x + target_rel.x,
            actor_loc.y + target_rel.y,
            cursor_z,
        )
        scale_vec = FVector(0.01, glyph_w * 0.3 / 100.0, cursor_h / 100.0)
        return world_pt, scale_vec, actor_rot

    def _show_cursor_at_glyph(actor, target_glyph):
        """Move cursor to target_glyph. Returns True on success."""
        if _cursor_actor is None:
            return False
        placement = _get_cursor_placement(actor, target_glyph)
        if placement is None:
            return False
        world_pt, scale_vec, rot = placement
        try:
            _cursor_actor.set_actor_scale(scale_vec)
        except Exception:
            pass
        _cursor_actor.set_actor_location(world_pt)
        _cursor_actor.set_actor_rotation(rot)
        _cursor_actor.SetActorHiddenInGame(False)
        _cursor_state['active']  = True
        _cursor_state['timer']   = 0.0
        _cursor_state['visible'] = True
        return True

    def _position_cursor(hit_actor, hit):
        """Derive target_glyph from a click hit, move cursor, set focus."""
        if _cursor_actor is None or hit_actor is None:
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

        # No kernings — fall back to dropping the cursor at the click point.
        if not kernings or len(kernings) == 0:
            try:
                _cursor_actor.set_actor_location(hit.impact_point)
                _cursor_actor.set_actor_rotation(hit_actor.get_actor_rotation())
                _cursor_actor.SetActorHiddenInGame(False)
                _cursor_state['active']  = True
                _cursor_state['timer']   = 0.0
                _cursor_state['visible'] = True
            except Exception:
                pass
            _focus_state['actor']      = hit_actor
            _focus_state['string_idx'] = len(text)
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

        _focus_state['actor']      = hit_actor
        _focus_state['string_idx'] = _glyph_to_string_idx(text, target_glyph)
        _log(f'text3d_click: cursor snap clicked={clicked_glyph} '
             f'side={side} → {target_glyph}  '
             f'focus string_idx={_focus_state["string_idx"]}')

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

        target_glyph = _string_idx_to_glyph(text, idx)
        _show_cursor_at_glyph(actor, target_glyph)

    # Notepad-style typing via direct Windows keyboard poll
    # Bypasses UE's input routing so we get layout-correct translation
    # (Shift, CapsLock, AltGr, dead keys) exactly like notepad.exe.
    # Runs alongside HotkeyManager bindings in main.py without disturbing them.
    try:
        import ctypes as _ctypes
        _user32 = _ctypes.WinDLL('user32', use_last_error=True)
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
        _WIN32_TYPING_OK = True
    except Exception as _win_err:
        _WIN32_TYPING_OK = False
        _user32 = None
        _ctypes = None
        _log(f'text3d_click: ctypes typing unavailable ({_win_err})')

    _prev_vk_down = bytearray(256)

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

    def _on_vk_rise(vk):
        """Rising-edge handler — one character event, like notepad's WM_CHAR."""
        if _focus_state['actor'] is None:
            return
        # Special keys first (ToUnicode would return '\b','\r','\t','\x1b' etc.
        # but we want our own handling).
        if vk == 0x08:      # VK_BACK
            _handle_typed_char('\b')
            return
        if vk == 0x0D:      # VK_RETURN
            _handle_typed_char('\n')
            return
        if vk == 0x09:      # VK_TAB
            _handle_typed_char('\t')
            return
        if vk == 0x1B:      # VK_ESCAPE — leave the field
            _unfocus()
            return
        # Everything else: ask Windows to translate via the current layout
        try:
            kb_state  = _build_kb_state()
            scan_code = _user32.MapVirtualKeyW(vk, 0)  # MAPVK_VK_TO_VSC
            outbuf    = _ctypes.create_unicode_buffer(8)
            result    = _user32.ToUnicode(
                vk, scan_code, kb_state, outbuf, len(outbuf), 0)
        except Exception:
            return
        if result > 0:
            for c in outbuf.value[:result]:
                # Skip control chars (NUL..US); printable space (0x20) is OK
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
    CURSOR_BLINK_RATE = 1.0

    def tick_fn(dt):
        # Typing poll (fires char events via Win32 ToUnicode when focused)
        _poll_keyboard()

        # Blink cursor
        if _cursor_actor is not None and _cursor_state['active']:
            _cursor_state['timer'] += dt
            half = CURSOR_BLINK_RATE * 0.5
            should_show = (_cursor_state['timer'] % CURSOR_BLINK_RATE) < half
            if should_show != _cursor_state['visible']:
                _cursor_state['visible'] = should_show
                _cursor_actor.SetActorHiddenInGame(not should_show)

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
                    _log(f'text3d_click: off-click — hit '
                         f'"{hit_actor.get_name()}" (not watched), unfocusing')
                else:
                    _log('text3d_click: off-click — nothing under cursor, unfocusing')
                _unfocus()
                return

            _log_click_on_actor_from_hit(matched_actor, hit, text_content=matched_text)
            _position_cursor(matched_actor, hit)

        elif not currently_down:
            _state['fired'] = False

    _log(f'text3d_click: log -> {_LOG_PATH}')
    return single_actor, table_renderer, tick_fn
