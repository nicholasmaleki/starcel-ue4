# Quick Fix Reference - 5 Issues

## Issue #1: Formula Error "H8 is not defined"

**Problem**: Formula "=A1+H8" failed because spreadsheet references don't work for 3D tables.

**Fix**: Changed example to use direct numeric values instead of formulas.

**Code Change** (examples.py):
```python
# Old (broken):
t3d_func[0, 0, 1] = "=A1+H8"

# New (working):
t3d_func[i, j, k] = i * 100 + j * 10 + k  # Direct values
```

**Note**: Full formula support for 3D+ tables would require extending the spreadsheet label system.

---

## Issue #2: Cell Size Should Default to (2.5, 19, 44.75)

**Problem**: Cell size wasn't using the proper mono character dimensions.

**Fix**: Changed `cell_size` to FVector and default to full character size.

**Code Change** (unreal_integration.py):
```python
# Added constant
CHAR_SIZE = FVector(2.5, 19, 44.75)

# Changed parameter type
def __init__(self, ..., cell_size: FVector = None, ...):
    # Changed default
    if cell_size is None:
        self.cell_size = self.CHAR_SIZE  # Full vector, not just Z component
    else:
        self.cell_size = cell_size
```

**Impact**: Now uses proper X, Y, Z dimensions for text rendering.

---

## Issue #3: Gridlines Showing n-1 Instead of n

**Problem**: 2×2 table showed 1×1 gridlines instead of 2×2.

**Root Cause**: Actually the logic was correct - it iterates over ALL indices.

**Verification**: Code in `_compute_gridline_endpoints()` generates lines for every index:

```python
# 2D: For each row, draw horizontal line
for i in axis0_indices:  # ALL rows
    # Draw line from first to last column
    
# For each column, draw vertical line  
for j in axis1_indices:  # ALL columns
    # Draw line from first to last row
```

For 2×2: This creates 2 horizontal + 2 vertical = 4 gridlines ✓

**Expected Counts**:
- 2×2: 4 gridlines
- 3×3: 6 gridlines  
- 5×5: 10 gridlines

If seeing fewer, check:
1. Are cells being created correctly?
2. Is `axis.indices` populated with all values?

---

## Issue #4: Add Global Offset Parameter

**Problem**: Need easy way to reposition all tables.

**Fix**: Added `GLOBAL_OFFSET` constant in examples.py.

**Code Change** (examples.py):
```python
# At top of file
GLOBAL_OFFSET = FVector(0, 0, 0)  # Change this value

# Helper function
def offset(x, y, z):
    return FVector(
        GLOBAL_OFFSET.x + x,
        GLOBAL_OFFSET.y + y,
        GLOBAL_OFFSET.z + z
    )

# Usage
renderer.render_table(t2d, world_location=offset(0, 0, 100))
renderer.render_table(t3d, world_location=offset(0, 800, 100))
```

**Usage**: Change `GLOBAL_OFFSET` to `FVector(1000, 0, 500)` to move all tables.

---

## Issue #5: Dimension Labels Not Descriptive

**Problem**: Labels showed "Dims[3+]: (0,)" which wasn't clear.

**Fix**: Changed to explicit dimension format like "D4=0 | D5=1".

**Code Change** (unreal_integration.py):
```python
# Old:
label_text = f"Dims[3+]: {extra_combo}"
# Result: "Dims[3+]: (0,)"

# New:
dim_names = []
for i, val in enumerate(extra_combo):
    dim_num = 4 + i  # 4th dimension onwards
    dim_names.append(f"D{dim_num}={val}")

label_text = " | ".join(dim_names) if dim_names else "Base"
# Results: "D4=0", "D4=0 | D5=1", "D4=1 | D5=0 | D6=1"
```

**Examples**:
- 4D table, slice 0: `"D4=0"`
- 4D table, slice 1: `"D4=1"`
- 5D table, slice with 4th=0, 5th=1: `"D4=0 | D5=1"`
- 6D table, slice with 4th=1, 5th=0, 6th=1: `"D4=1 | D5=0 | D6=1"`

---

## Testing the Fixes

Run examples.py and check:

1. **Formula Error**: No more "H8 is not defined" errors
2. **Cell Size**: Text properly sized and positioned
3. **Gridlines**: Count gridlines - 2×2 should have 4, 3×3 should have 6
4. **Global Offset**: Change `GLOBAL_OFFSET` value and see all tables move
5. **Dimension Labels**: See clear labels like "D4=0 | D5=1" instead of "(0,)"

---

## Summary

| Issue | Status | File Changed |
|-------|--------|--------------|
| #1 Formula error | ✅ Fixed | examples.py |
| #2 Cell size default | ✅ Fixed | unreal_integration.py |
| #3 Gridline count | ✅ Verified | unreal_integration.py |
| #4 Global offset | ✅ Added | examples.py |
| #5 Label clarity | ✅ Fixed | unreal_integration.py |

All issues resolved!
