#include "LargeDataObject.h"
#include "Net/UnrealNetwork.h"
#include "Engine/NetSerialization.h"

void ULargeDataObject::BuildChunks()
{
    TArray<uint8> Bytes;
    SerializeToBytes(Bytes);

    ReplicatedChunks.Chunks.Empty();

    int32 Offset = 0;
    int32 Index = 0;

    while (Offset < Bytes.Num())
    {
        FLargeDataChunk& Chunk = ReplicatedChunks.Chunks.AddDefaulted_GetRef();
        Chunk.Index = Index++;

        int32 Size = FMath::Min(ChunkSize, Bytes.Num() - Offset);
        Chunk.Data.Append(Bytes.GetData() + Offset, Size);
        Chunk.Hash = FCrc::MemCrc32(Chunk.Data.GetData(), Chunk.Data.Num());

        Offset += Size;
    }

    ReplicatedChunks.MarkArrayDirty();
}

void ULargeDataObject::ApplyChunks()
{
    ReplicatedChunks.Chunks.Sort(
        [](const FLargeDataChunk& A, const FLargeDataChunk& B)
        {
            return A.Index < B.Index;
        });

    TArray<uint8> Bytes;
    for (const auto& Chunk : ReplicatedChunks.Chunks)
        Bytes.Append(Chunk.Data);

    DeserializeFromBytes(Bytes);
}

void ULargeDataObject::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty>& OutLifetimeProps
) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ULargeDataObject, ReplicatedChunks);
}
