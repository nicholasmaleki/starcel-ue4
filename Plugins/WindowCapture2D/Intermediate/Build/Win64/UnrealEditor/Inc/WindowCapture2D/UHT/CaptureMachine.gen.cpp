// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "WindowCapture2D/Public/CaptureMachine.h"
#include "WindowCapture2D/Public/CaptureMachineProperties.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCaptureMachine() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
	UPackage* Z_Construct_UPackage__Script_WindowCapture2D();
	WINDOWCAPTURE2D_API UClass* Z_Construct_UClass_UCaptureMachine();
	WINDOWCAPTURE2D_API UClass* Z_Construct_UClass_UCaptureMachine_NoRegister();
	WINDOWCAPTURE2D_API UFunction* Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature();
	WINDOWCAPTURE2D_API UScriptStruct* Z_Construct_UScriptStruct_FCaptureMachineProperties();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics
	{
		struct _Script_WindowCapture2D_eventCaptureMachineChangeTexture_Parms
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
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics::NewProp_NewTexture = { "NewTexture", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(_Script_WindowCapture2D_eventCaptureMachineChangeTexture_Parms, NewTexture), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics::NewProp_NewTexture,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/CaptureMachine.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_WindowCapture2D, nullptr, "CaptureMachineChangeTexture__DelegateSignature", nullptr, nullptr, sizeof(Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics::_Script_WindowCapture2D_eventCaptureMachineChangeTexture_Parms), Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature_Statics::FuncParams);
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
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(CaptureMachine_eventCreateTexture_Parms, ReturnValue), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics::Function_MetaDataParams[] = {
		{ "Category", "WindowCapture2D" },
		{ "ModuleRelativePath", "Public/CaptureMachine.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCaptureMachine, nullptr, "CreateTexture", nullptr, nullptr, sizeof(Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics::CaptureMachine_eventCreateTexture_Parms), Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCaptureMachine_CreateTexture()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCaptureMachine_CreateTexture_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCaptureMachine);
	UClass* Z_Construct_UClass_UCaptureMachine_NoRegister()
	{
		return UCaptureMachine::StaticClass();
	}
	struct Z_Construct_UClass_UCaptureMachine_Statics
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
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCaptureMachine_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_WindowCapture2D,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UCaptureMachine_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UCaptureMachine_CreateTexture, "CreateTexture" }, // 1101362394
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCaptureMachine_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "CaptureMachine.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/CaptureMachine.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCaptureMachine_Statics::NewProp_Properties_MetaData[] = {
		{ "Category", "WindowCapture2D" },
		{ "ModuleRelativePath", "Public/CaptureMachine.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCaptureMachine_Statics::NewProp_Properties = { "Properties", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UCaptureMachine, Properties), Z_Construct_UScriptStruct_FCaptureMachineProperties, METADATA_PARAMS(Z_Construct_UClass_UCaptureMachine_Statics::NewProp_Properties_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCaptureMachine_Statics::NewProp_Properties_MetaData)) }; // 1111378952
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCaptureMachine_Statics::NewProp_TextureTarget_MetaData[] = {
		{ "Category", "SceneCapture" },
		{ "ModuleRelativePath", "Public/CaptureMachine.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCaptureMachine_Statics::NewProp_TextureTarget = { "TextureTarget", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UCaptureMachine, TextureTarget), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UCaptureMachine_Statics::NewProp_TextureTarget_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCaptureMachine_Statics::NewProp_TextureTarget_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCaptureMachine_Statics::NewProp_ChangeTexture_MetaData[] = {
		{ "Category", "SceneCapture" },
		{ "ModuleRelativePath", "Public/CaptureMachine.h" },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UCaptureMachine_Statics::NewProp_ChangeTexture = { "ChangeTexture", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UCaptureMachine, ChangeTexture), Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UCaptureMachine_Statics::NewProp_ChangeTexture_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCaptureMachine_Statics::NewProp_ChangeTexture_MetaData)) }; // 861174616
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCaptureMachine_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCaptureMachine_Statics::NewProp_Properties,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCaptureMachine_Statics::NewProp_TextureTarget,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCaptureMachine_Statics::NewProp_ChangeTexture,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCaptureMachine_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCaptureMachine>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UCaptureMachine_Statics::ClassParams = {
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
		if (!Z_Registration_Info_UClass_UCaptureMachine.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCaptureMachine.OuterSingleton, Z_Construct_UClass_UCaptureMachine_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UCaptureMachine.OuterSingleton;
	}
	template<> WINDOWCAPTURE2D_API UClass* StaticClass<UCaptureMachine>()
	{
		return UCaptureMachine::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCaptureMachine);
	UCaptureMachine::~UCaptureMachine() {}
	struct Z_CompiledInDeferFile_FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UCaptureMachine, UCaptureMachine::StaticClass, TEXT("UCaptureMachine"), &Z_Registration_Info_UClass_UCaptureMachine, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCaptureMachine), 3788431885U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_3111160287(TEXT("/Script/WindowCapture2D"),
		Z_CompiledInDeferFile_FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
