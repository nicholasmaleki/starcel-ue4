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
        // Bind callbacks based on authority
        if (HasAuthority())
        {
            LargeString->OnFullyReceived.AddDynamic(
                this,
                &ALargeStringRPCActor::Server_OnFullStringReceived
            );
            UE_LOG(LogTemp, Log, TEXT("[SERVER] LargeStringRPCActor bound to LargeString"));
        }
        else
        {
            LargeString->OnFullyReceived.AddDynamic(
                this,
                &ALargeStringRPCActor::Client_OnFullStringReceived
            );
            UE_LOG(LogTemp, Log, TEXT("[CLIENT] LargeStringRPCActor bound to LargeString"));
        }
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
        TEXT("[SERVER] Server_ReceiveChunk %d/%d (%d bytes)"),
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

    // Skip on server if we already have the data
    if (HasAuthority())
    {
        UE_LOG(LogTemp, Verbose, TEXT("[SERVER] Skipping multicast chunk (already has data)"));
        return;
    }

    UE_LOG(LogTemp, Log,
        TEXT("[CLIENT] Multicast_ReceiveChunk %d/%d (%d bytes)"),
        Index + 1, TotalChunks, Chunk.Num());

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
        TEXT("[CLIENT] Client_ReceiveChunk %d/%d (%d bytes)"),
        Index + 1, TotalChunks, Chunk.Num());

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

    // Broadcast to server-side listeners (including Python)
    OnServerStringReceived.Broadcast(Full);

    // Auto-multicast if enabled
    if (bAutoMulticastOnServerReceive)
    {
        UE_LOG(LogTemp, Warning, TEXT("[SERVER] Auto-multicasting chunks to clients"));
        TriggerMulticastChunks();
    }

    // Also send simple completion notification
    // Multicast_OnFullStringReceived(Full);
}


void ALargeStringRPCActor::Client_OnFullStringReceived()
{
    if (!LargeString)
        return;

    FString Full = LargeString->ToString();

    UE_LOG(LogTemp, Warning,
        TEXT("[CLIENT] Full string received (%d chars)"),
        Full.Len());

    OnClientStringReceived.Broadcast(Full);
}


void ALargeStringRPCActor::TriggerMulticastChunks()
{
    if (!HasAuthority())
    {
        UE_LOG(LogTemp, Error, TEXT("TriggerMulticastChunks can only be called on server"));
        return;
    }

    if (!LargeString)
    {
        UE_LOG(LogTemp, Error, TEXT("No LargeString to multicast"));
        return;
    }

    int32 ChunkCount = LargeString->GetChunkCount();

    if (ChunkCount == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No chunks available to multicast"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("[SERVER] Multicasting %d chunks to all clients"), ChunkCount);

    for (int32 i = 0; i < ChunkCount; ++i)
    {
        TArray<uint8> Chunk = LargeString->GetChunk(i);
        Multicast_ReceiveChunk(Chunk, i, ChunkCount);
    }

    UE_LOG(LogTemp, Warning, TEXT("[SERVER] Multicast complete"));

    // Optional: Send notification when all chunks have been sent
    // Multicast_OnFullStringReceivedNotification();
}


void ALargeStringRPCActor::Multicast_OnFullStringReceived_Implementation(
    const FString& FullString)
{
    // Skip on server (it already has the data)
    if (HasAuthority())
        return;

    UE_LOG(LogTemp, Warning,
        TEXT("[CLIENT] Multicast full string notification received (%d chars)"),
        FullString.Len());

    OnClientStringReceived.Broadcast(FullString);
}


void ALargeStringRPCActor::Multicast_OnFullStringReceivedNotification_Implementation()
{
    // Skip on server (it already has the data)
    if (HasAuthority())
        return;

    UE_LOG(LogTemp, Warning,
        TEXT("[CLIENT] Multicast notification received - string is ready"));

    // Optionally trigger a special callback for multicast scenarios
    // This lets you distinguish between direct client receive vs multicast receive
    OnClientStringReceived.Broadcast(FString::Printf(TEXT("[MULTICAST] Ready")));
}