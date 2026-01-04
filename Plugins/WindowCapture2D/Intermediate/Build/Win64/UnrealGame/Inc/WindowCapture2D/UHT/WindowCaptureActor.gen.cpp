// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "WindowCapture2D/Public/WindowCaptureActor.h"
#include "WindowCapture2D/Public/CaptureMachineProperties.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWindowCaptureActor() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
	UPackage* Z_Construct_UPackage__Script_WindowCapture2D();
	WINDOWCAPTURE2D_API UClass* Z_Construct_UClass_AWindowCaptureActor();
	WINDOWCAPTURE2D_API UClass* Z_Construct_UClass_AWindowCaptureActor_NoRegister();
	WINDOWCAPTURE2D_API UClass* Z_Construct_UClass_UCaptureMachine_NoRegister();
	WINDOWCAPTURE2D_API UFunction* Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature();
	WINDOWCAPTURE2D_API UScriptStruct* Z_Construct_UScriptStruct_FCaptureMachineProperties();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics
	{
		struct _Script_WindowCapture2D_eventWindowCaptureActorChangeTexture_Parms
		{
			UTexture2D* NewTexture;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_NewTexture;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics::NewProp_NewTexture = { "NewTexture", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(_Script_WindowCapture2D_eventWindowCaptureActorChangeTexture_Parms, NewTexture), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics::NewProp_NewTexture,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/WindowCaptureActor.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_WindowCapture2D, nullptr, "WindowCaptureActorChangeTexture__DelegateSignature", nullptr, nullptr, sizeof(Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics::_Script_WindowCapture2D_eventWindowCaptureActorChangeTexture_Parms), Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature_Statics::FuncParams);
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
		static const UECodeGen_Private::FObjectPropertyParams NewProp_NewTexture;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics::NewProp_NewTexture = { "NewTexture", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(WindowCaptureActor_eventOnChangeTexture_Parms, NewTexture), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics::NewProp_NewTexture,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/WindowCaptureActor.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AWindowCaptureActor, nullptr, "OnChangeTexture", nullptr, nullptr, sizeof(Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics::WindowCaptureActor_eventOnChangeTexture_Parms), Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AWindowCaptureActor_Start_Statics
	{
		struct WindowCaptureActor_eventStart_Parms
		{
			UTexture2D* ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AWindowCaptureActor_Start_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(WindowCaptureActor_eventStart_Parms, ReturnValue), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AWindowCaptureActor_Start_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AWindowCaptureActor_Start_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AWindowCaptureActor_Start_Statics::Function_MetaDataParams[] = {
		{ "Category", "WindowCapture2D" },
		{ "ModuleRelativePath", "Public/WindowCaptureActor.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AWindowCaptureActor_Start_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AWindowCaptureActor, nullptr, "Start", nullptr, nullptr, sizeof(Z_Construct_UFunction_AWindowCaptureActor_Start_Statics::WindowCaptureActor_eventStart_Parms), Z_Construct_UFunction_AWindowCaptureActor_Start_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AWindowCaptureActor_Start_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AWindowCaptureActor_Start_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AWindowCaptureActor_Start_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AWindowCaptureActor_Start()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AWindowCaptureActor_Start_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AWindowCaptureActor);
	UClass* Z_Construct_UClass_AWindowCaptureActor_NoRegister()
	{
		return AWindowCaptureActor::StaticClass();
	}
	struct Z_Construct_UClass_AWindowCaptureActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Properties_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Properties;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TextureTarget_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_TextureTarget;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ChangeTexture_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_ChangeTexture;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CaptureMachine_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_CaptureMachine;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AWindowCaptureActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_WindowCapture2D,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_AWindowCaptureActor_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AWindowCaptureActor_OnChangeTexture, "OnChangeTexture" }, // 2809968651
		{ &Z_Construct_UFunction_AWindowCaptureActor_Start, "Start" }, // 3958298678
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWindowCaptureActor_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "WindowCaptureActor.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/WindowCaptureActor.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_Properties_MetaData[] = {
		{ "Category", "WindowCapture2D" },
		{ "ModuleRelativePath", "Public/WindowCaptureActor.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_Properties = { "Properties", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AWindowCaptureActor, Properties), Z_Construct_UScriptStruct_FCaptureMachineProperties, METADATA_PARAMS(Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_Properties_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_Properties_MetaData)) }; // 1111378952
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_TextureTarget_MetaData[] = {
		{ "Category", "SceneCapture" },
		{ "ModuleRelativePath", "Public/WindowCaptureActor.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_TextureTarget = { "TextureTarget", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AWindowCaptureActor, TextureTarget), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_TextureTarget_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_TextureTarget_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_ChangeTexture_MetaData[] = {
		{ "Category", "SceneCapture" },
		{ "ModuleRelativePath", "Public/WindowCaptureActor.h" },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_ChangeTexture = { "ChangeTexture", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AWindowCaptureActor, ChangeTexture), Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_ChangeTexture_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_ChangeTexture_MetaData)) }; // 2464096871
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_CaptureMachine_MetaData[] = {
		{ "ModuleRelativePath", "Public/WindowCaptureActor.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_CaptureMachine = { "CaptureMachine", nullptr, (EPropertyFlags)0x0020080000002000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AWindowCaptureActor, CaptureMachine), Z_Construct_UClass_UCaptureMachine_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_CaptureMachine_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_CaptureMachine_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AWindowCaptureActor_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_Properties,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_TextureTarget,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_ChangeTexture,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWindowCaptureActor_Statics::NewProp_CaptureMachine,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AWindowCaptureActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AWindowCaptureActor>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AWindowCaptureActor_Statics::ClassParams = {
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
		if (!Z_Registration_Info_UClass_AWindowCaptureActor.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AWindowCaptureActor.OuterSingleton, Z_Construct_UClass_AWindowCaptureActor_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AWindowCaptureActor.OuterSingleton;
	}
	template<> WINDOWCAPTURE2D_API UClass* StaticClass<AWindowCaptureActor>()
	{
		return AWindowCaptureActor::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AWindowCaptureActor);
	AWindowCaptureActor::~AWindowCaptureActor() {}
	struct Z_CompiledInDeferFile_FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AWindowCaptureActor, AWindowCaptureActor::StaticClass, TEXT("AWindowCaptureActor"), &Z_Registration_Info_UClass_AWindowCaptureActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AWindowCaptureActor), 3930498669U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_4025527909(TEXT("/Script/WindowCapture2D"),
		Z_CompiledInDeferFile_FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
