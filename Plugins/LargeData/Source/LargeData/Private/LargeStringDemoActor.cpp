#include "LargeStringDemoActor.h"

ALargeStringDemoActor::ALargeStringDemoActor()
{
    PrimaryActorTick.bCanEverTick = false;
    LargeString = nullptr;
}

void ALargeStringDemoActor::BeginPlay()
{
    Super::BeginPlay();

    // Create at runtime (safe, named, GC-tracked)
    LargeString = NewObject<ULargeStringAsync>(this);

    // Bind to completion event
    LargeString->OnFullyReceived.AddDynamic(
        this,
        &ALargeStringDemoActor::OnStringFullyReceived
    );
}

// ---------------- RPCs ----------------

// Server receives chunk from client
void ALargeStringDemoActor::Server_SendChunk_Implementation(
    const TArray<uint8>& Chunk,
    int32 Index,
    int32 TotalChunks)
{
    LargeString->ReceiveChunk(Chunk, Index, TotalChunks);
}

// Client receives chunk from server
void ALargeStringDemoActor::Client_ReceiveChunk_Implementation(
    const TArray<uint8>& Chunk,
    int32 Index,
    int32 TotalChunks)
{
    LargeString->ReceiveChunk(Chunk, Index, TotalChunks);
}

// ---------------- Callbacks ----------------

void ALargeStringDemoActor::OnStringFullyReceived()
{
    UE_LOG(
        LogTemp,
        Log,
        TEXT("Large string fully received! Size: %d bytes"),
        LargeString->GetSerializedSize()
    );

    const bool bIsServer =
        UKismetSystemLibrary::IsDedicatedServer(this);

    if (bIsServer)
    {
        // Modify string on server
        ModifyStringOnServer();

        // Send back to clients
        SendAllChunks();
    }
    else
    {
        // Client: print first 100 characters
        UE_LOG(
            LogTemp,
            Log,
            TEXT("Client sees string start: %s"),
            *LargeString->ToString().Left(100)
        );
    }
}

// ---------------- Sending ----------------

void ALargeStringDemoActor::SendAllChunks()
{
    const bool bIsServer =
        UKismetSystemLibrary::IsDedicatedServer(this);

    const int32 TotalChunks = LargeString->GetChunkCount();

    for (int32 i = 0; i < TotalChunks; ++i)
    {
        const TArray<uint8> Chunk = LargeString->GetChunk(i);

        if (bIsServer)
        {
            Client_ReceiveChunk(Chunk, i, TotalChunks);
        }
        else
        {
            Server_SendChunk(Chunk, i, TotalChunks);
        }
    }
}

// ---------------- Server mutation ----------------

void ALargeStringDemoActor::ModifyStringOnServer()
{
    FString Current = LargeString->ToString();
    Current.Append(TEXT("\n--Modified on server--\n"));

    LargeString->SetFromStringAsync(Current);
}
