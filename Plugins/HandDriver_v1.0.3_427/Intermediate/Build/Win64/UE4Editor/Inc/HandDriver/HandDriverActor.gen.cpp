// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HandDriver/Public/HandDriverActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHandDriverActor() {}
// Cross Module References
	HANDDRIVER_API UClass* Z_Construct_UClass_AHandDriverActor_NoRegister();
	HANDDRIVER_API UClass* Z_Construct_UClass_AHandDriverActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_HandDriver();
// End Cross Module References
	DEFINE_FUNCTION(AHandDriverActor::execDataRecvBytes)
	{
		P_GET_UBOOL_REF(Z_Param_Out_success);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<uint8>*)Z_Param__Result=P_THIS->DataRecvBytes(Z_Param_Out_success);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AHandDriverActor::execDataRecv)
	{
		P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_str);
		P_GET_UBOOL_REF(Z_Param_Out_success);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DataRecv(Z_Param_Out_str,Z_Param_Out_success);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AHandDriverActor::execStartUDPReceiver)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_YourChosenSocketName);
		P_GET_PROPERTY(FStrProperty,Z_Param_TheIP);
		P_GET_PROPERTY(FIntProperty,Z_Param_ThePort);
		P_GET_UBOOL_REF(Z_Param_Out_success);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->StartUDPReceiver(Z_Param_YourChosenSocketName,Z_Param_TheIP,Z_Param_ThePort,Z_Param_Out_success);
		P_NATIVE_END;
	}
	void AHandDriverActor::StaticRegisterNativesAHandDriverActor()
	{
		UClass* Class = AHandDriverActor::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "DataRecv", &AHandDriverActor::execDataRecv },
			{ "DataRecvBytes", &AHandDriverActor::execDataRecvBytes },
			{ "StartUDPReceiver", &AHandDriverActor::execStartUDPReceiver },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AHandDriverActor_DataRecv_Statics
	{
		struct HandDriverActor_eventDataRecv_Parms
		{
			FString str;
			bool success;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_str;
		static void NewProp_success_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_success;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_AHandDriverActor_DataRecv_Statics::NewProp_str = { "str", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HandDriverActor_eventDataRecv_Parms, str), METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_AHandDriverActor_DataRecv_Statics::NewProp_success_SetBit(void* Obj)
	{
		((HandDriverActor_eventDataRecv_Parms*)Obj)->success = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AHandDriverActor_DataRecv_Statics::NewProp_success = { "success", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(HandDriverActor_eventDataRecv_Parms), &Z_Construct_UFunction_AHandDriverActor_DataRecv_Statics::NewProp_success_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AHandDriverActor_DataRecv_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AHandDriverActor_DataRecv_Statics::NewProp_str,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AHandDriverActor_DataRecv_Statics::NewProp_success,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AHandDriverActor_DataRecv_Statics::Function_MetaDataParams[] = {
		{ "Category", "UDP" },
		{ "ModuleRelativePath", "Public/HandDriverActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AHandDriverActor_DataRecv_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AHandDriverActor, nullptr, "DataRecv", nullptr, nullptr, sizeof(HandDriverActor_eventDataRecv_Parms), Z_Construct_UFunction_AHandDriverActor_DataRecv_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AHandDriverActor_DataRecv_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AHandDriverActor_DataRecv_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AHandDriverActor_DataRecv_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AHandDriverActor_DataRecv()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AHandDriverActor_DataRecv_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AHandDriverActor_DataRecvBytes_Statics
	{
		struct HandDriverActor_eventDataRecvBytes_Parms
		{
			bool success;
			TArray<uint8> ReturnValue;
		};
		static void NewProp_success_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_success;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_AHandDriverActor_DataRecvBytes_Statics::NewProp_success_SetBit(void* Obj)
	{
		((HandDriverActor_eventDataRecvBytes_Parms*)Obj)->success = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AHandDriverActor_DataRecvBytes_Statics::NewProp_success = { "success", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(HandDriverActor_eventDataRecvBytes_Parms), &Z_Construct_UFunction_AHandDriverActor_DataRecvBytes_Statics::NewProp_success_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AHandDriverActor_DataRecvBytes_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_AHandDriverActor_DataRecvBytes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HandDriverActor_eventDataRecvBytes_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AHandDriverActor_DataRecvBytes_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AHandDriverActor_DataRecvBytes_Statics::NewProp_success,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AHandDriverActor_DataRecvBytes_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AHandDriverActor_DataRecvBytes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AHandDriverActor_DataRecvBytes_Statics::Function_MetaDataParams[] = {
		{ "Category", "UDP" },
		{ "ModuleRelativePath", "Public/HandDriverActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AHandDriverActor_DataRecvBytes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AHandDriverActor, nullptr, "DataRecvBytes", nullptr, nullptr, sizeof(HandDriverActor_eventDataRecvBytes_Parms), Z_Construct_UFunction_AHandDriverActor_DataRecvBytes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AHandDriverActor_DataRecvBytes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AHandDriverActor_DataRecvBytes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AHandDriverActor_DataRecvBytes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AHandDriverActor_DataRecvBytes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AHandDriverActor_DataRecvBytes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics
	{
		struct HandDriverActor_eventStartUDPReceiver_Parms
		{
			FString YourChosenSocketName;
			FString TheIP;
			int32 ThePort;
			bool success;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_YourChosenSocketName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_YourChosenSocketName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TheIP_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_TheIP;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ThePort_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ThePort;
		static void NewProp_success_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_success;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::NewProp_YourChosenSocketName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::NewProp_YourChosenSocketName = { "YourChosenSocketName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HandDriverActor_eventStartUDPReceiver_Parms, YourChosenSocketName), METADATA_PARAMS(Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::NewProp_YourChosenSocketName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::NewProp_YourChosenSocketName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::NewProp_TheIP_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::NewProp_TheIP = { "TheIP", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HandDriverActor_eventStartUDPReceiver_Parms, TheIP), METADATA_PARAMS(Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::NewProp_TheIP_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::NewProp_TheIP_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::NewProp_ThePort_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::NewProp_ThePort = { "ThePort", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HandDriverActor_eventStartUDPReceiver_Parms, ThePort), METADATA_PARAMS(Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::NewProp_ThePort_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::NewProp_ThePort_MetaData)) };
	void Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::NewProp_success_SetBit(void* Obj)
	{
		((HandDriverActor_eventStartUDPReceiver_Parms*)Obj)->success = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::NewProp_success = { "success", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(HandDriverActor_eventStartUDPReceiver_Parms), &Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::NewProp_success_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::NewProp_YourChosenSocketName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::NewProp_TheIP,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::NewProp_ThePort,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::NewProp_success,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::Function_MetaDataParams[] = {
		{ "Category", "UDP" },
		{ "ModuleRelativePath", "Public/HandDriverActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AHandDriverActor, nullptr, "StartUDPReceiver", nullptr, nullptr, sizeof(HandDriverActor_eventStartUDPReceiver_Parms), Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_AHandDriverActor_NoRegister()
	{
		return AHandDriverActor::StaticClass();
	}
	struct Z_Construct_UClass_AHandDriverActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AHandDriverActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_HandDriver,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_AHandDriverActor_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AHandDriverActor_DataRecv, "DataRecv" }, // 855088894
		{ &Z_Construct_UFunction_AHandDriverActor_DataRecvBytes, "DataRecvBytes" }, // 4138545868
		{ &Z_Construct_UFunction_AHandDriverActor_StartUDPReceiver, "StartUDPReceiver" }, // 2368094428
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AHandDriverActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "HandDriverActor.h" },
		{ "ModuleRelativePath", "Public/HandDriverActor.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AHandDriverActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AHandDriverActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AHandDriverActor_Statics::ClassParams = {
		&AHandDriverActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AHandDriverActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AHandDriverActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AHandDriverActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AHandDriverActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AHandDriverActor, 299844265);
	template<> HANDDRIVER_API UClass* StaticClass<AHandDriverActor>()
	{
		return AHandDriverActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AHandDriverActor(Z_Construct_UClass_AHandDriverActor, &AHandDriverActor::StaticClass, TEXT("/Script/HandDriver"), TEXT("AHandDriverActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AHandDriverActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
