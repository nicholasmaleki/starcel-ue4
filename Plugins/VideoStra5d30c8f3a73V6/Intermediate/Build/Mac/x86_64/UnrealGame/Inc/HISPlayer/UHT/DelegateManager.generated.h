// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "DelegateManager.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class HISPlayerStatus : uint8;
struct FHISTimedMetadata;
#ifdef HISPLAYER_DelegateManager_generated_h
#error "DelegateManager.generated.h already included, missing '#pragma once' in DelegateManager.h"
#endif
#define HISPLAYER_DelegateManager_generated_h

#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_13_DELEGATE \
struct _Script_HISPlayer_eventEventDelegateNoParam_Parms \
{ \
	int32 Index; \
}; \
static inline void FEventDelegateNoParam_DelegateWrapper(const FMulticastScriptDelegate& EventDelegateNoParam, int32 Index) \
{ \
	_Script_HISPlayer_eventEventDelegateNoParam_Parms Parms; \
	Parms.Index=Index; \
	EventDelegateNoParam.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_14_DELEGATE \
struct _Script_HISPlayer_eventEventDelegatePercentage_Parms \
{ \
	float Percentage; \
	int32 Index; \
}; \
static inline void FEventDelegatePercentage_DelegateWrapper(const FMulticastScriptDelegate& EventDelegatePercentage, float Percentage, int32 Index) \
{ \
	_Script_HISPlayer_eventEventDelegatePercentage_Parms Parms; \
	Parms.Percentage=Percentage; \
	Parms.Index=Index; \
	EventDelegatePercentage.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_15_DELEGATE \
struct _Script_HISPlayer_eventEventDelegateStatus_Parms \
{ \
	HISPlayerStatus Status; \
	int32 Index; \
}; \
static inline void FEventDelegateStatus_DelegateWrapper(const FMulticastScriptDelegate& EventDelegateStatus, HISPlayerStatus Status, int32 Index) \
{ \
	_Script_HISPlayer_eventEventDelegateStatus_Parms Parms; \
	Parms.Status=Status; \
	Parms.Index=Index; \
	EventDelegateStatus.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_16_DELEGATE \
struct _Script_HISPlayer_eventEventDelegateResolution_Parms \
{ \
	FIntPoint Resolution; \
	int32 Index; \
}; \
static inline void FEventDelegateResolution_DelegateWrapper(const FMulticastScriptDelegate& EventDelegateResolution, FIntPoint Resolution, int32 Index) \
{ \
	_Script_HISPlayer_eventEventDelegateResolution_Parms Parms; \
	Parms.Resolution=Resolution; \
	Parms.Index=Index; \
	EventDelegateResolution.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_17_DELEGATE \
struct _Script_HISPlayer_eventEventDelegateError_Parms \
{ \
	int32 ErrorCode; \
	int32 Index; \
}; \
static inline void FEventDelegateError_DelegateWrapper(const FMulticastScriptDelegate& EventDelegateError, int32 ErrorCode, int32 Index) \
{ \
	_Script_HISPlayer_eventEventDelegateError_Parms Parms; \
	Parms.ErrorCode=ErrorCode; \
	Parms.Index=Index; \
	EventDelegateError.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_18_DELEGATE \
struct _Script_HISPlayer_eventEventDelegateTimedMetadata_Parms \
{ \
	FHISTimedMetadata TimedMetadata; \
	int32 Index; \
}; \
static inline void FEventDelegateTimedMetadata_DelegateWrapper(const FMulticastScriptDelegate& EventDelegateTimedMetadata, FHISTimedMetadata TimedMetadata, int32 Index) \
{ \
	_Script_HISPlayer_eventEventDelegateTimedMetadata_Parms Parms; \
	Parms.TimedMetadata=TimedMetadata; \
	Parms.Index=Index; \
	EventDelegateTimedMetadata.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_19_DELEGATE \
struct _Script_HISPlayer_eventEventDelegatePCMData_Parms \
{ \
	TArray<float> PCMData; \
	int32 timestamp; \
	int32 Index; \
}; \
static inline void FEventDelegatePCMData_DelegateWrapper(const FMulticastScriptDelegate& EventDelegatePCMData, TArray<float> const& PCMData, int32 timestamp, int32 Index) \
{ \
	_Script_HISPlayer_eventEventDelegatePCMData_Parms Parms; \
	Parms.PCMData=PCMData; \
	Parms.timestamp=timestamp; \
	Parms.Index=Index; \
	EventDelegatePCMData.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_23_SPARSE_DATA
#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_23_RPC_WRAPPERS
#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_23_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_23_ACCESSORS
#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_23_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUDelegateManager(); \
	friend struct Z_Construct_UClass_UDelegateManager_Statics; \
public: \
	DECLARE_CLASS(UDelegateManager, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/HISPlayer"), NO_API) \
	DECLARE_SERIALIZER(UDelegateManager)


#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_23_INCLASS \
private: \
	static void StaticRegisterNativesUDelegateManager(); \
	friend struct Z_Construct_UClass_UDelegateManager_Statics; \
public: \
	DECLARE_CLASS(UDelegateManager, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/HISPlayer"), NO_API) \
	DECLARE_SERIALIZER(UDelegateManager)


#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_23_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UDelegateManager(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UDelegateManager) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UDelegateManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDelegateManager); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UDelegateManager(UDelegateManager&&); \
	NO_API UDelegateManager(const UDelegateManager&); \
public:


#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_23_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UDelegateManager(UDelegateManager&&); \
	NO_API UDelegateManager(const UDelegateManager&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UDelegateManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDelegateManager); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UDelegateManager)


#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_21_PROLOG
#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_23_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_23_SPARSE_DATA \
	FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_23_RPC_WRAPPERS \
	FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_23_ACCESSORS \
	FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_23_INCLASS \
	FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_23_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_23_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_23_SPARSE_DATA \
	FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_23_ACCESSORS \
	FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_23_INCLASS_NO_PURE_DECLS \
	FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h_23_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> HISPLAYER_API UClass* StaticClass<class UDelegateManager>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_DelegateManager_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
