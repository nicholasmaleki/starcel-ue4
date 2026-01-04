// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWindowCapture2D_init() {}
	WINDOWCAPTURE2D_API UFunction* Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature();
	WINDOWCAPTURE2D_API UFunction* Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature();
	WINDOWCAPTURE2D_API UFunction* Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureWidgetChangeTexture__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_WindowCapture2D;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_WindowCapture2D()
	{
		if (!Z_Registration_Info_UPackage__Script_WindowCapture2D.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_WindowCapture2D_CaptureMachineChangeTexture__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureActorChangeTexture__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_WindowCapture2D_WindowCaptureWidgetChangeTexture__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/WindowCapture2D",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x4C75C42B,
				0x48816D86,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_WindowCapture2D.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_WindowCapture2D.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_WindowCapture2D(Z_Construct_UPackage__Script_WindowCapture2D, TEXT("/Script/WindowCapture2D"), Z_Registration_Info_UPackage__Script_WindowCapture2D, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x4C75C42B, 0x48816D86));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
