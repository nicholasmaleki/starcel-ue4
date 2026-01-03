// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FInputImageDescription;
struct FTransformImageParams;
struct FColor;
struct FLatentActionInfo;
class UObject;
class UTexture2D;
class UTextureCube;
#ifdef RUNTIMEIMAGELOADER_RuntimeImageLoader_generated_h
#error "RuntimeImageLoader.generated.h already included, missing '#pragma once' in RuntimeImageLoader.h"
#endif
#define RUNTIMEIMAGELOADER_RuntimeImageLoader_generated_h

#define HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h_50_SPARSE_DATA
#define HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h_50_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetThisPluginResourcesDirectory); \
	DECLARE_FUNCTION(execFindImagesInDirectory); \
	DECLARE_FUNCTION(execLoadFileToByteArray); \
	DECLARE_FUNCTION(execCancelAll); \
	DECLARE_FUNCTION(execLoadImagePixels); \
	DECLARE_FUNCTION(execLoadImageFromBytesSync); \
	DECLARE_FUNCTION(execLoadImageSync); \
	DECLARE_FUNCTION(execLoadHDRIAsCubemapAsync); \
	DECLARE_FUNCTION(execLoadImageFromBytesAsync); \
	DECLARE_FUNCTION(execLoadImageAsync);


#define HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h_50_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetThisPluginResourcesDirectory); \
	DECLARE_FUNCTION(execFindImagesInDirectory); \
	DECLARE_FUNCTION(execLoadFileToByteArray); \
	DECLARE_FUNCTION(execCancelAll); \
	DECLARE_FUNCTION(execLoadImagePixels); \
	DECLARE_FUNCTION(execLoadImageFromBytesSync); \
	DECLARE_FUNCTION(execLoadImageSync); \
	DECLARE_FUNCTION(execLoadHDRIAsCubemapAsync); \
	DECLARE_FUNCTION(execLoadImageFromBytesAsync); \
	DECLARE_FUNCTION(execLoadImageAsync);


#define HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h_50_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesURuntimeImageLoader(); \
	friend struct Z_Construct_UClass_URuntimeImageLoader_Statics; \
public: \
	DECLARE_CLASS(URuntimeImageLoader, UWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/RuntimeImageLoader"), NO_API) \
	DECLARE_SERIALIZER(URuntimeImageLoader)


#define HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h_50_INCLASS \
private: \
	static void StaticRegisterNativesURuntimeImageLoader(); \
	friend struct Z_Construct_UClass_URuntimeImageLoader_Statics; \
public: \
	DECLARE_CLASS(URuntimeImageLoader, UWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/RuntimeImageLoader"), NO_API) \
	DECLARE_SERIALIZER(URuntimeImageLoader)


#define HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h_50_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API URuntimeImageLoader(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(URuntimeImageLoader) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, URuntimeImageLoader); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(URuntimeImageLoader); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API URuntimeImageLoader(URuntimeImageLoader&&); \
	NO_API URuntimeImageLoader(const URuntimeImageLoader&); \
public:


#define HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h_50_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API URuntimeImageLoader() { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API URuntimeImageLoader(URuntimeImageLoader&&); \
	NO_API URuntimeImageLoader(const URuntimeImageLoader&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, URuntimeImageLoader); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(URuntimeImageLoader); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(URuntimeImageLoader)


#define HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h_50_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__ImageReader() { return STRUCT_OFFSET(URuntimeImageLoader, ImageReader); }


#define HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h_47_PROLOG
#define HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h_50_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h_50_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h_50_SPARSE_DATA \
	HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h_50_RPC_WRAPPERS \
	HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h_50_INCLASS \
	HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h_50_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h_50_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h_50_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h_50_SPARSE_DATA \
	HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h_50_RPC_WRAPPERS_NO_PURE_DECLS \
	HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h_50_INCLASS_NO_PURE_DECLS \
	HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h_50_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> RUNTIMEIMAGELOADER_API UClass* StaticClass<class URuntimeImageLoader>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID HostProject_Plugins_RuntimeImageLoader_Source_RuntimeImageLoader_Public_RuntimeImageLoader_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
