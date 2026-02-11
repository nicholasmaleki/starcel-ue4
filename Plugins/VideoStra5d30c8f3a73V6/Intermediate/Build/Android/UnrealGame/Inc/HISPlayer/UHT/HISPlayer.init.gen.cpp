// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHISPlayer_init() {}
	HISPLAYER_API UFunction* Z_Construct_UDelegateFunction_HISPlayer_EventDelegateError__DelegateSignature();
	HISPLAYER_API UFunction* Z_Construct_UDelegateFunction_HISPlayer_EventDelegateNoParam__DelegateSignature();
	HISPLAYER_API UFunction* Z_Construct_UDelegateFunction_HISPlayer_EventDelegatePCMData__DelegateSignature();
	HISPLAYER_API UFunction* Z_Construct_UDelegateFunction_HISPlayer_EventDelegatePercentage__DelegateSignature();
	HISPLAYER_API UFunction* Z_Construct_UDelegateFunction_HISPlayer_EventDelegateResolution__DelegateSignature();
	HISPLAYER_API UFunction* Z_Construct_UDelegateFunction_HISPlayer_EventDelegateStatus__DelegateSignature();
	HISPLAYER_API UFunction* Z_Construct_UDelegateFunction_HISPlayer_EventDelegateTimedMetadata__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_HISPlayer;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_HISPlayer()
	{
		if (!Z_Registration_Info_UPackage__Script_HISPlayer.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_HISPlayer_EventDelegateError__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_HISPlayer_EventDelegateNoParam__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_HISPlayer_EventDelegatePCMData__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_HISPlayer_EventDelegatePercentage__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_HISPlayer_EventDelegateResolution__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_HISPlayer_EventDelegateStatus__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_HISPlayer_EventDelegateTimedMetadata__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/HISPlayer",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0xD2053470,
				0x39F92FBE,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_HISPlayer.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_HISPlayer.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_HISPlayer(Z_Construct_UPackage__Script_HISPlayer, TEXT("/Script/HISPlayer"), Z_Registration_Info_UPackage__Script_HISPlayer, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xD2053470, 0x39F92FBE));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
