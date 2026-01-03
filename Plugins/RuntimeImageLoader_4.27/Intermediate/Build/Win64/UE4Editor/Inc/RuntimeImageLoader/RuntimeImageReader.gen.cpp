// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RuntimeImageLoader/Public/RuntimeImageReader.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRuntimeImageReader() {}
// Cross Module References
	RUNTIMEIMAGELOADER_API UScriptStruct* Z_Construct_UScriptStruct_FImageReadResult();
	UPackage* Z_Construct_UPackage__Script_RuntimeImageLoader();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FColor();
	ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UTextureCube_NoRegister();
	RUNTIMEIMAGELOADER_API UScriptStruct* Z_Construct_UScriptStruct_FTransformImageParams();
	ENGINE_API UEnum* Z_Construct_UEnum_Engine_TextureFilter();
	RUNTIMEIMAGELOADER_API UScriptStruct* Z_Construct_UScriptStruct_FInputImageDescription();
	RUNTIMEIMAGELOADER_API UClass* Z_Construct_UClass_URuntimeImageReader_NoRegister();
	RUNTIMEIMAGELOADER_API UClass* Z_Construct_UClass_URuntimeImageReader();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	RUNTIMEIMAGELOADER_API UClass* Z_Construct_UClass_URuntimeTextureFactory_NoRegister();
// End Cross Module References
class UScriptStruct* FImageReadResult::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern RUNTIMEIMAGELOADER_API uint32 Get_Z_Construct_UScriptStruct_FImageReadResult_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FImageReadResult, Z_Construct_UPackage__Script_RuntimeImageLoader(), TEXT("ImageReadResult"), sizeof(FImageReadResult), Get_Z_Construct_UScriptStruct_FImageReadResult_Hash());
	}
	return Singleton;
}
template<> RUNTIMEIMAGELOADER_API UScriptStruct* StaticStruct<FImageReadResult>()
{
	return FImageReadResult::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FImageReadResult(FImageReadResult::StaticStruct, TEXT("/Script/RuntimeImageLoader"), TEXT("ImageReadResult"), false, nullptr, nullptr);
static struct FScriptStruct_RuntimeImageLoader_StaticRegisterNativesFImageReadResult
{
	FScriptStruct_RuntimeImageLoader_StaticRegisterNativesFImageReadResult()
	{
		UScriptStruct::DeferCppStructOps<FImageReadResult>(FName(TEXT("ImageReadResult")));
	}
} ScriptStruct_RuntimeImageLoader_StaticRegisterNativesFImageReadResult;
	struct Z_Construct_UScriptStruct_FImageReadResult_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_OutImagePixels_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OutImagePixels_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_OutImagePixels;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OutTexture_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OutTexture;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OutTextureCube_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OutTextureCube;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FImageReadResult_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/RuntimeImageReader.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FImageReadResult_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FImageReadResult>();
	}
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FImageReadResult_Statics::NewProp_OutImagePixels_Inner = { "OutImagePixels", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FImageReadResult_Statics::NewProp_OutImagePixels_MetaData[] = {
		{ "ModuleRelativePath", "Public/RuntimeImageReader.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FImageReadResult_Statics::NewProp_OutImagePixels = { "OutImagePixels", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FImageReadResult, OutImagePixels), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FImageReadResult_Statics::NewProp_OutImagePixels_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FImageReadResult_Statics::NewProp_OutImagePixels_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FImageReadResult_Statics::NewProp_OutTexture_MetaData[] = {
		{ "ModuleRelativePath", "Public/RuntimeImageReader.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FImageReadResult_Statics::NewProp_OutTexture = { "OutTexture", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FImageReadResult, OutTexture), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(Z_Construct_UScriptStruct_FImageReadResult_Statics::NewProp_OutTexture_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FImageReadResult_Statics::NewProp_OutTexture_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FImageReadResult_Statics::NewProp_OutTextureCube_MetaData[] = {
		{ "ModuleRelativePath", "Public/RuntimeImageReader.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FImageReadResult_Statics::NewProp_OutTextureCube = { "OutTextureCube", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FImageReadResult, OutTextureCube), Z_Construct_UClass_UTextureCube_NoRegister, METADATA_PARAMS(Z_Construct_UScriptStruct_FImageReadResult_Statics::NewProp_OutTextureCube_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FImageReadResult_Statics::NewProp_OutTextureCube_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FImageReadResult_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FImageReadResult_Statics::NewProp_OutImagePixels_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FImageReadResult_Statics::NewProp_OutImagePixels,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FImageReadResult_Statics::NewProp_OutTexture,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FImageReadResult_Statics::NewProp_OutTextureCube,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FImageReadResult_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_RuntimeImageLoader,
		nullptr,
		&NewStructOps,
		"ImageReadResult",
		sizeof(FImageReadResult),
		alignof(FImageReadResult),
		Z_Construct_UScriptStruct_FImageReadResult_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FImageReadResult_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FImageReadResult_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FImageReadResult_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FImageReadResult()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FImageReadResult_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_RuntimeImageLoader();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("ImageReadResult"), sizeof(FImageReadResult), Get_Z_Construct_UScriptStruct_FImageReadResult_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FImageReadResult_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FImageReadResult_Hash() { return 3162717968U; }
class UScriptStruct* FTransformImageParams::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern RUNTIMEIMAGELOADER_API uint32 Get_Z_Construct_UScriptStruct_FTransformImageParams_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FTransformImageParams, Z_Construct_UPackage__Script_RuntimeImageLoader(), TEXT("TransformImageParams"), sizeof(FTransformImageParams), Get_Z_Construct_UScriptStruct_FTransformImageParams_Hash());
	}
	return Singleton;
}
template<> RUNTIMEIMAGELOADER_API UScriptStruct* StaticStruct<FTransformImageParams>()
{
	return FTransformImageParams::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FTransformImageParams(FTransformImageParams::StaticStruct, TEXT("/Script/RuntimeImageLoader"), TEXT("TransformImageParams"), false, nullptr, nullptr);
static struct FScriptStruct_RuntimeImageLoader_StaticRegisterNativesFTransformImageParams
{
	FScriptStruct_RuntimeImageLoader_StaticRegisterNativesFTransformImageParams()
	{
		UScriptStruct::DeferCppStructOps<FTransformImageParams>(FName(TEXT("TransformImageParams")));
	}
} ScriptStruct_RuntimeImageLoader_StaticRegisterNativesFTransformImageParams;
	struct Z_Construct_UScriptStruct_FTransformImageParams_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bForUI_MetaData[];
#endif
		static void NewProp_bForUI_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bForUI;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FilterMode_MetaData[];
#endif
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_FilterMode;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PercentSizeX_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_PercentSizeX;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PercentSizeY_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_PercentSizeY;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTransformImageParams_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/RuntimeImageReader.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTransformImageParams>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_bForUI_MetaData[] = {
		{ "Category", "Runtime Image Reader" },
		{ "ModuleRelativePath", "Public/RuntimeImageReader.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_bForUI_SetBit(void* Obj)
	{
		((FTransformImageParams*)Obj)->bForUI = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_bForUI = { "bForUI", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FTransformImageParams), &Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_bForUI_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_bForUI_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_bForUI_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_FilterMode_MetaData[] = {
		{ "Category", "Runtime Image Reader" },
		{ "ModuleRelativePath", "Public/RuntimeImageReader.h" },
	};
#endif
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_FilterMode = { "FilterMode", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FTransformImageParams, FilterMode), Z_Construct_UEnum_Engine_TextureFilter, METADATA_PARAMS(Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_FilterMode_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_FilterMode_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_PercentSizeX_MetaData[] = {
		{ "Category", "Runtime Image Reader" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/RuntimeImageReader.h" },
		{ "UIMax", "100" },
		{ "UIMin", "0" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_PercentSizeX = { "PercentSizeX", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FTransformImageParams, PercentSizeX), METADATA_PARAMS(Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_PercentSizeX_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_PercentSizeX_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_PercentSizeY_MetaData[] = {
		{ "Category", "Runtime Image Reader" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/RuntimeImageReader.h" },
		{ "UIMax", "100" },
		{ "UIMin", "0" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_PercentSizeY = { "PercentSizeY", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FTransformImageParams, PercentSizeY), METADATA_PARAMS(Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_PercentSizeY_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_PercentSizeY_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTransformImageParams_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_bForUI,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_FilterMode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_PercentSizeX,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTransformImageParams_Statics::NewProp_PercentSizeY,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTransformImageParams_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_RuntimeImageLoader,
		nullptr,
		&NewStructOps,
		"TransformImageParams",
		sizeof(FTransformImageParams),
		alignof(FTransformImageParams),
		Z_Construct_UScriptStruct_FTransformImageParams_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTransformImageParams_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FTransformImageParams_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTransformImageParams_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FTransformImageParams()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FTransformImageParams_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_RuntimeImageLoader();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("TransformImageParams"), sizeof(FTransformImageParams), Get_Z_Construct_UScriptStruct_FTransformImageParams_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FTransformImageParams_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FTransformImageParams_Hash() { return 3571832393U; }
class UScriptStruct* FInputImageDescription::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern RUNTIMEIMAGELOADER_API uint32 Get_Z_Construct_UScriptStruct_FInputImageDescription_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FInputImageDescription, Z_Construct_UPackage__Script_RuntimeImageLoader(), TEXT("InputImageDescription"), sizeof(FInputImageDescription), Get_Z_Construct_UScriptStruct_FInputImageDescription_Hash());
	}
	return Singleton;
}
template<> RUNTIMEIMAGELOADER_API UScriptStruct* StaticStruct<FInputImageDescription>()
{
	return FInputImageDescription::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FInputImageDescription(FInputImageDescription::StaticStruct, TEXT("/Script/RuntimeImageLoader"), TEXT("InputImageDescription"), false, nullptr, nullptr);
static struct FScriptStruct_RuntimeImageLoader_StaticRegisterNativesFInputImageDescription
{
	FScriptStruct_RuntimeImageLoader_StaticRegisterNativesFInputImageDescription()
	{
		UScriptStruct::DeferCppStructOps<FInputImageDescription>(FName(TEXT("InputImageDescription")));
	}
} ScriptStruct_RuntimeImageLoader_StaticRegisterNativesFInputImageDescription;
	struct Z_Construct_UScriptStruct_FInputImageDescription_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ImageFilename_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ImageFilename;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_ImageBytes_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ImageBytes_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ImageBytes;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FInputImageDescription_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/RuntimeImageReader.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FInputImageDescription_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FInputImageDescription>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FInputImageDescription_Statics::NewProp_ImageFilename_MetaData[] = {
		{ "ModuleRelativePath", "Public/RuntimeImageReader.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FInputImageDescription_Statics::NewProp_ImageFilename = { "ImageFilename", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FInputImageDescription, ImageFilename), METADATA_PARAMS(Z_Construct_UScriptStruct_FInputImageDescription_Statics::NewProp_ImageFilename_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FInputImageDescription_Statics::NewProp_ImageFilename_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FInputImageDescription_Statics::NewProp_ImageBytes_Inner = { "ImageBytes", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FInputImageDescription_Statics::NewProp_ImageBytes_MetaData[] = {
		{ "ModuleRelativePath", "Public/RuntimeImageReader.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FInputImageDescription_Statics::NewProp_ImageBytes = { "ImageBytes", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FInputImageDescription, ImageBytes), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FInputImageDescription_Statics::NewProp_ImageBytes_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FInputImageDescription_Statics::NewProp_ImageBytes_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FInputImageDescription_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInputImageDescription_Statics::NewProp_ImageFilename,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInputImageDescription_Statics::NewProp_ImageBytes_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInputImageDescription_Statics::NewProp_ImageBytes,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FInputImageDescription_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_RuntimeImageLoader,
		nullptr,
		&NewStructOps,
		"InputImageDescription",
		sizeof(FInputImageDescription),
		alignof(FInputImageDescription),
		Z_Construct_UScriptStruct_FInputImageDescription_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FInputImageDescription_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FInputImageDescription_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FInputImageDescription_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FInputImageDescription()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FInputImageDescription_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_RuntimeImageLoader();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("InputImageDescription"), sizeof(FInputImageDescription), Get_Z_Construct_UScriptStruct_FInputImageDescription_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FInputImageDescription_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FInputImageDescription_Hash() { return 3814749064U; }
	void URuntimeImageReader::StaticRegisterNativesURuntimeImageReader()
	{
	}
	UClass* Z_Construct_UClass_URuntimeImageReader_NoRegister()
	{
		return URuntimeImageReader::StaticClass();
	}
	struct Z_Construct_UClass_URuntimeImageReader_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Results_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Results_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Results;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PendingReadResult_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_PendingReadResult;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TextureFactory_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_TextureFactory;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_URuntimeImageReader_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_RuntimeImageLoader,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeImageReader_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "RuntimeImageReader.h" },
		{ "ModuleRelativePath", "Public/RuntimeImageReader.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_URuntimeImageReader_Statics::NewProp_Results_Inner = { "Results", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FImageReadResult, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeImageReader_Statics::NewProp_Results_MetaData[] = {
		{ "ModuleRelativePath", "Public/RuntimeImageReader.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_URuntimeImageReader_Statics::NewProp_Results = { "Results", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(URuntimeImageReader, Results), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_URuntimeImageReader_Statics::NewProp_Results_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeImageReader_Statics::NewProp_Results_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeImageReader_Statics::NewProp_PendingReadResult_MetaData[] = {
		{ "ModuleRelativePath", "Public/RuntimeImageReader.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_URuntimeImageReader_Statics::NewProp_PendingReadResult = { "PendingReadResult", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(URuntimeImageReader, PendingReadResult), Z_Construct_UScriptStruct_FImageReadResult, METADATA_PARAMS(Z_Construct_UClass_URuntimeImageReader_Statics::NewProp_PendingReadResult_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeImageReader_Statics::NewProp_PendingReadResult_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URuntimeImageReader_Statics::NewProp_TextureFactory_MetaData[] = {
		{ "ModuleRelativePath", "Public/RuntimeImageReader.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URuntimeImageReader_Statics::NewProp_TextureFactory = { "TextureFactory", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(URuntimeImageReader, TextureFactory), Z_Construct_UClass_URuntimeTextureFactory_NoRegister, METADATA_PARAMS(Z_Construct_UClass_URuntimeImageReader_Statics::NewProp_TextureFactory_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeImageReader_Statics::NewProp_TextureFactory_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_URuntimeImageReader_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URuntimeImageReader_Statics::NewProp_Results_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URuntimeImageReader_Statics::NewProp_Results,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URuntimeImageReader_Statics::NewProp_PendingReadResult,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URuntimeImageReader_Statics::NewProp_TextureFactory,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_URuntimeImageReader_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URuntimeImageReader>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_URuntimeImageReader_Statics::ClassParams = {
		&URuntimeImageReader::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_URuntimeImageReader_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeImageReader_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_URuntimeImageReader_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_URuntimeImageReader_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_URuntimeImageReader()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_URuntimeImageReader_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(URuntimeImageReader, 1829936875);
	template<> RUNTIMEIMAGELOADER_API UClass* StaticClass<URuntimeImageReader>()
	{
		return URuntimeImageReader::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_URuntimeImageReader(Z_Construct_UClass_URuntimeImageReader, &URuntimeImageReader::StaticClass, TEXT("/Script/RuntimeImageLoader"), TEXT("URuntimeImageReader"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(URuntimeImageReader);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
