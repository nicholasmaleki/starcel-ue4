#include "LargeDataObject.h"
#include "Net/UnrealNetwork.h"
#include "Engine/NetSerialization.h"

ULargeDataObject::ULargeDataObject()
{
    DynamicChunkSize = 0; // Use default unless explicitly set
}

void ULargeDataObject::BuildChunks()
{
    TArray<uint8> Bytes;
    SerializeToBytes(Bytes);

    ReplicatedChunks.Chunks.Empty();

    int32 Offset = 0;
    int32 Index = 0;
    const int32 SizePerChunk = GetChunkSize();

    while (Offset < Bytes.Num())
    {
        FLargeDataChunk& Chunk = ReplicatedChunks.Chunks.AddDefaulted_GetRef();
        Chunk.Index = Index++;

        int32 Size = FMath::Min(SizePerChunk, Bytes.Num() - Offset);
        Chunk.Data.Append(Bytes.GetData() + Offset, Size);
        Chunk.Hash = FCrc::MemCrc32(Chunk.Data.GetData(), Chunk.Data.Num());

        Offset += Size;
    }

    // Mark array dirty so replication system sends updates
    ReplicatedChunks.MarkArrayDirty();
}

void ULargeDataObject::ApplyChunks()
{
    // Ensure chunks are applied in order
    ReplicatedChunks.Chunks.Sort([](const FLargeDataChunk& A, const FLargeDataChunk& B)
        {
            return A.Index < B.Index;
        });

    TArray<uint8> Bytes;
    Bytes.Reserve(ReplicatedChunks.Chunks.Num() * GetChunkSize());

    for (const auto& Chunk : ReplicatedChunks.Chunks)
    {
        Bytes.Append(Chunk.Data);
    }

    DeserializeFromBytes(Bytes);
}

void ULargeDataObject::OnRep_ReplicatedChunks()
{
    // Automatically apply chunks when updated on clients
    ApplyChunks();
}

void ULargeDataObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ULargeDataObject, ReplicatedChunks);
}
