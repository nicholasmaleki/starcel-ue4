#pragma once 

#include "Widgets/SCompoundWidget.h"
#include "Input/Reply.h"
#include "Types/SlateEnums.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"


class SEditableTextBox;

class SHandDriverSourceFactory : public  SCompoundWidget
{
public:

	DECLARE_DELEGATE_OneParam(FOnOkClicked, FIPv4Endpoint);

	SLATE_BEGIN_ARGS(SHandDriverSourceFactory) {}
	SLATE_EVENT(FOnOkClicked, OnOkClicked);
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
private:
	void OnEndpointChanged(const FText& NewValue, ETextCommit::Type);

	FReply OnOkClicked();

	TWeakPtr<SEditableTextBox> EditabledText;
	FOnOkClicked OkClicked;
};