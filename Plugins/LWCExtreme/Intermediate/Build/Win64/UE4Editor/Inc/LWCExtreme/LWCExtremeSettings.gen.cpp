// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LWCExtreme/Public/LWCExtremeSettings.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLWCExtremeSettings() {}
// Cross Module References
	LWCEXTREME_API UClass* Z_Construct_UClass_ULWCExtremeSettings_NoRegister();
	LWCEXTREME_API UClass* Z_Construct_UClass_ULWCExtremeSettings();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_LWCExtreme();
// End Cross Module References
	void ULWCExtremeSettings::StaticRegisterNativesULWCExtremeSettings()
	{
	}
	UClass* Z_Construct_UClass_ULWCExtremeSettings_NoRegister()
	{
		return ULWCExtremeSettings::StaticClass();
	}
	struct Z_Construct_UClass_ULWCExtremeSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DefaultPrecision_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_DefaultPrecision;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaxStringLength_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_MaxStringLength;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULWCExtremeSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_LWCExtreme,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULWCExtremeSettings_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "LWCExtremeSettings.h" },
		{ "ModuleRelativePath", "Public/LWCExtremeSettings.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULWCExtremeSettings_Statics::NewProp_DefaultPrecision_MetaData[] = {
		{ "Category", "LWCExtreme|Settings" },
		{ "Comment", "// Runtime-configurable precision for FHybridNumber calculations\n" },
		{ "ModuleRelativePath", "Public/LWCExtremeSettings.h" },
		{ "ToolTip", "Runtime-configurable precision for FHybridNumber calculations" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_ULWCExtremeSettings_Statics::NewProp_DefaultPrecision = { "DefaultPrecision", nullptr, (EPropertyFlags)0x0010000000004005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULWCExtremeSettings, DefaultPrecision), METADATA_PARAMS(Z_Construct_UClass_ULWCExtremeSettings_Statics::NewProp_DefaultPrecision_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULWCExtremeSettings_Statics::NewProp_DefaultPrecision_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULWCExtremeSettings_Statics::NewProp_MaxStringLength_MetaData[] = {
		{ "Category", "LWCExtreme|Settings" },
		{ "Comment", "// Maximum allowed digits for FLargeString or similar large data types\n" },
		{ "ModuleRelativePath", "Public/LWCExtremeSettings.h" },
		{ "ToolTip", "Maximum allowed digits for FLargeString or similar large data types" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_ULWCExtremeSettings_Statics::NewProp_MaxStringLength = { "MaxStringLength", nullptr, (EPropertyFlags)0x0010000000004005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULWCExtremeSettings, MaxStringLength), METADATA_PARAMS(Z_Construct_UClass_ULWCExtremeSettings_Statics::NewProp_MaxStringLength_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULWCExtremeSettings_Statics::NewProp_MaxStringLength_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULWCExtremeSettings_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULWCExtremeSettings_Statics::NewProp_DefaultPrecision,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULWCExtremeSettings_Statics::NewProp_MaxStringLength,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULWCExtremeSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULWCExtremeSettings>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULWCExtremeSettings_Statics::ClassParams = {
		&ULWCExtremeSettings::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ULWCExtremeSettings_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ULWCExtremeSettings_Statics::PropPointers),
		0,
		0x001000A6u,
		METADATA_PARAMS(Z_Construct_UClass_ULWCExtremeSettings_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULWCExtremeSettings_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULWCExtremeSettings()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULWCExtremeSettings_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULWCExtremeSettings, 1118943784);
	template<> LWCEXTREME_API UClass* StaticClass<ULWCExtremeSettings>()
	{
		return ULWCExtremeSettings::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULWCExtremeSettings(Z_Construct_UClass_ULWCExtremeSettings, &ULWCExtremeSettings::StaticClass, TEXT("/Script/LWCExtreme"), TEXT("ULWCExtremeSettings"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULWCExtremeSettings);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
