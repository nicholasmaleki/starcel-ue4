#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Net/UnrealNetwork.h"
#include "Engine/NetSerialization.h"
#include "LargeDataObject.generated.h"

USTRUCT()
struct FLargeDataChunk : public FFastArraySerializerItem
{
    GENERATED_BODY()

    UPROPERTY()
    int32 Index;

    UPROPERTY()
    TArray<uint8> Data;

    UPROPERTY()
    uint32 Hash;
};

USTRUCT()
struct FLargeChunkArray : public FFastArraySerializer
{
    GENERATED_BODY()

    UPROPERTY()
    TArray<FLargeDataChunk> Chunks;

    bool NetDeltaSerialize(FNetDeltaSerializeInfo& Info)
    {
        return FFastArraySerializer::FastArrayDeltaSerialize<
            FLargeDataChunk, FLargeChunkArray>(Chunks, Info, *this);
    }
};

template<>
struct TStructOpsTypeTraits<FLargeChunkArray>
    : public TStructOpsTypeTraitsBase2<FLargeChunkArray>
{
    enum { WithNetDeltaSerializer = true };
};

UCLASS(BlueprintType, Blueprintable)
class LARGEDATA_API ULargeDataObject : public UObject
{
    GENERATED_BODY()

public:
    virtual bool IsSupportedForNetworking() const override { return true; }

    UPROPERTY(Replicated)
    FLargeChunkArray ReplicatedChunks;

protected:
    static constexpr int32 ChunkSize = 256 * 1024;

    virtual void SerializeToBytes(TArray<uint8>& OutBytes) const = 0;
    virtual void DeserializeFromBytes(const TArray<uint8>& InBytes) = 0;

    void BuildChunks(const TArray<uint8>&);
    void ApplyChunks(const TArray<uint8>&);

    virtual void GetLifetimeReplicatedProps(
        TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
