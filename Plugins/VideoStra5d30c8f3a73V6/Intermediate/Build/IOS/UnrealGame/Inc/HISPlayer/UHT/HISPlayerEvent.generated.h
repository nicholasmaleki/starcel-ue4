// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "HISPlayerTypes/HISPlayerEvent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef HISPLAYER_HISPlayerEvent_generated_h
#error "HISPlayerEvent.generated.h already included, missing '#pragma once' in HISPlayerEvent.h"
#endif
#define HISPLAYER_HISPlayerEvent_generated_h

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerEvent_h


#define FOREACH_ENUM_HISPLAYEREVENT(op) \
	op(HISPlayerEvent::NONE) \
	op(HISPlayerEvent::INIT_COMPLETE) \
	op(HISPlayerEvent::PLAYBACK_STARTED) \
	op(HISPlayerEvent::END_OF_CONTENT) \
	op(HISPlayerEvent::BUFFERING_ENDED) \
	op(HISPlayerEvent::TEXTURE_CHANGED) \
	op(HISPlayerEvent::TRACK_CHANGED) \
	op(HISPlayerEvent::PLAYBACK_PAUSED) \
	op(HISPlayerEvent::STOPPED) \
	op(HISPlayerEvent::SEEKED) \
	op(HISPlayerEvent::BUFFERING) \
	op(HISPlayerEvent::EXTERNAL_PCM) \
	op(HISPlayerEvent::LOADING) \
	op(HISPlayerEvent::TIMED_METADATA_RENDER) \
	op(HISPlayerEvent::SERVER_CONNECTION) 

enum class HISPlayerEvent : uint8;
template<> struct TIsUEnumClass<HISPlayerEvent> { enum { Value = true }; };
template<> HISPLAYER_API UEnum* StaticEnum<HISPlayerEvent>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
