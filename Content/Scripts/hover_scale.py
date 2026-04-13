"""Shared hover-scale animation helpers for PyActor components.

Consolidates the identical scale-lerp and hover-callback patterns from
pyactor_icon.IconSphere and pyactor_text3d.PyActorText3D.
"""
from __future__ import annotations

try:
    from unreal_engine import FVector
except ImportError:
    FVector = None


def apply_hover_begin(actor_state, hover_direction: int = -1):
    """Set target_scale for hover-in.

    Parameters
    ----------
    actor_state : object
        Must have ``base_scale`` (FVector), ``target_scale`` (FVector),
        ``HOVER_DELTA`` (float), and ``_hovered`` (bool) attributes.
    hover_direction : int
        -1 = shrink on hover (IconSphere), +1 = grow on hover (Text3D).
    """
    actor_state._hovered = True
    delta = actor_state.HOVER_DELTA * hover_direction
    base = actor_state.base_scale
    actor_state.target_scale = FVector(
        base.x + delta, base.y + delta, base.z + delta
    )


def apply_hover_end(actor_state):
    """Reset target_scale to base on hover-out."""
    actor_state._hovered = False
    actor_state.target_scale = actor_state.base_scale


def lerp_scale(uobject, target_scale, lerp_speed: float, dt: float):
    """Smoothly interpolate actor scale toward target_scale.

    Call from tick(). Returns the lerp alpha used.
    """
    cur = uobject.get_actor_scale()
    lerp_alpha = min(1.0, lerp_speed * dt)
    uobject.set_actor_scale(FVector(
        cur.x + (target_scale.x - cur.x) * lerp_alpha,
        cur.y + (target_scale.y - cur.y) * lerp_alpha,
        cur.z + (target_scale.z - cur.z) * lerp_alpha,
    ))
    return lerp_alpha
