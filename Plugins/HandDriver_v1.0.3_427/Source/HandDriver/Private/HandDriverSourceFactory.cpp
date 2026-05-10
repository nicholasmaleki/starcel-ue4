#include "HandDriverSourceFactory.h"
#include "HandDriverSource.h"
#include "SHandDriverSourceFactory.h"

#define LOCTEXT_NAMESPACE "HandDriverSourceFactory"

FText UHandDriverSourceFactory::GetSourceDisplayName() const
{
	return LOCTEXT("SourceDisplayName", "Hand Driver");
}

FText UHandDriverSourceFactory::GetSourceTooltip() const
{
	return LOCTEXT("SourceTooltip", "Creates a connection to a Hand Driver UDP Stream");
}

TSharedPtr<SWidget> UHandDriverSourceFactory::BuildCreationPanel(FOnLiveLinkSourceCreated OnLiveLinkSourceCreated) const
{
	return SNew(SHandDriverSourceFactory)
		.OnOkClicked(SHandDriverSourceFactory::FOnOkClicked::CreateUObject(this, &UHandDriverSourceFactory::OnOkClicked, OnLiveLinkSourceCreated));
}

TSharedPtr<ILiveLinkSource> UHandDriverSourceFactory::CreateSource(const FString& ConnectionString) const
{
	FIPv4Endpoint DeviceEndpoint;
	if (FIPv4Endpoint::Parse(ConnectionString, DeviceEndpoint))
	{
		return TSharedPtr<ILiveLinkSource>();
	}
	return MakeShared<FHandDriverSource>(DeviceEndpoint);
}

TSharedPtr<ILiveLinkSource> UHandDriverSourceFactory::CreateSourceAtRuntime(const FString& ConnectionString)
{
	FIPv4Endpoint DeviceEndpoint;
	if (!FIPv4Endpoint::Parse(ConnectionString, DeviceEndpoint))
	{
		return TSharedPtr<ILiveLinkSource>();
	}
	return MakeShared<FHandDriverSource>(DeviceEndpoint);
}

void UHandDriverSourceFactory::OnOkClicked(FIPv4Endpoint Endpoint, FOnLiveLinkSourceCreated OnLiveLinkSourceCreated) const
{
	OnLiveLinkSourceCreated.ExecuteIfBound(MakeShared<FHandDriverSource>(Endpoint), Endpoint.ToString());
}
#undef LOCTEXT_NAMESPACE