// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HISPlayer/Public/HISPlayerTypes/HISPlayerTrack.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHISPlayerTrack() {}
// Cross Module References
	HISPLAYER_API UScriptStruct* Z_Construct_UScriptStruct_FHISPlayerTrack();
	UPackage* Z_Construct_UPackage__Script_HISPlayer();
// End Cross Module References
class UScriptStruct* FHISPlayerTrack::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern HISPLAYER_API uint32 Get_Z_Construct_UScriptStruct_FHISPlayerTrack_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FHISPlayerTrack, Z_Construct_UPackage__Script_HISPlayer(), TEXT("HISPlayerTrack"), sizeof(FHISPlayerTrack), Get_Z_Construct_UScriptStruct_FHISPlayerTrack_Hash());
	}
	return Singleton;
}
template<> HISPLAYER_API UScriptStruct* StaticStruct<FHISPlayerTrack>()
{
	return FHISPlayerTrack::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FHISPlayerTrack(FHISPlayerTrack::StaticStruct, TEXT("/Script/HISPlayer"), TEXT("HISPlayerTrack"), false, nullptr, nullptr);
static struct FScriptStruct_HISPlayer_StaticRegisterNativesFHISPlayerTrack
{
	FScriptStruct_HISPlayer_StaticRegisterNativesFHISPlayerTrack()
	{
		UScriptStruct::DeferCppStructOps<FHISPlayerTrack>(FName(TEXT("HISPlayerTrack")));
	}
} ScriptStruct_HISPlayer_StaticRegisterNativesFHISPlayerTrack;
	struct Z_Construct_UScriptStruct_FHISPlayerTrack_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_id_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_id;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bitrate_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_bitrate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_width_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_width;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_height_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_height;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_framerate_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_framerate;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Category", "HISPlayer|Track" },
		{ "DisplayName", "HISPlayer Track" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerTrack.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FHISPlayerTrack>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_id_MetaData[] = {
		{ "Category", "SpawnParams" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerTrack.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FHISPlayerTrack, id), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_id_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_id_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_bitrate_MetaData[] = {
		{ "Category", "SpawnParams" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerTrack.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_bitrate = { "bitrate", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FHISPlayerTrack, bitrate), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_bitrate_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_bitrate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_width_MetaData[] = {
		{ "Category", "SpawnParams" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerTrack.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_width = { "width", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FHISPlayerTrack, width), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_width_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_width_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_height_MetaData[] = {
		{ "Category", "SpawnParams" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerTrack.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_height = { "height", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FHISPlayerTrack, height), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_height_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_height_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_framerate_MetaData[] = {
		{ "Category", "SpawnParams" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerTrack.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_framerate = { "framerate", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FHISPlayerTrack, framerate), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_framerate_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_framerate_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_id,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_bitrate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_width,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_height,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::NewProp_framerate,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_HISPlayer,
		nullptr,
		&NewStructOps,
		"HISPlayerTrack",
		sizeof(FHISPlayerTrack),
		alignof(FHISPlayerTrack),
		Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FHISPlayerTrack()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FHISPlayerTrack_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_HISPlayer();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("HISPlayerTrack"), sizeof(FHISPlayerTrack), Get_Z_Construct_UScriptStruct_FHISPlayerTrack_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FHISPlayerTrack_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FHISPlayerTrack_Hash() { return 1271781788U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
