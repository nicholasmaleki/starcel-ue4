/// Created by HISPlayer © - 2024  

#pragma once

#include "HISPlayerTypes/HISID3Tag.h"
#include "HISTimedMetadata.generated.h"

USTRUCT(BlueprintType)
struct FHISTimedMetadata
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HISPlayer|ID3 Metadata")
	int32 TimeStamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HISPlayer|ID3 Metadata")
	FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HISPlayer|ID3 Metadata")
	FString Album;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HISPlayer|ID3 Metadata")
	FString Artist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HISPlayer|ID3 Metadata")
	FString Date;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HISPlayer|ID3 Metadata")
	FString Genre;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HISPlayer|ID3 Metadata")
	FString SessionInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HISPlayer|ID3 Metadata")
	FString TrackNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HISPlayer|ID3 Metadata")
	FString Year;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HISPlayer|ID3 Metadata")
	FString Lyric;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HISPlayer|ID3 Metadata")
	FString PrivateFrame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HISPlayer|ID3 Metadata")
	FString Comment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HISPlayer|ID3 Metadata")
	FString Text;

public:

	FHISTimedMetadata() { TimeStamp = 0; }

	FHISTimedMetadata(int _TimeStamp) : TimeStamp(_TimeStamp)	{ }

	void SetTagContent(const EHISID3Tag Tag, FString Content) {
		switch (Tag)
		{
			case EHISID3Tag::TITLE:
				Title = Content;
				break;
			case EHISID3Tag::ALBUM:
				Album = Content;
				break;
			case EHISID3Tag::ARTIST:
				Artist = Content;
				break;
			case EHISID3Tag::DATE:
				Date = Content;
				break;
			case EHISID3Tag::GENRE:
				Genre = Content;
				break;
			case EHISID3Tag::SESSION_INFO:
				SessionInfo = Content;
				break;
			case EHISID3Tag::TRACK_NUMBER:
				TrackNumber = Content;
				break;
			case EHISID3Tag::YEAR:
				Year = Content;
				break;
			case EHISID3Tag::PICTURE:
				// The Picture tag matadata is not supported yet
				break;
			case EHISID3Tag::LYRIC:
				Lyric = Content;
				break;
			case EHISID3Tag::PRIVATE_FRAME:
				PrivateFrame = Content;
				break;
			case EHISID3Tag::COMMENT:
				Comment = Content;
				break;
			case EHISID3Tag::TEXT:
				Text = Content;
				break;
			case EHISID3Tag::EXTRA_DATA:
				// The Extra data tag metadata is not supported yet
				break;
			default:
				break;
		}
	}
};
