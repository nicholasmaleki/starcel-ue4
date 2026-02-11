// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "HISPlayerTypes/HISID3Tag.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef HISPLAYER_HISID3Tag_generated_h
#error "HISID3Tag.generated.h already included, missing '#pragma once' in HISID3Tag.h"
#endif
#define HISPLAYER_HISID3Tag_generated_h

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISID3Tag_h


#define FOREACH_ENUM_EHISID3TAG(op) \
	op(EHISID3Tag::TITLE) \
	op(EHISID3Tag::ALBUM) \
	op(EHISID3Tag::ARTIST) \
	op(EHISID3Tag::DATE) \
	op(EHISID3Tag::GENRE) \
	op(EHISID3Tag::SESSION_INFO) \
	op(EHISID3Tag::TRACK_NUMBER) \
	op(EHISID3Tag::YEAR) \
	op(EHISID3Tag::PICTURE) \
	op(EHISID3Tag::LYRIC) \
	op(EHISID3Tag::PRIVATE_FRAME) \
	op(EHISID3Tag::COMMENT) \
	op(EHISID3Tag::TEXT) \
	op(EHISID3Tag::EXTRA_DATA) 

enum class EHISID3Tag : uint8;
template<> struct TIsUEnumClass<EHISID3Tag> { enum { Value = true }; };
template<> HISPLAYER_API UEnum* StaticEnum<EHISID3Tag>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
