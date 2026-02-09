// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Text3D/Public/Text3DActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeText3DActor() {}
// Cross Module References
	TEXT3D_API UClass* Z_Construct_UClass_AText3DActor_NoRegister();
	TEXT3D_API UClass* Z_Construct_UClass_AText3DActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_Text3D();
	TEXT3D_API UClass* Z_Construct_UClass_UText3DComponent_NoRegister();
// End Cross Module References
	void AText3DActor::StaticRegisterNativesAText3DActor()
	{
	}
	UClass* Z_Construct_UClass_AText3DActor_NoRegister()
	{
		return AText3DActor::StaticClass();
	}
	struct Z_Construct_UClass_AText3DActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Text3DComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Text3DComponent;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AText3DActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_Text3D,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AText3DActor_Statics::Class_MetaDataParams[] = {
		{ "ClassGroupNames", "Text3D" },
		{ "ComponentWrapperClass", "" },
		{ "DisplayName", "Text 3D" },
		{ "IncludePath", "Text3DActor.h" },
		{ "ModuleRelativePath", "Public/Text3DActor.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AText3DActor_Statics::NewProp_Text3DComponent_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Text" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Text3DActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AText3DActor_Statics::NewProp_Text3DComponent = { "Text3DComponent", nullptr, (EPropertyFlags)0x00400000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AText3DActor, Text3DComponent), Z_Construct_UClass_UText3DComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AText3DActor_Statics::NewProp_Text3DComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AText3DActor_Statics::NewProp_Text3DComponent_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AText3DActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AText3DActor_Statics::NewProp_Text3DComponent,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AText3DActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AText3DActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AText3DActor_Statics::ClassParams = {
		&AText3DActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AText3DActor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AText3DActor_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AText3DActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AText3DActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AText3DActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AText3DActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AText3DActor, 182586564);
	template<> TEXT3D_API UClass* StaticClass<AText3DActor>()
	{
		return AText3DActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AText3DActor(Z_Construct_UClass_AText3DActor, &AText3DActor::StaticClass, TEXT("/Script/Text3D"), TEXT("AText3DActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AText3DActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
