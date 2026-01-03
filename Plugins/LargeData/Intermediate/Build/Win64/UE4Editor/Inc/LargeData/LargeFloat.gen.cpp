// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LargeData/Public/LargeFloat.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLargeFloat() {}
// Cross Module References
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeFloat_NoRegister();
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeFloat();
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeDataObject();
	UPackage* Z_Construct_UPackage__Script_LargeData();
// End Cross Module References
	DEFINE_FUNCTION(ULargeFloat::execToString)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->ToString();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULargeFloat::execSetFromString)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InDecimal);
		P_GET_PROPERTY(FIntProperty,Z_Param_PrecisionBits);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetFromString(Z_Param_InDecimal,Z_Param_PrecisionBits);
		P_NATIVE_END;
	}
	void ULargeFloat::StaticRegisterNativesULargeFloat()
	{
		UClass* Class = ULargeFloat::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "SetFromString", &ULargeFloat::execSetFromString },
			{ "ToString", &ULargeFloat::execToString },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULargeFloat_SetFromString_Statics
	{
		struct LargeFloat_eventSetFromString_Parms
		{
			FString InDecimal;
			int32 PrecisionBits;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InDecimal_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_InDecimal;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_PrecisionBits;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeFloat_SetFromString_Statics::NewProp_InDecimal_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ULargeFloat_SetFromString_Statics::NewProp_InDecimal = { "InDecimal", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeFloat_eventSetFromString_Parms, InDecimal), METADATA_PARAMS(Z_Construct_UFunction_ULargeFloat_SetFromString_Statics::NewProp_InDecimal_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeFloat_SetFromString_Statics::NewProp_InDecimal_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULargeFloat_SetFromString_Statics::NewProp_PrecisionBits = { "PrecisionBits", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeFloat_eventSetFromString_Parms, PrecisionBits), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULargeFloat_SetFromString_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeFloat_SetFromString_Statics::NewProp_InDecimal,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeFloat_SetFromString_Statics::NewProp_PrecisionBits,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeFloat_SetFromString_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LargeFloat.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULargeFloat_SetFromString_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULargeFloat, nullptr, "SetFromString", nullptr, nullptr, sizeof(LargeFloat_eventSetFromString_Parms), Z_Construct_UFunction_ULargeFloat_SetFromString_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeFloat_SetFromString_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULargeFloat_SetFromString_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeFloat_SetFromString_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULargeFloat_SetFromString()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULargeFloat_SetFromString_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULargeFloat_ToString_Statics
	{
		struct LargeFloat_eventToString_Parms
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
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ULargeFloat_ToString_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeFloat_eventToString_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULargeFloat_ToString_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeFloat_ToString_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeFloat_ToString_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LargeFloat.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULargeFloat_ToString_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULargeFloat, nullptr, "ToString", nullptr, nullptr, sizeof(LargeFloat_eventToString_Parms), Z_Construct_UFunction_ULargeFloat_ToString_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeFloat_ToString_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULargeFloat_ToString_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeFloat_ToString_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULargeFloat_ToString()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULargeFloat_ToString_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ULargeFloat_NoRegister()
	{
		return ULargeFloat::StaticClass();
	}
	struct Z_Construct_UClass_ULargeFloat_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULargeFloat_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ULargeDataObject,
		(UObject* (*)())Z_Construct_UPackage__Script_LargeData,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULargeFloat_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULargeFloat_SetFromString, "SetFromString" }, // 4203441139
		{ &Z_Construct_UFunction_ULargeFloat_ToString, "ToString" }, // 156085432
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULargeFloat_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "LargeFloat.h" },
		{ "ModuleRelativePath", "Public/LargeFloat.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULargeFloat_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULargeFloat>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULargeFloat_Statics::ClassParams = {
		&ULargeFloat::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_ULargeFloat_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULargeFloat_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULargeFloat()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULargeFloat_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULargeFloat, 4015275455);
	template<> LARGEDATA_API UClass* StaticClass<ULargeFloat>()
	{
		return ULargeFloat::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULargeFloat(Z_Construct_UClass_ULargeFloat, &ULargeFloat::StaticClass, TEXT("/Script/LargeData"), TEXT("ULargeFloat"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULargeFloat);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
