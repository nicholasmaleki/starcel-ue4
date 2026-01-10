#include "LargeStringAsync.h"
#include "Async/Async.h"

void ULargeStringAsync::SetFromStringAsync(const FString& InString)
{
    // Build chunks asynchronously off the game thread
    Async(EAsyncExecution::Thread, [this, InString]()
        {
            Value = InString;

            // Convert UTF-16 FString to UTF-8 bytes
            FTCHARToUTF8 Converter(*Value);
            SerializedData.Empty(Converter.Length());
            SerializedData.Append(reinterpret_cast<const uint8*>(Converter.Get()), Converter.Length());

            // Build chunks from serialized data
            BuildChunks();
        });
}

void ULargeStringAsync::BuildChunks()
{
    Chunks.Empty();
    int32 TotalBytes = SerializedData.Num();

    for (int32 Offset = 0; Offset < TotalBytes; Offset += MaxChunkSize)
    {
        int32 Size = FMath::Min(MaxChunkSize, TotalBytes - Offset);

        // Copy bytes into a chunk
        TArray<uint8> Chunk;
        Chunk.Append(&SerializedData[Offset], Size);

        Chunks.Add(Chunk);
    }
}

TArray<uint8> ULargeStringAsync::GetChunk(int32 Index) const
{
    if (Chunks.IsValidIndex(Index))
        return Chunks[Index];
    return TArray<uint8>();
}

void ULargeStringAsync::ReceiveChunk(const TArray<uint8>& Chunk, int32 Index, int32 TotalChunks)
{
    if (ReceivedChunks.Num() < TotalChunks)
        ReceivedChunks.SetNum(TotalChunks);

    ReceivedChunks[Index] = Chunk;

    // Check if all chunks are received
    bool bAllReceived = true;
    for (const auto& C : ReceivedChunks)
    {
        if (C.Num() == 0)
        {
            bAllReceived = false;
            break;
        }
    }

    if (bAllReceived)
    {
        ReassembleFromChunksAsync();
    }
}

void ULargeStringAsync::ReassembleFromChunksAsync()
{
    Async(EAsyncExecution::Thread, [this]()
        {
            ReassembleChunks();

            // Notify main thread
            Async(EAsyncExecution::TaskGraphMainThread, [this]()
                {
                    OnFullyReceived.Broadcast();
                });
        });
}

void ULargeStringAsync::ReassembleChunks()
{
    SerializedData.Empty();

    for (const auto& Chunk : ReceivedChunks)
        SerializedData.Append(Chunk);

    // Convert UTF-8 bytes back to FString
    Value = UTF8_TO_TCHAR(SerializedData.GetData());

    // Clear temporary received storage
    ReceivedChunks.Empty();
}
