// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "WindowCapture2D/Public/CaptureMachineProperties.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCaptureMachineProperties() {}
// Cross Module References
	UPackage* Z_Construct_UPackage__Script_WindowCapture2D();
	WINDOWCAPTURE2D_API UEnum* Z_Construct_UEnum_WindowCapture2D_ETitleMatchingWindowSearch();
	WINDOWCAPTURE2D_API UScriptStruct* Z_Construct_UScriptStruct_FCaptureMachineProperties();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_ETitleMatchingWindowSearch;
	static UEnum* ETitleMatchingWindowSearch_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_ETitleMatchingWindowSearch.OuterSingleton)
		{
			Z_Registration_Info_UEnum_ETitleMatchingWindowSearch.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_WindowCapture2D_ETitleMatchingWindowSearch, Z_Construct_UPackage__Script_WindowCapture2D(), TEXT("ETitleMatchingWindowSearch"));
		}
		return Z_Registration_Info_UEnum_ETitleMatchingWindowSearch.OuterSingleton;
	}
	template<> WINDOWCAPTURE2D_API UEnum* StaticEnum<ETitleMatchingWindowSearch>()
	{
		return ETitleMatchingWindowSearch_StaticEnum();
	}
	struct Z_Construct_UEnum_WindowCapture2D_ETitleMatchingWindowSearch_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_WindowCapture2D_ETitleMatchingWindowSearch_Statics::Enumerators[] = {
		{ "ETitleMatchingWindowSearch::PerfectMatch", (int64)ETitleMatchingWindowSearch::PerfectMatch },
		{ "ETitleMatchingWindowSearch::ForwardMatch", (int64)ETitleMatchingWindowSearch::ForwardMatch },
		{ "ETitleMatchingWindowSearch::PartialMatch", (int64)ETitleMatchingWindowSearch::PartialMatch },
		{ "ETitleMatchingWindowSearch::BackwardMatch", (int64)ETitleMatchingWindowSearch::BackwardMatch },
		{ "ETitleMatchingWindowSearch::RegularExpression", (int64)ETitleMatchingWindowSearch::RegularExpression },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_WindowCapture2D_ETitleMatchingWindowSearch_Statics::Enum_MetaDataParams[] = {
		{ "BackwardMatch.Name", "ETitleMatchingWindowSearch::BackwardMatch" },
		{ "BlueprintType", "true" },
		{ "ForwardMatch.Name", "ETitleMatchingWindowSearch::ForwardMatch" },
		{ "ModuleRelativePath", "Public/CaptureMachineProperties.h" },
		{ "PartialMatch.Name", "ETitleMatchingWindowSearch::PartialMatch" },
		{ "PerfectMatch.Name", "ETitleMatchingWindowSearch::PerfectMatch" },
		{ "RegularExpression.Name", "ETitleMatchingWindowSearch::RegularExpression" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_WindowCapture2D_ETitleMatchingWindowSearch_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_WindowCapture2D,
		nullptr,
		"ETitleMatchingWindowSearch",
		"ETitleMatchingWindowSearch",
		Z_Construct_UEnum_WindowCapture2D_ETitleMatchingWindowSearch_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_WindowCapture2D_ETitleMatchingWindowSearch_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_WindowCapture2D_ETitleMatchingWindowSearch_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_WindowCapture2D_ETitleMatchingWindowSearch_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_WindowCapture2D_ETitleMatchingWindowSearch()
	{
		if (!Z_Registration_Info_UEnum_ETitleMatchingWindowSearch.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ETitleMatchingWindowSearch.InnerSingleton, Z_Construct_UEnum_WindowCapture2D_ETitleMatchingWindowSearch_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_ETitleMatchingWindowSearch.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_CaptureMachineProperties;
class UScriptStruct* FCaptureMachineProperties::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_CaptureMachineProperties.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_CaptureMachineProperties.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FCaptureMachineProperties, Z_Construct_UPackage__Script_WindowCapture2D(), TEXT("CaptureMachineProperties"));
	}
	return Z_Registration_Info_UScriptStruct_CaptureMachineProperties.OuterSingleton;
}
template<> WINDOWCAPTURE2D_API UScriptStruct* StaticStruct<FCaptureMachineProperties>()
{
	return FCaptureMachineProperties::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CaptureTargetTitle_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_CaptureTargetTitle;
		static const UECodeGen_Private::FBytePropertyParams NewProp_TitleMatchingWindowSearch_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TitleMatchingWindowSearch_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_TitleMatchingWindowSearch;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FrameRate_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_FrameRate;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CheckWindowSize_MetaData[];
#endif
		static void NewProp_CheckWindowSize_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_CheckWindowSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CutShadow_MetaData[];
#endif
		static void NewProp_CutShadow_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_CutShadow;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/CaptureMachineProperties.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FCaptureMachineProperties>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CaptureTargetTitle_MetaData[] = {
		{ "Category", "WindowCapture2D" },
		{ "ModuleRelativePath", "Public/CaptureMachineProperties.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CaptureTargetTitle = { "CaptureTargetTitle", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FCaptureMachineProperties, CaptureTargetTitle), METADATA_PARAMS(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CaptureTargetTitle_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CaptureTargetTitle_MetaData)) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_TitleMatchingWindowSearch_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_TitleMatchingWindowSearch_MetaData[] = {
		{ "Category", "WindowCapture2D" },
		{ "ModuleRelativePath", "Public/CaptureMachineProperties.h" },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_TitleMatchingWindowSearch = { "TitleMatchingWindowSearch", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FCaptureMachineProperties, TitleMatchingWindowSearch), Z_Construct_UEnum_WindowCapture2D_ETitleMatchingWindowSearch, METADATA_PARAMS(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_TitleMatchingWindowSearch_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_TitleMatchingWindowSearch_MetaData)) }; // 2824474358
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_FrameRate_MetaData[] = {
		{ "Category", "WindowCapture2D" },
		{ "ModuleRelativePath", "Public/CaptureMachineProperties.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_FrameRate = { "FrameRate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FCaptureMachineProperties, FrameRate), METADATA_PARAMS(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_FrameRate_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_FrameRate_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CheckWindowSize_MetaData[] = {
		{ "Category", "WindowCapture2D" },
		{ "ModuleRelativePath", "Public/CaptureMachineProperties.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CheckWindowSize_SetBit(void* Obj)
	{
		((FCaptureMachineProperties*)Obj)->CheckWindowSize = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CheckWindowSize = { "CheckWindowSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(FCaptureMachineProperties), &Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CheckWindowSize_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CheckWindowSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CheckWindowSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CutShadow_MetaData[] = {
		{ "Category", "WindowCapture2D" },
		{ "ModuleRelativePath", "Public/CaptureMachineProperties.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CutShadow_SetBit(void* Obj)
	{
		((FCaptureMachineProperties*)Obj)->CutShadow = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CutShadow = { "CutShadow", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(FCaptureMachineProperties), &Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CutShadow_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CutShadow_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CutShadow_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CaptureTargetTitle,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_TitleMatchingWindowSearch_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_TitleMatchingWindowSearch,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_FrameRate,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CheckWindowSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CutShadow,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_WindowCapture2D,
		nullptr,
		&NewStructOps,
		"CaptureMachineProperties",
		sizeof(FCaptureMachineProperties),
		alignof(FCaptureMachineProperties),
		Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FCaptureMachineProperties()
	{
		if (!Z_Registration_Info_UScriptStruct_CaptureMachineProperties.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_CaptureMachineProperties.InnerSingleton, Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_CaptureMachineProperties.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachineProperties_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachineProperties_h_Statics::EnumInfo[] = {
		{ ETitleMatchingWindowSearch_StaticEnum, TEXT("ETitleMatchingWindowSearch"), &Z_Registration_Info_UEnum_ETitleMatchingWindowSearch, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2824474358U) },
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachineProperties_h_Statics::ScriptStructInfo[] = {
		{ FCaptureMachineProperties::StaticStruct, Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewStructOps, TEXT("CaptureMachineProperties"), &Z_Registration_Info_UScriptStruct_CaptureMachineProperties, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FCaptureMachineProperties), 1111378952U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachineProperties_h_3754058874(TEXT("/Script/WindowCapture2D"),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachineProperties_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachineProperties_h_Statics::ScriptStructInfo),
		Z_CompiledInDeferFile_FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachineProperties_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachineProperties_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
