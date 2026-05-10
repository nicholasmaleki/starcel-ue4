// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Common/UdpSocketReceiver.h>
#include <Common/UdpSocketBuilder.h>
#include "HandDriverActor.generated.h"


UCLASS()
class HANDDRIVER_API AHandDriverActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHandDriverActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	FSocket* ListenSocket;
	FUdpSocketReceiver* Receiver = nullptr;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "UDP")
		void StartUDPReceiver(const FString& YourChosenSocketName, const FString& TheIP, const int32 ThePort, bool& success);

	UFUNCTION(BlueprintCallable, Category = "UDP")
		void DataRecv(FString& str, bool& success);
	UFUNCTION(BlueprintCallable, Category = "UDP")
		TArray<uint8> DataRecvBytes(bool& success);
};
