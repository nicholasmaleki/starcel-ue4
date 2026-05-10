#pragma once

#include "ILiveLinkSOurce.h"
#include "HAL/Runnable.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "IMessageContext.h"

class FRunnableThread;
class FSocket;
class ILiveLinkClient;
class ISocketSubsystem;

class HANDDRIVER_API FHandDriverSource : public ILiveLinkSource, public FRunnable
{

public:
	FHandDriverSource(FIPv4Endpoint Endpoint);

	virtual ~FHandDriverSource();

	//Begin ILiveLinkSource Interface
	virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;

	virtual bool IsSourceStillValid() const override;

	virtual bool RequestSourceShutdown() override;

	virtual FText GetSourceMachineName() const override { return SourceMachineName; };

	virtual FText GetSourceStatus() const override { return SourceStatus; };

	virtual FText GetSourceType() const override { return SourceType; };

	//End ILiveLinkSource Interface

	//Begin FRunnable Interface

	virtual bool Init() override { return true; };

	virtual uint32 Run() override;

	void Start();

	virtual void Stop() override;

	virtual void Exit() override {}

	//End FRunnable Interface

	void HandleReceivedData(TSharedPtr<TArray<uint8>, ESPMode::ThreadSafe> ReceivedData);

private:
	ILiveLinkClient* Client;

	// Our identifier in LiveLink
	FGuid SourceGuid;

	FMessageAddress LiveLinkAddress;

	FText SourceStatus;
	FText SourceMachineName;
	FText SourceType;

	FIPv4Endpoint DeviceEndpoint;

	//Socket to receive data from the device
	FSocket* Socket;

	//Subsystem associated to Socket
	ISocketSubsystem* SocketSubsystem;

	//Threadsafe Bool for terminating the main thread loop
	FThreadSafeBool Stopping;

	//Thread to run the socket on
	FRunnableThread* Thread;

	//Name of the sockets thread
	FString ThreadName;

	//Time to wait between attempted receives
	FTimespan WaitTime;

	//List of subjects we have already encountered
	TSet<FName> EncounteredSubjects;

	//Buffer to receive socket data into
	TArray<uint8> RecvBuffer;
};