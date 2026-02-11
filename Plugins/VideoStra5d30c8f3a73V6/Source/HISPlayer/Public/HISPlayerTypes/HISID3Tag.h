/// Created by HISPlayer © - 2024  

#pragma once
#include "HISID3Tag.generated.h"

UENUM()
enum class EHISID3Tag : uint8 {
	TITLE = 0				UMETA(DisplayName = "Title"),
	ALBUM = 1				UMETA(DisplayName = "Album"),
	ARTIST = 2				UMETA(DisplayName = "Artist"),
	DATE = 3				UMETA(DisplayName = "Date"),
	GENRE = 4				UMETA(DisplayName = "Genre"),
	SESSION_INFO = 5		UMETA(DisplayName = "Session Info"),
	TRACK_NUMBER = 6		UMETA(DisplayName = "Track Number"),	// or TRACK_NUM
	YEAR = 7				UMETA(DisplayName = "Year"),
	PICTURE = 8				UMETA(DisplayName = "Picture"),
	LYRIC = 9				UMETA(DisplayName = "Lyric"),
	PRIVATE_FRAME = 10		UMETA(DisplayName = "Private Frame"),
	COMMENT = 11			UMETA(DisplayName = "Comment"),
	TEXT = 12				UMETA(DisplayName = "Text"),			// or TXXX
	EXTRA_DATA = 13			UMETA(DisplayName = "Extra Data"),		// or EXTRA_TAG
};
