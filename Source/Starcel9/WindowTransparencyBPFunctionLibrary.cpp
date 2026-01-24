// WindowTransparencyBPFunctionLibrary.cpp

#include "WindowTransparencyBPFunctionLibrary.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

// Only include window headers for client builds
#if PLATFORM_WINDOWS && !UE_SERVER
#include "Widgets/SWindow.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include <windows.h>
#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")
#include "Windows/HideWindowsPlatformTypes.h"
#endif

bool UWindowTransparencyBPFunctionLibrary::bIsTransparencyEnabled = false;
bool UWindowTransparencyBPFunctionLibrary::bIsDesktopBackground = false;

#if PLATFORM_WINDOWS && !UE_SERVER

// Get the game window handle
static HWND GetGameWindowHandle()
{
    if (!GEngine || !GEngine->GameViewport)
        return nullptr;

    TSharedPtr<SWindow> GameSWindow = GEngine->GameViewport->GetWindow();
    if (!GameSWindow.IsValid() || !GameSWindow->GetNativeWindow().IsValid())
        return nullptr;

    void* Handle = GameSWindow->GetNativeWindow()->GetOSWindowHandle();
    return static_cast<HWND>(Handle);
}

// Helper to find the WorkerW window for desktop background mode
static HWND GetWorkerW()
{
    HWND hProgman = FindWindowW(L"Progman", nullptr);
    if (!hProgman) return nullptr;

    // Trigger creation of WorkerW
    SendMessageTimeoutW(hProgman, 0x052C, 0xD, 0, SMTO_NORMAL, 1000, nullptr);

    // Find WorkerW
    HWND hWorkerW = nullptr;
    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL
        {
            HWND hShellViewWin = FindWindowExW(hwnd, nullptr, L"SHELLDLL_DefView", nullptr);
            if (hShellViewWin)
            {
                HWND* pWorkerW = reinterpret_cast<HWND*>(lParam);
                *pWorkerW = FindWindowExW(nullptr, hwnd, L"WorkerW", nullptr);
                return 0; // FALSE - stop enumeration
            }
            return 1; // TRUE - continue enumeration
        }, reinterpret_cast<LPARAM>(&hWorkerW));

    return hWorkerW;
}

#endif // PLATFORM_WINDOWS && !UE_SERVER

void UWindowTransparencyBPFunctionLibrary::EnableWindowTransparency(bool bKeepBorder)
{
#if PLATFORM_WINDOWS && !UE_SERVER
    if (GIsEditor)
    {
        UE_LOG(LogTemp, Warning, TEXT("Window transparency does not work in editor - use packaged build"));
        return;
    }

    if (!GEngine || !GEngine->GameViewport)
    {
        UE_LOG(LogTemp, Warning, TEXT("GEngine or GameViewport is null"));
        return;
    }
    HWND hwnd = GetGameWindowHandle();
    if (!hwnd)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get window handle"));
        return;
    }

    // Get current styles
    LONG_PTR currentStyle = GetWindowLongPtrW(hwnd, GWL_STYLE);
    LONG_PTR currentExStyle = GetWindowLongPtrW(hwnd, GWL_EXSTYLE);

    // Add WS_EX_LAYERED for transparency support
    currentExStyle |= WS_EX_LAYERED;

    // Optionally remove border/caption for borderless window
    if (!bKeepBorder)
    {
        currentStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
        currentStyle |= WS_POPUP;
    }

    SetWindowLongPtrW(hwnd, GWL_STYLE, currentStyle);
    SetWindowLongPtrW(hwnd, GWL_EXSTYLE, currentExStyle);

    // Force window update
    RECT rect;
    GetWindowRect(hwnd, &rect);
    SetWindowPos(hwnd, nullptr, rect.left, rect.top,
        rect.right - rect.left, rect.bottom - rect.top,
        SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOACTIVATE);

    // CRITICAL: Extend DWM frame into client area for alpha blending
    MARGINS margins = { -1, -1, -1, -1 };
    HRESULT hr = DwmExtendFrameIntoClientArea(hwnd, &margins);

    if (SUCCEEDED(hr))
    {
        bIsTransparencyEnabled = true;
        UE_LOG(LogTemp, Log, TEXT("Window transparency enabled (KeepBorder: %s)"), bKeepBorder ? TEXT("Yes") : TEXT("No"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("DwmExtendFrameIntoClientArea failed: 0x%08X"), hr);
    }
#endif
    // Silently do nothing on unsupported platforms
}

void UWindowTransparencyBPFunctionLibrary::DisableWindowTransparency()
{
#if PLATFORM_WINDOWS && !UE_SERVER
    if (GIsEditor) return;
    HWND hwnd = GetGameWindowHandle();
    if (!hwnd) return;

    // Remove WS_EX_LAYERED
    LONG_PTR currentExStyle = GetWindowLongPtrW(hwnd, GWL_EXSTYLE);
    currentExStyle &= ~WS_EX_LAYERED;
    SetWindowLongPtrW(hwnd, GWL_EXSTYLE, currentExStyle);

    // Reset DWM margins
    MARGINS margins = { 0, 0, 0, 0 };
    DwmExtendFrameIntoClientArea(hwnd, &margins);

    // Force window update
    RECT rect;
    GetWindowRect(hwnd, &rect);
    SetWindowPos(hwnd, nullptr, rect.left, rect.top,
        rect.right - rect.left, rect.bottom - rect.top,
        SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOACTIVATE);

    bIsTransparencyEnabled = false;
    UE_LOG(LogTemp, Log, TEXT("Window transparency disabled"));
#endif
    // Silently do nothing on unsupported platforms
}

void UWindowTransparencyBPFunctionLibrary::SetAsDesktopBackground()
{
#if PLATFORM_WINDOWS && !UE_SERVER
    if (GIsEditor) return;
    HWND hwnd = GetGameWindowHandle();
    if (!hwnd) return;

    HWND hWorkerW = GetWorkerW();
    if (!hWorkerW)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get WorkerW window"));
        return;
    }

    // Parent to WorkerW
    SetParent(hwnd, hWorkerW);

    // Get screen dimensions
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Set as child window
    SetWindowLongPtrW(hwnd, GWL_STYLE, WS_VISIBLE | WS_CHILD);
    SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, screenWidth, screenHeight, SWP_SHOWWINDOW);

    bIsDesktopBackground = true;
    UE_LOG(LogTemp, Log, TEXT("Window set as desktop background"));
#endif
    // Silently do nothing on unsupported platforms
}

void UWindowTransparencyBPFunctionLibrary::RestoreFromDesktopBackground()
{
#if PLATFORM_WINDOWS && !UE_SERVER
    if (GIsEditor) return;
    HWND hwnd = GetGameWindowHandle();
    if (!hwnd) return;

    // Remove parent
    SetParent(hwnd, nullptr);

    // Restore normal window style
    SetWindowLongPtrW(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);

    // Force window update
    RECT rect;
    GetWindowRect(hwnd, &rect);
    SetWindowPos(hwnd, HWND_NOTOPMOST, rect.left, rect.top,
        rect.right - rect.left, rect.bottom - rect.top,
        SWP_FRAMECHANGED | SWP_SHOWWINDOW);

    bIsDesktopBackground = false;
    UE_LOG(LogTemp, Log, TEXT("Window restored from desktop background"));
#endif
    // Silently do nothing on unsupported platforms
}

void UWindowTransparencyBPFunctionLibrary::SetClickThrough(bool bEnable)
{
#if PLATFORM_WINDOWS && !UE_SERVER
    if (GIsEditor) return;
    HWND hwnd = GetGameWindowHandle();
    if (!hwnd) return;

    LONG_PTR currentExStyle = GetWindowLongPtrW(hwnd, GWL_EXSTYLE);

    if (bEnable)
    {
        currentExStyle |= WS_EX_TRANSPARENT;
    }
    else
    {
        currentExStyle &= ~WS_EX_TRANSPARENT;
    }

    SetWindowLongPtrW(hwnd, GWL_EXSTYLE, currentExStyle);

    UE_LOG(LogTemp, Log, TEXT("Click-through %s"), bEnable ? TEXT("enabled") : TEXT("disabled"));
#else
    UE_LOG(LogTemp, Warning, TEXT("Click-through only supported on Windows client builds"));
#endif
}

bool UWindowTransparencyBPFunctionLibrary::HasContentUnderMouse(UObject* WorldContextObject)
{
#if PLATFORM_WINDOWS && !UE_SERVER
    if (!WorldContextObject || !GEngine)
        return false;

    UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
    if (!World) return false;

    APlayerController* PC = GEngine->GetFirstLocalPlayerController(World);
    if (!PC) return false;

    float X, Y;
    if (!PC->GetMousePosition(X, Y))
        return false;

    FVector2D MousePos(X, Y);
    FHitResult Hit;

    // Check if we hit any visible geometry
    if (PC->GetHitResultAtScreenPosition(MousePos, ECC_Visibility, true, Hit))
        return true;

    return false;
#else
    return false;
#endif
}