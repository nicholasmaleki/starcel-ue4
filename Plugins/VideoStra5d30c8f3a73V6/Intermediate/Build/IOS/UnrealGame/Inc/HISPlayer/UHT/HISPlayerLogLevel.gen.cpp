// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HISPlayer/Public/HISPlayerTypes/HISPlayerLogLevel.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHISPlayerLogLevel() {}
// Cross Module References
	HISPLAYER_API UEnum* Z_Construct_UEnum_HISPlayer_HISPlayerLogLevel();
	UPackage* Z_Construct_UPackage__Script_HISPlayer();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_HISPlayerLogLevel;
	static UEnum* HISPlayerLogLevel_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_HISPlayerLogLevel.OuterSingleton)
		{
			Z_Registration_Info_UEnum_HISPlayerLogLevel.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_HISPlayer_HISPlayerLogLevel, Z_Construct_UPackage__Script_HISPlayer(), TEXT("HISPlayerLogLevel"));
		}
		return Z_Registration_Info_UEnum_HISPlayerLogLevel.OuterSingleton;
	}
	template<> HISPLAYER_API UEnum* StaticEnum<HISPlayerLogLevel>()
	{
		return HISPlayerLogLevel_StaticEnum();
	}
	struct Z_Construct_UEnum_HISPlayer_HISPlayerLogLevel_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_HISPlayer_HISPlayerLogLevel_Statics::Enumerators[] = {
		{ "HISPlayerLogLevel::DEBUG", (int64)HISPlayerLogLevel::DEBUG },
		{ "HISPlayerLogLevel::INFO", (int64)HISPlayerLogLevel::INFO },
		{ "HISPlayerLogLevel::WARNING", (int64)HISPlayerLogLevel::WARNING },
		{ "HISPlayerLogLevel::ERROR", (int64)HISPlayerLogLevel::ERROR },
		{ "HISPlayerLogLevel::NONE", (int64)HISPlayerLogLevel::NONE },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_HISPlayer_HISPlayerLogLevel_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Category", "HISPlayer|Types" },
		{ "DEBUG.DisplayName", "DEBUG" },
		{ "DEBUG.Name", "HISPlayerLogLevel::DEBUG" },
		{ "ERROR.Comment", "// Indicates potential issues or situations that may require attention\n" },
		{ "ERROR.DisplayName", "ERROR" },
		{ "ERROR.Name", "HISPlayerLogLevel::ERROR" },
		{ "ERROR.ToolTip", "Indicates potential issues or situations that may require attention" },
		{ "INFO.Comment", "// Logs messages useful for debugging and troubleshooting purposes\n" },
		{ "INFO.DisplayName", "INFO" },
		{ "INFO.Name", "HISPlayerLogLevel::INFO" },
		{ "INFO.ToolTip", "Logs messages useful for debugging and troubleshooting purposes" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerLogLevel.h" },
		{ "NONE.Comment", "// Indicates critical errors that may prevent the application from functioning correctly\n" },
		{ "NONE.DisplayName", "NONE" },
		{ "NONE.Name", "HISPlayerLogLevel::NONE" },
		{ "NONE.ToolTip", "Indicates critical errors that may prevent the application from functioning correctly" },
		{ "WARNING.Comment", "// Provides general informational messages about the application's execution\n" },
		{ "WARNING.DisplayName", "WARNING" },
		{ "WARNING.Name", "HISPlayerLogLevel::WARNING" },
		{ "WARNING.ToolTip", "Provides general informational messages about the application's execution" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_HISPlayer_HISPlayerLogLevel_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_HISPlayer,
		nullptr,
		"HISPlayerLogLevel",
		"HISPlayerLogLevel",
		Z_Construct_UEnum_HISPlayer_HISPlayerLogLevel_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_HISPlayer_HISPlayerLogLevel_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_HISPlayer_HISPlayerLogLevel_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_HISPlayer_HISPlayerLogLevel_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_HISPlayer_HISPlayerLogLevel()
	{
		if (!Z_Registration_Info_UEnum_HISPlayerLogLevel.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_HISPlayerLogLevel.InnerSingleton, Z_Construct_UEnum_HISPlayer_HISPlayerLogLevel_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_HISPlayerLogLevel.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerLogLevel_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerLogLevel_h_Statics::EnumInfo[] = {
		{ HISPlayerLogLevel_StaticEnum, TEXT("HISPlayerLogLevel"), &Z_Registration_Info_UEnum_HISPlayerLogLevel, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3103664291U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerLogLevel_h_594709671(TEXT("/Script/HISPlayer"),
		nullptr, 0,
		nullptr, 0,
		Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerLogLevel_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerLogLevel_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
