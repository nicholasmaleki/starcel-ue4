"""
Unreal Engine Integration for nD Tables

Real implementation using UnrealEnginePython:
https://github.com/20tab/UnrealEnginePython

Features:
- Cell text rendering with rotation
- Cylinder gridlines (both instanced and regular)
- Sphere/cube placeholders
- Animation support
- Mouse interaction for resizing
"""

import numpy as np
from typing import List, Tuple, Optional, Dict
from nd_table_v2 import Table, Axis

# Unreal imports (will be available when running in Unreal)
try:
    import unreal_engine as ue
    from unreal_engine import FVector, FRotator, FTransform
    from unreal_engine.classes import (
        StaticMeshActor, StaticMesh, Blueprint,
        InstancedStaticMeshComponent, Actor,
        EComponentMobility
    )
    from unreal_engine.structs import InstancedStaticMeshInstanceData
    import unreal_engine.KismetMathLibrary as KismetMathLibrary
    
    UNREAL_AVAILABLE = True
except ImportError:
    UNREAL_AVAILABLE = False
    # Placeholders for development
    FVector = type('FVector', (), {})
    FRotator = type('FRotator', (), {})
    FTransform = type('FTransform', (), {})


# ============================================================================
# UNREAL AXIS PRESETS (Enhanced)
# ============================================================================

class UnrealAxisPresets:
    """
    Unreal Engine axis orientation presets
    
    Unreal coordinate system:
    - Z up
    - Y right  
    - X away from camera (forward)
    """
    
    # Default 16D axis labels
    DEFAULT_16D_AXIS = ["x", "y", "z", "w", "v", "u", "t", "s", 
                        "r", "q", "p", "o", "n", "m", "l", "k"]
    
    @staticmethod
    def setup_axis_presets():
        """Setup standard axis configurations"""
        default_3d_axis = UnrealAxisPresets.DEFAULT_16D_AXIS[:3]
        
        presets = {
            # Standard Unreal: Z up, Y right, X forward
            'unreal_default': default_3d_axis,
            
            # Wall-mounted table (best for 2D/3D tables on screens)
            # Y right, -Z down, X forward
            'wall_table': [default_3d_axis[1], 
                          f"-{default_3d_axis[2]}", 
                          default_3d_axis[0]],
            
            # Ground table
            'ground_table': [default_3d_axis[1],
                            f"-{default_3d_axis[0]}",
                            f"-{default_3d_axis[2]}"],
            
            # Ground table Z-up
            'ground_table_zup': [default_3d_axis[1],
                                f"-{default_3d_axis[0]}",
                                default_3d_axis[2]],
            
            # Wall graph (for 2D graphs on screens)
            'wall_graph': [default_3d_axis[1],
                          default_3d_axis[2],
                          default_3d_axis[0]],
            
            # Ground graph (Z-up)
            'ground_graph': [default_3d_axis[1],
                            default_3d_axis[0],
                            default_3d_axis[2]],
        }
        
        return presets
        
    @staticmethod
    def get_orientation_vector(preset: str, axis_idx: int) -> FVector:
        """Get unit vector for axis in preset orientation"""
        presets = UnrealAxisPresets.setup_axis_presets()
        if preset not in presets:
            raise ValueError(f"Unknown preset: {preset}")
            
        axis_spec = presets[preset][axis_idx]
        
        # Parse axis (might be negative)
        negative = axis_spec.startswith('-')
        axis_name = axis_spec.lstrip('-')
        
        # Map to Unreal vectors
        vectors = {
            'x': FVector(1, 0, 0),
            'y': FVector(0, 1, 0),
            'z': FVector(0, 0, 1),
        }
        
        vec = vectors.get(axis_name, FVector(1, 0, 0))
        if negative:
            vec = FVector(-vec.x, -vec.y, -vec.z)
            
        return vec


# ============================================================================
# UNREAL RENDERER
# ============================================================================

class UnrealTableRenderer:
    """
    Render nD tables in Unreal Engine
    
    Features:
    - Text3D cells with rotation
    - Cylinder gridlines (instanced & regular)
    - Placeholder shapes (spheres, cubes)
    - Animation support
    - Mouse interaction
    """
    
    def __init__(self, 
                 world=None,
                 cell_spacing: float = 100.0,
                 cell_size: float = 80.0,
                 orientation_preset: str = 'wall_table',
                 debug: bool = False):
        """
        Args:
            world: Unreal world object
            cell_spacing: Distance between cell centers
            cell_size: Size of each cell
            orientation_preset: Axis orientation preset
            debug: Print debug info
        """
        self.world = world
        self.cell_spacing = cell_spacing
        self.cell_size = cell_size
        self.orientation_preset = orientation_preset
        self.debug = debug
        
        # Track spawned actors
        self.cell_actors = {}  # idx -> actor
        self.gridline_actors = []
        self.instanced_gridlines = None
        
        # Cache resources
        self.cylinder_mesh = None
        self.sphere_mesh = None
        self.cube_mesh = None
        self.cell_blueprint = None
        
        if UNREAL_AVAILABLE and world:
            self._load_resources()
            
    def _load_resources(self):
        """Load Unreal assets"""
        try:
            # Load meshes
            self.cylinder_mesh = ue.load_object(StaticMesh, '/Engine/BasicShapes/Cylinder')
            self.sphere_mesh = ue.load_object(StaticMesh, '/Engine/BasicShapes/Sphere')
            self.cube_mesh = ue.load_object(StaticMesh, '/Engine/BasicShapes/Cube')
            
            # Load cell blueprint (assumes you have this)
            self.cell_blueprint = ue.load_object(Blueprint, '/Game/Blueprints/Assets/BP_Cell.BP_Cell')
            
            if self.debug:
                ue.log("Loaded Unreal resources")
        except Exception as e:
            if self.debug:
                ue.log_warning(f"Failed to load some resources: {e}")
                
    def render_table(self, 
                    table: Table,
                    origin: FVector = None,
                    render_gridlines: bool = True,
                    use_instanced_gridlines: bool = True,
                    render_text: bool = True):
        """
        Render complete table in Unreal
        
        Args:
            table: Table to render
            origin: World position for table origin (0,0,0 or 1,1,1)
            render_gridlines: Draw gridlines
            use_instanced_gridlines: Use InstancedStaticMesh for gridlines
            render_text: Render cell text
        """
        if not UNREAL_AVAILABLE:
            print("[Unreal] Not running in Unreal Engine - using placeholders")
            self._render_placeholder(table, origin)
            return
            
        if origin is None:
            origin = FVector(0, 0, 0)
            
        if self.debug:
            ue.log(f"Rendering {table.ndim}D table at {origin}")
            
        # Determine table origin cell
        origin_cell = self._get_origin_cell(table)
        
        # Render cells
        if render_text:
            self._render_cells(table, origin, origin_cell)
            
        # Render gridlines
        if render_gridlines:
            if use_instanced_gridlines:
                self._render_gridlines_instanced(table, origin, origin_cell)
            else:
                self._render_gridlines_regular(table, origin, origin_cell)
                
    def _get_origin_cell(self, table: Table) -> Tuple[int, ...]:
        """
        Get the cell that should be at the render origin
        
        Uses (0,0,0) if available, otherwise (1,1,1), or first cell
        """
        # Try (0, 0, 0)
        origin = tuple(0 for _ in range(table.ndim))
        if all(0 in axis.indices for axis in table.axes):
            return origin
            
        # Try (1, 1, 1)
        origin = tuple(1 for _ in range(table.ndim))
        if all(1 in axis.indices for axis in table.axes):
            return origin
            
        # Use first cell
        return tuple(axis.indices[0] for axis in table.axes)
        
    def _get_cell_world_position(self, 
                                 table: Table,
                                 cell_idx: Tuple[int, ...],
                                 origin_world: FVector,
                                 origin_cell: Tuple[int, ...]) -> FVector:
        """Calculate world position for a cell"""
        # Get cell offset from origin
        offset = []
        for i in range(min(3, table.ndim)):  # Only handle up to 3D visually
            cell_pos = table.axes[i].indices.index(cell_idx[i])
            origin_pos = table.axes[i].indices.index(origin_cell[i])
            offset.append((cell_pos - origin_pos) * self.cell_spacing)
            
        # Pad to 3D
        while len(offset) < 3:
            offset.append(0)
            
        # Apply orientation
        orientation_vec = self._get_orientation_vectors(table)
        
        world_offset = FVector(
            offset[0] * orientation_vec[0].x + offset[1] * orientation_vec[1].x + offset[2] * orientation_vec[2].x,
            offset[0] * orientation_vec[0].y + offset[1] * orientation_vec[1].y + offset[2] * orientation_vec[2].y,
            offset[0] * orientation_vec[0].z + offset[1] * orientation_vec[1].z + offset[2] * orientation_vec[2].z,
        )
        
        return FVector(
            origin_world.x + world_offset.x,
            origin_world.y + world_offset.y,
            origin_world.z + world_offset.z
        )
        
    def _get_orientation_vectors(self, table: Table) -> List[FVector]:
        """Get orientation vectors for table axes"""
        vectors = []
        for i in range(min(3, table.ndim)):
            vec = UnrealAxisPresets.get_orientation_vector(self.orientation_preset, i)
            vectors.append(vec)
        return vectors
        
    def _render_cells(self, 
                     table: Table,
                     origin: FVector,
                     origin_cell: Tuple[int, ...]):
        """Render all cell text"""
        if not self.cell_blueprint:
            if self.debug:
                ue.log_warning("No cell blueprint - using spheres")
            self._render_cells_placeholder(table, origin, origin_cell)
            return
            
        for idx, cell in table.cells.items():
            # Get world position
            pos = self._get_cell_world_position(table, idx, origin, origin_cell)
            
            # Get cell value
            value = table[idx]
            if value is None:
                continue
                
            # Spawn cell actor
            cell_actor = self.world.actor_spawn(self.cell_blueprint.GeneratedClass)
            
            # Set transform
            rotation = self._get_cell_rotation(table, idx)
            transform = FTransform(pos, rotation, FVector(1, 1, 1))
            cell_actor.set_actor_transform(transform)
            
            # Set text
            try:
                text_component = cell_actor.get_actor_component('Text3DComponent')
                if text_component:
                    text_component.Text = str(value)
            except:
                pass
                
            # Track actor
            self.cell_actors[idx] = cell_actor
            
        if self.debug:
            ue.log(f"Rendered {len(self.cell_actors)} cells")
            
    def _render_cells_placeholder(self,
                                  table: Table,
                                  origin: FVector,
                                  origin_cell: Tuple[int, ...]):
        """Render cells as spheres (placeholder)"""
        for idx, cell in table.cells.items():
            value = table[idx]
            if value is None:
                continue
                
            pos = self._get_cell_world_position(table, idx, origin, origin_cell)
            
            # Spawn sphere
            sphere = self.world.actor_spawn(StaticMeshActor)
            smc = sphere.StaticMeshComponent
            smc.SetStaticMesh(self.sphere_mesh)
            smc.Mobility = EComponentMobility.Movable
            
            scale = self.cell_size / 100.0
            transform = FTransform(pos, FRotator(0, 0, 0), FVector(scale, scale, scale))
            sphere.set_actor_transform(transform)
            
            self.cell_actors[idx] = sphere
            
    def _get_cell_rotation(self, table: Table, idx: Tuple[int, ...]) -> FRotator:
        """
        Get rotation for cell text
        
        Can be customized per cell or based on table orientation
        """
        # Default: face camera
        # TODO: Add custom rotation options
        return FRotator(0, 0, 0)
        
    def _render_gridlines_regular(self,
                                  table: Table,
                                  origin: FVector,
                                  origin_cell: Tuple[int, ...]):
        """Render gridlines using regular StaticMeshActors"""
        if self.debug:
            ue.log("Rendering gridlines (regular meshes)")
            
        gridlines = self._compute_gridline_endpoints(table, origin, origin_cell)
        
        for start, end in gridlines:
            self._spawn_cylinder_between_points(start, end)
            
        if self.debug:
            ue.log(f"Rendered {len(gridlines)} gridlines")
            
    def _render_gridlines_instanced(self,
                                    table: Table,
                                    origin: FVector,
                                    origin_cell: Tuple[int, ...]):
        """Render gridlines using InstancedStaticMeshComponent"""
        if self.debug:
            ue.log("Rendering gridlines (instanced)")
            
        gridlines = self._compute_gridline_endpoints(table, origin, origin_cell)
        
        # Create instanced mesh actor
        instanced_actor = self.world.actor_spawn(Actor)
        instanced_actor.set_actor_label('Gridlines_Instanced')
        instanced_actor.add_actor_root_component(InstancedStaticMeshComponent, 'Root')
        
        instanced_component = instanced_actor.get_component_by_type(InstancedStaticMeshComponent)
        instanced_component.StaticMesh = self.cylinder_mesh
        
        # Build instance data
        instances = []
        for start, end in gridlines:
            transform = self._get_cylinder_transform(start, end)
            instances.append(
                InstancedStaticMeshInstanceData(Transform=transform.get_matrix())
            )
            
        instanced_component.PerInstanceSMData = instances
        
        self.instanced_gridlines = instanced_actor
        
        if self.debug:
            ue.log(f"Rendered {len(instances)} instanced gridlines")
            
    def _compute_gridline_endpoints(self,
                                    table: Table,
                                    origin: FVector,
                                    origin_cell: Tuple[int, ...]) -> List[Tuple[FVector, FVector]]:
        """
        Compute start and end points for all gridlines
        
        Returns list of (start_point, end_point) tuples
        """
        gridlines = []
        
        # For 2D tables, draw grid
        if table.ndim == 2:
            # Vertical lines (along axis 0)
            for col_idx in table.axes[1].indices:
                start_idx = (table.axes[0].indices[0], col_idx)
                end_idx = (table.axes[0].indices[-1], col_idx)
                
                start_pos = self._get_cell_world_position(table, start_idx, origin, origin_cell)
                end_pos = self._get_cell_world_position(table, end_idx, origin, origin_cell)
                
                gridlines.append((start_pos, end_pos))
                
            # Horizontal lines (along axis 1)
            for row_idx in table.axes[0].indices:
                start_idx = (row_idx, table.axes[1].indices[0])
                end_idx = (row_idx, table.axes[1].indices[-1])
                
                start_pos = self._get_cell_world_position(table, start_idx, origin, origin_cell)
                end_pos = self._get_cell_world_position(table, end_idx, origin, origin_cell)
                
                gridlines.append((start_pos, end_pos))
                
        # For 3D tables, draw grid on each face
        elif table.ndim == 3:
            # TODO: Implement 3D gridlines
            pass
            
        return gridlines
        
    def _spawn_cylinder_between_points(self, point1: FVector, point2: FVector):
        """
        Spawn a cylinder between two points (working code from your example)
        """
        midpoint = FVector(
            (point1.x + point2.x) / 2,
            (point1.y + point2.y) / 2,
            (point1.z + point2.z) / 2
        )
        
        distance = KismetMathLibrary.Vector_Distance(point1, point2)
        
        cylinder_rotation = KismetMathLibrary.FindLookAtRotation(point1, point2)
        cylinder_rotation.pitch += 90
        
        cylinder = self.world.actor_spawn(StaticMeshActor)
        smc = cylinder.StaticMeshComponent
        smc.SetStaticMesh(self.cylinder_mesh)
        smc.Mobility = EComponentMobility.Movable
        
        # Scale: thin cylinder stretched to distance
        scale = FVector(0.1, 0.1, distance / 100.0)
        transform = FTransform(midpoint, cylinder_rotation, scale)
        cylinder.set_actor_transform(transform)
        
        self.gridline_actors.append(cylinder)
        
    def _get_cylinder_transform(self, point1: FVector, point2: FVector) -> FTransform:
        """Get transform for cylinder between two points"""
        midpoint = FVector(
            (point1.x + point2.x) / 2,
            (point1.y + point2.y) / 2,
            (point1.z + point2.z) / 2
        )
        
        distance = KismetMathLibrary.Vector_Distance(point1, point2)
        
        cylinder_rotation = KismetMathLibrary.FindLookAtRotation(point1, point2)
        cylinder_rotation.pitch += 90
        
        scale = FVector(0.1, 0.1, distance / 100.0)
        
        return FTransform(midpoint, cylinder_rotation, scale)
        
    def clear_rendering(self):
        """Clear all rendered actors"""
        if not UNREAL_AVAILABLE:
            return
            
        # Destroy cell actors
        for actor in self.cell_actors.values():
            try:
                actor.actor_destroy()
            except:
                pass
        self.cell_actors.clear()
        
        # Destroy gridlines
        for actor in self.gridline_actors:
            try:
                actor.actor_destroy()
            except:
                pass
        self.gridline_actors.clear()
        
        # Destroy instanced gridlines
        if self.instanced_gridlines:
            try:
                self.instanced_gridlines.actor_destroy()
            except:
                pass
            self.instanced_gridlines = None
            
        if self.debug:
            ue.log("Cleared all rendered actors")
            
    def _render_placeholder(self, table: Table, origin):
        """Non-Unreal placeholder rendering"""
        print(f"[Placeholder] Rendering {table.ndim}D table")
        print(f"  Origin: {origin}")
        print(f"  Shape: {table.shape}")
        print(f"  Cells: {len(table.cells) if hasattr(table, 'cells') else 'N/A'}")


# ============================================================================
# ANIMATION SUPPORT
# ============================================================================

class TableAnimator:
    """
    Animate table operations
    
    Supports:
    - Fade in/out
    - Slide transitions
    - Propagation visualization
    - Custom speeds
    """
    
    def __init__(self, renderer: UnrealTableRenderer, speed: float = 1.0):
        """
        Args:
            renderer: UnrealTableRenderer instance
            speed: Animation speed multiplier (1.0 = normal)
        """
        self.renderer = renderer
        self.speed = speed
        
    def animate_cell_update(self, 
                           table: Table,
                           cell_idx: Tuple[int, ...],
                           duration: float = 0.5):
        """Animate a cell value changing"""
        # TODO: Implement animation
        if self.renderer.debug:
            print(f"[Animation] Cell {cell_idx} update over {duration/self.speed}s")
            
    def animate_propagation(self,
                           table: Table,
                           start_cell: Tuple[int, ...],
                           affected_cells: List[Tuple[int, ...]],
                           duration: float = 1.0):
        """
        Visualize formula propagation
        
        Shows how changes flow through dependencies
        """
        if self.renderer.debug:
            print(f"[Animation] Propagation from {start_cell}")
            print(f"  Affects: {len(affected_cells)} cells")
            print(f"  Duration: {duration/self.speed}s")
            
        # TODO: Implement with colored highlights/arrows
        
    def animate_spread(self,
                      tables: List[Table],
                      positions: List,
                      duration: float = 2.0):
        """Animate tables spreading into position"""
        if self.renderer.debug:
            print(f"[Animation] Spreading {len(tables)} tables over {duration/self.speed}s")
            
        # TODO: Implement


# ============================================================================
# MOUSE INTERACTION
# ============================================================================

class TableMouseHandler:
    """
    Handle mouse interaction for table resizing
    
    Provides callbacks for resizing operations
    Will be implemented by user with:
    self.uobject.bind_key(...)
    """
    
    def __init__(self, table: Table, renderer: UnrealTableRenderer):
        self.table = table
        self.renderer = renderer
        self.is_resizing = False
        self.resize_start = None
        
    def start_resize(self):
        """Begin resize operation"""
        self.is_resizing = True
        if self.renderer.debug:
            ue.log("Started resize")
            
    def update_resize(self, mouse_delta: FVector):
        """Update during resize"""
        if not self.is_resizing:
            return
            
        # TODO: Implement resize logic
        
    def end_resize(self):
        """End resize operation"""
        self.is_resizing = False
        if self.renderer.debug:
            ue.log("Ended resize")
            
    def setup_key_bindings(self, uobject):
        """
        Setup key bindings (call from Unreal Python)
        
        Example:
            handler.setup_key_bindings(self.uobject)
        """
        # TODO: Implement with bind_key
        pass


# ============================================================================
# EXAMPLE USAGE
# ============================================================================

def example_unreal_rendering():
    """Example of rendering a table in Unreal"""
    
    # This would be called from Unreal Python context
    if not UNREAL_AVAILABLE:
        print("Run this from inside Unreal Engine")
        return
        
    # Get world
    world = ue.get_world()
    
    # Create table
    table = Table(shape=(5, 5))
    table['A1'] = 100
    table['A2'] = 200
    table['A3'] = "=A1 + A2"
    
    # Create renderer
    renderer = UnrealTableRenderer(
        world=world,
        cell_spacing=100.0,
        orientation_preset='wall_table',
        debug=True
    )
    
    # Render
    origin = FVector(0, 0, 100)
    renderer.render_table(table, origin=origin)
    
    ue.log("Table rendered successfully!")
