import unreal_engine as ue


# Python proxy for spawn_text3d_executor — hosted on BP_PyActorEmpty, paired
# with a BP_Cell Text3D child set up by ue_spawn.spawn_text3d_pyactor.
#
# Spawn structure:
#   parent  = BP_PyActorEmpty (this proxy)
#   child   = BP_Cell  (attached to parent, exposed as parent.text3d_actor)
#
# Two ways to fire:
#   - Ctrl+Enter (rising edge) — Win32 GetAsyncKeyState polling, works
#     regardless of UE focus. Fires when this executor's text3d is the
#     globally-focused actor (PyActorGlobalClick) OR when no actor is
#     focused (so a freshly-spawned executor works without test_text3d_click
#     set up first).
#   - Mouse click on the Text3D child (rising edge) — tick-based cursor
#     trace via click_helpers.cursor_hit_actor. No focus gating; clicking
#     directly is an unambiguous "run me now" gesture.
#
# Tick is force-enabled in begin_play so the polling runs even if the
# host BP forgot to flip bStartWithTickEnabled.


class PyActorText3DExecutor:
    """Run the BP_Cell child's text as Python on Ctrl+Enter or click."""

    TEXT_COMPONENT_NAME = 'Text3DComponent'

    VK_CONTROL = 0x11
    VK_RETURN = 0x0D

    def begin_play(self):
        # parent.text3d_actor is set by spawn_text3d_pyactor AFTER actor_spawn
        # returns from BeginPlay, so it's not visible here. Read on first tick.
        self._text3d_actor = None
        self._first_tick = True
        self._prev_combo_down = False
        self._prev_mouse_down = False

        # Force tick on regardless of BP defaults — without this the Win32
        # poll never runs and Ctrl+Enter silently does nothing.
        try:
            self.uobject.set_actor_tick_enabled(True)
        except Exception as e:
            ue.log_warning(
                f'PyActorText3DExecutor: set_actor_tick_enabled failed ({e})')

        # Player controller for cursor trace + click event routing.
        self._player_controller = None
        try:
            from click_helpers import setup_player_controller
            self._player_controller = setup_player_controller(self.uobject)
        except Exception as e:
            ue.log_warning(
                f'PyActorText3DExecutor: player controller setup failed ({e}); '
                'click-to-run disabled.')

        self._win32_ok = False
        self._user32 = None
        try:
            import ctypes
            self._user32 = ctypes.WinDLL('user32', use_last_error=True)
            self._user32.GetAsyncKeyState.argtypes = [ctypes.c_int]
            self._user32.GetAsyncKeyState.restype = ctypes.c_short
            self._win32_ok = True
        except Exception as e:
            ue.log_warning(
                f'PyActorText3DExecutor: ctypes init failed ({e}); '
                'Ctrl+Enter execution disabled.')

        ue.log(f'PyActorText3DExecutor: ready on {self.uobject.get_name()}')

    def tick(self, dt):
        if self._first_tick:
            self._first_tick = False
            try:
                self._text3d_actor = getattr(self.uobject, 'text3d_actor', None)
            except Exception:
                self._text3d_actor = None
            if self._text3d_actor is None:
                ue.log_warning(
                    'PyActorText3DExecutor: parent.text3d_actor missing — '
                    'spawn via ue_spawn.spawn_text3d_executor.')
            else:
                ue.log(
                    f'PyActorText3DExecutor: bound to '
                    f'{self._text3d_actor.get_name()} '
                    f'(Ctrl+Enter or click to run)')
                # Register the child with PyActorText3D's typing system so
                # clicking the text focuses it for editing.  Without this,
                # the global click poll treats every click on this child
                # as off-target and unfocuses.  Both calls are idempotent.
                try:
                    from pyactor_text3d import PyActorText3D
                    PyActorText3D.register_actor(self._text3d_actor)
                    PyActorText3D._ensure_global_typing()
                except Exception as e:
                    ue.log_warning(
                        f'PyActorText3DExecutor: typing registration failed ({e})')

        if self._text3d_actor is None:
            return

        # Ctrl+Enter (Win32 polling)
        if self._win32_ok and self._is_target_focused():
            down = self._is_ctrl_enter_down()
            if down and not self._prev_combo_down:
                self._run_code(trigger='Ctrl+Enter')
            self._prev_combo_down = down
        else:
            self._prev_combo_down = False

        # Click on the child Text3D
        self._poll_click()

    def _poll_click(self):
        if self._player_controller is None:
            return
        try:
            from click_helpers import is_mouse_down, cursor_hit_actor
        except Exception:
            return

        mouse_down = is_mouse_down(self._player_controller)
        try:
            on_target = (
                cursor_hit_actor(self.uobject, self._player_controller)
                is self._text3d_actor)
        except Exception:
            on_target = False

        if mouse_down and not self._prev_mouse_down and on_target:
            self._run_code(trigger='click')
        self._prev_mouse_down = mouse_down

    def _is_target_focused(self):
        """True when this executor's text3d should respond to Ctrl+Enter.

        Fires when our text3d is the globally-focused actor OR when no
        actor is focused at all (so a fresh executor without the typing
        system set up still runs)."""
        try:
            from pyactor_global_click import PyActorGlobalClick
            focused = PyActorGlobalClick.get_focused_actor()
        except Exception:
            return True
        if focused is None:
            return True
        return focused is self._text3d_actor

    def _is_ctrl_enter_down(self):
        ctrl = self._user32.GetAsyncKeyState(self.VK_CONTROL) & 0x8000
        enter = self._user32.GetAsyncKeyState(self.VK_RETURN) & 0x8000
        return bool(ctrl) and bool(enter)

    def _run_code(self, trigger='?'):
        try:
            t3d = self._text3d_actor.get_actor_component(self.TEXT_COMPONENT_NAME)
        except Exception as e:
            ue.log_warning(
                f'PyActorText3DExecutor: get_actor_component failed: {e}')
            return
        if t3d is None:
            return
        try:
            code = str(t3d.Text or '')
        except Exception:
            return
        if not code.strip():
            return

        # Several executors can co-exist (e.g. test_text3d_pyactor spawns one
        # whose text is a plain English label, not Python). When Ctrl+Enter
        # fires unfocused, all executors run — silently skip texts that don't
        # parse as Python rather than spamming SyntaxError warnings.
        try:
            compiled = compile(code, '<text3d>', 'exec')
        except SyntaxError:
            return

        ue.log(
            f'PyActorText3DExecutor: running {trigger} on '
            f'{self._text3d_actor.get_name()}\n{code}')
        env = {
            '__name__': '__main__',
            'ue': ue,
            'self': self,
            'actor': self._text3d_actor,
            'parent': self.uobject,
        }
        try:
            exec(compiled, env)
        except Exception as e:
            ue.log_warning(f'PyActorText3DExecutor: exec failed: {e}')
