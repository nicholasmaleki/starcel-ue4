// Fill out your copyright notice in the Description page of Project Settings.


#include "HandComMeshComponent.h"


UHandComMeshComponent::UHandComMeshComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	IsInit = false;
	for (int8 BoneIndex = 0; BoneIndex < EHandJointCount; BoneIndex++)
	{
		L_BoneNameMappings.Add(static_cast<EHandJoint>(BoneIndex), TEXT(""));
		R_BoneNameMappings.Add(static_cast<EHandJoint>(BoneIndex),TEXT(""));
	}
	//Init();
}

void UHandComMeshComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UHandComMeshComponent::Init()
{
	if (IsInit)
	{
		return;
	}
	int32 num = SkeletalMesh->GetRefSkeleton().GetNum();
	for (int32 i = 0; i < num; i++)
	{
		FName bone_name = SkeletalMesh->GetRefSkeleton().GetBoneName(i);
		FTransform transform = GetBoneLocalTransformByName(bone_name);
		FQuat origin_rotator;
		if (bone_name.ToString().Contains("Index")|| bone_name.ToString().Contains("Middle")|| bone_name.ToString().Contains("Ring")|| bone_name.ToString().Contains("Pinky"))
		{
			origin_rotator = FQuat(0,0,0,0);
		}
		else
		{
			origin_rotator = transform.GetRotation();
		}
		OriginRotations.Add(bone_name, origin_rotator);
	}
	IsInit = true;
}

void UHandComMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHandComMeshComponent::UpdateBonePose(FName bone_name, float angle, int32 axis)
{
	FTransform transform = GetBoneLocalTransformByName(bone_name);
	FRotator bone_rotate;


	switch (axis)
	{
	case -3:
		bone_rotate = FRotator(transform.GetRotation().GetRotationAxis().X - angle, transform.GetRotation().GetRotationAxis().Y, transform.GetRotation().GetRotationAxis().Z);

		break;
	case -2:
		//bone_rotate = FRotator(transform.GetRotation().GetRotationAxis().X, transform.GetRotation().GetRotationAxis().Y - angle, transform.GetRotation().GetRotationAxis().Z);
		bone_rotate = transform.Rotator().Add(0,-angle,0);

		break;
	case -1:
		bone_rotate = FRotator(transform.GetRotation().GetRotationAxis().X, transform.GetRotation().GetRotationAxis().Y, transform.GetRotation().GetRotationAxis().Z - angle);

		break;
	case 0:
		bone_rotate = FRotator(transform.GetRotation().GetRotationAxis().X + angle, transform.GetRotation().GetRotationAxis().Y, transform.GetRotation().GetRotationAxis().Z);

		break;
	case 1:
		bone_rotate = FRotator(transform.GetRotation().GetRotationAxis().X, transform.GetRotation().GetRotationAxis().Y + angle, transform.GetRotation().GetRotationAxis().Z);

		break;
	case 2:
		bone_rotate = FRotator(transform.GetRotation().GetRotationAxis().X, transform.GetRotation().GetRotationAxis().Y, transform.GetRotation().GetRotationAxis().Z + angle);

		break;
	}

	transform.SetRotation(bone_rotate.Quaternion());
	SetBoneLocalTransformByName(bone_name, transform);
}


void UHandComMeshComponent::UpdateWristRotate(FName bone_name,FQuat quat)
{
	FTransform transform = GetBoneLocalTransformByName(bone_name);

	transform.SetRotation(quat);
	SetBoneLocalTransformByName(bone_name, transform);
}

void UHandComMeshComponent::UpdateBonePose(FName bone_name, float angle1, float angle2, int32 axis1, int32 axis2)
{
	FTransform transform = GetBoneLocalTransformByName(bone_name);
	FRotator bone_rotate;


	switch (axis1)
	{
	case -3:
		bone_rotate = FRotator(transform.GetRotation().GetRotationAxis().X - angle1, transform.GetRotation().GetRotationAxis().Y, transform.GetRotation().GetRotationAxis().Z);

		break;
	case -2:
		bone_rotate = FRotator(transform.GetRotation().GetRotationAxis().X, transform.GetRotation().GetRotationAxis().Y - angle1, transform.GetRotation().GetRotationAxis().Z);

		break;
	case -1:
		bone_rotate = FRotator(transform.GetRotation().GetRotationAxis().X, transform.GetRotation().GetRotationAxis().Y, transform.GetRotation().GetRotationAxis().Z - angle1);

		break;
	case 0:
		bone_rotate = FRotator(transform.GetRotation().GetRotationAxis().X + angle1, transform.GetRotation().GetRotationAxis().Y, transform.GetRotation().GetRotationAxis().Z);

		break;
	case 1:
		bone_rotate = FRotator(transform.GetRotation().GetRotationAxis().X + angle2, transform.GetRotation().GetRotationAxis().Y - angle1, transform.GetRotation().GetRotationAxis().Z);

		break;
	case 2:
		bone_rotate = FRotator(transform.GetRotation().GetRotationAxis().X, transform.GetRotation().GetRotationAxis().Y, transform.GetRotation().GetRotationAxis().Z + angle1);

		break;
	}

	transform.SetRotation(bone_rotate.Quaternion());
	SetBoneLocalTransformByName(bone_name, transform);
}

void UHandComMeshComponent::UpdateBonePose(FName bone_name, float angle1, float angle2,float angle3, int32 axis1, int32 axis2)
{
	FTransform transform = GetBoneLocalTransformByName(bone_name);
	FRotator bone_rotate;


	switch (axis1)
	{
	case -3:
		bone_rotate = FRotator(transform.GetRotation().GetRotationAxis().X - angle1, transform.GetRotation().GetRotationAxis().Y, transform.GetRotation().GetRotationAxis().Z);

		break;
	case -2:
		bone_rotate = FRotator(transform.GetRotation().GetRotationAxis().X, transform.GetRotation().GetRotationAxis().Y - angle1, transform.GetRotation().GetRotationAxis().Z);

		break;
	case -1:
		bone_rotate = FRotator(transform.GetRotation().GetRotationAxis().X, transform.GetRotation().GetRotationAxis().Y, transform.GetRotation().GetRotationAxis().Z - angle1);

		break;
	case 0:
		bone_rotate = FRotator(transform.GetRotation().GetRotationAxis().X + angle1, transform.GetRotation().GetRotationAxis().Y, transform.GetRotation().GetRotationAxis().Z);

		break;
	case 1:
		//bone_rotate = FRotator(transform.GetRotation().GetRotationAxis().X + angle2, transform.GetRotation().GetRotationAxis().Y - angle1, transform.GetRotation().GetRotationAxis().Z+angle3);
		bone_rotate = transform.Rotator().Add(angle2,-angle1,angle3);

		break;
	case 2:
		bone_rotate = FRotator(transform.GetRotation().GetRotationAxis().X, transform.GetRotation().GetRotationAxis().Y, transform.GetRotation().GetRotationAxis().Z + angle1);

		break;
	}

	transform.SetRotation(bone_rotate.Quaternion());
	SetBoneLocalTransformByName(bone_name, transform);
}

void UHandComMeshComponent::ResetBonePose()
{
	int32 num = SkeletalMesh->GetRefSkeleton().GetNum();
	for (int32 i = 0; i < num; i++)
	{
		FName bone_name = SkeletalMesh->GetRefSkeleton().GetBoneName(i);
		FTransform transform = GetBoneLocalTransformByName(bone_name);
		transform.SetRotation(OriginRotations[bone_name]);
		SetBoneLocalTransformByName(bone_name, transform);
	}
}

const FTransform& UHandComMeshComponent::GetBoneLocalTransformByName(const FName& BoneName) const
{
	static FTransform zeroTransform;
	if (!SkeletalMesh || !RequiredBones.IsValid())
	{
		return zeroTransform;
	}

	int32 boneIndex = GetBoneIndex(BoneName);
	if (boneIndex >= 0 && boneIndex < BoneSpaceTransforms.Num())
	{
		return BoneSpaceTransforms[boneIndex];
	}

	return zeroTransform;
}

void UHandComMeshComponent::SetBoneLocalTransformByName(const FName& BoneName, const FTransform& InTransform)
{
	if (!SkeletalMesh || !RequiredBones.IsValid())
	{
		return;
	}
	

	int32 boneIndex = GetBoneIndex(BoneName);
	if (boneIndex >= 0 && boneIndex < BoneSpaceTransforms.Num())
	{
		BoneSpaceTransforms[boneIndex] = InTransform;
		MarkRefreshTransformDirty();
	}
}
