#pragma once

#include "LargeDataObject.h"
#include <string>
#include "LargeString.generated.h"

UCLASS(BlueprintType)
class LARGEDATA_API ULargeString : public ULargeDataObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
        void SetFromString(const FString& InString);

    UFUNCTION(BlueprintCallable)
        FString ToString() const;

protected:
    std::string Value;

    virtual void SerializeToBytes(TArray<uint8>& Out) const override;
    virtual void DeserializeFromBytes(const TArray<uint8>& In) override;
};
