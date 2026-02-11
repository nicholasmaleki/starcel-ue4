// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HISPlayer/Public/HISPlayerTypes/HISPlayerStatus.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHISPlayerStatus() {}
// Cross Module References
	HISPLAYER_API UEnum* Z_Construct_UEnum_HISPlayer_HISPlayerStatus();
	UPackage* Z_Construct_UPackage__Script_HISPlayer();
// End Cross Module References
	static UEnum* HISPlayerStatus_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_HISPlayer_HISPlayerStatus, Z_Construct_UPackage__Script_HISPlayer(), TEXT("HISPlayerStatus"));
		}
		return Singleton;
	}
	template<> HISPLAYER_API UEnum* StaticEnum<HISPlayerStatus>()
	{
		return HISPlayerStatus_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_HISPlayerStatus(HISPlayerStatus_StaticEnum, TEXT("/Script/HISPlayer"), TEXT("HISPlayerStatus"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_HISPlayer_HISPlayerStatus_Hash() { return 611147368U; }
	UEnum* Z_Construct_UEnum_HISPlayer_HISPlayerStatus()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_HISPlayer();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("HISPlayerStatus"), 0, Get_Z_Construct_UEnum_HISPlayer_HISPlayerStatus_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "HISPlayerStatus::NONE", (int64)HISPlayerStatus::NONE },
				{ "HISPlayerStatus::CLOSE", (int64)HISPlayerStatus::CLOSE },
				{ "HISPlayerStatus::STOP", (int64)HISPlayerStatus::STOP },
				{ "HISPlayerStatus::PLAY", (int64)HISPlayerStatus::PLAY },
				{ "HISPlayerStatus::PAUSE", (int64)HISPlayerStatus::PAUSE },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
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
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_HISPlayer,
				nullptr,
				"HISPlayerStatus",
				"HISPlayerStatus",
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
