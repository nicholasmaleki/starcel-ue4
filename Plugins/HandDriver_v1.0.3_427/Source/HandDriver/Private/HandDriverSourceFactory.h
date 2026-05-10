#pragma once

#include "LiveLinkSourceFactory.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "HandDriverSourceFactory.generated.h"

UCLASS()
class UHandDriverSourceFactory : public ULiveLinkSourceFactory
{
public:

	GENERATED_BODY()

	virtual FText GetSourceDisplayName() const override;
	virtual FText GetSourceTooltip() const override;

	virtual EMenuType GetMenuType() const override { return EMenuType::SubPanel; }
	virtual TSharedPtr<SWidget> BuildCreationPanel(FOnLiveLinkSourceCreated OnLiveLinkSourceCreated) const override;
	TSharedPtr<ILiveLinkSource> CreateSource(const FString& ConnectionString) const override;

	static TSharedPtr<ILiveLinkSource> CreateSourceAtRuntime(const FString& ConnectionString);

private:
	void OnOkClicked(FIPv4Endpoint Endpoint, FOnLiveLinkSourceCreated OnLiveLinkSourceCreated) const;

};