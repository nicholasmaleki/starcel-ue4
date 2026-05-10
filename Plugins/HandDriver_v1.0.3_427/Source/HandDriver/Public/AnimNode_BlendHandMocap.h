#pragma once

#include "CoreMinimal.h"
#include "HandComponent.h"
class UHandDriverController;
#include "AnimNode_BlendHandMocap.generated.h"

USTRUCT(BlueprintInternalUseOnly)
struct HANDDRIVER_API FAnimNode_BlendHandMocap : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()

	FAnimNode_BlendHandMocap();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	FPoseLink Hand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	FPoseLink MoCap;

	// FAnimNode_Base interface
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;

	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext & Context) override;

	virtual void Update_AnyThread(const FAnimationUpdateContext & Context) override;

	virtual void Evaluate_AnyThread(FPoseContext& Output) override;
	// End of FAnimNode_Base interface

private:
	UHandComponent* HandComponent;
};
