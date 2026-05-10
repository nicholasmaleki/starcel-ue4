#pragma once

#include "CoreMinimal.h"
#include "AnimGraphNode_Base.h"
#include "AnimNode_UdexrealHandPose.h"
#include "AnimGraphNode_UdexrealHandPose.generated.h"

/**
 * 
 */
UCLASS()
class UAnimGraphNode_UdexrealHandPose : public UAnimGraphNode_Base
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category = Settings)
	FAnimNode_UdexrealHandPose Node;

	virtual  FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual  FText GetTooltipText() const override;
	virtual  FText GetMenuCategory() const override;
};
