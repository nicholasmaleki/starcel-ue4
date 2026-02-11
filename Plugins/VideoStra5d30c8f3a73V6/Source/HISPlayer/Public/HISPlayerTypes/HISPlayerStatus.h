/// Created by HISPlayer © - 2024  

#pragma once
#include "HISPlayerStatus.generated.h"

UENUM(BlueprintType, Category = "HISPlayer|Types")
enum class HISPlayerStatus : uint8 {
	NONE = 0		UMETA(DisplayName = "None"),
	CLOSE = 1		UMETA(DisplayName = "Close"),
	STOP = 2		UMETA(DisplayName = "Stop"),
	PLAY = 3		UMETA(DisplayName = "Play"),
	PAUSE = 4		UMETA(DisplayName = "Pause"),
};
