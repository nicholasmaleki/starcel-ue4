// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HISPlayer/Public/HISPlayerFunctions.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHISPlayerFunctions() {}
// Cross Module References
	HISPLAYER_API UClass* Z_Construct_UClass_UHISPlayerFunctions_NoRegister();
	HISPLAYER_API UClass* Z_Construct_UClass_UHISPlayerFunctions();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_HISPlayer();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntPoint();
	ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
	HISPLAYER_API UClass* Z_Construct_UClass_UDelegateManager_NoRegister();
	HISPLAYER_API UEnum* Z_Construct_UEnum_HISPlayer_HISPlayerStatus();
	HISPLAYER_API UScriptStruct* Z_Construct_UScriptStruct_FHISPlayerTrack();
	HISPLAYER_API UScriptStruct* Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FLatentActionInfo();
// End Cross Module References
	DEFINE_FUNCTION(UHISPlayerFunctions::execChangeVideoContent)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_GET_PROPERTY(FStrProperty,Z_Param_url);
		P_FINISH;
		P_NATIVE_BEGIN;
		UHISPlayerFunctions::ChangeVideoContent(Z_Param_streamIndex,Z_Param_url);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execSelectTrack)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_GET_PROPERTY(FIntProperty,Z_Param_trackIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		UHISPlayerFunctions::SelectTrack(Z_Param_streamIndex,Z_Param_trackIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execGetTrackID)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_GET_PROPERTY(FIntProperty,Z_Param_trackIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=UHISPlayerFunctions::GetTrackID(Z_Param_streamIndex,Z_Param_trackIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execGetTrackHeight)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_GET_PROPERTY(FIntProperty,Z_Param_trackIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=UHISPlayerFunctions::GetTrackHeight(Z_Param_streamIndex,Z_Param_trackIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execGetTrackWidth)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_GET_PROPERTY(FIntProperty,Z_Param_trackIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=UHISPlayerFunctions::GetTrackWidth(Z_Param_streamIndex,Z_Param_trackIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execGetTrackFramerate)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_GET_PROPERTY(FIntProperty,Z_Param_trackIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=UHISPlayerFunctions::GetTrackFramerate(Z_Param_streamIndex,Z_Param_trackIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execGetTrackBitrate)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_GET_PROPERTY(FIntProperty,Z_Param_trackIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=UHISPlayerFunctions::GetTrackBitrate(Z_Param_streamIndex,Z_Param_trackIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execGetTracks)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FHISPlayerTrack>*)Z_Param__Result=UHISPlayerFunctions::GetTracks(Z_Param_streamIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execGetTrackCount)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=UHISPlayerFunctions::GetTrackCount(Z_Param_streamIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execGetVideoWidth)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=UHISPlayerFunctions::GetVideoWidth(Z_Param_streamIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execGetVideoHeight)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=UHISPlayerFunctions::GetVideoHeight(Z_Param_streamIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execSetPlaybackProperties)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_GET_STRUCT_REF(FHISPlayerPlaybackProperties,Z_Param_Out_Properties);
		P_FINISH;
		P_NATIVE_BEGIN;
		UHISPlayerFunctions::SetPlaybackProperties(Z_Param_streamIndex,Z_Param_Out_Properties);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execGetDelegateManager)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UDelegateManager**)Z_Param__Result=UHISPlayerFunctions::GetDelegateManager(Z_Param_streamIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execGetPlayerStatus)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(HISPlayerStatus*)Z_Param__Result=UHISPlayerFunctions::GetPlayerStatus(Z_Param_streamIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execClose)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		UHISPlayerFunctions::Close(Z_Param_streamIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execGetTotalTime)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=UHISPlayerFunctions::GetTotalTime(Z_Param_streamIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execGetCurrentPosition)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=UHISPlayerFunctions::GetCurrentPosition(Z_Param_streamIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execSetMute)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_GET_UBOOL(Z_Param_isMute);
		P_FINISH;
		P_NATIVE_BEGIN;
		UHISPlayerFunctions::SetMute(Z_Param_streamIndex,Z_Param_isMute);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execGetPlaybackRate)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=UHISPlayerFunctions::GetPlaybackRate(Z_Param_streamIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execSetPlaybackRate)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_GET_PROPERTY(FFloatProperty,Z_Param_rate);
		P_FINISH;
		P_NATIVE_BEGIN;
		UHISPlayerFunctions::SetPlaybackRate(Z_Param_streamIndex,Z_Param_rate);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execSetVolume)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_GET_PROPERTY(FFloatProperty,Z_Param_newVolume);
		P_FINISH;
		P_NATIVE_BEGIN;
		UHISPlayerFunctions::SetVolume(Z_Param_streamIndex,Z_Param_newVolume);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execSeek)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_GET_PROPERTY(FIntProperty,Z_Param_msec);
		P_FINISH;
		P_NATIVE_BEGIN;
		UHISPlayerFunctions::Seek(Z_Param_streamIndex,Z_Param_msec);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execStop)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		UHISPlayerFunctions::Stop(Z_Param_streamIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execPause)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		UHISPlayerFunctions::Pause(Z_Param_streamIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execResume)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		UHISPlayerFunctions::Resume(Z_Param_streamIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execUpdate)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		UHISPlayerFunctions::Update(Z_Param_streamIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execOpenPlayer)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_GET_PROPERTY(FStrProperty,Z_Param_url);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=UHISPlayerFunctions::OpenPlayer(Z_Param_streamIndex,Z_Param_url);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execCreateNewTexture)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_GET_STRUCT(FIntPoint,Z_Param_resolution);
		P_GET_OBJECT_REF(UTexture2D,Z_Param_Out_outputTexture);
		P_FINISH;
		P_NATIVE_BEGIN;
		UHISPlayerFunctions::CreateNewTexture(Z_Param_streamIndex,Z_Param_resolution,Z_Param_Out_outputTexture);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execSetup)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_streamIndex);
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
		P_GET_OBJECT_REF(UTexture2D,Z_Param_Out_outputTexture);
		P_GET_STRUCT(FLatentActionInfo,Z_Param_LatentInfo);
		P_FINISH;
		P_NATIVE_BEGIN;
		UHISPlayerFunctions::Setup(Z_Param_streamIndex,Z_Param_WorldContextObject,Z_Param_Out_outputTexture,Z_Param_LatentInfo);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHISPlayerFunctions::execBeginPlay)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_numStreams);
		P_FINISH;
		P_NATIVE_BEGIN;
		UHISPlayerFunctions::BeginPlay(Z_Param_numStreams);
		P_NATIVE_END;
	}
	void UHISPlayerFunctions::StaticRegisterNativesUHISPlayerFunctions()
	{
		UClass* Class = UHISPlayerFunctions::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "BeginPlay", &UHISPlayerFunctions::execBeginPlay },
			{ "ChangeVideoContent", &UHISPlayerFunctions::execChangeVideoContent },
			{ "Close", &UHISPlayerFunctions::execClose },
			{ "CreateNewTexture", &UHISPlayerFunctions::execCreateNewTexture },
			{ "GetCurrentPosition", &UHISPlayerFunctions::execGetCurrentPosition },
			{ "GetDelegateManager", &UHISPlayerFunctions::execGetDelegateManager },
			{ "GetPlaybackRate", &UHISPlayerFunctions::execGetPlaybackRate },
			{ "GetPlayerStatus", &UHISPlayerFunctions::execGetPlayerStatus },
			{ "GetTotalTime", &UHISPlayerFunctions::execGetTotalTime },
			{ "GetTrackBitrate", &UHISPlayerFunctions::execGetTrackBitrate },
			{ "GetTrackCount", &UHISPlayerFunctions::execGetTrackCount },
			{ "GetTrackFramerate", &UHISPlayerFunctions::execGetTrackFramerate },
			{ "GetTrackHeight", &UHISPlayerFunctions::execGetTrackHeight },
			{ "GetTrackID", &UHISPlayerFunctions::execGetTrackID },
			{ "GetTracks", &UHISPlayerFunctions::execGetTracks },
			{ "GetTrackWidth", &UHISPlayerFunctions::execGetTrackWidth },
			{ "GetVideoHeight", &UHISPlayerFunctions::execGetVideoHeight },
			{ "GetVideoWidth", &UHISPlayerFunctions::execGetVideoWidth },
			{ "OpenPlayer", &UHISPlayerFunctions::execOpenPlayer },
			{ "Pause", &UHISPlayerFunctions::execPause },
			{ "Resume", &UHISPlayerFunctions::execResume },
			{ "Seek", &UHISPlayerFunctions::execSeek },
			{ "SelectTrack", &UHISPlayerFunctions::execSelectTrack },
			{ "SetMute", &UHISPlayerFunctions::execSetMute },
			{ "SetPlaybackProperties", &UHISPlayerFunctions::execSetPlaybackProperties },
			{ "SetPlaybackRate", &UHISPlayerFunctions::execSetPlaybackRate },
			{ "Setup", &UHISPlayerFunctions::execSetup },
			{ "SetVolume", &UHISPlayerFunctions::execSetVolume },
			{ "Stop", &UHISPlayerFunctions::execStop },
			{ "Update", &UHISPlayerFunctions::execUpdate },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_BeginPlay_Statics
	{
		struct HISPlayerFunctions_eventBeginPlay_Parms
		{
			int32 numStreams;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_numStreams;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_BeginPlay_Statics::NewProp_numStreams = { "numStreams", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventBeginPlay_Parms, numStreams), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_BeginPlay_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_BeginPlay_Statics::NewProp_numStreams,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_BeginPlay_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09* Pre-initialize HISPlayer, minimal code needed to be called on BeginPlay\n\x09*/" },
		{ "DisplayName", "HISPlayer BeginPlay" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Pre-initialize HISPlayer, minimal code needed to be called on BeginPlay" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_BeginPlay_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "BeginPlay", nullptr, nullptr, sizeof(HISPlayerFunctions_eventBeginPlay_Parms), Z_Construct_UFunction_UHISPlayerFunctions_BeginPlay_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_BeginPlay_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_BeginPlay_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_BeginPlay_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_BeginPlay()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_BeginPlay_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_ChangeVideoContent_Statics
	{
		struct HISPlayerFunctions_eventChangeVideoContent_Parms
		{
			int32 streamIndex;
			FString url;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_url_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_url;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_ChangeVideoContent_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventChangeVideoContent_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_ChangeVideoContent_Statics::NewProp_url_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_ChangeVideoContent_Statics::NewProp_url = { "url", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventChangeVideoContent_Parms, url), METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_ChangeVideoContent_Statics::NewProp_url_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_ChangeVideoContent_Statics::NewProp_url_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_ChangeVideoContent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_ChangeVideoContent_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_ChangeVideoContent_Statics::NewProp_url,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_ChangeVideoContent_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09* Change Video Content\n\x09*\n\x09* Use this method to change the content of a Stream at runtime.\n\x09* @param Stream Index\n\x09* @param Content URL\n\x09*/" },
		{ "DisplayName", "HISPlayer Change Video Content" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Change Video Content\n\nUse this method to change the content of a Stream at runtime.\n@param Stream Index\n@param Content URL" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_ChangeVideoContent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "ChangeVideoContent", nullptr, nullptr, sizeof(HISPlayerFunctions_eventChangeVideoContent_Parms), Z_Construct_UFunction_UHISPlayerFunctions_ChangeVideoContent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_ChangeVideoContent_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_ChangeVideoContent_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_ChangeVideoContent_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_ChangeVideoContent()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_ChangeVideoContent_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_Close_Statics
	{
		struct HISPlayerFunctions_eventClose_Parms
		{
			int32 streamIndex;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_Close_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventClose_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_Close_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_Close_Statics::NewProp_streamIndex,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_Close_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09 * Method for closing and releasing HISPlayer\n\x09 * @param Stream index\n\x09 */" },
		{ "DisplayName", "HISPlayer Close" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Method for closing and releasing HISPlayer\n@param Stream index" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_Close_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "Close", nullptr, nullptr, sizeof(HISPlayerFunctions_eventClose_Parms), Z_Construct_UFunction_UHISPlayerFunctions_Close_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_Close_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_Close_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_Close_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_Close()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_Close_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_CreateNewTexture_Statics
	{
		struct HISPlayerFunctions_eventCreateNewTexture_Parms
		{
			int32 streamIndex;
			FIntPoint resolution;
			UTexture2D* outputTexture;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_resolution;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_outputTexture;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_CreateNewTexture_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventCreateNewTexture_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_CreateNewTexture_Statics::NewProp_resolution = { "resolution", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventCreateNewTexture_Parms, resolution), Z_Construct_UScriptStruct_FIntPoint, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_CreateNewTexture_Statics::NewProp_outputTexture = { "outputTexture", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventCreateNewTexture_Parms, outputTexture), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_CreateNewTexture_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_CreateNewTexture_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_CreateNewTexture_Statics::NewProp_resolution,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_CreateNewTexture_Statics::NewProp_outputTexture,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_CreateNewTexture_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09 * Create a new texture of a new resolution\n\x09 * @param Stream index\n\x09 * @param FIntPoint for resolution. X value for Width, Y value for Height.\n\x09 */" },
		{ "DisplayName", "HISPlayer Create New Texture" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Create a new texture of a new resolution\n@param Stream index\n@param FIntPoint for resolution. X value for Width, Y value for Height." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_CreateNewTexture_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "CreateNewTexture", nullptr, nullptr, sizeof(HISPlayerFunctions_eventCreateNewTexture_Parms), Z_Construct_UFunction_UHISPlayerFunctions_CreateNewTexture_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_CreateNewTexture_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_CreateNewTexture_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_CreateNewTexture_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_CreateNewTexture()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_CreateNewTexture_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_GetCurrentPosition_Statics
	{
		struct HISPlayerFunctions_eventGetCurrentPosition_Parms
		{
			int32 streamIndex;
			int32 ReturnValue;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetCurrentPosition_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetCurrentPosition_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetCurrentPosition_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetCurrentPosition_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_GetCurrentPosition_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetCurrentPosition_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetCurrentPosition_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_GetCurrentPosition_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09 * Returns the current time position of the current track\n\x09 * @param Stream index\n\x09 */" },
		{ "DisplayName", "HISPlayer GetCurrentPosition" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Returns the current time position of the current track\n@param Stream index" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_GetCurrentPosition_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "GetCurrentPosition", nullptr, nullptr, sizeof(HISPlayerFunctions_eventGetCurrentPosition_Parms), Z_Construct_UFunction_UHISPlayerFunctions_GetCurrentPosition_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetCurrentPosition_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_GetCurrentPosition_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetCurrentPosition_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_GetCurrentPosition()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_GetCurrentPosition_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_GetDelegateManager_Statics
	{
		struct HISPlayerFunctions_eventGetDelegateManager_Parms
		{
			int32 streamIndex;
			UDelegateManager* ReturnValue;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetDelegateManager_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetDelegateManager_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetDelegateManager_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetDelegateManager_Parms, ReturnValue), Z_Construct_UClass_UDelegateManager_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_GetDelegateManager_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetDelegateManager_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetDelegateManager_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_GetDelegateManager_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09* Get the Delegate Manager\n\x09* @param Stream index\n\x09*/" },
		{ "DisplayName", "HISPlayer Get Delegate Manager" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Get the Delegate Manager\n@param Stream index" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_GetDelegateManager_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "GetDelegateManager", nullptr, nullptr, sizeof(HISPlayerFunctions_eventGetDelegateManager_Parms), Z_Construct_UFunction_UHISPlayerFunctions_GetDelegateManager_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetDelegateManager_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_GetDelegateManager_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetDelegateManager_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_GetDelegateManager()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_GetDelegateManager_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_GetPlaybackRate_Statics
	{
		struct HISPlayerFunctions_eventGetPlaybackRate_Parms
		{
			int32 streamIndex;
			float ReturnValue;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetPlaybackRate_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetPlaybackRate_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetPlaybackRate_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetPlaybackRate_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_GetPlaybackRate_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetPlaybackRate_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetPlaybackRate_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_GetPlaybackRate_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09* Get Current Playback Speed Rate\n\x09*\n\x09* @param Stream index\n\x09* @return Current Playback Rate\n\x09*/" },
		{ "DisplayName", "HISPlayer Get Playback Rate" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Get Current Playback Speed Rate\n\n@param Stream index\n@return Current Playback Rate" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_GetPlaybackRate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "GetPlaybackRate", nullptr, nullptr, sizeof(HISPlayerFunctions_eventGetPlaybackRate_Parms), Z_Construct_UFunction_UHISPlayerFunctions_GetPlaybackRate_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetPlaybackRate_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_GetPlaybackRate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetPlaybackRate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_GetPlaybackRate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_GetPlaybackRate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_GetPlayerStatus_Statics
	{
		struct HISPlayerFunctions_eventGetPlayerStatus_Parms
		{
			int32 streamIndex;
			HISPlayerStatus ReturnValue;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetPlayerStatus_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetPlayerStatus_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetPlayerStatus_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetPlayerStatus_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetPlayerStatus_Parms, ReturnValue), Z_Construct_UEnum_HISPlayer_HISPlayerStatus, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_GetPlayerStatus_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetPlayerStatus_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetPlayerStatus_Statics::NewProp_ReturnValue_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetPlayerStatus_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_GetPlayerStatus_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09* Get the player status\n\x09* @param Stream index\n\x09*/" },
		{ "DisplayName", "HISPlayer Get Player Status" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Get the player status\n@param Stream index" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_GetPlayerStatus_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "GetPlayerStatus", nullptr, nullptr, sizeof(HISPlayerFunctions_eventGetPlayerStatus_Parms), Z_Construct_UFunction_UHISPlayerFunctions_GetPlayerStatus_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetPlayerStatus_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_GetPlayerStatus_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetPlayerStatus_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_GetPlayerStatus()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_GetPlayerStatus_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_GetTotalTime_Statics
	{
		struct HISPlayerFunctions_eventGetTotalTime_Parms
		{
			int32 streamIndex;
			int32 ReturnValue;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTotalTime_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetTotalTime_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTotalTime_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetTotalTime_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_GetTotalTime_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTotalTime_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTotalTime_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_GetTotalTime_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09 * Returns the total time of the current track\n\x09 * @param Stream index\n\x09 */" },
		{ "DisplayName", "HISPlayer GetTotalTime" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Returns the total time of the current track\n@param Stream index" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_GetTotalTime_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "GetTotalTime", nullptr, nullptr, sizeof(HISPlayerFunctions_eventGetTotalTime_Parms), Z_Construct_UFunction_UHISPlayerFunctions_GetTotalTime_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetTotalTime_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_GetTotalTime_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetTotalTime_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_GetTotalTime()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_GetTotalTime_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_GetTrackBitrate_Statics
	{
		struct HISPlayerFunctions_eventGetTrackBitrate_Parms
		{
			int32 streamIndex;
			int32 trackIndex;
			int32 ReturnValue;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_trackIndex;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackBitrate_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetTrackBitrate_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackBitrate_Statics::NewProp_trackIndex = { "trackIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetTrackBitrate_Parms, trackIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackBitrate_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetTrackBitrate_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_GetTrackBitrate_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTrackBitrate_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTrackBitrate_Statics::NewProp_trackIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTrackBitrate_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_GetTrackBitrate_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09* Get the bitrate of a certain track of a certain stream\n\x09* @param Stream index\n\x09* @param Track index\n\x09*/" },
		{ "DisplayName", "HISPlayer Get Track Bitrate" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Get the bitrate of a certain track of a certain stream\n@param Stream index\n@param Track index" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackBitrate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "GetTrackBitrate", nullptr, nullptr, sizeof(HISPlayerFunctions_eventGetTrackBitrate_Parms), Z_Construct_UFunction_UHISPlayerFunctions_GetTrackBitrate_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetTrackBitrate_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_GetTrackBitrate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetTrackBitrate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_GetTrackBitrate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_GetTrackBitrate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_GetTrackCount_Statics
	{
		struct HISPlayerFunctions_eventGetTrackCount_Parms
		{
			int32 streamIndex;
			int32 ReturnValue;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackCount_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetTrackCount_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackCount_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetTrackCount_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_GetTrackCount_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTrackCount_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTrackCount_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_GetTrackCount_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09* Get the number of tracks of a certain stream\n\x09* @param Stream index\n\x09* @param Track index\n\x09*/" },
		{ "DisplayName", "HISPlayer Get Track Count" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Get the number of tracks of a certain stream\n@param Stream index\n@param Track index" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackCount_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "GetTrackCount", nullptr, nullptr, sizeof(HISPlayerFunctions_eventGetTrackCount_Parms), Z_Construct_UFunction_UHISPlayerFunctions_GetTrackCount_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetTrackCount_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_GetTrackCount_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetTrackCount_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_GetTrackCount()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_GetTrackCount_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_GetTrackFramerate_Statics
	{
		struct HISPlayerFunctions_eventGetTrackFramerate_Parms
		{
			int32 streamIndex;
			int32 trackIndex;
			float ReturnValue;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_trackIndex;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackFramerate_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetTrackFramerate_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackFramerate_Statics::NewProp_trackIndex = { "trackIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetTrackFramerate_Parms, trackIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackFramerate_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetTrackFramerate_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_GetTrackFramerate_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTrackFramerate_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTrackFramerate_Statics::NewProp_trackIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTrackFramerate_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_GetTrackFramerate_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09* Get the framerate of a certain track of a certain stream\n\x09* @param Stream index\n\x09* @param Track index\n\x09*/" },
		{ "DisplayName", "HISPlayer Get Track Framerate" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Get the framerate of a certain track of a certain stream\n@param Stream index\n@param Track index" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackFramerate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "GetTrackFramerate", nullptr, nullptr, sizeof(HISPlayerFunctions_eventGetTrackFramerate_Parms), Z_Construct_UFunction_UHISPlayerFunctions_GetTrackFramerate_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetTrackFramerate_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_GetTrackFramerate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetTrackFramerate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_GetTrackFramerate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_GetTrackFramerate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_GetTrackHeight_Statics
	{
		struct HISPlayerFunctions_eventGetTrackHeight_Parms
		{
			int32 streamIndex;
			int32 trackIndex;
			int32 ReturnValue;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_trackIndex;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackHeight_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetTrackHeight_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackHeight_Statics::NewProp_trackIndex = { "trackIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetTrackHeight_Parms, trackIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackHeight_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetTrackHeight_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_GetTrackHeight_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTrackHeight_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTrackHeight_Statics::NewProp_trackIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTrackHeight_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_GetTrackHeight_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09* Get the width of a certain track of a certain stream\n\x09* @param Stream index\n\x09* @param Track index\n\x09*/" },
		{ "DisplayName", "HISPlayer Get Track Height" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Get the width of a certain track of a certain stream\n@param Stream index\n@param Track index" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackHeight_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "GetTrackHeight", nullptr, nullptr, sizeof(HISPlayerFunctions_eventGetTrackHeight_Parms), Z_Construct_UFunction_UHISPlayerFunctions_GetTrackHeight_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetTrackHeight_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_GetTrackHeight_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetTrackHeight_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_GetTrackHeight()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_GetTrackHeight_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_GetTrackID_Statics
	{
		struct HISPlayerFunctions_eventGetTrackID_Parms
		{
			int32 streamIndex;
			int32 trackIndex;
			FString ReturnValue;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_trackIndex;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackID_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetTrackID_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackID_Statics::NewProp_trackIndex = { "trackIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetTrackID_Parms, trackIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackID_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetTrackID_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_GetTrackID_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTrackID_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTrackID_Statics::NewProp_trackIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTrackID_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_GetTrackID_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09* Get the ID of a certain track of a certain stream\n\x09* @param Stream index\n\x09* @param Track index\n\x09*/" },
		{ "DisplayName", "HISPlayer Get Track ID" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Get the ID of a certain track of a certain stream\n@param Stream index\n@param Track index" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackID_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "GetTrackID", nullptr, nullptr, sizeof(HISPlayerFunctions_eventGetTrackID_Parms), Z_Construct_UFunction_UHISPlayerFunctions_GetTrackID_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetTrackID_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_GetTrackID_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetTrackID_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_GetTrackID()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_GetTrackID_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_GetTracks_Statics
	{
		struct HISPlayerFunctions_eventGetTracks_Parms
		{
			int32 streamIndex;
			TArray<FHISPlayerTrack> ReturnValue;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTracks_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetTracks_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTracks_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FHISPlayerTrack, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTracks_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetTracks_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_GetTracks_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTracks_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTracks_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTracks_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_GetTracks_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09* Provides information about the tracks of a certain stream\n\x09* @param Stream index\n\x09* @param Track index\n\x09*/" },
		{ "DisplayName", "HISPlayer Get Tracks" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Provides information about the tracks of a certain stream\n@param Stream index\n@param Track index" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_GetTracks_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "GetTracks", nullptr, nullptr, sizeof(HISPlayerFunctions_eventGetTracks_Parms), Z_Construct_UFunction_UHISPlayerFunctions_GetTracks_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetTracks_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_GetTracks_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetTracks_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_GetTracks()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_GetTracks_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_GetTrackWidth_Statics
	{
		struct HISPlayerFunctions_eventGetTrackWidth_Parms
		{
			int32 streamIndex;
			int32 trackIndex;
			int32 ReturnValue;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_trackIndex;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackWidth_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetTrackWidth_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackWidth_Statics::NewProp_trackIndex = { "trackIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetTrackWidth_Parms, trackIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackWidth_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetTrackWidth_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_GetTrackWidth_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTrackWidth_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTrackWidth_Statics::NewProp_trackIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetTrackWidth_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_GetTrackWidth_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09* Get the width of a certain track of a certain stream\n\x09* @param Stream index\n\x09* @param Track index\n\x09*/" },
		{ "DisplayName", "HISPlayer Get Track Width" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Get the width of a certain track of a certain stream\n@param Stream index\n@param Track index" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_GetTrackWidth_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "GetTrackWidth", nullptr, nullptr, sizeof(HISPlayerFunctions_eventGetTrackWidth_Parms), Z_Construct_UFunction_UHISPlayerFunctions_GetTrackWidth_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetTrackWidth_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_GetTrackWidth_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetTrackWidth_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_GetTrackWidth()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_GetTrackWidth_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_GetVideoHeight_Statics
	{
		struct HISPlayerFunctions_eventGetVideoHeight_Parms
		{
			int32 streamIndex;
			int32 ReturnValue;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetVideoHeight_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetVideoHeight_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetVideoHeight_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetVideoHeight_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_GetVideoHeight_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetVideoHeight_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetVideoHeight_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_GetVideoHeight_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09* Get the height of the current track of a certain stream\n\x09* @param Stream index\n\x09*/" },
		{ "DisplayName", "HISPlayer Get Video Height" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Get the height of the current track of a certain stream\n@param Stream index" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_GetVideoHeight_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "GetVideoHeight", nullptr, nullptr, sizeof(HISPlayerFunctions_eventGetVideoHeight_Parms), Z_Construct_UFunction_UHISPlayerFunctions_GetVideoHeight_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetVideoHeight_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_GetVideoHeight_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetVideoHeight_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_GetVideoHeight()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_GetVideoHeight_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_GetVideoWidth_Statics
	{
		struct HISPlayerFunctions_eventGetVideoWidth_Parms
		{
			int32 streamIndex;
			int32 ReturnValue;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetVideoWidth_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetVideoWidth_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_GetVideoWidth_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventGetVideoWidth_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_GetVideoWidth_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetVideoWidth_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_GetVideoWidth_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_GetVideoWidth_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09* Get the width of the current track of a certain stream\n\x09* @param Stream index\n\x09*/" },
		{ "DisplayName", "HISPlayer Get Video Width" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Get the width of the current track of a certain stream\n@param Stream index" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_GetVideoWidth_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "GetVideoWidth", nullptr, nullptr, sizeof(HISPlayerFunctions_eventGetVideoWidth_Parms), Z_Construct_UFunction_UHISPlayerFunctions_GetVideoWidth_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetVideoWidth_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_GetVideoWidth_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_GetVideoWidth_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_GetVideoWidth()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_GetVideoWidth_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_OpenPlayer_Statics
	{
		struct HISPlayerFunctions_eventOpenPlayer_Parms
		{
			int32 streamIndex;
			FString url;
			int32 ReturnValue;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_url_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_url;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_OpenPlayer_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventOpenPlayer_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_OpenPlayer_Statics::NewProp_url_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_OpenPlayer_Statics::NewProp_url = { "url", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventOpenPlayer_Parms, url), METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_OpenPlayer_Statics::NewProp_url_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_OpenPlayer_Statics::NewProp_url_MetaData)) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_OpenPlayer_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventOpenPlayer_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_OpenPlayer_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_OpenPlayer_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_OpenPlayer_Statics::NewProp_url,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_OpenPlayer_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_OpenPlayer_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09 * Start HISPlayer\n\x09 * @param Stream index\n\x09 */" },
		{ "DisplayName", "HISPlayer Open Player" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Start HISPlayer\n@param Stream index" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_OpenPlayer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "OpenPlayer", nullptr, nullptr, sizeof(HISPlayerFunctions_eventOpenPlayer_Parms), Z_Construct_UFunction_UHISPlayerFunctions_OpenPlayer_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_OpenPlayer_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_OpenPlayer_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_OpenPlayer_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_OpenPlayer()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_OpenPlayer_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_Pause_Statics
	{
		struct HISPlayerFunctions_eventPause_Parms
		{
			int32 streamIndex;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_Pause_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventPause_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_Pause_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_Pause_Statics::NewProp_streamIndex,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_Pause_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09 * Pause the video\n\x09 * @param Stream index\n\x09 */" },
		{ "DisplayName", "HISPlayer Pause" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Pause the video\n@param Stream index" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_Pause_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "Pause", nullptr, nullptr, sizeof(HISPlayerFunctions_eventPause_Parms), Z_Construct_UFunction_UHISPlayerFunctions_Pause_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_Pause_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_Pause_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_Pause_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_Pause()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_Pause_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_Resume_Statics
	{
		struct HISPlayerFunctions_eventResume_Parms
		{
			int32 streamIndex;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_Resume_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventResume_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_Resume_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_Resume_Statics::NewProp_streamIndex,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_Resume_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09 * Resume the paused or stopped video.\n\x09 * @param Stream index\n\x09 */" },
		{ "DisplayName", "HISPlayer Resume" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Resume the paused or stopped video.\n@param Stream index" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_Resume_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "Resume", nullptr, nullptr, sizeof(HISPlayerFunctions_eventResume_Parms), Z_Construct_UFunction_UHISPlayerFunctions_Resume_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_Resume_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_Resume_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_Resume_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_Resume()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_Resume_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_Seek_Statics
	{
		struct HISPlayerFunctions_eventSeek_Parms
		{
			int32 streamIndex;
			int32 msec;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_msec;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_Seek_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventSeek_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_Seek_Statics::NewProp_msec = { "msec", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventSeek_Parms, msec), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_Seek_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_Seek_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_Seek_Statics::NewProp_msec,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_Seek_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09 * Seeks the video to a certain position\n\x09 * @param Stream index\n\x09 * @param msec\n\x09 */" },
		{ "DisplayName", "HISPlayer Seek" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Seeks the video to a certain position\n@param Stream index\n@param msec" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_Seek_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "Seek", nullptr, nullptr, sizeof(HISPlayerFunctions_eventSeek_Parms), Z_Construct_UFunction_UHISPlayerFunctions_Seek_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_Seek_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_Seek_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_Seek_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_Seek()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_Seek_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_SelectTrack_Statics
	{
		struct HISPlayerFunctions_eventSelectTrack_Parms
		{
			int32 streamIndex;
			int32 trackIndex;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_trackIndex;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_SelectTrack_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventSelectTrack_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_SelectTrack_Statics::NewProp_trackIndex = { "trackIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventSelectTrack_Parms, trackIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_SelectTrack_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_SelectTrack_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_SelectTrack_Statics::NewProp_trackIndex,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_SelectTrack_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09* Select a certain track of a certain stream to be used as the main track. The possible tracks can be obtained from the tracks returned from the method GetTracks.\n\x09* The playerIndex is associated with the index of the element of Multi Stream Properties\n\x09* @param Stream index\n\x09*/" },
		{ "DisplayName", "HISPlayer Select Track" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Select a certain track of a certain stream to be used as the main track. The possible tracks can be obtained from the tracks returned from the method GetTracks.\nThe playerIndex is associated with the index of the element of Multi Stream Properties\n@param Stream index" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_SelectTrack_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "SelectTrack", nullptr, nullptr, sizeof(HISPlayerFunctions_eventSelectTrack_Parms), Z_Construct_UFunction_UHISPlayerFunctions_SelectTrack_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_SelectTrack_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_SelectTrack_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_SelectTrack_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_SelectTrack()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_SelectTrack_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_SetMute_Statics
	{
		struct HISPlayerFunctions_eventSetMute_Parms
		{
			int32 streamIndex;
			bool isMute;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static void NewProp_isMute_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_isMute;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_SetMute_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventSetMute_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UHISPlayerFunctions_SetMute_Statics::NewProp_isMute_SetBit(void* Obj)
	{
		((HISPlayerFunctions_eventSetMute_Parms*)Obj)->isMute = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_SetMute_Statics::NewProp_isMute = { "isMute", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(HISPlayerFunctions_eventSetMute_Parms), &Z_Construct_UFunction_UHISPlayerFunctions_SetMute_Statics::NewProp_isMute_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_SetMute_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_SetMute_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_SetMute_Statics::NewProp_isMute,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_SetMute_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09 * Mute the player\n\x09 * @param Stream index\n\x09 * @param isMute\n\x09 */" },
		{ "DisplayName", "HISPlayer SetMute" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Mute the player\n@param Stream index\n@param isMute" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_SetMute_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "SetMute", nullptr, nullptr, sizeof(HISPlayerFunctions_eventSetMute_Parms), Z_Construct_UFunction_UHISPlayerFunctions_SetMute_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_SetMute_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_SetMute_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_SetMute_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_SetMute()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_SetMute_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackProperties_Statics
	{
		struct HISPlayerFunctions_eventSetPlaybackProperties_Parms
		{
			int32 streamIndex;
			FHISPlayerPlaybackProperties Properties;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Properties_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Properties;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackProperties_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventSetPlaybackProperties_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackProperties_Statics::NewProp_Properties_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackProperties_Statics::NewProp_Properties = { "Properties", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventSetPlaybackProperties_Parms, Properties), Z_Construct_UScriptStruct_FHISPlayerPlaybackProperties, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackProperties_Statics::NewProp_Properties_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackProperties_Statics::NewProp_Properties_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackProperties_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackProperties_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackProperties_Statics::NewProp_Properties,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackProperties_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09* Set the current playback properties of the stream\n\x09* @param Stream index\n\x09* @param PlayerPlaybackProperties type.\n\x09* @return PlayerPlaybackProperties type.\n\x09*/" },
		{ "DisplayName", "HISPlayer Set PlayBack Properties" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Set the current playback properties of the stream\n@param Stream index\n@param PlayerPlaybackProperties type.\n@return PlayerPlaybackProperties type." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackProperties_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "SetPlaybackProperties", nullptr, nullptr, sizeof(HISPlayerFunctions_eventSetPlaybackProperties_Parms), Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackProperties_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackProperties_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackProperties_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackProperties_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackProperties()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackProperties_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackRate_Statics
	{
		struct HISPlayerFunctions_eventSetPlaybackRate_Parms
		{
			int32 streamIndex;
			float rate;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_rate;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackRate_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventSetPlaybackRate_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackRate_Statics::NewProp_rate = { "rate", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventSetPlaybackRate_Parms, rate), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackRate_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackRate_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackRate_Statics::NewProp_rate,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackRate_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09* Set Playback Speed Rate\n\x09*\n\x09* @param Stream index\n\x09* @param Playback Speed Rate. (Example: 1.0 = 100% speed, 1.5 = 150% speed, 0.75 = 75% speed)\n\x09* .\n\x09*/" },
		{ "DisplayName", "HISPlayer Set Playback Rate" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Set Playback Speed Rate\n\n@param Stream index\n@param Playback Speed Rate. (Example: 1.0 = 100% speed, 1.5 = 150% speed, 0.75 = 75% speed)\n." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackRate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "SetPlaybackRate", nullptr, nullptr, sizeof(HISPlayerFunctions_eventSetPlaybackRate_Parms), Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackRate_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackRate_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackRate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackRate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackRate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackRate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_Setup_Statics
	{
		struct HISPlayerFunctions_eventSetup_Parms
		{
			int32 streamIndex;
			UObject* WorldContextObject;
			UTexture2D* outputTexture;
			FLatentActionInfo LatentInfo;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_outputTexture;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_LatentInfo;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_Setup_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventSetup_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_Setup_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventSetup_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_Setup_Statics::NewProp_outputTexture = { "outputTexture", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventSetup_Parms, outputTexture), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_Setup_Statics::NewProp_LatentInfo = { "LatentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventSetup_Parms, LatentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_Setup_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_Setup_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_Setup_Statics::NewProp_WorldContextObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_Setup_Statics::NewProp_outputTexture,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_Setup_Statics::NewProp_LatentInfo,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_Setup_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09* Initialize HISPlayer, needed before using the player. It internally creates a texture in runtime.\n\x09*/" },
		{ "DefaultToSelf", "WorldContextObject" },
		{ "DisplayName", "HISPlayer Setup" },
		{ "Latent", "" },
		{ "LatentInfo", "LatentInfo" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Initialize HISPlayer, needed before using the player. It internally creates a texture in runtime." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_Setup_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "Setup", nullptr, nullptr, sizeof(HISPlayerFunctions_eventSetup_Parms), Z_Construct_UFunction_UHISPlayerFunctions_Setup_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_Setup_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_Setup_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_Setup_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_Setup()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_Setup_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_SetVolume_Statics
	{
		struct HISPlayerFunctions_eventSetVolume_Parms
		{
			int32 streamIndex;
			float newVolume;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_newVolume;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_SetVolume_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventSetVolume_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_SetVolume_Statics::NewProp_newVolume = { "newVolume", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventSetVolume_Parms, newVolume), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_SetVolume_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_SetVolume_Statics::NewProp_streamIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_SetVolume_Statics::NewProp_newVolume,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_SetVolume_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09 * Set a new value for the volume of the player\n\x09 * @param Stream index\n\x09 * @param newVolume - must be included in the range [0.0f,1.0f]\n\x09 */" },
		{ "DisplayName", "HISPlayer SetVolume" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Set a new value for the volume of the player\n@param Stream index\n@param newVolume - must be included in the range [0.0f,1.0f]" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_SetVolume_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "SetVolume", nullptr, nullptr, sizeof(HISPlayerFunctions_eventSetVolume_Parms), Z_Construct_UFunction_UHISPlayerFunctions_SetVolume_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_SetVolume_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_SetVolume_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_SetVolume_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_SetVolume()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_SetVolume_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_Stop_Statics
	{
		struct HISPlayerFunctions_eventStop_Parms
		{
			int32 streamIndex;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_Stop_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventStop_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_Stop_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_Stop_Statics::NewProp_streamIndex,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_Stop_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09 * Stops the video and next time you press play, it begins from start\n\x09 * @param Stream index\n\x09 */" },
		{ "DisplayName", "HISPlayer Stop" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Stops the video and next time you press play, it begins from start\n@param Stream index" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_Stop_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "Stop", nullptr, nullptr, sizeof(HISPlayerFunctions_eventStop_Parms), Z_Construct_UFunction_UHISPlayerFunctions_Stop_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_Stop_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_Stop_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_Stop_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_Stop()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_Stop_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHISPlayerFunctions_Update_Statics
	{
		struct HISPlayerFunctions_eventUpdate_Parms
		{
			int32 streamIndex;
		};
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_streamIndex;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UHISPlayerFunctions_Update_Statics::NewProp_streamIndex = { "streamIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HISPlayerFunctions_eventUpdate_Parms, streamIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHISPlayerFunctions_Update_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHISPlayerFunctions_Update_Statics::NewProp_streamIndex,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHISPlayerFunctions_Update_Statics::Function_MetaDataParams[] = {
		{ "Category", "HISPlayer" },
		{ "Comment", "/**\n\x09 * Update each frame, needs to be called every frame\n\x09 * @param Stream index\n\x09 */" },
		{ "DisplayName", "HISPlayer Update" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
		{ "ToolTip", "Update each frame, needs to be called every frame\n@param Stream index" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHISPlayerFunctions_Update_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHISPlayerFunctions, nullptr, "Update", nullptr, nullptr, sizeof(HISPlayerFunctions_eventUpdate_Parms), Z_Construct_UFunction_UHISPlayerFunctions_Update_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_Update_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHISPlayerFunctions_Update_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHISPlayerFunctions_Update_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHISPlayerFunctions_Update()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHISPlayerFunctions_Update_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UHISPlayerFunctions_NoRegister()
	{
		return UHISPlayerFunctions::StaticClass();
	}
	struct Z_Construct_UClass_UHISPlayerFunctions_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UHISPlayerFunctions_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_HISPlayer,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UHISPlayerFunctions_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UHISPlayerFunctions_BeginPlay, "BeginPlay" }, // 986377436
		{ &Z_Construct_UFunction_UHISPlayerFunctions_ChangeVideoContent, "ChangeVideoContent" }, // 4231048429
		{ &Z_Construct_UFunction_UHISPlayerFunctions_Close, "Close" }, // 3373179058
		{ &Z_Construct_UFunction_UHISPlayerFunctions_CreateNewTexture, "CreateNewTexture" }, // 383547553
		{ &Z_Construct_UFunction_UHISPlayerFunctions_GetCurrentPosition, "GetCurrentPosition" }, // 63632866
		{ &Z_Construct_UFunction_UHISPlayerFunctions_GetDelegateManager, "GetDelegateManager" }, // 2893140006
		{ &Z_Construct_UFunction_UHISPlayerFunctions_GetPlaybackRate, "GetPlaybackRate" }, // 4221156324
		{ &Z_Construct_UFunction_UHISPlayerFunctions_GetPlayerStatus, "GetPlayerStatus" }, // 444502020
		{ &Z_Construct_UFunction_UHISPlayerFunctions_GetTotalTime, "GetTotalTime" }, // 2931501183
		{ &Z_Construct_UFunction_UHISPlayerFunctions_GetTrackBitrate, "GetTrackBitrate" }, // 1203884848
		{ &Z_Construct_UFunction_UHISPlayerFunctions_GetTrackCount, "GetTrackCount" }, // 785957849
		{ &Z_Construct_UFunction_UHISPlayerFunctions_GetTrackFramerate, "GetTrackFramerate" }, // 1119594867
		{ &Z_Construct_UFunction_UHISPlayerFunctions_GetTrackHeight, "GetTrackHeight" }, // 2068264562
		{ &Z_Construct_UFunction_UHISPlayerFunctions_GetTrackID, "GetTrackID" }, // 2467413336
		{ &Z_Construct_UFunction_UHISPlayerFunctions_GetTracks, "GetTracks" }, // 3560555877
		{ &Z_Construct_UFunction_UHISPlayerFunctions_GetTrackWidth, "GetTrackWidth" }, // 2199921475
		{ &Z_Construct_UFunction_UHISPlayerFunctions_GetVideoHeight, "GetVideoHeight" }, // 2118253113
		{ &Z_Construct_UFunction_UHISPlayerFunctions_GetVideoWidth, "GetVideoWidth" }, // 1509494727
		{ &Z_Construct_UFunction_UHISPlayerFunctions_OpenPlayer, "OpenPlayer" }, // 3882980202
		{ &Z_Construct_UFunction_UHISPlayerFunctions_Pause, "Pause" }, // 3942889869
		{ &Z_Construct_UFunction_UHISPlayerFunctions_Resume, "Resume" }, // 1416726540
		{ &Z_Construct_UFunction_UHISPlayerFunctions_Seek, "Seek" }, // 2599738831
		{ &Z_Construct_UFunction_UHISPlayerFunctions_SelectTrack, "SelectTrack" }, // 2233704959
		{ &Z_Construct_UFunction_UHISPlayerFunctions_SetMute, "SetMute" }, // 621759924
		{ &Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackProperties, "SetPlaybackProperties" }, // 4166321071
		{ &Z_Construct_UFunction_UHISPlayerFunctions_SetPlaybackRate, "SetPlaybackRate" }, // 3255837456
		{ &Z_Construct_UFunction_UHISPlayerFunctions_Setup, "Setup" }, // 3326484336
		{ &Z_Construct_UFunction_UHISPlayerFunctions_SetVolume, "SetVolume" }, // 3687643865
		{ &Z_Construct_UFunction_UHISPlayerFunctions_Stop, "Stop" }, // 4252630546
		{ &Z_Construct_UFunction_UHISPlayerFunctions_Update, "Update" }, // 3122144614
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHISPlayerFunctions_Statics::Class_MetaDataParams[] = {
		{ "DisplayName", "HISPlayer Unreal" },
		{ "IncludePath", "HISPlayerFunctions.h" },
		{ "IsBlueprintBase", "false" },
		{ "ModuleRelativePath", "Public/HISPlayerFunctions.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UHISPlayerFunctions_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHISPlayerFunctions>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UHISPlayerFunctions_Statics::ClassParams = {
		&UHISPlayerFunctions::StaticClass,
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
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UHISPlayerFunctions_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UHISPlayerFunctions_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UHISPlayerFunctions()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UHISPlayerFunctions_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UHISPlayerFunctions, 2470834316);
	template<> HISPLAYER_API UClass* StaticClass<UHISPlayerFunctions>()
	{
		return UHISPlayerFunctions::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UHISPlayerFunctions(Z_Construct_UClass_UHISPlayerFunctions, &UHISPlayerFunctions::StaticClass, TEXT("/Script/HISPlayer"), TEXT("UHISPlayerFunctions"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UHISPlayerFunctions);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
