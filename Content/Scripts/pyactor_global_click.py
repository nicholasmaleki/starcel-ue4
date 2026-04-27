import unreal_engine as ue


class PyActorGlobalClick:
    """Singleton PyActor that hosts the world's global click/input tick.

    Owns the per-frame work for global LMB hit-tests, keyboard poll,
    caret blink, focus management, highlight rendering — i.e. anything
    that needs one tick across all Text3D actors rather than per-instance.

    Call set_tick_fn(fn) after spawn with the tick closure built by
    test_text3d_click (which still owns the state machine via closures — a
    future refactor could migrate that state onto this class directly).

    Focus tracking is global: only one Text3D actor can be focused at a
    time. Use ``set_focused_actor(actor)`` from the focus state machine,
    and ``is_any_focused()`` from any other system that wants to suppress
    its own input while the user is typing (e.g. PyPawnDrone WASD).
    Register an unfocus handler with ``add_unfocus_handler(fn)`` to react
    to focus loss (e.g. recompute table layout).
    """

    _focused_actor = None
    _on_unfocus_handlers = []

    @classmethod
    def set_focused_actor(cls, actor):
        """Set the currently focused Text3D actor (or None to clear).
        Fires registered unfocus handlers for the previous actor if it
        differs from `actor`."""
        prev = cls._focused_actor
        if prev is actor:
            return
        cls._focused_actor = actor
        if prev is not None:
            for handler in list(cls._on_unfocus_handlers):
                try:
                    handler(prev)
                except Exception as e:
                    try:
                        ue.log_warning(
                            f'PyActorGlobalClick unfocus handler error: {e}')
                    except Exception:
                        pass

    @classmethod
    def get_focused_actor(cls):
        return cls._focused_actor

    @classmethod
    def is_any_focused(cls):
        return cls._focused_actor is not None

    @classmethod
    def add_unfocus_handler(cls, fn):
        """Register fn(prev_actor) to fire when an actor loses focus."""
        if fn not in cls._on_unfocus_handlers:
            cls._on_unfocus_handlers.append(fn)

    @classmethod
    def remove_unfocus_handler(cls, fn):
        try:
            cls._on_unfocus_handlers.remove(fn)
        except ValueError:
            pass

    def begin_play(self):
        self._tick_fn = None
        ue.log('PyActorGlobalClick: ready (awaiting set_tick_fn)')

    def set_tick_fn(self, fn):
        self._tick_fn = fn
        ue.log('PyActorGlobalClick: tick function attached')

    def tick(self, dt):
        fn = self._tick_fn
        if fn is None:
            return
        try:
            fn(dt)
        except Exception as e:
            try:
                ue.log_warning(f'PyActorGlobalClick tick error: {e}')
            except Exception:
                pass
