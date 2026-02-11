// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HISPlayer/Public/HISPlayerTypes/HISPlayerPlaybackProperties.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHISPlayerPlaybackProperties() {}
// Cross Module References
	HISPLAYER_API UScriptStruct* Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties();
	UPackage* Z_Construct_UPackage__Script_HISPlayer();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_HISPlayerPlaybackProperties;
class UScriptStruct* FHISPlayerPlaybackProperties::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_HISPlayerPlaybackProperties.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_HISPlayerPlaybackProperties.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties, Z_Construct_UPackage__Script_HISPlayer(), TEXT("HISPlayerPlaybackProperties"));
	}
	return Z_Registration_Info_UScriptStruct_HISPlayerPlaybackProperties.OuterSingleton;
}
template<> HISPLAYER_API UScriptStruct* StaticStruct<FHISPlayerPlaybackProperties>()
{
	return FHISPlayerPlaybackProperties::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bAutoplay_MetaData[];
#endif
		static void NewProp_bAutoplay_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bAutoplay;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bLooping_MetaData[];
#endif
		static void NewProp_bLooping_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bLooping;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bMute_MetaData[];
#endif
		static void NewProp_bMute_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bMute;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Category", "HISPlayer|Types" },
		{ "DisplayName", "HISPlayer Playback Properties" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerPlaybackProperties.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FHISPlayerPlaybackProperties>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bAutoplay_MetaData[] = {
		{ "Category", "SpawnParams" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerPlaybackProperties.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bAutoplay_SetBit(void* Obj)
	{
		((FHISPlayerPlaybackProperties*)Obj)->bAutoplay = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bAutoplay = { "bAutoplay", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(FHISPlayerPlaybackProperties), &Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bAutoplay_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bAutoplay_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bAutoplay_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bLooping_MetaData[] = {
		{ "Category", "SpawnParams" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerPlaybackProperties.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bLooping_SetBit(void* Obj)
	{
		((FHISPlayerPlaybackProperties*)Obj)->bLooping = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bLooping = { "bLooping", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(FHISPlayerPlaybackProperties), &Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bLooping_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bLooping_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bLooping_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bMute_MetaData[] = {
		{ "Category", "SpawnParams" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerPlaybackProperties.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bMute_SetBit(void* Obj)
	{
		((FHISPlayerPlaybackProperties*)Obj)->bMute = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bMute = { "bMute", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(FHISPlayerPlaybackProperties), &Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bMute_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bMute_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bMute_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bAutoplay,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bLooping,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bMute,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_HISPlayer,
		nullptr,
		&NewStructOps,
		"HISPlayerPlaybackProperties",
		sizeof(FHISPlayerPlaybackProperties),
		alignof(FHISPlayerPlaybackProperties),
		Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties()
	{
		if (!Z_Registration_Info_UScriptStruct_HISPlayerPlaybackProperties.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_HISPlayerPlaybackProperties.InnerSingleton, Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_HISPlayerPlaybackProperties.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerPlaybackProperties_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerPlaybackProperties_h_Statics::ScriptStructInfo[] = {
		{ FHISPlayerPlaybackProperties::StaticStruct, Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewStructOps, TEXT("HISPlayerPlaybackProperties"), &Z_Registration_Info_UScriptStruct_HISPlayerPlaybackProperties, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FHISPlayerPlaybackProperties), 116301691U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerPlaybackProperties_h_1552950590(TEXT("/Script/HISPlayer"),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerPlaybackProperties_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerPlaybackProperties_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
