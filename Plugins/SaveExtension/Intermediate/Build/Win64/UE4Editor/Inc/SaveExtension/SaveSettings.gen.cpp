// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SaveExtension/Public/SaveSettings.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSaveSettings() {}
// Cross Module References
	SAVEEXTENSION_API UClass* Z_Construct_UClass_USaveSettings_NoRegister();
	SAVEEXTENSION_API UClass* Z_Construct_UClass_USaveSettings();
	DEVELOPERSETTINGS_API UClass* Z_Construct_UClass_UDeveloperSettings();
	UPackage* Z_Construct_UPackage__Script_SaveExtension();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	SAVEEXTENSION_API UClass* Z_Construct_UClass_USavePreset_NoRegister();
// End Cross Module References
	void USaveSettings::StaticRegisterNativesUSaveSettings()
	{
	}
	UClass* Z_Construct_UClass_USaveSettings_NoRegister()
	{
		return USaveSettings::StaticClass();
	}
	struct Z_Construct_UClass_USaveSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Preset_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_Preset;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bTickWithGameWorld_MetaData[];
#endif
		static void NewProp_bTickWithGameWorld_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bTickWithGameWorld;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USaveSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UDeveloperSettings,
		(UObject* (*)())Z_Construct_UPackage__Script_SaveExtension,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USaveSettings_Statics::Class_MetaDataParams[] = {
		{ "ClassGroupNames", "SaveExtension" },
		{ "DisplayName", "Save Extension" },
		{ "IncludePath", "SaveSettings.h" },
		{ "ModuleRelativePath", "Public/SaveSettings.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USaveSettings_Statics::NewProp_Preset_MetaData[] = {
		{ "Category", "Save Extension" },
		{ "DisplayName", "Preset" },
		{ "ModuleRelativePath", "Public/SaveSettings.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_USaveSettings_Statics::NewProp_Preset = { "Preset", nullptr, (EPropertyFlags)0x0024080000004001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USaveSettings, Preset), Z_Construct_UClass_USavePreset_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_USaveSettings_Statics::NewProp_Preset_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USaveSettings_Statics::NewProp_Preset_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USaveSettings_Statics::NewProp_bTickWithGameWorld_MetaData[] = {
		{ "Category", "Save Extension" },
		{ "Comment", "// If true SaveManager will tick with the world. If game is paused, saving process may be interrupted.\n" },
		{ "ModuleRelativePath", "Public/SaveSettings.h" },
		{ "ToolTip", "If true SaveManager will tick with the world. If game is paused, saving process may be interrupted." },
	};
#endif
	void Z_Construct_UClass_USaveSettings_Statics::NewProp_bTickWithGameWorld_SetBit(void* Obj)
	{
		((USaveSettings*)Obj)->bTickWithGameWorld = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USaveSettings_Statics::NewProp_bTickWithGameWorld = { "bTickWithGameWorld", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(USaveSettings), &Z_Construct_UClass_USaveSettings_Statics::NewProp_bTickWithGameWorld_SetBit, METADATA_PARAMS(Z_Construct_UClass_USaveSettings_Statics::NewProp_bTickWithGameWorld_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USaveSettings_Statics::NewProp_bTickWithGameWorld_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USaveSettings_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USaveSettings_Statics::NewProp_Preset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USaveSettings_Statics::NewProp_bTickWithGameWorld,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_USaveSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USaveSettings>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USaveSettings_Statics::ClassParams = {
		&USaveSettings::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_USaveSettings_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_USaveSettings_Statics::PropPointers),
		0,
		0x001000A6u,
		METADATA_PARAMS(Z_Construct_UClass_USaveSettings_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USaveSettings_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USaveSettings()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USaveSettings_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USaveSettings, 1911330569);
	template<> SAVEEXTENSION_API UClass* StaticClass<USaveSettings>()
	{
		return USaveSettings::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_USaveSettings(Z_Construct_UClass_USaveSettings, &USaveSettings::StaticClass, TEXT("/Script/SaveExtension"), TEXT("USaveSettings"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USaveSettings);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
