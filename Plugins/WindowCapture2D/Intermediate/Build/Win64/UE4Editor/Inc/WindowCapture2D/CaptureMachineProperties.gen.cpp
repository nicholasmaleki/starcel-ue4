// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "WindowCapture2D/Public/CaptureMachineProperties.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCaptureMachineProperties() {}
// Cross Module References
	WINDOWCAPTURE2D_API UEnum* Z_Construct_UEnum_WindowCapture2D_ETitleMatchingWindowSearch();
	UPackage* Z_Construct_UPackage__Script_WindowCapture2D();
	WINDOWCAPTURE2D_API UScriptStruct* Z_Construct_UScriptStruct_FCaptureMachineProperties();
// End Cross Module References
	static UEnum* ETitleMatchingWindowSearch_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_WindowCapture2D_ETitleMatchingWindowSearch, Z_Construct_UPackage__Script_WindowCapture2D(), TEXT("ETitleMatchingWindowSearch"));
		}
		return Singleton;
	}
	template<> WINDOWCAPTURE2D_API UEnum* StaticEnum<ETitleMatchingWindowSearch>()
	{
		return ETitleMatchingWindowSearch_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ETitleMatchingWindowSearch(ETitleMatchingWindowSearch_StaticEnum, TEXT("/Script/WindowCapture2D"), TEXT("ETitleMatchingWindowSearch"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_WindowCapture2D_ETitleMatchingWindowSearch_Hash() { return 3317078671U; }
	UEnum* Z_Construct_UEnum_WindowCapture2D_ETitleMatchingWindowSearch()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_WindowCapture2D();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ETitleMatchingWindowSearch"), 0, Get_Z_Construct_UEnum_WindowCapture2D_ETitleMatchingWindowSearch_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ETitleMatchingWindowSearch::PerfectMatch", (int64)ETitleMatchingWindowSearch::PerfectMatch },
				{ "ETitleMatchingWindowSearch::ForwardMatch", (int64)ETitleMatchingWindowSearch::ForwardMatch },
				{ "ETitleMatchingWindowSearch::PartialMatch", (int64)ETitleMatchingWindowSearch::PartialMatch },
				{ "ETitleMatchingWindowSearch::BackwardMatch", (int64)ETitleMatchingWindowSearch::BackwardMatch },
				{ "ETitleMatchingWindowSearch::RegularExpression", (int64)ETitleMatchingWindowSearch::RegularExpression },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BackwardMatch.Name", "ETitleMatchingWindowSearch::BackwardMatch" },
				{ "BlueprintType", "true" },
				{ "ForwardMatch.Name", "ETitleMatchingWindowSearch::ForwardMatch" },
				{ "ModuleRelativePath", "Public/CaptureMachineProperties.h" },
				{ "PartialMatch.Name", "ETitleMatchingWindowSearch::PartialMatch" },
				{ "PerfectMatch.Name", "ETitleMatchingWindowSearch::PerfectMatch" },
				{ "RegularExpression.Name", "ETitleMatchingWindowSearch::RegularExpression" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_WindowCapture2D,
				nullptr,
				"ETitleMatchingWindowSearch",
				"ETitleMatchingWindowSearch",
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
class UScriptStruct* FCaptureMachineProperties::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern WINDOWCAPTURE2D_API uint32 Get_Z_Construct_UScriptStruct_FCaptureMachineProperties_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FCaptureMachineProperties, Z_Construct_UPackage__Script_WindowCapture2D(), TEXT("CaptureMachineProperties"), sizeof(FCaptureMachineProperties), Get_Z_Construct_UScriptStruct_FCaptureMachineProperties_Hash());
	}
	return Singleton;
}
template<> WINDOWCAPTURE2D_API UScriptStruct* StaticStruct<FCaptureMachineProperties>()
{
	return FCaptureMachineProperties::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FCaptureMachineProperties(FCaptureMachineProperties::StaticStruct, TEXT("/Script/WindowCapture2D"), TEXT("CaptureMachineProperties"), false, nullptr, nullptr);
static struct FScriptStruct_WindowCapture2D_StaticRegisterNativesFCaptureMachineProperties
{
	FScriptStruct_WindowCapture2D_StaticRegisterNativesFCaptureMachineProperties()
	{
		UScriptStruct::DeferCppStructOps<FCaptureMachineProperties>(FName(TEXT("CaptureMachineProperties")));
	}
} ScriptStruct_WindowCapture2D_StaticRegisterNativesFCaptureMachineProperties;
	struct Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CaptureTargetTitle_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_CaptureTargetTitle;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_TitleMatchingWindowSearch_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TitleMatchingWindowSearch_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_TitleMatchingWindowSearch;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FrameRate_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_FrameRate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CheckWindowSize_MetaData[];
#endif
		static void NewProp_CheckWindowSize_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_CheckWindowSize;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CutShadow_MetaData[];
#endif
		static void NewProp_CutShadow_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_CutShadow;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/CaptureMachineProperties.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FCaptureMachineProperties>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CaptureTargetTitle_MetaData[] = {
		{ "Category", "WindowCapture2D" },
		{ "ModuleRelativePath", "Public/CaptureMachineProperties.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CaptureTargetTitle = { "CaptureTargetTitle", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCaptureMachineProperties, CaptureTargetTitle), METADATA_PARAMS(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CaptureTargetTitle_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CaptureTargetTitle_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_TitleMatchingWindowSearch_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_TitleMatchingWindowSearch_MetaData[] = {
		{ "Category", "WindowCapture2D" },
		{ "ModuleRelativePath", "Public/CaptureMachineProperties.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_TitleMatchingWindowSearch = { "TitleMatchingWindowSearch", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCaptureMachineProperties, TitleMatchingWindowSearch), Z_Construct_UEnum_WindowCapture2D_ETitleMatchingWindowSearch, METADATA_PARAMS(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_TitleMatchingWindowSearch_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_TitleMatchingWindowSearch_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_FrameRate_MetaData[] = {
		{ "Category", "WindowCapture2D" },
		{ "ModuleRelativePath", "Public/CaptureMachineProperties.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_FrameRate = { "FrameRate", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCaptureMachineProperties, FrameRate), METADATA_PARAMS(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_FrameRate_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_FrameRate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CheckWindowSize_MetaData[] = {
		{ "Category", "WindowCapture2D" },
		{ "ModuleRelativePath", "Public/CaptureMachineProperties.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CheckWindowSize_SetBit(void* Obj)
	{
		((FCaptureMachineProperties*)Obj)->CheckWindowSize = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CheckWindowSize = { "CheckWindowSize", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FCaptureMachineProperties), &Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CheckWindowSize_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CheckWindowSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CheckWindowSize_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CutShadow_MetaData[] = {
		{ "Category", "WindowCapture2D" },
		{ "ModuleRelativePath", "Public/CaptureMachineProperties.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CutShadow_SetBit(void* Obj)
	{
		((FCaptureMachineProperties*)Obj)->CutShadow = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CutShadow = { "CutShadow", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FCaptureMachineProperties), &Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CutShadow_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CutShadow_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CutShadow_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CaptureTargetTitle,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_TitleMatchingWindowSearch_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_TitleMatchingWindowSearch,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_FrameRate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CheckWindowSize,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::NewProp_CutShadow,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::ReturnStructParams = {
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
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FCaptureMachineProperties_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_WindowCapture2D();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("CaptureMachineProperties"), sizeof(FCaptureMachineProperties), Get_Z_Construct_UScriptStruct_FCaptureMachineProperties_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FCaptureMachineProperties_Hash() { return 953817136U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
