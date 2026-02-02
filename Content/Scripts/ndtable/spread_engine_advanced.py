"""
Advanced Spread Engine for nD Tables

Spreading is spatial table projection - replicating, arranging, and transforming
tables in n-dimensional space.

Features:
- Spread 0D → 1D, 1D → 2D, 2D → 3D, etc.
- Arbitrary direction vectors
- Multi-axis spreading
- Split into slices or replicate whole
- Function-based spreading
- Center-out, backwards, from any cell
"""

import numpy as np
from typing import List, Tuple, Union, Callable, Optional, Dict
from nd_table_v2 import Table, Axis


# ============================================================================
# SPREAD ENGINE
# ============================================================================

class SpreadEngine:
    """
    Advanced multi-dimensional table spreading
    
    Spreading transforms tables spatially:
    - 0D table → line of tables (1D)
    - 1D table → plane of tables (2D)
    - 2D table → volume of tables (3D)
    - 3D table → hypervolume or multiple 3D arrangements
    
    Can split tables into slices or replicate whole tables.
    """
    
    def __init__(self, debug: bool = False):
        self.debug = debug
        
    def spread(self,
               source: Union[Table, List[Table]],
               mode: str = 'replicate',
               direction: Union[str, Tuple[float, ...]] = 'x',
               count: int = None,
               spacing: float = 100.0,
               pattern: str = 'linear',
               from_cell: Union[str, Tuple] = None,
               split_axis: int = None,
               function: Callable = None,
               **kwargs) -> Union[List[Table], Dict]:
        """
        Spread tables in n-dimensional space
        
        Args:
            source: Single table or list of tables
            mode: 'replicate' (copy whole table) or 'slice' (split into pieces)
            direction: Direction to spread ('x', '-y', 'both', tuple vector, 'multi')
            count: Number of copies/slices (auto if None)
            spacing: Distance between tables
            pattern: 'linear', 'grid', 'radial', 'spiral', 'function'
            from_cell: Starting cell (None = auto, 'center' = center, or index)
            split_axis: Which axis to split along (for slice mode)
            function: Custom function for positioning (t -> position)
            
        Returns:
            List of tables or dict with structure info
        """
        # Normalize source
        if isinstance(source, Table):
            tables = [source]
            single_source = True
        else:
            tables = source
            single_source = False
            
        if self.debug:
            print(f"[SPREAD] Mode: {mode}, Direction: {direction}, Pattern: {pattern}")
            print(f"  Source: {len(tables)} table(s)")
            
        # Execute spread based on mode
        if mode == 'replicate':
            result = self._spread_replicate(tables, direction, count, spacing, pattern, function)
        elif mode == 'slice':
            result = self._spread_slice(tables[0] if single_source else tables, 
                                       direction, split_axis, spacing, pattern)
        else:
            raise ValueError(f"Unknown spread mode: {mode}")
            
        if self.debug:
            print(f"  Result: {len(result) if isinstance(result, list) else 'dict'}")
            
        return result
        
    def _spread_replicate(self,
                         tables: List[Table],
                         direction: Union[str, Tuple],
                         count: Optional[int],
                         spacing: float,
                         pattern: str,
                         function: Optional[Callable]) -> List[Tuple[Table, Tuple[float, ...]]]:
        """
        Replicate tables in space
        
        Returns list of (table, position) tuples
        """
        if count is None:
            count = len(tables)
            
        # Parse direction
        direction_vec = self._parse_direction(direction)
        
        # Generate positions based on pattern
        if pattern == 'linear':
            positions = self._linear_positions(count, direction_vec, spacing)
        elif pattern == 'grid':
            positions = self._grid_positions(count, direction_vec, spacing)
        elif pattern == 'radial':
            positions = self._radial_positions(count, spacing)
        elif pattern == 'spiral':
            positions = self._spiral_positions(count, spacing)
        elif pattern == 'function' and function:
            positions = self._function_positions(count, function, spacing)
        else:
            raise ValueError(f"Unknown pattern: {pattern}")
            
        # Pair tables with positions
        result = []
        for i in range(count):
            table = tables[i % len(tables)]  # Repeat if not enough tables
            pos = positions[i]
            result.append((table, pos))
            
        return result
        
    def _spread_slice(self,
                     table: Table,
                     direction: Union[str, Tuple],
                     split_axis: Optional[int],
                     spacing: float,
                     pattern: str) -> List[Tuple[Table, Tuple[float, ...]]]:
        """
        Slice table into lower-dimensional pieces
        
        Examples:
        - 2D table → multiple 1D tables (sliced along rows or columns)
        - 3D table → multiple 2D tables (sliced along depth)
        """
        if split_axis is None:
            # Default: split along last axis
            split_axis = table.ndim - 1
            
        if split_axis >= table.ndim:
            raise ValueError(f"Split axis {split_axis} >= table dimensions {table.ndim}")
            
        if self.debug:
            print(f"  Slicing along axis {split_axis}")
            
        # Create slices
        slices = []
        axis = table.axes[split_axis]
        
        for idx in axis.indices:
            # Extract slice
            # Build slice tuple: [:, :, idx, :, ...]
            slice_idx = [slice(None)] * table.ndim
            slice_idx[split_axis] = idx
            
            # Get slice as new table
            # TODO: Implement proper slicing
            slice_table = table  # Placeholder
            slices.append(slice_table)
            
        # Position slices
        direction_vec = self._parse_direction(direction)
        positions = self._linear_positions(len(slices), direction_vec, spacing)
        
        result = [(t, p) for t, p in zip(slices, positions)]
        return result
        
    def _parse_direction(self, direction: Union[str, Tuple]) -> np.ndarray:
        """
        Parse direction specification
        
        Accepts:
        - 'x', 'y', 'z', etc. (axis names)
        - '-x', '-y' (negative directions)
        - 'both' (bidirectional)
        - 'multi' (multi-axis)
        - (x, y, z) tuple (direct vector)
        """
        if isinstance(direction, (tuple, list)):
            return np.array(direction)
            
        if isinstance(direction, np.ndarray):
            return direction
            
        # String specifications
        if direction == 'both':
            return np.array([0, 0, 0])  # Special marker
        elif direction == 'multi':
            return np.array([0, 0, 0])  # Special marker
        else:
            # Parse axis name
            negative = direction.startswith('-')
            axis_name = direction.lstrip('-')
            
            # Map to vector
            axis_map = {
                'x': np.array([1, 0, 0]),
                'y': np.array([0, 1, 0]),
                'z': np.array([0, 0, 1]),
                'w': np.array([0, 0, 0, 1]),
            }
            
            vec = axis_map.get(axis_name, np.array([1, 0, 0]))
            
            if negative:
                vec = -vec
                
            return vec
            
    def _linear_positions(self,
                         count: int,
                         direction: np.ndarray,
                         spacing: float) -> List[Tuple[float, ...]]:
        """Generate linear positions along direction"""
        positions = []
        
        # Normalize direction
        if np.linalg.norm(direction) > 0:
            direction = direction / np.linalg.norm(direction)
        else:
            direction = np.array([1, 0, 0])
            
        for i in range(count):
            pos = direction * spacing * i
            positions.append(tuple(pos))
            
        return positions
        
    def _grid_positions(self,
                       count: int,
                       direction: np.ndarray,
                       spacing: float) -> List[Tuple[float, ...]]:
        """
        Generate grid positions
        
        Spreads in 2D grid pattern
        """
        # Calculate grid dimensions
        grid_size = int(np.ceil(np.sqrt(count)))
        
        positions = []
        for i in range(count):
            row = i // grid_size
            col = i % grid_size
            
            pos = np.array([col * spacing, row * spacing, 0])
            positions.append(tuple(pos))
            
        return positions
        
    def _radial_positions(self,
                         count: int,
                         spacing: float) -> List[Tuple[float, ...]]:
        """Generate radial positions (circle)"""
        positions = []
        angle_step = 2 * np.pi / count
        
        for i in range(count):
            angle = i * angle_step
            x = spacing * np.cos(angle)
            y = spacing * np.sin(angle)
            z = 0
            positions.append((x, y, z))
            
        return positions
        
    def _spiral_positions(self,
                         count: int,
                         spacing: float) -> List[Tuple[float, ...]]:
        """Generate spiral positions"""
        positions = []
        angle_step = np.pi / 4  # 45 degrees
        
        for i in range(count):
            angle = i * angle_step
            radius = spacing * (i * 0.5)  # Expanding spiral
            
            x = radius * np.cos(angle)
            y = radius * np.sin(angle)
            z = 0
            positions.append((x, y, z))
            
        return positions
        
    def _function_positions(self,
                           count: int,
                           function: Callable,
                           spacing: float) -> List[Tuple[float, ...]]:
        """Generate positions using custom function"""
        positions = []
        
        for i in range(count):
            t = i * spacing
            pos = function(t)
            
            # Ensure tuple format
            if isinstance(pos, np.ndarray):
                pos = tuple(pos)
            elif not isinstance(pos, tuple):
                pos = (pos, 0, 0)
                
            positions.append(pos)
            
        return positions
        
    def spread_multi_axis(self,
                         table: Table,
                         axes: List[int],
                         spacing: List[float],
                         counts: List[int]) -> List[Tuple[Table, Tuple[float, ...]]]:
        """
        Spread along multiple axes simultaneously
        
        Args:
            table: Source table
            axes: List of axis indices to spread along
            spacing: Spacing for each axis
            counts: Number of copies along each axis
            
        Returns:
            List of (table, position) tuples arranged in nD grid
        """
        if len(axes) != len(spacing) != len(counts):
            raise ValueError("axes, spacing, and counts must have same length")
            
        if self.debug:
            print(f"[MULTI-AXIS SPREAD] Axes: {axes}, Counts: {counts}")
            
        # Generate grid positions
        positions = []
        
        # Build index ranges for each axis
        ranges = [range(c) for c in counts]
        
        # Generate all combinations
        import itertools
        for combo in itertools.product(*ranges):
            # Calculate position
            pos = [0.0, 0.0, 0.0]
            for i, (axis_idx, idx, space) in enumerate(zip(axes, combo, spacing)):
                if axis_idx < 3:  # Only affect first 3 dimensions visually
                    pos[axis_idx] += idx * space
                    
            positions.append((table, tuple(pos)))
            
        if self.debug:
            print(f"  Generated {len(positions)} positions")
            
        return positions
        
    def spread_from_center(self,
                          table: Table,
                          direction: Union[str, Tuple],
                          count: int,
                          spacing: float) -> List[Tuple[Table, Tuple[float, ...]]]:
        """
        Spread outward from center
        
        Creates symmetric arrangement
        """
        if self.debug:
            print(f"[CENTER SPREAD] Count: {count}")
            
        direction_vec = self._parse_direction(direction)
        
        # Normalize
        if np.linalg.norm(direction_vec) > 0:
            direction_vec = direction_vec / np.linalg.norm(direction_vec)
            
        positions = []
        
        # Center position
        if count % 2 == 1:
            # Odd count: one at center
            positions.append((table, (0, 0, 0)))
            side_count = count // 2
        else:
            # Even count: symmetric around center
            side_count = count // 2
            
        # Spread both directions
        for i in range(1, side_count + 1):
            pos_forward = direction_vec * spacing * i
            pos_backward = -direction_vec * spacing * i
            
            positions.append((table, tuple(pos_forward)))
            positions.append((table, tuple(pos_backward)))
            
        return positions[:count]  # Ensure exact count
        
    def spread_along_curve(self,
                          table: Table,
                          curve_function: Callable[[float], Tuple[float, ...]],
                          count: int,
                          t_range: Tuple[float, float] = (0, 1)) -> List[Tuple[Table, Tuple[float, ...]]]:
        """
        Spread tables along a parametric curve
        
        Args:
            table: Table to spread
            curve_function: Function t -> (x, y, z) defining curve
            count: Number of tables
            t_range: Parameter range (start, end)
            
        Examples:
            # Parabola
            curve = lambda t: (t, t**2, 0)
            
            # Helix
            curve = lambda t: (cos(t), sin(t), t)
            
            # Sine wave
            curve = lambda t: (t, sin(t), 0)
        """
        if self.debug:
            print(f"[CURVE SPREAD] Count: {count}, Range: {t_range}")
            
        t_start, t_end = t_range
        t_values = np.linspace(t_start, t_end, count)
        
        positions = []
        for t in t_values:
            pos = curve_function(t)
            positions.append((table, pos))
            
        return positions


# ============================================================================
# DIMENSIONAL PROJECTION
# ============================================================================

class DimensionalProjector:
    """
    Project tables between dimensions
    
    Examples:
    - Project 3D table to 2D (flatten along axis)
    - Expand 2D table to 3D (extrude)
    - Slice nD table to lower D
    """
    
    def __init__(self, debug: bool = False):
        self.debug = debug
        
    def project_down(self,
                    table: Table,
                    axis: int,
                    method: str = 'sum') -> Table:
        """
        Project table to lower dimension by collapsing an axis
        
        Args:
            table: Source table
            axis: Axis to collapse
            method: 'sum', 'mean', 'max', 'min', 'first', 'last'
            
        Returns:
            Table with one fewer dimension
        """
        if table.ndim <= 1:
            raise ValueError("Cannot project 1D or 0D table down")
            
        if self.debug:
            print(f"[PROJECT DOWN] {table.ndim}D → {table.ndim-1}D, axis={axis}, method={method}")
            
        # TODO: Implement projection
        # This requires aggregating values along the specified axis
        
        return Table(shape=(3, 3))  # Placeholder
        
    def project_up(self,
                   table: Table,
                   new_axis_size: int,
                   method: str = 'replicate') -> Table:
        """
        Project table to higher dimension
        
        Args:
            table: Source table
            new_axis_size: Size of new dimension
            method: 'replicate' (copy) or 'interpolate'
            
        Returns:
            Table with one more dimension
        """
        if self.debug:
            print(f"[PROJECT UP] {table.ndim}D → {table.ndim+1}D, new_size={new_axis_size}")
            
        # TODO: Implement
        
        return Table(shape=(3, 3, 3))  # Placeholder
        
    def slice_nD(self,
                table: Table,
                axis: int,
                index: int) -> Table:
        """
        Extract a slice from nD table
        
        Returns table with one fewer dimension
        """
        if self.debug:
            print(f"[SLICE] Extracting slice at axis={axis}, index={index}")
            
        # TODO: Implement
        
        return Table(shape=(3, 3))  # Placeholder


# ============================================================================
# SPREAD VISUALIZATION
# ============================================================================

class SpreadVisualizer:
    """
    Visualize spread patterns
    
    Helps preview spread arrangements before applying
    """
    
    def __init__(self, debug: bool = True):
        self.debug = debug
        
    def preview_positions(self,
                         positions: List[Tuple[float, ...]],
                         labels: List[str] = None):
        """Print preview of spread positions"""
        print("=== SPREAD PREVIEW ===")
        
        for i, pos in enumerate(positions):
            label = labels[i] if labels else f"Table {i}"
            print(f"  {label}: {pos}")
            
        # Simple ASCII visualization for 2D
        if all(len(p) >= 2 for p in positions):
            self._visualize_2d(positions, labels)
            
    def _visualize_2d(self,
                     positions: List[Tuple[float, ...]],
                     labels: List[str] = None):
        """ASCII visualization of 2D spread pattern"""
        print("\n2D Visualization:")
        
        # Extract x, y
        xs = [p[0] for p in positions]
        ys = [p[1] for p in positions]
        
        # Normalize to grid
        if max(xs) != min(xs):
            xs_norm = [(x - min(xs)) / (max(xs) - min(xs)) * 20 for x in xs]
        else:
            xs_norm = [10] * len(xs)
            
        if max(ys) != min(ys):
            ys_norm = [(y - min(ys)) / (max(ys) - min(ys)) * 10 for y in ys]
        else:
            ys_norm = [5] * len(ys)
            
        # Create grid
        grid = [[' ' for _ in range(22)] for _ in range(12)]
        
        # Place markers
        for i, (x, y) in enumerate(zip(xs_norm, ys_norm)):
            xi = int(x)
            yi = 11 - int(y)  # Flip Y
            if 0 <= xi < 22 and 0 <= yi < 12:
                grid[yi][xi] = str(i % 10)
                
        # Print grid
        for row in grid:
            print(''.join(row))


# ============================================================================
# EXAMPLE USAGE
# ============================================================================

def example_spreading():
    """Examples of different spread patterns"""
    
    print("=== SPREAD ENGINE EXAMPLES ===\n")
    
    # Create source table
    table = Table(shape=(3, 3))
    table['A1'] = 100
    
    engine = SpreadEngine(debug=True)
    visualizer = SpreadVisualizer()
    
    # Example 1: Linear spread
    print("\n1. LINEAR SPREAD")
    result = engine.spread(
        source=table,
        mode='replicate',
        direction='x',
        count=5,
        spacing=100.0,
        pattern='linear'
    )
    positions = [pos for _, pos in result]
    visualizer.preview_positions(positions, [f"T{i}" for i in range(len(positions))])
    
    # Example 2: Grid spread
    print("\n2. GRID SPREAD")
    result = engine.spread(
        source=table,
        mode='replicate',
        direction='x',
        count=9,
        spacing=50.0,
        pattern='grid'
    )
    positions = [pos for _, pos in result]
    visualizer.preview_positions(positions[:9])
    
    # Example 3: Spiral spread
    print("\n3. SPIRAL SPREAD")
    result = engine.spread(
        source=table,
        mode='replicate',
        direction='x',
        count=8,
        spacing=30.0,
        pattern='spiral'
    )
    positions = [pos for _, pos in result]
    visualizer.preview_positions(positions)
    
    # Example 4: Multi-axis spread
    print("\n4. MULTI-AXIS SPREAD")
    result = engine.spread_multi_axis(
        table=table,
        axes=[0, 1],  # X and Y
        spacing=[100, 100],
        counts=[3, 3]  # 3x3 grid
    )
    positions = [pos for _, pos in result]
    visualizer.preview_positions(positions[:9])
    
    # Example 5: Center spread
    print("\n5. CENTER SPREAD")
    result = engine.spread_from_center(
        table=table,
        direction='x',
        count=7,
        spacing=80.0
    )
    positions = [pos for _, pos in result]
    visualizer.preview_positions(positions)
    
    # Example 6: Curve spread
    print("\n6. CURVE SPREAD (Parabola)")
    result = engine.spread_along_curve(
        table=table,
        curve_function=lambda t: (t * 100, (t * 100) ** 2 / 500, 0),
        count=10,
        t_range=(0, 1)
    )
    positions = [pos for _, pos in result]
    visualizer.preview_positions(positions[:5])  # Show first 5


if __name__ == '__main__':
    example_spreading()
