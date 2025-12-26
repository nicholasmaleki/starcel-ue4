// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LWCExtreme/Public/FHybridQuaternion.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFHybridQuaternion() {}
// Cross Module References
	LWCEXTREME_API UScriptStruct* Z_Construct_UScriptStruct_FHybridQuaternion();
	UPackage* Z_Construct_UPackage__Script_LWCExtreme();
// End Cross Module References
class UScriptStruct* FHybridQuaternion::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LWCEXTREME_API uint32 Get_Z_Construct_UScriptStruct_FHybridQuaternion_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FHybridQuaternion, Z_Construct_UPackage__Script_LWCExtreme(), TEXT("HybridQuaternion"), sizeof(FHybridQuaternion), Get_Z_Construct_UScriptStruct_FHybridQuaternion_Hash());
	}
	return Singleton;
}
template<> LWCEXTREME_API UScriptStruct* StaticStruct<FHybridQuaternion>()
{
	return FHybridQuaternion::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FHybridQuaternion(FHybridQuaternion::StaticStruct, TEXT("/Script/LWCExtreme"), TEXT("HybridQuaternion"), false, nullptr, nullptr);
static struct FScriptStruct_LWCExtreme_StaticRegisterNativesFHybridQuaternion
{
	FScriptStruct_LWCExtreme_StaticRegisterNativesFHybridQuaternion()
	{
		UScriptStruct::DeferCppStructOps<FHybridQuaternion>(FName(TEXT("HybridQuaternion")));
	}
} ScriptStruct_LWCExtreme_StaticRegisterNativesFHybridQuaternion;
	struct Z_Construct_UScriptStruct_FHybridQuaternion_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHybridQuaternion_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/FHybridQuaternion.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FHybridQuaternion_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FHybridQuaternion>();
	}
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FHybridQuaternion_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LWCExtreme,
		nullptr,
		&NewStructOps,
		"HybridQuaternion",
		sizeof(FHybridQuaternion),
		alignof(FHybridQuaternion),
		nullptr,
		0,
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FHybridQuaternion_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHybridQuaternion_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FHybridQuaternion()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FHybridQuaternion_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LWCExtreme();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("HybridQuaternion"), sizeof(FHybridQuaternion), Get_Z_Construct_UScriptStruct_FHybridQuaternion_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FHybridQuaternion_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FHybridQuaternion_Hash() { return 2515437181U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
