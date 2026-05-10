// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PoseableMeshComponent.h"
#include "HandDriverTypes.h"
#include "HandComMeshComponent.generated.h"

/**
 */
UCLASS(ClassGroup = Rendering, hidecategories = (Object, Physics), config = Engine, editinlinenew, meta = (BlueprintSpawnableComponent))
class HANDDRIVER_API UHandComMeshComponent : public UPoseableMeshComponent
{
	GENERATED_UCLASS_BODY()
public: 
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Init();

	void UpdateBonePose(FName bone_name, float angle, int32 axis);
	void UpdateWristRotate(FName bone_name, FQuat quat);
	void UpdateBonePose(FName bone_name, float angle1, float angle2, int32 axis1, int32 axis2);
	void UpdateBonePose(FName bone_name, float angle1, float angle2,float angle3, int32 axis1, int32 axis2);

	void ResetBonePose();

	const FTransform& GetBoneLocalTransformByName(const FName& BoneName) const;
	void SetBoneLocalTransformByName(const FName& BoneName, const FTransform& InTransform);

public:
	bool IsInit;

	UPROPERTY(EditAnywhere,Category = "LeftHand")
	TMap<EHandJoint, FName> L_BoneNameMappings;

	UPROPERTY(EditAnywhere,Category = "RightHand")
	TMap<EHandJoint, FName> R_BoneNameMappings;

private:
	TMap<FName, FQuat> OriginRotations;


	
};