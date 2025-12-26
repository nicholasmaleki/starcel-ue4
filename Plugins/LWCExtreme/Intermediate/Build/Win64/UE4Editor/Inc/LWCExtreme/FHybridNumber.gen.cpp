// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LWCExtreme/Public/FHybridNumber.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFHybridNumber() {}
// Cross Module References
	LWCEXTREME_API UScriptStruct* Z_Construct_UScriptStruct_FHybridNumber();
	UPackage* Z_Construct_UPackage__Script_LWCExtreme();
// End Cross Module References
class UScriptStruct* FHybridNumber::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LWCEXTREME_API uint32 Get_Z_Construct_UScriptStruct_FHybridNumber_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FHybridNumber, Z_Construct_UPackage__Script_LWCExtreme(), TEXT("HybridNumber"), sizeof(FHybridNumber), Get_Z_Construct_UScriptStruct_FHybridNumber_Hash());
	}
	return Singleton;
}
template<> LWCEXTREME_API UScriptStruct* StaticStruct<FHybridNumber>()
{
	return FHybridNumber::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FHybridNumber(FHybridNumber::StaticStruct, TEXT("/Script/LWCExtreme"), TEXT("HybridNumber"), false, nullptr, nullptr);
static struct FScriptStruct_LWCExtreme_StaticRegisterNativesFHybridNumber
{
	FScriptStruct_LWCExtreme_StaticRegisterNativesFHybridNumber()
	{
		UScriptStruct::DeferCppStructOps<FHybridNumber>(FName(TEXT("HybridNumber")));
	}
} ScriptStruct_LWCExtreme_StaticRegisterNativesFHybridNumber;
	struct Z_Construct_UScriptStruct_FHybridNumber_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHybridNumber_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "// dynamic precision\n" },
		{ "ModuleRelativePath", "Public/FHybridNumber.h" },
		{ "ToolTip", "dynamic precision" },
	};
#endif
	void* Z_Construct_UScriptStruct_FHybridNumber_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FHybridNumber>();
	}
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FHybridNumber_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LWCExtreme,
		nullptr,
		&NewStructOps,
		"HybridNumber",
		sizeof(FHybridNumber),
		alignof(FHybridNumber),
		nullptr,
		0,
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FHybridNumber_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHybridNumber_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FHybridNumber()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FHybridNumber_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LWCExtreme();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("HybridNumber"), sizeof(FHybridNumber), Get_Z_Construct_UScriptStruct_FHybridNumber_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FHybridNumber_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FHybridNumber_Hash() { return 716260418U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
