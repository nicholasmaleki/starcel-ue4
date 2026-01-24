// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLargeData_init() {}
	LARGEDATA_API UFunction* Z_Construct_UDelegateFunction_LargeData_OnLargeStringAsyncReceived__DelegateSignature();
	LARGEDATA_API UFunction* Z_Construct_UDelegateFunction_LargeData_OnChunksBuilt__DelegateSignature();
	LARGEDATA_API UFunction* Z_Construct_UDelegateFunction_LargeData_OnServerStringReceived__DelegateSignature();
	LARGEDATA_API UFunction* Z_Construct_UDelegateFunction_LargeData_OnClientStringReceived__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_LargeData()
	{
		static UPackage* ReturnPackage = nullptr;
		if (!ReturnPackage)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_LargeData_OnLargeStringAsyncReceived__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_LargeData_OnChunksBuilt__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_LargeData_OnServerStringReceived__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_LargeData_OnClientStringReceived__DelegateSignature,
			};
			static const UE4CodeGen_Private::FPackageParams PackageParams = {
				"/Script/LargeData",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x6089D061,
				0x356AD894,
				METADATA_PARAMS(nullptr, 0)
			};
			UE4CodeGen_Private::ConstructUPackage(ReturnPackage, PackageParams);
		}
		return ReturnPackage;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
