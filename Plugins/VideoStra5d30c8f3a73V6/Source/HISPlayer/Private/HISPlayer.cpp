/// Created by HISPlayer © - 2024  

#include "HISPlayerPrivatePCH.h"
#include "../Public/HisPlayerFunctions.h"

DEFINE_LOG_CATEGORY(LogHISPlayer);

#define LOCTEXT_NAMESPACE "HISPlayer"

class FHISPlayer : public IHISPlayer
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FHISPlayer, HISPlayer)

void FHISPlayer::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UHISPlayerFunctions::StartupModule();
}

void FHISPlayer::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UHISPlayerFunctions::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE
