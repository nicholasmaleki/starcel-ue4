#include "LWCExtreme.h"
#include "CoreMinimal.h"
#include "HAL/PlatformProcess.h"
#include "Misc/Paths.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FLWCExtremeModule, LWCExtreme)

// Keep handles alive for entire process lifetime
static void* GMPHandle = nullptr;
static void* MPFRHandle = nullptr;

void FLWCExtremeModule::StartupModule()
{
    // Resolve ThirdParty directory
    const FString BaseDir = FPaths::Combine(
        FPaths::ProjectPluginsDir(),
        TEXT("LWCExtreme"),
        TEXT("ThirdParty")
    );

    const FString BinDir = FPaths::Combine(BaseDir, TEXT("Bin"), TEXT("Win64"));

    const FString GMPPath = FPaths::Combine(BinDir, TEXT("gmp-10.dll"));
    const FString MPFRPath = FPaths::Combine(BinDir, TEXT("mpfr-6.dll"));

    GMPHandle = FPlatformProcess::GetDllHandle(*GMPPath);
    MPFRHandle = FPlatformProcess::GetDllHandle(*MPFRPath);

    if (!GMPHandle || !MPFRHandle)
    {
        UE_LOG(LogTemp, Fatal, TEXT("Failed to load GMP/MPFR DLLs"));
    }
}

void FLWCExtremeModule::ShutdownModule()
{
    // INTENTIONALLY EMPTY
    // Do NOT FreeDllHandle()
    // We want the OS to clean up at process exit
}
