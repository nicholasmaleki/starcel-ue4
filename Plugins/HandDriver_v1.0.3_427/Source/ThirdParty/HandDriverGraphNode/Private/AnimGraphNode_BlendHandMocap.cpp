//Fill out your copyright notice in the Description page of Project Settings.

#include "AnimGraphNode_BlendHandMocap.h"

#define LOCTEXT_NAMESPACE "HandDriverAnimNode"

UAnimGraphNode_BlendHandMocap::UAnimGraphNode_BlendHandMocap(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FText UAnimGraphNode_BlendHandMocap::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("NodeTitle","Blend Hand Data In Mocap");
}

FText UAnimGraphNode_BlendHandMocap::GetTooltipText() const
{
	return LOCTEXT("NodeTooltip", "Add hand data with mocap full body data");
}

FLinearColor UAnimGraphNode_BlendHandMocap::GetNodeTitleColor() const
{
	return FLinearColor(0.75f, 0.75f, 0.75f);
}

FText UAnimGraphNode_BlendHandMocap::GetMenuCategory() const
{
	return LOCTEXT("NodeCategory", "HandDriver Blend Mocap Data");
}

#undef LOCTEXT_NAMESPACE
