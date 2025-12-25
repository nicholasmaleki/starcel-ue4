#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "LargeString.generated.h"

USTRUCT(BlueprintType)
struct FLargeString
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FString Value;

    static constexpr int32 DefaultChunkSize = 1024;

    FLargeString() : Value() {}

    FString ToString() const { return Value; }
    void FromString(const FString& In) { Value = In; }

    bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
    {
        int32 ChunkSize = FMath::Clamp(UHybridSettings::Get()->LargeStringChunkSize, 256, 4096);
        if (Ar.IsSaving())
        {
            int32 TotalLength = Value.Len();
            Ar << TotalLength;
            for (int32 Offset = 0; Offset < TotalLength; Offset += ChunkSize)
            {
                FString Chunk = Value.Mid(Offset, FMath::Min(ChunkSize, TotalLength - Offset));
                Ar << Chunk;
            }
        }
        else
        {
            int32 TotalLength = 0;
            Ar << TotalLength;
            Value.Empty();
            Value.Reserve(TotalLength);
            for (int32 Offset = 0; Offset < TotalLength; Offset += ChunkSize)
            {
                FString Chunk;
                Ar << Chunk;
                Value += Chunk;
            }
        }
        bOutSuccess = true;
        return true;
    }
};

template<>
struct TStructOpsTypeTraits<FLargeString> : public TStructOpsTypeTraitsBase2<FLargeString>
{
    enum
    {
        WithNetSerializer = true,
        WithCopy = true
    };
};