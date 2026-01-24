#pragma once

#include "CoreMinimal.h"
#include "LargeDataObject.h"
#include "LargeStringAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLargeStringAsyncReceived);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChunksBuilt);

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

    /** Build chunks asynchronously from FString */
    UFUNCTION(BlueprintCallable)
    void SetFromStringAsync(const FString& InString);

    /** Receive a chunk (called by RPC actor or Python) */
    UFUNCTION(BlueprintCallable)
    void ReceiveChunk(const TArray<uint8>& Chunk, int32 Index, int32 TotalChunks);

    /** Async reassembly */
    UFUNCTION(BlueprintCallable)
    void ReassembleFromChunksAsync();

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

    /** 1MB chunks (safe for RPC + memory) */
    static constexpr int32 MaxChunkSize = 1024 * 1024;

    FString Value;
    TArray<uint8> SerializedData;
    TArray<TArray<uint8>> Chunks;
    TArray<TArray<uint8>> ReceivedChunks;

    int32 ExpectedChunks = 0;

    void BuildChunks();
    void ReassembleChunks();
};
