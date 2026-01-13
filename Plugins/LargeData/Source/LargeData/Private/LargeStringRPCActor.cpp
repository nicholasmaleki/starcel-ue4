#include "LargeStringRPCActor.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetSystemLibrary.h"

ALargeStringRPCActor::ALargeStringRPCActor()
{
    bReplicates = true;
}

// Server: Receive chunk from client
void ALargeStringRPCActor::Server_ReceiveChunk_Implementation(
    const TArray<uint8>& Chunk,
    int32 Index,
    int32 TotalChunks)
{
    UE_LOG(LogTemp, Log,
        TEXT("Server_ReceiveChunk %d/%d (%d bytes)"),
        Index + 1, TotalChunks, Chunk.Num());

    if (LargeString)
    {
        LargeString->ReceiveChunk(Chunk, Index, TotalChunks);

        // Check if all chunks have been received
        bool bAllReceived = true;
        for (int32 i = 0; i < LargeString->GetChunkCount(); ++i)
        {
            if (LargeString->GetChunk(i).Num() == 0)
            {
                bAllReceived = false;
                break;
            }
        }

        if (bAllReceived)
        {
            Server_OnFullStringReceived();
        }
    }


// Multicast to all clients including sender
// Multicast_ReceiveChunk(Chunk, Index, TotalChunks);

// Send to a specific client (needs PlayerController reference)
// Client_ReceiveChunk(Chunk, Index, TotalChunks);
}

// Multicast: Server → all clients
void ALargeStringRPCActor::Multicast_ReceiveChunk_Implementation(
    const TArray<uint8>& Chunk,
    int32 Index,
    int32 TotalChunks)
{
    if (!LargeString)
    {
        UE_LOG(LogTemp, Warning,
            TEXT("Multicast_ReceiveChunk: LargeString is null"));
        return;
    }

    LargeString->ReceiveChunk(Chunk, Index, TotalChunks);
}

// Client RPC: Server → specific client
void ALargeStringRPCActor::Client_ReceiveChunk_Implementation(
    const TArray<uint8>& Chunk,
    int32 Index,
    int32 TotalChunks)
{
    if (!LargeString)
    {
        UE_LOG(LogTemp, Warning,
            TEXT("Client_ReceiveChunk: LargeString is null"));
        return;
    }

    LargeString->ReceiveChunk(Chunk, Index, TotalChunks);
}

// Server full string received callback
void ALargeStringRPCActor::Server_OnFullStringReceived()
{
    if (!LargeString)
        return;

    UE_LOG(LogTemp, Log,
        TEXT("[SERVER] Full string received! Length=%d"),
        LargeString->ToString().Len());
}
