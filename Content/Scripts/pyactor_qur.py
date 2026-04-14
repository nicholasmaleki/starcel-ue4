import unreal_engine as ue
from unreal_engine import FVector, FRotator, FTransform
import random
import pickle
import os

try:
    from unreal_engine.classes import StaticMeshActor, Blueprint, Material
    from unreal_engine.enums import EComponentMobility
except Exception:
    StaticMeshActor = Blueprint = Material = EComponentMobility = None

try:
    import worldhello
except Exception:
    worldhello = None

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
    "Hello World",
]

FONT_PATH = '/Game/Fonts/CatFont_Font'
QUOTE_INTERVAL = 90.0   # 1.5 minutes between quote changes
QUOTE_OFFSET   = FVector(0, 100, 200)  # to the right and up from the cat


class PyActorQur:
    """Spawns a rotating quote above the Qur cat using CatFont."""

    def begin_play(self):
        self._elapsed    = 0.0
        self._quote_actor = None
        self._font       = None
        self._first_quote_pending = True

        try:
            self._font = ue.load_object(ue.find_class('Font'), FONT_PATH)
        except Exception as e:
            ue.log_warning(f'PyActorQur: could not load font "{FONT_PATH}": {e}')

        # ---- Load quotes from pickle (falls back to hardcoded QUOTES) ----
        file_path = os.path.join(os.path.dirname(__file__), "quotes.pkl")
        self.__quotes = None
        try:
            with open(file_path, 'rb') as file:
                loaded_quotes_hex = pickle.load(file)
                self.__quotes = [bytes.fromhex(h).decode('utf-8') for h in loaded_quotes_hex]
                if worldhello is not None:
                    self.__quotes.append(worldhello.hello_world())
            print("Successfully unpickled quotes")
        except Exception:
            print("Failed to unpickle quotes")

        ue.log(f'PyActorQur: started on {self.uobject.get_name()}')
        # NOTE: defer first quote spawn to tick() — calling actor_spawn here
        # can fail with "running a ConstructionScript" on some PIE sessions.

    def tick(self, dt):
        # Deferred first-quote spawn (avoids ConstructionScript conflict)
        if self._first_quote_pending:
            self._first_quote_pending = False
            self._show_quote()
            return

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

        # Prefer loaded quotes, fall back to hardcoded list
        quote_pool = self.__quotes if self.__quotes else QUOTES
        quote = random.choice(quote_pool)

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
                transform = FTransform(spawn_loc, FRotator(0, 0, 90), FVector(2, 2, 2))
                actor.set_actor_transform(transform)

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
