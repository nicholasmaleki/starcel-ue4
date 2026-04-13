"""
Comprehensive nD Table Examples
"""

from .ndtable import Table, Axis
from .unreal_integration import UnrealTableRenderer
from unreal_engine import FVector
from unreal_engine_tools import get_world
import numpy as np


GLOBAL_OFFSET = FVector(0, 100, 700)


def offset(x, y, z):
    return FVector(
        GLOBAL_OFFSET.x + x,
        GLOBAL_OFFSET.y + y,
        GLOBAL_OFFSET.z + z
    )


def example_text_sizing_test():
    """Test tab and newline handling with cell sizing"""
    print("=" * 70)
    print("TEXT SIZING TEST - TABS, NEWLINES, AND LENGTH")
    print(f"Global Offset: {GLOBAL_OFFSET}")
    print("=" * 70)
    
    world = get_world()
    
    renderer = UnrealTableRenderer(
        world=world,
        cell_spacing=100.0,
        orientation_preset='wall_table',
        text_mode='3d',
        debug=True,
        aggressive_debug=True
    )
    
    # ===== TEST 1: VARYING TEXT LENGTHS WITH TABS AND NEWLINES =====
    print("\n[TEST 1] 2D - Tabs and newlines...")
    t_length = Table(shape=(3, 3), aggressive_debug=True)
    
    # Row 0: Short, medium, long with tabs
    t_length[0, 0] = "A"
    t_length[0, 1] = "Hello"
    t_length[0, 2] = "This is \ta very long\t\t text string"
    
    # Row 1: Newlines  
    t_length[1, 0] = "XY"
    t_length[1, 1] = "Testing"
    t_length[1, 2] = "Even longer text \nthat goes on and on"
    
    # Row 2: Multiple tabs and newlines
    t_length[2, 0] = "123"
    t_length[2, 1] = "hello\t\t\tworld!"
    t_length[2, 2] = "The quick brown fox\n\n\njumps over the lazy dog"
    
    renderer.render_table(t_length, world_location=offset(0, 0, 100))
    print("✓ 2D tab/newline test rendered\n")
    
    # ===== TEST 2: TABS =====
    print("\n[TEST 2] Tabs - should expand to 4 char widths...")
    t_tabs = Table(shape=(5, 2), aggressive_debug=True)
    t_tabs[0, 0] = "No tab"
    t_tabs[0, 1] = "Has\ttab"          # 1 tab = 4 extra chars
    
    t_tabs[1, 0] = "Two\t\ttabs"       # 2 tabs = 8 extra chars
    t_tabs[1, 1] = "Name\tValue\tQty"  # Multiple tabs
    
    t_tabs[2, 0] = "A\tB\tC\tD"        # Tab-separated
    t_tabs[2, 1] = "\tLeading"         # Leading tab
    
    t_tabs[3, 0] = "Trail\t"           # Trailing tab
    t_tabs[3, 1] = "\t\t\tMany"       # Multiple leading tabs
    
    t_tabs[4, 0] = "Col1\tCol2"
    t_tabs[4, 1] = "Data\tMore"
    
    renderer.render_table(t_tabs, world_location=offset(1000, 0, 100))
    print("✓ Tabs rendered\n")
    
    # ===== TEST 3: NEWLINES =====
    print("\n[TEST 3] Newlines - should increase cell height...")
    t_newlines = Table(shape=(5, 2), aggressive_debug=True)
    t_newlines[0, 0] = "Single"
    t_newlines[0, 1] = "Line1\nLine2"              # 2 lines
    
    t_newlines[1, 0] = "One\nTwo\nThree"           # 3 lines
    t_newlines[1, 1] = "A\nB\nC\nD"                # 4 lines
    
    t_newlines[2, 0] = "Multi\nline\ntext\nhere\nnow"  # 5 lines
    t_newlines[2, 1] = "Short"
    
    t_newlines[3, 0] = "X"
    t_newlines[3, 1] = "Two\nLines"
    
    t_newlines[4, 0] = "List:\nItem1\nItem2\nItem3"
    t_newlines[4, 1] = "Done"
    
    renderer.render_table(t_newlines, world_location=offset(2000, 0, 100))
    print("✓ Newlines rendered\n")
    
    # ===== TEST 4: COMBINED TABS AND NEWLINES =====
    print("\n[TEST 4] Combined tabs and newlines...")
    t_combined = Table(shape=(4, 3), aggressive_debug=True)
    
    # Headers with tabs
    t_combined[0, 0] = "Name\tAge\tCity"
    t_combined[0, 1] = "Product\tPrice\tQty"
    t_combined[0, 2] = "ID\tStatus"
    
    # Multi-line with tabs
    t_combined[1, 0] = "Alice\t25\tNY\nBob\t30\tLA"
    t_combined[1, 1] = "Widget\t$10\t5\nGadget\t$20\t3"
    t_combined[1, 2] = "001\tActive\n002\tPending"
    
    # Indented multi-line
    t_combined[2, 0] = "Header\n\tIndented\n\t\tDouble"
    t_combined[2, 1] = "Data:\n\tValue1\n\tValue2\n\tValue3"
    t_combined[2, 2] = "Note:\n\tImportant"
    
    # Table-like structure
    t_combined[3, 0] = "R1:\tVal1\nR2:\tVal2\nR3:\tVal3"
    t_combined[3, 1] = "C1\tC2\tC3\nD1\tD2\tD3"
    t_combined[3, 2] = "Final\tCell"
    
    renderer.render_table(t_combined, world_location=offset(0, 1000, 100))
    print("✓ Combined tabs/newlines rendered\n")
    
    # ===== TEST 5: EDGE CASES =====
    print("\n[TEST 5] Edge cases...")
    t_edge = Table(shape=(3, 3), aggressive_debug=True)
    t_edge[0, 0] = ""              # Empty string
    t_edge[0, 1] = " "             # Single space
    t_edge[0, 2] = "Normal"
    
    t_edge[1, 0] = "\n"            # Just newline
    t_edge[1, 1] = "\t"            # Just tab
    t_edge[1, 2] = "\n\t"          # Both
    
    t_edge[2, 0] = "\n\n\n"        # Multiple newlines
    t_edge[2, 1] = "\t\t\t"        # Multiple tabs
    t_edge[2, 2] = "Regular"
    
    renderer.render_table(t_edge, world_location=offset(1000, 1000, 100))
    print("✓ Edge cases rendered\n")
    
    print("=" * 70)
    print("TEXT SIZING TESTS COMPLETE")
    print(f"Total cells: {len(renderer.cell_actors)}")
    print(f"Total gridlines: {len(renderer.gridline_actors)}")
    print("=" * 70)
    print()


def test_nd_table_grid(base_location=None):
    """
    Comprehensive nD table rendering test (2D through 7D).
    Uses 10x10 for the base 2D table.

    Returns dict compatible with test_spawn_all results format.
    """
    from unreal_engine import FVector as _FV

    if base_location is None:
        base_location = GLOBAL_OFFSET

    def _off(x, y, z):
        return _FV(base_location.x + x, base_location.y + y,
                   base_location.z + z)

    _log = print
    _log("=" * 70)
    _log("test_nd_table_grid")
    _log(f"Base Location: {base_location}")
    _log("=" * 70)

    world = get_world()

    renderer = UnrealTableRenderer(
        world=world,
        cell_spacing=100.0,
        orientation_preset='wall_table',
        text_mode='3d',
        debug=False,
        aggressive_debug=True
    )

    # ===== 2D TABLE (3x3) =====
    _log("\n[2D TEST] Creating 3x3 table...")
    t2d = Table(shape=(3, 3), aggressive_debug=True)
    for i in range(3):
        for j in range(3):
            t2d[i, j] = f"({i},{j})"
    t2d[0, 0] = 100
    t2d[1, 0] = 200
    t2d[2, 0] = 300
    renderer.render_table(t2d, world_location=_off(0, 0, 100))
    _log("2D rendered\n")

    # ===== 2D WITH NEGATIVES =====
    _log("[2D NEGATIVE] Table with negative indices...")
    t2d_neg = Table(shape=[(-1, 1), (-1, 1)], aggressive_debug=True)
    for i in range(-1, 2):
        for j in range(-1, 2):
            t2d_neg[i, j] = f"[{i},{j}]"
    renderer.render_table(t2d_neg, world_location=_off(600, 0, 100))
    _log("2D negative rendered\n")

    # ===== 3D TABLE =====
    _log("[3D TEST] Creating 2x2x2 table...")
    t3d = Table(shape=(2, 2, 2), aggressive_debug=True)
    for i in range(2):
        for j in range(2):
            for k in range(2):
                t3d[i, j, k] = f"{i}{j}{k}"
    renderer.render_table(t3d, world_location=_off(0, 600, 100))
    _log("3D rendered\n")

    # ===== 3D WITH TABS AND NEWLINES =====
    _log("[3D TAB/NEWLINE] Table with special characters...")
    t3d_special = Table(shape=(2, 2, 2), aggressive_debug=True)
    t3d_special[0, 0, 0] = "hello\nworld!"
    t3d_special[0, 0, 1] = "tab\tsep"
    t3d_special[0, 1, 0] = "multi\nline"
    t3d_special[0, 1, 1] = "A"
    t3d_special[1, 0, 0] = "B\nC"
    t3d_special[1, 0, 1] = "D"
    t3d_special[1, 1, 0] = "tabs:\there"
    t3d_special[1, 1, 1] = "end"
    renderer.render_table(t3d_special, world_location=_off(600, 600, 100))
    _log("3D tab/newline rendered\n")

    # ===== 3D WITH NEGATIVES =====
    _log("[3D NEGATIVE] Table with negative indices...")
    t3d_neg = Table(shape=[(-1, 1), (-1, 1), (-1, 1)], aggressive_debug=True)
    for i in range(-1, 2):
        for j in range(-1, 2):
            for k in range(-1, 2):
                t3d_neg[i, j, k] = f"[{i},{j},{k}]"
    renderer.render_table(t3d_neg, world_location=_off(1200, 0, 100))
    _log("3D negative rendered\n")

    # ===== 3D WITH FUNCTION =====
    _log("[3D FUNCTION] Table with callable function...")
    t3d_func = Table(shape=(2, 2, 2), aggressive_debug=True)
    for i in range(2):
        for j in range(2):
            for k in range(2):
                t3d_func[i, j, k] = i * 100 + j * 10 + k
    def calc_sum():
        return t3d_func[0,0,0] + t3d_func[1,1,1]
    t3d_func[0, 0, 1] = calc_sum
    renderer.render_table(t3d_func, world_location=_off(1200, 600, 100))
    _log("3D function rendered\n")

    # ===== 4D TABLE =====
    _log("[4D TEST] Creating 2^4 table...")
    t4d = Table(shape=(2, 2, 2, 2), aggressive_debug=True)
    for i in range(2):
        for j in range(2):
            for k in range(2):
                for w in range(2):
                    t4d[i,j,k,w] = f"{i}{j}{k}{w}"
    renderer.render_table(t4d, world_location=_off(0, 1200, 100))
    _log("4D rendered\n")

    # ===== 4D WITH NEGATIVE =====
    _log("[4D NEGATIVE] Table with negative 4th dimension...")
    axes_4d = [
        Axis(start=0, end=1, name="dim0"),
        Axis(start=0, end=1, name="dim1"),
        Axis(start=0, end=1, name="dim2"),
        Axis(start=-1, end=1, name="dim3")
    ]
    t4d_neg = Table(axes=axes_4d, aggressive_debug=True)
    for i in range(2):
        for j in range(2):
            for k in range(2):
                for w in range(-1, 2):
                    t4d_neg[i,j,k,w] = f"D4={w}"
    renderer.render_table(t4d_neg, world_location=_off(600, 1200, 100))
    _log("4D negative rendered\n")

    # ===== 5D TABLE =====
    _log("[5D TEST] Creating 2^5 table...")
    t5d = Table(shape=(2, 2, 2, 2, 2), aggressive_debug=True)
    for i in range(2):
        for j in range(2):
            for k in range(2):
                for w in range(2):
                    for v in range(2):
                        t5d[i,j,k,w,v] = f"{i}{j}{k}{w}{v}"
    renderer.render_table(t5d, world_location=_off(0, 1800, 100))
    _log("5D rendered\n")

    # ===== 6D TABLE (2^6 = 64 cells) =====
    _log("[6D TEST] Creating 2^6 table (64 cells)...")
    t6d = Table(shape=(2, 2, 2, 2, 2, 2), aggressive_debug=True)
    count = 0
    for i in range(2):
        for j in range(2):
            for k in range(2):
                for w in range(2):
                    for v in range(2):
                        for u in range(2):
                            t6d[i,j,k,w,v,u] = count
                            count += 1
    renderer.render_table(t6d, world_location=_off(0, 2400, 100))
    _log(f"6D rendered ({count} cells)\n")

    n_cells = len(renderer.cell_actors)
    n_lines = len(renderer.gridline_actors)
    _log("=" * 70)
    _log(f"ALL TESTS COMPLETE")
    _log(f"Cells: {n_cells}, Gridlines: {n_lines}")
    _log("=" * 70)

    return renderer


# Keep old name as alias for backwards compatibility
example_unreal_rendering = test_nd_table_grid


if __name__ == '__main__':
    # Run text sizing test first
    example_text_sizing_test()
    
    # Then run full rendering tests
    example_unreal_rendering()

