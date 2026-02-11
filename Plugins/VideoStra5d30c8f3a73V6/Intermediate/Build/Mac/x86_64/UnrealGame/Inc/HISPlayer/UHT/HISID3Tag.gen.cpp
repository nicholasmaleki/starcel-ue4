// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HISPlayer/Public/HISPlayerTypes/HISID3Tag.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHISID3Tag() {}
// Cross Module References
	HISPLAYER_API UEnum* Z_Construct_UEnum_HISPlayer_EHISID3Tag();
	UPackage* Z_Construct_UPackage__Script_HISPlayer();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EHISID3Tag;
	static UEnum* EHISID3Tag_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EHISID3Tag.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EHISID3Tag.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_HISPlayer_EHISID3Tag, Z_Construct_UPackage__Script_HISPlayer(), TEXT("EHISID3Tag"));
		}
		return Z_Registration_Info_UEnum_EHISID3Tag.OuterSingleton;
	}
	template<> HISPLAYER_API UEnum* StaticEnum<EHISID3Tag>()
	{
		return EHISID3Tag_StaticEnum();
	}
	struct Z_Construct_UEnum_HISPlayer_EHISID3Tag_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_HISPlayer_EHISID3Tag_Statics::Enumerators[] = {
		{ "EHISID3Tag::TITLE", (int64)EHISID3Tag::TITLE },
		{ "EHISID3Tag::ALBUM", (int64)EHISID3Tag::ALBUM },
		{ "EHISID3Tag::ARTIST", (int64)EHISID3Tag::ARTIST },
		{ "EHISID3Tag::DATE", (int64)EHISID3Tag::DATE },
		{ "EHISID3Tag::GENRE", (int64)EHISID3Tag::GENRE },
		{ "EHISID3Tag::SESSION_INFO", (int64)EHISID3Tag::SESSION_INFO },
		{ "EHISID3Tag::TRACK_NUMBER", (int64)EHISID3Tag::TRACK_NUMBER },
		{ "EHISID3Tag::YEAR", (int64)EHISID3Tag::YEAR },
		{ "EHISID3Tag::PICTURE", (int64)EHISID3Tag::PICTURE },
		{ "EHISID3Tag::LYRIC", (int64)EHISID3Tag::LYRIC },
		{ "EHISID3Tag::PRIVATE_FRAME", (int64)EHISID3Tag::PRIVATE_FRAME },
		{ "EHISID3Tag::COMMENT", (int64)EHISID3Tag::COMMENT },
		{ "EHISID3Tag::TEXT", (int64)EHISID3Tag::TEXT },
		{ "EHISID3Tag::EXTRA_DATA", (int64)EHISID3Tag::EXTRA_DATA },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_HISPlayer_EHISID3Tag_Statics::Enum_MetaDataParams[] = {
		{ "ALBUM.DisplayName", "Album" },
		{ "ALBUM.Name", "EHISID3Tag::ALBUM" },
		{ "ARTIST.DisplayName", "Artist" },
		{ "ARTIST.Name", "EHISID3Tag::ARTIST" },
		{ "COMMENT.DisplayName", "Comment" },
		{ "COMMENT.Name", "EHISID3Tag::COMMENT" },
		{ "DATE.DisplayName", "Date" },
		{ "DATE.Name", "EHISID3Tag::DATE" },
		{ "EXTRA_DATA.Comment", "// or TXXX\n" },
		{ "EXTRA_DATA.DisplayName", "Extra Data" },
		{ "EXTRA_DATA.Name", "EHISID3Tag::EXTRA_DATA" },
		{ "EXTRA_DATA.ToolTip", "or TXXX" },
		{ "GENRE.DisplayName", "Genre" },
		{ "GENRE.Name", "EHISID3Tag::GENRE" },
		{ "LYRIC.DisplayName", "Lyric" },
		{ "LYRIC.Name", "EHISID3Tag::LYRIC" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISID3Tag.h" },
		{ "PICTURE.DisplayName", "Picture" },
		{ "PICTURE.Name", "EHISID3Tag::PICTURE" },
		{ "PRIVATE_FRAME.DisplayName", "Private Frame" },
		{ "PRIVATE_FRAME.Name", "EHISID3Tag::PRIVATE_FRAME" },
		{ "SESSION_INFO.DisplayName", "Session Info" },
		{ "SESSION_INFO.Name", "EHISID3Tag::SESSION_INFO" },
		{ "TEXT.DisplayName", "Text" },
		{ "TEXT.Name", "EHISID3Tag::TEXT" },
		{ "TITLE.DisplayName", "Title" },
		{ "TITLE.Name", "EHISID3Tag::TITLE" },
		{ "TRACK_NUMBER.DisplayName", "Track Number" },
		{ "TRACK_NUMBER.Name", "EHISID3Tag::TRACK_NUMBER" },
		{ "YEAR.Comment", "// or TRACK_NUM\n" },
		{ "YEAR.DisplayName", "Year" },
		{ "YEAR.Name", "EHISID3Tag::YEAR" },
		{ "YEAR.ToolTip", "or TRACK_NUM" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_HISPlayer_EHISID3Tag_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_HISPlayer,
		nullptr,
		"EHISID3Tag",
		"EHISID3Tag",
		Z_Construct_UEnum_HISPlayer_EHISID3Tag_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_HISPlayer_EHISID3Tag_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_HISPlayer_EHISID3Tag_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_HISPlayer_EHISID3Tag_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_HISPlayer_EHISID3Tag()
	{
		if (!Z_Registration_Info_UEnum_EHISID3Tag.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EHISID3Tag.InnerSingleton, Z_Construct_UEnum_HISPlayer_EHISID3Tag_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EHISID3Tag.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISID3Tag_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISID3Tag_h_Statics::EnumInfo[] = {
		{ EHISID3Tag_StaticEnum, TEXT("EHISID3Tag"), &Z_Registration_Info_UEnum_EHISID3Tag, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2020109612U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISID3Tag_h_1479189435(TEXT("/Script/HISPlayer"),
		nullptr, 0,
		nullptr, 0,
		Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISID3Tag_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_HISPlayer_Source_HISPlayer_Public_HISPlayerTypes_HISID3Tag_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
