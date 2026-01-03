// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RuntimeImageLoader/Private/TextureFactory/RuntimeTextureFactory.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRuntimeTextureFactory() {}
// Cross Module References
	RUNTIMEIMAGELOADER_API UClass* Z_Construct_UClass_URuntimeTextureFactory_NoRegister();
	RUNTIMEIMAGELOADER_API UClass* Z_Construct_UClass_URuntimeTextureFactory();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_RuntimeImageLoader();
// End Cross Module References
	void URuntimeTextureFactory::StaticRegisterNativesURuntimeTextureFactory()
	{
	}
	UClass* Z_Construct_UClass_URuntimeTextureFactory_NoRegister()
	{
		return URuntimeTextureFactory::StaticClass();
	}
	struct Z_Construct_UClass_URuntimeTextureFactory_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_URuntimeTextureFactory_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_RuntimeImageLoader,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeTextureFactory_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "TextureFactory/RuntimeTextureFactory.h" },
		{ "ModuleRelativePath", "Private/TextureFactory/RuntimeTextureFactory.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_URuntimeTextureFactory_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URuntimeTextureFactory>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_URuntimeTextureFactory_Statics::ClassParams = {
		&URuntimeTextureFactory::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_URuntimeTextureFactory_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeTextureFactory_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_URuntimeTextureFactory()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_URuntimeTextureFactory_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(URuntimeTextureFactory, 1526432150);
	template<> RUNTIMEIMAGELOADER_API UClass* StaticClass<URuntimeTextureFactory>()
	{
		return URuntimeTextureFactory::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_URuntimeTextureFactory(Z_Construct_UClass_URuntimeTextureFactory, &URuntimeTextureFactory::StaticClass, TEXT("/Script/RuntimeImageLoader"), TEXT("URuntimeTextureFactory"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(URuntimeTextureFactory);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
