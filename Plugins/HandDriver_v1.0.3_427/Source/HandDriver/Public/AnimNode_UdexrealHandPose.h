#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNodeBase.h"
#include "HandComponent.h"
#include "AnimNode_UdexrealHandPose.generated.h"

USTRUCT(BlueprintInternalUseOnly)
struct HANDDRIVER_API FAnimNode_UdexrealHandPose:public  FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()

	FAnimNode_UdexrealHandPose();

	//FAnimNode_Base interface
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;
	virtual void Evaluate_AnyThread(FPoseContext& Output) override;
	//End of FAnimNode_Base interface

private :
	void Init(USkeletalMeshComponent& SkeletalMeshComponent);
	void ResetBonePose(FCSPose<FCompactPose>& Pose);
	static void SetComponentSpaceRotation(const FName& BoneName, const FQuat& Rotation, FCSPose<FCompactPose>& Pose);
	static FQuat GetComponentSpaceRotation(const FName& BoneName, FCSPose<FCompactPose>& Pose);
	void UpdateBonePose(FName bone_name, float angle, EHandAxis axis,FCSPose<FCompactPose>& Pose);
	void UpdateBonePose(FName bone_name, float angle1, float angle2, EHandAxis axis1, int32 axis2,FCSPose<FCompactPose>& Pose);
	void UpdateBonePose(FName bone_name, float angle1, float angle2, float angle3, EHandAxis axis1,int32 axis2,FCSPose<FCompactPose>& Pose);
	void UpdateBonePose(FName bone_name, float angle1, float angle2, float angle3, EHandAxis axis1,int32 axis2,int32 axis3,FCSPose<FCompactPose>& Pose);
	void HandComponentFingersValueToArray();
private:
	UHandComponent* HandComponent;
	bool IsInit;
	bool IsOrigin;
	TMap<FName, FQuat> OriginRotations;
	
};