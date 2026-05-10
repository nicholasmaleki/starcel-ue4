// Fill out your copyright notice in the Description page of Project Settings.


#include "HandDriverBPLibrary.h"
#include "ILiveLinkClient.h"
#include "LiveLinkClient.h"
#include "LiveLinkClientReference.h"
#include "HandDriverSourceFactory.h"

void UHandDriverBPLibrary::CreateSourceRuntime( const FString& ConnectionString, FLiveLinkSourceHandle& Handle )
{
	TSharedPtr<ILiveLinkSource> NewSource;
	while (true)
	{
		NewSource = UHandDriverSourceFactory::CreateSourceAtRuntime( ConnectionString );
		if (NewSource != nullptr)
		{
			break;
		}
	}
	FLiveLinkClientReference ClientRef;
	ClientRef.GetClient( )->AddSource( NewSource );
	Handle = FLiveLinkSourceHandle();
	Handle.SetSourcePointer( NewSource );
}
