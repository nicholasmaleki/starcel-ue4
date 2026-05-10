// Fill out your copyright notice in the Description page of Project Settings.


#include "HandDriverActor.h"

// Sets default values
AHandDriverActor::AHandDriverActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHandDriverActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHandDriverActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHandDriverActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//delete UDPReceiver;
	//UDPReceiver = nullptr;

	//Clear all sockets!
	//      makes sure repeat plays in Editor dont hold on to old sockets!
	if (this->Receiver != nullptr)
	{
		this->Receiver->Stop();
		delete this->Receiver;
		this->Receiver = nullptr;
	}
	if (ListenSocket)
	{
		ListenSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ListenSocket);
	}

}

void AHandDriverActor::StartUDPReceiver(const FString& YourChosenSocketName, const FString& TheIP, const int32 ThePort, bool& success)
{
	TSharedRef<FInternetAddr> targetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	FIPv4Address Addr;
	FIPv4Address::Parse(TheIP, Addr);
	FIPv4Endpoint Endpoint(FIPv4Address::Any, ThePort);  //所有ip地址本地
	//FIPv4Endpoint Endpoint(Addr, ThePort);                 //指定ip地址
	ListenSocket = FUdpSocketBuilder(*YourChosenSocketName)
		.AsNonBlocking()
		.AsReusable()
		.BoundToEndpoint(Endpoint)
		.WithReceiveBufferSize(2 * 1024 * 1024);
	//BUFFER SIZE
	int32 BufferSize = 2 * 1024 * 1024;
	ListenSocket->SetSendBufferSize(BufferSize, BufferSize);
	ListenSocket->SetReceiveBufferSize(BufferSize, BufferSize);

	if (!ListenSocket)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Scokets"));
		success = false;

	}
	if (ListenSocket)
	{
		UE_LOG(LogTemp, Warning, TEXT("The receiver is initialized"));
		success = true;
		this->Receiver = new FUdpSocketReceiver(ListenSocket, FTimespan::FromMilliseconds(100), TEXT("DEFAULT"));
		this->Receiver->OnDataReceived().BindLambda([this](const FArrayReaderPtr& Data, const FIPv4Endpoint& From)
			{
				TArray<uint8> ReceiveBytes;
				ReceiveBytes.Append(Data->GetData(), Data->Num());
				FMemory::Memcpy(ReceiveBytes.GetData(), Data->GetData(), Data->Num() * sizeof(uint8));

			});
		//this->Receiver->OnDataReceived().BindUFunction(this, "DataRecvBytes2" );
		this->Receiver->Start();
	}
}

void AHandDriverActor::DataRecv(FString& str, bool& success)
{
	if (!ListenSocket)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Send Sockets"));
		success = false;
		//return success;
	}
	TSharedRef<FInternetAddr> targetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	TArray<uint8> ReceivedData;//定义一个接收器
	uint32 Size;
	if (ListenSocket->HasPendingData(Size))
	{
		success = true;
		str = "";
		uint8* Recv = new uint8[Size];
		int32 BytesRead = 0;

		ReceivedData.SetNumUninitialized(FMath::Min(Size, 65507u));
		ListenSocket->RecvFrom(ReceivedData.GetData(), ReceivedData.Num(), BytesRead, *targetAddr);//创建远程接收地址
		char ansiiData[1024];
		memcpy(ansiiData, ReceivedData.GetData(), BytesRead);//拷贝数据到接收器
		ansiiData[BytesRead] = 0;                            //判断数据结束
		FString debugData = ANSI_TO_TCHAR(ansiiData);         //字符串转换
		str = debugData;
		// memset(ansiiData,0,1024);//清空 

	}
	else
	{
		success = false;
	}
}

TArray<uint8> AHandDriverActor::DataRecvBytes(bool& success)
{
	if (!ListenSocket)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Send Sockets"));
		success = false;
		//return success;
	}
	TSharedRef<FInternetAddr> targetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	TArray<uint8> ReceivedData;//定义一个接收器
	uint32 Size;
	if (ListenSocket->HasPendingData(Size))
	{
		success = true;

		uint8* Recv = new uint8[Size];
		int32 BytesRead = 0;

		ReceivedData.SetNumUninitialized(FMath::Min(Size, 65507u));
		ListenSocket->RecvFrom(ReceivedData.GetData(), ReceivedData.Num(), BytesRead, *targetAddr);//创建远程接收地址
		// memset(ansiiData,0,1024);//清空 
		ReceivedData.SetNum(BytesRead);
		return ReceivedData;
	}
	else
	{
		success = false;
	}
	return TArray<uint8>();
}