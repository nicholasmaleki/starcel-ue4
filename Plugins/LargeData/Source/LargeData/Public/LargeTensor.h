#pragma once
#include "LargeDataObject.h"
#include "LargeTensorRegion.h"

THIRD_PARTY_INCLUDES_START
#pragma push_macro("check")
#undef check
#include <xtensor/containers/xarray.hpp>
#pragma pop_macro("check")
THIRD_PARTY_INCLUDES_END

#include "LargeTensor.generated.h"

UCLASS(BlueprintType)
class LARGEDATA_API ULargeTensor : public ULargeDataObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
        void UpdateRegion(
            const TArray<int64>& Start,
            const TArray<int64>& Extent,
            const TArray<uint8>& RawData
        );

protected:
    xt::xarray<double> Tensor;

    UPROPERTY(Replicated)
        TArray<FLargeTensorRegionUpdate> RegionUpdates;

    virtual void SerializeToBytes(TArray<uint8>& Out) const override;
    virtual void DeserializeFromBytes(const TArray<uint8>& In) override;

    void ApplyRegion(const FLargeTensorRegionUpdate& Update);
};
