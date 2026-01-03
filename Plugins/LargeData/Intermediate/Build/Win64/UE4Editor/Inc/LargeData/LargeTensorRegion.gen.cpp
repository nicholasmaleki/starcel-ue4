// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LargeData/Public/LargeTensorRegion.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLargeTensorRegion() {}
// Cross Module References
	LARGEDATA_API UScriptStruct* Z_Construct_UScriptStruct_FLargeTensorRegionUpdate();
	UPackage* Z_Construct_UPackage__Script_LargeData();
// End Cross Module References
class UScriptStruct* FLargeTensorRegionUpdate::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LARGEDATA_API uint32 Get_Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLargeTensorRegionUpdate, Z_Construct_UPackage__Script_LargeData(), TEXT("LargeTensorRegionUpdate"), sizeof(FLargeTensorRegionUpdate), Get_Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Hash());
	}
	return Singleton;
}
template<> LARGEDATA_API UScriptStruct* StaticStruct<FLargeTensorRegionUpdate>()
{
	return FLargeTensorRegionUpdate::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLargeTensorRegionUpdate(FLargeTensorRegionUpdate::StaticStruct, TEXT("/Script/LargeData"), TEXT("LargeTensorRegionUpdate"), false, nullptr, nullptr);
static struct FScriptStruct_LargeData_StaticRegisterNativesFLargeTensorRegionUpdate
{
	FScriptStruct_LargeData_StaticRegisterNativesFLargeTensorRegionUpdate()
	{
		UScriptStruct::DeferCppStructOps<FLargeTensorRegionUpdate>(FName(TEXT("LargeTensorRegionUpdate")));
	}
} ScriptStruct_LargeData_StaticRegisterNativesFLargeTensorRegionUpdate;
	struct Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FInt64PropertyParams NewProp_Start_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Start_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Start;
		static const UE4CodeGen_Private::FInt64PropertyParams NewProp_Extent_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Extent_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Extent;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_RawData_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RawData_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_RawData;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Hash_MetaData[];
#endif
		static const UE4CodeGen_Private::FUInt32PropertyParams NewProp_Hash;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LargeTensorRegion.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLargeTensorRegionUpdate>();
	}
	const UE4CodeGen_Private::FInt64PropertyParams Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_Start_Inner = { "Start", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int64, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_Start_MetaData[] = {
		{ "ModuleRelativePath", "Public/LargeTensorRegion.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_Start = { "Start", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLargeTensorRegionUpdate, Start), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_Start_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_Start_MetaData)) };
	const UE4CodeGen_Private::FInt64PropertyParams Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_Extent_Inner = { "Extent", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int64, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_Extent_MetaData[] = {
		{ "ModuleRelativePath", "Public/LargeTensorRegion.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_Extent = { "Extent", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLargeTensorRegionUpdate, Extent), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_Extent_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_Extent_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_RawData_Inner = { "RawData", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_RawData_MetaData[] = {
		{ "ModuleRelativePath", "Public/LargeTensorRegion.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_RawData = { "RawData", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLargeTensorRegionUpdate, RawData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_RawData_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_RawData_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_Hash_MetaData[] = {
		{ "ModuleRelativePath", "Public/LargeTensorRegion.h" },
	};
#endif
	const UE4CodeGen_Private::FUInt32PropertyParams Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_Hash = { "Hash", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::UInt32, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLargeTensorRegionUpdate, Hash), METADATA_PARAMS(Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_Hash_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_Hash_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_Start_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_Start,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_Extent_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_Extent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_RawData_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_RawData,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::NewProp_Hash,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LargeData,
		nullptr,
		&NewStructOps,
		"LargeTensorRegionUpdate",
		sizeof(FLargeTensorRegionUpdate),
		alignof(FLargeTensorRegionUpdate),
		Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLargeTensorRegionUpdate()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LargeData();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LargeTensorRegionUpdate"), sizeof(FLargeTensorRegionUpdate), Get_Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLargeTensorRegionUpdate_Hash() { return 384295183U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
