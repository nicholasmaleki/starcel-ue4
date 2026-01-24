#include "LargeStringRPCActor.h"
#include "Net/UnrealNetwork.h"


ALargeStringRPCActor::ALargeStringRPCActor()
{
    bReplicates = true;
    bAlwaysRelevant = true;
    SetReplicateMovement(false);
}


void ALargeStringRPCActor::BeginPlay()
{
    Super::BeginPlay();

    if (LargeString)
    {
        LargeString->OnFullyReceived.AddDynamic(
            this,
            &ALargeStringRPCActor::Server_OnFullStringReceived
        );

        UE_LOG(LogTemp, Log, TEXT("LargeStringRPCActor bound to LargeString"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("LargeStringRPCActor has no LargeString assigned"));
    }
}


void ALargeStringRPCActor::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty>& OutLifetimeProps
) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}


void ALargeStringRPCActor::Server_ReceiveChunk_Implementation(
    const TArray<uint8>& Chunk,
    int32 Index,
    int32 TotalChunks)
{
    if (!LargeString)
        return;

    UE_LOG(LogTemp, Log,
        TEXT("Server_ReceiveChunk %d/%d (%d bytes)"),
        Index + 1, TotalChunks, Chunk.Num());

    LargeString->ReceiveChunk(Chunk, Index, TotalChunks);
}


void ALargeStringRPCActor::Multicast_ReceiveChunk_Implementation(
    const TArray<uint8>& Chunk,
    int32 Index,
    int32 TotalChunks)
{
    if (!LargeString)
        return;

    UE_LOG(LogTemp, Log,
        TEXT("Multicast_ReceiveChunk %d/%d"),
        Index + 1, TotalChunks);

    LargeString->ReceiveChunk(Chunk, Index, TotalChunks);
}


void ALargeStringRPCActor::Client_ReceiveChunk_Implementation(
    const TArray<uint8>& Chunk,
    int32 Index,
    int32 TotalChunks)
{
    if (!LargeString)
        return;

    UE_LOG(LogTemp, Log,
        TEXT("Client_ReceiveChunk %d/%d"),
        Index + 1, TotalChunks);

    LargeString->ReceiveChunk(Chunk, Index, TotalChunks);
}


void ALargeStringRPCActor::Server_OnFullStringReceived()
{
    if (!LargeString)
        return;

    FString Full = LargeString->ToString();

    UE_LOG(LogTemp, Warning,
        TEXT("[SERVER] Full string received (%d chars)"),
        Full.Len());

    OnServerStringReceived.Broadcast(Full);
    Multicast_OnFullStringReceived(Full);
}


void ALargeStringRPCActor::Multicast_OnFullStringReceived_Implementation(
    const FString& FullString)
{
    UE_LOG(LogTemp, Warning,
        TEXT("[CLIENT] Full string received (%d chars)"),
        FullString.Len());

    OnClientStringReceived.Broadcast(FullString);
}
