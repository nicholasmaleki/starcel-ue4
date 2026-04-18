"""Shared click-detection and player-controller helpers for PyActor components.

Consolidates the identical _is_mouse_down(), cursor_hit_actor(), and
player-controller setup code that was copy-pasted across pyactor_icon,
pyactor_sound, pyactor_text3d, pyactor_file_explorer, and gizmo.
"""
from __future__ import annotations

try:
    import unreal_engine as ue
    from unreal_engine.enums import ECollisionChannel
except ImportError:
    ue = None
    ECollisionChannel = None


# Player controller setup

def setup_player_controller(uobject):
    """Enable input and configure the player controller for click/hover events.

    Returns the player controller, or None on failure.
    """
    try:
        uobject.enable_input()
    except Exception:
        pass

    player_controller = None
    try:
        player_controller = uobject.get_player_controller()
        if player_controller is not None:
            player_controller.bEnableMouseOverEvents = True
            player_controller.bEnableClickEvents     = True
            if ECollisionChannel is not None:
                player_controller.CurrentClickTraceChannel = \
                    ECollisionChannel.ECC_WorldDynamic
    except Exception as e:
        if ue:
            ue.log_warning(f'click_helpers: player controller setup failed: {e}')

    return player_controller


# Mouse button check

def is_mouse_down(player_controller) -> bool:
    """Check if left mouse button is currently held.

    Tries multiple UEP API styles for compatibility across engine versions.
    Returns False if player_controller is None or all methods fail.
    """
    if player_controller is None:
        return False
    try:
        from unreal_engine import FKey
        return player_controller.IsInputKeyDown(FKey('LeftMouseButton'))
    except Exception:
        pass
    try:
        return player_controller.IsInputKeyDown('LeftMouseButton')
    except Exception:
        pass
    try:
        return player_controller.is_input_key_down('LeftMouseButton')
    except Exception:
        return False


# Cursor trace

def cursor_hit_actor(uobject, player_controller, channel=None):
    """Trace under the cursor and return the hit actor, or None.

    Tries uobject.get_hit_result_under_cursor first, falls back to the
    player controller method.
    """
    if channel is None and ECollisionChannel is not None:
        channel = ECollisionChannel.ECC_WorldDynamic

    try:
        hit = uobject.get_hit_result_under_cursor(channel)
        if hit is not None:
            return hit.actor
    except Exception:
        pass

    if player_controller is not None:
        try:
            hit = player_controller.get_hit_result_under_cursor(channel, False)
            if hit is not None:
                return hit.actor
        except Exception:
            pass

    return None
