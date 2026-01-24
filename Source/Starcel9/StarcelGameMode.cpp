#include "StarcelGameMode.h"
#include "Engine/World.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"


AStarcelGameMode::AStarcelGameMode()
{
    // nothing special yet
}


void AStarcelGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    if (!NewPlayer)
        return;

    UE_LOG(LogTemp, Warning,
        TEXT("[StarcelGameMode] Player joined: %s"),
        *NewPlayer->GetName()
    );

    OnPlayerJoined.Broadcast(NewPlayer);
}
