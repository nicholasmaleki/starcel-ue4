// WindowTransparencyBPFunctionLibrary.h

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WindowTransparencyBPFunctionLibrary.generated.h"

/**
 * Blueprint function library for controlling window transparency on Windows
 * Note: These functions are no-ops on dedicated server builds
 */
UCLASS()
class STARCEL9_API UWindowTransparencyBPFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /**
     * Enable window transparency (DWM composition)
     * This only enables the ability to show transparency - use post-process materials to control what's transparent
     * @param bKeepBorder - If true, keeps window border/titlebar. If false, removes them for borderless transparent window
     */
    UFUNCTION(BlueprintCallable, Category = "Window|Transparency")
        static void EnableWindowTransparency(bool bKeepBorder = true);

    /**
     * Disable window transparency and restore normal rendering
     */
    UFUNCTION(BlueprintCallable, Category = "Window|Transparency")
        static void DisableWindowTransparency();

    /**
     * Set window as desktop background (live wallpaper mode)
     */
    UFUNCTION(BlueprintCallable, Category = "Window|Transparency")
        static void SetAsDesktopBackground();

    /**
     * Restore window from desktop background mode
     */
    UFUNCTION(BlueprintCallable, Category = "Window|Transparency")
        static void RestoreFromDesktopBackground();

    /**
     * Enable/disable OS-level click-through (all clicks pass through window)
     * @param bEnable - If true, all mouse input passes through. If false, window receives input normally
     */
    UFUNCTION(BlueprintCallable, Category = "Window|Transparency")
        static void SetClickThrough(bool bEnable);

    /**
     * Check if there's UE content under the mouse (for per-pixel click-through)
     * Returns true if there's an actor or UI widget under mouse
     */
    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Window|Transparency")
        static bool HasContentUnderMouse(UObject* WorldContextObject);

private:
    static bool bIsTransparencyEnabled;
    static bool bIsDesktopBackground;
};