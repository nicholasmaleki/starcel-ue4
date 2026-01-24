// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LargeData/Public/LargeStringAsync.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLargeStringAsync() {}
// Cross Module References
	LARGEDATA_API UFunction* Z_Construct_UDelegateFunction_LargeData_OnChunksBuilt__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_LargeData();
	LARGEDATA_API UFunction* Z_Construct_UDelegateFunction_LargeData_OnLargeStringAsyncReceived__DelegateSignature();
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeStringAsync_NoRegister();
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeStringAsync();
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeDataObject();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_LargeData_OnChunksBuilt__DelegateSignature_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_LargeData_OnChunksBuilt__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LargeStringAsync.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_LargeData_OnChunksBuilt__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_LargeData, nullptr, "OnChunksBuilt__DelegateSignature", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_LargeData_OnChunksBuilt__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LargeData_OnChunksBuilt__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_LargeData_OnChunksBuilt__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_LargeData_OnChunksBuilt__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UDelegateFunction_LargeData_OnLargeStringAsyncReceived__DelegateSignature_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_LargeData_OnLargeStringAsyncReceived__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LargeStringAsync.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_LargeData_OnLargeStringAsyncReceived__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_LargeData, nullptr, "OnLargeStringAsyncReceived__DelegateSignature", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_LargeData_OnLargeStringAsyncReceived__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LargeData_OnLargeStringAsyncReceived__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_LargeData_OnLargeStringAsyncReceived__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_LargeData_OnLargeStringAsyncReceived__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	DEFINE_FUNCTION(ULargeStringAsync::execGetSerializedSize)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetSerializedSize();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULargeStringAsync::execToString)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->ToString();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULargeStringAsync::execGetChunk)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_Index);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<uint8>*)Z_Param__Result=P_THIS->GetChunk(Z_Param_Index);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULargeStringAsync::execIsFullyReceived)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->IsFullyReceived();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULargeStringAsync::execGetExpectedChunkCount)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetExpectedChunkCount();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULargeStringAsync::execGetChunkCount)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetChunkCount();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULargeStringAsync::execReassembleFromChunksAsync)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ReassembleFromChunksAsync();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULargeStringAsync::execReceiveChunk)
	{
		P_GET_TARRAY_REF(uint8,Z_Param_Out_Chunk);
		P_GET_PROPERTY(FIntProperty,Z_Param_Index);
		P_GET_PROPERTY(FIntProperty,Z_Param_TotalChunks);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ReceiveChunk(Z_Param_Out_Chunk,Z_Param_Index,Z_Param_TotalChunks);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULargeStringAsync::execSetFromStringAsync)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InString);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetFromStringAsync(Z_Param_InString);
		P_NATIVE_END;
	}
	void ULargeStringAsync::StaticRegisterNativesULargeStringAsync()
	{
		UClass* Class = ULargeStringAsync::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetChunk", &ULargeStringAsync::execGetChunk },
			{ "GetChunkCount", &ULargeStringAsync::execGetChunkCount },
			{ "GetExpectedChunkCount", &ULargeStringAsync::execGetExpectedChunkCount },
			{ "GetSerializedSize", &ULargeStringAsync::execGetSerializedSize },
			{ "IsFullyReceived", &ULargeStringAsync::execIsFullyReceived },
			{ "ReassembleFromChunksAsync", &ULargeStringAsync::execReassembleFromChunksAsync },
			{ "ReceiveChunk", &ULargeStringAsync::execReceiveChunk },
			{ "SetFromStringAsync", &ULargeStringAsync::execSetFromStringAsync },
			{ "ToString", &ULargeStringAsync::execToString },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULargeStringAsync_GetChunk_Statics
	{
		struct LargeStringAsync_eventGetChunk_Parms
		{
			int32 Index;
			TArray<uint8> ReturnValue;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Index;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULargeStringAsync_GetChunk_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringAsync_eventGetChunk_Parms, Index), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ULargeStringAsync_GetChunk_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULargeStringAsync_GetChunk_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringAsync_eventGetChunk_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULargeStringAsync_GetChunk_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeStringAsync_GetChunk_Statics::NewProp_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeStringAsync_GetChunk_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeStringAsync_GetChunk_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeStringAsync_GetChunk_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LargeStringAsync.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULargeStringAsync_GetChunk_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULargeStringAsync, nullptr, "GetChunk", nullptr, nullptr, sizeof(LargeStringAsync_eventGetChunk_Parms), Z_Construct_UFunction_ULargeStringAsync_GetChunk_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeStringAsync_GetChunk_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULargeStringAsync_GetChunk_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeStringAsync_GetChunk_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULargeStringAsync_GetChunk()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULargeStringAsync_GetChunk_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULargeStringAsync_GetChunkCount_Statics
	{
		struct LargeStringAsync_eventGetChunkCount_Parms
		{
			int32 ReturnValue;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULargeStringAsync_GetChunkCount_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringAsync_eventGetChunkCount_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULargeStringAsync_GetChunkCount_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeStringAsync_GetChunkCount_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeStringAsync_GetChunkCount_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LargeStringAsync.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULargeStringAsync_GetChunkCount_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULargeStringAsync, nullptr, "GetChunkCount", nullptr, nullptr, sizeof(LargeStringAsync_eventGetChunkCount_Parms), Z_Construct_UFunction_ULargeStringAsync_GetChunkCount_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeStringAsync_GetChunkCount_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULargeStringAsync_GetChunkCount_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeStringAsync_GetChunkCount_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULargeStringAsync_GetChunkCount()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULargeStringAsync_GetChunkCount_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULargeStringAsync_GetExpectedChunkCount_Statics
	{
		struct LargeStringAsync_eventGetExpectedChunkCount_Parms
		{
			int32 ReturnValue;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULargeStringAsync_GetExpectedChunkCount_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringAsync_eventGetExpectedChunkCount_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULargeStringAsync_GetExpectedChunkCount_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeStringAsync_GetExpectedChunkCount_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeStringAsync_GetExpectedChunkCount_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LargeStringAsync.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULargeStringAsync_GetExpectedChunkCount_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULargeStringAsync, nullptr, "GetExpectedChunkCount", nullptr, nullptr, sizeof(LargeStringAsync_eventGetExpectedChunkCount_Parms), Z_Construct_UFunction_ULargeStringAsync_GetExpectedChunkCount_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeStringAsync_GetExpectedChunkCount_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULargeStringAsync_GetExpectedChunkCount_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeStringAsync_GetExpectedChunkCount_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULargeStringAsync_GetExpectedChunkCount()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULargeStringAsync_GetExpectedChunkCount_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULargeStringAsync_GetSerializedSize_Statics
	{
		struct LargeStringAsync_eventGetSerializedSize_Parms
		{
			int32 ReturnValue;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULargeStringAsync_GetSerializedSize_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringAsync_eventGetSerializedSize_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULargeStringAsync_GetSerializedSize_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeStringAsync_GetSerializedSize_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeStringAsync_GetSerializedSize_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LargeStringAsync.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULargeStringAsync_GetSerializedSize_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULargeStringAsync, nullptr, "GetSerializedSize", nullptr, nullptr, sizeof(LargeStringAsync_eventGetSerializedSize_Parms), Z_Construct_UFunction_ULargeStringAsync_GetSerializedSize_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeStringAsync_GetSerializedSize_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULargeStringAsync_GetSerializedSize_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeStringAsync_GetSerializedSize_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULargeStringAsync_GetSerializedSize()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULargeStringAsync_GetSerializedSize_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULargeStringAsync_IsFullyReceived_Statics
	{
		struct LargeStringAsync_eventIsFullyReceived_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_ULargeStringAsync_IsFullyReceived_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LargeStringAsync_eventIsFullyReceived_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULargeStringAsync_IsFullyReceived_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LargeStringAsync_eventIsFullyReceived_Parms), &Z_Construct_UFunction_ULargeStringAsync_IsFullyReceived_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULargeStringAsync_IsFullyReceived_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeStringAsync_IsFullyReceived_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeStringAsync_IsFullyReceived_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LargeStringAsync.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULargeStringAsync_IsFullyReceived_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULargeStringAsync, nullptr, "IsFullyReceived", nullptr, nullptr, sizeof(LargeStringAsync_eventIsFullyReceived_Parms), Z_Construct_UFunction_ULargeStringAsync_IsFullyReceived_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeStringAsync_IsFullyReceived_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULargeStringAsync_IsFullyReceived_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeStringAsync_IsFullyReceived_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULargeStringAsync_IsFullyReceived()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULargeStringAsync_IsFullyReceived_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULargeStringAsync_ReassembleFromChunksAsync_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeStringAsync_ReassembleFromChunksAsync_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/** Async reassembly */" },
		{ "ModuleRelativePath", "Public/LargeStringAsync.h" },
		{ "ToolTip", "Async reassembly" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULargeStringAsync_ReassembleFromChunksAsync_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULargeStringAsync, nullptr, "ReassembleFromChunksAsync", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULargeStringAsync_ReassembleFromChunksAsync_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeStringAsync_ReassembleFromChunksAsync_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULargeStringAsync_ReassembleFromChunksAsync()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULargeStringAsync_ReassembleFromChunksAsync_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk_Statics
	{
		struct LargeStringAsync_eventReceiveChunk_Parms
		{
			TArray<uint8> Chunk;
			int32 Index;
			int32 TotalChunks;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Chunk_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Chunk_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Chunk;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Index;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_TotalChunks;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk_Statics::NewProp_Chunk_Inner = { "Chunk", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk_Statics::NewProp_Chunk_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk_Statics::NewProp_Chunk = { "Chunk", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringAsync_eventReceiveChunk_Parms, Chunk), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk_Statics::NewProp_Chunk_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk_Statics::NewProp_Chunk_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringAsync_eventReceiveChunk_Parms, Index), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk_Statics::NewProp_TotalChunks = { "TotalChunks", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringAsync_eventReceiveChunk_Parms, TotalChunks), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk_Statics::NewProp_Chunk_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk_Statics::NewProp_Chunk,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk_Statics::NewProp_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk_Statics::NewProp_TotalChunks,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/** Receive a chunk (called by RPC actor or Python) */" },
		{ "ModuleRelativePath", "Public/LargeStringAsync.h" },
		{ "ToolTip", "Receive a chunk (called by RPC actor or Python)" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULargeStringAsync, nullptr, "ReceiveChunk", nullptr, nullptr, sizeof(LargeStringAsync_eventReceiveChunk_Parms), Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULargeStringAsync_SetFromStringAsync_Statics
	{
		struct LargeStringAsync_eventSetFromStringAsync_Parms
		{
			FString InString;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InString_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_InString;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeStringAsync_SetFromStringAsync_Statics::NewProp_InString_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ULargeStringAsync_SetFromStringAsync_Statics::NewProp_InString = { "InString", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringAsync_eventSetFromStringAsync_Parms, InString), METADATA_PARAMS(Z_Construct_UFunction_ULargeStringAsync_SetFromStringAsync_Statics::NewProp_InString_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeStringAsync_SetFromStringAsync_Statics::NewProp_InString_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULargeStringAsync_SetFromStringAsync_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeStringAsync_SetFromStringAsync_Statics::NewProp_InString,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeStringAsync_SetFromStringAsync_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/** Build chunks asynchronously from FString */" },
		{ "ModuleRelativePath", "Public/LargeStringAsync.h" },
		{ "ToolTip", "Build chunks asynchronously from FString" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULargeStringAsync_SetFromStringAsync_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULargeStringAsync, nullptr, "SetFromStringAsync", nullptr, nullptr, sizeof(LargeStringAsync_eventSetFromStringAsync_Parms), Z_Construct_UFunction_ULargeStringAsync_SetFromStringAsync_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeStringAsync_SetFromStringAsync_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULargeStringAsync_SetFromStringAsync_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeStringAsync_SetFromStringAsync_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULargeStringAsync_SetFromStringAsync()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULargeStringAsync_SetFromStringAsync_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULargeStringAsync_ToString_Statics
	{
		struct LargeStringAsync_eventToString_Parms
		{
			FString ReturnValue;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ULargeStringAsync_ToString_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringAsync_eventToString_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULargeStringAsync_ToString_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeStringAsync_ToString_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeStringAsync_ToString_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LargeStringAsync.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULargeStringAsync_ToString_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULargeStringAsync, nullptr, "ToString", nullptr, nullptr, sizeof(LargeStringAsync_eventToString_Parms), Z_Construct_UFunction_ULargeStringAsync_ToString_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeStringAsync_ToString_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULargeStringAsync_ToString_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeStringAsync_ToString_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULargeStringAsync_ToString()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULargeStringAsync_ToString_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ULargeStringAsync_NoRegister()
	{
		return ULargeStringAsync::StaticClass();
	}
	struct Z_Construct_UClass_ULargeStringAsync_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnFullyReceived_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnFullyReceived;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnChunksBuilt_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnChunksBuilt;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULargeStringAsync_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ULargeDataObject,
		(UObject* (*)())Z_Construct_UPackage__Script_LargeData,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULargeStringAsync_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULargeStringAsync_GetChunk, "GetChunk" }, // 2078071925
		{ &Z_Construct_UFunction_ULargeStringAsync_GetChunkCount, "GetChunkCount" }, // 3154786892
		{ &Z_Construct_UFunction_ULargeStringAsync_GetExpectedChunkCount, "GetExpectedChunkCount" }, // 2932690731
		{ &Z_Construct_UFunction_ULargeStringAsync_GetSerializedSize, "GetSerializedSize" }, // 4133764479
		{ &Z_Construct_UFunction_ULargeStringAsync_IsFullyReceived, "IsFullyReceived" }, // 391052158
		{ &Z_Construct_UFunction_ULargeStringAsync_ReassembleFromChunksAsync, "ReassembleFromChunksAsync" }, // 1953374076
		{ &Z_Construct_UFunction_ULargeStringAsync_ReceiveChunk, "ReceiveChunk" }, // 804026855
		{ &Z_Construct_UFunction_ULargeStringAsync_SetFromStringAsync, "SetFromStringAsync" }, // 697932192
		{ &Z_Construct_UFunction_ULargeStringAsync_ToString, "ToString" }, // 2718216335
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULargeStringAsync_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * ULargeStringAsync\n *\n * Async, chunked large string support.\n * Pure data + async logic (NO RPCs here).\n * 1GB-safe via chunking.\n */" },
		{ "IncludePath", "LargeStringAsync.h" },
		{ "ModuleRelativePath", "Public/LargeStringAsync.h" },
		{ "ToolTip", "ULargeStringAsync\n\nAsync, chunked large string support.\nPure data + async logic (NO RPCs here).\n1GB-safe via chunking." },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULargeStringAsync_Statics::NewProp_OnFullyReceived_MetaData[] = {
		{ "Comment", "/** Fired when full string reconstructed */" },
		{ "ModuleRelativePath", "Public/LargeStringAsync.h" },
		{ "ToolTip", "Fired when full string reconstructed" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_ULargeStringAsync_Statics::NewProp_OnFullyReceived = { "OnFullyReceived", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULargeStringAsync, OnFullyReceived), Z_Construct_UDelegateFunction_LargeData_OnLargeStringAsyncReceived__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_ULargeStringAsync_Statics::NewProp_OnFullyReceived_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULargeStringAsync_Statics::NewProp_OnFullyReceived_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULargeStringAsync_Statics::NewProp_OnChunksBuilt_MetaData[] = {
		{ "Comment", "/** Fired when chunks are ready */" },
		{ "ModuleRelativePath", "Public/LargeStringAsync.h" },
		{ "ToolTip", "Fired when chunks are ready" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_ULargeStringAsync_Statics::NewProp_OnChunksBuilt = { "OnChunksBuilt", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULargeStringAsync, OnChunksBuilt), Z_Construct_UDelegateFunction_LargeData_OnChunksBuilt__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_ULargeStringAsync_Statics::NewProp_OnChunksBuilt_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULargeStringAsync_Statics::NewProp_OnChunksBuilt_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULargeStringAsync_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULargeStringAsync_Statics::NewProp_OnFullyReceived,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULargeStringAsync_Statics::NewProp_OnChunksBuilt,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULargeStringAsync_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULargeStringAsync>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULargeStringAsync_Statics::ClassParams = {
		&ULargeStringAsync::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ULargeStringAsync_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ULargeStringAsync_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_ULargeStringAsync_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULargeStringAsync_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULargeStringAsync()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULargeStringAsync_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULargeStringAsync, 2661459740);
	template<> LARGEDATA_API UClass* StaticClass<ULargeStringAsync>()
	{
		return ULargeStringAsync::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULargeStringAsync(Z_Construct_UClass_ULargeStringAsync, &ULargeStringAsync::StaticClass, TEXT("/Script/LargeData"), TEXT("ULargeStringAsync"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULargeStringAsync);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
