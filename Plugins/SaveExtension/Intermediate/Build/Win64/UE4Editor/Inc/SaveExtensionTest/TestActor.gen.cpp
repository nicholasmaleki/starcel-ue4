// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Test/Private/Helpers/TestActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTestActor() {}
// Cross Module References
	SAVEEXTENSIONTEST_API UScriptStruct* Z_Construct_UScriptStruct_FTestSaveStruct();
	UPackage* Z_Construct_UPackage__Script_SaveExtensionTest();
	SAVEEXTENSIONTEST_API UClass* Z_Construct_UClass_ATestActor_NoRegister();
	SAVEEXTENSIONTEST_API UClass* Z_Construct_UClass_ATestActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
// End Cross Module References
class UScriptStruct* FTestSaveStruct::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern SAVEEXTENSIONTEST_API uint32 Get_Z_Construct_UScriptStruct_FTestSaveStruct_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FTestSaveStruct, Z_Construct_UPackage__Script_SaveExtensionTest(), TEXT("TestSaveStruct"), sizeof(FTestSaveStruct), Get_Z_Construct_UScriptStruct_FTestSaveStruct_Hash());
	}
	return Singleton;
}
template<> SAVEEXTENSIONTEST_API UScriptStruct* StaticStruct<FTestSaveStruct>()
{
	return FTestSaveStruct::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FTestSaveStruct(FTestSaveStruct::StaticStruct, TEXT("/Script/SaveExtensionTest"), TEXT("TestSaveStruct"), false, nullptr, nullptr);
static struct FScriptStruct_SaveExtensionTest_StaticRegisterNativesFTestSaveStruct
{
	FScriptStruct_SaveExtensionTest_StaticRegisterNativesFTestSaveStruct()
	{
		UScriptStruct::DeferCppStructOps<FTestSaveStruct>(FName(TEXT("TestSaveStruct")));
	}
} ScriptStruct_SaveExtensionTest_StaticRegisterNativesFTestSaveStruct;
	struct Z_Construct_UScriptStruct_FTestSaveStruct_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTestSaveStruct_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Private/Helpers/TestActor.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FTestSaveStruct_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTestSaveStruct>();
	}
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTestSaveStruct_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_SaveExtensionTest,
		nullptr,
		&NewStructOps,
		"TestSaveStruct",
		sizeof(FTestSaveStruct),
		alignof(FTestSaveStruct),
		nullptr,
		0,
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FTestSaveStruct_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTestSaveStruct_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FTestSaveStruct()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FTestSaveStruct_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_SaveExtensionTest();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("TestSaveStruct"), sizeof(FTestSaveStruct), Get_Z_Construct_UScriptStruct_FTestSaveStruct_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FTestSaveStruct_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FTestSaveStruct_Hash() { return 3310884690U; }
	void ATestActor::StaticRegisterNativesATestActor()
	{
	}
	UClass* Z_Construct_UClass_ATestActor_NoRegister()
	{
		return ATestActor::StaticClass();
	}
	struct Z_Construct_UClass_ATestActor_Statics
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
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MyFloat_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MyFloat;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MyU8_MetaData[];
#endif
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_MyU8;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MyU16_MetaData[];
#endif
		static const UE4CodeGen_Private::FFInt16PropertyParams NewProp_MyU16;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MyU32_MetaData[];
#endif
		static const UE4CodeGen_Private::FUInt32PropertyParams NewProp_MyU32;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MyU64_MetaData[];
#endif
		static const UE4CodeGen_Private::FFInt64PropertyParams NewProp_MyU64;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MyI8_MetaData[];
#endif
		static const UE4CodeGen_Private::FInt8PropertyParams NewProp_MyI8;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MyI16_MetaData[];
#endif
		static const UE4CodeGen_Private::FInt16PropertyParams NewProp_MyI16;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MyI32_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_MyI32;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MyI64_MetaData[];
#endif
		static const UE4CodeGen_Private::FInt64PropertyParams NewProp_MyI64;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MyStruct_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MyStruct;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATestActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_SaveExtensionTest,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATestActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Helpers/TestActor.h" },
		{ "ModuleRelativePath", "Private/Helpers/TestActor.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATestActor_Statics::NewProp_bMyBool_MetaData[] = {
		{ "ModuleRelativePath", "Private/Helpers/TestActor.h" },
	};
#endif
	void Z_Construct_UClass_ATestActor_Statics::NewProp_bMyBool_SetBit(void* Obj)
	{
		((ATestActor*)Obj)->bMyBool = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ATestActor_Statics::NewProp_bMyBool = { "bMyBool", nullptr, (EPropertyFlags)0x0010000001000000, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ATestActor), &Z_Construct_UClass_ATestActor_Statics::NewProp_bMyBool_SetBit, METADATA_PARAMS(Z_Construct_UClass_ATestActor_Statics::NewProp_bMyBool_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATestActor_Statics::NewProp_bMyBool_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATestActor_Statics::NewProp_MyFloat_MetaData[] = {
		{ "ModuleRelativePath", "Private/Helpers/TestActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATestActor_Statics::NewProp_MyFloat = { "MyFloat", nullptr, (EPropertyFlags)0x0010000001000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATestActor, MyFloat), METADATA_PARAMS(Z_Construct_UClass_ATestActor_Statics::NewProp_MyFloat_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATestActor_Statics::NewProp_MyFloat_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATestActor_Statics::NewProp_MyU8_MetaData[] = {
		{ "Comment", "// INTEGERS\n" },
		{ "ModuleRelativePath", "Private/Helpers/TestActor.h" },
		{ "ToolTip", "INTEGERS" },
	};
#endif
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_ATestActor_Statics::NewProp_MyU8 = { "MyU8", nullptr, (EPropertyFlags)0x0010000001000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATestActor, MyU8), nullptr, METADATA_PARAMS(Z_Construct_UClass_ATestActor_Statics::NewProp_MyU8_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATestActor_Statics::NewProp_MyU8_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATestActor_Statics::NewProp_MyU16_MetaData[] = {
		{ "ModuleRelativePath", "Private/Helpers/TestActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFInt16PropertyParams Z_Construct_UClass_ATestActor_Statics::NewProp_MyU16 = { "MyU16", nullptr, (EPropertyFlags)0x0010000001000000, UE4CodeGen_Private::EPropertyGenFlags::UInt16, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATestActor, MyU16), METADATA_PARAMS(Z_Construct_UClass_ATestActor_Statics::NewProp_MyU16_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATestActor_Statics::NewProp_MyU16_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATestActor_Statics::NewProp_MyU32_MetaData[] = {
		{ "ModuleRelativePath", "Private/Helpers/TestActor.h" },
	};
#endif
	const UE4CodeGen_Private::FUInt32PropertyParams Z_Construct_UClass_ATestActor_Statics::NewProp_MyU32 = { "MyU32", nullptr, (EPropertyFlags)0x0010000001000000, UE4CodeGen_Private::EPropertyGenFlags::UInt32, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATestActor, MyU32), METADATA_PARAMS(Z_Construct_UClass_ATestActor_Statics::NewProp_MyU32_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATestActor_Statics::NewProp_MyU32_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATestActor_Statics::NewProp_MyU64_MetaData[] = {
		{ "ModuleRelativePath", "Private/Helpers/TestActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFInt64PropertyParams Z_Construct_UClass_ATestActor_Statics::NewProp_MyU64 = { "MyU64", nullptr, (EPropertyFlags)0x0010000001000000, UE4CodeGen_Private::EPropertyGenFlags::UInt64, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATestActor, MyU64), METADATA_PARAMS(Z_Construct_UClass_ATestActor_Statics::NewProp_MyU64_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATestActor_Statics::NewProp_MyU64_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATestActor_Statics::NewProp_MyI8_MetaData[] = {
		{ "ModuleRelativePath", "Private/Helpers/TestActor.h" },
	};
#endif
	const UE4CodeGen_Private::FInt8PropertyParams Z_Construct_UClass_ATestActor_Statics::NewProp_MyI8 = { "MyI8", nullptr, (EPropertyFlags)0x0010000001000000, UE4CodeGen_Private::EPropertyGenFlags::Int8, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATestActor, MyI8), METADATA_PARAMS(Z_Construct_UClass_ATestActor_Statics::NewProp_MyI8_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATestActor_Statics::NewProp_MyI8_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATestActor_Statics::NewProp_MyI16_MetaData[] = {
		{ "ModuleRelativePath", "Private/Helpers/TestActor.h" },
	};
#endif
	const UE4CodeGen_Private::FInt16PropertyParams Z_Construct_UClass_ATestActor_Statics::NewProp_MyI16 = { "MyI16", nullptr, (EPropertyFlags)0x0010000001000000, UE4CodeGen_Private::EPropertyGenFlags::Int16, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATestActor, MyI16), METADATA_PARAMS(Z_Construct_UClass_ATestActor_Statics::NewProp_MyI16_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATestActor_Statics::NewProp_MyI16_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATestActor_Statics::NewProp_MyI32_MetaData[] = {
		{ "ModuleRelativePath", "Private/Helpers/TestActor.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_ATestActor_Statics::NewProp_MyI32 = { "MyI32", nullptr, (EPropertyFlags)0x0010000001000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATestActor, MyI32), METADATA_PARAMS(Z_Construct_UClass_ATestActor_Statics::NewProp_MyI32_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATestActor_Statics::NewProp_MyI32_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATestActor_Statics::NewProp_MyI64_MetaData[] = {
		{ "ModuleRelativePath", "Private/Helpers/TestActor.h" },
	};
#endif
	const UE4CodeGen_Private::FInt64PropertyParams Z_Construct_UClass_ATestActor_Statics::NewProp_MyI64 = { "MyI64", nullptr, (EPropertyFlags)0x0010000001000000, UE4CodeGen_Private::EPropertyGenFlags::Int64, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATestActor, MyI64), METADATA_PARAMS(Z_Construct_UClass_ATestActor_Statics::NewProp_MyI64_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATestActor_Statics::NewProp_MyI64_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATestActor_Statics::NewProp_MyStruct_MetaData[] = {
		{ "ModuleRelativePath", "Private/Helpers/TestActor.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ATestActor_Statics::NewProp_MyStruct = { "MyStruct", nullptr, (EPropertyFlags)0x0010000001000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATestActor, MyStruct), Z_Construct_UScriptStruct_FTestSaveStruct, METADATA_PARAMS(Z_Construct_UClass_ATestActor_Statics::NewProp_MyStruct_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATestActor_Statics::NewProp_MyStruct_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ATestActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATestActor_Statics::NewProp_bMyBool,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATestActor_Statics::NewProp_MyFloat,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATestActor_Statics::NewProp_MyU8,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATestActor_Statics::NewProp_MyU16,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATestActor_Statics::NewProp_MyU32,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATestActor_Statics::NewProp_MyU64,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATestActor_Statics::NewProp_MyI8,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATestActor_Statics::NewProp_MyI16,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATestActor_Statics::NewProp_MyI32,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATestActor_Statics::NewProp_MyI64,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATestActor_Statics::NewProp_MyStruct,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATestActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATestActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ATestActor_Statics::ClassParams = {
		&ATestActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ATestActor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ATestActor_Statics::PropPointers),
		0,
		0x008000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ATestActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATestActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATestActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ATestActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ATestActor, 1788204000);
	template<> SAVEEXTENSIONTEST_API UClass* StaticClass<ATestActor>()
	{
		return ATestActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ATestActor(Z_Construct_UClass_ATestActor, &ATestActor::StaticClass, TEXT("/Script/SaveExtensionTest"), TEXT("ATestActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATestActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
