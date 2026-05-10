// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "UObject/WeakObjectPtr.h"
#include "Engine/Engine.h"
#include "CoreMinimal.h"
#include "ILiveLinkSource.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HandDriverBPLibrary.generated.h"

/**
 * 
 */
UCLASS()
class HANDDRIVER_API UHandDriverBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create HandDriver Live Link Source at runtime", Keywords = "create HandDriver source live link"), Category = "HandDriver")
	static void CreateSourceRuntime( const FString& ConnectionString, FLiveLinkSourceHandle& Handle );
};
