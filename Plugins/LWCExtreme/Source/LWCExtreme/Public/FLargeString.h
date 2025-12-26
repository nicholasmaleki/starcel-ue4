#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "LWCExtremeSettings.h"
#include "FLargeString.generated.h"

USTRUCT(BlueprintType)
struct LWCEXTREME_API FLargeString
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LWCExtreme|LargeString")
        FString Value;

    static constexpr int32 DefaultChunkSize = 1024;

    FLargeString() : Value() {}

    FORCEINLINE FString ToString() const { return Value; }
    FORCEINLINE void FromString(const FString& In)
    {
        int32 MaxLen = GetDefault<ULWCExtremeSettings>()->MaxStringLength;
        if (In.Len() > MaxLen)
        {
            Value = In.Left(MaxLen);
        }
        else
        {
            Value = In;
        }
    }

    FORCEINLINE bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
    {
        int32 MaxLen = GetDefault<ULWCExtremeSettings>()->MaxStringLength;
        int32 ChunkSize = FMath::Clamp(DefaultChunkSize, 256, 4096);

        if (Ar.IsSaving())
        {
            int32 TotalLength = FMath::Min(Value.Len(), MaxLen);
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
            TotalLength = FMath::Min(TotalLength, MaxLen);

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
