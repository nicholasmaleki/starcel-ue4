// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "HISPlayerTypes/HISPlayerStatus.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef HISPLAYER_HISPlayerStatus_generated_h
#error "HISPlayerStatus.generated.h already included, missing '#pragma once' in HISPlayerStatus.h"
#endif
#define HISPLAYER_HISPlayerStatus_generated_h

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerStatus_h


#define FOREACH_ENUM_HISPLAYERSTATUS(op) \
	op(HISPlayerStatus::NONE) \
	op(HISPlayerStatus::CLOSE) \
	op(HISPlayerStatus::STOP) \
	op(HISPlayerStatus::PLAY) \
	op(HISPlayerStatus::PAUSE) 

enum class HISPlayerStatus : uint8;
template<> struct TIsUEnumClass<HISPlayerStatus> { enum { Value = true }; };
template<> HISPLAYER_API UEnum* StaticEnum<HISPlayerStatus>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
