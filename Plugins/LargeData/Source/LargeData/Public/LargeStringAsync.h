#pragma once

#include "CoreMinimal.h"
#include "LargeDataObject.h"  // Base class for large data objects
#include "Kismet/KismetSystemLibrary.h"
#include "LargeStringAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLargeStringAsyncReceived);

/**
 * ULargeStringAsync
 *
 * Async, chunked large string support.
 * Can be used with or without an actor.
 * Fully compatible with RPC or Python usage.
 */
UCLASS(BlueprintType)
class LARGEDATA_API ULargeStringAsync : public ULargeDataObject
{
    GENERATED_BODY()

public:
    /** Async set string (builds chunks off game thread) */
    UFUNCTION(BlueprintCallable)
        void SetFromStringAsync(const FString& InString);

    /** Async reassemble from received chunks */
    UFUNCTION(BlueprintCallable)
        void ReassembleFromChunksAsync();

    /** Receive a chunk (from RPC) */
    UFUNCTION(BlueprintCallable)
        void ReceiveChunk(const TArray<uint8>& Chunk, int32 Index, int32 TotalChunks);

    /** Event called when the full string has been received */
    UPROPERTY(BlueprintAssignable)
        FOnLargeStringAsyncReceived OnFullyReceived;

    /** Get total number of chunks */
    UFUNCTION(BlueprintCallable)
        int32 GetChunkCount() const { return Chunks.Num(); }

    /** Get a chunk by index */
    UFUNCTION(BlueprintCallable)
        TArray<uint8> GetChunk(int32 Index) const;

    /** Get the reconstructed FString */
    UFUNCTION(BlueprintCallable)
        FString ToString() const { return Value; }

    /** Get serialized UTF-8 size in bytes */
    UFUNCTION(BlueprintCallable)
        int32 GetSerializedSize() const { return SerializedData.Num(); }

protected:
    /** Maximum chunk size (1MB default) */
    static constexpr int32 MaxChunkSize = 1024 * 1024;

    /** Original string as UTF-16 */
    FString Value;

    /** Serialized UTF-8 string */
    TArray<uint8> SerializedData;

    /** Array of chunks ready to send via RPC */
    TArray<TArray<uint8>> Chunks;

    /** Temporary storage for received chunks */
    TArray<TArray<uint8>> ReceivedChunks;

    /** Internal: build chunks from Value/SerializedData */
    void BuildChunks();

    /** Internal: reassemble chunks into Value */
    void ReassembleChunks();
};
