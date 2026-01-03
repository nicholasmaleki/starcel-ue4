#pragma once

#include "LargeDataObject.h"

THIRD_PARTY_INCLUDES_START
#pragma push_macro("check")
#undef check
#include <boost/multiprecision/cpp_int.hpp>
#pragma pop_macro("check")
THIRD_PARTY_INCLUDES_END

#include "LargeInt.generated.h"

UCLASS(BlueprintType)
class LARGEDATA_API ULargeInt : public ULargeDataObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
        void SetFromString(const FString& Value);

    UFUNCTION(BlueprintCallable)
        FString ToString() const;

protected:
    boost::multiprecision::cpp_int Value;

    virtual void SerializeToBytes(TArray<uint8>& Out) const override;
    virtual void DeserializeFromBytes(const TArray<uint8>& In) override;
};
