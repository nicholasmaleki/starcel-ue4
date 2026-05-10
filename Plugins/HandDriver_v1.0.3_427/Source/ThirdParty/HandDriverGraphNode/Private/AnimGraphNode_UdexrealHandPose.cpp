//Fill out your copyright notice in the Description page of Project Settings.

#include "AnimGraphNode_UdexrealHandPose.h"

#define LOCTEXT_NAMESPACE "HandDriverAnimNode"

UAnimGraphNode_UdexrealHandPose::UAnimGraphNode_UdexrealHandPose(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FText UAnimGraphNode_UdexrealHandPose::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("NodeTitle", "Udexreal Hand Pose");
}

FText UAnimGraphNode_UdexrealHandPose::GetTooltipText() const
{
	return LOCTEXT("NodeTooltip", "Retrieves the current pose associated with the supplied subject");
}

FText UAnimGraphNode_UdexrealHandPose::GetMenuCategory() const
{
	return LOCTEXT("NodeCategory", "HandDriver");
}

#undef LOCTEXT_NAMESPACE