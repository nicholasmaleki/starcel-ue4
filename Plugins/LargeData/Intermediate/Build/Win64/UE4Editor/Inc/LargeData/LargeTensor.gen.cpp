// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LargeData/Public/LargeTensor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLargeTensor() {}
// Cross Module References
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeTensor_NoRegister();
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeTensor();
	LARGEDATA_API UClass* Z_Construct_UClass_ULargeDataObject();
	UPackage* Z_Construct_UPackage__Script_LargeData();
	LARGEDATA_API UScriptStruct* Z_Construct_UScriptStruct_FLargeTensorRegionUpdate();
// End Cross Module References
	DEFINE_FUNCTION(ULargeTensor::execUpdateRegion)
	{
		P_GET_TARRAY_REF(int64,Z_Param_Out_Start);
		P_GET_TARRAY_REF(int64,Z_Param_Out_Extent);
		P_GET_TARRAY_REF(uint8,Z_Param_Out_RawData);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->UpdateRegion(Z_Param_Out_Start,Z_Param_Out_Extent,Z_Param_Out_RawData);
		P_NATIVE_END;
	}
	void ULargeTensor::StaticRegisterNativesULargeTensor()
	{
		UClass* Class = ULargeTensor::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "UpdateRegion", &ULargeTensor::execUpdateRegion },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics
	{
		struct LargeTensor_eventUpdateRegion_Parms
		{
			TArray<int64> Start;
			TArray<int64> Extent;
			TArray<uint8> RawData;
		};
		static const UE4CodeGen_Private::FInt64PropertyParams NewProp_Start_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Start_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Start;
		static const UE4CodeGen_Private::FInt64PropertyParams NewProp_Extent_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Extent_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Extent;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_RawData_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RawData_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_RawData;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FInt64PropertyParams Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::NewProp_Start_Inner = { "Start", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int64, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::NewProp_Start_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::NewProp_Start = { "Start", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeTensor_eventUpdateRegion_Parms, Start), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::NewProp_Start_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::NewProp_Start_MetaData)) };
	const UE4CodeGen_Private::FInt64PropertyParams Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::NewProp_Extent_Inner = { "Extent", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int64, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::NewProp_Extent_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::NewProp_Extent = { "Extent", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeTensor_eventUpdateRegion_Parms, Extent), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::NewProp_Extent_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::NewProp_Extent_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::NewProp_RawData_Inner = { "RawData", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::NewProp_RawData_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::NewProp_RawData = { "RawData", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LargeTensor_eventUpdateRegion_Parms, RawData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::NewProp_RawData_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::NewProp_RawData_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::NewProp_Start_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::NewProp_Start,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::NewProp_Extent_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::NewProp_Extent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::NewProp_RawData_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::NewProp_RawData,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LargeTensor.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULargeTensor, nullptr, "UpdateRegion", nullptr, nullptr, sizeof(LargeTensor_eventUpdateRegion_Parms), Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULargeTensor_UpdateRegion()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULargeTensor_UpdateRegion_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ULargeTensor_NoRegister()
	{
		return ULargeTensor::StaticClass();
	}
	struct Z_Construct_UClass_ULargeTensor_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_RegionUpdates_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RegionUpdates_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_RegionUpdates;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULargeTensor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ULargeDataObject,
		(UObject* (*)())Z_Construct_UPackage__Script_LargeData,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULargeTensor_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULargeTensor_UpdateRegion, "UpdateRegion" }, // 1396434414
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULargeTensor_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "LargeTensor.h" },
		{ "ModuleRelativePath", "Public/LargeTensor.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULargeTensor_Statics::NewProp_RegionUpdates_Inner = { "RegionUpdates", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLargeTensorRegionUpdate, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULargeTensor_Statics::NewProp_RegionUpdates_MetaData[] = {
		{ "ModuleRelativePath", "Public/LargeTensor.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ULargeTensor_Statics::NewProp_RegionUpdates = { "RegionUpdates", nullptr, (EPropertyFlags)0x0020080000000020, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULargeTensor, RegionUpdates), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ULargeTensor_Statics::NewProp_RegionUpdates_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULargeTensor_Statics::NewProp_RegionUpdates_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULargeTensor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULargeTensor_Statics::NewProp_RegionUpdates_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULargeTensor_Statics::NewProp_RegionUpdates,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULargeTensor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULargeTensor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULargeTensor_Statics::ClassParams = {
		&ULargeTensor::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ULargeTensor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ULargeTensor_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_ULargeTensor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULargeTensor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULargeTensor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULargeTensor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULargeTensor, 1414865567);
	template<> LARGEDATA_API UClass* StaticClass<ULargeTensor>()
	{
		return ULargeTensor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULargeTensor(Z_Construct_UClass_ULargeTensor, &ULargeTensor::StaticClass, TEXT("/Script/LargeData"), TEXT("ULargeTensor"), false, nullptr, nullptr, nullptr);

	void ULargeTensor::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
	{
		static const FName Name_RegionUpdates(TEXT("RegionUpdates"));

		const bool bIsValid = true
			&& Name_RegionUpdates == ClassReps[(int32)ENetFields_Private::RegionUpdates].Property->GetFName();

		checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in ULargeTensor"));
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULargeTensor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
