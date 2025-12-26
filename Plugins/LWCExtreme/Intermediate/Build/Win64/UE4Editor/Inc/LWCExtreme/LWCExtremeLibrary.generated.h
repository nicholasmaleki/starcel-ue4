// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FHybridTransform;
struct FHybridVector;
struct FHybridQuaternion;
struct FHybridNumber;
#ifdef LWCEXTREME_LWCExtremeLibrary_generated_h
#error "LWCExtremeLibrary.generated.h already included, missing '#pragma once' in LWCExtremeLibrary.h"
#endif
#define LWCEXTREME_LWCExtremeLibrary_generated_h

#define Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h_13_SPARSE_DATA
#define Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h_13_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execTransformGetScale); \
	DECLARE_FUNCTION(execTransformGetRotation); \
	DECLARE_FUNCTION(execTransformGetLocation); \
	DECLARE_FUNCTION(execTransformVector); \
	DECLARE_FUNCTION(execTransformPosition); \
	DECLARE_FUNCTION(execTransformInverse); \
	DECLARE_FUNCTION(execTransformMultiply); \
	DECLARE_FUNCTION(execQuatRotateVector); \
	DECLARE_FUNCTION(execQuatSlerp); \
	DECLARE_FUNCTION(execQuatInverse); \
	DECLARE_FUNCTION(execQuatConjugate); \
	DECLARE_FUNCTION(execQuatNormalize); \
	DECLARE_FUNCTION(execQuatScalarMultiply); \
	DECLARE_FUNCTION(execQuatSubtract); \
	DECLARE_FUNCTION(execQuatAdd); \
	DECLARE_FUNCTION(execQuatMultiply); \
	DECLARE_FUNCTION(execVectorProjectOn); \
	DECLARE_FUNCTION(execVectorDistanceSquared); \
	DECLARE_FUNCTION(execVectorDistance); \
	DECLARE_FUNCTION(execVectorLerp); \
	DECLARE_FUNCTION(execVectorNormalize); \
	DECLARE_FUNCTION(execVectorSize); \
	DECLARE_FUNCTION(execVectorCombine); \
	DECLARE_FUNCTION(execVectorComponentScale); \
	DECLARE_FUNCTION(execVectorScale); \
	DECLARE_FUNCTION(execVectorSubtract); \
	DECLARE_FUNCTION(execVectorAdd); \
	DECLARE_FUNCTION(execVectorCross); \
	DECLARE_FUNCTION(execVectorDot); \
	DECLARE_FUNCTION(execTan); \
	DECLARE_FUNCTION(execCos); \
	DECLARE_FUNCTION(execSin); \
	DECLARE_FUNCTION(execExp); \
	DECLARE_FUNCTION(execLn); \
	DECLARE_FUNCTION(execSqrt);


#define Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execTransformGetScale); \
	DECLARE_FUNCTION(execTransformGetRotation); \
	DECLARE_FUNCTION(execTransformGetLocation); \
	DECLARE_FUNCTION(execTransformVector); \
	DECLARE_FUNCTION(execTransformPosition); \
	DECLARE_FUNCTION(execTransformInverse); \
	DECLARE_FUNCTION(execTransformMultiply); \
	DECLARE_FUNCTION(execQuatRotateVector); \
	DECLARE_FUNCTION(execQuatSlerp); \
	DECLARE_FUNCTION(execQuatInverse); \
	DECLARE_FUNCTION(execQuatConjugate); \
	DECLARE_FUNCTION(execQuatNormalize); \
	DECLARE_FUNCTION(execQuatScalarMultiply); \
	DECLARE_FUNCTION(execQuatSubtract); \
	DECLARE_FUNCTION(execQuatAdd); \
	DECLARE_FUNCTION(execQuatMultiply); \
	DECLARE_FUNCTION(execVectorProjectOn); \
	DECLARE_FUNCTION(execVectorDistanceSquared); \
	DECLARE_FUNCTION(execVectorDistance); \
	DECLARE_FUNCTION(execVectorLerp); \
	DECLARE_FUNCTION(execVectorNormalize); \
	DECLARE_FUNCTION(execVectorSize); \
	DECLARE_FUNCTION(execVectorCombine); \
	DECLARE_FUNCTION(execVectorComponentScale); \
	DECLARE_FUNCTION(execVectorScale); \
	DECLARE_FUNCTION(execVectorSubtract); \
	DECLARE_FUNCTION(execVectorAdd); \
	DECLARE_FUNCTION(execVectorCross); \
	DECLARE_FUNCTION(execVectorDot); \
	DECLARE_FUNCTION(execTan); \
	DECLARE_FUNCTION(execCos); \
	DECLARE_FUNCTION(execSin); \
	DECLARE_FUNCTION(execExp); \
	DECLARE_FUNCTION(execLn); \
	DECLARE_FUNCTION(execSqrt);


#define Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULWCExtremeLibrary(); \
	friend struct Z_Construct_UClass_ULWCExtremeLibrary_Statics; \
public: \
	DECLARE_CLASS(ULWCExtremeLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LWCExtreme"), NO_API) \
	DECLARE_SERIALIZER(ULWCExtremeLibrary)


#define Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h_13_INCLASS \
private: \
	static void StaticRegisterNativesULWCExtremeLibrary(); \
	friend struct Z_Construct_UClass_ULWCExtremeLibrary_Statics; \
public: \
	DECLARE_CLASS(ULWCExtremeLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LWCExtreme"), NO_API) \
	DECLARE_SERIALIZER(ULWCExtremeLibrary)


#define Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h_13_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULWCExtremeLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULWCExtremeLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULWCExtremeLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULWCExtremeLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULWCExtremeLibrary(ULWCExtremeLibrary&&); \
	NO_API ULWCExtremeLibrary(const ULWCExtremeLibrary&); \
public:


#define Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h_13_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULWCExtremeLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULWCExtremeLibrary(ULWCExtremeLibrary&&); \
	NO_API ULWCExtremeLibrary(const ULWCExtremeLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULWCExtremeLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULWCExtremeLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULWCExtremeLibrary)


#define Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h_13_PRIVATE_PROPERTY_OFFSET
#define Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h_10_PROLOG
#define Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h_13_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h_13_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h_13_SPARSE_DATA \
	Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h_13_RPC_WRAPPERS \
	Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h_13_INCLASS \
	Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h_13_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h_13_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h_13_SPARSE_DATA \
	Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h_13_INCLASS_NO_PURE_DECLS \
	Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LWCEXTREME_API UClass* StaticClass<class ULWCExtremeLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Starcel9_Plugins_LWCExtreme_Source_LWCExtreme_Public_LWCExtremeLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
