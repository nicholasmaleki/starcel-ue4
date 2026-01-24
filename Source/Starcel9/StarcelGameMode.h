#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "StarcelGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
FOnPlayerJoined,
APlayerController*,
Player
);


/**
 * GameMode that exposes PostLogin to Python / Blueprint.
 * Server-only.
 */
UCLASS()
class STARCEL9_API AStarcelGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AStarcelGameMode();

    /** Fired when a client joins (server only) */
    UPROPERTY(BlueprintAssignable, Category = "Python")
        FOnPlayerJoined OnPlayerJoined;

    /** Called by engine when a player connects */
    virtual void PostLogin(APlayerController* NewPlayer) override;
};
