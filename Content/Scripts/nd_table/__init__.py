"""
nD Table - Multi-dimensional Tables with Negative Indexing

A comprehensive n-dimensional table system for Unreal Engine and beyond.

Features:
- Variable syntax: t['C1'] = A1 + A2
- Numpy backend mode
- Undo/redo system
- Custom cell naming
- Cross-table formulas
- Merge cells & combine tables
- Unreal Engine rendering
- PGA (Geometric Algebra) support
- Advanced spreading patterns
"""

from .ndtable import (
    Table, Axis, Cell,
    DependencyGraph,
    spreadsheet_labels,
    UndoRedoSystem,
    CellReference,
    FormulaExpression,
)

from .unreal_integration import (
    UnrealTableRenderer,
    UnrealAxisPresets,
    TableAnimator,
    TableMouseHandler,
)

from .spread_engine import (
    SpreadEngine,
    SpreadVisualizer,
    DimensionalProjector,
)

from .pga_integration import (
    PGATable,
    PGAConverter,
    PGAOperations,
    PGAPrimitives,
    PGAFormulaEngine,
)

# Generate all cell references A1-ZZ999
_cell_refs = {}

# Single letters A-Z (A1-Z999)
for i in range(26):
    col = chr(ord('A') + i)
    for row in range(1, 1000):
        ref = f"{col}{row}"
        _cell_refs[ref] = CellReference(ref)

# Double letters AA-ZZ (AA1-ZZ99)
for i in range(26):
    for j in range(26):
        col = chr(ord('A') + i) + chr(ord('A') + j)
        for row in range(1, 100):
            ref = f"{col}{row}"
            _cell_refs[ref] = CellReference(ref)

# Custom axis labels (ha1-ha99, etc.)
custom_labels = ["ha", "haha", "hahaha", "ho", "he", "hi", "hehe", "hoho", "haha"]
for label in custom_labels:
    for row in range(1, 100):
        ref = f"{label}{row}"
        if ref not in _cell_refs:  # Avoid duplicates
            _cell_refs[ref] = CellReference(ref)

# Export all cell references to module level
globals().update(_cell_refs)

# Define __all__ for explicit exports
__all__ = [
    # Core classes
    'Table', 'Axis', 'Cell',
    'DependencyGraph', 'spreadsheet_labels',
    'UndoRedoSystem',
    'CellReference', 'FormulaExpression',
    
    # Unreal integration
    'UnrealTableRenderer', 'UnrealAxisPresets',
    'TableAnimator', 'TableMouseHandler',
    
    # Spreading
    'SpreadEngine', 'SpreadVisualizer', 'DimensionalProjector',
    
    # PGA
    'PGATable', 'PGAConverter', 'PGAOperations', 'PGAPrimitives',
    'PGAFormulaEngine',
] + list(_cell_refs.keys())

__version__ = '2.0.0'
__author__ = 'nD Table Team'
__description__ = 'N-dimensional tables with negative indexing for Unreal Engine'

# Quick usage example in docstring
__doc__ += """

Quick Start:
    >>> from nd_table import Table, A1, A2
    >>> t = Table(shape=(5, 5))
    >>> t['A1'] = 100
    >>> t['A2'] = 200
    >>> t['A3'] = A1 + A2  # Variable syntax!
    >>> print(t['A3'])  # 300
    
Unreal Rendering:
    >>> from nd_table import UnrealTableRenderer
    >>> from unreal_engine_tools import get_world
    >>> from unreal_engine import FVector
    >>> 
    >>> renderer = UnrealTableRenderer(world=get_world())
    >>> renderer.render_table(t, origin=FVector(0, 0, 100))
"""
