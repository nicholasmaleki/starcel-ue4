// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LargeData/Public/LargeDataObject.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLargeDataObject() {}
// Cross Module References
	LARGEDATA_API UScriptStruct* Z_Construct_UScriptStruct_FLargeChunkArray();
	UPackage* Z_Construct_UPackage__Script_LargeData();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FFastArraySerializer();
	LARGEDATA_API UScriptStruct* Z_Construct_UScriptStruct_FLargeDataChunk();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FFastArraySerializerItem();
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeDataObject_NoRegister();
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeDataObject();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
// End Cross Module References

static_assert(std::is_polymorphic<FLargeChunkArray>() == std::is_polymorphic<FFastArraySerializer>(), "USTRUCT FLargeChunkArray cannot be polymorphic unless super FFastArraySerializer is polymorphic");

class UScriptStruct* FLargeChunkArray::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LARGEDATA_API uint32 Get_Z_Construct_UScriptStruct_FLargeChunkArray_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLargeChunkArray, Z_Construct_UPackage__Script_LargeData(), TEXT("LargeChunkArray"), sizeof(FLargeChunkArray), Get_Z_Construct_UScriptStruct_FLargeChunkArray_Hash());
	}
	return Singleton;
}
template<> LARGEDATA_API UScriptStruct* StaticStruct<FLargeChunkArray>()
{
	return FLargeChunkArray::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLargeChunkArray(FLargeChunkArray::StaticStruct, TEXT("/Script/LargeData"), TEXT("LargeChunkArray"), false, nullptr, nullptr);
static struct FScriptStruct_LargeData_StaticRegisterNativesFLargeChunkArray
{
	FScriptStruct_LargeData_StaticRegisterNativesFLargeChunkArray()
	{
		UScriptStruct::DeferCppStructOps<FLargeChunkArray>(FName(TEXT("LargeChunkArray")));
	}
} ScriptStruct_LargeData_StaticRegisterNativesFLargeChunkArray;
	struct Z_Construct_UScriptStruct_FLargeChunkArray_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Chunks_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Chunks_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Chunks;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLargeChunkArray_Statics::Struct_MetaDataParams[] = {
		{ "Comment", "/** Array of chunks using FastArraySerializer for efficient replication */" },
		{ "ModuleRelativePath", "Public/LargeDataObject.h" },
		{ "ToolTip", "Array of chunks using FastArraySerializer for efficient replication" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLargeChunkArray_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLargeChunkArray>();
	}
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLargeChunkArray_Statics::NewProp_Chunks_Inner = { "Chunks", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLargeDataChunk, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLargeChunkArray_Statics::NewProp_Chunks_MetaData[] = {
		{ "ModuleRelativePath", "Public/LargeDataObject.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLargeChunkArray_Statics::NewProp_Chunks = { "Chunks", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLargeChunkArray, Chunks), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLargeChunkArray_Statics::NewProp_Chunks_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLargeChunkArray_Statics::NewProp_Chunks_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLargeChunkArray_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLargeChunkArray_Statics::NewProp_Chunks_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLargeChunkArray_Statics::NewProp_Chunks,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLargeChunkArray_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LargeData,
		Z_Construct_UScriptStruct_FFastArraySerializer,
		&NewStructOps,
		"LargeChunkArray",
		sizeof(FLargeChunkArray),
		alignof(FLargeChunkArray),
		Z_Construct_UScriptStruct_FLargeChunkArray_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLargeChunkArray_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLargeChunkArray_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLargeChunkArray_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLargeChunkArray()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLargeChunkArray_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LargeData();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LargeChunkArray"), sizeof(FLargeChunkArray), Get_Z_Construct_UScriptStruct_FLargeChunkArray_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLargeChunkArray_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLargeChunkArray_Hash() { return 2633011270U; }

static_assert(std::is_polymorphic<FLargeDataChunk>() == std::is_polymorphic<FFastArraySerializerItem>(), "USTRUCT FLargeDataChunk cannot be polymorphic unless super FFastArraySerializerItem is polymorphic");

class UScriptStruct* FLargeDataChunk::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LARGEDATA_API uint32 Get_Z_Construct_UScriptStruct_FLargeDataChunk_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLargeDataChunk, Z_Construct_UPackage__Script_LargeData(), TEXT("LargeDataChunk"), sizeof(FLargeDataChunk), Get_Z_Construct_UScriptStruct_FLargeDataChunk_Hash());
	}
	return Singleton;
}
template<> LARGEDATA_API UScriptStruct* StaticStruct<FLargeDataChunk>()
{
	return FLargeDataChunk::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLargeDataChunk(FLargeDataChunk::StaticStruct, TEXT("/Script/LargeData"), TEXT("LargeDataChunk"), false, nullptr, nullptr);
static struct FScriptStruct_LargeData_StaticRegisterNativesFLargeDataChunk
{
	FScriptStruct_LargeData_StaticRegisterNativesFLargeDataChunk()
	{
		UScriptStruct::DeferCppStructOps<FLargeDataChunk>(FName(TEXT("LargeDataChunk")));
	}
} ScriptStruct_LargeData_StaticRegisterNativesFLargeDataChunk;
	struct Z_Construct_UScriptStruct_FLargeDataChunk_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Index_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Index;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Data_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Data_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Data;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Hash_MetaData[];
#endif
		static const UE4CodeGen_Private::FUInt32PropertyParams NewProp_Hash;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLargeDataChunk_Statics::Struct_MetaDataParams[] = {
		{ "Comment", "/** Single chunk of large data, replicated efficiently */" },
		{ "ModuleRelativePath", "Public/LargeDataObject.h" },
		{ "ToolTip", "Single chunk of large data, replicated efficiently" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLargeDataChunk_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLargeDataChunk>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLargeDataChunk_Statics::NewProp_Index_MetaData[] = {
		{ "ModuleRelativePath", "Public/LargeDataObject.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLargeDataChunk_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLargeDataChunk, Index), METADATA_PARAMS(Z_Construct_UScriptStruct_FLargeDataChunk_Statics::NewProp_Index_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLargeDataChunk_Statics::NewProp_Index_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FLargeDataChunk_Statics::NewProp_Data_Inner = { "Data", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLargeDataChunk_Statics::NewProp_Data_MetaData[] = {
		{ "ModuleRelativePath", "Public/LargeDataObject.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLargeDataChunk_Statics::NewProp_Data = { "Data", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLargeDataChunk, Data), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLargeDataChunk_Statics::NewProp_Data_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLargeDataChunk_Statics::NewProp_Data_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLargeDataChunk_Statics::NewProp_Hash_MetaData[] = {
		{ "ModuleRelativePath", "Public/LargeDataObject.h" },
	};
#endif
	const UE4CodeGen_Private::FUInt32PropertyParams Z_Construct_UScriptStruct_FLargeDataChunk_Statics::NewProp_Hash = { "Hash", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::UInt32, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLargeDataChunk, Hash), METADATA_PARAMS(Z_Construct_UScriptStruct_FLargeDataChunk_Statics::NewProp_Hash_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLargeDataChunk_Statics::NewProp_Hash_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLargeDataChunk_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLargeDataChunk_Statics::NewProp_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLargeDataChunk_Statics::NewProp_Data_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLargeDataChunk_Statics::NewProp_Data,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLargeDataChunk_Statics::NewProp_Hash,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLargeDataChunk_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LargeData,
		Z_Construct_UScriptStruct_FFastArraySerializerItem,
		&NewStructOps,
		"LargeDataChunk",
		sizeof(FLargeDataChunk),
		alignof(FLargeDataChunk),
		Z_Construct_UScriptStruct_FLargeDataChunk_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLargeDataChunk_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLargeDataChunk_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLargeDataChunk_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLargeDataChunk()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLargeDataChunk_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LargeData();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LargeDataChunk"), sizeof(FLargeDataChunk), Get_Z_Construct_UScriptStruct_FLargeDataChunk_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLargeDataChunk_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLargeDataChunk_Hash() { return 1498156929U; }
	DEFINE_FUNCTION(ULargeDataObject::execOnRep_ReplicatedChunks)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnRep_ReplicatedChunks();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULargeDataObject::execApplyChunks)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ApplyChunks();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULargeDataObject::execBuildChunks)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->BuildChunks();
		P_NATIVE_END;
	}
	void ULargeDataObject::StaticRegisterNativesULargeDataObject()
	{
		UClass* Class = ULargeDataObject::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "ApplyChunks", &ULargeDataObject::execApplyChunks },
			{ "BuildChunks", &ULargeDataObject::execBuildChunks },
			{ "OnRep_ReplicatedChunks", &ULargeDataObject::execOnRep_ReplicatedChunks },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULargeDataObject_ApplyChunks_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeDataObject_ApplyChunks_Statics::Function_MetaDataParams[] = {
		{ "Category", "Large Data" },
		{ "Comment", "/** Apply replicated chunks back to object data */" },
		{ "ModuleRelativePath", "Public/LargeDataObject.h" },
		{ "ToolTip", "Apply replicated chunks back to object data" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULargeDataObject_ApplyChunks_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULargeDataObject, nullptr, "ApplyChunks", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULargeDataObject_ApplyChunks_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeDataObject_ApplyChunks_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULargeDataObject_ApplyChunks()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULargeDataObject_ApplyChunks_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULargeDataObject_BuildChunks_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeDataObject_BuildChunks_Statics::Function_MetaDataParams[] = {
		{ "Category", "Large Data" },
		{ "Comment", "/** Build chunks from current object data */" },
		{ "ModuleRelativePath", "Public/LargeDataObject.h" },
		{ "ToolTip", "Build chunks from current object data" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULargeDataObject_BuildChunks_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULargeDataObject, nullptr, "BuildChunks", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULargeDataObject_BuildChunks_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeDataObject_BuildChunks_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULargeDataObject_BuildChunks()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULargeDataObject_BuildChunks_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULargeDataObject_OnRep_ReplicatedChunks_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeDataObject_OnRep_ReplicatedChunks_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/** Called when replicated chunks change on clients */" },
		{ "ModuleRelativePath", "Public/LargeDataObject.h" },
		{ "ToolTip", "Called when replicated chunks change on clients" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULargeDataObject_OnRep_ReplicatedChunks_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULargeDataObject, nullptr, "OnRep_ReplicatedChunks", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULargeDataObject_OnRep_ReplicatedChunks_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeDataObject_OnRep_ReplicatedChunks_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULargeDataObject_OnRep_ReplicatedChunks()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULargeDataObject_OnRep_ReplicatedChunks_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ULargeDataObject_NoRegister()
	{
		return ULargeDataObject::StaticClass();
	}
	struct Z_Construct_UClass_ULargeDataObject_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ReplicatedChunks_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReplicatedChunks;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DynamicChunkSize_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_DynamicChunkSize;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULargeDataObject_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_LargeData,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULargeDataObject_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULargeDataObject_ApplyChunks, "ApplyChunks" }, // 1826158085
		{ &Z_Construct_UFunction_ULargeDataObject_BuildChunks, "BuildChunks" }, // 598076690
		{ &Z_Construct_UFunction_ULargeDataObject_OnRep_ReplicatedChunks, "OnRep_ReplicatedChunks" }, // 3377233876
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULargeDataObject_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/** Base class for objects that replicate large data in chunks */" },
		{ "IncludePath", "LargeDataObject.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/LargeDataObject.h" },
		{ "ToolTip", "Base class for objects that replicate large data in chunks" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULargeDataObject_Statics::NewProp_ReplicatedChunks_MetaData[] = {
		{ "Comment", "/** Replicated chunks */" },
		{ "ModuleRelativePath", "Public/LargeDataObject.h" },
		{ "ToolTip", "Replicated chunks" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULargeDataObject_Statics::NewProp_ReplicatedChunks = { "ReplicatedChunks", "OnRep_ReplicatedChunks", (EPropertyFlags)0x0010000100000020, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULargeDataObject, ReplicatedChunks), Z_Construct_UScriptStruct_FLargeChunkArray, METADATA_PARAMS(Z_Construct_UClass_ULargeDataObject_Statics::NewProp_ReplicatedChunks_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULargeDataObject_Statics::NewProp_ReplicatedChunks_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULargeDataObject_Statics::NewProp_DynamicChunkSize_MetaData[] = {
		{ "Category", "Large Data" },
		{ "Comment", "/** Optional: dynamically set chunk size (in bytes) */" },
		{ "ModuleRelativePath", "Public/LargeDataObject.h" },
		{ "ToolTip", "Optional: dynamically set chunk size (in bytes)" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_ULargeDataObject_Statics::NewProp_DynamicChunkSize = { "DynamicChunkSize", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULargeDataObject, DynamicChunkSize), METADATA_PARAMS(Z_Construct_UClass_ULargeDataObject_Statics::NewProp_DynamicChunkSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULargeDataObject_Statics::NewProp_DynamicChunkSize_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULargeDataObject_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULargeDataObject_Statics::NewProp_ReplicatedChunks,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULargeDataObject_Statics::NewProp_DynamicChunkSize,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULargeDataObject_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULargeDataObject>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULargeDataObject_Statics::ClassParams = {
		&ULargeDataObject::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ULargeDataObject_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ULargeDataObject_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_ULargeDataObject_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULargeDataObject_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULargeDataObject()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULargeDataObject_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULargeDataObject, 447980169);
	template<> LARGEDATA_API UClass* StaticClass<ULargeDataObject>()
	{
		return ULargeDataObject::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULargeDataObject(Z_Construct_UClass_ULargeDataObject, &ULargeDataObject::StaticClass, TEXT("/Script/LargeData"), TEXT("ULargeDataObject"), false, nullptr, nullptr, nullptr);

	void ULargeDataObject::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
	{
		static const FName Name_ReplicatedChunks(TEXT("ReplicatedChunks"));

		const bool bIsValid = true
			&& Name_ReplicatedChunks == ClassReps[(int32)ENetFields_Private::ReplicatedChunks].Property->GetFName();

		checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in ULargeDataObject"));
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULargeDataObject);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
