#include "LargeStringAsync.h"
#include "Async/Async.h"

void ULargeStringAsync::SetFromStringAsync(const FString& InString)
{
    UE_LOG(LogTemp, Log,
        TEXT("SetFromStringAsync: chars=%d"),
        InString.Len());

    Async(EAsyncExecution::Thread, [this, InString]()
    {
        Value = InString;

        FTCHARToUTF8 Converter(*Value);
        SerializedData.Reset(Converter.Length());
        SerializedData.Append(
            reinterpret_cast<const uint8*>(Converter.Get()),
            Converter.Length()
        );

        BuildChunks();

        Async(EAsyncExecution::TaskGraphMainThread, [this]()
        {
            UE_LOG(LogTemp, Log,
                TEXT("Chunks built: %d"), Chunks.Num());
            OnChunksBuilt.Broadcast();
        });
    });
}

void ULargeStringAsync::BuildChunks()
{
    Chunks.Reset();

    const int32 TotalBytes = SerializedData.Num();
    for (int32 Offset = 0; Offset < TotalBytes; Offset += MaxChunkSize)
    {
        const int32 Size = FMath::Min(MaxChunkSize, TotalBytes - Offset);
        TArray<uint8> Chunk;
        Chunk.Append(&SerializedData[Offset], Size);
        Chunks.Add(MoveTemp(Chunk));
    }

    UE_LOG(LogTemp, Log,
        TEXT("SerializedData=%d bytes, Chunks=%d"),
        TotalBytes, Chunks.Num());
}

TArray<uint8> ULargeStringAsync::GetChunk(int32 Index) const
{
    return Chunks.IsValidIndex(Index) ? Chunks[Index] : TArray<uint8>();
}

bool ULargeStringAsync::IsFullyReceived() const
{
    if (ExpectedChunks <= 0 || ReceivedChunks.Num() != ExpectedChunks)
        return false;

    for (const TArray<uint8>& C : ReceivedChunks)
    {
        if (C.Num() == 0)
            return false;
    }

    return true;
}

void ULargeStringAsync::ReceiveChunk(
    const TArray<uint8>& Chunk,
    int32 Index,
    int32 TotalChunks)
{
    if (Index < 0 || Index >= TotalChunks)
    {
        UE_LOG(LogTemp, Warning,
            TEXT("ReceiveChunk: Invalid index %d/%d"),
            Index, TotalChunks);
        return;
    }

    if (ExpectedChunks != TotalChunks)
    {
        ExpectedChunks = TotalChunks;
        ReceivedChunks.SetNum(ExpectedChunks);

        UE_LOG(LogTemp, Log,
            TEXT("Receiving %d chunks total"), ExpectedChunks);
    }

    ReceivedChunks[Index] = Chunk;

    if (IsFullyReceived())
    {
        ReassembleFromChunksAsync();
    }
}

void ULargeStringAsync::ReassembleFromChunksAsync()
{
    Async(EAsyncExecution::Thread, [this]()
    {
        ReassembleChunks();

        Async(EAsyncExecution::TaskGraphMainThread, [this]()
        {
            UE_LOG(LogTemp, Log, TEXT("Reassembly complete"));
            OnFullyReceived.Broadcast();
        });
    });
}

void ULargeStringAsync::ReassembleChunks()
{
    SerializedData.Reset();

    int64 TotalBytes = 0;
    for (const TArray<uint8>& Chunk : ReceivedChunks)
        TotalBytes += Chunk.Num();

    SerializedData.Reserve(TotalBytes);

    for (const TArray<uint8>& Chunk : ReceivedChunks)
        SerializedData.Append(Chunk);

    Value = UTF8_TO_TCHAR(SerializedData.GetData());

    ExpectedChunks = 0;
    ReceivedChunks.Reset();
}
