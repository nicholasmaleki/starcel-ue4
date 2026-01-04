// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "WindowCapture2D/Public/WindowCaptureActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWindowCaptureActor() {}
// Cross Module References
	WINDOWCAPTURE2D_API UFunction* Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_WindowCapture2D();
	ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
	WINDOWCAPTURE2D_API UClass* Z_Construct_UClass_AWindowCaptureActor_NoRegister();
	WINDOWCAPTURE2D_API UClass* Z_Construct_UClass_AWindowCaptureActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	WINDOWCAPTURE2D_API UScriptStruct* Z_Construct_UScriptStruct_FCaptureMachineProperties();
	WINDOWCAPTURE2D_API UClass* Z_Construct_UClass_UCaptureMachine_NoRegister();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics
	{
		struct _Script_WindowCapture2D_eventWindowCaptureActorChangeTexture_Parms
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
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics::NewProp_NewTexture = { "NewTexture", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_WindowCapture2D_eventWindowCaptureActorChangeTexture_Parms, NewTexture), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics::NewProp_NewTexture,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/WindowCaptureActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_WindowCapture2D, nullptr, "WindowCaptureActorChangeTexture__DelegateSignature", nullptr, nullptr, sizeof(_Script_WindowCapture2D_eventWindowCaptureActorChangeTexture_Parms), Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	DEFINE_FUNCTION(AWindowCaptureActor::execOnChangeTexture)
	{
		P_GET_OBJECT(UTexture2D,Z_Param_NewTexture);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnChangeTexture(Z_Param_NewTexture);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AWindowCaptureActor::execStart)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UTexture2D**)Z_Param__Result=P_THIS->Start();
		P_NATIVE_END;
	}
	void AWindowCaptureActor::StaticRegisterNativesAWindowCaptureActor()
	{
		UClass* Class = AWindowCaptureActor::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnChangeTexture", &AWindowCaptureActor::execOnChangeTexture },
			{ "Start", &AWindowCaptureActor::execStart },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics
	{
		struct WindowCaptureActor_eventOnChangeTexture_Parms
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
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics::NewProp_NewTexture = { "NewTexture", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(WindowCaptureActor_eventOnChangeTexture_Parms, NewTexture), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics::NewProp_NewTexture,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/WindowCaptureActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AWindowCaptureActor, nullptr, "OnChangeTexture", nullptr, nullptr, sizeof(WindowCaptureActor_eventOnChangeTexture_Parms), Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AWindowCaptureActor_Start_Statics
	{
		struct WindowCaptureActor_eventStart_Parms
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
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AWindowCaptureActor_Start_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(WindowCaptureActor_eventStart_Parms, ReturnValue), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AWindowCaptureActor_Start_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AWindowCaptureActor_Start_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AWindowCaptureActor_Start_Statics::Function_MetaDataParams[] = {
		{ "Category", "WindowCapture2D" },
		{ "ModuleRelativePath", "Public/WindowCaptureActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AWindowCaptureActor_Start_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AWindowCaptureActor, nullptr, "Start", nullptr, nullptr, sizeof(WindowCaptureActor_eventStart_Parms), Z_Construct_UFunction_AWindowCaptureActor_Start_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AWindowCaptureActor_Start_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AWindowCaptureActor_Start_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AWindowCaptureActor_Start_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AWindowCaptureActor_Start()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AWindowCaptureActor_Start_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_AWindowCaptureActor_NoRegister()
	{
		return AWindowCaptureActor::StaticClass();
	}
	struct Z_Construct_UClass_AWindowCaptureActor_Statics
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
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CaptureMachine_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CaptureMachine;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AWindowCaptureActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_WindowCapture2D,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_AWindowCaptureActor_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture, "OnChangeTexture" }, // 2408289900
		{ &Z_Construct_UFunction_AWindowCaptureActor_Start, "Start" }, // 94265268
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWindowCaptureActor_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "WindowCaptureActor.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/WindowCaptureActor.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_Properties_MetaData[] = {
		{ "Category", "WindowCapture2D" },
		{ "ModuleRelativePath", "Public/WindowCaptureActor.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_Properties = { "Properties", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AWindowCaptureActor, Properties), Z_Construct_UScriptStruct_FCaptureMachineProperties, METADATA_PARAMS(Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_Properties_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_Properties_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_TextureTarget_MetaData[] = {
		{ "Category", "SceneCapture" },
		{ "ModuleRelativePath", "Public/WindowCaptureActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_TextureTarget = { "TextureTarget", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AWindowCaptureActor, TextureTarget), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_TextureTarget_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_TextureTarget_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_ChangeTexture_MetaData[] = {
		{ "Category", "SceneCapture" },
		{ "ModuleRelativePath", "Public/WindowCaptureActor.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_ChangeTexture = { "ChangeTexture", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AWindowCaptureActor, ChangeTexture), Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_ChangeTexture_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_ChangeTexture_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_CaptureMachine_MetaData[] = {
		{ "ModuleRelativePath", "Public/WindowCaptureActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_CaptureMachine = { "CaptureMachine", nullptr, (EPropertyFlags)0x0020080000002000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AWindowCaptureActor, CaptureMachine), Z_Construct_UClass_UCaptureMachine_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_CaptureMachine_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_CaptureMachine_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AWindowCaptureActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_Properties,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_TextureTarget,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_ChangeTexture,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_CaptureMachine,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AWindowCaptureActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AWindowCaptureActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AWindowCaptureActor_Statics::ClassParams = {
		&AWindowCaptureActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AWindowCaptureActor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AWindowCaptureActor_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AWindowCaptureActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AWindowCaptureActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AWindowCaptureActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AWindowCaptureActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AWindowCaptureActor, 124510214);
	template<> WINDOWCAPTURE2D_API UClass* StaticClass<AWindowCaptureActor>()
	{
		return AWindowCaptureActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AWindowCaptureActor(Z_Construct_UClass_AWindowCaptureActor, &AWindowCaptureActor::StaticClass, TEXT("/Script/WindowCapture2D"), TEXT("AWindowCaptureActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AWindowCaptureActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
