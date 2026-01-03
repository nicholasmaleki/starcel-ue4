// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LargeData/Public/LargeByteDataObject.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLargeByteDataObject() {}
// Cross Module References
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeByteDataObject_NoRegister();
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeByteDataObject();
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeDataObject();
	UPackage* Z_Construct_UPackage__Script_LargeData();
// End Cross Module References
	void ULargeByteDataObject::StaticRegisterNativesULargeByteDataObject()
	{
	}
	UClass* Z_Construct_UClass_ULargeByteDataObject_NoRegister()
	{
		return ULargeByteDataObject::StaticClass();
	}
	struct Z_Construct_UClass_ULargeByteDataObject_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULargeByteDataObject_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ULargeDataObject,
		(UObject* (*)())Z_Construct_UPackage__Script_LargeData,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULargeByteDataObject_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * A concrete subclass of ULargeDataObject that stores a simple byte array.\n */" },
		{ "IncludePath", "LargeByteDataObject.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/LargeByteDataObject.h" },
		{ "ToolTip", "A concrete subclass of ULargeDataObject that stores a simple byte array." },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULargeByteDataObject_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULargeByteDataObject>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULargeByteDataObject_Statics::ClassParams = {
		&ULargeByteDataObject::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_ULargeByteDataObject_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULargeByteDataObject_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULargeByteDataObject()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULargeByteDataObject_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULargeByteDataObject, 3225681146);
	template<> LARGEDATA_API UClass* StaticClass<ULargeByteDataObject>()
	{
		return ULargeByteDataObject::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULargeByteDataObject(Z_Construct_UClass_ULargeByteDataObject, &ULargeByteDataObject::StaticClass, TEXT("/Script/LargeData"), TEXT("ULargeByteDataObject"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULargeByteDataObject);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
