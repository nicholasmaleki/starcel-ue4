"""
nD Table Package
"""

from .ndtable import (
    Table, Axis, Cell,
    DependencyGraph,
    spreadsheet_labels,
    UndoRedoSystem,
    CellReference,
    FormulaExpression,
    create_cell_globals,
)

from .unreal_integration import (
    UnrealTableRenderer,
    UnrealAxisPresets,
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

# Create all cell references
_refs = create_cell_globals()
globals().update(_refs)

__all__ = ['Table', 'Axis', 'Cell', 'UnrealTableRenderer', 'SpreadEngine', 'PGATable'] + list(_refs.keys())
__version__ = '2.0.0'
