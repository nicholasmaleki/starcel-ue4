#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LWCExtremeSettings.h"
#include "LWCExtremeSettingsLibrary.generated.h"

UCLASS()
class LWCEXTREME_API ULWCExtremeSettingsLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Settings")
        static int32 GetDefaultPrecision(const ULWCExtremeSettings* Settings)
    {
        return Settings ? Settings->DefaultPrecision : 50;
    }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Settings")
        static int32 GetMaxStringLength(const ULWCExtremeSettings* Settings)
    {
        return Settings ? Settings->MaxStringLength : 2000000000;
    }
};
