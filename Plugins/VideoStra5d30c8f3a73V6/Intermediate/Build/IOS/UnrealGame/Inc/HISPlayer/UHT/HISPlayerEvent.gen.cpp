// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HISPlayer/Public/HISPlayerTypes/HISPlayerEvent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHISPlayerEvent() {}
// Cross Module References
	HISPLAYER_API UEnum* Z_Construct_UEnum_HISPlayer_HISPlayerEvent();
	UPackage* Z_Construct_UPackage__Script_HISPlayer();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_HISPlayerEvent;
	static UEnum* HISPlayerEvent_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_HISPlayerEvent.OuterSingleton)
		{
			Z_Registration_Info_UEnum_HISPlayerEvent.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_HISPlayer_HISPlayerEvent, Z_Construct_UPackage__Script_HISPlayer(), TEXT("HISPlayerEvent"));
		}
		return Z_Registration_Info_UEnum_HISPlayerEvent.OuterSingleton;
	}
	template<> HISPLAYER_API UEnum* StaticEnum<HISPlayerEvent>()
	{
		return HISPlayerEvent_StaticEnum();
	}
	struct Z_Construct_UEnum_HISPlayer_HISPlayerEvent_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_HISPlayer_HISPlayerEvent_Statics::Enumerators[] = {
		{ "HISPlayerEvent::NONE", (int64)HISPlayerEvent::NONE },
		{ "HISPlayerEvent::INIT_COMPLETE", (int64)HISPlayerEvent::INIT_COMPLETE },
		{ "HISPlayerEvent::PLAYBACK_STARTED", (int64)HISPlayerEvent::PLAYBACK_STARTED },
		{ "HISPlayerEvent::END_OF_CONTENT", (int64)HISPlayerEvent::END_OF_CONTENT },
		{ "HISPlayerEvent::BUFFERING_ENDED", (int64)HISPlayerEvent::BUFFERING_ENDED },
		{ "HISPlayerEvent::TEXTURE_CHANGED", (int64)HISPlayerEvent::TEXTURE_CHANGED },
		{ "HISPlayerEvent::TRACK_CHANGED", (int64)HISPlayerEvent::TRACK_CHANGED },
		{ "HISPlayerEvent::PLAYBACK_PAUSED", (int64)HISPlayerEvent::PLAYBACK_PAUSED },
		{ "HISPlayerEvent::STOPPED", (int64)HISPlayerEvent::STOPPED },
		{ "HISPlayerEvent::SEEKED", (int64)HISPlayerEvent::SEEKED },
		{ "HISPlayerEvent::BUFFERING", (int64)HISPlayerEvent::BUFFERING },
		{ "HISPlayerEvent::EXTERNAL_PCM", (int64)HISPlayerEvent::EXTERNAL_PCM },
		{ "HISPlayerEvent::LOADING", (int64)HISPlayerEvent::LOADING },
		{ "HISPlayerEvent::TIMED_METADATA_RENDER", (int64)HISPlayerEvent::TIMED_METADATA_RENDER },
		{ "HISPlayerEvent::SERVER_CONNECTION", (int64)HISPlayerEvent::SERVER_CONNECTION },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_HISPlayer_HISPlayerEvent_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "BUFFERING.Comment", "// The player has seeked\n" },
		{ "BUFFERING.DisplayName", "Buffering" },
		{ "BUFFERING.Name", "HISPlayerEvent::BUFFERING" },
		{ "BUFFERING.ToolTip", "The player has seeked" },
		{ "BUFFERING_ENDED.Comment", "// The player has reached the end of the video playback\n" },
		{ "BUFFERING_ENDED.DisplayName", "Ended" },
		{ "BUFFERING_ENDED.Name", "HISPlayerEvent::BUFFERING_ENDED" },
		{ "BUFFERING_ENDED.ToolTip", "The player has reached the end of the video playback" },
		{ "Category", "HISPlayer|Types" },
		{ "END_OF_CONTENT.Comment", "// The player has started playing the video\n" },
		{ "END_OF_CONTENT.DisplayName", "End of content" },
		{ "END_OF_CONTENT.Name", "HISPlayerEvent::END_OF_CONTENT" },
		{ "END_OF_CONTENT.ToolTip", "The player has started playing the video" },
		{ "EXTERNAL_PCM.Comment", "// The player is buffering\n" },
		{ "EXTERNAL_PCM.DisplayName", "On External PCM received" },
		{ "EXTERNAL_PCM.Name", "HISPlayerEvent::EXTERNAL_PCM" },
		{ "EXTERNAL_PCM.ToolTip", "The player is buffering" },
		{ "INIT_COMPLETE.Comment", "// No or unknown event\n" },
		{ "INIT_COMPLETE.DisplayName", "Init complete" },
		{ "INIT_COMPLETE.Name", "HISPlayerEvent::INIT_COMPLETE" },
		{ "INIT_COMPLETE.ToolTip", "No or unknown event" },
		{ "LOADING.Comment", "// The player is buffering\n" },
		{ "LOADING.DisplayName", "Loading" },
		{ "LOADING.Name", "HISPlayerEvent::LOADING" },
		{ "LOADING.ToolTip", "The player is buffering" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISPlayerEvent.h" },
		{ "NONE.DisplayName", "None" },
		{ "NONE.Name", "HISPlayerEvent::NONE" },
		{ "PLAYBACK_PAUSED.Comment", "// The track of the playback has changed. This is especially useful for protocols with several resolution tracks (ABR)\n" },
		{ "PLAYBACK_PAUSED.DisplayName", "Paused" },
		{ "PLAYBACK_PAUSED.Name", "HISPlayerEvent::PLAYBACK_PAUSED" },
		{ "PLAYBACK_PAUSED.ToolTip", "The track of the playback has changed. This is especially useful for protocols with several resolution tracks (ABR)" },
		{ "PLAYBACK_STARTED.Comment", "// The Player has been initialized, but it's not playing \n" },
		{ "PLAYBACK_STARTED.DisplayName", "Started" },
		{ "PLAYBACK_STARTED.Name", "HISPlayerEvent::PLAYBACK_STARTED" },
		{ "PLAYBACK_STARTED.ToolTip", "The Player has been initialized, but it's not playing" },
		{ "SEEKED.Comment", "// The player has been closed\n" },
		{ "SEEKED.DisplayName", "Seeked" },
		{ "SEEKED.Name", "HISPlayerEvent::SEEKED" },
		{ "SEEKED.ToolTip", "The player has been closed" },
		{ "SERVER_CONNECTION.DisplayName", "Server Connection" },
		{ "SERVER_CONNECTION.Name", "HISPlayerEvent::SERVER_CONNECTION" },
		{ "STOPPED.Comment", "// The playback has been paused\n" },
		{ "STOPPED.DisplayName", "Stopped" },
		{ "STOPPED.Name", "HISPlayerEvent::STOPPED" },
		{ "STOPPED.ToolTip", "The playback has been paused" },
		{ "TEXTURE_CHANGED.Comment", "// The player has buffered enough content and has resume the playback. Wait for this event before starting playback.\n" },
		{ "TEXTURE_CHANGED.DisplayName", "Texture Changed" },
		{ "TEXTURE_CHANGED.Name", "HISPlayerEvent::TEXTURE_CHANGED" },
		{ "TEXTURE_CHANGED.ToolTip", "The player has buffered enough content and has resume the playback. Wait for this event before starting playback." },
		{ "TIMED_METADATA_RENDER.Comment", "/**\n\x09 * This event is called when new timed metadata is ready for display in HLS.\n\x09 * \n\x09 * Timed metadata includes additional information about the playing content that may be displayed\n\x09 * to the user and this information may change at different times throughout the content.\n\x09 * Each time new metadata is available for display, this event occurs.\n\x09 */" },
		{ "TIMED_METADATA_RENDER.DisplayName", "Timed Metadata Render" },
		{ "TIMED_METADATA_RENDER.Name", "HISPlayerEvent::TIMED_METADATA_RENDER" },
		{ "TIMED_METADATA_RENDER.ToolTip", "This event is called when new timed metadata is ready for display in HLS.\n\nTimed metadata includes additional information about the playing content that may be displayed\nto the user and this information may change at different times throughout the content.\nEach time new metadata is available for display, this event occurs." },
		{ "TRACK_CHANGED.Comment", "// The internal texture has changed\n" },
		{ "TRACK_CHANGED.DisplayName", "Track Changed" },
		{ "TRACK_CHANGED.Name", "HISPlayerEvent::TRACK_CHANGED" },
		{ "TRACK_CHANGED.ToolTip", "The internal texture has changed" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_HISPlayer_HISPlayerEvent_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_HISPlayer,
		nullptr,
		"HISPlayerEvent",
		"HISPlayerEvent",
		Z_Construct_UEnum_HISPlayer_HISPlayerEvent_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_HISPlayer_HISPlayerEvent_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_HISPlayer_HISPlayerEvent_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_HISPlayer_HISPlayerEvent_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_HISPlayer_HISPlayerEvent()
	{
		if (!Z_Registration_Info_UEnum_HISPlayerEvent.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_HISPlayerEvent.InnerSingleton, Z_Construct_UEnum_HISPlayer_HISPlayerEvent_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_HISPlayerEvent.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerEvent_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerEvent_h_Statics::EnumInfo[] = {
		{ HISPlayerEvent_StaticEnum, TEXT("HISPlayerEvent"), &Z_Registration_Info_UEnum_HISPlayerEvent, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3965678408U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerEvent_h_2045899171(TEXT("/Script/HISPlayer"),
		nullptr, 0,
		nullptr, 0,
		Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerEvent_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerEvent_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
