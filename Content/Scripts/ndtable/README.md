# nD Table V2 - Advanced Multi-dimensional Tables

Complete rewrite with major enhancements for Unreal Engine integration and advanced features.

## 🚀 What's New in V2

### Major Features

1. **Variable Syntax** - Write formulas naturally
   ```python
   from nd_table_v2 import A1, A2
   t['C1'] = A1 + A2  # Stores formula, not value!
   ```

2. **Numpy Backend Mode** - High performance for large tables
   ```python
   t = Table(shape=(1000, 1000), use_numpy_backend=True)
   ```

3. **Undo/Redo System** - Runtime undo/redo support
   ```python
   t.undo()  # Ctrl+Z
   t.redo()  # Ctrl+Shift+Z
   ```

4. **Custom Cell Naming** - Name cells and reference them
   ```python
   t.name_cell('A1', 'price')
   t.get_cell_by_name('price')
   ```

5. **Cross-Table Formulas** - Reference cells across tables
   ```python
   t['A1'] = "=table2.B1 + table3.C1"
   ```

6. **Enhanced Axis System** - 16D labels, per-axis zero options
   ```python
   axis = Axis(include_zero=True, include_negative_zero=True)
   ```

7. **Advanced Spreading** - Multi-axis, patterns, curves
   ```python
   engine.spread_multi_axis(table, axes=[0,1], counts=[3,3])
   ```

8. **PGA Integration** - Geometric algebra with kingdon
   ```python
   pga_table = PGATable(shape=(5, 5))
   ```

9. **Unreal Engine Integration** - Real rendering
   ```python
   renderer = UnrealTableRenderer(world)
   renderer.render_table(table)
   ```

10. **Always Reevaluate Mode** - Never cache formulas
    ```python
    t = Table(always_reevaluate=True)
    ```

## 📦 Installation

```bash
# Core library
pip install numpy

# Optional: PGA support
pip install kingdon

# Optional: Unreal Engine
# Use UnrealEnginePython: https://github.com/20tab/UnrealEnginePython
```

## 🎯 Quick Start

### Basic Table with New Syntax

```python
from nd_table_v2 import Table, A1, A2, B1, B2

# Create table
t = Table(shape=(5, 5))

# Set values
t['A1'] = 100
t['B1'] = 200

# NEW: Variable syntax for formulas
t['C1'] = A1 + B1  # Stores "A1 + B1" formula
t['C2'] = A1 * B2 / (A2 + 10)  # Complex expressions

# Access
print(t['C1'])  # 300

# Updates propagate automatically
t['A1'] = 500
print(t['C1'])  # 700
```

### Aggressive Debug Mode

```python
t = Table(shape=(5, 5), aggressive_debug=True)

t['A1'] = 10
t['A2'] = 20
t['A3'] = A1 + A2

# Shows detailed dependency tracking:
# [DEPENDENCY] Cell(2, 0) ← Cell(0, 0)
# [DEPENDENCY] Cell(2, 0) ← Cell(1, 0)
# [PROPAGATION] Starting from Cell(0, 0)
#   └─ Will affect: Cell(2, 0)
# [FORMULA EVAL] Cell(2, 0): A1 + A2
#   └─ Result: 30
```

### Numpy Backend for Performance

```python
# For large tables, use numpy backend
t = Table(shape=(1000, 1000), use_numpy_backend=True)

# Much faster for bulk operations
for i in range(1000):
    for j in range(1000):
        t[i, j] = i * j

# Seamless numpy conversion
arr = t.to_numpy()
```

## 🎨 Advanced Features

### Custom Cell Naming

```python
t = Table(shape=(10, 10))

# Name important cells
t['A1'] = 1000
t.name_cell('A1', 'revenue')

t['A2'] = 0.2
t.name_cell('A2', 'tax_rate')

# Reference by name
revenue = t.get_cell_by_name('revenue')
tax = t.get_cell_by_name('tax_rate')

# Use in formulas (coming soon)
# t['A3'] = "=revenue * tax_rate"
```

### Cross-Table References

```python
# Create multiple tables
prices = Table(shape=(5, 5))
prices['A1'] = 100

quantities = Table(shape=(5, 5))
quantities['A1'] = 10

# Register globally
Table.set_global_table('prices', prices)
Table.set_global_table('quantities', quantities)

# Reference across tables
totals = Table(shape=(5, 5))
totals['A1'] = "=prices.A1 * quantities.A1"

print(totals['A1'])  # 1000
```

### Enhanced Axis System

```python
from nd_table_v2 import Axis

# 16D axis labels
axis = Axis(
    start=-5, end=5,
    name="x-axis",
    labels=["xa", "xb", "xc"],  # Custom labels
    include_zero=True,
    include_negative_zero=True,  # -0 separate from 0
    include_positive_zero=True,  # +0 separate from 0
    spreadsheet_axis=True  # Use A, B, C labels
)

t = Table(axes=[axis])
```

### Advanced Spreading

```python
from spread_engine_advanced import SpreadEngine

engine = SpreadEngine(debug=True)
table = Table(shape=(3, 3))

# Grid pattern
result = engine.spread(
    source=table,
    mode='replicate',
    count=9,
    spacing=100.0,
    pattern='grid'
)

# Multi-axis spread
result = engine.spread_multi_axis(
    table=table,
    axes=[0, 1, 2],  # X, Y, Z
    spacing=[100, 100, 100],
    counts=[3, 3, 3]  # 3x3x3 = 27 tables
)

# Curve-based spread
result = engine.spread_along_curve(
    table=table,
    curve_function=lambda t: (t, t**2, np.sin(t)),
    count=20
)

# Center spread
result = engine.spread_from_center(
    table=table,
    direction='x',
    count=7,
    spacing=80
)
```

### Unreal Engine Integration

```python
from unreal_integration import UnrealTableRenderer

# In Unreal Python context
world = ue.get_world()

# Create renderer
renderer = UnrealTableRenderer(
    world=world,
    cell_spacing=100.0,
    orientation_preset='wall_table',
    debug=True
)

# Render table
renderer.render_table(
    table=my_table,
    origin=FVector(0, 0, 100),
    render_gridlines=True,
    use_instanced_gridlines=True
)

# Clear when done
renderer.clear_rendering()
```

### PGA (Geometric Algebra)

```python
from pga_integration import PGATable, PGAPrimitives

# Create PGA table
pga_table = PGATable(shape=(5, 5), pga_signature=(3, 0, 1))

# Create geometric objects
primitives = PGAPrimitives(pga_table.algebra)

# Points
p1 = primitives.point(0, 0, 0)
p2 = primitives.point(1, 0, 0)
p3 = primitives.point(0, 1, 0)

# Store in table
pga_table[(0, 0)] = p1
pga_table[(0, 1)] = p2
pga_table[(0, 2)] = p3

# Geometric operations
line = pga_table.wedge_product((0, 0), (0, 1))  # Line through 2 points
plane = p1 ^ p2 ^ p3  # Plane through 3 points
```

### Undo/Redo System

```python
t = Table(shape=(5, 5), enable_undo=True)

t['A1'] = 10
t['A2'] = 20
t['A3'] = 30

# Undo last operation
t.undo()  # A3 becomes None

# Undo again
t.undo()  # A2 becomes None

# Redo
t.redo()  # A2 becomes 20 again

# In Unreal, bind to keys:
# self.uobject.bind_key('Z', ue.IE_PRESSED, lambda: t.undo())
# self.uobject.bind_key('Y', ue.IE_PRESSED, lambda: t.redo())
```

## 🎮 Unreal Engine Features

### Axis Orientation Presets

```python
from unreal_integration import UnrealAxisPresets

presets = UnrealAxisPresets.setup_axis_presets()

# Available presets:
# - 'unreal_default': Z up, Y right, X forward
# - 'wall_table': Best for 2D/3D tables on screens
# - 'ground_table': Table on ground
# - 'ground_table_zup': Ground table with Z up
# - 'wall_graph': 2D graphs on walls
# - 'ground_graph': 3D graphs on ground

# Use in renderer
renderer = UnrealTableRenderer(
    orientation_preset='wall_table'
)
```

### Gridlines

```python
# Compute gridline positions
gridlines = renderer._compute_gridline_endpoints(table, origin, origin_cell)

# Render with regular meshes
renderer._render_gridlines_regular(table, origin, origin_cell)

# Or with instanced meshes (more efficient)
renderer._render_gridlines_instanced(table, origin, origin_cell)
```

### Cell Text with Rotation

```python
# Cells support custom rotation
class CustomRenderer(UnrealTableRenderer):
    def _get_cell_rotation(self, table, idx):
        # Custom rotation per cell
        return FRotator(0, idx[0] * 45, idx[1] * 30)
```

### Animation

```python
from unreal_integration import TableAnimator

animator = TableAnimator(renderer, speed=2.0)

# Animate cell update
animator.animate_cell_update(table, cell_idx=(0, 0), duration=0.5)

# Animate propagation
animator.animate_propagation(
    table=table,
    start_cell=(0, 0),
    affected_cells=[(0, 1), (0, 2), (1, 0)],
    duration=1.0
)

# Animate spread
animator.animate_spread(tables, positions, duration=2.0)
```

## 📊 API Reference

### Table Class

```python
Table(
    shape=None,              # Dimensions (tuples or lists)
    axes=None,               # Custom Axis objects
    mode="normal",           # "normal" or "pga"
    lazy_eval=True,          # Lazy formula evaluation
    always_reevaluate=False, # Never cache formulas
    use_numpy_backend=False, # Use numpy for storage
    enable_undo=True,        # Enable undo/redo
    debug=False,             # Basic debug output
    aggressive_debug=False   # Detailed debug output
)
```

#### Key Methods

- `name_cell(idx, name)` - Name a cell
- `get_cell_by_name(name)` - Get value by name
- `undo()` - Undo last operation
- `redo()` - Redo last undone operation
- `visualize_dependencies()` - Show dependency graph
- `to_numpy()` - Convert to numpy array
- `from_numpy(arr)` - Create from numpy

#### Class Methods

- `set_default_table(table)` - Set default for bare references
- `set_global_table(name, table)` - Register for cross-table refs

### Axis Class

```python
Axis(
    start=-1,                    # Start index
    end=1,                       # End index (inclusive)
    name=None,                   # Axis name
    labels=None,                 # Custom labels
    include_zero=True,           # Include 0 (was skip_zero)
    include_negative_zero=False, # Include -0
    include_positive_zero=False, # Include +0
    use_spreadsheet_labels=False,# A, B, C labels
    spreadsheet_axis=False       # This axis uses spreadsheet
)
```

### SpreadEngine Class

```python
engine.spread(
    source,              # Table or list of tables
    mode='replicate',    # 'replicate' or 'slice'
    direction='x',       # Direction to spread
    count=None,          # Number of copies
    spacing=100.0,       # Distance between tables
    pattern='linear',    # 'linear', 'grid', 'radial', 'spiral', 'function'
    from_cell=None,      # Starting cell
    split_axis=None,     # Axis to split (for slice mode)
    function=None        # Custom position function
)

engine.spread_multi_axis(table, axes, spacing, counts)
engine.spread_from_center(table, direction, count, spacing)
engine.spread_along_curve(table, curve_function, count, t_range)
```

### UnrealTableRenderer Class

```python
renderer = UnrealTableRenderer(
    world=None,                    # Unreal world
    cell_spacing=100.0,            # Distance between cells
    cell_size=80.0,                # Cell size
    orientation_preset='wall_table', # Axis orientation
    debug=False
)

renderer.render_table(
    table,
    origin=FVector(0,0,0),
    render_gridlines=True,
    use_instanced_gridlines=True,
    render_text=True
)

renderer.clear_rendering()
```

## 🔧 Configuration

### Lists vs Tuples

Both work everywhere:

```python
# Tuples
t[(0, 1, 2)] = 42
t[0:2, 0:2]

# Lists  
t[[0, 1, 2]] = 42
t[[0, 1], [0, 1]]

# Mixed
shape = [(0, 5), [0, 5]]  # OK
```

### Debug Modes

```python
# Basic debug
t = Table(debug=True)
# Shows: [Table] Set Cell(0,0) = Cell(42)

# Aggressive debug
t = Table(aggressive_debug=True)
# Shows:
# [TABLE INIT] Created 2D table: (3, 3)
# [DEPENDENCY] Cell(2, 0) ← Cell(0, 0)
# [PROPAGATION] Starting from Cell(0, 0)
#   └─ Will affect: Cell(2, 0)
# [FORMULA EVAL] Cell(2, 0): A1 + A2
#   └─ Result: 30
```

## 🎯 Best Practices

### 1. Use Numpy Backend for Large Tables

```python
# For tables > 100x100, use numpy backend
big_table = Table(shape=(1000, 1000), use_numpy_backend=True)
```

### 2. Enable Undo for Interactive Use

```python
# Always enable undo for user-facing tables
t = Table(enable_undo=True)
```

### 3. Use Aggressive Debug During Development

```python
# Turn on detailed logging while debugging formulas
t = Table(aggressive_debug=True)
```

### 4. Name Important Cells

```python
# Makes code more readable
t.name_cell('A1', 'total_revenue')
t.name_cell('A2', 'expenses')
t.name_cell('A3', 'profit')
```

### 5. Use Variable Syntax When Possible

```python
# Cleaner than strings
t['C1'] = A1 + A2  # Better
t['C1'] = "=A1 + A2"  # Works but less clean
```

## 🚧 Known Limitations

### Not Yet Implemented

- Cell merging (infrastructure ready, needs implementation)
- Table combining (infrastructure ready)
- Auto-resize (placeholder exists)
- Full nD range parsing (A1:C3:ha5)
- Boolean mask returning Table (currently returns numpy array)
- Callable formulas (storing function objects)

### Partial Implementation

- Cross-table formulas (basic support, needs more testing)
- PGA operations (core working, advanced operations needed)
- Unreal animation (framework ready, needs filling out)
- Mouse interaction (callbacks defined, needs implementation)

## 📚 Examples

See `examples_v2.py` for comprehensive examples of all features.

## 🤝 Contributing

This is a complete implementation based on your specifications. To extend:

1. Fill in placeholder methods (marked with `# TODO`)
2. Implement remaining spread patterns
3. Add more PGA operations
4. Extend Unreal integration
5. Add visualization helpers

## 📄 License

Use as needed for your project.

## 🔗 Related

- Original nD Table: `nd_table.py`
- Unreal Python: https://github.com/20tab/UnrealEnginePython
- Kingdon (PGA): https://github.com/tBuLi/kingdon/

## ✨ Credits

Designed for flexible n-dimensional table manipulation with:
- Simple API for basic use
- Powerful features for advanced use
- Unreal Engine integration
- Geometric algebra support
