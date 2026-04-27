import unreal_engine as ue
from unreal_engine_tools import find_component

try:
    from unreal_engine.classes import Material
except Exception:
    Material = None


class PyActorCursor:
    """Blinking insertion caret as a self-contained PyActor.

    Spawn via spawn_pyactor with a 'Cube' StaticMeshComponent root, e.g.
        spawn_pyactor(
            'pyactor_cursor', 'PyActorCursor',
            components=[dict(class_name='StaticMeshComponent',
                             name='Cube', root=True,
                             mesh='/Engine/BasicShapes/Cube.Cube')])

    Caller drives the caret with ``move_to(world_pt, scale_vec, rotation)``.
    Blinking is automatic at BLINK_RATE seconds per cycle once visible.
    Use ``hide()`` to stop blinking and hide.

    PyActorText3D owns the singleton instance and is the single point of
    truth for cursor placement (computes glyph-relative world coords);
    this class only renders/blinks.
    """

    BLINK_RATE      = 1.0
    CURSOR_MAT_PATH = '/Game/Materials/M_Color_Translucent.M_Color_Translucent'
    MESH_COMPONENT  = 'Cube'

    def begin_play(self):
        self._timer   = 0.0
        self._visible = False
        self._active  = False

        try:
            self.uobject.SetActorHiddenInGame(True)
        except Exception:
            pass

        # Translucent material (cursor is overlaid on text — never block clicks)
        self._smc = find_component(self.uobject, self.MESH_COMPONENT)
        if self._smc is not None and Material is not None:
            try:
                mat = ue.load_object(Material, self.CURSOR_MAT_PATH)
                mid = self._smc.create_material_instance_dynamic(mat)
                self._smc.set_material(0, mid)
            except Exception as e:
                ue.log_warning(f'PyActorCursor: material setup failed: {e}')
        try:
            self.uobject.SetActorEnableCollision(False)
        except Exception:
            pass

        ue.log('PyActorCursor: ready')

    def move_to(self, world_pt, scale_vec, rotation=None):
        """Position the caret in world space, set scale/rotation, show + blink."""
        try:
            self.uobject.set_actor_scale(scale_vec)
        except Exception:
            pass
        try:
            self.uobject.set_actor_location(world_pt)
        except Exception:
            pass
        if rotation is not None:
            try:
                self.uobject.set_actor_rotation(rotation)
            except Exception:
                pass
        self.show()

    def show(self):
        try:
            self.uobject.SetActorHiddenInGame(False)
        except Exception:
            pass
        self._active  = True
        self._timer   = 0.0
        self._visible = True

    def hide(self):
        try:
            self.uobject.SetActorHiddenInGame(True)
        except Exception:
            pass
        self._active  = False
        self._visible = False

    def tick(self, dt):
        if not self._active:
            return
        self._timer += dt
        half = self.BLINK_RATE * 0.5
        should_show = (self._timer % self.BLINK_RATE) < half
        if should_show != self._visible:
            self._visible = should_show
            try:
                self.uobject.SetActorHiddenInGame(not should_show)
            except Exception:
                pass
