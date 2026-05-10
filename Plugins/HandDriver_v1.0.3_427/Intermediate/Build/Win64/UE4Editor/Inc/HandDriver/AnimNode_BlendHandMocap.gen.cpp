// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HandDriver/Public/AnimNode_BlendHandMocap.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAnimNode_BlendHandMocap() {}
// Cross Module References
	HANDDRIVER_API UScriptStruct* Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap();
	UPackage* Z_Construct_UPackage__Script_HandDriver();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FAnimNode_Base();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FPoseLink();
// End Cross Module References

static_assert(std::is_polymorphic<FAnimNode_BlendHandMocap>() == std::is_polymorphic<FAnimNode_Base>(), "USTRUCT FAnimNode_BlendHandMocap cannot be polymorphic unless super FAnimNode_Base is polymorphic");

class UScriptStruct* FAnimNode_BlendHandMocap::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern HANDDRIVER_API uint32 Get_Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap, Z_Construct_UPackage__Script_HandDriver(), TEXT("AnimNode_BlendHandMocap"), sizeof(FAnimNode_BlendHandMocap), Get_Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Hash());
	}
	return Singleton;
}
template<> HANDDRIVER_API UScriptStruct* StaticStruct<FAnimNode_BlendHandMocap>()
{
	return FAnimNode_BlendHandMocap::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAnimNode_BlendHandMocap(FAnimNode_BlendHandMocap::StaticStruct, TEXT("/Script/HandDriver"), TEXT("AnimNode_BlendHandMocap"), false, nullptr, nullptr);
static struct FScriptStruct_HandDriver_StaticRegisterNativesFAnimNode_BlendHandMocap
{
	FScriptStruct_HandDriver_StaticRegisterNativesFAnimNode_BlendHandMocap()
	{
		UScriptStruct::DeferCppStructOps<FAnimNode_BlendHandMocap>(FName(TEXT("AnimNode_BlendHandMocap")));
	}
} ScriptStruct_HandDriver_StaticRegisterNativesFAnimNode_BlendHandMocap;
	struct Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Hand_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Hand;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MoCap_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MoCap;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/AnimNode_BlendHandMocap.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAnimNode_BlendHandMocap>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Statics::NewProp_Hand_MetaData[] = {
		{ "Category", "Links" },
		{ "ModuleRelativePath", "Public/AnimNode_BlendHandMocap.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Statics::NewProp_Hand = { "Hand", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAnimNode_BlendHandMocap, Hand), Z_Construct_UScriptStruct_FPoseLink, METADATA_PARAMS(Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Statics::NewProp_Hand_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Statics::NewProp_Hand_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Statics::NewProp_MoCap_MetaData[] = {
		{ "Category", "Links" },
		{ "ModuleRelativePath", "Public/AnimNode_BlendHandMocap.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Statics::NewProp_MoCap = { "MoCap", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAnimNode_BlendHandMocap, MoCap), Z_Construct_UScriptStruct_FPoseLink, METADATA_PARAMS(Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Statics::NewProp_MoCap_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Statics::NewProp_MoCap_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Statics::NewProp_Hand,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Statics::NewProp_MoCap,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_HandDriver,
		Z_Construct_UScriptStruct_FAnimNode_Base,
		&NewStructOps,
		"AnimNode_BlendHandMocap",
		sizeof(FAnimNode_BlendHandMocap),
		alignof(FAnimNode_BlendHandMocap),
		Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_HandDriver();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AnimNode_BlendHandMocap"), sizeof(FAnimNode_BlendHandMocap), Get_Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAnimNode_BlendHandMocap_Hash() { return 266603247U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
