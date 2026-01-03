#pragma once

#include "LargeDataObject.h"

THIRD_PARTY_INCLUDES_START
#pragma push_macro("check")
#undef check
#include <boost/multiprecision/mpfr.hpp>
#pragma pop_macro("check")
THIRD_PARTY_INCLUDES_END

#include "LargeFloat.generated.h"

using BigFloat = boost::multiprecision::number<
    boost::multiprecision::mpfr_float_backend<0>
>;

UCLASS(BlueprintType)
class LARGEDATA_API ULargeFloat : public ULargeDataObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
        void SetFromString(const FString& InDecimal, int32 PrecisionBits);

    UFUNCTION(BlueprintCallable)
        FString ToString() const;

protected:
    virtual void SerializeToBytes(TArray<uint8>& Out) const override;
    virtual void DeserializeFromBytes(const TArray<uint8>& In) override;

private:
    BigFloat Value;
};
