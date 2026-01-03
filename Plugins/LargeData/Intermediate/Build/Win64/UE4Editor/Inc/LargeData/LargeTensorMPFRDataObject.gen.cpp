// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LargeData/Public/LargeTensorMPFRDataObject.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLargeTensorMPFRDataObject() {}
// Cross Module References
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeTensorMPFRDataObject_NoRegister();
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeTensorMPFRDataObject();
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeDataObject();
	UPackage* Z_Construct_UPackage__Script_LargeData();
// End Cross Module References
	void ULargeTensorMPFRDataObject::StaticRegisterNativesULargeTensorMPFRDataObject()
	{
	}
	UClass* Z_Construct_UClass_ULargeTensorMPFRDataObject_NoRegister()
	{
		return ULargeTensorMPFRDataObject::StaticClass();
	}
	struct Z_Construct_UClass_ULargeTensorMPFRDataObject_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULargeTensorMPFRDataObject_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ULargeDataObject,
		(UObject* (*)())Z_Construct_UPackage__Script_LargeData,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULargeTensorMPFRDataObject_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Concrete ULargeDataObject subclass storing an xtensor xarray of mpfr_float\n */" },
		{ "IncludePath", "LargeTensorMPFRDataObject.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/LargeTensorMPFRDataObject.h" },
		{ "ToolTip", "Concrete ULargeDataObject subclass storing an xtensor xarray of mpfr_float" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULargeTensorMPFRDataObject_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULargeTensorMPFRDataObject>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULargeTensorMPFRDataObject_Statics::ClassParams = {
		&ULargeTensorMPFRDataObject::StaticClass,
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
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_ULargeTensorMPFRDataObject_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULargeTensorMPFRDataObject_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULargeTensorMPFRDataObject()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULargeTensorMPFRDataObject_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULargeTensorMPFRDataObject, 1787110196);
	template<> LARGEDATA_API UClass* StaticClass<ULargeTensorMPFRDataObject>()
	{
		return ULargeTensorMPFRDataObject::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULargeTensorMPFRDataObject(Z_Construct_UClass_ULargeTensorMPFRDataObject, &ULargeTensorMPFRDataObject::StaticClass, TEXT("/Script/LargeData"), TEXT("ULargeTensorMPFRDataObject"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULargeTensorMPFRDataObject);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
