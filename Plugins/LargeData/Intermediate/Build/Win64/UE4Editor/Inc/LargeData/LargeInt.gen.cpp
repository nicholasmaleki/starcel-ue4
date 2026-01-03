// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LargeData/Public/LargeInt.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLargeInt() {}
// Cross Module References
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeInt_NoRegister();
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeInt();
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeDataObject();
	UPackage* Z_Construct_UPackage__Script_LargeData();
// End Cross Module References
	DEFINE_FUNCTION(ULargeInt::execToString)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->ToString();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULargeInt::execSetFromString)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetFromString(Z_Param_Value);
		P_NATIVE_END;
	}
	void ULargeInt::StaticRegisterNativesULargeInt()
	{
		UClass* Class = ULargeInt::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "SetFromString", &ULargeInt::execSetFromString },
			{ "ToString", &ULargeInt::execToString },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULargeInt_SetFromString_Statics
	{
		struct LargeInt_eventSetFromString_Parms
		{
			FString Value;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeInt_SetFromString_Statics::NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ULargeInt_SetFromString_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeInt_eventSetFromString_Parms, Value), METADATA_PARAMS(Z_Construct_UFunction_ULargeInt_SetFromString_Statics::NewProp_Value_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeInt_SetFromString_Statics::NewProp_Value_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULargeInt_SetFromString_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeInt_SetFromString_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeInt_SetFromString_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LargeInt.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULargeInt_SetFromString_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULargeInt, nullptr, "SetFromString", nullptr, nullptr, sizeof(LargeInt_eventSetFromString_Parms), Z_Construct_UFunction_ULargeInt_SetFromString_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeInt_SetFromString_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULargeInt_SetFromString_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeInt_SetFromString_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULargeInt_SetFromString()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULargeInt_SetFromString_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULargeInt_ToString_Statics
	{
		struct LargeInt_eventToString_Parms
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
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ULargeInt_ToString_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeInt_eventToString_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULargeInt_ToString_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeInt_ToString_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeInt_ToString_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LargeInt.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULargeInt_ToString_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULargeInt, nullptr, "ToString", nullptr, nullptr, sizeof(LargeInt_eventToString_Parms), Z_Construct_UFunction_ULargeInt_ToString_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeInt_ToString_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULargeInt_ToString_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeInt_ToString_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULargeInt_ToString()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULargeInt_ToString_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ULargeInt_NoRegister()
	{
		return ULargeInt::StaticClass();
	}
	struct Z_Construct_UClass_ULargeInt_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULargeInt_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ULargeDataObject,
		(UObject* (*)())Z_Construct_UPackage__Script_LargeData,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULargeInt_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULargeInt_SetFromString, "SetFromString" }, // 2473204434
		{ &Z_Construct_UFunction_ULargeInt_ToString, "ToString" }, // 147982051
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULargeInt_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "LargeInt.h" },
		{ "ModuleRelativePath", "Public/LargeInt.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULargeInt_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULargeInt>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULargeInt_Statics::ClassParams = {
		&ULargeInt::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_ULargeInt_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULargeInt_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULargeInt()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULargeInt_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULargeInt, 1520369058);
	template<> LARGEDATA_API UClass* StaticClass<ULargeInt>()
	{
		return ULargeInt::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULargeInt(Z_Construct_UClass_ULargeInt, &ULargeInt::StaticClass, TEXT("/Script/LargeData"), TEXT("ULargeInt"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULargeInt);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
