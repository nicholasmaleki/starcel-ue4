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
void EmptyLinkFunctionForGeneratedCodeHISPlayer_init() {}
	HISPLAYER_API UFunction* Z_Construct_UDelegateFunction_HISPlayer_EventDelegateNoParam__DelegateSignature();
	HISPLAYER_API UFunction* Z_Construct_UDelegateFunction_HISPlayer_EventDelegatePercentage__DelegateSignature();
	HISPLAYER_API UFunction* Z_Construct_UDelegateFunction_HISPlayer_EventDelegateStatus__DelegateSignature();
	HISPLAYER_API UFunction* Z_Construct_UDelegateFunction_HISPlayer_EventDelegateResolution__DelegateSignature();
	HISPLAYER_API UFunction* Z_Construct_UDelegateFunction_HISPlayer_EventDelegateError__DelegateSignature();
	HISPLAYER_API UFunction* Z_Construct_UDelegateFunction_HISPlayer_EventDelegateTimedMetadata__DelegateSignature();
	HISPLAYER_API UFunction* Z_Construct_UDelegateFunction_HISPlayer_EventDelegatePCMData__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_HISPlayer()
	{
		static UPackage* ReturnPackage = nullptr;
		if (!ReturnPackage)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_HISPlayer_EventDelegateNoParam__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_HISPlayer_EventDelegatePercentage__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_HISPlayer_EventDelegateStatus__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_HISPlayer_EventDelegateResolution__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_HISPlayer_EventDelegateError__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_HISPlayer_EventDelegateTimedMetadata__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_HISPlayer_EventDelegatePCMData__DelegateSignature,
			};
			static const UE4CodeGen_Private::FPackageParams PackageParams = {
				"/Script/HISPlayer",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x497E0734,
				0x0F8A0FC0,
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
