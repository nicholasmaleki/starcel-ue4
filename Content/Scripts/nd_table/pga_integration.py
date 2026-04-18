"""
Projective Geometric Algebra (PGA) Integration

Uses kingdon library: https://github.com/tBuLi/kingdon/

Provides:
- PGA mode for tables
- Multivector storage (bivectors, trivectors, nVectors)
- PGA operations on table data
- Conversion to/from multivectors
"""

import numpy as np
from typing import Union, Tuple, List, Optional, Dict, Any

try:
    from kingdon import Algebra
    KINGDON_AVAILABLE = True
except ImportError:
    KINGDON_AVAILABLE = False
    print("Warning: kingdon not installed. Install with: pip install kingdon")


# PGA TABLE MODE

class PGATable:
    """
    Table operating in PGA mode
    
    Cells can store multivectors (scalars, vectors, bivectors, trivectors, etc.)
    Operations follow geometric algebra rules
    """
    
    def __init__(self,
                 shape: Tuple[int, ...],
                 pga_signature: Tuple[int, int, int] = (3, 0, 1),
                 debug: bool = False):
        """
        Args:
            shape: Table dimensions
            pga_signature: (p, q, r) signature for algebra
                         Default (3, 0, 1) is PGA for 3D
            debug: Print debug info
        """
        if not KINGDON_AVAILABLE:
            raise ImportError("kingdon library required for PGA mode")
            
        self.shape = shape
        self.pga_signature = pga_signature
        self.debug = debug
        
        # Initialize algebra
        p, q, r = pga_signature
        self.algebra = Algebra(p, q, r)
        
        # Get blades
        self.blades = self.algebra.blades
        
        # Storage for multivectors
        self.cells = {}
        
        # Blade names for reference
        self.blade_names = list(self.blades.keys())
        
        if self.debug:
            print(f"[PGA] Initialized with signature {pga_signature}")
            print(f"  Available blades: {self.blade_names}")
            
    def __setitem__(self, idx: Tuple[int, ...], value: Any):
        """
        Set cell value
        
        Value can be:
        - Scalar (float/int)
        - Multivector from algebra
        - Dict of blade components
        """
        if isinstance(value, dict):
            # Build multivector from components
            mv = self._build_multivector(value)
            self.cells[idx] = mv
        else:
            self.cells[idx] = value
            
        if self.debug:
            print(f"[PGA] Set {idx} = {value}")
            
    def __getitem__(self, idx: Tuple[int, ...]) -> Any:
        """Get cell value"""
        return self.cells.get(idx)
        
    def _build_multivector(self, components: Dict[str, float]):
        """
        Build multivector from component dictionary
        
        Example:
            {'e1': 1.0, 'e2': 2.0, 'e12': 3.0}
        """
        # Start with zero
        mv = 0
        
        for blade_name, coeff in components.items():
            if blade_name in self.blades:
                blade = self.blades[blade_name]
                mv += coeff * blade
            else:
                raise ValueError(f"Unknown blade: {blade_name}")
                
        return mv
        
    def to_dict(self, multivector) -> Dict[str, float]:
        """Convert multivector to component dictionary"""
        # Extract coefficients for each blade
        components = {}
        
        # TODO: Implement proper coefficient extraction
        # This depends on kingdon's internal structure
        
        return components
        
    def geometric_product(self, idx1: Tuple, idx2: Tuple) -> Any:
        """Compute geometric product of two cells"""
        v1 = self[idx1]
        v2 = self[idx2]
        
        if v1 is None or v2 is None:
            return None
            
        result = v1 * v2
        
        if self.debug:
            print(f"[PGA] {idx1} * {idx2} = {result}")
            
        return result
        
    def wedge_product(self, idx1: Tuple, idx2: Tuple) -> Any:
        """Compute wedge (outer) product"""
        v1 = self[idx1]
        v2 = self[idx2]
        
        if v1 is None or v2 is None:
            return None
            
        result = v1 ^ v2
        
        if self.debug:
            print(f"[PGA] {idx1} ^ {idx2} = {result}")
            
        return result
        
    def dot_product(self, idx1: Tuple, idx2: Tuple) -> Any:
        """Compute inner product"""
        v1 = self[idx1]
        v2 = self[idx2]
        
        if v1 is None or v2 is None:
            return None
            
        result = v1 | v2
        
        if self.debug:
            print(f"[PGA] {idx1} | {idx2} = {result}")
            
        return result


# PGA CONVERTERS

class PGAConverter:
    """
    Convert between regular tables and PGA tables
    
    Handles:
    - Scalar tables → PGA (embed as grade-0)
    - Vector tables → PGA (as grade-1)
    - PGA tables → numpy arrays (extract coefficients)
    """
    
    @staticmethod
    def to_pga(table, 
               pga_signature: Tuple[int, int, int] = (3, 0, 1),
               grade: int = 0) -> PGATable:
        """
        Convert regular table to PGA table
        
        Args:
            table: Source table
            pga_signature: Algebra signature
            grade: Grade to embed values as (0=scalar, 1=vector, etc.)
        """
        pga_table = PGATable(table.shape, pga_signature)
        
        # Copy values
        for idx, cell in table.cells.items():
            value = table[idx]
            
            if value is None:
                continue
                
            if grade == 0:
                # Embed as scalar
                pga_table[idx] = value
            elif grade == 1:
                # Embed as vector (use first basis vector)
                blade = pga_table.blades['e1']
                pga_table[idx] = value * blade
            else:
                raise NotImplementedError(f"Grade {grade} embedding not implemented")
                
        return pga_table
        
    @staticmethod
    def from_pga(pga_table: PGATable,
                 extract_grade: int = 0) -> np.ndarray:
        """
        Convert PGA table to numpy array
        
        Args:
            pga_table: Source PGA table
            extract_grade: Which grade to extract (0=scalar part, etc.)
        """
        arr = np.zeros(pga_table.shape)
        
        for idx, mv in pga_table.cells.items():
            if mv is None:
                continue
                
            # Extract specific grade
            # TODO: Implement grade extraction
            # For now, try to get scalar part
            try:
                if hasattr(mv, 'value'):
                    value = mv.value
                else:
                    value = float(mv)
            except:
                value = 0
                
            # Convert to array position
            arr_idx = idx  # Assuming simple mapping
            arr[arr_idx] = value
            
        return arr


# PGA OPERATIONS

class PGAOperations:
    """
    Common PGA operations for tables
    """
    
    @staticmethod
    def create_point(x: float, y: float, z: float, algebra) -> Any:
        """Create a point in PGA"""
        # Point = x*e1 + y*e2 + z*e3 + e0
        blades = algebra.blades
        point = x * blades['e1'] + y * blades['e2'] + z * blades['e3'] + blades['e0']
        return point
        
    @staticmethod
    def create_line(p1, p2, algebra) -> Any:
        """Create a line through two points"""
        # Line = p1 ^ p2
        return p1 ^ p2
        
    @staticmethod
    def create_plane(p1, p2, p3, algebra) -> Any:
        """Create a plane through three points"""
        # Plane = p1 ^ p2 ^ p3
        return p1 ^ p2 ^ p3
        
    @staticmethod
    def distance(p1, p2) -> float:
        """Calculate distance between two points"""
        # In PGA, distance involves the geometric product
        # d² = (p1 - p2) * (p1 - p2)
        diff = p1 - p2
        dist_sq = diff * diff
        
        # Extract scalar part
        try:
            if hasattr(dist_sq, 'value'):
                return np.sqrt(abs(dist_sq.value))
            else:
                return np.sqrt(abs(float(dist_sq)))
        except:
            return 0.0
            
    @staticmethod
    def reflect(point, plane) -> Any:
        """Reflect point across plane"""
        # In PGA: reflected = -plane * point * plane
        return -plane * point * plane
        
    @staticmethod
    def rotate(object, rotor) -> Any:
        """Rotate object using rotor"""
        # In PGA: rotated = rotor * object * ~rotor
        return rotor * object * ~rotor


# PGA FORMULAS IN TABLES

class PGAFormulaEngine:
    """
    Formula engine that understands PGA operations
    
    Allows formulas like:
    - "=A1 ^ A2" (wedge product)
    - "=A1 | A2" (dot product)
    - "=reflect(A1, A2)" (reflection)
    """
    
    def __init__(self, pga_table: PGATable):
        self.pga_table = pga_table
        
    def evaluate(self, formula: str, context: Dict[str, Any] = None) -> Any:
        """
        Evaluate PGA formula
        
        Formula can contain:
        - Cell references (A1, B2)
        - PGA operators (^, |, *)
        - PGA functions (reflect, rotate, etc.)
        """
        if context is None:
            context = {}
            
        # Add PGA operations to context
        context.update({
            'reflect': PGAOperations.reflect,
            'rotate': PGAOperations.rotate,
            'distance': PGAOperations.distance,
        })
        
        # Add algebra and blades
        context['algebra'] = self.pga_table.algebra
        context.update(self.pga_table.blades)
        
        # Replace cell references with values
        eval_formula = formula
        
        # Find cell references (A1, B2, etc.)
        import re
        for match in re.finditer(r'\b([A-Z]+\d+)\b', formula):
            ref = match.group(1)
            # TODO: Parse reference and get value
            # For now, this is a placeholder
            
        # Evaluate
        try:
            result = eval(eval_formula, context)
            return result
        except Exception as e:
            print(f"Error evaluating PGA formula: {e}")
            return None


# GEOMETRIC PRIMITIVES

class PGAPrimitives:
    """
    Create geometric primitives using PGA
    """
    
    def __init__(self, algebra):
        self.algebra = algebra
        self.blades = algebra.blades
        
    def point(self, x: float, y: float, z: float = 0.0):
        """Create a point"""
        return PGAOperations.create_point(x, y, z, self.algebra)
        
    def line(self, p1, p2):
        """Create a line through two points"""
        return PGAOperations.create_line(p1, p2, self.algebra)
        
    def plane(self, p1, p2, p3):
        """Create a plane through three points"""
        return PGAOperations.create_plane(p1, p2, p3, self.algebra)
        
    def circle(self, center, radius: float):
        """Create a circle"""
        # Circle in PGA is defined by center and radius
        # This is a simplified version
        return center  # Placeholder
        
    def sphere(self, center, radius: float):
        """Create a sphere"""
        return center  # Placeholder


# EXAMPLE USAGE

def example_pga_table():
    """Example using PGA tables"""
    
    if not KINGDON_AVAILABLE:
        print("Install kingdon to run PGA examples:")
        print("  pip install kingdon")
        return
        
    print("=== PGA TABLE EXAMPLE ===\n")
    
    # Create PGA table
    pga_table = PGATable(shape=(3, 3), pga_signature=(3, 0, 1), debug=True)
    
    # Get blades
    blades = pga_table.blades
    print(f"Available blades: {list(blades.keys())}\n")
    
    # Create geometric objects
    primitives = PGAPrimitives(pga_table.algebra)
    
    # Store points in table
    p1 = primitives.point(0, 0, 0)
    p2 = primitives.point(1, 0, 0)
    p3 = primitives.point(0, 1, 0)
    
    pga_table[(0, 0)] = p1
    pga_table[(0, 1)] = p2
    pga_table[(0, 2)] = p3
    
    print("\nPoints stored in table:")
    print(f"  [0,0]: {pga_table[(0, 0)]}")
    print(f"  [0,1]: {pga_table[(0, 1)]}")
    print(f"  [0,2]: {pga_table[(0, 2)]}")
    
    # Create line from two points
    line = pga_table.wedge_product((0, 0), (0, 1))
    pga_table[(1, 0)] = line
    
    print(f"\nLine through p1 and p2:")
    print(f"  [1,0]: {line}")
    
    # Create plane from three points
    p1_val = pga_table[(0, 0)]
    p2_val = pga_table[(0, 1)]
    p3_val = pga_table[(0, 2)]
    
    plane = p1_val ^ p2_val ^ p3_val
    pga_table[(2, 0)] = plane
    
    print(f"\nPlane through p1, p2, p3:")
    print(f"  [2,0]: {plane}")
    
    # Calculate distance
    dist = PGAOperations.distance(p1, p2)
    print(f"\nDistance between p1 and p2: {dist}")
    
    print("\n=== PGA operations in table complete ===")


def example_pga_conversion():
    """Example converting regular table to PGA"""
    
    if not KINGDON_AVAILABLE:
        return
        
    print("\n=== PGA CONVERSION EXAMPLE ===\n")
    
    from nd_table_v2 import Table
    
    # Create regular table
    table = Table(shape=(3, 3))
    table[0, 0] = 1.0
    table[0, 1] = 2.0
    table[0, 2] = 3.0
    
    print("Regular table values:")
    print(f"  [0,0]: {table[0, 0]}")
    print(f"  [0,1]: {table[0, 1]}")
    print(f"  [0,2]: {table[0, 2]}")
    
    # Convert to PGA (embed as scalars)
    pga_table = PGAConverter.to_pga(table, grade=0)
    
    print("\nConverted to PGA table:")
    print(f"  [0,0]: {pga_table[(0, 0)]}")
    print(f"  [0,1]: {pga_table[(0, 1)]}")
    print(f"  [0,2]: {pga_table[(0, 2)]}")
    
    # Convert back to numpy
    arr = PGAConverter.from_pga(pga_table, extract_grade=0)
    
    print("\nConverted back to numpy:")
    print(arr)


if __name__ == '__main__':
    example_pga_table()
    example_pga_conversion()
