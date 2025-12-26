// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LWCExtreme/Public/FHybridTransform.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFHybridTransform() {}
// Cross Module References
	LWCEXTREME_API UScriptStruct* Z_Construct_UScriptStruct_FHybridTransform();
	UPackage* Z_Construct_UPackage__Script_LWCExtreme();
// End Cross Module References
class UScriptStruct* FHybridTransform::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LWCEXTREME_API uint32 Get_Z_Construct_UScriptStruct_FHybridTransform_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FHybridTransform, Z_Construct_UPackage__Script_LWCExtreme(), TEXT("HybridTransform"), sizeof(FHybridTransform), Get_Z_Construct_UScriptStruct_FHybridTransform_Hash());
	}
	return Singleton;
}
template<> LWCEXTREME_API UScriptStruct* StaticStruct<FHybridTransform>()
{
	return FHybridTransform::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FHybridTransform(FHybridTransform::StaticStruct, TEXT("/Script/LWCExtreme"), TEXT("HybridTransform"), false, nullptr, nullptr);
static struct FScriptStruct_LWCExtreme_StaticRegisterNativesFHybridTransform
{
	FScriptStruct_LWCExtreme_StaticRegisterNativesFHybridTransform()
	{
		UScriptStruct::DeferCppStructOps<FHybridTransform>(FName(TEXT("HybridTransform")));
	}
} ScriptStruct_LWCExtreme_StaticRegisterNativesFHybridTransform;
	struct Z_Construct_UScriptStruct_FHybridTransform_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHybridTransform_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/FHybridTransform.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FHybridTransform_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FHybridTransform>();
	}
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FHybridTransform_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LWCExtreme,
		nullptr,
		&NewStructOps,
		"HybridTransform",
		sizeof(FHybridTransform),
		alignof(FHybridTransform),
		nullptr,
		0,
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FHybridTransform_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHybridTransform_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FHybridTransform()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FHybridTransform_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LWCExtreme();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("HybridTransform"), sizeof(FHybridTransform), Get_Z_Construct_UScriptStruct_FHybridTransform_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FHybridTransform_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FHybridTransform_Hash() { return 2298336188U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
