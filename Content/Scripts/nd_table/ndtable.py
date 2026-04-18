"""
nD Table V2 - Enhanced Multi-dimensional Table System

Major improvements:
- Variable syntax: t['A3'] = A1 + A2 (stores formula)
- Numpy backend mode for performance
- Undo/redo system
- Custom cell naming
- Enhanced axis system (16D labels, per-axis zero options)
- Lists allowed anywhere tuples are used
- Cross-table formulas: =table2.A1
- Custom label ranges: ha1:he3
- Always-reevaluate mode
- Aggressive debug mode focused on dependencies
"""

import re
import numpy as np
from typing import Any, Union, List, Tuple, Optional, Callable, Dict, Set
from collections import defaultdict, deque
import warnings
import copy
import inspect


# CELL REFERENCE PROXY (for variable syntax)

class CellReference:
    """
    Proxy object for cell references that captures operations
    
    Allows: A1 + A2 to create a formula instead of evaluating immediately
    """
    
    def __init__(self, ref: str, table: 'Table' = None):
        self.ref = ref
        self.table = table
        
    def __add__(self, other):
        if isinstance(other, CellReference):
            return FormulaExpression(f"{self.ref} + {other.ref}")
        return FormulaExpression(f"{self.ref} + {other}")
        
    def __sub__(self, other):
        if isinstance(other, CellReference):
            return FormulaExpression(f"{self.ref} - {other.ref}")
        return FormulaExpression(f"{self.ref} - {other}")
        
    def __mul__(self, other):
        if isinstance(other, CellReference):
            return FormulaExpression(f"{self.ref} * {other.ref}")
        return FormulaExpression(f"{self.ref} * {other}")
        
    def __truediv__(self, other):
        if isinstance(other, CellReference):
            return FormulaExpression(f"{self.ref} / {other.ref}")
        return FormulaExpression(f"{self.ref} / {other}")
        
    def __pow__(self, other):
        if isinstance(other, CellReference):
            return FormulaExpression(f"{self.ref} ** {other.ref}")
        return FormulaExpression(f"{self.ref} ** {other}")
        
    def __repr__(self):
        return f"CellRef({self.ref})"
        
    def __str__(self):
        return self.ref


class FormulaExpression:
    """Represents a formula expression that can be assigned to a cell"""
    
    def __init__(self, expression: str):
        self.expression = expression
        
    def __add__(self, other):
        if isinstance(other, (CellReference, FormulaExpression)):
            return FormulaExpression(f"{self.expression} + {other}")
        return FormulaExpression(f"{self.expression} + {other}")
        
    def __sub__(self, other):
        if isinstance(other, (CellReference, FormulaExpression)):
            return FormulaExpression(f"{self.expression} - {other}")
        return FormulaExpression(f"{self.expression} - {other}")
        
    def __mul__(self, other):
        if isinstance(other, (CellReference, FormulaExpression)):
            return FormulaExpression(f"{self.expression} * {other}")
        return FormulaExpression(f"{self.expression} * {other}")
        
    def __truediv__(self, other):
        if isinstance(other, (CellReference, FormulaExpression)):
            return FormulaExpression(f"{self.expression} / {other}")
        return FormulaExpression(f"{self.expression} / {other}")
        
    def __repr__(self):
        return f"Formula({self.expression})"
        
    def __str__(self):
        return self.expression


def create_cell_globals():
    """Create global CellReference objects for A1-ZZ99"""
    cell_refs = {}
    
    # Generate column labels
    cols = []
    for i in range(26):
        cols.append(chr(ord('A') + i))
    for i in range(26):
        for j in range(26):
            cols.append(chr(ord('A') + i) + chr(ord('A') + j))
    
    # Create references
    for col in cols[:100]:  # Limit to 100 columns
        for row in range(1, 100):
            ref = f"{col}{row}"
            cell_refs[ref] = CellReference(ref)
            
    return cell_refs


# CELL CLASS (with numpy backend option)

class Cell:
    """Cell storage - raw values, formulas, metadata"""
    
    def __init__(self, raw_value=None, formula=None, pga_blade=None, name=None):
        self.raw_value = raw_value
        self.formula = formula
        self.pga_blade = pga_blade
        self.name = name  # Custom cell name
        self._evaluated = False
        self._cached_value = None
        
    def __repr__(self):
        parts = []
        if self.name:
            parts.append(f"name='{self.name}'")
        if self.formula:
            parts.append(f"formula='{self.formula}'")
        elif self.raw_value is not None:
            parts.append(f"value={self.raw_value}")
        return f"Cell({', '.join(parts)})"


# ENHANCED AXIS CLASS

class Axis:
    """
    Enhanced Axis with 16D labels and flexible zero options
    """
    
    # Default 16D axis labels
    DEFAULT_16D_LABELS = ["x", "y", "z", "w", "v", "u", "t", "s", 
                          "r", "q", "p", "o", "n", "m", "l", "k"]
    
    def __init__(self, 
                 start: int = -1, 
                 end: int = 1,
                 name: str = None,
                 labels: List[str] = None,
                 include_zero: bool = True,
                 include_negative_zero: bool = False,
                 include_positive_zero: bool = False,
                 use_spreadsheet_labels: bool = False,
                 spreadsheet_axis: bool = False):
        """
        Args:
            start: Starting index
            end: Ending index (inclusive)
            name: Optional axis name
            labels: Custom labels (repeats if too short)
            include_zero: Include 0 in axis (default True, was skip_zero)
            include_negative_zero: Include -0 as separate from 0
            include_positive_zero: Include +0 as separate from 0
            use_spreadsheet_labels: Use A,B,C style labels
            spreadsheet_axis: This axis uses spreadsheet labeling in table
        """
        self.start = start
        self.end = end
        self.name = name
        self.custom_labels = labels
        self.include_zero = include_zero
        self.include_negative_zero = include_negative_zero
        self.include_positive_zero = include_positive_zero
        self.use_spreadsheet_labels = use_spreadsheet_labels
        self.spreadsheet_axis = spreadsheet_axis
        
        self._generate_indices()
        
    def _generate_indices(self):
        """Generate the actual indices for this axis"""
        indices = []
        
        # Handle negative zero
        if self.include_negative_zero and self.start <= 0:
            indices.append(-0)
            
        # Main range
        for i in range(self.start, self.end + 1):
            if not self.include_zero and i == 0:
                continue
            if i == 0 and self.include_negative_zero:
                continue
            indices.append(i)
            
        # Handle positive zero
        if self.include_positive_zero and 0 in indices:
            zero_idx = indices.index(0)
            indices.insert(zero_idx + 1, +0)
            
        self.indices = indices
        
    def get_label(self, index: int) -> str:
        """Get label for a given index"""
        try:
            pos = self.indices.index(index)
        except ValueError:
            return str(index)
            
        if self.use_spreadsheet_labels or self.spreadsheet_axis:
            return spreadsheet_labels(len(self.indices))[pos]
            
        if self.custom_labels:
            label_idx = pos % len(self.custom_labels)
            if pos >= len(self.custom_labels):
                warnings.warn(f"Axis {self.name}: labels too short, repeating")
            return self.custom_labels[label_idx]
            
        return str(index)
        
    def parse_label(self, label: str) -> int:
        """Parse a label back to an index"""
        # Try as integer first
        try:
            return int(label)
        except ValueError:
            pass
            
        # Check custom labels
        if self.custom_labels:
            try:
                label_idx = self.custom_labels.index(label)
                return self.indices[label_idx]
            except ValueError:
                pass
                
        # Check spreadsheet labels
        if self.use_spreadsheet_labels or self.spreadsheet_axis:
            labels = spreadsheet_labels(len(self.indices))
            try:
                label_idx = labels.index(label.upper())
                return self.indices[label_idx]
            except ValueError:
                pass
                
        raise ValueError(f"Label '{label}' not found in axis")
        
    def __len__(self):
        return len(self.indices)
        
    def __repr__(self):
        name_str = f"'{self.name}'" if self.name else "unnamed"
        return f"Axis({name_str}, {self.start}..{self.end}, {len(self)} indices)"


def spreadsheet_labels(num_labels: int) -> List[str]:
    """Generate Excel-style column labels"""
    labels = []
    for i in range(num_labels):
        label = ""
        n = i
        while True:
            label = chr(ord('A') + (n % 26)) + label
            n = n // 26
            if n == 0:
                break
            n -= 1
        labels.append(label)
    return labels


# UNDO/REDO SYSTEM

class UndoRedoSystem:
    """
    Runtime undo/redo system for table operations
    
    Tracks changes and allows Ctrl+Z / Ctrl+Shift+Z
    """
    
    def __init__(self, max_history: int = 100):
        self.max_history = max_history
        self.undo_stack = []
        self.redo_stack = []
        
    def record_change(self, table: 'Table', operation: str, data: Dict):
        """Record a change for undo"""
        change = {
            'operation': operation,
            'data': data,
            'timestamp': None  # Could add timestamp if needed
        }
        self.undo_stack.append(change)
        
        # Limit stack size
        if len(self.undo_stack) > self.max_history:
            self.undo_stack.pop(0)
            
        # Clear redo stack on new change
        self.redo_stack.clear()
        
    def undo(self, table: 'Table') -> bool:
        """Undo last operation"""
        if not self.undo_stack:
            return False
            
        change = self.undo_stack.pop()
        
        # Apply reverse operation
        if change['operation'] == 'set_cell':
            # Restore old value
            idx = change['data']['idx']
            old_cell = change['data']['old_cell']
            table.cells[idx] = old_cell
            
        elif change['operation'] == 'add_row':
            # Remove the added row
            # TODO: Implement row removal
            pass
            
        # Add to redo stack
        self.redo_stack.append(change)
        return True
        
    def redo(self, table: 'Table') -> bool:
        """Redo last undone operation"""
        if not self.redo_stack:
            return False
            
        change = self.redo_stack.pop()
        
        # Reapply operation
        if change['operation'] == 'set_cell':
            idx = change['data']['idx']
            new_cell = change['data']['new_cell']
            table.cells[idx] = new_cell
            
        # Add back to undo stack
        self.undo_stack.append(change)
        return True


# ENHANCED DEPENDENCY GRAPH

class DependencyGraph:
    """
    Enhanced dependency graph with performance optimizations
    and better debug output
    """
    
    def __init__(self, debug: bool = False, aggressive_debug: bool = False):
        self.dependencies = defaultdict(set)
        self.dependents = defaultdict(set)
        self.debug = debug
        self.aggressive_debug = aggressive_debug
        
    def add_dependency(self, cell_id: str, depends_on: str):
        """Add a dependency relationship"""
        self.dependencies[cell_id].add(depends_on)
        self.dependents[depends_on].add(cell_id)
        
        if self.aggressive_debug:
            print(f"[DEPENDENCY] {cell_id} ← {depends_on}")
            print(f"  └─ {cell_id} now depends on: {self.dependencies[cell_id]}")
            
    def remove_cell(self, cell_id: str):
        """Remove all dependencies for a cell"""
        # Remove from dependencies
        for dep in list(self.dependencies[cell_id]):
            self.dependents[dep].discard(cell_id)
            if self.aggressive_debug:
                print(f"[DEPENDENCY] Removed {cell_id} from {dep}'s dependents")
        del self.dependencies[cell_id]
        
        # Remove from dependents
        for dependent in list(self.dependents[cell_id]):
            self.dependencies[dependent].discard(cell_id)
        del self.dependents[cell_id]
        
    def get_affected_cells(self, cell_id: str) -> List[str]:
        """Get all cells affected by changes to cell_id (propagation order)"""
        affected = set()
        queue = deque([cell_id])
        
        if self.aggressive_debug:
            print(f"[PROPAGATION] Starting from {cell_id}")
        
        while queue:
            current = queue.popleft()
            for dependent in self.dependents.get(current, set()):
                if dependent not in affected:
                    affected.add(dependent)
                    queue.append(dependent)
                    if self.aggressive_debug:
                        print(f"  └─ Will affect: {dependent}")
                    
        # Topological sort
        sorted_cells = self._topological_sort(affected)
        
        if self.aggressive_debug and sorted_cells:
            print(f"[PROPAGATION] Evaluation order: {' → '.join(sorted_cells)}")
            
        return sorted_cells
        
    def _topological_sort(self, cells: Set[str]) -> List[str]:
        """Sort cells in evaluation order"""
        if not cells:
            return []
            
        local_deps = {cell: self.dependencies[cell] & cells for cell in cells}
        
        in_degree = {cell: 0 for cell in cells}
        for cell in cells:
            for dep in local_deps[cell]:
                in_degree[cell] += 1
                
        queue = deque([cell for cell in cells if in_degree[cell] == 0])
        result = []
        
        while queue:
            cell = queue.popleft()
            result.append(cell)
            
            for dependent in self.dependents.get(cell, set()):
                if dependent in cells:
                    in_degree[dependent] -= 1
                    if in_degree[dependent] == 0:
                        queue.append(dependent)
                        
        if len(result) != len(cells):
            raise ValueError("Circular dependency detected!")
            
        return result
        
    def detect_cycles(self) -> List[List[str]]:
        """Detect all cycles"""
        cycles = []
        visited = set()
        rec_stack = set()
        
        def dfs(node, path):
            visited.add(node)
            rec_stack.add(node)
            path.append(node)
            
            for neighbor in self.dependencies.get(node, set()):
                if neighbor not in visited:
                    dfs(neighbor, path[:])
                elif neighbor in rec_stack:
                    cycle_start = path.index(neighbor)
                    cycles.append(path[cycle_start:] + [neighbor])
                    
            rec_stack.remove(node)
            
        for node in list(self.dependencies.keys()):
            if node not in visited:
                dfs(node, [])
                
        return cycles
        
    def visualize(self) -> str:
        """Create a visual representation of the dependency graph"""
        lines = ["=== DEPENDENCY GRAPH ==="]
        
        for cell_id in sorted(self.dependencies.keys()):
            deps = self.dependencies[cell_id]
            if deps:
                lines.append(f"{cell_id}:")
                for dep in sorted(deps):
                    lines.append(f"  ← {dep}")
                    
        return "\n".join(lines)


# TABLE CLASS (ENHANCED)

class Table:
    """
    Enhanced N-dimensional table
    
    New features:
    - Variable syntax (A1 + A2)
    - Numpy backend mode
    - Undo/redo
    - Custom cell names
    - Lists allowed for indices
    - Cross-table formulas
    - Always-reevaluate mode
    """
    
    _global_tables = {}
    _default_table = None  # The default table for bare references
    
    def __init__(self,
                 shape: Union[Tuple, List] = None,
                 axes: List[Axis] = None,
                 mode: str = "normal",
                 lazy_eval: bool = True,
                 always_reevaluate: bool = False,
                 use_numpy_backend: bool = False,
                 enable_undo: bool = True,
                 debug: bool = False,
                 aggressive_debug: bool = False):
        """
        Create enhanced n-dimensional table
        
        Args:
            shape: Table dimensions (tuples or lists)
            axes: Custom Axis objects
            mode: "normal" or "pga"
            lazy_eval: Evaluate formulas on access
            always_reevaluate: Always recalculate, never cache
            use_numpy_backend: Use numpy arrays instead of Cell objects
            enable_undo: Enable undo/redo system
            debug: Print debug information
            aggressive_debug: Very detailed debug output
        """
        self.mode = mode
        self.lazy_eval = lazy_eval
        self.always_reevaluate = always_reevaluate
        self.use_numpy_backend = use_numpy_backend
        self.debug = debug
        self.aggressive_debug = aggressive_debug
        
        # Undo/redo
        self.undo_system = UndoRedoSystem() if enable_undo else None
        
        # Dependency graph
        self.dep_graph = DependencyGraph(debug=debug, aggressive_debug=aggressive_debug)
        
        # Named cells
        self.named_cells = {}  # name -> idx mapping
        
        # Initialize axes
        if axes:
            self.axes = axes
        elif shape:
            self.axes = self._create_axes_from_shape(shape)
        else:
            # Default 2D with spreadsheet labels
            self.axes = [
                Axis(start=-1, end=1, name="rows"),
                Axis(start=-1, end=1, name="cols", spreadsheet_axis=True)
            ]
            
        # Cell storage
        if self.use_numpy_backend:
            # Numpy backend for performance
            self.data_array = np.empty(self.shape, dtype=object)
            self.formula_array = np.empty(self.shape, dtype=object)
            self.cells = None
        else:
            self.cells = {}
            self.data_array = None
            self.formula_array = None
            
        # Setup spreadsheet labels
        self._setup_spreadsheet_labels()
        
        # PGA support
        self.pga_blades = {} if mode == "pga" else None
        
        if self.aggressive_debug:
            print(f"[TABLE INIT] Created {self.ndim}D table: {self.shape}")
            print(f"  Mode: {self.mode}")
            print(f"  Lazy eval: {self.lazy_eval}")
            print(f"  Always reevaluate: {self.always_reevaluate}")
            print(f"  Numpy backend: {self.use_numpy_backend}")
            
    def _create_axes_from_shape(self, shape) -> List[Axis]:
        """Create axes from shape (accepts tuples or lists)"""
        # Convert to list if tuple
        if isinstance(shape, tuple):
            shape = list(shape)
            
        axes = []
        
        if isinstance(shape[0], (list, tuple)):
            # Shape is [(start, end), ...]
            for i, spec in enumerate(shape):
                if isinstance(spec, (list, tuple)):
                    start, end = spec
                else:
                    start, end = 0, spec - 1
                axes.append(Axis(start=start, end=end, name=f"dim{i}"))
        else:
            # Shape is [size1, size2, ...]
            for i, size in enumerate(shape):
                axes.append(Axis(start=0, end=size-1, name=f"dim{i}"))
                
        return axes
        
    def _setup_spreadsheet_labels(self):
        """Setup spreadsheet-style labels"""
        # Find which axes use spreadsheet labels
        self.spreadsheet_axes = []
        for i, axis in enumerate(self.axes):
            if axis.spreadsheet_axis:
                self.spreadsheet_axes.append(i)
                
        # Set up first spreadsheet axis (typically columns)
        if self.spreadsheet_axes:
            col_axis_idx = self.spreadsheet_axes[0]
            col_axis = self.axes[col_axis_idx]
            num_cols = len(col_axis)
            self.spreadsheet_cols = spreadsheet_labels(num_cols)
            
            self.col_to_idx = {}
            for i, label in enumerate(self.spreadsheet_cols):
                idx = col_axis.indices[i]
                self.col_to_idx[label] = idx
        else:
            # Default: second axis is columns with spreadsheet labels
            if len(self.axes) >= 2:
                col_axis = self.axes[1]
                col_axis.spreadsheet_axis = True
                self.spreadsheet_axes = [1]
                num_cols = len(col_axis)
                self.spreadsheet_cols = spreadsheet_labels(num_cols)
                
                self.col_to_idx = {}
                for i, label in enumerate(self.spreadsheet_cols):
                    idx = col_axis.indices[i]
                    self.col_to_idx[label] = idx
                    
    @property
    def shape(self) -> Tuple[int, ...]:
        """Get shape as tuple"""
        return tuple(len(axis) for axis in self.axes)
        
    @property
    def ndim(self) -> int:
        """Number of dimensions"""
        return len(self.axes)
        
    def name_cell(self, idx: Union[Tuple, List, str], name: str):
        """
        Give a cell a custom name for referencing
        
        Args:
            idx: Cell index (tuple/list) or spreadsheet ref (str)
            name: Name to assign
            
        Example:
            t.name_cell('A1', 'price')
            t.name_cell([0, 0], 'total')
            # Then use: t['total'] or in formulas: =price * 2
        """
        if isinstance(idx, str):
            idx = self._normalize_index(idx)
        elif isinstance(idx, list):
            idx = tuple(idx)
            
        self.named_cells[name] = idx
        
        # Also store in cell if not using numpy backend
        if not self.use_numpy_backend:
            if idx not in self.cells:
                self.cells[idx] = Cell(name=name)
            else:
                self.cells[idx].name = name
                
        if self.aggressive_debug:
            print(f"[NAMED CELL] '{name}' → {idx}")
            
    def get_cell_by_name(self, name: str):
        """Get cell value by name"""
        if name not in self.named_cells:
            raise ValueError(f"No cell named '{name}'")
        return self[self.named_cells[name]]
        
    @classmethod
    def set_default_table(cls, table: 'Table'):
        """Set the default table for bare cell references"""
        cls._default_table = table
        
        if table.aggressive_debug:
            print(f"[DEFAULT TABLE] Set default table")
            
    def __getitem__(self, key):
        """Enhanced getitem with lists, names, cross-table support"""
        # Handle named cells
        if isinstance(key, str) and key in self.named_cells:
            key = self.named_cells[key]
            
        # Handle CellReference objects
        if isinstance(key, CellReference):
            key = key.ref
            
        # Convert lists to tuples
        if isinstance(key, list):
            key = tuple(key)
        elif isinstance(key, tuple) and any(isinstance(k, list) for k in key):
            key = tuple(k if not isinstance(k, list) else tuple(k) for k in key)
            
        # Handle boolean masks
        if isinstance(key, np.ndarray) and key.dtype == bool:
            return self._boolean_indexing(key, return_table=True)
            
        idx = self._normalize_index(key)
        
        # Check if it's a slice/range
        if any(isinstance(i, slice) for i in idx):
            return self._get_range(idx)
            
        # Single cell access
        if self.use_numpy_backend:
            formula = self.formula_array[self._array_position(idx)]
            if formula:
                if self.always_reevaluate:
                    return self._evaluate_formula_str(idx, formula)
                # Check cache... TODO
            return self.data_array[self._array_position(idx)]
        else:
            cell = self.cells.get(idx)
            if cell is None:
                return None
                
            if cell.formula:
                if self.always_reevaluate:
                    return self._evaluate_formula(idx, cell)
                elif self.lazy_eval:
                    return self._evaluate_formula(idx, cell)
                else:
                    return cell._cached_value
            else:
                return cell.raw_value
                
    def __setitem__(self, key, value):
        """Enhanced setitem with FormulaExpression support"""
        # Handle named cells
        if isinstance(key, str) and key in self.named_cells:
            key = self.named_cells[key]
            
        # Convert lists to tuples
        if isinstance(key, list):
            key = tuple(key)
        elif isinstance(key, tuple) and any(isinstance(k, list) for k in key):
            key = tuple(k if not isinstance(k, list) else tuple(k) for k in key)
            
        # Handle FormulaExpression (from A1 + A2)
        if isinstance(value, FormulaExpression):
            value = "=" + value.expression
        elif isinstance(value, CellReference):
            value = "=" + value.ref
        elif callable(value):
            # Function assigned to cell - store as formula
            # Extract function body and store
            source = inspect.getsource(value)
            value = "=python(" + source + ")"
            
        idx = self._normalize_index(key)
        
        # Check if it's a slice/range
        if any(isinstance(i, slice) for i in idx):
            self._set_range(idx, value)
            return
            
        # Single cell assignment
        self._set_cell(idx, value)
        
    def _set_cell(self, idx: Union[Tuple, List], value):
        """Set a single cell (enhanced with undo support)"""
        if isinstance(idx, list):
            idx = tuple(idx)
            
        cell_id = self._cell_id(idx)
        
        # Record for undo
        if self.undo_system:
            old_cell = self.cells.get(idx) if not self.use_numpy_backend else None
            self.undo_system.record_change(self, 'set_cell', {
                'idx': idx,
                'old_cell': copy.deepcopy(old_cell) if old_cell else None,
                'new_value': value
            })
            
        # Remove old dependencies (only if cell had formula)
        if not self.use_numpy_backend:
            if idx in self.cells and self.cells[idx].formula:
                self.dep_graph.remove_cell(cell_id)
                
        # Parse value
        if isinstance(value, str):
            if value.startswith('='):
                # Formula
                formula = value[1:]
                
                if self.use_numpy_backend:
                    self.formula_array[self._array_position(idx)] = formula
                else:
                    cell = Cell(formula=formula)
                    
                # Parse dependencies (including cross-table)
                deps = self._parse_formula_dependencies(formula)
                for dep in deps:
                    self.dep_graph.add_dependency(cell_id, dep)
                    
                # Eager evaluation if needed
                if not self.lazy_eval and not self.use_numpy_backend:
                    cell._cached_value = self._evaluate_formula(idx, cell)
                    cell._evaluated = True
                    
                if not self.use_numpy_backend:
                    self.cells[idx] = cell
                    
            elif value.startswith('"') and value.endswith('"'):
                # String literal
                if self.use_numpy_backend:
                    self.data_array[self._array_position(idx)] = value[1:-1]
                else:
                    self.cells[idx] = Cell(raw_value=value[1:-1])
            else:
                # Try to evaluate
                try:
                    evaluated = eval(value, self._get_formula_context())
                    if self.use_numpy_backend:
                        self.data_array[self._array_position(idx)] = evaluated
                    else:
                        self.cells[idx] = Cell(raw_value=evaluated)
                except:
                    if self.use_numpy_backend:
                        self.data_array[self._array_position(idx)] = value
                    else:
                        self.cells[idx] = Cell(raw_value=value)
        else:
            if self.use_numpy_backend:
                self.data_array[self._array_position(idx)] = value
            else:
                self.cells[idx] = Cell(raw_value=value)
                
        if self.aggressive_debug:
            print(f"[SET CELL] {cell_id} = {value}")
            
        # Invalidate/update dependent cells
        affected = self.dep_graph.get_affected_cells(cell_id)
        
        if not self.use_numpy_backend:
            for affected_id in affected:
                affected_idx = self._parse_cell_id(affected_id)
                affected_cell = self.cells.get(affected_idx)
                if affected_cell and affected_cell.formula:
                    if self.lazy_eval and not self.always_reevaluate:
                        affected_cell._evaluated = False
                        affected_cell._cached_value = None
                        if self.aggressive_debug:
                            print(f"  └─ Invalidated {affected_id}")
                    else:
                        affected_cell._cached_value = self._evaluate_formula(affected_idx, affected_cell)
                        affected_cell._evaluated = True
                        if self.aggressive_debug:
                            print(f"  └─ Recalculated {affected_id} = {affected_cell._cached_value}")
                            
    def _normalize_index(self, key) -> Tuple[int, ...]:
        """Normalize index (accepts lists and tuples)"""
        # Spreadsheet-style
        if isinstance(key, str):
            if ':' in key:
                return self._parse_range(key)
            else:
                return self._parse_cell_reference(key)
                
        # Tuple or list
        if isinstance(key, (tuple, list)):
            return tuple(key)
            
        # Single index for 1D
        if self.ndim == 1:
            return (key,)
            
        raise ValueError(f"Invalid index format: {key}")
        
    def _parse_cell_reference(self, ref: str) -> Tuple[int, ...]:
        """
        Parse cell reference including custom labels and cross-table
        
        Supports:
        - A1, B2 (spreadsheet)
        - ha1, he3 (custom labels)
        - table2.A1 (cross-table) - returns marker for cross-table
        - A (axis reference)
        """
        # Check for cross-table reference
        if '.' in ref:
            parts = ref.split('.')
            if len(parts) == 2:
                table_name, cell_ref = parts
                # Return special marker
                return ('__CROSS_TABLE__', table_name, cell_ref)
                
        # Check if it's just an axis reference (A, B, ha)
        if len(ref) <= 2 and ref.isalpha():
            # Could be axis reference - not supported in index yet
            raise ValueError(f"Axis reference '{ref}' not yet supported in indexing")
            
        # Parse standard reference (A1, ha3, etc.)
        match = re.match(r'^([A-Za-z]+)(\d+)$', ref)
        if not match:
            raise ValueError(f"Invalid cell reference: {ref}")
            
        col_label, row_str = match.groups()
        col_label = col_label.lower()
        
        # Try spreadsheet labels first
        if hasattr(self, 'col_to_idx') and col_label.upper() in self.col_to_idx:
            col_idx = self.col_to_idx[col_label.upper()]
        else:
            # Try custom labels
            col_idx = None
            for axis in self.axes:
                if axis.custom_labels:
                    try:
                        col_idx = axis.parse_label(col_label)
                        break
                    except ValueError:
                        continue
            if col_idx is None:
                raise ValueError(f"Column {col_label} not found")
                
        # Get row index
        row_num = int(row_str) - 1
        if row_num < 0 or row_num >= len(self.axes[0]):
            raise ValueError(f"Row {row_str} out of range")
        row_idx = self.axes[0].indices[row_num]
        
        return (row_idx, col_idx)
        
    def _parse_range(self, range_str: str):
        """Parse range including custom labels (ha1:he3)"""
        parts = range_str.split(':')
        if len(parts) < 2:
            raise ValueError(f"Invalid range: {range_str}")
            
        # Parse each part
        indices = []
        for part in parts:
            try:
                idx = self._parse_cell_reference(part)
                indices.append(idx)
            except:
                # Might be axis reference
                indices.append(part)
                
        # Build slices
        if len(indices) == 2:
            start_idx, end_idx = indices
            return tuple(slice(s, e+1 if isinstance(e, int) else e) 
                        for s, e in zip(start_idx, end_idx))
        else:
            # nD range (A1:C3:ha5)
            # TODO: Implement full nD range parsing
            raise NotImplementedError("nD ranges not fully implemented yet")
            
    def _parse_formula_dependencies(self, formula: str) -> Set[str]:
        """Parse formula dependencies including cross-table (=table2.A1)"""
        deps = set()
        
        # Cross-table references (table2.A1)
        for match in re.finditer(r'\b(\w+)\.([A-Z]+\d+)\b', formula):
            table_name, cell_ref = match.groups()
            # Create dependency on other table's cell
            deps.add(f"{table_name}.{cell_ref}")
            
        # Standard spreadsheet refs
        for match in re.finditer(r'\b([A-Z]+\d+)\b', formula):
            ref = match.group(1)
            if '.' not in ref:  # Not part of cross-table ref
                try:
                    idx = self._parse_cell_reference(ref)
                    deps.add(self._cell_id(idx))
                except ValueError:
                    pass
                    
        # Custom label refs (ha1, he3)
        for match in re.finditer(r'\b([a-z]+\d+)\b', formula):
            ref = match.group(1)
            try:
                idx = self._parse_cell_reference(ref)
                deps.add(self._cell_id(idx))
            except ValueError:
                pass
                
        return deps
        
    def _evaluate_formula(self, idx: Tuple[int, ...], cell: Cell):
        """Evaluate formula with cross-table support"""
        if cell._evaluated and self.lazy_eval and not self.always_reevaluate:
            return cell._cached_value
            
        formula = cell.formula
        
        if self.aggressive_debug:
            print(f"[FORMULA EVAL] {self._cell_id(idx)}: {formula}")
            
        context = self._get_formula_context()
        
        # Handle cross-table references
        eval_formula = formula
        for match in re.finditer(r'\b(\w+)\.([A-Z]+\d+)\b', formula):
            table_name, cell_ref = match.groups()
            if table_name in self._global_tables:
                other_table = self._global_tables[table_name]
                try:
                    value = other_table[cell_ref]
                    eval_formula = eval_formula.replace(f"{table_name}.{cell_ref}", str(value))
                except:
                    pass
                    
        # Replace standard cell references
        for match in re.finditer(r'\b([A-Z]+\d+)\b', eval_formula):
            ref = match.group(1)
            if '.' not in formula or formula.find(ref) < formula.find('.'):
                try:
                    ref_idx = self._parse_cell_reference(ref)
                    ref_value = self[ref_idx]
                    eval_formula = eval_formula.replace(ref, str(ref_value))
                except ValueError:
                    pass
                    
        # Evaluate
        try:
            result = eval(eval_formula, context)
        except Exception as e:
            if self.aggressive_debug:
                print(f"  └─ ERROR: {e}")
            raise
            
        if not self.always_reevaluate:
            cell._cached_value = result
            cell._evaluated = True
            
        if self.aggressive_debug:
            print(f"  └─ Result: {result}")
            
        return result
        
    def _get_formula_context(self) -> Dict:
        """Get context for formula evaluation"""
        import math, builtins
        context = {
            '__builtins__': builtins.__dict__ if hasattr(builtins, '__dict__') else builtins,
            'math': math,
            'np': np,
            # Common builtins explicitly for safety
            'max': max, 'min': min, 'sum': sum, 'abs': abs,
            'round': round, 'len': len, 'int': int, 'float': float,
            'str': str, 'bool': bool, 'list': list,
        }
        
        # Add global tables
        context.update(self._global_tables)
        
        # Add named cells
        for name, idx in self.named_cells.items():
            try:
                context[name] = self[idx]
            except:
                pass
                
        return context
        
    def _cell_id(self, idx: Tuple[int, ...]) -> str:
        """Convert index to cell ID"""
        return f"Cell{idx}"
        
    def _parse_cell_id(self, cell_id: str) -> Tuple[int, ...]:
        """Parse cell ID to index"""
        match = re.search(r'\(([^)]+)\)', cell_id)
        if match:
            parts = match.group(1).split(',')
            return tuple(int(p.strip()) for p in parts)
        raise ValueError(f"Invalid cell ID: {cell_id}")
        
    def _array_position(self, idx: Tuple[int, ...]) -> Tuple[int, ...]:
        """Convert table index to array position"""
        return tuple(
            self.axes[i].indices.index(idx[i])
            for i in range(len(idx))
        )
        
    def _boolean_indexing(self, mask: np.ndarray, return_table: bool = True):
        """Boolean mask indexing"""
        if return_table:
            # Return Table with selected cells
            # TODO: Implement
            raise NotImplementedError("Boolean mask returning Table not implemented yet")
        else:
            arr = self.to_numpy()
            return arr[mask]
            
    def _get_range(self, slices: Tuple) -> 'Table':
        """Get range as new Table"""
        # TODO: Implement properly
        return Table(shape=(3, 3))  # Placeholder
        
    def _set_range(self, slices: Tuple, value):
        """Set range with broadcasting"""
        # TODO: Implement properly
        pass
        
    def add_row(self, position: int = None):
        """Add a row"""
        if self.ndim < 1:
            raise ValueError("Cannot add row to 0D table")
        axis = self.axes[0]
        if position is None:
            position = len(axis.indices)
        new_idx = axis.indices[-1] + 1 if position >= len(axis.indices) else axis.indices[0] - 1
        axis.indices.insert(position, new_idx)
        
    def add_column(self, position: int = None):
        """Add a column"""
        if self.ndim < 2:
            raise ValueError("Cannot add column")
        axis = self.axes[1]
        if position is None:
            position = len(axis.indices)
        new_idx = axis.indices[-1] + 1 if position >= len(axis.indices) else axis.indices[0] - 1
        axis.indices.insert(position, new_idx)
        self._setup_spreadsheet_labels()
        
    def add_depth(self, position: int = None):
        """Add depth (3rd dimension)"""
        if self.ndim < 3:
            raise ValueError("Cannot add depth to table with < 3 dimensions")
        axis = self.axes[2]
        if position is None:
            position = len(axis.indices)
        new_idx = axis.indices[-1] + 1 if position >= len(axis.indices) else axis.indices[0] - 1
        axis.indices.insert(position, new_idx)
        
    def merge_cells(self, range_ref: Union[str, Tuple, List]):
        """
        Merge cells in a range
        
        Args:
            range_ref: Range like "A1:C3" or ((0,0), (2,2))
            
        The first cell in the range becomes the merged cell.
        Other cells are marked as merged but not rendered.
        """
        # TODO: Implement cell merging
        if self.aggressive_debug:
            print(f"[MERGE CELLS] {range_ref}")
        raise NotImplementedError("Cell merging not fully implemented")
        
    def combine_tables(self, other: 'Table', position: str = "right", offset: Tuple = None):
        """
        Combine two tables
        
        Args:
            other: Table to combine with
            position: "right", "bottom", "custom"
            offset: Custom offset for positioning
            
        Returns:
            New combined table
        """
        # TODO: Implement table combining
        if self.aggressive_debug:
            print(f"[COMBINE] Combining with another table at {position}")
        raise NotImplementedError("Table combining not fully implemented")
        
    def auto_resize(self, text: str, method: str = "fit", aspect_ratio: Tuple[int, int] = (16, 9)):
        """
        Auto-resize cell based on text length
        
        Args:
            text: Text to fit
            method: "fit" (full length), "square", or "aspect"
            aspect_ratio: Ratio for aspect method (default 16:9)
        """
        # TODO: Implement auto-resize
        text_len = len(text)
        
        if method == "fit":
            width = text_len
            height = 1
        elif method == "square":
            side = int(np.sqrt(text_len))
            width = height = side
        elif method == "aspect":
            # Fit to aspect ratio
            w, h = aspect_ratio
            ratio = w / h
            height = int(np.sqrt(text_len / ratio))
            width = int(height * ratio)
        else:
            raise ValueError(f"Unknown resize method: {method}")
            
        if self.aggressive_debug:
            print(f"[AUTO RESIZE] Text length {text_len} → {width}x{height}")
            
        return (width, height)
        
    def to_numpy(self, fill_value=0) -> np.ndarray:
        """Convert to numpy array"""
        shape = self.shape
        arr = np.full(shape, fill_value, dtype=object)
        
        if self.use_numpy_backend:
            return self.data_array.copy()
        else:
            for idx, cell in self.cells.items():
                arr_idx = tuple(
                    self.axes[i].indices.index(idx[i])
                    for i in range(len(idx))
                )
                if cell.formula:
                    value = self._evaluate_formula(idx, cell)
                else:
                    value = cell.raw_value
                arr[arr_idx] = value
                
        return arr
        
    @classmethod
    def from_numpy(cls, arr: np.ndarray, offset: Union[Tuple, List] = None, use_numpy_backend: bool = True) -> 'Table':
        """Create table from numpy array"""
        if offset is None:
            offset = tuple(0 for _ in arr.shape)
        elif isinstance(offset, list):
            offset = tuple(offset)
            
        shape = [(off, off + size - 1) for off, size in zip(offset, arr.shape)]
        table = cls(shape=shape, use_numpy_backend=use_numpy_backend)
        
        if use_numpy_backend:
            table.data_array = arr.copy()
        else:
            for idx in np.ndindex(arr.shape):
                table_idx = tuple(o + i for o, i in zip(offset, idx))
                table[table_idx] = arr[idx]
                
        return table
        
    def undo(self) -> bool:
        """Undo last operation"""
        if self.undo_system:
            result = self.undo_system.undo(self)
            if self.aggressive_debug:
                print(f"[UNDO] {'Success' if result else 'Nothing to undo'}")
            return result
        return False
        
    def redo(self) -> bool:
        """Redo last undone operation"""
        if self.undo_system:
            result = self.undo_system.redo(self)
            if self.aggressive_debug:
                print(f"[REDO] {'Success' if result else 'Nothing to redo'}")
            return result
        return False
        
    def visualize_dependencies(self) -> str:
        """Visualize the dependency graph"""
        return self.dep_graph.visualize()
        
    def __repr__(self):
        dims_str = "x".join(str(len(axis)) for axis in self.axes)
        if self.use_numpy_backend:
            return f"Table({dims_str}, numpy backend)"
        else:
            return f"Table({dims_str}, {len(self.cells)} cells)"


# Export cell references for convenient use
# Users can do: from nd_table_v2 import A1, A2, A3, etc.
# Then: t['C1'] = A1 + A2
_cell_globals = create_cell_globals()
globals().update(_cell_globals)
