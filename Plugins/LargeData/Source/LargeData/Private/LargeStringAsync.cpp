#include "LargeStringAsync.h"
#include "Async/Async.h"

ULargeStringAsync::ULargeStringAsync()
{
    ChunkSize = DefaultChunkSize;
}

void ULargeStringAsync::SetChunkSize(int32 NewChunkSize)
{
    if (NewChunkSize <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid chunk size %d, using default %d"),
            NewChunkSize, DefaultChunkSize);
        ChunkSize = DefaultChunkSize;
        return;
    }

    if (NewChunkSize > 65536)
    {
        UE_LOG(LogTemp, Warning,
            TEXT("Chunk size %d exceeds 64KB RPC limit, clamping to 63KB"),
            NewChunkSize);
        ChunkSize = 63 * 1024;
        return;
    }

    ChunkSize = NewChunkSize;
    UE_LOG(LogTemp, Log, TEXT("Chunk size set to %d bytes"), ChunkSize);
}

void ULargeStringAsync::SetFromStringAsync(const FString& InString)
{
    UE_LOG(LogTemp, Log,
        TEXT("SetFromStringAsync: chars=%d, chunk size=%d"),
        InString.Len(), ChunkSize);

    // Use weak pointer to prevent crashes if object is destroyed
    TWeakObjectPtr<ULargeStringAsync> WeakThis(this);

    Async(EAsyncExecution::Thread, [WeakThis, InString]()
        {
            if (!WeakThis.IsValid())
            {
                UE_LOG(LogTemp, Warning, TEXT("SetFromStringAsync: Object destroyed during async operation"));
                return;
            }

            WeakThis->Value = InString;

            FTCHARToUTF8 Converter(*WeakThis->Value);
            WeakThis->SerializedData.Reset(Converter.Length());
            WeakThis->SerializedData.Append(
                reinterpret_cast<const uint8*>(Converter.Get()),
                Converter.Length()
            );

            WeakThis->BuildChunks();

            Async(EAsyncExecution::TaskGraphMainThread, [WeakThis]()
                {
                    if (!WeakThis.IsValid())
                        return;

                    UE_LOG(LogTemp, Log,
                        TEXT("Chunks built: %d (chunk size: %d bytes)"),
                        WeakThis->Chunks.Num(), WeakThis->ChunkSize);
                    WeakThis->OnChunksBuilt.Broadcast();
                });
        });
}

void ULargeStringAsync::BuildChunks()
{
    Chunks.Reset();

    const int32 TotalBytes = SerializedData.Num();
    if (TotalBytes == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("BuildChunks: No data to chunk"));
        return;
    }

    for (int32 Offset = 0; Offset < TotalBytes; Offset += ChunkSize)
    {
        const int32 Size = FMath::Min(ChunkSize, TotalBytes - Offset);
        TArray<uint8> ChunkData;
        ChunkData.Reserve(Size);
        ChunkData.Append(&SerializedData[Offset], Size);

        FByteChunk Chunk(MoveTemp(ChunkData));
        Chunks.Add(MoveTemp(Chunk));
    }

    UE_LOG(LogTemp, Log,
        TEXT("SerializedData=%d bytes, Chunks=%d, ChunkSize=%d"),
        TotalBytes, Chunks.Num(), ChunkSize);
}

TArray<uint8> ULargeStringAsync::GetChunk(int32 Index) const
{
    return Chunks.IsValidIndex(Index) ? Chunks[Index].Data : TArray<uint8>();
}

bool ULargeStringAsync::IsFullyReceived() const
{
    if (ExpectedChunks <= 0 || ReceivedChunks.Num() != ExpectedChunks)
        return false;

    for (const FByteChunk& C : ReceivedChunks)
    {
        if (C.Data.Num() == 0)
            return false;
    }

    return true;
}

void ULargeStringAsync::ReceiveChunk(
    const TArray<uint8>& Chunk,
    int32 Index,
    int32 TotalChunks)
{
    // Ensure we're on the game thread for thread safety
    if (!IsInGameThread())
    {
        UE_LOG(LogTemp, Error, TEXT("ReceiveChunk called from non-game thread!"));
        return;
    }

    // Validate input
    if (Index < 0 || Index >= TotalChunks)
    {
        UE_LOG(LogTemp, Warning,
            TEXT("ReceiveChunk: Invalid index %d/%d"),
            Index, TotalChunks);
        return;
    }

    if (Chunk.Num() == 0)
    {
        UE_LOG(LogTemp, Warning,
            TEXT("ReceiveChunk: Empty chunk at index %d"),
            Index);
        return;
    }

    // Initialize received chunks array if needed
    if (ExpectedChunks != TotalChunks)
    {
        ExpectedChunks = TotalChunks;
        ReceivedChunks.Reset();
        ReceivedChunks.SetNum(ExpectedChunks);

        UE_LOG(LogTemp, Log,
            TEXT("Receiving %d chunks total"), ExpectedChunks);
    }

    // Deep copy the chunk data into the wrapper struct
    ReceivedChunks[Index].Data = Chunk;

    UE_LOG(LogTemp, Log, TEXT("Received chunk %d/%d (%d bytes)"),
        Index + 1, TotalChunks, Chunk.Num());

    // Check if all chunks received
    if (IsFullyReceived())
    {
        UE_LOG(LogTemp, Log, TEXT("All chunks received, starting reassembly"));
        ReassembleFromChunksAsync();
    }
}

void ULargeStringAsync::ReassembleFromChunksAsync()
{
    // Prevent multiple simultaneous reassembly operations
    bool Expected = false;
    if (!bIsReassembling.compare_exchange_strong(Expected, true))
    {
        UE_LOG(LogTemp, Warning, TEXT("Reassembly already in progress, ignoring duplicate call"));
        return;
    }

    // Use weak pointer to prevent crashes if object is destroyed
    TWeakObjectPtr<ULargeStringAsync> WeakThis(this);

    Async(EAsyncExecution::Thread, [WeakThis]()
        {
            if (!WeakThis.IsValid())
            {
                UE_LOG(LogTemp, Warning, TEXT("ReassembleFromChunksAsync: Object destroyed during async operation"));
                return;
            }

            WeakThis->ReassembleChunks();

            Async(EAsyncExecution::TaskGraphMainThread, [WeakThis]()
                {
                    if (!WeakThis.IsValid())
                        return;

                    WeakThis->bIsReassembling = false;

                    UE_LOG(LogTemp, Log, TEXT("Reassembly complete: %d characters"),
                        WeakThis->Value.Len());

                    WeakThis->OnFullyReceived.Broadcast();
                });
        });
}

void ULargeStringAsync::ReassembleChunks()
{
    SerializedData.Reset();

    // Calculate total size
    int64 TotalBytes = 0;
    for (const FByteChunk& Chunk : ReceivedChunks)
    {
        TotalBytes += Chunk.Data.Num();
    }

    if (TotalBytes == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("ReassembleChunks: No data to reassemble"));
        Value.Empty();
        ExpectedChunks = 0;
        ReceivedChunks.Reset();
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("Reassembling %lld bytes from %d chunks"),
        TotalBytes, ReceivedChunks.Num());

    // Reserve space for all data + null terminator
    SerializedData.Reserve(TotalBytes + 1);

    // Append all chunks
    for (const FByteChunk& Chunk : ReceivedChunks)
    {
        SerializedData.Append(Chunk.Data);
    }

    // CRITICAL: Add null terminator for UTF8 conversion
    SerializedData.Add(0);

    // Convert UTF8 to TCHAR (excluding the null terminator we added)
    FUTF8ToTCHAR Converter(
        reinterpret_cast<const ANSICHAR*>(SerializedData.GetData()),
        SerializedData.Num() - 1
    );

    Value = FString(Converter.Length(), Converter.Get());

    UE_LOG(LogTemp, Log, TEXT("Converted to string: %d characters"), Value.Len());

    // Cleanup
    ExpectedChunks = 0;
    ReceivedChunks.Reset();
}