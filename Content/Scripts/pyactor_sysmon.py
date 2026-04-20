import unreal_engine as ue
from unreal_engine_tools import find_component

# Python component: live system monitor
#
# Spawn via spawn_system_monitor(...) in ue_spawn.py — dynamic PyActor,
# no Blueprint placeholder required. The Text3DComponent is added after
# BeginPlay by spawn_pyactor(components=...).
#
# Data sources:
#   sysinfo.py          get_info_string(mode='minimal', units='usa')
#   activity_tracker.py read_stats()   ← requires tracker daemon to be running
#
# The Text3D is updated every UPDATE_INTERVAL seconds via tick(dt).
# Imports are done lazily inside _update() to support hot-reload in UE editor.
#
# If activity_tracker is not running, read_stats() returns None and only
# sysinfo data is displayed — no crash.


class PyActorSysmon:
    """
    Tick-based system monitor that writes live metrics to a Text3DComponent.
    """

    UPDATE_INTERVAL = 2.0    # seconds between refreshes

    def begin_play(self):
        self._elapsed = 0.0
        self.text3d   = None

    def tick(self, dt):
        # Lazy component lookup — ue_spawn.spawn_pyactor adds components
        # after BeginPlay, so the Text3DComponent may not exist until tick.
        if self.text3d is None:
            try:
                self.text3d = find_component(self.uobject, 'Text3DComponent')
            except Exception:
                pass
            if self.text3d is None:
                return
            ue.log(f'PyActorSysmon: started on {self.uobject.get_name()}')
            self._update()
            return

        self._elapsed += dt
        if self._elapsed >= self.UPDATE_INTERVAL:
            self._elapsed = 0.0
            self._update()


    def _update(self):
        """Read sysinfo + activity_tracker, format, push to Text3DComponent."""
        lines = []

        # System info
        try:
            from sysinfo import get_info_string
            sys_str = get_info_string(mode='minimal', units='usa')
            if sys_str:
                lines.append(sys_str.strip())
        except Exception as e:
            lines.append(f'[sysinfo error: {e}]')

        # Activity tracker (optional daemon)
        try:
            from activity_tracker import read_stats
            stats = read_stats()
            if stats:
                apm   = stats.get('actions_per_min',  0.0)
                cpm   = stats.get('clicks_per_min',   0.0)
                kpm   = stats.get('keys_per_min',     0.0)
                dist  = stats.get('mouse_distance_px', 0.0)
                lines.append(
                    f'APM: {apm:.1f}  '
                    f'Clicks/min: {cpm:.1f}  '
                    f'Keys/min: {kpm:.1f}  '
                    f'Mouse px: {dist:.0f}'
                )
        except Exception:
            pass   # silently skip if tracker not available

        display = '\n'.join(lines) if lines else '(no data)'

        try:
            self.text3d.Text = display
        except Exception as e:
            ue.log_warning(f'PyActorSysmon: failed to set Text3D text: {e}')
