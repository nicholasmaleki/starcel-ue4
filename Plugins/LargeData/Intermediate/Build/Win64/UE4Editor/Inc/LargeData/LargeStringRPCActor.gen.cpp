// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LargeData/Public/LargeStringRPCActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLargeStringRPCActor() {}
// Cross Module References
	LARGEDATA_API UClass* Z_Construct_UClass_ALargeStringRPCActor_NoRegister();
	LARGEDATA_API UClass* Z_Construct_UClass_ALargeStringRPCActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_LargeData();
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeStringAsync_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(ALargeStringRPCActor::execClient_ReceiveChunk)
	{
		P_GET_TARRAY(uint8,Z_Param_Chunk);
		P_GET_PROPERTY(FIntProperty,Z_Param_Index);
		P_GET_PROPERTY(FIntProperty,Z_Param_TotalChunks);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Client_ReceiveChunk_Implementation(Z_Param_Chunk,Z_Param_Index,Z_Param_TotalChunks);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ALargeStringRPCActor::execMulticast_ReceiveChunk)
	{
		P_GET_TARRAY(uint8,Z_Param_Chunk);
		P_GET_PROPERTY(FIntProperty,Z_Param_Index);
		P_GET_PROPERTY(FIntProperty,Z_Param_TotalChunks);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Multicast_ReceiveChunk_Implementation(Z_Param_Chunk,Z_Param_Index,Z_Param_TotalChunks);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ALargeStringRPCActor::execServer_ReceiveChunk)
	{
		P_GET_TARRAY(uint8,Z_Param_Chunk);
		P_GET_PROPERTY(FIntProperty,Z_Param_Index);
		P_GET_PROPERTY(FIntProperty,Z_Param_TotalChunks);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Server_ReceiveChunk_Implementation(Z_Param_Chunk,Z_Param_Index,Z_Param_TotalChunks);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ALargeStringRPCActor::execServer_OnFullStringReceived)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Server_OnFullStringReceived();
		P_NATIVE_END;
	}
	static FName NAME_ALargeStringRPCActor_Client_ReceiveChunk = FName(TEXT("Client_ReceiveChunk"));
	void ALargeStringRPCActor::Client_ReceiveChunk(TArray<uint8> const& Chunk, int32 Index, int32 TotalChunks)
	{
		LargeStringRPCActor_eventClient_ReceiveChunk_Parms Parms;
		Parms.Chunk=Chunk;
		Parms.Index=Index;
		Parms.TotalChunks=TotalChunks;
		ProcessEvent(FindFunctionChecked(NAME_ALargeStringRPCActor_Client_ReceiveChunk),&Parms);
	}
	static FName NAME_ALargeStringRPCActor_Multicast_ReceiveChunk = FName(TEXT("Multicast_ReceiveChunk"));
	void ALargeStringRPCActor::Multicast_ReceiveChunk(TArray<uint8> const& Chunk, int32 Index, int32 TotalChunks)
	{
		LargeStringRPCActor_eventMulticast_ReceiveChunk_Parms Parms;
		Parms.Chunk=Chunk;
		Parms.Index=Index;
		Parms.TotalChunks=TotalChunks;
		ProcessEvent(FindFunctionChecked(NAME_ALargeStringRPCActor_Multicast_ReceiveChunk),&Parms);
	}
	static FName NAME_ALargeStringRPCActor_Server_ReceiveChunk = FName(TEXT("Server_ReceiveChunk"));
	void ALargeStringRPCActor::Server_ReceiveChunk(TArray<uint8> const& Chunk, int32 Index, int32 TotalChunks)
	{
		LargeStringRPCActor_eventServer_ReceiveChunk_Parms Parms;
		Parms.Chunk=Chunk;
		Parms.Index=Index;
		Parms.TotalChunks=TotalChunks;
		ProcessEvent(FindFunctionChecked(NAME_ALargeStringRPCActor_Server_ReceiveChunk),&Parms);
	}
	void ALargeStringRPCActor::StaticRegisterNativesALargeStringRPCActor()
	{
		UClass* Class = ALargeStringRPCActor::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "Client_ReceiveChunk", &ALargeStringRPCActor::execClient_ReceiveChunk },
			{ "Multicast_ReceiveChunk", &ALargeStringRPCActor::execMulticast_ReceiveChunk },
			{ "Server_OnFullStringReceived", &ALargeStringRPCActor::execServer_OnFullStringReceived },
			{ "Server_ReceiveChunk", &ALargeStringRPCActor::execServer_ReceiveChunk },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk_Statics
	{
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
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk_Statics::NewProp_Chunk_Inner = { "Chunk", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk_Statics::NewProp_Chunk_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk_Statics::NewProp_Chunk = { "Chunk", nullptr, (EPropertyFlags)0x0010000008000082, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringRPCActor_eventClient_ReceiveChunk_Parms, Chunk), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk_Statics::NewProp_Chunk_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk_Statics::NewProp_Chunk_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringRPCActor_eventClient_ReceiveChunk_Parms, Index), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk_Statics::NewProp_TotalChunks = { "TotalChunks", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringRPCActor_eventClient_ReceiveChunk_Parms, TotalChunks), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk_Statics::NewProp_Chunk_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk_Statics::NewProp_Chunk,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk_Statics::NewProp_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk_Statics::NewProp_TotalChunks,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/** Server \xe2\x86\x92 specific client: send chunk to one client */" },
		{ "ModuleRelativePath", "Public/LargeStringRPCActor.h" },
		{ "ToolTip", "Server \xe2\x86\x92 specific client: send chunk to one client" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ALargeStringRPCActor, nullptr, "Client_ReceiveChunk", nullptr, nullptr, sizeof(LargeStringRPCActor_eventClient_ReceiveChunk_Parms), Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01020CC0, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk_Statics
	{
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
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk_Statics::NewProp_Chunk_Inner = { "Chunk", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk_Statics::NewProp_Chunk_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk_Statics::NewProp_Chunk = { "Chunk", nullptr, (EPropertyFlags)0x0010000008000082, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringRPCActor_eventMulticast_ReceiveChunk_Parms, Chunk), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk_Statics::NewProp_Chunk_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk_Statics::NewProp_Chunk_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringRPCActor_eventMulticast_ReceiveChunk_Parms, Index), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk_Statics::NewProp_TotalChunks = { "TotalChunks", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringRPCActor_eventMulticast_ReceiveChunk_Parms, TotalChunks), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk_Statics::NewProp_Chunk_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk_Statics::NewProp_Chunk,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk_Statics::NewProp_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk_Statics::NewProp_TotalChunks,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/** Server \xe2\x86\x92 All clients: multicast a chunk */" },
		{ "ModuleRelativePath", "Public/LargeStringRPCActor.h" },
		{ "ToolTip", "Server \xe2\x86\x92 All clients: multicast a chunk" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ALargeStringRPCActor, nullptr, "Multicast_ReceiveChunk", nullptr, nullptr, sizeof(LargeStringRPCActor_eventMulticast_ReceiveChunk_Parms), Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00024CC0, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ALargeStringRPCActor_Server_OnFullStringReceived_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ALargeStringRPCActor_Server_OnFullStringReceived_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/** Called when the full string is received on the server */" },
		{ "ModuleRelativePath", "Public/LargeStringRPCActor.h" },
		{ "ToolTip", "Called when the full string is received on the server" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ALargeStringRPCActor_Server_OnFullStringReceived_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ALargeStringRPCActor, nullptr, "Server_OnFullStringReceived", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ALargeStringRPCActor_Server_OnFullStringReceived_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeStringRPCActor_Server_OnFullStringReceived_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ALargeStringRPCActor_Server_OnFullStringReceived()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ALargeStringRPCActor_Server_OnFullStringReceived_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk_Statics
	{
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
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk_Statics::NewProp_Chunk_Inner = { "Chunk", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk_Statics::NewProp_Chunk_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk_Statics::NewProp_Chunk = { "Chunk", nullptr, (EPropertyFlags)0x0010000008000082, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringRPCActor_eventServer_ReceiveChunk_Parms, Chunk), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk_Statics::NewProp_Chunk_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk_Statics::NewProp_Chunk_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringRPCActor_eventServer_ReceiveChunk_Parms, Index), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk_Statics::NewProp_TotalChunks = { "TotalChunks", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringRPCActor_eventServer_ReceiveChunk_Parms, TotalChunks), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk_Statics::NewProp_Chunk_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk_Statics::NewProp_Chunk,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk_Statics::NewProp_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk_Statics::NewProp_TotalChunks,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/** Client \xe2\x86\x92 Server: receive a chunk */" },
		{ "ModuleRelativePath", "Public/LargeStringRPCActor.h" },
		{ "ToolTip", "Client \xe2\x86\x92 Server: receive a chunk" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ALargeStringRPCActor, nullptr, "Server_ReceiveChunk", nullptr, nullptr, sizeof(LargeStringRPCActor_eventServer_ReceiveChunk_Parms), Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00220CC0, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ALargeStringRPCActor_NoRegister()
	{
		return ALargeStringRPCActor::StaticClass();
	}
	struct Z_Construct_UClass_ALargeStringRPCActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LargeString_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_LargeString;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ALargeStringRPCActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_LargeData,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ALargeStringRPCActor_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ALargeStringRPCActor_Client_ReceiveChunk, "Client_ReceiveChunk" }, // 1331476124
		{ &Z_Construct_UFunction_ALargeStringRPCActor_Multicast_ReceiveChunk, "Multicast_ReceiveChunk" }, // 2916637851
		{ &Z_Construct_UFunction_ALargeStringRPCActor_Server_OnFullStringReceived, "Server_OnFullStringReceived" }, // 912756693
		{ &Z_Construct_UFunction_ALargeStringRPCActor_Server_ReceiveChunk, "Server_ReceiveChunk" }, // 2216804323
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ALargeStringRPCActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "LargeStringRPCActor.h" },
		{ "ModuleRelativePath", "Public/LargeStringRPCActor.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ALargeStringRPCActor_Statics::NewProp_LargeString_MetaData[] = {
		{ "Category", "LargeStringRPCActor" },
		{ "Comment", "/** The LargeStringAsync object attached to this actor */" },
		{ "ModuleRelativePath", "Public/LargeStringRPCActor.h" },
		{ "ToolTip", "The LargeStringAsync object attached to this actor" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALargeStringRPCActor_Statics::NewProp_LargeString = { "LargeString", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ALargeStringRPCActor, LargeString), Z_Construct_UClass_ULargeStringAsync_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ALargeStringRPCActor_Statics::NewProp_LargeString_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ALargeStringRPCActor_Statics::NewProp_LargeString_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ALargeStringRPCActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeStringRPCActor_Statics::NewProp_LargeString,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ALargeStringRPCActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALargeStringRPCActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ALargeStringRPCActor_Statics::ClassParams = {
		&ALargeStringRPCActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ALargeStringRPCActor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ALargeStringRPCActor_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ALargeStringRPCActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ALargeStringRPCActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ALargeStringRPCActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ALargeStringRPCActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ALargeStringRPCActor, 2754332025);
	template<> LARGEDATA_API UClass* StaticClass<ALargeStringRPCActor>()
	{
		return ALargeStringRPCActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ALargeStringRPCActor(Z_Construct_UClass_ALargeStringRPCActor, &ALargeStringRPCActor::StaticClass, TEXT("/Script/LargeData"), TEXT("ALargeStringRPCActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ALargeStringRPCActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
