#pragma once
#include "CoreMinimal.h"
#include "LargeTensorRegion.generated.h"

USTRUCT()
struct FLargeTensorRegionUpdate
{
    GENERATED_BODY()

    UPROPERTY()
    TArray<int64> Start;

    UPROPERTY()
    TArray<int64> Extent;

    UPROPERTY()
    TArray<uint8> RawData;

    UPROPERTY()
    uint32 Hash;
};
