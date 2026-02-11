/// Created by HISPlayer © - 2024  

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HISPlayerTypes/HISPlayerStatus.h"
#include "HISPlayerTypes/HISTimedMetadata.h"
#include "HISPlayerLogs.h"
#include "HISPlayerTypes/HISPlayerLogLevel.h"
#include "DelegateManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventDelegateNoParam, int, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEventDelegatePercentage, float, Percentage, int, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEventDelegateStatus, HISPlayerStatus, Status, int, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEventDelegateResolution, FIntPoint, Resolution, int, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEventDelegateError, int, ErrorCode, int, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEventDelegateTimedMetadata, FHISTimedMetadata, TimedMetadata, int, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FEventDelegatePCMData, const TArray<float>&, PCMData, int, timestamp, int, Index);

UCLASS()
class UDelegateManager : public UObject {
	GENERATED_BODY()

public:

	UDelegateManager();

	~UDelegateManager();

	UPROPERTY(BlueprintAssignable, Category = "HISPlayer")
	FEventDelegateNoParam OnLoading;

	UPROPERTY(BlueprintAssignable, Category = "HISPlayer")
	FEventDelegateNoParam OnPlay;

	UPROPERTY(BlueprintAssignable, Category = "HISPlayer")
	FEventDelegateNoParam OnPause;

	UPROPERTY(BlueprintAssignable, Category = "HISPlayer")
	FEventDelegateNoParam OnStop;

	UPROPERTY(BlueprintAssignable, Category = "HISPlayer")
	FEventDelegateNoParam OnEndContent;

	UPROPERTY(BlueprintAssignable, Category = "HISPlayer")
	FEventDelegatePercentage OnBuffering;

	UPROPERTY(BlueprintAssignable, Category = "HISPlayer")
	FEventDelegateStatus OnStatusChanged;

	UPROPERTY(BlueprintAssignable, Category = "HISPlayer")
	FEventDelegateResolution OnTrackChanged;

	UPROPERTY(BlueprintAssignable, Category = "HISPlayer")
	FEventDelegateError OnError;

	UPROPERTY(BlueprintAssignable, Category = "HISPlayer")
	FEventDelegateTimedMetadata OnTimedMetadata;

	UPROPERTY(BlueprintAssignable, Category = "HISPlayer")
	FEventDelegatePCMData OnPCMDataReceived;

	UPROPERTY(BlueprintAssignable, Category = "HISPlayer")
	FEventDelegateNoParam OnInitComplete;

	UPROPERTY(BlueprintAssignable, Category = "HISPlayer")
	FEventDelegateNoParam OnSeekComplete;
};
