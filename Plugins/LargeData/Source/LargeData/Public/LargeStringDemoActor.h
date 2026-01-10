#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LargeStringAsync.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LargeStringDemoActor.generated.h"

/**
 * Actor for sending/receiving large strings asynchronously.
 * Demonstrates server/client chunked RPC usage.
 */
UCLASS()
class LARGEDATA_API ALargeStringDemoActor : public AActor
{
    GENERATED_BODY()

public:
    ALargeStringDemoActor();

    /** Async large string object */
    UPROPERTY()
    ULargeStringAsync* LargeString;

    /** Client RPC: receive a chunk from server */
    UFUNCTION(Client, Reliable)
    void Client_ReceiveChunk(const TArray<uint8>& Chunk, int32 Index, int32 TotalChunks);

    /** Server RPC: receive a chunk from client */
    UFUNCTION(Server, Reliable)
    void Server_SendChunk(const TArray<uint8>& Chunk, int32 Index, int32 TotalChunks);

    /** Called when full string has been received */
    UFUNCTION()
    void OnStringFullyReceived();

    /** Send all chunks automatically (detects server/client) */
    void SendAllChunks();

    /** Example server modification of string */
    void ModifyStringOnServer();

protected:
    virtual void BeginPlay() override;
};
