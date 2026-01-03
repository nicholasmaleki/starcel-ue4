// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FSEComponentClassFilter;
struct FSEActorClassFilter;
#ifdef SAVEEXTENSION_SavePreset_generated_h
#error "SavePreset.generated.h already included, missing '#pragma once' in SavePreset.h"
#endif
#define SAVEEXTENSION_SavePreset_generated_h

#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_SPARSE_DATA
#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_RPC_WRAPPERS \
	virtual void BPGetSlotNameFromId_Implementation(int32 Id, FName& Name) const; \
 \
	DECLARE_FUNCTION(execGetComponentFilter); \
	DECLARE_FUNCTION(execGetActorFilter); \
	DECLARE_FUNCTION(execBPGetSlotNameFromId);


#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void BPGetSlotNameFromId_Implementation(int32 Id, FName& Name) const; \
 \
	DECLARE_FUNCTION(execGetComponentFilter); \
	DECLARE_FUNCTION(execGetActorFilter); \
	DECLARE_FUNCTION(execBPGetSlotNameFromId);


#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_EVENT_PARMS \
	struct SavePreset_eventBPGetSlotNameFromId_Parms \
	{ \
		int32 Id; \
		FName Name; \
	};


#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_CALLBACK_WRAPPERS
#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSavePreset(); \
	friend struct Z_Construct_UClass_USavePreset_Statics; \
public: \
	DECLARE_CLASS(USavePreset, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SaveExtension"), NO_API) \
	DECLARE_SERIALIZER(USavePreset)


#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_INCLASS \
private: \
	static void StaticRegisterNativesUSavePreset(); \
	friend struct Z_Construct_UClass_USavePreset_Statics; \
public: \
	DECLARE_CLASS(USavePreset, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SaveExtension"), NO_API) \
	DECLARE_SERIALIZER(USavePreset)


#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USavePreset(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USavePreset) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USavePreset); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USavePreset); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USavePreset(USavePreset&&); \
	NO_API USavePreset(const USavePreset&); \
public:


#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USavePreset(USavePreset&&); \
	NO_API USavePreset(const USavePreset&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USavePreset); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USavePreset); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(USavePreset)


#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__bSaveAndLoadSublevels() { return STRUCT_OFFSET(USavePreset, bSaveAndLoadSublevels); }


#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_31_PROLOG \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_EVENT_PARMS


#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_SPARSE_DATA \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_RPC_WRAPPERS \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_CALLBACK_WRAPPERS \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_INCLASS \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_SPARSE_DATA \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_RPC_WRAPPERS_NO_PURE_DECLS \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_CALLBACK_WRAPPERS \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_INCLASS_NO_PURE_DECLS \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h_34_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SAVEEXTENSION_API UClass* StaticClass<class USavePreset>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SavePreset_h


#define FOREACH_ENUM_ESAVEASYNCMODE(op) \
	op(ESaveASyncMode::OnlySync) \
	op(ESaveASyncMode::LoadAsync) \
	op(ESaveASyncMode::SaveAsync) \
	op(ESaveASyncMode::SaveAndLoadAsync) 

enum class ESaveASyncMode : uint8;
template<> SAVEEXTENSION_API UEnum* StaticEnum<ESaveASyncMode>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
