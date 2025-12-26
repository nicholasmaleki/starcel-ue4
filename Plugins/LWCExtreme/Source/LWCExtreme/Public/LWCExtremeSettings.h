#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LWCExtremeSettings.generated.h"

UCLASS(BlueprintType, Config = Game, DefaultConfig)
class LWCEXTREME_API ULWCExtremeSettings : public UObject
{
    GENERATED_BODY()

public:

    // Runtime-configurable precision for FHybridNumber calculations
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = "LWCExtreme|Settings")
        int32 DefaultPrecision = 50;

    // Maximum allowed digits for FLargeString or similar large data types
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = "LWCExtreme|Settings")
        int32 MaxStringLength = 2000000000;

    // Inline getters and setters
    FORCEINLINE int32 GetDefaultPrecision() const { return DefaultPrecision; }
    FORCEINLINE void SetDefaultPrecision(int32 Precision) { DefaultPrecision = Precision; }

    FORCEINLINE int32 GetMaxStringLength() const { return MaxStringLength; }
    FORCEINLINE void SetMaxStringLength(int32 MaxLength) { MaxStringLength = MaxLength; }
};
