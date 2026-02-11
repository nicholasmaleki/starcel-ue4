// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HISPlayer/Public/HISPlayerTypes/HISTimedMetadata.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHISTimedMetadata() {}
// Cross Module References
	HISPLAYER_API UScriptStruct* Z_Construct_UScriptStruct_FHISTimedMetadata();
	UPackage* Z_Construct_UPackage__Script_HISPlayer();
// End Cross Module References
class UScriptStruct* FHISTimedMetadata::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern HISPLAYER_API uint32 Get_Z_Construct_UScriptStruct_FHISTimedMetadata_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FHISTimedMetadata, Z_Construct_UPackage__Script_HISPlayer(), TEXT("HISTimedMetadata"), sizeof(FHISTimedMetadata), Get_Z_Construct_UScriptStruct_FHISTimedMetadata_Hash());
	}
	return Singleton;
}
template<> HISPLAYER_API UScriptStruct* StaticStruct<FHISTimedMetadata>()
{
	return FHISTimedMetadata::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FHISTimedMetadata(FHISTimedMetadata::StaticStruct, TEXT("/Script/HISPlayer"), TEXT("HISTimedMetadata"), false, nullptr, nullptr);
static struct FScriptStruct_HISPlayer_StaticRegisterNativesFHISTimedMetadata
{
	FScriptStruct_HISPlayer_StaticRegisterNativesFHISTimedMetadata()
	{
		UScriptStruct::DeferCppStructOps<FHISTimedMetadata>(FName(TEXT("HISTimedMetadata")));
	}
} ScriptStruct_HISPlayer_StaticRegisterNativesFHISTimedMetadata;
	struct Z_Construct_UScriptStruct_FHISTimedMetadata_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TimeStamp_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_TimeStamp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Title_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Title;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Album_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Album;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Artist_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Artist;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Date_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Date;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Genre_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Genre;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SessionInfo_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_SessionInfo;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TrackNumber_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_TrackNumber;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Year_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Year;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Lyric_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Lyric;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PrivateFrame_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_PrivateFrame;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Comment_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Comment;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Text_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Text;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISTimedMetadata.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FHISTimedMetadata>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_TimeStamp_MetaData[] = {
		{ "Category", "HISPlayer|ID3 Metadata" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISTimedMetadata.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_TimeStamp = { "TimeStamp", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FHISTimedMetadata, TimeStamp), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_TimeStamp_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_TimeStamp_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Title_MetaData[] = {
		{ "Category", "HISPlayer|ID3 Metadata" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISTimedMetadata.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Title = { "Title", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FHISTimedMetadata, Title), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Title_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Title_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Album_MetaData[] = {
		{ "Category", "HISPlayer|ID3 Metadata" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISTimedMetadata.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Album = { "Album", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FHISTimedMetadata, Album), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Album_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Album_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Artist_MetaData[] = {
		{ "Category", "HISPlayer|ID3 Metadata" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISTimedMetadata.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Artist = { "Artist", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FHISTimedMetadata, Artist), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Artist_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Artist_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Date_MetaData[] = {
		{ "Category", "HISPlayer|ID3 Metadata" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISTimedMetadata.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Date = { "Date", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FHISTimedMetadata, Date), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Date_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Date_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Genre_MetaData[] = {
		{ "Category", "HISPlayer|ID3 Metadata" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISTimedMetadata.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Genre = { "Genre", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FHISTimedMetadata, Genre), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Genre_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Genre_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_SessionInfo_MetaData[] = {
		{ "Category", "HISPlayer|ID3 Metadata" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISTimedMetadata.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_SessionInfo = { "SessionInfo", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FHISTimedMetadata, SessionInfo), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_SessionInfo_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_SessionInfo_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_TrackNumber_MetaData[] = {
		{ "Category", "HISPlayer|ID3 Metadata" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISTimedMetadata.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_TrackNumber = { "TrackNumber", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FHISTimedMetadata, TrackNumber), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_TrackNumber_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_TrackNumber_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Year_MetaData[] = {
		{ "Category", "HISPlayer|ID3 Metadata" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISTimedMetadata.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Year = { "Year", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FHISTimedMetadata, Year), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Year_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Year_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Lyric_MetaData[] = {
		{ "Category", "HISPlayer|ID3 Metadata" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISTimedMetadata.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Lyric = { "Lyric", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FHISTimedMetadata, Lyric), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Lyric_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Lyric_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_PrivateFrame_MetaData[] = {
		{ "Category", "HISPlayer|ID3 Metadata" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISTimedMetadata.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_PrivateFrame = { "PrivateFrame", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FHISTimedMetadata, PrivateFrame), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_PrivateFrame_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_PrivateFrame_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Comment_MetaData[] = {
		{ "Category", "HISPlayer|ID3 Metadata" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISTimedMetadata.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Comment = { "Comment", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FHISTimedMetadata, Comment), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Comment_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Comment_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Text_MetaData[] = {
		{ "Category", "HISPlayer|ID3 Metadata" },
		{ "ModuleRelativePath", "Public/HISPlayerTypes/HISTimedMetadata.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Text = { "Text", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FHISTimedMetadata, Text), METADATA_PARAMS(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Text_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Text_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_TimeStamp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Title,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Album,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Artist,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Date,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Genre,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_SessionInfo,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_TrackNumber,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Year,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Lyric,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_PrivateFrame,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Comment,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::NewProp_Text,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_HISPlayer,
		nullptr,
		&NewStructOps,
		"HISTimedMetadata",
		sizeof(FHISTimedMetadata),
		alignof(FHISTimedMetadata),
		Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FHISTimedMetadata()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FHISTimedMetadata_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_HISPlayer();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("HISTimedMetadata"), sizeof(FHISTimedMetadata), Get_Z_Construct_UScriptStruct_FHISTimedMetadata_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FHISTimedMetadata_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FHISTimedMetadata_Hash() { return 399256332U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
