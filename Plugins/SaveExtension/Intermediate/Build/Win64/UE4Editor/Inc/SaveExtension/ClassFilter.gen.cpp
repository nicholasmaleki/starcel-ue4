// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SaveExtension/Public/Misc/ClassFilter.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeClassFilter() {}
// Cross Module References
	SAVEEXTENSION_API UScriptStruct* Z_Construct_UScriptStruct_FSEComponentClassFilter();
	UPackage* Z_Construct_UPackage__Script_SaveExtension();
	SAVEEXTENSION_API UScriptStruct* Z_Construct_UScriptStruct_FSEClassFilter();
	SAVEEXTENSION_API UScriptStruct* Z_Construct_UScriptStruct_FSEActorClassFilter();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
// End Cross Module References
class UScriptStruct* FSEComponentClassFilter::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern SAVEEXTENSION_API uint32 Get_Z_Construct_UScriptStruct_FSEComponentClassFilter_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FSEComponentClassFilter, Z_Construct_UPackage__Script_SaveExtension(), TEXT("SEComponentClassFilter"), sizeof(FSEComponentClassFilter), Get_Z_Construct_UScriptStruct_FSEComponentClassFilter_Hash());
	}
	return Singleton;
}
template<> SAVEEXTENSION_API UScriptStruct* StaticStruct<FSEComponentClassFilter>()
{
	return FSEComponentClassFilter::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FSEComponentClassFilter(FSEComponentClassFilter::StaticStruct, TEXT("/Script/SaveExtension"), TEXT("SEComponentClassFilter"), false, nullptr, nullptr);
static struct FScriptStruct_SaveExtension_StaticRegisterNativesFSEComponentClassFilter
{
	FScriptStruct_SaveExtension_StaticRegisterNativesFSEComponentClassFilter()
	{
		UScriptStruct::DeferCppStructOps<FSEComponentClassFilter>(FName(TEXT("SEComponentClassFilter")));
	}
} ScriptStruct_SaveExtension_StaticRegisterNativesFSEComponentClassFilter;
	struct Z_Construct_UScriptStruct_FSEComponentClassFilter_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ClassFilter_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ClassFilter;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSEComponentClassFilter_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Misc/ClassFilter.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FSEComponentClassFilter_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSEComponentClassFilter>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSEComponentClassFilter_Statics::NewProp_ClassFilter_MetaData[] = {
		{ "Category", "Filter" },
		{ "ModuleRelativePath", "Public/Misc/ClassFilter.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FSEComponentClassFilter_Statics::NewProp_ClassFilter = { "ClassFilter", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSEComponentClassFilter, ClassFilter), Z_Construct_UScriptStruct_FSEClassFilter, METADATA_PARAMS(Z_Construct_UScriptStruct_FSEComponentClassFilter_Statics::NewProp_ClassFilter_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSEComponentClassFilter_Statics::NewProp_ClassFilter_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FSEComponentClassFilter_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSEComponentClassFilter_Statics::NewProp_ClassFilter,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FSEComponentClassFilter_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_SaveExtension,
		nullptr,
		&NewStructOps,
		"SEComponentClassFilter",
		sizeof(FSEComponentClassFilter),
		alignof(FSEComponentClassFilter),
		Z_Construct_UScriptStruct_FSEComponentClassFilter_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSEComponentClassFilter_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FSEComponentClassFilter_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSEComponentClassFilter_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FSEComponentClassFilter()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FSEComponentClassFilter_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_SaveExtension();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("SEComponentClassFilter"), sizeof(FSEComponentClassFilter), Get_Z_Construct_UScriptStruct_FSEComponentClassFilter_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FSEComponentClassFilter_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FSEComponentClassFilter_Hash() { return 818704424U; }
class UScriptStruct* FSEActorClassFilter::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern SAVEEXTENSION_API uint32 Get_Z_Construct_UScriptStruct_FSEActorClassFilter_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FSEActorClassFilter, Z_Construct_UPackage__Script_SaveExtension(), TEXT("SEActorClassFilter"), sizeof(FSEActorClassFilter), Get_Z_Construct_UScriptStruct_FSEActorClassFilter_Hash());
	}
	return Singleton;
}
template<> SAVEEXTENSION_API UScriptStruct* StaticStruct<FSEActorClassFilter>()
{
	return FSEActorClassFilter::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FSEActorClassFilter(FSEActorClassFilter::StaticStruct, TEXT("/Script/SaveExtension"), TEXT("SEActorClassFilter"), false, nullptr, nullptr);
static struct FScriptStruct_SaveExtension_StaticRegisterNativesFSEActorClassFilter
{
	FScriptStruct_SaveExtension_StaticRegisterNativesFSEActorClassFilter()
	{
		UScriptStruct::DeferCppStructOps<FSEActorClassFilter>(FName(TEXT("SEActorClassFilter")));
	}
} ScriptStruct_SaveExtension_StaticRegisterNativesFSEActorClassFilter;
	struct Z_Construct_UScriptStruct_FSEActorClassFilter_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ClassFilter_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ClassFilter;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSEActorClassFilter_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Misc/ClassFilter.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FSEActorClassFilter_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSEActorClassFilter>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSEActorClassFilter_Statics::NewProp_ClassFilter_MetaData[] = {
		{ "Category", "Filter" },
		{ "ModuleRelativePath", "Public/Misc/ClassFilter.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FSEActorClassFilter_Statics::NewProp_ClassFilter = { "ClassFilter", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSEActorClassFilter, ClassFilter), Z_Construct_UScriptStruct_FSEClassFilter, METADATA_PARAMS(Z_Construct_UScriptStruct_FSEActorClassFilter_Statics::NewProp_ClassFilter_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSEActorClassFilter_Statics::NewProp_ClassFilter_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FSEActorClassFilter_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSEActorClassFilter_Statics::NewProp_ClassFilter,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FSEActorClassFilter_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_SaveExtension,
		nullptr,
		&NewStructOps,
		"SEActorClassFilter",
		sizeof(FSEActorClassFilter),
		alignof(FSEActorClassFilter),
		Z_Construct_UScriptStruct_FSEActorClassFilter_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSEActorClassFilter_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FSEActorClassFilter_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSEActorClassFilter_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FSEActorClassFilter()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FSEActorClassFilter_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_SaveExtension();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("SEActorClassFilter"), sizeof(FSEActorClassFilter), Get_Z_Construct_UScriptStruct_FSEActorClassFilter_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FSEActorClassFilter_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FSEActorClassFilter_Hash() { return 1661620460U; }
class UScriptStruct* FSEClassFilter::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern SAVEEXTENSION_API uint32 Get_Z_Construct_UScriptStruct_FSEClassFilter_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FSEClassFilter, Z_Construct_UPackage__Script_SaveExtension(), TEXT("SEClassFilter"), sizeof(FSEClassFilter), Get_Z_Construct_UScriptStruct_FSEClassFilter_Hash());
	}
	return Singleton;
}
template<> SAVEEXTENSION_API UScriptStruct* StaticStruct<FSEClassFilter>()
{
	return FSEClassFilter::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FSEClassFilter(FSEClassFilter::StaticStruct, TEXT("/Script/SaveExtension"), TEXT("SEClassFilter"), false, nullptr, nullptr);
static struct FScriptStruct_SaveExtension_StaticRegisterNativesFSEClassFilter
{
	FScriptStruct_SaveExtension_StaticRegisterNativesFSEClassFilter()
	{
		UScriptStruct::DeferCppStructOps<FSEClassFilter>(FName(TEXT("SEClassFilter")));
	}
} ScriptStruct_SaveExtension_StaticRegisterNativesFSEClassFilter;
	struct Z_Construct_UScriptStruct_FSEClassFilter_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BaseClass_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_BaseClass;
		static const UE4CodeGen_Private::FSoftClassPropertyParams NewProp_AllowedClasses_ElementProp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AllowedClasses_MetaData[];
#endif
		static const UE4CodeGen_Private::FSetPropertyParams NewProp_AllowedClasses;
		static const UE4CodeGen_Private::FSoftClassPropertyParams NewProp_IgnoredClasses_ElementProp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IgnoredClasses_MetaData[];
#endif
		static const UE4CodeGen_Private::FSetPropertyParams NewProp_IgnoredClasses;
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_BakedAllowedClasses_ElementProp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BakedAllowedClasses_MetaData[];
#endif
		static const UE4CodeGen_Private::FSetPropertyParams NewProp_BakedAllowedClasses;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSEClassFilter_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Misc/ClassFilter.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSEClassFilter>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_BaseClass_MetaData[] = {
		{ "Comment", "// Used from editor side to limit displayed classes\n" },
		{ "ModuleRelativePath", "Public/Misc/ClassFilter.h" },
		{ "ToolTip", "Used from editor side to limit displayed classes" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_BaseClass = { "BaseClass", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSEClassFilter, BaseClass), Z_Construct_UClass_UObject_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_BaseClass_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_BaseClass_MetaData)) };
	const UE4CodeGen_Private::FSoftClassPropertyParams Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_AllowedClasses_ElementProp = { "AllowedClasses", nullptr, (EPropertyFlags)0x0004000000000001, UE4CodeGen_Private::EPropertyGenFlags::SoftClass, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_AllowedClasses_MetaData[] = {
		{ "Category", "Serialization" },
		{ "Comment", "/** This classes are allowed (and their children) */" },
		{ "ModuleRelativePath", "Public/Misc/ClassFilter.h" },
		{ "ToolTip", "This classes are allowed (and their children)" },
	};
#endif
	const UE4CodeGen_Private::FSetPropertyParams Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_AllowedClasses = { "AllowedClasses", nullptr, (EPropertyFlags)0x0014000000000005, UE4CodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSEClassFilter, AllowedClasses), METADATA_PARAMS(Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_AllowedClasses_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_AllowedClasses_MetaData)) };
	const UE4CodeGen_Private::FSoftClassPropertyParams Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_IgnoredClasses_ElementProp = { "IgnoredClasses", nullptr, (EPropertyFlags)0x0004000000000001, UE4CodeGen_Private::EPropertyGenFlags::SoftClass, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_IgnoredClasses_MetaData[] = {
		{ "Category", "Serialization" },
		{ "Comment", "/** This classes are ignored (and their children) */" },
		{ "ModuleRelativePath", "Public/Misc/ClassFilter.h" },
		{ "ToolTip", "This classes are ignored (and their children)" },
	};
#endif
	const UE4CodeGen_Private::FSetPropertyParams Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_IgnoredClasses = { "IgnoredClasses", nullptr, (EPropertyFlags)0x0014000000000005, UE4CodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSEClassFilter, IgnoredClasses), METADATA_PARAMS(Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_IgnoredClasses_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_IgnoredClasses_MetaData)) };
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_BakedAllowedClasses_ElementProp = { "BakedAllowedClasses", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UObject_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_BakedAllowedClasses_MetaData[] = {
		{ "ModuleRelativePath", "Public/Misc/ClassFilter.h" },
	};
#endif
	const UE4CodeGen_Private::FSetPropertyParams Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_BakedAllowedClasses = { "BakedAllowedClasses", nullptr, (EPropertyFlags)0x0020080000002000, UE4CodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSEClassFilter, BakedAllowedClasses), METADATA_PARAMS(Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_BakedAllowedClasses_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_BakedAllowedClasses_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FSEClassFilter_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_BaseClass,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_AllowedClasses_ElementProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_AllowedClasses,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_IgnoredClasses_ElementProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_IgnoredClasses,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_BakedAllowedClasses_ElementProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSEClassFilter_Statics::NewProp_BakedAllowedClasses,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FSEClassFilter_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_SaveExtension,
		nullptr,
		&NewStructOps,
		"SEClassFilter",
		sizeof(FSEClassFilter),
		alignof(FSEClassFilter),
		Z_Construct_UScriptStruct_FSEClassFilter_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSEClassFilter_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FSEClassFilter_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSEClassFilter_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FSEClassFilter()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FSEClassFilter_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_SaveExtension();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("SEClassFilter"), sizeof(FSEClassFilter), Get_Z_Construct_UScriptStruct_FSEClassFilter_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FSEClassFilter_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FSEClassFilter_Hash() { return 537980356U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
