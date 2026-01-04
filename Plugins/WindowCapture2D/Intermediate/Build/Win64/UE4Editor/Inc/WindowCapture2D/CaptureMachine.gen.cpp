// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "WindowCapture2D/Public/CaptureMachine.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCaptureMachine() {}
// Cross Module References
	WINDOWCAPTURE2D_API UFunction* Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_WindowCapture2D();
	ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
	WINDOWCAPTURE2D_API UClass* Z_Construct_UClass_UCaptureMachine_NoRegister();
	WINDOWCAPTURE2D_API UClass* Z_Construct_UClass_UCaptureMachine();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	WINDOWCAPTURE2D_API UScriptStruct* Z_Construct_UScriptStruct_FCaptureMachineProperties();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics
	{
		struct _Script_WindowCapture2D_eventCaptureMachineChangeTexture_Parms
		{
			UTexture2D* NewTexture;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_NewTexture;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics::NewProp_NewTexture = { "NewTexture", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_WindowCapture2D_eventCaptureMachineChangeTexture_Parms, NewTexture), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics::NewProp_NewTexture,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/CaptureMachine.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_WindowCapture2D, nullptr, "CaptureMachineChangeTexture__DelegateSignature", nullptr, nullptr, sizeof(_Script_WindowCapture2D_eventCaptureMachineChangeTexture_Parms), Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	DEFINE_FUNCTION(UCaptureMachine::execCreateTexture)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UTexture2D**)Z_Param__Result=P_THIS->CreateTexture();
		P_NATIVE_END;
	}
	void UCaptureMachine::StaticRegisterNativesUCaptureMachine()
	{
		UClass* Class = UCaptureMachine::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CreateTexture", &UCaptureMachine::execCreateTexture },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics
	{
		struct CaptureMachine_eventCreateTexture_Parms
		{
			UTexture2D* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CaptureMachine_eventCreateTexture_Parms, ReturnValue), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics::Function_MetaDataParams[] = {
		{ "Category", "WindowCapture2D" },
		{ "ModuleRelativePath", "Public/CaptureMachine.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCaptureMachine, nullptr, "CreateTexture", nullptr, nullptr, sizeof(CaptureMachine_eventCreateTexture_Parms), Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCaptureMachine_CreateTexture()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UCaptureMachine_NoRegister()
	{
		return UCaptureMachine::StaticClass();
	}
	struct Z_Construct_UClass_UCaptureMachine_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Properties_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Properties;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TextureTarget_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_TextureTarget;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ChangeTexture_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_ChangeTexture;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCaptureMachine_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_WindowCapture2D,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UCaptureMachine_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UCaptureMachine_CreateTexture, "CreateTexture" }, // 863560269
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCaptureMachine_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "CaptureMachine.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/CaptureMachine.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCaptureMachine_Statics::NewProp_Properties_MetaData[] = {
		{ "Category", "WindowCapture2D" },
		{ "ModuleRelativePath", "Public/CaptureMachine.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCaptureMachine_Statics::NewProp_Properties = { "Properties", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCaptureMachine, Properties), Z_Construct_UScriptStruct_FCaptureMachineProperties, METADATA_PARAMS(Z_Construct_UClass_UCaptureMachine_Statics::NewProp_Properties_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCaptureMachine_Statics::NewProp_Properties_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCaptureMachine_Statics::NewProp_TextureTarget_MetaData[] = {
		{ "Category", "SceneCapture" },
		{ "ModuleRelativePath", "Public/CaptureMachine.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCaptureMachine_Statics::NewProp_TextureTarget = { "TextureTarget", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCaptureMachine, TextureTarget), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UCaptureMachine_Statics::NewProp_TextureTarget_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCaptureMachine_Statics::NewProp_TextureTarget_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCaptureMachine_Statics::NewProp_ChangeTexture_MetaData[] = {
		{ "Category", "SceneCapture" },
		{ "ModuleRelativePath", "Public/CaptureMachine.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UCaptureMachine_Statics::NewProp_ChangeTexture = { "ChangeTexture", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCaptureMachine, ChangeTexture), Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UCaptureMachine_Statics::NewProp_ChangeTexture_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCaptureMachine_Statics::NewProp_ChangeTexture_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCaptureMachine_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCaptureMachine_Statics::NewProp_Properties,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCaptureMachine_Statics::NewProp_TextureTarget,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCaptureMachine_Statics::NewProp_ChangeTexture,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCaptureMachine_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCaptureMachine>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCaptureMachine_Statics::ClassParams = {
		&UCaptureMachine::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UCaptureMachine_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UCaptureMachine_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UCaptureMachine_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCaptureMachine_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCaptureMachine()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCaptureMachine_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCaptureMachine, 3214016385);
	template<> WINDOWCAPTURE2D_API UClass* StaticClass<UCaptureMachine>()
	{
		return UCaptureMachine::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCaptureMachine(Z_Construct_UClass_UCaptureMachine, &UCaptureMachine::StaticClass, TEXT("/Script/WindowCapture2D"), TEXT("UCaptureMachine"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCaptureMachine);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
