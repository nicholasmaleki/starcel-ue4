/// Created by HISPlayer © - 2024  

#include "DelegateManager.h"

UDelegateManager::UDelegateManager() {
	UE_LOG(LogTemp, Log, TEXT("UDelegateManager Constructor"));
}

UDelegateManager::~UDelegateManager() {
	UE_LOG(LogTemp, Log, TEXT("UDelegateManager Destructor"));

	OnLoading.Clear();
	OnPlay.Clear();
	OnPause.Clear();
	OnStop.Clear();
	OnEndContent.Clear();
	OnBuffering.Clear();
	OnStatusChanged.Clear();
	OnTrackChanged.Clear();
	OnError.Clear();
	OnTimedMetadata.Clear();
	OnPCMDataReceived.Clear();
	OnPCMDataReceived.RemoveAll(this);
	OnInitComplete.Clear();
	OnSeekComplete.Clear();
}
