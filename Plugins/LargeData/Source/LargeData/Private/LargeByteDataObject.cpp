#include "LargeByteDataObject.h"

void ULargeByteDataObject::SetData(const TArray<uint8>& InData)
{
    Data = InData;
    BuildChunks();  // Build replication chunks whenever data changes
}

const TArray<uint8>& ULargeByteDataObject::GetData() const
{
    return Data;
}

void ULargeByteDataObject::SerializeToBytes(TArray<uint8>& OutBytes) const
{
    // Copy the internal data to the output array
    OutBytes = Data;
}

void ULargeByteDataObject::DeserializeFromBytes(const TArray<uint8>& InBytes)
{
    // Copy the incoming bytes to internal storage
    Data = InBytes;
}
