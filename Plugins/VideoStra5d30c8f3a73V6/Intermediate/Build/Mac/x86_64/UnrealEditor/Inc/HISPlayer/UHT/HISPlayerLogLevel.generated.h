// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "HISPlayerTypes/HISPlayerLogLevel.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef HISPLAYER_HISPlayerLogLevel_generated_h
#error "HISPlayerLogLevel.generated.h already included, missing '#pragma once' in HISPlayerLogLevel.h"
#endif
#define HISPLAYER_HISPlayerLogLevel_generated_h

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISPlayerLogLevel_h


#define FOREACH_ENUM_HISPLAYERLOGLEVEL(op) \
	op(HISPlayerLogLevel::DEBUG) \
	op(HISPlayerLogLevel::INFO) \
	op(HISPlayerLogLevel::WARNING) \
	op(HISPlayerLogLevel::ERROR) \
	op(HISPlayerLogLevel::NONE) 

enum class HISPlayerLogLevel : uint8;
template<> struct TIsUEnumClass<HISPlayerLogLevel> { enum { Value = true }; };
template<> HISPLAYER_API UEnum* StaticEnum<HISPlayerLogLevel>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
