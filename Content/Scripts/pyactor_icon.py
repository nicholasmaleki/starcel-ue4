import unreal_engine as ue
from unreal_engine import FVector, FRotator, FTransform
from unreal_engine_tools import find_component

# ---------------------------------------------------------------------------
# Python component: hover-shrink for spawn_icon
# ---------------------------------------------------------------------------
class IconSphere:
    """
    Mouse-hover shrink animation for a StaticMeshActor.
    Requires 'Enable Mouse over Events' in Project Settings > Input.
    """
    HOVER_DELTA = 0.1
    LERP_SPEED  = 8.0

    def begin_play(self):
        self.base_scale   = self.uobject.get_actor_scale()
        self.target_scale = self.base_scale
        try:
            smc = find_component(self.uobject, "Sphere")
            # print(smc)
            smc.bind_event('OnBeginCursorOver', self.on_hover_begin)
            smc.bind_event('OnEndCursorOver',   self.on_hover_end)
        except Exception as e:
            ue.log_warning(f'IconHoverComponent: cursor events unavailable: {e}')

    def on_hover_begin(self, mesh):
        d  = self.HOVER_DELTA
        bs = self.base_scale
        self.target_scale = FVector(bs.x - d, bs.y - d, bs.z - d)

    def on_hover_end(self, mesh):
        self.target_scale = self.base_scale

    def tick(self, dt):
        cur = self.uobject.get_actor_scale()
        tgt = self.target_scale
        a   = min(1.0, self.LERP_SPEED * dt)
        self.uobject.set_actor_scale(FVector(
            cur.x + (tgt.x - cur.x) * a,
            cur.y + (tgt.y - cur.y) * a,
            cur.z + (tgt.z - cur.z) * a,
        ))