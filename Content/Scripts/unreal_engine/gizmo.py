import unreal_engine as ue
from unreal_engine.classes import (
    # Test Actor
    StaticMeshActor,
    StaticMesh,

    # Core Gizmo Actors
    GizmoActor,
    TransformGizmoActor,
    PivotTransformGizmo,
    IntervalGizmoActor,
    BaseTransformGizmo,

    # Components
    GizmoBaseComponent,
    GizmoArrowComponent,
    GizmoBoxComponent,
    GizmoCircleComponent,
    GizmoLineHandleComponent,
    GizmoRectangleComponent,
    GizmoHandleMeshComponent,
    StaticMeshComponent,

    # Handle Groups
    GizmoHandleGroup,
    AxisGizmoHandleGroup,
    PivotTranslationGizmoHandleGroup,
    PivotScaleGizmoHandleGroup,
    PivotPlaneTranslationGizmoHandleGroup,
    PivotRotationGizmoHandleGroup,
    StretchGizmoHandleGroup,
    UniformScaleGizmoHandleGroup,

    # Interaction
    ViewportWorldInteraction,
    MouseCursorInteractor,
    ViewportInteractor,

    # Transform Sources & Proxies
    TransformProxy,

    # Builders
    TransformGizmoBuilder,
    IntervalGizmoBuilder,
)
from unreal_engine.enums import EComponentMobility
from unreal_engine import FVector, FRotator, FTransform, FLinearColor

# Get the world
world = ue.get_editor_world()

print("=" * 60)
print("TESTING GIZMOS ATTACHED TO ACTORS")
print("=" * 60)


# Helper function to create a test cylinder
def create_test_cylinder(location, name="TestCylinder"):
    """Create a cylinder actor for testing"""
    cylinder = world.actor_spawn(StaticMeshActor)
    cylinder_mesh = ue.load_object(StaticMesh, '/Engine/BasicShapes/Cylinder')
    smc = cylinder.StaticMeshComponent
    smc.SetStaticMesh(cylinder_mesh)
    smc.Mobility = EComponentMobility.Movable

    transform = FTransform(
        location,
        FRotator(0, 0, 0),
        FVector(0.5, 0.5, 1.0)  # Scale
    )
    cylinder.set_actor_transform(transform)
    cylinder.set_actor_label(name)

    print(f"✓ Created {name} at {location}")
    return cylinder


# Test 1: TransformGizmoActor attached to cylinder
print("\n" + "=" * 60)
print("TEST 1: TransformGizmoActor on Cylinder")
print("=" * 60)
try:
    # Create target cylinder
    target_cylinder_1 = create_test_cylinder(FVector(0, 0, 100), "Target_TransformGizmo")

    # Spawn transform gizmo at same location
    transform_gizmo = world.actor_spawn(
        TransformGizmoActor,
        FVector(0, 0, 100),
        FRotator(0, 0, 0)
    )
    print(f"✓ TransformGizmoActor spawned: {transform_gizmo}")

    # Try to attach gizmo to cylinder
    try:
        transform_gizmo.attach_to_actor(target_cylinder_1, '', 0)
        print(f"✓ Attached to cylinder")
    except Exception as e:
        print(f"✗ Attachment failed: {e}")

    # Inspect properties
    try:
        print(f"  SceneComponent: {transform_gizmo.SceneComponent}")
        print(f"  AllHandleGroups: {transform_gizmo.AllHandleGroups}")
        print(f"  WorldInteraction: {transform_gizmo.WorldInteraction}")
    except Exception as e:
        print(f"  Property inspection error: {e}")

except Exception as e:
    print(f"✗ TEST 1 FAILED: {e}")

# Test 2: PivotTransformGizmo attached to cylinder
print("\n" + "=" * 60)
print("TEST 2: PivotTransformGizmo on Cylinder")
print("=" * 60)
try:
    target_cylinder_2 = create_test_cylinder(FVector(300, 0, 100), "Target_PivotGizmo")

    pivot_gizmo = world.actor_spawn(
        PivotTransformGizmo,
        FVector(300, 0, 100),
        FRotator(0, 0, 0)
    )
    print(f"✓ PivotTransformGizmo spawned: {pivot_gizmo}")

    # Attach
    try:
        pivot_gizmo.attach_to_actor(target_cylinder_2, '', 0)
        print(f"✓ Attached to cylinder")
    except Exception as e:
        print(f"✗ Attachment failed: {e}")

    # Inspect handle groups
    try:
        print(f"  TranslationGizmoHandleGroup: {pivot_gizmo.TranslationGizmoHandleGroup}")
        print(f"  RotationGizmoHandleGroup: {pivot_gizmo.RotationGizmoHandleGroup}")
        print(f"  ScaleGizmoHandleGroup: {pivot_gizmo.ScaleGizmoHandleGroup}")
        print(f"  UniformScaleGizmoHandleGroup: {pivot_gizmo.UniformScaleGizmoHandleGroup}")
    except Exception as e:
        print(f"  Handle group inspection error: {e}")

except Exception as e:
    print(f"✗ TEST 2 FAILED: {e}")

# Test 3: Custom gizmo with individual components on cylinder
print("\n" + "=" * 60)
print("TEST 3: Custom Gizmo Components on Cylinder")
print("=" * 60)
try:
    target_cylinder_3 = create_test_cylinder(FVector(600, 0, 100), "Target_CustomComponents")

    # Add Arrow Component for X-axis
    print("\n  Adding GizmoArrowComponent (X-axis - Red)...")
    try:
        arrow_x = target_cylinder_3.add_actor_component(GizmoArrowComponent, 'ArrowX')
        arrow_x.Direction = FVector(1, 0, 0)
        arrow_x.Length = 100.0
        arrow_x.Thickness = 5.0
        arrow_x.Gap = 10.0
        arrow_x.Color = FLinearColor(1, 0, 0, 1)  # Red
        arrow_x.HoverSizeMultiplier = 1.5
        print(f"  ✓ Arrow X added and configured")
    except Exception as e:
        print(f"  ✗ Arrow X failed: {e}")

    # Add Arrow Component for Y-axis
    print("\n  Adding GizmoArrowComponent (Y-axis - Green)...")
    try:
        arrow_y = target_cylinder_3.add_actor_component(GizmoArrowComponent, 'ArrowY')
        arrow_y.Direction = FVector(0, 1, 0)
        arrow_y.Length = 100.0
        arrow_y.Thickness = 5.0
        arrow_y.Gap = 10.0
        arrow_y.Color = FLinearColor(0, 1, 0, 1)  # Green
        arrow_y.HoverSizeMultiplier = 1.5
        print(f"  ✓ Arrow Y added and configured")
    except Exception as e:
        print(f"  ✗ Arrow Y failed: {e}")

    # Add Arrow Component for Z-axis
    print("\n  Adding GizmoArrowComponent (Z-axis - Blue)...")
    try:
        arrow_z = target_cylinder_3.add_actor_component(GizmoArrowComponent, 'ArrowZ')
        arrow_z.Direction = FVector(0, 0, 1)
        arrow_z.Length = 100.0
        arrow_z.Thickness = 5.0
        arrow_z.Gap = 10.0
        arrow_z.Color = FLinearColor(0, 0, 1, 1)  # Blue
        arrow_z.HoverSizeMultiplier = 1.5
        print(f"  ✓ Arrow Z added and configured")
    except Exception as e:
        print(f"  ✗ Arrow Z failed: {e}")

    # Add Circle Component for rotation (XY plane)
    print("\n  Adding GizmoCircleComponent (XY plane)...")
    try:
        circle_xy = target_cylinder_3.add_actor_component(GizmoCircleComponent, 'CircleXY')
        circle_xy.Normal = FVector(0, 0, 1)
        circle_xy.Radius = 80.0
        circle_xy.Thickness = 3.0
        circle_xy.NumSides = 64
        circle_xy.Color = FLinearColor(0.5, 0.5, 1, 0.5)
        circle_xy.bViewAligned = False
        print(f"  ✓ Circle XY added and configured")
    except Exception as e:
        print(f"  ✗ Circle XY failed: {e}")

    # Add Box Component for bounds visualization
    print("\n  Adding GizmoBoxComponent...")
    try:
        box = target_cylinder_3.add_actor_component(GizmoBoxComponent, 'BoundingBox')
        box.Origin = FVector(0, 0, 0)
        box.Dimensions = FVector(60, 60, 60)
        box.LineThickness = 2.0
        box.Color = FLinearColor(1, 1, 0, 0.3)  # Yellow, transparent
        print(f"  ✓ Box added and configured")
    except Exception as e:
        print(f"  ✗ Box failed: {e}")

    # Add Rectangle Component for plane translation (XY)
    print("\n  Adding GizmoRectangleComponent (XY plane)...")
    try:
        rect_xy = target_cylinder_3.add_actor_component(GizmoRectangleComponent, 'RectXY')
        rect_xy.DirectionX = FVector(1, 0, 0)
        rect_xy.DirectionY = FVector(0, 1, 0)
        rect_xy.LengthX = 40.0
        rect_xy.LengthY = 40.0
        rect_xy.Thickness = 1.0
        rect_xy.OffsetX = 50.0
        rect_xy.OffsetY = 50.0
        rect_xy.Color = FLinearColor(1, 1, 0, 0.5)  # Yellow
        print(f"  ✓ Rectangle XY added and configured")
    except Exception as e:
        print(f"  ✗ Rectangle XY failed: {e}")

    print("\n✓ TEST 3 COMPLETE - Check cylinder in viewport!")

except Exception as e:
    print(f"✗ TEST 3 FAILED: {e}")

# Test 4: BaseTransformGizmo on cylinder
print("\n" + "=" * 60)
print("TEST 4: BaseTransformGizmo on Cylinder")
print("=" * 60)
try:
    target_cylinder_4 = create_test_cylinder(FVector(900, 0, 100), "Target_BaseGizmo")

    base_gizmo = world.actor_spawn(
        BaseTransformGizmo,
        FVector(900, 0, 100),
        FRotator(0, 0, 0)
    )
    print(f"✓ BaseTransformGizmo spawned: {base_gizmo}")

    # Attach
    try:
        base_gizmo.attach_to_actor(target_cylinder_4, '', 0)
        print(f"✓ Attached to cylinder")
    except Exception as e:
        print(f"✗ Attachment failed: {e}")

except Exception as e:
    print(f"✗ TEST 4 FAILED: {e}")

# Test 5: IntervalGizmoActor on cylinder
print("\n" + "=" * 60)
print("TEST 5: IntervalGizmoActor on Cylinder")
print("=" * 60)
try:
    target_cylinder_5 = create_test_cylinder(FVector(1200, 0, 100), "Target_IntervalGizmo")

    interval_gizmo = world.actor_spawn(
        IntervalGizmoActor,
        FVector(1200, 0, 100),
        FRotator(0, 0, 0)
    )
    print(f"✓ IntervalGizmoActor spawned: {interval_gizmo}")

    # Attach
    try:
        interval_gizmo.attach_to_actor(target_cylinder_5, '', 0)
        print(f"✓ Attached to cylinder")
    except Exception as e:
        print(f"✗ Attachment failed: {e}")

    # Inspect components
    try:
        print(f"  UpIntervalComponent: {interval_gizmo.UpIntervalComponent}")
        print(f"  DownIntervalComponent: {interval_gizmo.DownIntervalComponent}")
        print(f"  ForwardIntervalComponent: {interval_gizmo.ForwardIntervalComponent}")
    except Exception as e:
        print(f"  Component inspection error: {e}")

except Exception as e:
    print(f"✗ TEST 5 FAILED: {e}")

# Test 6: Testing component visibility and interaction
print("\n" + "=" * 60)
print("TEST 6: Component Visibility & Interaction")
print("=" * 60)
try:
    target_cylinder_6 = create_test_cylinder(FVector(1500, 0, 100), "Target_VisibilityTest")

    # Add a line handle component
    print("\n  Adding GizmoLineHandleComponent...")
    try:
        line_handle = target_cylinder_6.add_actor_component(GizmoLineHandleComponent, 'LineHandle')
        line_handle.Normal = FVector(0, 0, 1)
        line_handle.HandleSize = 25.0
        line_handle.Thickness = 4.0
        line_handle.Direction = FVector(1, 0, 0)
        line_handle.Length = 120.0
        line_handle.Color = FLinearColor(1, 0, 1, 1)  # Magenta
        line_handle.bImageScale = True
        print(f"  ✓ Line handle added")

        # Test visibility methods
        print(f"  Testing visibility methods...")
        print(f"    IsVisible: {line_handle.IsVisible()}")
        line_handle.SetVisibility(True)
        print(f"    Set visibility to True")

        # Test hover state (if available)
        try:
            line_handle.UpdateHoverState(True, 0)
            print(f"    Updated hover state")
        except:
            print(f"    UpdateHoverState not available or requires parameters")

    except Exception as e:
        print(f"  ✗ Line handle failed: {e}")

except Exception as e:
    print(f"✗ TEST 6 FAILED: {e}")

# Test 7: TransformProxy connection test
print("\n" + "=" * 60)
print("TEST 7: TransformProxy Connection")
print("=" * 60)
try:
    target_cylinder_7 = create_test_cylinder(FVector(1800, 0, 100), "Target_ProxyTest")

    # Create transform proxy
    proxy = TransformProxy()
    print(f"✓ TransformProxy created: {proxy}")

    # Try to set initial transform
    try:
        initial_transform = target_cylinder_7.get_actor_transform()
        proxy.SharedTransform = initial_transform
        proxy.InitialSharedTransform = initial_transform
        print(f"✓ Proxy transforms set")
        print(f"  SharedTransform location: {proxy.SharedTransform.translation}")
    except Exception as e:
        print(f"✗ Proxy transform setting failed: {e}")

    # Create a gizmo and try to connect proxy
    try:
        gizmo_with_proxy = world.actor_spawn(
            TransformGizmoActor,
            FVector(1800, 0, 100),
            FRotator(0, 0, 0)
        )
        print(f"✓ Gizmo for proxy test spawned")
        # Note: Actual connection might require more setup
    except Exception as e:
        print(f"✗ Gizmo with proxy failed: {e}")

except Exception as e:
    print(f"✗ TEST 7 FAILED: {e}")

print("\n" + "=" * 60)
print("TESTING COMPLETE - CHECK VIEWPORT")
print("=" * 60)

print("\nSUMMARY:")
print("- Look for cylinders in your viewport at different locations")
print("- Test cylinders should have gizmo components attached")
print("- Try selecting and manipulating the target actors")
print("\nKEY LOCATIONS:")
print("  X=0:    TransformGizmoActor")
print("  X=300:  PivotTransformGizmo")
print("  X=600:  Custom Components (arrows, circles, box, rect)")
print("  X=900:  BaseTransformGizmo")
print("  X=1200: IntervalGizmoActor")
print("  X=1500: Visibility Test")
print("  X=1800: TransformProxy Test")