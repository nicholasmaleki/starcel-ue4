// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HISPlayer/Public/HISPlayerTypes/HISPlayerTrack.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHISPlayerTrack() {}
// Cross Module References
	HISPLAYER_API UScriptStruct* Z_Construct_UScriptStruct_FHISPlayerTrack();
	UPackage* Z_Construct_UPackage__Script_HISPlayer();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_HISPlayerTrack;
class UScriptStruct* FHISPlayerTrack::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_HISPlayerTrack.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_HISPlayerTrack.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FHISPlayerTrack, Z_Construct_UPackage__Script_HISPlayer(), TEXT("HISPlayerTrack"));
	}
	return Z_Registration_Info_UScriptStruct_HISPlayerTrack.OuterSingleton;
}
template<> HISPLAYER_API UScriptStruct* StaticStruct<FHISPlayerTrack>()
{
	return FHISPlayerTrack::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FHISPlayerTrack_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_id_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_id;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bitrate_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_bitrate;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_width_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_width;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_height_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_height;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_framerate_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_framerate;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Category", "HISPlayer|Track" },
		{ "DisplayName", "HISPlayer Track" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerTrack.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FHISPlayerTrack>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_id_MetaData[] = {
		{ "Category", "SpawnParams" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerTrack.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FHISPlayerTrack, id), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_id_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_id_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_bitrate_MetaData[] = {
		{ "Category", "SpawnParams" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerTrack.h" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_bitrate = { "bitrate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FHISPlayerTrack, bitrate), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_bitrate_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_bitrate_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_width_MetaData[] = {
		{ "Category", "SpawnParams" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerTrack.h" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_width = { "width", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FHISPlayerTrack, width), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_width_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_width_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_height_MetaData[] = {
		{ "Category", "SpawnParams" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerTrack.h" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_height = { "height", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FHISPlayerTrack, height), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_height_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_height_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_framerate_MetaData[] = {
		{ "Category", "SpawnParams" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerTrack.h" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_framerate = { "framerate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FHISPlayerTrack, framerate), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_framerate_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_framerate_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_id,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_bitrate,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_width,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_height,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_framerate,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_HISPlayer,
		nullptr,
		&NewStructOps,
		"HISPlayerTrack",
		sizeof(FHISPlayerTrack),
		alignof(FHISPlayerTrack),
		Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FHISPlayerTrack()
	{
		if (!Z_Registration_Info_UScriptStruct_HISPlayerTrack.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_HISPlayerTrack.InnerSingleton, Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_HISPlayerTrack.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerTrack_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerTrack_h_Statics::ScriptStructInfo[] = {
		{ FHISPlayerTrack::StaticStruct, Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewStructOps, TEXT("HISPlayerTrack"), &Z_Registration_Info_UScriptStruct_HISPlayerTrack, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FHISPlayerTrack), 2705976217U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerTrack_h_2768892281(TEXT("/Script/HISPlayer"),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerTrack_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerTrack_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
