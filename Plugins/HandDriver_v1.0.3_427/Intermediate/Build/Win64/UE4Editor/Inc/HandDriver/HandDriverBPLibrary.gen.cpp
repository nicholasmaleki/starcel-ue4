// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HandDriver/Public/HandDriverBPLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHandDriverBPLibrary() {}
// Cross Module References
	HANDDRIVER_API UClass* Z_Construct_UClass_UHandDriverBPLibrary_NoRegister();
	HANDDRIVER_API UClass* Z_Construct_UClass_UHandDriverBPLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_HandDriver();
	LIVELINKINTERFACE_API UScriptStruct* Z_Construct_UScriptStruct_FLiveLinkSourceHandle();
// End Cross Module References
	DEFINE_FUNCTION(UHandDriverBPLibrary::execCreateSourceRuntime)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_ConnectionString);
		P_GET_STRUCT_REF(FLiveLinkSourceHandle,Z_Param_Out_Handle);
		P_FINISH;
		P_NATIVE_BEGIN;
		UHandDriverBPLibrary::CreateSourceRuntime(Z_Param_ConnectionString,Z_Param_Out_Handle);
		P_NATIVE_END;
	}
	void UHandDriverBPLibrary::StaticRegisterNativesUHandDriverBPLibrary()
	{
		UClass* Class = UHandDriverBPLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CreateSourceRuntime", &UHandDriverBPLibrary::execCreateSourceRuntime },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UHandDriverBPLibrary_CreateSourceRuntime_Statics
	{
		struct HandDriverBPLibrary_eventCreateSourceRuntime_Parms
		{
			FString ConnectionString;
			FLiveLinkSourceHandle Handle;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ConnectionString_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ConnectionString;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Handle;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHandDriverBPLibrary_CreateSourceRuntime_Statics::NewProp_ConnectionString_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UHandDriverBPLibrary_CreateSourceRuntime_Statics::NewProp_ConnectionString = { "ConnectionString", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HandDriverBPLibrary_eventCreateSourceRuntime_Parms, ConnectionString), METADATA_PARAMS(Z_Construct_UFunction_UHandDriverBPLibrary_CreateSourceRuntime_Statics::NewProp_ConnectionString_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UHandDriverBPLibrary_CreateSourceRuntime_Statics::NewProp_ConnectionString_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UHandDriverBPLibrary_CreateSourceRuntime_Statics::NewProp_Handle = { "Handle", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HandDriverBPLibrary_eventCreateSourceRuntime_Parms, Handle), Z_Construct_UScriptStruct_FLiveLinkSourceHandle, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHandDriverBPLibrary_CreateSourceRuntime_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHandDriverBPLibrary_CreateSourceRuntime_Statics::NewProp_ConnectionString,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHandDriverBPLibrary_CreateSourceRuntime_Statics::NewProp_Handle,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHandDriverBPLibrary_CreateSourceRuntime_Statics::Function_MetaDataParams[] = {
		{ "Category", "HandDriver" },
		{ "DisplayName", "Create HandDriver Live Link Source at runtime" },
		{ "Keywords", "create HandDriver source live link" },
		{ "ModuleRelativePath", "Public/HandDriverBPLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHandDriverBPLibrary_CreateSourceRuntime_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHandDriverBPLibrary, nullptr, "CreateSourceRuntime", nullptr, nullptr, sizeof(HandDriverBPLibrary_eventCreateSourceRuntime_Parms), Z_Construct_UFunction_UHandDriverBPLibrary_CreateSourceRuntime_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHandDriverBPLibrary_CreateSourceRuntime_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04442401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHandDriverBPLibrary_CreateSourceRuntime_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHandDriverBPLibrary_CreateSourceRuntime_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHandDriverBPLibrary_CreateSourceRuntime()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHandDriverBPLibrary_CreateSourceRuntime_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UHandDriverBPLibrary_NoRegister()
	{
		return UHandDriverBPLibrary::StaticClass();
	}
	struct Z_Construct_UClass_UHandDriverBPLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UHandDriverBPLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_HandDriver,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UHandDriverBPLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UHandDriverBPLibrary_CreateSourceRuntime, "CreateSourceRuntime" }, // 2798583401
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandDriverBPLibrary_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "HandDriverBPLibrary.h" },
		{ "ModuleRelativePath", "Public/HandDriverBPLibrary.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UHandDriverBPLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHandDriverBPLibrary>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UHandDriverBPLibrary_Statics::ClassParams = {
		&UHandDriverBPLibrary::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UHandDriverBPLibrary_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UHandDriverBPLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UHandDriverBPLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UHandDriverBPLibrary_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UHandDriverBPLibrary, 4179899610);
	template<> HANDDRIVER_API UClass* StaticClass<UHandDriverBPLibrary>()
	{
		return UHandDriverBPLibrary::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UHandDriverBPLibrary(Z_Construct_UClass_UHandDriverBPLibrary, &UHandDriverBPLibrary::StaticClass, TEXT("/Script/HandDriver"), TEXT("UHandDriverBPLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UHandDriverBPLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
