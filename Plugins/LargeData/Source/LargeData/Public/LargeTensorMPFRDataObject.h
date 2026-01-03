#pragma once

#include "CoreMinimal.h"
#include "LargeDataObject.h"

#pragma push_macro("check")
#undef check
#include <boost/multiprecision/mpfr.hpp>
#include <boost/multiprecision/number.hpp>
#include <xtensor/containers/xarray.hpp>
#include <xtensor/io/xio.hpp>
#pragma pop_macro("check")

#include "LargeTensorMPFRDataObject.generated.h"

// Define MPFR float type with 256-bit precision
using mpfr_float = boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<256>>;

/**
 * Concrete ULargeDataObject subclass storing an xtensor xarray of mpfr_float
 */
UCLASS(BlueprintType, Blueprintable)
class LARGEDATA_API ULargeTensorMPFRDataObject : public ULargeDataObject
{
    GENERATED_BODY()

public:
    ULargeTensorMPFRDataObject() = default;

    /** Set the tensor */
    void SetTensor(const xt::xarray<mpfr_float>& InTensor);

    /** Get the tensor */
    const xt::xarray<mpfr_float>& GetTensor() const;

protected:
    /** Override abstract methods from ULargeDataObject */
    virtual void SerializeToBytes(TArray<uint8>& OutBytes) const override;
    virtual void DeserializeFromBytes(const TArray<uint8>& InBytes) override;

private:
    /** Internal tensor storage */
    xt::xarray<mpfr_float> Tensor;
};
