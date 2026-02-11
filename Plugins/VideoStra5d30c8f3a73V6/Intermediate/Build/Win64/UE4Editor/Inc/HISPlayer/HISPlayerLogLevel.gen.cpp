// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HISPlayer/Public/HISPlayerTypes/HISPlayerLogLevel.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHISPlayerLogLevel() {}
// Cross Module References
	HISPLAYER_API UEnum* Z_Construct_UEnum_HISPlayer_HISPlayerLogLevel();
	UPackage* Z_Construct_UPackage__Script_HISPlayer();
// End Cross Module References
	static UEnum* HISPlayerLogLevel_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_HISPlayer_HISPlayerLogLevel, Z_Construct_UPackage__Script_HISPlayer(), TEXT("HISPlayerLogLevel"));
		}
		return Singleton;
	}
	template<> HISPLAYER_API UEnum* StaticEnum<HISPlayerLogLevel>()
	{
		return HISPlayerLogLevel_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_HISPlayerLogLevel(HISPlayerLogLevel_StaticEnum, TEXT("/Script/HISPlayer"), TEXT("HISPlayerLogLevel"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_HISPlayer_HISPlayerLogLevel_Hash() { return 2773225252U; }
	UEnum* Z_Construct_UEnum_HISPlayer_HISPlayerLogLevel()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_HISPlayer();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("HISPlayerLogLevel"), 0, Get_Z_Construct_UEnum_HISPlayer_HISPlayerLogLevel_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "HISPlayerLogLevel::DEBUG", (int64)HISPlayerLogLevel::DEBUG },
				{ "HISPlayerLogLevel::INFO", (int64)HISPlayerLogLevel::INFO },
				{ "HISPlayerLogLevel::WARNING", (int64)HISPlayerLogLevel::WARNING },
				{ "HISPlayerLogLevel::ERROR", (int64)HISPlayerLogLevel::ERROR },
				{ "HISPlayerLogLevel::NONE", (int64)HISPlayerLogLevel::NONE },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
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
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_HISPlayer,
				nullptr,
				"HISPlayerLogLevel",
				"HISPlayerLogLevel",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
