"""
Unreal Engine Integration for nD Tables - GetActorBounds() Version

FIXES:
- Uses GetActorBounds() for automatic cell sizing
- Proper min_depth respecting actual text depth
- Back face gridlines fixed by positioning far edges correctly
"""

import numpy as np
from typing import List, Tuple, Optional, Dict
from .ndtable import Table, Axis

import unreal_engine as ue
from unreal_engine import FVector, FRotator, FTransform
from unreal_engine.enums import EComponentMobility
from unreal_engine.classes import (
    StaticMeshActor, StaticMesh, Blueprint,
    InstancedStaticMeshComponent, Actor,
    KismetMathLibrary, KismetSystemLibrary
)
from unreal_engine.structs import InstancedStaticMeshInstanceData
from unreal_engine_tools import get_world


class UnrealAxisPresets:
    """Axis orientation presets"""
    
    @staticmethod
    def get_orientation_vector(preset: str, axis_index: int) -> FVector:
        presets = {
            'wall_table': [
                FVector(0, 1, 0),    # Axis 0 (rows): RIGHT (Y direction)
                FVector(0, 0, -1),   # Axis 1 (columns): DOWN (-Z direction)
                FVector(1, 0, 0),    # Axis 2 (depth): FORWARD (X direction)
                FVector(0, 0, -1),   # 4D+: spread downward
            ],
            'ground_table': [
                FVector(1, 0, 0),
                FVector(0, 1, 0),
                FVector(0, 0, 1),
                FVector(0, 0, 1),
            ],
        }
        
        if preset not in presets:
            preset = 'wall_table'
        
        vectors = presets[preset]
        if axis_index < len(vectors):
            return vectors[axis_index]
        else:
            return FVector(0, 1, 0) if axis_index % 2 == 0 else FVector(0, 0, -1)


class UnrealTableRenderer:
    """Render nD tables with GetActorBounds()-based sizing"""
    
    def __init__(self,
                 world=None,
                 cell_spacing: float = 100.0,
                 min_depth: float = 0.0,
                 padding_x_pos: float = 10.0,
                 padding_x_neg: float = 10.0,
                 padding_y_pos: float = 10.0,
                 padding_y_neg: float = 10.0,
                 padding_z_pos: float = 10.0,
                 padding_z_neg: float = 10.0,
                 orientation_preset: str = 'wall_table',
                 text_mode: str = '3d',
                 debug: bool = False,
                 aggressive_debug: bool = False):
        self.world = world
        self.base_cell_spacing = cell_spacing
        self.min_depth = min_depth
        self.padding_x_pos = padding_x_pos
        self.padding_x_neg = padding_x_neg
        self.padding_y_pos = padding_y_pos
        self.padding_y_neg = padding_y_neg
        self.padding_z_pos = padding_z_pos
        self.padding_z_neg = padding_z_neg
        self.orientation_preset = orientation_preset
        self.text_mode = text_mode
        self.debug = debug
        self.aggressive_debug = aggressive_debug
        
        self.cell_actors = {}
        self.gridline_actors = []
        
        self.cell_width_per_row = {}
        self.cell_height_per_column = {}
        self.cell_depth_per_layer = {}
        
        self.cylinder_mesh = None
        self.sphere_mesh = None
        
        if world:
            self._load_resources()
    
    def _load_resources(self):
        try:
            self.cylinder_mesh = ue.load_object(StaticMesh, '/Engine/BasicShapes/Cylinder')
            self.sphere_mesh = ue.load_object(StaticMesh, '/Engine/BasicShapes/Sphere')
            if self.aggressive_debug:
                ue.log("Loaded resources")
        except Exception as e:
            if self.aggressive_debug:
                ue.log_warning(f"Resources not loaded: {e}")
    
    def render_table(self,
                    table: Table,
                    world_location: FVector = None,
                    render_gridlines: bool = True,
                    render_text: bool = True):
        if world_location is None:
            world_location = FVector(0, 0, 0)
        
        if self.aggressive_debug:
            ue.log(f"[RENDER] {table.ndim}D table at {world_location}")
        
        if table.ndim > 3:
            self._render_nd_table(table, world_location, render_gridlines, render_text)
        else:
            self._render_direct(table, world_location, render_gridlines, render_text)
    
    def _render_direct(self, table: Table, world_location: FVector,
                      render_gridlines: bool, render_text: bool):
        origin_cell = self._get_origin_cell(table)
        
        if render_text:
            temp_actors = self._spawn_text_actors(table)
            self._measure_and_size_cells(table, temp_actors)
            self._reposition_actors(table, temp_actors, world_location, origin_cell)
            self.cell_actors.update(temp_actors)
        
        if render_gridlines:
            self._render_gridlines(table, world_location, origin_cell)
    
    def _get_origin_cell(self, table: Table) -> Tuple[int, ...]:
        origin = tuple(axis.indices[0] for axis in table.axes)
        if self.aggressive_debug:
            ue.log(f"[ORIGIN] {origin}")
        return origin
    
    def _spawn_text_actors(self, table: Table) -> Dict:
        if self.text_mode == '2d':
            blueprint_path = '/Game/Blueprints/Assets/BP_Cell2D.BP_Cell2D'
            component_name = 'NewTextRenderComponent'
        else:
            blueprint_path = '/Game/Blueprints/Assets/BP_Cell.BP_Cell'
            component_name = 'Text3DComponent'
        
        try:
            cell_bp = ue.load_object(Blueprint, blueprint_path)
        except Exception as e:
            if self.aggressive_debug:
                ue.log_warning(f"Could not load blueprint: {e}")
            return {}
        
        actors = {}
        temp_pos = FVector(0, 0, 0)
        
        for idx, cell in table.cells.items():
            try:
                value = table[idx]
            except Exception as e:
                if self.aggressive_debug:
                    ue.log_warning(f"Error evaluating {idx}: {e}")
                value = "#ERROR"
            
            if value is None:
                continue
            
            cell_actor = self.world.actor_spawn(cell_bp.GeneratedClass)
            cell_actor.set_actor_location(temp_pos)
            
            try:
                text_component = cell_actor.get_actor_component(component_name)
                if text_component:
                    text_component.Text = str(value)
            except Exception as e:
                if self.aggressive_debug:
                    ue.log_warning(f"Failed to set text: {e}")
            
            actors[idx] = cell_actor
        
        if self.aggressive_debug:
            ue.log(f"Spawned {len(actors)} text actors")
        
        return actors
    
    def _measure_and_size_cells(self, table: Table, actors: Dict):
        self.cell_width_per_row.clear()
        self.cell_height_per_column.clear()
        self.cell_depth_per_layer.clear()
        
        max_width_per_row = {}
        max_height_per_column = {}
        max_depth_per_layer = {}
        
        for idx, actor in actors.items():
            try:
                origin, box_extent = actor.GetActorBounds()
                
                width = box_extent.y * 2
                height = box_extent.z * 2
                depth = box_extent.x * 2
                
                if self.aggressive_debug:
                    ue.log(f"Cell {idx} bounds: box_extent=({box_extent.x}, {box_extent.y}, {box_extent.z})")
                    ue.log(f"Cell {idx} calculated: width={width}, height={height}, depth={depth}")
                
                row_idx = idx[0] if len(idx) > 0 else 0
                if row_idx not in max_width_per_row:
                    max_width_per_row[row_idx] = width
                else:
                    max_width_per_row[row_idx] = max(max_width_per_row[row_idx], width)
                
                col_idx = idx[1] if len(idx) > 1 else 0
                if col_idx not in max_height_per_column:
                    max_height_per_column[col_idx] = height
                else:
                    max_height_per_column[col_idx] = max(max_height_per_column[col_idx], height)
                
                depth_idx = idx[2] if len(idx) > 2 else 0
                if depth_idx not in max_depth_per_layer:
                    max_depth_per_layer[depth_idx] = depth
                else:
                    max_depth_per_layer[depth_idx] = max(max_depth_per_layer[depth_idx], depth)
                    
            except Exception as e:
                if self.aggressive_debug:
                    ue.log_warning(f"Error measuring {idx}: {e}")
        
        # Apply padding based on orientation
        # For wall_table: X=depth (forward/back), Y=width (left/right), Z=height (up/down)
        
        for row_idx, width in max_width_per_row.items():
            # Width goes in Y direction for wall_table
            self.cell_width_per_row[row_idx] = width + self.padding_y_pos + self.padding_y_neg
        
        for col_idx, height in max_height_per_column.items():
            # Height goes in Z direction for wall_table
            self.cell_height_per_column[col_idx] = height + self.padding_z_pos + self.padding_z_neg
        
        for depth_idx, depth in max_depth_per_layer.items():
            # Depth goes in X direction for wall_table
            actual_depth = max(self.min_depth, depth) if self.min_depth > 0 else depth
            self.cell_depth_per_layer[depth_idx] = actual_depth + self.padding_x_pos + self.padding_x_neg
        
        if self.aggressive_debug:
            ue.log(f"Row widths (Y): {self.cell_width_per_row}")
            ue.log(f"Column heights (Z): {self.cell_height_per_column}")
            ue.log(f"Depths (X): {self.cell_depth_per_layer}")
            ue.log(f"Padding - X:{self.padding_x_pos}/{self.padding_x_neg}, Y:{self.padding_y_pos}/{self.padding_y_neg}, Z:{self.padding_z_pos}/{self.padding_z_neg}")
    
    def _reposition_actors(self, table: Table, actors: Dict, 
                          world_location: FVector, origin_cell: Tuple[int, ...]):
        for idx, actor in actors.items():
            pos = self._get_cell_world_position(table, idx, world_location, origin_cell)
            actor.set_actor_location(pos)
    
    def _get_cell_world_position(self, table: Table, idx: Tuple[int, ...],
                                 world_location: FVector,
                                 origin_cell: Tuple[int, ...]) -> FVector:
        offset = []
        
        for axis_idx, (cell_idx, origin_idx) in enumerate(zip(idx, origin_cell)):
            axis_indices = list(table.axes[axis_idx].indices)
            
            if cell_idx == origin_idx:
                offset.append(0.0)
            else:
                start = min(origin_idx, cell_idx)
                end = max(origin_idx, cell_idx)
                
                cumulative = 0.0
                for i in axis_indices:
                    if i < start:
                        continue
                    if i >= end:
                        break
                    
                    if axis_idx == 0:
                        spacing = self.cell_width_per_row.get(i, self.base_cell_spacing)
                    elif axis_idx == 1:
                        spacing = self.cell_height_per_column.get(i, self.base_cell_spacing)
                    else:
                        spacing = self.cell_depth_per_layer.get(i, self.base_cell_spacing)
                    
                    cumulative += spacing
                
                if cell_idx < origin_idx:
                    cumulative = -cumulative
                
                offset.append(cumulative)
        
        while len(offset) < 3:
            offset.append(0)
        
        orient = []
        for i in range(3):
            orient.append(UnrealAxisPresets.get_orientation_vector(self.orientation_preset, i))
        
        world_offset = FVector(
            offset[0] * orient[0].x + offset[1] * orient[1].x + offset[2] * orient[2].x,
            offset[0] * orient[0].y + offset[1] * orient[1].y + offset[2] * orient[2].y,
            offset[0] * orient[0].z + offset[1] * orient[1].z + offset[2] * orient[2].z,
        )
        
        return FVector(
            world_location.x + world_offset.x,
            world_location.y + world_offset.y,
            world_location.z + world_offset.z
        )
    
    def _render_gridlines(self, table: Table, world_location: FVector, origin_cell: Tuple[int, ...]):
        if self.aggressive_debug:
            ue.log("Rendering gridlines")
        
        gridlines = self._compute_gridline_endpoints(table, world_location, origin_cell)
        
        for start, end in gridlines:
            self._spawn_cylinder_between_points(start, end)
        
        if self.aggressive_debug:
            ue.log(f"Rendered {len(self.gridline_actors)} gridlines")
    
    def _compute_gridline_endpoints(self, table: Table, world_location: FVector,
                                    origin_cell: Tuple[int, ...]) -> List[Tuple[FVector, FVector]]:
        gridlines = []
        num_visual_dims = min(3, table.ndim)
        
        orient = []
        for i in range(3):
            orient.append(UnrealAxisPresets.get_orientation_vector(self.orientation_preset, i))
        
        if num_visual_dims == 1:
            axis0_indices = list(table.axes[0].indices)
            
            start_idx = (axis0_indices[0],)
            start_pos = self._get_cell_world_position(table, start_idx, world_location, origin_cell)
            
            total_span = sum(self.cell_width_per_row.get(i, self.base_cell_spacing) 
                           for i in axis0_indices)
            
            extend = FVector(orient[0].x * total_span, orient[0].y * total_span, orient[0].z * total_span)
            end_pos = FVector(start_pos.x + extend.x, start_pos.y + extend.y, start_pos.z + extend.z)
            
            gridlines.append((start_pos, end_pos))
        
        elif num_visual_dims == 2:
            axis0_indices = list(table.axes[0].indices)
            axis1_indices = list(table.axes[1].indices)
            
            n_rows = len(axis0_indices)
            n_cols = len(axis1_indices)
            
            total_row_span = sum(self.cell_width_per_row.get(i, self.base_cell_spacing) for i in axis0_indices)
            total_col_span = sum(self.cell_height_per_column.get(j, self.base_cell_spacing) for j in axis1_indices)
            
            # HORIZONTAL (n_rows + 1)
            for i in range(n_rows + 1):
                cumulative_row = sum(self.cell_width_per_row.get(axis0_indices[k], self.base_cell_spacing)
                                   for k in range(i) if k < n_rows)
                
                ref_idx = (axis0_indices[0], axis1_indices[0])
                start_pos = self._get_cell_world_position(table, ref_idx, world_location, origin_cell)
                
                row_shift = FVector(orient[0].x * cumulative_row, orient[0].y * cumulative_row, orient[0].z * cumulative_row)
                col_extend = FVector(orient[1].x * total_col_span, orient[1].y * total_col_span, orient[1].z * total_col_span)
                
                line_start = FVector(start_pos.x + row_shift.x, start_pos.y + row_shift.y, start_pos.z + row_shift.z)
                line_end = FVector(line_start.x + col_extend.x, line_start.y + col_extend.y, line_start.z + col_extend.z)
                
                gridlines.append((line_start, line_end))
            
            # VERTICAL (n_cols + 1)
            for j in range(n_cols + 1):
                cumulative_col = sum(self.cell_height_per_column.get(axis1_indices[k], self.base_cell_spacing)
                                   for k in range(j) if k < n_cols)
                
                ref_idx = (axis0_indices[0], axis1_indices[0])
                start_pos = self._get_cell_world_position(table, ref_idx, world_location, origin_cell)
                
                col_shift = FVector(orient[1].x * cumulative_col, orient[1].y * cumulative_col, orient[1].z * cumulative_col)
                row_extend = FVector(orient[0].x * total_row_span, orient[0].y * total_row_span, orient[0].z * total_row_span)
                
                line_start = FVector(start_pos.x + col_shift.x, start_pos.y + col_shift.y, start_pos.z + col_shift.z)
                line_end = FVector(line_start.x + row_extend.x, line_start.y + row_extend.y, line_start.z + row_extend.z)
                
                gridlines.append((line_start, line_end))
        
        elif num_visual_dims == 3:
            axis0_indices = list(table.axes[0].indices)
            axis1_indices = list(table.axes[1].indices)
            axis2_indices = list(table.axes[2].indices)
            
            n0, n1, n2 = len(axis0_indices), len(axis1_indices), len(axis2_indices)
            
            total_row = sum(self.cell_width_per_row.get(i, self.base_cell_spacing) for i in axis0_indices)
            total_col = sum(self.cell_height_per_column.get(j, self.base_cell_spacing) for j in axis1_indices)
            total_depth = sum(self.cell_depth_per_layer.get(k, self.base_cell_spacing) for k in axis2_indices)
            
            if self.aggressive_debug:
                ue.log(f"3D spans - row:{total_row}, col:{total_col}, depth:{total_depth}")
                ue.log(f"Expected gridlines: {(n1+1)*(n2+1)} + {(n0+1)*(n2+1)} + {(n0+1)*(n1+1)} = {(n1+1)*(n2+1) + (n0+1)*(n2+1) + (n0+1)*(n1+1)}")
            
            # Lines parallel to axis 0 (rows)
            for j in range(n1 + 1):
                cum_col = sum(self.cell_height_per_column.get(axis1_indices[k], self.base_cell_spacing) 
                           for k in range(min(j, n1)))
                
                for k in range(n2 + 1):
                    cum_depth = sum(self.cell_depth_per_layer.get(axis2_indices[m], self.base_cell_spacing)
                                 for m in range(min(k, n2)))
                    
                    ref_idx = (axis0_indices[0], axis1_indices[0], axis2_indices[0])
                    start_pos = self._get_cell_world_position(table, ref_idx, world_location, origin_cell)
                    
                    shifts = FVector(
                        orient[1].x * cum_col + orient[2].x * cum_depth,
                        orient[1].y * cum_col + orient[2].y * cum_depth,
                        orient[1].z * cum_col + orient[2].z * cum_depth
                    )
                    extend = FVector(orient[0].x * total_row, orient[0].y * total_row, orient[0].z * total_row)
                    
                    line_start = FVector(start_pos.x + shifts.x, start_pos.y + shifts.y, start_pos.z + shifts.z)
                    line_end = FVector(line_start.x + extend.x, line_start.y + extend.y, line_start.z + extend.z)
                    gridlines.append((line_start, line_end))
            
            # Lines parallel to axis 1 (columns)
            for i in range(n0 + 1):
                cum_row = sum(self.cell_width_per_row.get(axis0_indices[k], self.base_cell_spacing)
                           for k in range(min(i, n0)))
                
                for k in range(n2 + 1):
                    cum_depth = sum(self.cell_depth_per_layer.get(axis2_indices[m], self.base_cell_spacing)
                                 for m in range(min(k, n2)))
                    
                    ref_idx = (axis0_indices[0], axis1_indices[0], axis2_indices[0])
                    start_pos = self._get_cell_world_position(table, ref_idx, world_location, origin_cell)
                    
                    shifts = FVector(
                        orient[0].x * cum_row + orient[2].x * cum_depth,
                        orient[0].y * cum_row + orient[2].y * cum_depth,
                        orient[0].z * cum_row + orient[2].z * cum_depth
                    )
                    extend = FVector(orient[1].x * total_col, orient[1].y * total_col, orient[1].z * total_col)
                    
                    line_start = FVector(start_pos.x + shifts.x, start_pos.y + shifts.y, start_pos.z + shifts.z)
                    line_end = FVector(line_start.x + extend.x, line_start.y + extend.y, line_start.z + extend.z)
                    gridlines.append((line_start, line_end))
            
            # Lines parallel to axis 2 (depth)
            for i in range(n0 + 1):
                cum_row = sum(self.cell_width_per_row.get(axis0_indices[k], self.base_cell_spacing)
                           for k in range(min(i, n0)))
                
                for j in range(n1 + 1):
                    cum_col = sum(self.cell_height_per_column.get(axis1_indices[k], self.base_cell_spacing)
                               for k in range(min(j, n1)))
                    
                    ref_idx = (axis0_indices[0], axis1_indices[0], axis2_indices[0])
                    start_pos = self._get_cell_world_position(table, ref_idx, world_location, origin_cell)
                    
                    shifts = FVector(
                        orient[0].x * cum_row + orient[1].x * cum_col,
                        orient[0].y * cum_row + orient[1].y * cum_col,
                        orient[0].z * cum_row + orient[1].z * cum_col
                    )
                    extend = FVector(orient[2].x * total_depth, orient[2].y * total_depth, orient[2].z * total_depth)
                    
                    line_start = FVector(start_pos.x + shifts.x, start_pos.y + shifts.y, start_pos.z + shifts.z)
                    line_end = FVector(line_start.x + extend.x, line_start.y + extend.y, line_start.z + extend.z)
                    gridlines.append((line_start, line_end))
        
        return gridlines
    
    def _spawn_cylinder_between_points(self, start: FVector, end: FVector):
        if not self.cylinder_mesh:
            return
        
        mid = FVector((start.x + end.x) / 2, (start.y + end.y) / 2, (start.z + end.z) / 2)
        distance = KismetMathLibrary.Vector_Distance(start, end)
        
        if distance < 0.01:
            return
        
        rotation = KismetMathLibrary.FindLookAtRotation(start, end)
        rotation.pitch += 90
        
        cylinder = self.world.actor_spawn(StaticMeshActor)
        cylinder.StaticMeshComponent.SetStaticMesh(self.cylinder_mesh)
        cylinder.StaticMeshComponent.Mobility = EComponentMobility.Movable
        
        scale = FVector(0.02, 0.02, distance / 100.0)
        transform = FTransform(mid, rotation, scale)
        cylinder.set_actor_transform(transform)
        
        self.gridline_actors.append(cylinder)
    
    def _render_nd_table(self, table: Table, base_location: FVector,
                        render_gridlines: bool, render_text: bool):
        if self.aggressive_debug:
            ue.log(f"[RENDER nD] Spreading {table.ndim}D")
        
        extra_dims = table.ndim - 3
        
        import itertools
        extra_axes = [table.axes[3 + i].indices for i in range(extra_dims)]
        combinations = list(itertools.product(*extra_axes))
        
        total_slices = len(combinations)
        
        if table.ndim == 4:
            grid_cols, grid_rows, grid_depth = total_slices, 1, 1
        elif table.ndim == 5:
            grid_cols = int(np.ceil(np.sqrt(total_slices)))
            grid_rows = int(np.ceil(total_slices / grid_cols))
            grid_depth = 1
        else:
            grid_cols = int(np.ceil(total_slices ** (1/3)))
            grid_rows = int(np.ceil(np.sqrt(total_slices / grid_cols)))
            grid_depth = int(np.ceil(total_slices / (grid_cols * grid_rows)))
        
        max_size = max(len(table.axes[i]) for i in range(min(3, table.ndim)))
        slice_spacing_xy = max_size * self.base_cell_spacing * 1.5
        slice_spacing_z = max_size * self.base_cell_spacing * 2.0
        
        has_negative = any(min(table.axes[3 + i].indices) < 0 for i in range(extra_dims))
        
        for idx, extra_combo in enumerate(combinations):
            col = idx % grid_cols
            row = (idx // grid_cols) % grid_rows
            depth = idx // (grid_cols * grid_rows)
            
            slice_shape = tuple(len(table.axes[i]) for i in range(min(3, table.ndim)))
            slice_3d = Table(shape=slice_shape)
            
            for cell_idx in table.cells.keys():
                if len(cell_idx) > 3:
                    extra_idx = cell_idx[3:]
                    if extra_idx == extra_combo:
                        slice_idx = cell_idx[:3] if len(cell_idx) >= 3 else cell_idx
                        while len(slice_idx) < 3:
                            slice_idx = slice_idx + (0,)
                        slice_3d[slice_idx] = table[cell_idx]
            
            if has_negative:
                z_offset = sum(val * slice_spacing_z / (extra_dims + 1) for i, val in enumerate(extra_combo))
            else:
                z_offset = -depth * slice_spacing_z
            
            slice_location = FVector(
                base_location.x + col * slice_spacing_xy,
                base_location.y + row * slice_spacing_xy,
                base_location.z + z_offset
            )
            
            self._render_direct(slice_3d, slice_location, render_gridlines, render_text)
            
            dim_names = [f"D{4+i}={val}" for i, val in enumerate(extra_combo)]
            label_text = " | ".join(dim_names) if dim_names else "Base"
            label_pos = FVector(slice_location.x, slice_location.y, slice_location.z + 50)
            self._spawn_text_label(label_text, label_pos)
    
    def _spawn_text_label(self, text: str, position: FVector):
        blueprint_path = '/Game/Blueprints/Assets/BP_Cell.BP_Cell' if self.text_mode == '3d' else '/Game/Blueprints/Assets/BP_Cell2D.BP_Cell2D'
        component_name = 'Text3DComponent' if self.text_mode == '3d' else 'NewTextRenderComponent'
        
        try:
            cell_bp = ue.load_object(Blueprint, blueprint_path)
            label_actor = self.world.actor_spawn(cell_bp.GeneratedClass)
            label_actor.set_actor_location(position)
            
            text_component = label_actor.get_actor_component(component_name)
            if text_component:
                text_component.Text = text
            
            self.cell_actors[f"label_{text}"] = label_actor
        except Exception as e:
            if self.aggressive_debug:
                ue.log_warning(f"Failed label: {e}")
    
    def clear_rendering(self):
        for actor in self.cell_actors.values():
            try:
                actor.actor_destroy()
            except:
                pass
        
        for actor in self.gridline_actors:
            try:
                actor.actor_destroy()
            except:
                pass
        
        self.cell_actors.clear()
        self.gridline_actors.clear()


class TableAnimator:
    def __init__(self, renderer):
        self.renderer = renderer

class TableMouseHandler:
    def __init__(self, renderer):
        self.renderer = renderer
