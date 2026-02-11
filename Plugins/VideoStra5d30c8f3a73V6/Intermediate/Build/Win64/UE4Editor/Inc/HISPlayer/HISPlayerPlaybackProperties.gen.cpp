// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HISPlayer/Public/HISPlayerTypes/HISPlayerPlaybackProperties.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHISPlayerPlaybackProperties() {}
// Cross Module References
	HISPLAYER_API UScriptStruct* Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties();
	UPackage* Z_Construct_UPackage__Script_HISPlayer();
// End Cross Module References
class UScriptStruct* FHISPlayerPlaybackProperties::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern HISPLAYER_API uint32 Get_Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties, Z_Construct_UPackage__Script_HISPlayer(), TEXT("HISPlayerPlaybackProperties"), sizeof(FHISPlayerPlaybackProperties), Get_Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Hash());
	}
	return Singleton;
}
template<> HISPLAYER_API UScriptStruct* StaticStruct<FHISPlayerPlaybackProperties>()
{
	return FHISPlayerPlaybackProperties::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FHISPlayerPlaybackProperties(FHISPlayerPlaybackProperties::StaticStruct, TEXT("/Script/HISPlayer"), TEXT("HISPlayerPlaybackProperties"), false, nullptr, nullptr);
static struct FScriptStruct_HISPlayer_StaticRegisterNativesFHISPlayerPlaybackProperties
{
	FScriptStruct_HISPlayer_StaticRegisterNativesFHISPlayerPlaybackProperties()
	{
		UScriptStruct::DeferCppStructOps<FHISPlayerPlaybackProperties>(FName(TEXT("HISPlayerPlaybackProperties")));
	}
} ScriptStruct_HISPlayer_StaticRegisterNativesFHISPlayerPlaybackProperties;
	struct Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bAutoplay_MetaData[];
#endif
		static void NewProp_bAutoplay_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bAutoplay;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bLooping_MetaData[];
#endif
		static void NewProp_bLooping_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bLooping;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bMute_MetaData[];
#endif
		static void NewProp_bMute_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bMute;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Category", "HISPlayer|Types" },
		{ "DisplayName", "HISPlayer Playback Properties" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerPlaybackProperties.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FHISPlayerPlaybackProperties>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bAutoplay_MetaData[] = {
		{ "Category", "SpawnParams" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerPlaybackProperties.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bAutoplay_SetBit(void* Obj)
	{
		((FHISPlayerPlaybackProperties*)Obj)->bAutoplay = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bAutoplay = { "bAutoplay", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FHISPlayerPlaybackProperties), &Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bAutoplay_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bAutoplay_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bAutoplay_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bLooping_MetaData[] = {
		{ "Category", "SpawnParams" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerPlaybackProperties.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bLooping_SetBit(void* Obj)
	{
		((FHISPlayerPlaybackProperties*)Obj)->bLooping = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bLooping = { "bLooping", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FHISPlayerPlaybackProperties), &Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bLooping_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bLooping_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bLooping_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bMute_MetaData[] = {
		{ "Category", "SpawnParams" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerPlaybackProperties.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bMute_SetBit(void* Obj)
	{
		((FHISPlayerPlaybackProperties*)Obj)->bMute = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bMute = { "bMute", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FHISPlayerPlaybackProperties), &Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bMute_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bMute_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bMute_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bAutoplay,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bLooping,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::NewProp_bMute,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_HISPlayer,
		nullptr,
		&NewStructOps,
		"HISPlayerPlaybackProperties",
		sizeof(FHISPlayerPlaybackProperties),
		alignof(FHISPlayerPlaybackProperties),
		Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_HISPlayer();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("HISPlayerPlaybackProperties"), sizeof(FHISPlayerPlaybackProperties), Get_Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties_Hash() { return 2468224674U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
