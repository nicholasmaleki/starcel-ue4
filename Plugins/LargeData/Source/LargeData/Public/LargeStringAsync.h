#pragma once

#include "CoreMinimal.h"
#include "LargeDataObject.h"
#include "LargeStringAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLargeStringAsyncReceived);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChunksBuilt);

/**
 * Wrapper struct for byte array chunks (needed because UE doesn't support nested TArrays)
 */
USTRUCT(BlueprintType)
struct FByteChunk
{
    GENERATED_BODY()

        UPROPERTY()
        TArray<uint8> Data;

    FByteChunk() {}
    FByteChunk(TArray<uint8>&& InData) : Data(MoveTemp(InData)) {}
};

/**
 * ULargeStringAsync
 *
 * Async, chunked large string support.
 * Pure data + async logic (NO RPCs here).
 * 1GB-safe via chunking.
 */
UCLASS(BlueprintType)
class LARGEDATA_API ULargeStringAsync : public ULargeDataObject
{
    GENERATED_BODY()

public:

    ULargeStringAsync();

    /** Build chunks asynchronously from FString */
    UFUNCTION(BlueprintCallable)
        void SetFromStringAsync(const FString& InString);

    /** Receive a chunk (called by RPC actor or Python) */
    UFUNCTION(BlueprintCallable)
        void ReceiveChunk(const TArray<uint8>& Chunk, int32 Index, int32 TotalChunks);

    /** Async reassembly */
    UFUNCTION(BlueprintCallable)
        void ReassembleFromChunksAsync();

    /** Set the chunk size (must be called before SetFromStringAsync) */
    UFUNCTION(BlueprintCallable)
        void SetChunkSize(int32 NewChunkSize);

    /** Get the current chunk size */
    UFUNCTION(BlueprintCallable)
        int32 GetChunkSize() const { return ChunkSize; }

    /** Fired when full string reconstructed */
    UPROPERTY(BlueprintAssignable)
        FOnLargeStringAsyncReceived OnFullyReceived;

    /** Fired when chunks are ready */
    UPROPERTY(BlueprintAssignable)
        FOnChunksBuilt OnChunksBuilt;

    UFUNCTION(BlueprintCallable)
        int32 GetChunkCount() const { return Chunks.Num(); }

    UFUNCTION(BlueprintCallable)
        int32 GetExpectedChunkCount() const { return ExpectedChunks; }

    UFUNCTION(BlueprintCallable)
        bool IsFullyReceived() const;

    UFUNCTION(BlueprintCallable)
        TArray<uint8> GetChunk(int32 Index) const;

    UFUNCTION(BlueprintCallable)
        FString ToString() const { return Value; }

    UFUNCTION(BlueprintCallable)
        int32 GetSerializedSize() const { return SerializedData.Num(); }

protected:

    /**
     * Default chunk size: 63KB (safe under 64KB RPC limit)
     * Can be configured via SetChunkSize() from Python/Blueprint
     */
    static constexpr int32 DefaultChunkSize = 63 * 1024;

    UPROPERTY()
        int32 ChunkSize;

    UPROPERTY()
        FString Value;

    UPROPERTY()
        TArray<uint8> SerializedData;

    UPROPERTY()
        TArray<FByteChunk> Chunks;

    UPROPERTY()
        TArray<FByteChunk> ReceivedChunks;

    UPROPERTY()
        int32 ExpectedChunks = 0;

    // Thread safety flag
    std::atomic<bool> bIsReassembling{ false };

    void BuildChunks();
    void ReassembleChunks();
};