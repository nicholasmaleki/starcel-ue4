// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef HANDDRIVER_HandComponent_generated_h
#error "HandComponent.generated.h already included, missing '#pragma once' in HandComponent.h"
#endif
#define HANDDRIVER_HandComponent_generated_h

#define Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h_23_SPARSE_DATA
#define Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h_23_RPC_WRAPPERS
#define Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h_23_RPC_WRAPPERS_NO_PURE_DECLS
#define Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h_23_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUHandComponent(); \
	friend struct Z_Construct_UClass_UHandComponent_Statics; \
public: \
	DECLARE_CLASS(UHandComponent, USceneComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/HandDriver"), NO_API) \
	DECLARE_SERIALIZER(UHandComponent)


#define Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h_23_INCLASS \
private: \
	static void StaticRegisterNativesUHandComponent(); \
	friend struct Z_Construct_UClass_UHandComponent_Statics; \
public: \
	DECLARE_CLASS(UHandComponent, USceneComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/HandDriver"), NO_API) \
	DECLARE_SERIALIZER(UHandComponent)


#define Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h_23_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UHandComponent(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UHandComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UHandComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UHandComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UHandComponent(UHandComponent&&); \
	NO_API UHandComponent(const UHandComponent&); \
public:


#define Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h_23_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UHandComponent(UHandComponent&&); \
	NO_API UHandComponent(const UHandComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UHandComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UHandComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UHandComponent)


#define Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h_23_PRIVATE_PROPERTY_OFFSET
#define Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h_20_PROLOG
#define Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h_23_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h_23_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h_23_SPARSE_DATA \
	Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h_23_RPC_WRAPPERS \
	Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h_23_INCLASS \
	Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h_23_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h_23_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h_23_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h_23_SPARSE_DATA \
	Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
	Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h_23_INCLASS_NO_PURE_DECLS \
	Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h_23_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> HANDDRIVER_API UClass* StaticClass<class UHandComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Public_HandComponent_h


#define FOREACH_ENUM_EHANDAXIS(op) \
	op(EHandAxis::X) \
	op(EHandAxis::Y) \
	op(EHandAxis::Z) \
	op(EHandAxis::negative_X) \
	op(EHandAxis::negative_Y) \
	op(EHandAxis::negative_Z) 

enum class EHandAxis : uint8;
template<> HANDDRIVER_API UEnum* StaticEnum<EHandAxis>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
