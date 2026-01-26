#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LargeStringAsync.h"
#include "LargeStringRPCActor.generated.h"


/** Fired on server when full string arrives */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
FOnServerStringReceived,
const FString&,
FullString
);

/** Fired on clients when full string arrives */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
FOnClientStringReceived,
const FString&,
FullString
);

UCLASS()
class LARGEDATA_API ALargeStringRPCActor : public AActor
{
    GENERATED_BODY()

public:
    ALargeStringRPCActor();

    /** BeginPlay override to bind events */
    virtual void BeginPlay() override;

    /** Replication setup */
    virtual void GetLifetimeReplicatedProps(
        TArray<FLifetimeProperty>& OutLifetimeProps
    ) const override;

public:

    /** Large async string object */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        ULargeStringAsync* LargeString;

    /** Fired on server when full string arrives */
    UPROPERTY(BlueprintAssignable)
        FOnServerStringReceived OnServerStringReceived;

    /** Fired on clients when full string arrives */
    UPROPERTY(BlueprintAssignable)
        FOnClientStringReceived OnClientStringReceived;

    /** Flag to enable auto-multicast after server receives string */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LargeString")
        bool bAutoMulticastOnServerReceive = false;

    /** Client → Server */
    UFUNCTION(Server, Reliable)
        void Server_ReceiveChunk(
            const TArray<uint8>& Chunk,
            int32 Index,
            int32 TotalChunks
        );

    /** Server → All Clients */
    UFUNCTION(NetMulticast, Reliable)
        void Multicast_ReceiveChunk(
            const TArray<uint8>& Chunk,
            int32 Index,
            int32 TotalChunks
        );

    /** Server → One Client */
    UFUNCTION(Client, Reliable)
        void Client_ReceiveChunk(
            const TArray<uint8>& Chunk,
            int32 Index,
            int32 TotalChunks
        );

    /** Server → All Clients (completion) */
    UFUNCTION(NetMulticast, Reliable)
        void Multicast_OnFullStringReceived(const FString& FullString);

    /** Server → All Clients (completion notification ONLY, no data) */
    UFUNCTION(NetMulticast, Reliable)
        void Multicast_OnFullStringReceivedNotification();

    /** Trigger multicast of all chunks (for client→server→multicast flow) */
    UFUNCTION(BlueprintCallable, Category = "LargeString")
        void TriggerMulticastChunks();

protected:

    /** Called when the server receives the full string */
    UFUNCTION()
        void Server_OnFullStringReceived();

    /** Called when the client receives the full string */
    UFUNCTION()
        void Client_OnFullStringReceived();
};