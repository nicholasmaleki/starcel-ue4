// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Text3DEditor/Public/ActorFactoryText3D.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeActorFactoryText3D() {}
// Cross Module References
	TEXT3DEDITOR_API UClass* Z_Construct_UClass_UActorFactoryText3D_NoRegister();
	TEXT3DEDITOR_API UClass* Z_Construct_UClass_UActorFactoryText3D();
	UNREALED_API UClass* Z_Construct_UClass_UActorFactory();
	UPackage* Z_Construct_UPackage__Script_Text3DEditor();
// End Cross Module References
	void UActorFactoryText3D::StaticRegisterNativesUActorFactoryText3D()
	{
	}
	UClass* Z_Construct_UClass_UActorFactoryText3D_NoRegister()
	{
		return UActorFactoryText3D::StaticClass();
	}
	struct Z_Construct_UClass_UActorFactoryText3D_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UActorFactoryText3D_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorFactory,
		(UObject* (*)())Z_Construct_UPackage__Script_Text3DEditor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UActorFactoryText3D_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Object" },
		{ "IncludePath", "ActorFactoryText3D.h" },
		{ "ModuleRelativePath", "Public/ActorFactoryText3D.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UActorFactoryText3D_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UActorFactoryText3D>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UActorFactoryText3D_Statics::ClassParams = {
		&UActorFactoryText3D::StaticClass,
		"Editor",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x000830ACu,
		METADATA_PARAMS(Z_Construct_UClass_UActorFactoryText3D_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UActorFactoryText3D_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UActorFactoryText3D()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UActorFactoryText3D_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UActorFactoryText3D, 3149455864);
	template<> TEXT3DEDITOR_API UClass* StaticClass<UActorFactoryText3D>()
	{
		return UActorFactoryText3D::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UActorFactoryText3D(Z_Construct_UClass_UActorFactoryText3D, &UActorFactoryText3D::StaticClass, TEXT("/Script/Text3DEditor"), TEXT("UActorFactoryText3D"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UActorFactoryText3D);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
