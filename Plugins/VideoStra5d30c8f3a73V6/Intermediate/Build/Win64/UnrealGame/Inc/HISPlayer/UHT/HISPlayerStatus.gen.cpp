// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HISPlayer/Public/HISPlayerTypes/HISPlayerStatus.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHISPlayerStatus() {}
// Cross Module References
	HISPLAYER_API UEnum* Z_Construct_UEnum_HISPlayer_HISPlayerStatus();
	UPackage* Z_Construct_UPackage__Script_HISPlayer();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_HISPlayerStatus;
	static UEnum* HISPlayerStatus_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_HISPlayerStatus.OuterSingleton)
		{
			Z_Registration_Info_UEnum_HISPlayerStatus.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_HISPlayer_HISPlayerStatus, Z_Construct_UPackage__Script_HISPlayer(), TEXT("HISPlayerStatus"));
		}
		return Z_Registration_Info_UEnum_HISPlayerStatus.OuterSingleton;
	}
	template<> HISPLAYER_API UEnum* StaticEnum<HISPlayerStatus>()
	{
		return HISPlayerStatus_StaticEnum();
	}
	struct Z_Construct_UEnum_HISPlayer_HISPlayerStatus_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_HISPlayer_HISPlayerStatus_Statics::Enumerators[] = {
		{ "HISPlayerStatus::NONE", (int64)HISPlayerStatus::NONE },
		{ "HISPlayerStatus::CLOSE", (int64)HISPlayerStatus::CLOSE },
		{ "HISPlayerStatus::STOP", (int64)HISPlayerStatus::STOP },
		{ "HISPlayerStatus::PLAY", (int64)HISPlayerStatus::PLAY },
		{ "HISPlayerStatus::PAUSE", (int64)HISPlayerStatus::PAUSE },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_HISPlayer_HISPlayerStatus_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Category", "HISPlayer|Types" },
		{ "CLOSE.DisplayName", "Close" },
		{ "CLOSE.Name", "HISPlayerStatus::CLOSE" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerStatus.h" },
		{ "NONE.DisplayName", "None" },
		{ "NONE.Name", "HISPlayerStatus::NONE" },
		{ "PAUSE.DisplayName", "Pause" },
		{ "PAUSE.Name", "HISPlayerStatus::PAUSE" },
		{ "PLAY.DisplayName", "Play" },
		{ "PLAY.Name", "HISPlayerStatus::PLAY" },
		{ "STOP.DisplayName", "Stop" },
		{ "STOP.Name", "HISPlayerStatus::STOP" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_HISPlayer_HISPlayerStatus_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_HISPlayer,
		nullptr,
		"HISPlayerStatus",
		"HISPlayerStatus",
		Z_Construct_UEnum_HISPlayer_HISPlayerStatus_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_HISPlayer_HISPlayerStatus_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_HISPlayer_HISPlayerStatus_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_HISPlayer_HISPlayerStatus_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_HISPlayer_HISPlayerStatus()
	{
		if (!Z_Registration_Info_UEnum_HISPlayerStatus.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_HISPlayerStatus.InnerSingleton, Z_Construct_UEnum_HISPlayer_HISPlayerStatus_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_HISPlayerStatus.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerStatus_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerStatus_h_Statics::EnumInfo[] = {
		{ HISPlayerStatus_StaticEnum, TEXT("HISPlayerStatus"), &Z_Registration_Info_UEnum_HISPlayerStatus, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2313975536U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerStatus_h_3872949798(TEXT("/Script/HISPlayer"),
		nullptr, 0,
		nullptr, 0,
		Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerStatus_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerStatus_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
