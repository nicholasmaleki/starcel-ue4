// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SAVEEXTENSION_SaveSettings_generated_h
#error "SaveSettings.generated.h already included, missing '#pragma once' in SaveSettings.h"
#endif
#define SAVEEXTENSION_SaveSettings_generated_h

#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h_16_SPARSE_DATA
#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h_16_RPC_WRAPPERS
#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h_16_RPC_WRAPPERS_NO_PURE_DECLS
#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSaveSettings(); \
	friend struct Z_Construct_UClass_USaveSettings_Statics; \
public: \
	DECLARE_CLASS(USaveSettings, UDeveloperSettings, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig | CLASS_Config), CASTCLASS_None, TEXT("/Script/SaveExtension"), NO_API) \
	DECLARE_SERIALIZER(USaveSettings) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h_16_INCLASS \
private: \
	static void StaticRegisterNativesUSaveSettings(); \
	friend struct Z_Construct_UClass_USaveSettings_Statics; \
public: \
	DECLARE_CLASS(USaveSettings, UDeveloperSettings, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig | CLASS_Config), CASTCLASS_None, TEXT("/Script/SaveExtension"), NO_API) \
	DECLARE_SERIALIZER(USaveSettings) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h_16_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USaveSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USaveSettings) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USaveSettings); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USaveSettings); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USaveSettings(USaveSettings&&); \
	NO_API USaveSettings(const USaveSettings&); \
public:


#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h_16_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USaveSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USaveSettings(USaveSettings&&); \
	NO_API USaveSettings(const USaveSettings&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USaveSettings); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USaveSettings); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USaveSettings)


#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h_16_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__Preset() { return STRUCT_OFFSET(USaveSettings, Preset); }


#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h_13_PROLOG
#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h_16_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h_16_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h_16_SPARSE_DATA \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h_16_RPC_WRAPPERS \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h_16_INCLASS \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h_16_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h_16_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h_16_SPARSE_DATA \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h_16_INCLASS_NO_PURE_DECLS \
	Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SAVEEXTENSION_API UClass* StaticClass<class USaveSettings>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Starcel9_Plugins_SaveExtension_Source_SaveExtension_Public_SaveSettings_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
