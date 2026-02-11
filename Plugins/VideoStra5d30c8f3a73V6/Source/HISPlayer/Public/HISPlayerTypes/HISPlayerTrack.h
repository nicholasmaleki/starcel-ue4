/// Created by HISPlayer © - 2024 

#pragma once
#include "HISPlayerTrack.generated.h"

USTRUCT(BlueprintType, Category = "HISPlayer|Track", meta = (DisplayName = "HISPlayer Track"))
struct FHISPlayerTrack {
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnParams)
	FString id = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnParams)
	int bitrate = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnParams)
	int width = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnParams)
	int height = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnParams)
	int framerate = 0;
};
