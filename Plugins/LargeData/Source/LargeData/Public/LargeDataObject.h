#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Net/UnrealNetwork.h"
#include "Engine/NetSerialization.h"
#include "LargeDataObject.generated.h"

/** Single chunk of large data, replicated efficiently */
USTRUCT()
struct FLargeDataChunk : public FFastArraySerializerItem
{
    GENERATED_BODY()

        UPROPERTY()
        int32 Index = 0;

    UPROPERTY()
        TArray<uint8> Data;

    UPROPERTY()
        uint32 Hash = 0;
};

/** Array of chunks using FastArraySerializer for efficient replication */
USTRUCT()
struct FLargeChunkArray : public FFastArraySerializer
{
    GENERATED_BODY()

        UPROPERTY()
        TArray<FLargeDataChunk> Chunks;

    bool NetDeltaSerialize(FNetDeltaSerializeInfo& Info)
    {
        return FFastArraySerializer::FastArrayDeltaSerialize<FLargeDataChunk, FLargeChunkArray>(Chunks, Info, *this);
    }
};

/** Required for NetDeltaSerialize */
template<>
struct TStructOpsTypeTraits<FLargeChunkArray> : public TStructOpsTypeTraitsBase2<FLargeChunkArray>
{
    enum { WithNetDeltaSerializer = true };
};

/** Base class for objects that replicate large data in chunks */
UCLASS(BlueprintType, Blueprintable)
class LARGEDATA_API ULargeDataObject : public UObject
{
    GENERATED_BODY()

public:
    ULargeDataObject();

    virtual bool IsSupportedForNetworking() const override { return true; }

    /** Replicated chunks */
    UPROPERTY(ReplicatedUsing = OnRep_ReplicatedChunks)
        FLargeChunkArray ReplicatedChunks;

    /** Build chunks from current object data */
    UFUNCTION(BlueprintCallable, Category = "Large Data")
        void BuildChunks();

    /** Apply replicated chunks back to object data */
    UFUNCTION(BlueprintCallable, Category = "Large Data")
        void ApplyChunks();

    /** Optional: dynamically set chunk size (in bytes) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Large Data")
        int32 DynamicChunkSize;

protected:
    /** Serialize object data into byte array (to be implemented by subclasses) */
    virtual void SerializeToBytes(TArray<uint8>& OutBytes) const PURE_VIRTUAL(ULargeDataObject::SerializeToBytes, );

    /** Deserialize object data from byte array (to be implemented by subclasses) */
    virtual void DeserializeFromBytes(const TArray<uint8>& InBytes) PURE_VIRTUAL(ULargeDataObject::DeserializeFromBytes, );

    /** Called when replicated chunks change on clients */
    UFUNCTION()
        void OnRep_ReplicatedChunks();

    /** Get lifetime replicated properties */
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
    /** Returns chunk size to use (either dynamic or default) */
    FORCEINLINE int32 GetChunkSize() const { return DynamicChunkSize > 0 ? DynamicChunkSize : 256 * 1024; }
};
