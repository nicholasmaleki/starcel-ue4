#pragma once

#include "CoreMinimal.h"
#include "LargeDataObject.h"
#include "LargeByteDataObject.generated.h"

/**
 * A concrete subclass of ULargeDataObject that stores a simple byte array.
 */
UCLASS(BlueprintType, Blueprintable)
class LARGEDATA_API ULargeByteDataObject : public ULargeDataObject
{
    GENERATED_BODY()

public:
    ULargeByteDataObject() = default;

    /** Set the internal data */
    void SetData(const TArray<uint8>& InData);

    /** Get the internal data */
    const TArray<uint8>& GetData() const;

protected:
    /** Implement abstract methods from ULargeDataObject */
    virtual void SerializeToBytes(TArray<uint8>& OutBytes) const override;
    virtual void DeserializeFromBytes(const TArray<uint8>& InBytes) override;

private:
    /** Internal storage of raw bytes */
    TArray<uint8> Data;
};
