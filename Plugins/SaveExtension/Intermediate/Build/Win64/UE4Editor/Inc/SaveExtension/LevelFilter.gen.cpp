// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SaveExtension/Public/LevelFilter.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLevelFilter() {}
// Cross Module References
	SAVEEXTENSION_API UScriptStruct* Z_Construct_UScriptStruct_FSELevelFilter();
	UPackage* Z_Construct_UPackage__Script_SaveExtension();
	SAVEEXTENSION_API UScriptStruct* Z_Construct_UScriptStruct_FSEActorClassFilter();
	SAVEEXTENSION_API UScriptStruct* Z_Construct_UScriptStruct_FSEComponentClassFilter();
// End Cross Module References
class UScriptStruct* FSELevelFilter::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern SAVEEXTENSION_API uint32 Get_Z_Construct_UScriptStruct_FSELevelFilter_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FSELevelFilter, Z_Construct_UPackage__Script_SaveExtension(), TEXT("SELevelFilter"), sizeof(FSELevelFilter), Get_Z_Construct_UScriptStruct_FSELevelFilter_Hash());
	}
	return Singleton;
}
template<> SAVEEXTENSION_API UScriptStruct* StaticStruct<FSELevelFilter>()
{
	return FSELevelFilter::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FSELevelFilter(FSELevelFilter::StaticStruct, TEXT("/Script/SaveExtension"), TEXT("SELevelFilter"), false, nullptr, nullptr);
static struct FScriptStruct_SaveExtension_StaticRegisterNativesFSELevelFilter
{
	FScriptStruct_SaveExtension_StaticRegisterNativesFSELevelFilter()
	{
		UScriptStruct::DeferCppStructOps<FSELevelFilter>(FName(TEXT("SELevelFilter")));
	}
} ScriptStruct_SaveExtension_StaticRegisterNativesFSELevelFilter;
	struct Z_Construct_UScriptStruct_FSELevelFilter_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ActorFilter_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ActorFilter;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LoadActorFilter_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_LoadActorFilter;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bStoreComponents_MetaData[];
#endif
		static void NewProp_bStoreComponents_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bStoreComponents;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ComponentFilter_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ComponentFilter;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LoadComponentFilter_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_LoadComponentFilter;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSELevelFilter_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Contains all settings that affect saving.\n * This information is saved to be restored while loading.\n */" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/LevelFilter.h" },
		{ "ToolTip", "Contains all settings that affect saving.\nThis information is saved to be restored while loading." },
	};
#endif
	void* Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSELevelFilter>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_ActorFilter_MetaData[] = {
		{ "ModuleRelativePath", "Public/LevelFilter.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_ActorFilter = { "ActorFilter", nullptr, (EPropertyFlags)0x0010000001000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSELevelFilter, ActorFilter), Z_Construct_UScriptStruct_FSEActorClassFilter, METADATA_PARAMS(Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_ActorFilter_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_ActorFilter_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_LoadActorFilter_MetaData[] = {
		{ "ModuleRelativePath", "Public/LevelFilter.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_LoadActorFilter = { "LoadActorFilter", nullptr, (EPropertyFlags)0x0010000001000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSELevelFilter, LoadActorFilter), Z_Construct_UScriptStruct_FSEActorClassFilter, METADATA_PARAMS(Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_LoadActorFilter_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_LoadActorFilter_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_bStoreComponents_MetaData[] = {
		{ "ModuleRelativePath", "Public/LevelFilter.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_bStoreComponents_SetBit(void* Obj)
	{
		((FSELevelFilter*)Obj)->bStoreComponents = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_bStoreComponents = { "bStoreComponents", nullptr, (EPropertyFlags)0x0010000001000000, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FSELevelFilter), &Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_bStoreComponents_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_bStoreComponents_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_bStoreComponents_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_ComponentFilter_MetaData[] = {
		{ "ModuleRelativePath", "Public/LevelFilter.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_ComponentFilter = { "ComponentFilter", nullptr, (EPropertyFlags)0x0010000001000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSELevelFilter, ComponentFilter), Z_Construct_UScriptStruct_FSEComponentClassFilter, METADATA_PARAMS(Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_ComponentFilter_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_ComponentFilter_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_LoadComponentFilter_MetaData[] = {
		{ "ModuleRelativePath", "Public/LevelFilter.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_LoadComponentFilter = { "LoadComponentFilter", nullptr, (EPropertyFlags)0x0010000001000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSELevelFilter, LoadComponentFilter), Z_Construct_UScriptStruct_FSEComponentClassFilter, METADATA_PARAMS(Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_LoadComponentFilter_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_LoadComponentFilter_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FSELevelFilter_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_ActorFilter,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_LoadActorFilter,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_bStoreComponents,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_ComponentFilter,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSELevelFilter_Statics::NewProp_LoadComponentFilter,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FSELevelFilter_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_SaveExtension,
		nullptr,
		&NewStructOps,
		"SELevelFilter",
		sizeof(FSELevelFilter),
		alignof(FSELevelFilter),
		Z_Construct_UScriptStruct_FSELevelFilter_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSELevelFilter_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FSELevelFilter_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSELevelFilter_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FSELevelFilter()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FSELevelFilter_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_SaveExtension();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("SELevelFilter"), sizeof(FSELevelFilter), Get_Z_Construct_UScriptStruct_FSELevelFilter_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FSELevelFilter_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FSELevelFilter_Hash() { return 2916391128U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
