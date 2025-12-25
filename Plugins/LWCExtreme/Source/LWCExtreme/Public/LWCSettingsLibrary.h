#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LWCSettings.h"
#include "LWCSettingsLibrary.generated.h"

UCLASS()
class LWCEXTREME_API ULWCSettingsLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Settings")
        static int32 GetDefaultPrecision(const ULWCSettings* Settings)
    {
        return Settings ? Settings->DefaultPrecision : 50;
    }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Settings")
        static int32 GetMaxStringLength(const ULWCSettings* Settings)
    {
        return Settings ? Settings->MaxStringLength : 2000000000;
    }
};
