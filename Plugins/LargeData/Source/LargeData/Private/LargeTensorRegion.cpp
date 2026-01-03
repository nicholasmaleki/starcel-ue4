#include "LargeTensorRegion.h"
#include "Misc/Crc.h"

uint32 GetTensorRegionHash(const FLargeTensorRegionUpdate& Update)
{
    uint32 Hash = 0;

    Hash = FCrc::MemCrc32(
        Update.Start.GetData(),
        Update.Start.Num() * sizeof(int64),
        Hash
    );

    Hash = FCrc::MemCrc32(
        Update.Extent.GetData(),
        Update.Extent.Num() * sizeof(int64),
        Hash
    );

    Hash = FCrc::MemCrc32(
        Update.RawData.GetData(),
        Update.RawData.Num(),
        Hash
    );

    return Hash;
}
