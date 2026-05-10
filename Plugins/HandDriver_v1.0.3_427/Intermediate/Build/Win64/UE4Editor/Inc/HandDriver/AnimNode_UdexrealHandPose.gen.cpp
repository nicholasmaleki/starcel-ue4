// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HandDriver/Public/AnimNode_UdexrealHandPose.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAnimNode_UdexrealHandPose() {}
// Cross Module References
	HANDDRIVER_API UScriptStruct* Z_Construct_UScriptStruct_FAnimNode_UdexrealHandPose();
	UPackage* Z_Construct_UPackage__Script_HandDriver();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FAnimNode_Base();
// End Cross Module References

static_assert(std::is_polymorphic<FAnimNode_UdexrealHandPose>() == std::is_polymorphic<FAnimNode_Base>(), "USTRUCT FAnimNode_UdexrealHandPose cannot be polymorphic unless super FAnimNode_Base is polymorphic");

class UScriptStruct* FAnimNode_UdexrealHandPose::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern HANDDRIVER_API uint32 Get_Z_Construct_UScriptStruct_FAnimNode_UdexrealHandPose_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAnimNode_UdexrealHandPose, Z_Construct_UPackage__Script_HandDriver(), TEXT("AnimNode_UdexrealHandPose"), sizeof(FAnimNode_UdexrealHandPose), Get_Z_Construct_UScriptStruct_FAnimNode_UdexrealHandPose_Hash());
	}
	return Singleton;
}
template<> HANDDRIVER_API UScriptStruct* StaticStruct<FAnimNode_UdexrealHandPose>()
{
	return FAnimNode_UdexrealHandPose::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAnimNode_UdexrealHandPose(FAnimNode_UdexrealHandPose::StaticStruct, TEXT("/Script/HandDriver"), TEXT("AnimNode_UdexrealHandPose"), false, nullptr, nullptr);
static struct FScriptStruct_HandDriver_StaticRegisterNativesFAnimNode_UdexrealHandPose
{
	FScriptStruct_HandDriver_StaticRegisterNativesFAnimNode_UdexrealHandPose()
	{
		UScriptStruct::DeferCppStructOps<FAnimNode_UdexrealHandPose>(FName(TEXT("AnimNode_UdexrealHandPose")));
	}
} ScriptStruct_HandDriver_StaticRegisterNativesFAnimNode_UdexrealHandPose;
	struct Z_Construct_UScriptStruct_FAnimNode_UdexrealHandPose_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAnimNode_UdexrealHandPose_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/AnimNode_UdexrealHandPose.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAnimNode_UdexrealHandPose_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAnimNode_UdexrealHandPose>();
	}
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAnimNode_UdexrealHandPose_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_HandDriver,
		Z_Construct_UScriptStruct_FAnimNode_Base,
		&NewStructOps,
		"AnimNode_UdexrealHandPose",
		sizeof(FAnimNode_UdexrealHandPose),
		alignof(FAnimNode_UdexrealHandPose),
		nullptr,
		0,
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAnimNode_UdexrealHandPose_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_UdexrealHandPose_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAnimNode_UdexrealHandPose()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAnimNode_UdexrealHandPose_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_HandDriver();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AnimNode_UdexrealHandPose"), sizeof(FAnimNode_UdexrealHandPose), Get_Z_Construct_UScriptStruct_FAnimNode_UdexrealHandPose_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAnimNode_UdexrealHandPose_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAnimNode_UdexrealHandPose_Hash() { return 3147751662U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
