// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FHISPlayerTrack;
struct FHISPlayerPlaybackProperties;
class UDelegateManager;
enum class HISPlayerStatus : uint8;
struct FIntPoint;
class UTexture2D;
class UObject;
struct FLatentActionInfo;
#ifdef HISPLAYER_HISPlayerFunctions_generated_h
#error "HISPlayerFunctions.generated.h already included, missing '#pragma once' in HISPlayerFunctions.h"
#endif
#define HISPLAYER_HISPlayerFunctions_generated_h

#define Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h_17_SPARSE_DATA
#define Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h_17_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execChangeVideoContent); \
	DECLARE_FUNCTION(execSelectTrack); \
	DECLARE_FUNCTION(execGetTrackID); \
	DECLARE_FUNCTION(execGetTrackHeight); \
	DECLARE_FUNCTION(execGetTrackWidth); \
	DECLARE_FUNCTION(execGetTrackFramerate); \
	DECLARE_FUNCTION(execGetTrackBitrate); \
	DECLARE_FUNCTION(execGetTracks); \
	DECLARE_FUNCTION(execGetTrackCount); \
	DECLARE_FUNCTION(execGetVideoWidth); \
	DECLARE_FUNCTION(execGetVideoHeight); \
	DECLARE_FUNCTION(execSetPlaybackProperties); \
	DECLARE_FUNCTION(execGetDelegateManager); \
	DECLARE_FUNCTION(execGetPlayerStatus); \
	DECLARE_FUNCTION(execClose); \
	DECLARE_FUNCTION(execGetTotalTime); \
	DECLARE_FUNCTION(execGetCurrentPosition); \
	DECLARE_FUNCTION(execSetMute); \
	DECLARE_FUNCTION(execGetPlaybackRate); \
	DECLARE_FUNCTION(execSetPlaybackRate); \
	DECLARE_FUNCTION(execSetVolume); \
	DECLARE_FUNCTION(execSeek); \
	DECLARE_FUNCTION(execStop); \
	DECLARE_FUNCTION(execPause); \
	DECLARE_FUNCTION(execResume); \
	DECLARE_FUNCTION(execUpdate); \
	DECLARE_FUNCTION(execOpenPlayer); \
	DECLARE_FUNCTION(execCreateNewTexture); \
	DECLARE_FUNCTION(execSetup); \
	DECLARE_FUNCTION(execBeginPlay);


#define Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execChangeVideoContent); \
	DECLARE_FUNCTION(execSelectTrack); \
	DECLARE_FUNCTION(execGetTrackID); \
	DECLARE_FUNCTION(execGetTrackHeight); \
	DECLARE_FUNCTION(execGetTrackWidth); \
	DECLARE_FUNCTION(execGetTrackFramerate); \
	DECLARE_FUNCTION(execGetTrackBitrate); \
	DECLARE_FUNCTION(execGetTracks); \
	DECLARE_FUNCTION(execGetTrackCount); \
	DECLARE_FUNCTION(execGetVideoWidth); \
	DECLARE_FUNCTION(execGetVideoHeight); \
	DECLARE_FUNCTION(execSetPlaybackProperties); \
	DECLARE_FUNCTION(execGetDelegateManager); \
	DECLARE_FUNCTION(execGetPlayerStatus); \
	DECLARE_FUNCTION(execClose); \
	DECLARE_FUNCTION(execGetTotalTime); \
	DECLARE_FUNCTION(execGetCurrentPosition); \
	DECLARE_FUNCTION(execSetMute); \
	DECLARE_FUNCTION(execGetPlaybackRate); \
	DECLARE_FUNCTION(execSetPlaybackRate); \
	DECLARE_FUNCTION(execSetVolume); \
	DECLARE_FUNCTION(execSeek); \
	DECLARE_FUNCTION(execStop); \
	DECLARE_FUNCTION(execPause); \
	DECLARE_FUNCTION(execResume); \
	DECLARE_FUNCTION(execUpdate); \
	DECLARE_FUNCTION(execOpenPlayer); \
	DECLARE_FUNCTION(execCreateNewTexture); \
	DECLARE_FUNCTION(execSetup); \
	DECLARE_FUNCTION(execBeginPlay);


#define Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUHISPlayerFunctions(); \
	friend struct Z_Construct_UClass_UHISPlayerFunctions_Statics; \
public: \
	DECLARE_CLASS(UHISPlayerFunctions, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/HISPlayer"), NO_API) \
	DECLARE_SERIALIZER(UHISPlayerFunctions)


#define Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h_17_INCLASS \
private: \
	static void StaticRegisterNativesUHISPlayerFunctions(); \
	friend struct Z_Construct_UClass_UHISPlayerFunctions_Statics; \
public: \
	DECLARE_CLASS(UHISPlayerFunctions, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/HISPlayer"), NO_API) \
	DECLARE_SERIALIZER(UHISPlayerFunctions)


#define Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h_17_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UHISPlayerFunctions(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UHISPlayerFunctions) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UHISPlayerFunctions); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UHISPlayerFunctions); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UHISPlayerFunctions(UHISPlayerFunctions&&); \
	NO_API UHISPlayerFunctions(const UHISPlayerFunctions&); \
public:


#define Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h_17_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UHISPlayerFunctions(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UHISPlayerFunctions(UHISPlayerFunctions&&); \
	NO_API UHISPlayerFunctions(const UHISPlayerFunctions&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UHISPlayerFunctions); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UHISPlayerFunctions); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UHISPlayerFunctions)


#define Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h_17_PRIVATE_PROPERTY_OFFSET
#define Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h_15_PROLOG
#define Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h_17_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h_17_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h_17_SPARSE_DATA \
	Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h_17_RPC_WRAPPERS \
	Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h_17_INCLASS \
	Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h_17_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h_17_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h_17_SPARSE_DATA \
	Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h_17_INCLASS_NO_PURE_DECLS \
	Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> HISPLAYER_API UClass* StaticClass<class UHISPlayerFunctions>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Starcel9_Plugins_VideoStra5d30c8f3a73V6_Source_HISPlayer_Public_HISPlayerFunctions_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
