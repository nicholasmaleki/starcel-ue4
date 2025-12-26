// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LWCExtreme/Public/FLargeString.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFLargeString() {}
// Cross Module References
	LWCEXTREME_API UScriptStruct* Z_Construct_UScriptStruct_FLargeString();
	UPackage* Z_Construct_UPackage__Script_LWCExtreme();
// End Cross Module References
class UScriptStruct* FLargeString::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LWCEXTREME_API uint32 Get_Z_Construct_UScriptStruct_FLargeString_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLargeString, Z_Construct_UPackage__Script_LWCExtreme(), TEXT("LargeString"), sizeof(FLargeString), Get_Z_Construct_UScriptStruct_FLargeString_Hash());
	}
	return Singleton;
}
template<> LWCEXTREME_API UScriptStruct* StaticStruct<FLargeString>()
{
	return FLargeString::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLargeString(FLargeString::StaticStruct, TEXT("/Script/LWCExtreme"), TEXT("LargeString"), false, nullptr, nullptr);
static struct FScriptStruct_LWCExtreme_StaticRegisterNativesFLargeString
{
	FScriptStruct_LWCExtreme_StaticRegisterNativesFLargeString()
	{
		UScriptStruct::DeferCppStructOps<FLargeString>(FName(TEXT("LargeString")));
	}
} ScriptStruct_LWCExtreme_StaticRegisterNativesFLargeString;
	struct Z_Construct_UScriptStruct_FLargeString_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLargeString_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/FLargeString.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLargeString_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLargeString>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLargeString_Statics::NewProp_Value_MetaData[] = {
		{ "Category", "LWCExtreme|LargeString" },
		{ "ModuleRelativePath", "Public/FLargeString.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLargeString_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLargeString, Value), METADATA_PARAMS(Z_Construct_UScriptStruct_FLargeString_Statics::NewProp_Value_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLargeString_Statics::NewProp_Value_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLargeString_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLargeString_Statics::NewProp_Value,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLargeString_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LWCExtreme,
		nullptr,
		&NewStructOps,
		"LargeString",
		sizeof(FLargeString),
		alignof(FLargeString),
		Z_Construct_UScriptStruct_FLargeString_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLargeString_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLargeString_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLargeString_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLargeString()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLargeString_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LWCExtreme();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LargeString"), sizeof(FLargeString), Get_Z_Construct_UScriptStruct_FLargeString_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLargeString_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLargeString_Hash() { return 1385410747U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
