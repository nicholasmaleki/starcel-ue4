// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Test/Private/Helpers/TestGameInstance.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTestGameInstance() {}
// Cross Module References
	SAVEEXTENSIONTEST_API UClass* Z_Construct_UClass_UTestGameInstance_NoRegister();
	SAVEEXTENSIONTEST_API UClass* Z_Construct_UClass_UTestGameInstance();
	ENGINE_API UClass* Z_Construct_UClass_UGameInstance();
	UPackage* Z_Construct_UPackage__Script_SaveExtensionTest();
// End Cross Module References
	void UTestGameInstance::StaticRegisterNativesUTestGameInstance()
	{
	}
	UClass* Z_Construct_UClass_UTestGameInstance_NoRegister()
	{
		return UTestGameInstance::StaticClass();
	}
	struct Z_Construct_UClass_UTestGameInstance_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bMyBool_MetaData[];
#endif
		static void NewProp_bMyBool_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bMyBool;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UTestGameInstance_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UGameInstance,
		(UObject* (*)())Z_Construct_UPackage__Script_SaveExtensionTest,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTestGameInstance_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Helpers/TestGameInstance.h" },
		{ "ModuleRelativePath", "Private/Helpers/TestGameInstance.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTestGameInstance_Statics::NewProp_bMyBool_MetaData[] = {
		{ "ModuleRelativePath", "Private/Helpers/TestGameInstance.h" },
	};
#endif
	void Z_Construct_UClass_UTestGameInstance_Statics::NewProp_bMyBool_SetBit(void* Obj)
	{
		((UTestGameInstance*)Obj)->bMyBool = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UTestGameInstance_Statics::NewProp_bMyBool = { "bMyBool", nullptr, (EPropertyFlags)0x0010000001000000, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UTestGameInstance), &Z_Construct_UClass_UTestGameInstance_Statics::NewProp_bMyBool_SetBit, METADATA_PARAMS(Z_Construct_UClass_UTestGameInstance_Statics::NewProp_bMyBool_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UTestGameInstance_Statics::NewProp_bMyBool_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UTestGameInstance_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTestGameInstance_Statics::NewProp_bMyBool,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UTestGameInstance_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTestGameInstance>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UTestGameInstance_Statics::ClassParams = {
		&UTestGameInstance::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UTestGameInstance_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UTestGameInstance_Statics::PropPointers),
		0,
		0x008000A8u,
		METADATA_PARAMS(Z_Construct_UClass_UTestGameInstance_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UTestGameInstance_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UTestGameInstance()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UTestGameInstance_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UTestGameInstance, 4075153187);
	template<> SAVEEXTENSIONTEST_API UClass* StaticClass<UTestGameInstance>()
	{
		return UTestGameInstance::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UTestGameInstance(Z_Construct_UClass_UTestGameInstance, &UTestGameInstance::StaticClass, TEXT("/Script/SaveExtensionTest"), TEXT("UTestGameInstance"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UTestGameInstance);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
