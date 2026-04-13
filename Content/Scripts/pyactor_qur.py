import unreal_engine as ue
from unreal_engine import FVector, FRotator, FTransform
import random

try:
    from unreal_engine.classes import StaticMeshActor, Blueprint, Material
    from unreal_engine.enums import EComponentMobility
except Exception:
    StaticMeshActor = Blueprint = Material = EComponentMobility = None

# ---------------------------------------------------------------------------
# Python component for BP_Qur — spawns a Text3D quote every 60 seconds
#
# Blueprint requirements (BP_Qur):
#   - Skeletal mesh (Qur cat character)
#   - Python component → pyactor_qur.PyActorQur
#
# The quote text is spawned as a BP_Cell (Text3DComponent) actor above
# the cat, using CatFont_Font, and replaced each interval.
# ---------------------------------------------------------------------------

QUOTES = [
    "We're all mad here.",
    "Imagination is the only weapon\nin the war against reality.",
    "Every adventure requires\na first step.",
    "If you don't know where\nyou're going, any road\nwill take you there.",
    "I am not crazy;\nmy reality is just\ndifferent than yours.",
    "Only a few find the way;\nsome don't recognize it\nwhen they do.",
    "It's no use going back\nto yesterday, because\nI was a different person then.",
    "Who in the world am I?\nAh, that's the great puzzle.",
    "Begin at the beginning\nand go on till you come\nto the end; then stop.",
    "Curiouser and curiouser!",
    "Why, sometimes I've believed\nas many as six impossible\nthings before breakfast.",
    "Not all who wander are lost.",
]

FONT_PATH = '/Game/Fonts/CatFont_Font'
QUOTE_INTERVAL = 60.0   # seconds between quote changes
QUOTE_OFFSET   = FVector(0, 0, 200)  # above the cat


class PyActorQur:
    """Spawns a rotating quote above the Qur cat using CatFont."""

    def begin_play(self):
        self._elapsed    = 0.0
        self._quote_actor = None
        self._font       = None

        try:
            self._font = ue.load_object(ue.find_class('Font'), FONT_PATH)
        except Exception as e:
            ue.log_warning(f'PyActorQur: could not load font "{FONT_PATH}": {e}')

        ue.log(f'PyActorQur: started on {self.uobject.get_name()}')
        self._show_quote()

    def tick(self, dt):
        self._elapsed += dt
        if self._elapsed >= QUOTE_INTERVAL:
            self._elapsed = 0.0
            self._show_quote()

    def _show_quote(self):
        """Destroy old quote actor and spawn a new one with a random quote."""
        # Destroy previous
        if self._quote_actor is not None:
            try:
                self._quote_actor.actor_destroy()
            except Exception:
                pass
            self._quote_actor = None

        quote = random.choice(QUOTES)

        # Spawn BP_Cell (Text3DComponent)
        try:
            bp = ue.load_object(Blueprint,
                                '/Game/Blueprints/Assets/BP_Cell.BP_Cell')
            world = self.uobject.get_world()
            loc = self.uobject.get_actor_location()
            spawn_loc = FVector(loc.x + QUOTE_OFFSET.x,
                                loc.y + QUOTE_OFFSET.y,
                                loc.z + QUOTE_OFFSET.z)
            actor = world.actor_spawn(bp.GeneratedClass, spawn_loc)

            t3d = actor.get_actor_component('Text3DComponent')
            if t3d:
                t3d.Text = quote
                if self._font:
                    t3d.Font = self._font
                # Small scale for readable text
                actor.set_actor_scale(FVector(0.3, 0.3, 0.3))

            # Attach so it follows the cat
            owner = self.uobject.get_owner()
            try:
                actor.K2_AttachToActor(owner)
            except Exception:
                pass
            actor.K2_SetActorRelativeLocation(QUOTE_OFFSET)

            self._quote_actor = actor
            ue.log(f'PyActorQur: "{quote[:30]}..."')
        except Exception as e:
            ue.log_warning(f'PyActorQur: quote spawn failed: {e}')

    def end_play(self, reason):
        if self._quote_actor is not None:
            try:
                self._quote_actor.actor_destroy()
            except Exception:
                pass
