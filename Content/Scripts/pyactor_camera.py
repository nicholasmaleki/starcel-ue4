import unreal_engine as ue
from unreal_engine import FVector, FRotator
from unreal_engine_tools import find_component

# Python component: full camera control for BP_PyCamera
#
# Blueprint requirements (BP_PyCamera):
#   - CineCameraComponent as root (or added component), name: 'CineCameraComponent'
#   - Python component → pyactor_camera.PyActorCamera
#   - Blueprint string variable named 'camera_type' (Instance Editable, default "normal")
#
# Camera types:
#   'normal'        Standard 35mm full-frame
#   'cinematic'     Wide 24mm f/2.8 cinematic
#   'macro'         Extreme bokeh 50mm f/0.95
#   'bokeh'         Portrait 85mm f/1.4
#   'bokeh_tele'    Telephoto bokeh 135mm f/1.8
#   'panini'        Wide 14mm with Panini projection enabled
#   'cctv'          6mm 1/3" sensor security camera
#   'anamorphic'    40mm anamorphic widescreen
#   'orthographic'  Orthographic projection (no perspective)
#
# Projection modes:
#   set_projection('perspective')   — normal
#   set_projection('orthographic')  — flat/top-down/iso
#
# Panini:
#   enable_panini(d, s, screen_percentage)  — enable via console commands
#   disable_panini()                        — restore defaults
#
# View transfer:
#   transfer_to_player()   — make this camera the active view target

# Import CAMERA_PRESETS and _exec_console from ue_spawn (single source of truth)
try:
    from ue_spawn import CAMERA_PRESETS, _exec_console
except Exception as _e:
    ue.log_warning(f'pyactor_camera: could not import from ue_spawn: {_e}')
    CAMERA_PRESETS = {}
    def _exec_console(cmd):
        ue.log_warning(f'_exec_console stub: {cmd}')

# Map friendly type names → CAMERA_PRESETS keys
_TYPE_TO_PRESET = {
    'normal':        'default',
    'default':       'default',
    'cinematic':     'cinematic',
    'macro':         'bokeh_macro',
    'bokeh':         'bokeh_portrait',
    'bokeh_portrait':'bokeh_portrait',
    'bokeh_tele':    'bokeh_telephoto',
    'bokeh_telephoto':'bokeh_telephoto',
    'panini':        'panini',
    'cctv':          'cctv',
    'anamorphic':    'anamorphic',
}

# Projection mode int values (ECameraProjectionMode)
_PROJ_PERSPECTIVE   = 0
_PROJ_ORTHOGRAPHIC  = 1


class PyActorCamera:
    """
    Full camera control PyActor component for BP_PyCamera.
    Applies preset lens/DOF settings from ue_spawn.CAMERA_PRESETS and
    provides runtime methods for projection, Panini, and view transfer.
    """

    def begin_play(self):
        self.uobject.enable_input()
        self._cam = None
        self._current_type = 'normal'

        # Find CineCameraComponent
        try:
            self._cam = find_component(self.uobject, 'CineCameraComponent')
        except Exception:
            pass

        if self._cam is None:
            # Try generic CameraComponent fallback
            try:
                self._cam = find_component(self.uobject, 'CameraComponent')
            except Exception:
                pass

        if self._cam is None:
            ue.log_warning(
                f'PyActorCamera: no CineCameraComponent/CameraComponent found '
                f'on {self.uobject.get_name()}')
        else:
            ue.log(f'PyActorCamera: found camera component on {self.uobject.get_name()}')

        # Read Blueprint-exposed camera_type property, apply preset
        cam_type = getattr(self.uobject, 'camera_type', 'normal') or 'normal'
        self.set_type(cam_type)

    # Camera type / preset

    def set_type(self, type_name):
        """
        Apply a named camera type.  type_name is one of the keys in
        _TYPE_TO_PRESET, or 'orthographic' for orthographic projection.
        """
        self._current_type = type_name
        lower = type_name.lower()

        if lower == 'orthographic':
            self.set_projection('orthographic')
            return

        preset_key = _TYPE_TO_PRESET.get(lower, 'default')
        cfg = CAMERA_PRESETS.get(preset_key)
        if cfg is None:
            ue.log_warning(f'PyActorCamera.set_type: unknown type "{type_name}"')
            return

        self._apply_preset(cfg)
        ue.log(f'PyActorCamera: applied type="{type_name}" (preset="{preset_key}")')

    def _apply_preset(self, cfg):
        """Write cfg dict values to the CineCameraComponent."""
        if self._cam is None:
            return

        try:
            self._cam.CurrentFocalLength = cfg.get('focal_length', 35.0)
        except Exception as e:
            ue.log_warning(f'PyActorCamera: CurrentFocalLength: {e}')

        try:
            self._cam.CurrentAperture = cfg.get('aperture', 5.6)
        except Exception as e:
            ue.log_warning(f'PyActorCamera: CurrentAperture: {e}')

        try:
            sw = cfg.get('sensor_width', 36.0)
            self._cam.FilmbackSettings.SensorWidth  = sw
            self._cam.FilmbackSettings.SensorHeight = sw * 9.0 / 16.0
        except Exception as e:
            ue.log_warning(f'PyActorCamera: FilmbackSettings: {e}')

        try:
            self._cam.FocusSettings.ManualFocusDistance = cfg.get('focus_distance', 1000.0)
            self._cam.FocusSettings.FocusMethod = 1   # EFocusMethod::Manual
        except Exception as e:
            ue.log_warning(f'PyActorCamera: FocusSettings: {e}')

        try:
            self._cam.post_edit_change()
        except Exception:
            pass

        # Handle Panini from preset
        if cfg.get('panini', False):
            self.enable_panini(
                d=cfg.get('panini_d', 0.5),
                s=cfg.get('panini_s', 0.05),
                screen_percentage=cfg.get('screen_percentage', 150),
            )
        else:
            self.disable_panini()

        # Restore perspective if we were in orthographic
        self.set_projection('perspective')

    # Projection mode

    def set_projection(self, mode):
        """
        mode: 'perspective' (default) or 'orthographic'
        Uses integer literals because ECameraProjectionMode is not in enums.py.
        """
        if self._cam is None:
            return
        proj_int = _PROJ_ORTHOGRAPHIC if mode == 'orthographic' else _PROJ_PERSPECTIVE
        try:
            self._cam.SetProjectionMode(proj_int)
            ue.log(f'PyActorCamera: projection = {mode}')
        except Exception as e:
            ue.log_warning(f'PyActorCamera.set_projection({mode}): {e}')

    # Panini projection

    def enable_panini(self, d=0.5, s=0.05, screen_percentage=150):
        """Enable Panini projection via console commands (affects entire viewport)."""
        _exec_console(f'r.Upscale.Panini.D {d}')
        _exec_console(f'r.Upscale.Panini.S {s}')
        _exec_console(f'r.ScreenPercentage {screen_percentage}')
        ue.log(f'PyActorCamera: Panini ON (D={d} S={s} ScreenPercentage={screen_percentage})')

    def disable_panini(self):
        """Disable Panini projection and restore native screen percentage."""
        _exec_console('r.Upscale.Panini.D 0')
        _exec_console('r.Upscale.Panini.S 0')
        _exec_console('r.ScreenPercentage 100')

    # View transfer

    def transfer_to_player(self, blend_time=0.0):
        """
        Make this camera the active view target for player 0.
        blend_time=0.0 is instant; pass a positive value for a smooth transition.
        """
        try:
            pc = ue.get_player_controller(0)
            pc.SetViewTargetWithBlend(self.uobject, blend_time)
            ue.log(f'PyActorCamera: transferred view to {self.uobject.get_name()} '
                   f'(blend={blend_time}s)')
        except Exception as e:
            ue.log_warning(f'PyActorCamera.transfer_to_player: {e}')

    # Convenience accessors

    def get_focal_length(self):
        if self._cam is None:
            return None
        try:
            return self._cam.CurrentFocalLength
        except Exception:
            return None

    def set_focal_length(self, mm):
        if self._cam is None:
            return
        try:
            self._cam.CurrentFocalLength = float(mm)
        except Exception as e:
            ue.log_warning(f'PyActorCamera.set_focal_length: {e}')

    def set_aperture(self, f_stop):
        if self._cam is None:
            return
        try:
            self._cam.CurrentAperture = float(f_stop)
        except Exception as e:
            ue.log_warning(f'PyActorCamera.set_aperture: {e}')

    def set_focus_distance(self, ue_units):
        if self._cam is None:
            return
        try:
            self._cam.FocusSettings.ManualFocusDistance = float(ue_units)
        except Exception as e:
            ue.log_warning(f'PyActorCamera.set_focus_distance: {e}')
