// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HISPlayer/Public/HISPlayerTypes/HISID3Tag.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHISID3Tag() {}
// Cross Module References
	HISPLAYER_API UEnum* Z_Construct_UEnum_HISPlayer_EHISID3Tag();
	UPackage* Z_Construct_UPackage__Script_HISPlayer();
// End Cross Module References
	static UEnum* EHISID3Tag_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_HISPlayer_EHISID3Tag, Z_Construct_UPackage__Script_HISPlayer(), TEXT("EHISID3Tag"));
		}
		return Singleton;
	}
	template<> HISPLAYER_API UEnum* StaticEnum<EHISID3Tag>()
	{
		return EHISID3Tag_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EHISID3Tag(EHISID3Tag_StaticEnum, TEXT("/Script/HISPlayer"), TEXT("EHISID3Tag"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_HISPlayer_EHISID3Tag_Hash() { return 2993722168U; }
	UEnum* Z_Construct_UEnum_HISPlayer_EHISID3Tag()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_HISPlayer();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EHISID3Tag"), 0, Get_Z_Construct_UEnum_HISPlayer_EHISID3Tag_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
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
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
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
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_HISPlayer,
				nullptr,
				"EHISID3Tag",
				"EHISID3Tag",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
