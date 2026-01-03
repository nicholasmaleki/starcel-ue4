// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LargeData/Public/LargeString.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLargeString() {}
// Cross Module References
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeString_NoRegister();
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeString();
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeDataObject();
	UPackage* Z_Construct_UPackage__Script_LargeData();
// End Cross Module References
	DEFINE_FUNCTION(ULargeString::execToString)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->ToString();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULargeString::execSetFromString)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InString);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetFromString(Z_Param_InString);
		P_NATIVE_END;
	}
	void ULargeString::StaticRegisterNativesULargeString()
	{
		UClass* Class = ULargeString::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "SetFromString", &ULargeString::execSetFromString },
			{ "ToString", &ULargeString::execToString },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULargeString_SetFromString_Statics
	{
		struct LargeString_eventSetFromString_Parms
		{
			FString InString;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InString_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_InString;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeString_SetFromString_Statics::NewProp_InString_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ULargeString_SetFromString_Statics::NewProp_InString = { "InString", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeString_eventSetFromString_Parms, InString), METADATA_PARAMS(Z_Construct_UFunction_ULargeString_SetFromString_Statics::NewProp_InString_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeString_SetFromString_Statics::NewProp_InString_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULargeString_SetFromString_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeString_SetFromString_Statics::NewProp_InString,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeString_SetFromString_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LargeString.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULargeString_SetFromString_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULargeString, nullptr, "SetFromString", nullptr, nullptr, sizeof(LargeString_eventSetFromString_Parms), Z_Construct_UFunction_ULargeString_SetFromString_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeString_SetFromString_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULargeString_SetFromString_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeString_SetFromString_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULargeString_SetFromString()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULargeString_SetFromString_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULargeString_ToString_Statics
	{
		struct LargeString_eventToString_Parms
		{
			FString ReturnValue;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ULargeString_ToString_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeString_eventToString_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULargeString_ToString_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeString_ToString_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeString_ToString_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LargeString.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULargeString_ToString_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULargeString, nullptr, "ToString", nullptr, nullptr, sizeof(LargeString_eventToString_Parms), Z_Construct_UFunction_ULargeString_ToString_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeString_ToString_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULargeString_ToString_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeString_ToString_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULargeString_ToString()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULargeString_ToString_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ULargeString_NoRegister()
	{
		return ULargeString::StaticClass();
	}
	struct Z_Construct_UClass_ULargeString_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULargeString_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ULargeDataObject,
		(UObject* (*)())Z_Construct_UPackage__Script_LargeData,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULargeString_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULargeString_SetFromString, "SetFromString" }, // 3158196172
		{ &Z_Construct_UFunction_ULargeString_ToString, "ToString" }, // 2970418515
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULargeString_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "LargeString.h" },
		{ "ModuleRelativePath", "Public/LargeString.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULargeString_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULargeString>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULargeString_Statics::ClassParams = {
		&ULargeString::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_ULargeString_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULargeString_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULargeString()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULargeString_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULargeString, 2011264899);
	template<> LARGEDATA_API UClass* StaticClass<ULargeString>()
	{
		return ULargeString::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULargeString(Z_Construct_UClass_ULargeString, &ULargeString::StaticClass, TEXT("/Script/LargeData"), TEXT("ULargeString"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULargeString);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
