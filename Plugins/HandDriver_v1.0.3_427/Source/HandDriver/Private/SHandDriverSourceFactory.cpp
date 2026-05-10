#include "SHandDriverSourceFactory.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "HandDriverSourceEditor"

void SHandDriverSourceFactory::Construct(const FArguments& InArgs)
{
	OkClicked = InArgs._OnOkClicked;

	FIPv4Endpoint Endpoint;
	Endpoint.Address = FIPv4Address::Any;

	Endpoint.Port = 5555;

	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(250)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.FillWidth(0.5f)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("HandPortNumber","Port Number"))
				]
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				.FillWidth(0.5f)
				[
					SAssignNew(EditabledText, SEditableTextBox)
					.Text(FText::FromString(Endpoint.ToString()))
					.OnTextCommitted(this,&SHandDriverSourceFactory::OnEndpointChanged)
				]
			]
			+SVerticalBox::Slot()
			.HAlign(HAlign_Right)
			.AutoHeight()
			[
				SNew(SButton)
				.OnClicked(this,&SHandDriverSourceFactory::OnOkClicked)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("Ok","Ok"))
				]
			]
		]
			
	];
}

void SHandDriverSourceFactory::OnEndpointChanged(const FText& NewValue, ETextCommit::Type)
{
	TSharedPtr<SEditableTextBox> EditabledTextPin = EditabledText.Pin();
	if (EditabledTextPin.IsValid())
	{
		FIPv4Endpoint Endpoint;
		if (!FIPv4Endpoint::Parse(NewValue.ToString(), Endpoint))
		{
			Endpoint.Address = FIPv4Address::Any;
			Endpoint.Port = 5555;
		}
		EditabledTextPin->SetText(FText::FromString(Endpoint.ToString()));
	}
	
}

FReply SHandDriverSourceFactory::OnOkClicked()
{
	TSharedPtr<SEditableTextBox> EditabledTextPin = EditabledText.Pin();
	if (EditabledTextPin.IsValid())
	{
		FIPv4Endpoint Endpoint;
		if (FIPv4Endpoint::Parse(EditabledTextPin->GetText().ToString(), Endpoint))
		{
			OkClicked.ExecuteIfBound(Endpoint);
		}
	}
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE