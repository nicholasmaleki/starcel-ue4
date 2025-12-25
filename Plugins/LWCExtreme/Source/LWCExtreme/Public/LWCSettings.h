#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LWCSettings.generated.h"

UCLASS(BlueprintType, Config = Game)
class LWCEXTREME_API ULWCSettings : public UObject
{
    GENERATED_BODY()

public:
    // Runtime-configurable precision for FHybridNumber calculations
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = "LWCExtreme|Settings")
        int32 DefaultPrecision = 50;

    // Max allowed digits for FLargeString
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = "LWCExtreme|Settings")
        int32 MaxStringLength = 2000000000;
};