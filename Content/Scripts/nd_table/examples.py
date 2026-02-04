"""
Comprehensive Examples for nD Table V2

Demonstrates all major new features:
- Variable syntax (A1 + A2)
- Numpy backend mode
- Undo/redo
- Custom cell naming
- Cross-table formulas
- Enhanced spreading
- PGA integration
- Unreal rendering
"""

import numpy as np
from nd_table.ndtable import Table, Axis, create_cell_globals
from nd_table.spread_engine import SpreadEngine, SpreadVisualizer
from nd_table.pga_integration import PGATable, PGAPrimitives, PGAConverter, KINGDON_AVAILABLE
from nd_table import A1, A2, B1, B2

# Get cell references for formulas
globals().update(create_cell_globals())


# ============================================================================
# EXAMPLE 1: Variable Syntax
# ============================================================================

def example_variable_syntax():
    """Use variables instead of string formulas"""
    print("=" * 70)
    print("EXAMPLE 1: Variable Syntax")
    print("=" * 70)
    
    t = Table(shape=(5, 5), aggressive_aggressive_debug=True, aggressive_aggressive_aggressive_debug=True)
    
    # Traditional string formula
    t['A1'] = 10
    t['A2'] = 20
    t['A3'] = "=A1 + A2"
    
    print(f"Traditional: A3 = {t['A3']}")
    
    # NEW: Variable syntax
    from nd_table_v2 import A1, A2, B1, B2
    
    t['B1'] = 5
    t['B2'] = 10
    t['B3'] = A1 * B1  # Stores formula, not evaluated value!
    
    print(f"Variable syntax: B3 = {t['B3']}")
    
    # Complex expressions
    t['C1'] = (A1 + B1) * A2 / B2
    print(f"Complex: C1 = {t['C1']}")
    
    # Updates propagate
    t['A1'] = 100
    print(f"After A1=100: A3 = {t['A3']}, B3 = {t['B3']}")
    
    print()


# ============================================================================
# EXAMPLE 2: Numpy Backend Mode
# ============================================================================

def example_numpy_backend():
    """High-performance numpy backend"""
    print("=" * 70)
    print("EXAMPLE 2: Numpy Backend Mode")
    print("=" * 70)
    
    # Regular mode
    t1 = Table(shape=(100, 100), use_numpy_backend=False)
    print(f"Regular mode: {t1}")
    
    # Numpy backend mode
    t2 = Table(shape=(100, 100), use_numpy_backend=True)
    print(f"Numpy backend: {t2}")
    
    # Fill with data
    for i in range(10):
        for j in range(10):
            t2[i, j] = i * j
            
    # Convert to numpy (fast in numpy backend mode)
    arr = t2.to_numpy()
    print(f"Array shape: {arr.shape}")
    print(f"Sample values: {arr[:3, :3]}")
    
    # Create from numpy
    data = np.random.rand(50, 50)
    t3 = Table.from_numpy(data, use_numpy_backend=True)
    print(f"From numpy: {t3}")
    
    print()


# ============================================================================
# EXAMPLE 3: Undo/Redo System
# ============================================================================

def example_undo_redo():
    """Undo and redo operations"""
    print("=" * 70)
    print("EXAMPLE 3: Undo/Redo System")
    print("=" * 70)
    
    t = Table(shape=(3, 3), enable_undo=True, aggressive_aggressive_debug=True)
    
    print("Setting values...")
    t['A1'] = 10
    t['A2'] = 20
    t['A3'] = 30
    
    print(f"\nCurrent state: A1={t['A1']}, A2={t['A2']}, A3={t['A3']}")
    
    print("\nUndo last operation (A3=30)...")
    t.undo()
    print(f"After undo: A1={t['A1']}, A2={t['A2']}, A3={t['A3']}")
    
    print("\nUndo again (A2=20)...")
    t.undo()
    print(f"After undo: A1={t['A1']}, A2={t['A2']}, A3={t['A3']}")
    
    print("\nRedo...")
    t.redo()
    print(f"After redo: A1={t['A1']}, A2={t['A2']}, A3={t['A3']}")
    
    print()


# ============================================================================
# EXAMPLE 4: Custom Cell Naming
# ============================================================================

def example_custom_names():
    """Name cells and reference by name"""
    print("=" * 70)
    print("EXAMPLE 4: Custom Cell Naming")
    print("=" * 70)
    
    t = Table(shape=(5, 5), aggressive_aggressive_debug=True)
    
    # Name some cells
    t['A1'] = 100
    t.name_cell('A1', 'price')
    
    t['A2'] = 0.2
    t.name_cell('A2', 'tax_rate')
    
    t['A3'] = 10
    t.name_cell('A3', 'quantity')
    
    # Reference by name
    print(f"\nPrice: {t.get_cell_by_name('price')}")
    print(f"Tax rate: {t.get_cell_by_name('tax_rate')}")
    print(f"Quantity: {t.get_cell_by_name('quantity')}")
    
    # Use names in formulas
    # TODO: Implement name-based formula references
    # t['B1'] = "=price * quantity"
    # t['B2'] = "=B1 * tax_rate"
    
    print()


# ============================================================================
# EXAMPLE 5: Cross-Table Formulas
# ============================================================================

def example_cross_table():
    """Reference cells across multiple tables"""
    print("=" * 70)
    print("EXAMPLE 5: Cross-Table Formulas")
    print("=" * 70)
    
    # Create two tables
    prices = Table(shape=(3, 3), aggressive_aggressive_aggressive_debug=True)
    prices['A1'] = 100
    prices['A2'] = 200
    prices['A3'] = 300
    
    quantities = Table(shape=(3, 3), aggressive_aggressive_aggressive_debug=True)
    quantities['A1'] = 10
    quantities['A2'] = 20
    quantities['A3'] = 30
    
    # Register globally
    Table.set_global_table('prices', prices)
    Table.set_global_table('quantities', quantities)
    
    # Create totals table with cross-table formulas
    totals = Table(shape=(3, 3), aggressive_aggressive_debug=True)
    totals['A1'] = "=prices.A1 * quantities.A1"
    totals['A2'] = "=prices.A2 * quantities.A2"
    totals['A3'] = "=prices.A3 * quantities.A3"
    
    print(f"Total A1: {totals['A1']}")  # Should be 1000
    print(f"Total A2: {totals['A2']}")  # Should be 4000
    print(f"Total A3: {totals['A3']}")  # Should be 9000
    
    # Update source table
    print("\nUpdating prices.A1 to 500...")
    prices['A1'] = 500
    print(f"Total A1 now: {totals['A1']}")  # Should be 5000
    
    print()


# ============================================================================
# EXAMPLE 6: Enhanced Axis System
# ============================================================================

def example_enhanced_axes():
    """16D axis labels and per-axis zero options"""
    print("=" * 70)
    print("EXAMPLE 6: Enhanced Axis System")
    print("=" * 70)
    
    # Custom axes with zero options
    axis1 = Axis(
        start=-3, end=3,
        name="rows",
        include_zero=True,
        include_negative_zero=True,
        include_positive_zero=True
    )
    
    axis2 = Axis(
        start=-2, end=2,
        name="cols",
        labels=["alpha", "beta", "gamma", "delta", "epsilon"],
        spreadsheet_axis=True
    )
    
    t = Table(axes=[axis1, axis2], aggressive_aggressive_aggressive_debug=True)
    
    print(f"Axis 0 indices: {axis1.indices}")
    print(f"Axis 1 indices: {axis2.indices}")
    print(f"Axis 1 labels: {[axis2.get_label(i) for i in axis2.indices]}")
    
    # Access with custom labels
    # t['alpha1'] = 100  # Would work with proper parsing
    
    print()


# ============================================================================
# EXAMPLE 7: Advanced Spreading
# ============================================================================

def example_advanced_spreading():
    """Multi-axis and pattern-based spreading"""
    print("=" * 70)
    print("EXAMPLE 7: Advanced Spreading")
    print("=" * 70)
    
    table = Table(shape=(3, 3))
    table['A1'] = 42
    
    engine = SpreadEngine(aggressive_debug=True)
    visualizer = SpreadVisualizer()
    
    # Grid spread
    print("\n--- GRID SPREAD ---")
    result = engine.spread(
        source=table,
        mode='replicate',
        count=9,
        spacing=100.0,
        pattern='grid'
    )
    positions = [pos for _, pos in result]
    visualizer.preview_positions(positions[:9], [f"T{i}" for i in range(9)])
    
    # Multi-axis spread
    print("\n--- MULTI-AXIS SPREAD ---")
    result = engine.spread_multi_axis(
        table=table,
        axes=[0, 1],
        spacing=[150, 150],
        counts=[3, 3]
    )
    print(f"Created {len(result)} table positions")
    
    # Curve spread
    print("\n--- CURVE SPREAD ---")
    result = engine.spread_along_curve(
        table=table,
        curve_function=lambda t: (t * 100, np.sin(t * np.pi) * 50, 0),
        count=10
    )
    positions = [pos for _, pos in result]
    print("Sine wave positions:")
    for i, pos in enumerate(positions[:5]):
        print(f"  {i}: {pos}")
    
    print()


# ============================================================================
# EXAMPLE 8: Always Reevaluate Mode
# ============================================================================

def example_always_reevaluate():
    """Never cache formula results"""
    print("=" * 70)
    print("EXAMPLE 8: Always Reevaluate Mode")
    print("=" * 70)
    
    # Regular lazy mode (caches)
    t1 = Table(shape=(3, 3), lazy_eval=True, always_reevaluate=False)
    t1['A1'] = 10
    t1['A2'] = "=A1 * 2"
    
    print(f"Lazy mode: A2 = {t1['A2']}")
    print("(cached after first access)")
    
    # Always reevaluate mode (never caches)
    t2 = Table(shape=(3, 3), lazy_eval=True, always_reevaluate=True, aggressive_aggressive_debug=True)
    t2['A1'] = 10
    t2['A2'] = "=A1 * 2"
    
    print(f"\nAlways reevaluate: A2 = {t2['A2']}")
    print("(evaluates every time)")
    print(f"Access again: A2 = {t2['A2']}")
    print("(evaluates again)")
    
    print()


# ============================================================================
# EXAMPLE 9: Aggressive Debug Mode
# ============================================================================

def example_aggressive_debug():
    """Very detailed debug output"""
    print("=" * 70)
    print("EXAMPLE 9: Aggressive Debug Mode")
    print("=" * 70)
    
    t = Table(shape=(3, 3), aggressive_aggressive_debug=True)
    
    print("\nSetting up dependency chain...")
    t['A1'] = 100
    t['A2'] = 200
    t['A3'] = "=A1 + A2"
    
    print("\nAccessing A3...")
    result = t['A3']
    print(f"Result: {result}")
    
    print("\nChanging A1...")
    t['A1'] = 500
    
    print("\nAccessing A3 again...")
    result = t['A3']
    print(f"Result: {result}")
    
    print("\nDependency graph visualization:")
    print(t.visualize_dependencies())
    
    print()


# ============================================================================
# EXAMPLE 10: PGA Integration (if available)
# ============================================================================

def example_pga_integration():
    """Geometric algebra operations"""
    print("=" * 70)
    print("EXAMPLE 10: PGA Integration")
    print("=" * 70)
    
    if not KINGDON_AVAILABLE:
        print("Install kingdon for PGA support:")
        print("  pip install kingdon")
        print()
        return
        
    # Create PGA table
    pga_table = PGATable(shape=(5, 5), pga_signature=(3, 0, 1), aggressive_debug=True)
    
    # Create geometric primitives
    primitives = PGAPrimitives(pga_table.algebra)
    
    # Store points
    p1 = primitives.point(0, 0, 0)
    p2 = primitives.point(1, 0, 0)
    p3 = primitives.point(0, 1, 0)
    
    pga_table[(0, 0)] = p1
    pga_table[(0, 1)] = p2
    pga_table[(0, 2)] = p3
    
    print("\nStored 3 points in table")
    
    # Create line
    line = pga_table.wedge_product((0, 0), (0, 1))
    print(f"Line through p1 and p2: {line}")
    
    # Create plane
    p1_val = pga_table[(0, 0)]
    p2_val = pga_table[(0, 1)]
    p3_val = pga_table[(0, 2)]
    plane = p1_val ^ p2_val ^ p3_val
    print(f"Plane through 3 points: {plane}")
    
    print()


# ============================================================================
# EXAMPLE 11: Lists as Indices
# ============================================================================

def example_lists_as_indices():
    """Use lists instead of tuples"""
    print("=" * 70)
    print("EXAMPLE 11: Lists as Indices")
    print("=" * 70)
    
    t = Table(shape=(5, 5, 5))
    
    # Tuples work
    t[(0, 0, 0)] = "tuple"
    print(f"Tuple access: {t[(0, 0, 0)]}")
    
    # Lists also work!
    t[[1, 1, 1]] = "list"
    print(f"List access: {t[[1, 1, 1]]}")
    
    # Mixed
    t[([2, 2, 2])] = "mixed"
    print(f"Mixed: {t[[2, 2, 2]]}")
    
    print()




# ============================================================================
# EXAMPLE 12: Unreal Engine Rendering
# ============================================================================

def example_unreal_rendering():
    """Render table in Unreal Engine"""
    print("=" * 70)
    print("EXAMPLE 12: Unreal Engine Rendering")
    print("=" * 70)
    
    try:
        from unreal_engine_tools import get_world
        from nd_table.unreal_integration import UnrealTableRenderer
        from nd_table.ndtable import Table
        from nd_table import A1, A2
        
        # Get Unreal world
        world = get_world()
        
        # Create table
        t = Table(shape=(5, 5, 5), aggressive_debug=True)
        t['A1'] = 100
        t['A2'] = 200
        t['A3'] = A1 + A2
        t[[1,1,1]] = "yoo"
        
        print(f"\nTable created with {len(t.cells)} cells")
        
        # Create renderer
        renderer = UnrealTableRenderer(
            world=world,
            cell_spacing=100.0,
            orientation_preset='wall_table',
            aggressive_debug=True
        )
        
        # Render
        from unreal_engine import FVector
        origin = FVector(0, 0, 500)
        renderer.render_table(t, origin=origin, render_gridlines=True)
        
        print("\nTable rendered successfully!")
        print()
    except ImportError as e:
        print(f"Unreal imports not available: {e}")
        print("This example requires running inside Unreal Engine")
        print()

# ============================================================================
# RUN ALL EXAMPLES
# ============================================================================

if __name__ == "__main__":
    examples = [
        example_variable_syntax,
        example_numpy_backend,
        example_undo_redo,
        example_custom_names,
        example_cross_table,
        example_enhanced_axes,
        example_advanced_spreading,
        example_always_reevaluate,
        example_aggressive_debug,
        example_pga_integration,
        example_lists_as_indices,
        example_unreal_rendering,
    ]
    
    for example_func in examples:
        try:
            example_func()
        except Exception as e:
            print(f"ERROR in {example_func.__name__}: {e}")
            import traceback
            traceback.print_exc()
            print()
    
    print("=" * 70)
    print("ALL EXAMPLES COMPLETED")
    print("=" * 70)
