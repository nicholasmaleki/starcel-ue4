// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Text3D/Private/Text3DEngineSubsystem.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeText3DEngineSubsystem() {}
// Cross Module References
	TEXT3D_API UScriptStruct* Z_Construct_UScriptStruct_FCachedFontData();
	UPackage* Z_Construct_UPackage__Script_Text3D();
	ENGINE_API UClass* Z_Construct_UClass_UFont_NoRegister();
	TEXT3D_API UScriptStruct* Z_Construct_UScriptStruct_FCachedFontMeshes();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
	TEXT3D_API UClass* Z_Construct_UClass_UText3DEngineSubsystem_NoRegister();
	TEXT3D_API UClass* Z_Construct_UClass_UText3DEngineSubsystem();
	ENGINE_API UClass* Z_Construct_UClass_UEngineSubsystem();
	ENGINE_API UClass* Z_Construct_UClass_UMaterial_NoRegister();
// End Cross Module References
class UScriptStruct* FCachedFontData::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern TEXT3D_API uint32 Get_Z_Construct_UScriptStruct_FCachedFontData_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FCachedFontData, Z_Construct_UPackage__Script_Text3D(), TEXT("CachedFontData"), sizeof(FCachedFontData), Get_Z_Construct_UScriptStruct_FCachedFontData_Hash());
	}
	return Singleton;
}
template<> TEXT3D_API UScriptStruct* StaticStruct<FCachedFontData>()
{
	return FCachedFontData::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FCachedFontData(FCachedFontData::StaticStruct, TEXT("/Script/Text3D"), TEXT("CachedFontData"), false, nullptr, nullptr);
static struct FScriptStruct_Text3D_StaticRegisterNativesFCachedFontData
{
	FScriptStruct_Text3D_StaticRegisterNativesFCachedFontData()
	{
		UScriptStruct::DeferCppStructOps<FCachedFontData>(FName(TEXT("CachedFontData")));
	}
} ScriptStruct_Text3D_StaticRegisterNativesFCachedFontData;
	struct Z_Construct_UScriptStruct_FCachedFontData_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Font_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Font;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Meshes_ValueProp;
		static const UE4CodeGen_Private::FUInt32PropertyParams NewProp_Meshes_Key_KeyProp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Meshes_MetaData[];
#endif
		static const UE4CodeGen_Private::FMapPropertyParams NewProp_Meshes;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCachedFontData_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Private/Text3DEngineSubsystem.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FCachedFontData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FCachedFontData>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCachedFontData_Statics::NewProp_Font_MetaData[] = {
		{ "ModuleRelativePath", "Private/Text3DEngineSubsystem.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FCachedFontData_Statics::NewProp_Font = { "Font", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCachedFontData, Font), Z_Construct_UClass_UFont_NoRegister, METADATA_PARAMS(Z_Construct_UScriptStruct_FCachedFontData_Statics::NewProp_Font_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCachedFontData_Statics::NewProp_Font_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FCachedFontData_Statics::NewProp_Meshes_ValueProp = { "Meshes", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, Z_Construct_UScriptStruct_FCachedFontMeshes, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUInt32PropertyParams Z_Construct_UScriptStruct_FCachedFontData_Statics::NewProp_Meshes_Key_KeyProp = { "Meshes_Key", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::UInt32, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCachedFontData_Statics::NewProp_Meshes_MetaData[] = {
		{ "ModuleRelativePath", "Private/Text3DEngineSubsystem.h" },
	};
#endif
	const UE4CodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FCachedFontData_Statics::NewProp_Meshes = { "Meshes", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCachedFontData, Meshes), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FCachedFontData_Statics::NewProp_Meshes_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCachedFontData_Statics::NewProp_Meshes_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FCachedFontData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCachedFontData_Statics::NewProp_Font,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCachedFontData_Statics::NewProp_Meshes_ValueProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCachedFontData_Statics::NewProp_Meshes_Key_KeyProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCachedFontData_Statics::NewProp_Meshes,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FCachedFontData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Text3D,
		nullptr,
		&NewStructOps,
		"CachedFontData",
		sizeof(FCachedFontData),
		alignof(FCachedFontData),
		Z_Construct_UScriptStruct_FCachedFontData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCachedFontData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FCachedFontData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCachedFontData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FCachedFontData()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FCachedFontData_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_Text3D();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("CachedFontData"), sizeof(FCachedFontData), Get_Z_Construct_UScriptStruct_FCachedFontData_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FCachedFontData_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FCachedFontData_Hash() { return 3553459134U; }
class UScriptStruct* FCachedFontMeshes::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern TEXT3D_API uint32 Get_Z_Construct_UScriptStruct_FCachedFontMeshes_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FCachedFontMeshes, Z_Construct_UPackage__Script_Text3D(), TEXT("CachedFontMeshes"), sizeof(FCachedFontMeshes), Get_Z_Construct_UScriptStruct_FCachedFontMeshes_Hash());
	}
	return Singleton;
}
template<> TEXT3D_API UScriptStruct* StaticStruct<FCachedFontMeshes>()
{
	return FCachedFontMeshes::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FCachedFontMeshes(FCachedFontMeshes::StaticStruct, TEXT("/Script/Text3D"), TEXT("CachedFontMeshes"), false, nullptr, nullptr);
static struct FScriptStruct_Text3D_StaticRegisterNativesFCachedFontMeshes
{
	FScriptStruct_Text3D_StaticRegisterNativesFCachedFontMeshes()
	{
		UScriptStruct::DeferCppStructOps<FCachedFontMeshes>(FName(TEXT("CachedFontMeshes")));
	}
} ScriptStruct_Text3D_StaticRegisterNativesFCachedFontMeshes;
	struct Z_Construct_UScriptStruct_FCachedFontMeshes_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Glyphs_ValueProp;
		static const UE4CodeGen_Private::FUInt32PropertyParams NewProp_Glyphs_Key_KeyProp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Glyphs_MetaData[];
#endif
		static const UE4CodeGen_Private::FMapPropertyParams NewProp_Glyphs;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCachedFontMeshes_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Private/Text3DEngineSubsystem.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FCachedFontMeshes_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FCachedFontMeshes>();
	}
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FCachedFontMeshes_Statics::NewProp_Glyphs_ValueProp = { "Glyphs", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUInt32PropertyParams Z_Construct_UScriptStruct_FCachedFontMeshes_Statics::NewProp_Glyphs_Key_KeyProp = { "Glyphs_Key", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::UInt32, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCachedFontMeshes_Statics::NewProp_Glyphs_MetaData[] = {
		{ "ModuleRelativePath", "Private/Text3DEngineSubsystem.h" },
	};
#endif
	const UE4CodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FCachedFontMeshes_Statics::NewProp_Glyphs = { "Glyphs", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCachedFontMeshes, Glyphs), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FCachedFontMeshes_Statics::NewProp_Glyphs_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCachedFontMeshes_Statics::NewProp_Glyphs_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FCachedFontMeshes_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCachedFontMeshes_Statics::NewProp_Glyphs_ValueProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCachedFontMeshes_Statics::NewProp_Glyphs_Key_KeyProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCachedFontMeshes_Statics::NewProp_Glyphs,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FCachedFontMeshes_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Text3D,
		nullptr,
		&NewStructOps,
		"CachedFontMeshes",
		sizeof(FCachedFontMeshes),
		alignof(FCachedFontMeshes),
		Z_Construct_UScriptStruct_FCachedFontMeshes_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCachedFontMeshes_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FCachedFontMeshes_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCachedFontMeshes_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FCachedFontMeshes()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FCachedFontMeshes_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_Text3D();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("CachedFontMeshes"), sizeof(FCachedFontMeshes), Get_Z_Construct_UScriptStruct_FCachedFontMeshes_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FCachedFontMeshes_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FCachedFontMeshes_Hash() { return 2753138145U; }
	void UText3DEngineSubsystem::StaticRegisterNativesUText3DEngineSubsystem()
	{
	}
	UClass* Z_Construct_UClass_UText3DEngineSubsystem_NoRegister()
	{
		return UText3DEngineSubsystem::StaticClass();
	}
	struct Z_Construct_UClass_UText3DEngineSubsystem_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DefaultMaterial_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_DefaultMaterial;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_CachedFonts_ValueProp;
		static const UE4CodeGen_Private::FUInt32PropertyParams NewProp_CachedFonts_Key_KeyProp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CachedFonts_MetaData[];
#endif
		static const UE4CodeGen_Private::FMapPropertyParams NewProp_CachedFonts;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UText3DEngineSubsystem_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UEngineSubsystem,
		(UObject* (*)())Z_Construct_UPackage__Script_Text3D,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DEngineSubsystem_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Text3DEngineSubsystem.h" },
		{ "ModuleRelativePath", "Private/Text3DEngineSubsystem.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DEngineSubsystem_Statics::NewProp_DefaultMaterial_MetaData[] = {
		{ "ModuleRelativePath", "Private/Text3DEngineSubsystem.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UText3DEngineSubsystem_Statics::NewProp_DefaultMaterial = { "DefaultMaterial", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DEngineSubsystem, DefaultMaterial), Z_Construct_UClass_UMaterial_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UText3DEngineSubsystem_Statics::NewProp_DefaultMaterial_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DEngineSubsystem_Statics::NewProp_DefaultMaterial_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UText3DEngineSubsystem_Statics::NewProp_CachedFonts_ValueProp = { "CachedFonts", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, Z_Construct_UScriptStruct_FCachedFontData, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUInt32PropertyParams Z_Construct_UClass_UText3DEngineSubsystem_Statics::NewProp_CachedFonts_Key_KeyProp = { "CachedFonts_Key", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::UInt32, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DEngineSubsystem_Statics::NewProp_CachedFonts_MetaData[] = {
		{ "ModuleRelativePath", "Private/Text3DEngineSubsystem.h" },
	};
#endif
	const UE4CodeGen_Private::FMapPropertyParams Z_Construct_UClass_UText3DEngineSubsystem_Statics::NewProp_CachedFonts = { "CachedFonts", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DEngineSubsystem, CachedFonts), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UText3DEngineSubsystem_Statics::NewProp_CachedFonts_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DEngineSubsystem_Statics::NewProp_CachedFonts_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UText3DEngineSubsystem_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DEngineSubsystem_Statics::NewProp_DefaultMaterial,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DEngineSubsystem_Statics::NewProp_CachedFonts_ValueProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DEngineSubsystem_Statics::NewProp_CachedFonts_Key_KeyProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DEngineSubsystem_Statics::NewProp_CachedFonts,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UText3DEngineSubsystem_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UText3DEngineSubsystem>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UText3DEngineSubsystem_Statics::ClassParams = {
		&UText3DEngineSubsystem::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UText3DEngineSubsystem_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UText3DEngineSubsystem_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UText3DEngineSubsystem_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DEngineSubsystem_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UText3DEngineSubsystem()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UText3DEngineSubsystem_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UText3DEngineSubsystem, 3653833322);
	template<> TEXT3D_API UClass* StaticClass<UText3DEngineSubsystem>()
	{
		return UText3DEngineSubsystem::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UText3DEngineSubsystem(Z_Construct_UClass_UText3DEngineSubsystem, &UText3DEngineSubsystem::StaticClass, TEXT("/Script/Text3D"), TEXT("UText3DEngineSubsystem"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UText3DEngineSubsystem);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
