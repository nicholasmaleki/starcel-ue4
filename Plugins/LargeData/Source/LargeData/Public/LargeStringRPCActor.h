#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LargeStringAsync.h"
#include "LargeStringRPCActor.generated.h"

UCLASS()
class LARGEDATA_API ALargeStringRPCActor : public AActor
{
    GENERATED_BODY()

public:
    ALargeStringRPCActor();

    /** The LargeStringAsync object attached to this actor */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        ULargeStringAsync* LargeString;

    /** Called when the full string is received on the server */
    UFUNCTION()
        void Server_OnFullStringReceived();

    /** Client → Server: receive a chunk */
    UFUNCTION(Server, Reliable)
        void Server_ReceiveChunk(
            const TArray<uint8>& Chunk,
            int32 Index,
            int32 TotalChunks
        );

    /** Server → All clients: multicast a chunk */
    UFUNCTION(NetMulticast, Reliable)
        void Multicast_ReceiveChunk(
            const TArray<uint8>& Chunk,
            int32 Index,
            int32 TotalChunks
        );

    /** Server → specific client: send chunk to one client */
    UFUNCTION(Client, Reliable)
        void Client_ReceiveChunk(
            const TArray<uint8>& Chunk,
            int32 Index,
            int32 TotalChunks
        );
};
