// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LWCExtreme/Public/LWCExtremeSettingsLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLWCExtremeSettingsLibrary() {}
// Cross Module References
	LWCEXTREME_API UClass* Z_Construct_UClass_ULWCExtremeSettingsLibrary_NoRegister();
	LWCEXTREME_API UClass* Z_Construct_UClass_ULWCExtremeSettingsLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_LWCExtreme();
	LWCEXTREME_API UClass* Z_Construct_UClass_ULWCExtremeSettings_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(ULWCExtremeSettingsLibrary::execGetMaxStringLength)
	{
		P_GET_OBJECT(ULWCExtremeSettings,Z_Param_Settings);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=ULWCExtremeSettingsLibrary::GetMaxStringLength(Z_Param_Settings);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeSettingsLibrary::execGetDefaultPrecision)
	{
		P_GET_OBJECT(ULWCExtremeSettings,Z_Param_Settings);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=ULWCExtremeSettingsLibrary::GetDefaultPrecision(Z_Param_Settings);
		P_NATIVE_END;
	}
	void ULWCExtremeSettingsLibrary::StaticRegisterNativesULWCExtremeSettingsLibrary()
	{
		UClass* Class = ULWCExtremeSettingsLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetDefaultPrecision", &ULWCExtremeSettingsLibrary::execGetDefaultPrecision },
			{ "GetMaxStringLength", &ULWCExtremeSettingsLibrary::execGetMaxStringLength },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetDefaultPrecision_Statics
	{
		struct LWCExtremeSettingsLibrary_eventGetDefaultPrecision_Parms
		{
			const ULWCExtremeSettings* Settings;
			int32 ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Settings_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Settings;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetDefaultPrecision_Statics::NewProp_Settings_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetDefaultPrecision_Statics::NewProp_Settings = { "Settings", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeSettingsLibrary_eventGetDefaultPrecision_Parms, Settings), Z_Construct_UClass_ULWCExtremeSettings_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetDefaultPrecision_Statics::NewProp_Settings_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetDefaultPrecision_Statics::NewProp_Settings_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetDefaultPrecision_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeSettingsLibrary_eventGetDefaultPrecision_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetDefaultPrecision_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetDefaultPrecision_Statics::NewProp_Settings,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetDefaultPrecision_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetDefaultPrecision_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Settings" },
		{ "ModuleRelativePath", "Public/LWCExtremeSettingsLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetDefaultPrecision_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeSettingsLibrary, nullptr, "GetDefaultPrecision", nullptr, nullptr, sizeof(LWCExtremeSettingsLibrary_eventGetDefaultPrecision_Parms), Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetDefaultPrecision_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetDefaultPrecision_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetDefaultPrecision_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetDefaultPrecision_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetDefaultPrecision()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetDefaultPrecision_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetMaxStringLength_Statics
	{
		struct LWCExtremeSettingsLibrary_eventGetMaxStringLength_Parms
		{
			const ULWCExtremeSettings* Settings;
			int32 ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Settings_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Settings;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetMaxStringLength_Statics::NewProp_Settings_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetMaxStringLength_Statics::NewProp_Settings = { "Settings", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeSettingsLibrary_eventGetMaxStringLength_Parms, Settings), Z_Construct_UClass_ULWCExtremeSettings_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetMaxStringLength_Statics::NewProp_Settings_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetMaxStringLength_Statics::NewProp_Settings_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetMaxStringLength_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeSettingsLibrary_eventGetMaxStringLength_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetMaxStringLength_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetMaxStringLength_Statics::NewProp_Settings,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetMaxStringLength_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetMaxStringLength_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Settings" },
		{ "ModuleRelativePath", "Public/LWCExtremeSettingsLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetMaxStringLength_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeSettingsLibrary, nullptr, "GetMaxStringLength", nullptr, nullptr, sizeof(LWCExtremeSettingsLibrary_eventGetMaxStringLength_Parms), Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetMaxStringLength_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetMaxStringLength_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetMaxStringLength_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetMaxStringLength_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetMaxStringLength()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetMaxStringLength_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ULWCExtremeSettingsLibrary_NoRegister()
	{
		return ULWCExtremeSettingsLibrary::StaticClass();
	}
	struct Z_Construct_UClass_ULWCExtremeSettingsLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULWCExtremeSettingsLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_LWCExtreme,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULWCExtremeSettingsLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetDefaultPrecision, "GetDefaultPrecision" }, // 1180006655
		{ &Z_Construct_UFunction_ULWCExtremeSettingsLibrary_GetMaxStringLength, "GetMaxStringLength" }, // 3921494181
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULWCExtremeSettingsLibrary_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "LWCExtremeSettingsLibrary.h" },
		{ "ModuleRelativePath", "Public/LWCExtremeSettingsLibrary.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULWCExtremeSettingsLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULWCExtremeSettingsLibrary>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULWCExtremeSettingsLibrary_Statics::ClassParams = {
		&ULWCExtremeSettingsLibrary::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_ULWCExtremeSettingsLibrary_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULWCExtremeSettingsLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULWCExtremeSettingsLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULWCExtremeSettingsLibrary_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULWCExtremeSettingsLibrary, 2896413489);
	template<> LWCEXTREME_API UClass* StaticClass<ULWCExtremeSettingsLibrary>()
	{
		return ULWCExtremeSettingsLibrary::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULWCExtremeSettingsLibrary(Z_Construct_UClass_ULWCExtremeSettingsLibrary, &ULWCExtremeSettingsLibrary::StaticClass, TEXT("/Script/LWCExtreme"), TEXT("ULWCExtremeSettingsLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULWCExtremeSettingsLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
