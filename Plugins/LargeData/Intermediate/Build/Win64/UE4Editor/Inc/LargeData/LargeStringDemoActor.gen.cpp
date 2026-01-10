// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LargeData/Public/LargeStringDemoActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLargeStringDemoActor() {}
// Cross Module References
	LARGEDATA_API UClass* Z_Construct_UClass_ALargeStringDemoActor_NoRegister();
	LARGEDATA_API UClass* Z_Construct_UClass_ALargeStringDemoActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_LargeData();
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeStringAsync_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(ALargeStringDemoActor::execOnStringFullyReceived)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnStringFullyReceived();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ALargeStringDemoActor::execServer_SendChunk)
	{
		P_GET_TARRAY(uint8,Z_Param_Chunk);
		P_GET_PROPERTY(FIntProperty,Z_Param_Index);
		P_GET_PROPERTY(FIntProperty,Z_Param_TotalChunks);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Server_SendChunk_Implementation(Z_Param_Chunk,Z_Param_Index,Z_Param_TotalChunks);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ALargeStringDemoActor::execClient_ReceiveChunk)
	{
		P_GET_TARRAY(uint8,Z_Param_Chunk);
		P_GET_PROPERTY(FIntProperty,Z_Param_Index);
		P_GET_PROPERTY(FIntProperty,Z_Param_TotalChunks);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Client_ReceiveChunk_Implementation(Z_Param_Chunk,Z_Param_Index,Z_Param_TotalChunks);
		P_NATIVE_END;
	}
	static FName NAME_ALargeStringDemoActor_Client_ReceiveChunk = FName(TEXT("Client_ReceiveChunk"));
	void ALargeStringDemoActor::Client_ReceiveChunk(TArray<uint8> const& Chunk, int32 Index, int32 TotalChunks)
	{
		LargeStringDemoActor_eventClient_ReceiveChunk_Parms Parms;
		Parms.Chunk=Chunk;
		Parms.Index=Index;
		Parms.TotalChunks=TotalChunks;
		ProcessEvent(FindFunctionChecked(NAME_ALargeStringDemoActor_Client_ReceiveChunk),&Parms);
	}
	static FName NAME_ALargeStringDemoActor_Server_SendChunk = FName(TEXT("Server_SendChunk"));
	void ALargeStringDemoActor::Server_SendChunk(TArray<uint8> const& Chunk, int32 Index, int32 TotalChunks)
	{
		LargeStringDemoActor_eventServer_SendChunk_Parms Parms;
		Parms.Chunk=Chunk;
		Parms.Index=Index;
		Parms.TotalChunks=TotalChunks;
		ProcessEvent(FindFunctionChecked(NAME_ALargeStringDemoActor_Server_SendChunk),&Parms);
	}
	void ALargeStringDemoActor::StaticRegisterNativesALargeStringDemoActor()
	{
		UClass* Class = ALargeStringDemoActor::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "Client_ReceiveChunk", &ALargeStringDemoActor::execClient_ReceiveChunk },
			{ "OnStringFullyReceived", &ALargeStringDemoActor::execOnStringFullyReceived },
			{ "Server_SendChunk", &ALargeStringDemoActor::execServer_SendChunk },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk_Statics
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
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk_Statics::NewProp_Chunk_Inner = { "Chunk", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk_Statics::NewProp_Chunk_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk_Statics::NewProp_Chunk = { "Chunk", nullptr, (EPropertyFlags)0x0010000008000082, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringDemoActor_eventClient_ReceiveChunk_Parms, Chunk), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk_Statics::NewProp_Chunk_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk_Statics::NewProp_Chunk_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringDemoActor_eventClient_ReceiveChunk_Parms, Index), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk_Statics::NewProp_TotalChunks = { "TotalChunks", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringDemoActor_eventClient_ReceiveChunk_Parms, TotalChunks), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk_Statics::NewProp_Chunk_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk_Statics::NewProp_Chunk,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk_Statics::NewProp_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk_Statics::NewProp_TotalChunks,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/** Client RPC: receive a chunk from server */" },
		{ "ModuleRelativePath", "Public/LargeStringDemoActor.h" },
		{ "ToolTip", "Client RPC: receive a chunk from server" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ALargeStringDemoActor, nullptr, "Client_ReceiveChunk", nullptr, nullptr, sizeof(LargeStringDemoActor_eventClient_ReceiveChunk_Parms), Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01020CC0, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ALargeStringDemoActor_OnStringFullyReceived_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ALargeStringDemoActor_OnStringFullyReceived_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/** Called when full string has been received */" },
		{ "ModuleRelativePath", "Public/LargeStringDemoActor.h" },
		{ "ToolTip", "Called when full string has been received" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ALargeStringDemoActor_OnStringFullyReceived_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ALargeStringDemoActor, nullptr, "OnStringFullyReceived", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ALargeStringDemoActor_OnStringFullyReceived_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeStringDemoActor_OnStringFullyReceived_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ALargeStringDemoActor_OnStringFullyReceived()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ALargeStringDemoActor_OnStringFullyReceived_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk_Statics
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
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk_Statics::NewProp_Chunk_Inner = { "Chunk", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk_Statics::NewProp_Chunk_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk_Statics::NewProp_Chunk = { "Chunk", nullptr, (EPropertyFlags)0x0010000008000082, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringDemoActor_eventServer_SendChunk_Parms, Chunk), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk_Statics::NewProp_Chunk_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk_Statics::NewProp_Chunk_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringDemoActor_eventServer_SendChunk_Parms, Index), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk_Statics::NewProp_TotalChunks = { "TotalChunks", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeStringDemoActor_eventServer_SendChunk_Parms, TotalChunks), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk_Statics::NewProp_Chunk_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk_Statics::NewProp_Chunk,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk_Statics::NewProp_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk_Statics::NewProp_TotalChunks,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/** Server RPC: receive a chunk from client */" },
		{ "ModuleRelativePath", "Public/LargeStringDemoActor.h" },
		{ "ToolTip", "Server RPC: receive a chunk from client" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ALargeStringDemoActor, nullptr, "Server_SendChunk", nullptr, nullptr, sizeof(LargeStringDemoActor_eventServer_SendChunk_Parms), Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00220CC0, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ALargeStringDemoActor_NoRegister()
	{
		return ALargeStringDemoActor::StaticClass();
	}
	struct Z_Construct_UClass_ALargeStringDemoActor_Statics
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
	UObject* (*const Z_Construct_UClass_ALargeStringDemoActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_LargeData,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ALargeStringDemoActor_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ALargeStringDemoActor_Client_ReceiveChunk, "Client_ReceiveChunk" }, // 2930692563
		{ &Z_Construct_UFunction_ALargeStringDemoActor_OnStringFullyReceived, "OnStringFullyReceived" }, // 597926892
		{ &Z_Construct_UFunction_ALargeStringDemoActor_Server_SendChunk, "Server_SendChunk" }, // 2580323098
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ALargeStringDemoActor_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Actor for sending/receiving large strings asynchronously.\n * Demonstrates server/client chunked RPC usage.\n */" },
		{ "IncludePath", "LargeStringDemoActor.h" },
		{ "ModuleRelativePath", "Public/LargeStringDemoActor.h" },
		{ "ToolTip", "Actor for sending/receiving large strings asynchronously.\nDemonstrates server/client chunked RPC usage." },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ALargeStringDemoActor_Statics::NewProp_LargeString_MetaData[] = {
		{ "Comment", "/** Async large string object */" },
		{ "ModuleRelativePath", "Public/LargeStringDemoActor.h" },
		{ "ToolTip", "Async large string object" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALargeStringDemoActor_Statics::NewProp_LargeString = { "LargeString", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ALargeStringDemoActor, LargeString), Z_Construct_UClass_ULargeStringAsync_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ALargeStringDemoActor_Statics::NewProp_LargeString_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ALargeStringDemoActor_Statics::NewProp_LargeString_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ALargeStringDemoActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALargeStringDemoActor_Statics::NewProp_LargeString,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ALargeStringDemoActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALargeStringDemoActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ALargeStringDemoActor_Statics::ClassParams = {
		&ALargeStringDemoActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ALargeStringDemoActor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ALargeStringDemoActor_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ALargeStringDemoActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ALargeStringDemoActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ALargeStringDemoActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ALargeStringDemoActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ALargeStringDemoActor, 2966903120);
	template<> LARGEDATA_API UClass* StaticClass<ALargeStringDemoActor>()
	{
		return ALargeStringDemoActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ALargeStringDemoActor(Z_Construct_UClass_ALargeStringDemoActor, &ALargeStringDemoActor::StaticClass, TEXT("/Script/LargeData"), TEXT("ALargeStringDemoActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ALargeStringDemoActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
