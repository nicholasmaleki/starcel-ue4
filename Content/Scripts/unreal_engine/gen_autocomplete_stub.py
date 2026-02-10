import unreal_engine as ue
from pathlib import Path
import pystubgen, inspect, re, os
import unreal_engine.enums as enums
import unreal_engine.structs as structs

#TODO: rewrite UnrealEnginePython C++ Plugin to include all_enums() and all_structs()
#TODO: Maybe add unreal to python property mapping
# Unreal property	Python value
# float	            float
# int32	            int
# bool	            bool
# FString	        str
# FName	            str
# UObject*	        UObject wrapper
# UStruct	        struct wrapper
# TArray<T>	        list

# class Main:
#     # this is called on game start
#     def begin_play(self):
#         self.gen_intellisense_stubs()
#         self.gen_intellisense_stubs_classes()
#         self.gen_intellisense_stubs_structs()
#         self.gen_intellisense_stubs_enums()

def gen_intellisense_stubs():
    """
    Generates Python stubs for all Unreal classes in ue.all_classes()
    Replaces __unknown_params__ with (*args, **kwargs)
    Differentiates instance vs static methods
    """
    # --- UE4.27 constants stub ---
    constants_stub = '''\
# --- Class Flags (CLASS_*) ---
CLASS_NONE: int
CLASS_ABSTRACT: int
CLASS_DEFAULT_CONFIG: int
CLASS_CONFIG: int
CLASS_TRANSIENT: int
CLASS_OPTIONAL: int
CLASS_CONFIG_DO_NOT_CHECK_DEFAULTS: int

# --- Property Flags (CPF_*) ---
CPF_NONE: int
CPF_EDIT: int
CPF_CONSTPARM: int
CPF_BLUEPRINT_VISIBLE: int
CPF_EXPORT_OBJECT: int
CPF_BLUEPRINT_READ_ONLY: int
CPF_NET: int
CPF_EDIT_FIXED_SIZE: int
CPF_PARM: int
CPF_OUT_PARM: int
CPF_ZERO_CONSTRUCTOR: int
CPF_RETURN_PARM: int
CPF_DISABLE_EDIT_ON_TEMPLATE: int
CPF_NON_NULLABLE: int
CPF_TRANSIENT: int
CPF_CONFIG: int
CPF_REQUIRED_PARM: int
CPF_DISABLE_EDIT_ON_INSTANCE: int
CPF_EDIT_CONST: int
CPF_GLOBAL_CONFIG: int
CPF_INSTANCED_REFERENCE: int
CPF_EXPERIMENTAL_EXTERNAL_OBJECTS: int
CPF_DUPLICATE_TRANSIENT: int
CPF_SAVE_GAME: int
CPF_NO_CLEAR: int
CPF_VIRTUAL: int
CPF_REFERENCE_PARM: int
CPF_BLUEPRINT_ASSIGNABLE: int
CPF_DEPRECATED: int
CPF_IS_PLAIN_OLD_DATA: int
CPF_REP_SKIP: int
CPF_REP_NOTIFY: int
CPF_INTERP: int
CPF_NON_TRANSACTIONAL: int
CPF_EDITOR_ONLY: int
CPF_NO_DESTRUCTOR: int
CPF_AUTO_WEAK: int
CPF_CONTAINS_INSTANCED_REFERENCE: int
CPF_ASSET_REGISTRY_SEARCHABLE: int
CPF_SIMPLE_DISPLAY: int
CPF_ADVANCED_DISPLAY: int
CPF_PROTECTED: int
CPF_BLUEPRINT_CALLABLE: int
CPF_BLUEPRINT_AUTHORITY_ONLY: int
CPF_TEXT_EXPORT_TRANSIENT: int
CPF_NON_PIE_DUPLICATE_TRANSIENT: int
CPF_EXPOSE_ON_SPAWN: int
CPF_PERSISTENT_INSTANCE: int
CPF_UOBJECT_WRAPPER: int
CPF_HAS_GET_VALUE_TYPE_HASH: int
CPF_NATIVE_ACCESS_SPECIFIER_PUBLIC: int
CPF_NATIVE_ACCESS_SPECIFIER_PROTECTED: int
CPF_NATIVE_ACCESS_SPECIFIER_PRIVATE: int
CPF_SKIP_SERIALIZATION: int
CPF_TOBJECT_PTR: int
CPF_EXPERIMENTAL_OVERRIDABLE_LOGIC: int
CPF_EXPERIMENTAL_ALWAYS_OVERRIDEN: int
CPF_EXPERIMENTAL_NEVER_OVERRIDEN: int
CPF_ALLOW_SELF_REFERENCE: int

# --- Object Flags (RF_*) ---
RF_NO_FLAGS: int
RF_PUBLIC: int
RF_STANDALONE: int
RF_MARK_AS_NATIVE: int
RF_TRANSACTIONAL: int
RF_CLASS_DEFAULT_OBJECT: int
RF_ARCHETYPE_OBJECT: int
RF_TRANSIENT: int
RF_MARK_AS_ROOT_SET: int
RF_TAG_GARBAGE_TEMP: int
RF_NEED_INITIALIZATION: int
RF_NEED_LOAD: int
RF_KEEP_FOR_COOKER: int
RF_NEED_POST_LOAD: int
RF_NEED_POST_LOAD_SUBOBJECTS: int
RF_NEWER_VERSION_EXISTS: int
RF_BEGIN_DESTROYED: int
RF_FINISH_DESTROYED: int
RF_BEING_REGENERATED: int
RF_DEFAULT_SUB_OBJECT: int
RF_WAS_LOADED: int
RF_TEXT_EXPORT_TRANSIENT: int
RF_LOAD_COMPLETED: int
RF_INHERITABLE_COMPONENT_TEMPLATE: int
RF_DUPLICATE_TRANSIENT: int
RF_STRONG_REF_ON_FRAME: int
RF_DYNAMIC: int
RF_WILL_BE_LOADED: int
RF_HAS_EXTERNAL_PACKAGE: int
RF_ALL_FLAGS: int
'''

    # --- Generate the original source ---
    source = pystubgen.make_source(ue)

    functions_list = [o[1] for o in inspect.getmembers(ue) if inspect.isroutine(o[1])]
    funcDefs = '\n'.join([pystubgen.make_source(funcObj) for funcObj in functions_list])

    # --- Replace all __unknown_params__ with self, *args, **kwargs ---
    source = re.sub(r"\(__unknown_params__\)", "(self, *args, **kwargs)", source)

    # --- Output path ---
    stubFilePath = Path(os.path.join(os.path.abspath(ue.get_content_dir()),
                                     "Scripts", "unreal_engine", "__init__.py"))
    print(os.getcwd())

    if not os.access(str(stubFilePath), os.W_OK):
        print(f"p4 edit {str(stubFilePath)}")
        os.system(f"p4 edit {str(stubFilePath)} && pause>nul")

    # --- Write everything to file ---
    with open(str(stubFilePath), 'w', encoding='utf8') as outputFile:
        outputFile.write('# UE4.27 Constants Stub\n')
        outputFile.write(constants_stub)
        outputFile.write('\n\n# Freeform Methods\n')
        outputFile.write(funcDefs)
        outputFile.write('\n\n# Fixed Unreal module stubs\n')
        outputFile.write(source)

    # source = pystubgen.make_source(ue)
    #
    # functions_list = [o[1] for o in inspect.getmembers(ue) if inspect.isroutine(o[1])]
    # funcDefs = '\n'.join([pystubgen.make_source(funcObj) for funcObj in functions_list])
    #
    # # --- Output path ---
    # stubFilePath = Path(os.path.join(os.path.abspath(ue.get_content_dir()), "Scripts", "unreal_engine", "__init__.py"))
    # print(os.getcwd())
    #
    # if not os.access(str(stubFilePath), os.W_OK):
    #     print(f"p4 edit {str(stubFilePath)}")
    #     os.system(f"p4 edit {str(stubFilePath)} && pause>nul")
    #
    # # --- Write everything to file ---
    # with open(str(stubFilePath), 'w', encoding='utf8') as outputFile:
    #     outputFile.write('# UE4.27 Constants Stub\n')
    #     outputFile.write(constants_stub)
    #     outputFile.write('\n\n# Freeform Methods\n')
    #     outputFile.write(funcDefs)
    #     outputFile.write('\n\n')
    #     outputFile.write(source)

    print("Stub generation complete:", stubFilePath)


def gen_intellisense_stubs_classes():
    class_def_list = []
    for _class in ue.all_classes():
        class_def = [f'class {_class.get_name()}:']
        for function in _class.functions():
            class_def.append(f'    def {function}(__unknown_params__):')
            class_def.append(f'        pass\n')

        for _property in _class.properties():
            class_def.append(f'    {_property} = "__unknown__"\n')

        class_def_list.append('\n'.join(class_def))

    stubFilePath = Path(os.path.join(os.path.abspath(ue.get_content_dir()), "Scripts", "unreal_engine", "classes.py"))
    with open(str(stubFilePath), 'w', encoding='utf8') as outputFile:
        outputFile.write('\n'.join(class_def_list))

    print("Stub generation complete:", stubFilePath)


def gen_intellisense_stubs_structs():
    # Mapping of structs to fields with Python types
    structs_to_stub = {
        "FVector": {"X": float, "Y": float, "Z": float},
        "FRotator": {"Pitch": float, "Yaw": float, "Roll": float},
        "FTransform": {"Translation": "FVector", "Rotation": "FRotator", "Scale3D": "FVector"},
        "FQuat": {"X": float, "Y": float, "Z": float, "W": float},
        "FLinearColor": {"R": float, "G": float, "B": float, "A": float},
        "FColor": {"R": int, "G": int, "B": int, "A": int},
        "FHitResult": {
            "bBlockingHit": bool, "bStartPenetrating": bool, "Time": float, "Distance": float,
            "Location": "FVector", "ImpactPoint": "FVector", "Normal": "FVector", "ImpactNormal": "FVector",
            "PhysMaterial": "Any", "HitObject": "Any", "BoneName": str, "FaceIndex": int
        },
        "FVector2D": {"X": float, "Y": float},
        "FMargin": {"Left": float, "Top": float, "Right": float, "Bottom": float},
        "FSlateColor": {"SpecifiedColor": "FLinearColor", "ColorUseRule": int},
        "FAnchors": {"Minimum": "FVector2D", "Maximum": "FVector2D"},
        "FAnchorData": {"Offsets": "FMargin", "Anchors": "FAnchors", "Alignment": "FVector2D", "SizeRule": int},
        "FStaticMeshSourceModel": {"BuildSettings": "FMeshBuildSettings", "ReductionSettings": "Any", "ScreenSize": float},
        "FMeshBuildSettings": {
            "bRecomputeNormals": bool, "bRecomputeTangents": bool, "bRemoveDegenerates": bool,
            "bUseMikkTSpace": bool, "bBuildAdjacencyBuffer": bool, "bUseHighPrecisionTangentBasis": bool,
            "bUseFullPrecisionUVs": bool, "bGenerateLightmapUVs": bool, "MinLightmapResolution": int,
            "SrcLightmapIndex": int, "DstLightmapIndex": int
        },
        "FStaticMaterial": {"MaterialInterface": "Any", "MaterialSlotName": str, "UVChannelData": "Any", "ImportedMaterialSlotName": str},

        # Project-specific structs
        "FInputActionKeyMapping": {"ActionName": str, "Key": "Any", "bShift": bool, "bCtrl": bool, "bAlt": bool, "bCmd": bool},
        "FKey": {"KeyName": str},
        "FGraphReference": {"GraphGuid": str, "GraphBlueprint": "Any", "NodeGuid": str},
        "FAggregateGeom": {"Spheres": "list[Any]", "Boxes": "list[Any]", "Sphyls": "list[Any]", "ConvexElems": "list[Any]"},
        "FEdGraphPinType": {
            "PinCategory": str, "PinSubCategory": str, "PinSubCategoryObject": "Any", "bIsArray": bool,
            "bIsReference": bool, "bIsConst": bool, "bIsWeakPointer": bool, "bIsUObjectWrapper": bool, "PinValueType": "Any"
        },
        "FEdGraphTerminalType": {
            "TerminalCategory": str, "TerminalSubCategory": str, "TerminalSubCategoryObject": "Any",
            "bTerminalIsArray": bool, "bTerminalIsReference": bool, "bTerminalIsConst": bool,
            "bTerminalIsWeakPointer": bool, "bTerminalIsUObjectWrapper": bool
        },
    }

    stubFilePath = Path(os.path.join(os.path.abspath(ue.get_content_dir()), "Scripts", "unreal_engine", "structs.py"))

    with open(stubFilePath, "w", encoding="utf8") as f:
        f.write("from typing import Any, List\n\n")
        for struct_name, fields in structs_to_stub.items():
            f.write(f"class {struct_name}:\n")
            if not fields:
                f.write("    pass\n\n")
                continue
            for field_name, field_type in fields.items():
                if isinstance(field_type, str):
                    type_str = field_type
                elif isinstance(field_type, type):
                    type_str = field_type.__name__
                else:
                    type_str = "Any"
                f.write(f"    {field_name}: {type_str}\n")
            f.write("\n")

    print("Stub generation complete:", stubFilePath)

# TODO: EBlendMode, EPixelFormat, EMouseCursor etc.
def gen_intellisense_stubs_enums():
    ENGINE_ENUMS = [
        # Collision / tracing
        "ECollisionChannel",
        "ECollisionEnabled",
        "ECollisionResponse",
        "ECollisionResponseContainer",
        "EObjectTypeQuery",
        "ETraceTypeQuery",
        "EDrawDebugTrace",

        # Ticking / lifecycle
        "ETickingGroup",
        "EEndPlayReason",

        # Actor / component
        "EAutoReceiveInput",
        "EComponentMobility",
        "ENetRole",
        "ENetDormancy",

        # Input
        "EInputEvent",
        "EControllerHand",
        "EUserInterfaceActionType",
        "EInputEvent",

        # Physics
        "EPhysicalSurface",

        # Rendering
        "EDepthPriorityGroup",
        "EBlendMode",

        # Misc
        "ELifetimeCondition",
        "EAttachmentRule",
    ]

    enum_def_list = []
    for enum_name in ENGINE_ENUMS:
        try:
            enum_obj = getattr(enums, enum_name)
        except Exception:
            continue  # enum not available in this engine version

        enum_def = [f"class {enum_name}:"]

        try:
            for entry in enum_obj:
                name = getattr(entry, "name", None)
                value = getattr(entry, "value", None)

                if not name:
                    continue

                if value is None:
                    enum_def.append(f"    {name} = 0")
                else:
                    enum_def.append(f"    {name} = {value}")
        except Exception:
            enum_def.append("    pass")

        enum_def.append("")
        enum_def_list.append("\n".join(enum_def))

    stubFilePath = Path(
        os.path.join(os.path.abspath(ue.get_content_dir()), "Scripts", "unreal_engine", "enums.py")
    )

    with open(stubFilePath, "w", encoding="utf8") as outputFile:
        outputFile.write("\n".join(enum_def_list))

    print("Stub generation complete:", stubFilePath)


print("Started building stubs for unreal_engine, classes, structs, and enums")
gen_intellisense_stubs()
gen_intellisense_stubs_classes()
gen_intellisense_stubs_structs()
gen_intellisense_stubs_enums()
print("Finished building stubs")