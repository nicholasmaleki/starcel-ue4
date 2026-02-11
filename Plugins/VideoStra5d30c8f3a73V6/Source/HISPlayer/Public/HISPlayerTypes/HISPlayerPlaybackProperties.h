/// Created by HISPlayer © - 2024  

#pragma once
#include "HISPlayerPlaybackProperties.generated.h"

USTRUCT(BlueprintType, Category = "HISPlayer|Types", meta = (DisplayName = "HISPlayer Playback Properties"))
struct FHISPlayerPlaybackProperties {
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnParams)
		bool bAutoplay = true;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnParams)
		bool bLooping = true;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnParams)
		bool bMute = false;
};