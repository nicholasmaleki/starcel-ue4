from typing import Any, List

class FVector:
    X: float
    Y: float
    Z: float

class FRotator:
    Pitch: float
    Yaw: float
    Roll: float

class FTransform:
    Translation: FVector
    Rotation: FRotator
    Scale3D: FVector

class FQuat:
    X: float
    Y: float
    Z: float
    W: float

class FLinearColor:
    R: float
    G: float
    B: float
    A: float

class FColor:
    R: int
    G: int
    B: int
    A: int

class FHitResult:
    bBlockingHit: bool
    bStartPenetrating: bool
    Time: float
    Distance: float
    Location: FVector
    ImpactPoint: FVector
    Normal: FVector
    ImpactNormal: FVector
    PhysMaterial: Any
    HitObject: Any
    BoneName: str
    FaceIndex: int

class FVector2D:
    X: float
    Y: float

class FMargin:
    Left: float
    Top: float
    Right: float
    Bottom: float

class FSlateColor:
    SpecifiedColor: FLinearColor
    ColorUseRule: int

class FAnchors:
    Minimum: FVector2D
    Maximum: FVector2D

class FAnchorData:
    Offsets: FMargin
    Anchors: FAnchors
    Alignment: FVector2D
    SizeRule: int

class FStaticMeshSourceModel:
    BuildSettings: FMeshBuildSettings
    ReductionSettings: Any
    ScreenSize: float

class FMeshBuildSettings:
    bRecomputeNormals: bool
    bRecomputeTangents: bool
    bRemoveDegenerates: bool
    bUseMikkTSpace: bool
    bBuildAdjacencyBuffer: bool
    bUseHighPrecisionTangentBasis: bool
    bUseFullPrecisionUVs: bool
    bGenerateLightmapUVs: bool
    MinLightmapResolution: int
    SrcLightmapIndex: int
    DstLightmapIndex: int

class FStaticMaterial:
    MaterialInterface: Any
    MaterialSlotName: str
    UVChannelData: Any
    ImportedMaterialSlotName: str

class FInputActionKeyMapping:
    ActionName: str
    Key: Any
    bShift: bool
    bCtrl: bool
    bAlt: bool
    bCmd: bool

class FKey:
    KeyName: str

class FGraphReference:
    GraphGuid: str
    GraphBlueprint: Any
    NodeGuid: str

class FAggregateGeom:
    Spheres: list[Any]
    Boxes: list[Any]
    Sphyls: list[Any]
    ConvexElems: list[Any]

class FEdGraphPinType:
    PinCategory: str
    PinSubCategory: str
    PinSubCategoryObject: Any
    bIsArray: bool
    bIsReference: bool
    bIsConst: bool
    bIsWeakPointer: bool
    bIsUObjectWrapper: bool
    PinValueType: Any

class FEdGraphTerminalType:
    TerminalCategory: str
    TerminalSubCategory: str
    TerminalSubCategoryObject: Any
    bTerminalIsArray: bool
    bTerminalIsReference: bool
    bTerminalIsConst: bool
    bTerminalIsWeakPointer: bool
    bTerminalIsUObjectWrapper: bool

