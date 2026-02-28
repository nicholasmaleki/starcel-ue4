#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StarcelHelper.generated.h"

UCLASS()
class STARCEL9_API UStarcelHelper : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category="Starcel")
        static void ClickLMB();
};