#include "AnimNode_UdexrealHandPose.h"
#include "Animation/AnimInstanceProxy.h"
#include "Kismet/KismetMathLibrary.h"

FAnimNode_UdexrealHandPose::FAnimNode_UdexrealHandPose()
{
	IsInit = false;
}

void FAnimNode_UdexrealHandPose::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	FAnimNode_Base::Initialize_AnyThread(Context);
	UAnimInstance* anim = Context.AnimInstanceProxy->GetSkelMeshComponent()->GetAnimInstance();
	if (anim == nullptr || anim->GetOwningActor() == nullptr)
	{
		return;
	}

	AActor* actor = anim->GetOwningActor();
	UActorComponent* controller_comp = actor->GetComponentByClass(UHandComponent::StaticClass());
	UHandComponent* handComponent = dynamic_cast<UHandComponent*>(controller_comp);
	if (handComponent == nullptr)
	{
		return;
	}
	HandComponent = handComponent;

	if (handComponent->L_BoneNameMappings.Num()==0)
	{
		for (int8 BoneIndex = 0; BoneIndex < EHandJointCount; BoneIndex++)
		{
			handComponent->L_BoneNameMappings.Add(static_cast<EHandJoint>(BoneIndex), TEXT(""));
		}
	}
	if (handComponent->R_BoneNameMappings.Num()==0)
	{
		for (int8 BoneIndex = 0; BoneIndex < EHandJointCount; BoneIndex++)
		{
			handComponent->R_BoneNameMappings.Add(static_cast<EHandJoint>(BoneIndex), TEXT(""));
		}
	}

	USkeletalMeshComponent& SkeletalMeshComponent = *(Context.AnimInstanceProxy->GetSkelMeshComponent());
	Init(SkeletalMeshComponent);
}

void FAnimNode_UdexrealHandPose::Init(USkeletalMeshComponent& SkeletalMeshComponent)
{
	if (IsInit)
	{
		return;
	}
	int32 num = SkeletalMeshComponent.SkeletalMesh->GetRefSkeleton().GetNum();
	for (int32 i = 0; i < num; i++)
	{
		FName bone_name = SkeletalMeshComponent.SkeletalMesh->GetRefSkeleton().GetBoneName(i);
		FQuat origin_rotator = FQuat::Identity;
		if (OriginRotations.Num()==0)
		{
			OriginRotations.Add(bone_name, origin_rotator);
		}
		if (HandComponent->L_BoneNameMappings.Num() < 16)
		{
			return;
		}

		if (bone_name.ToString().Contains("Left"))
		{
			if (bone_name.ToString().Contains("Thumb"))
			{
				if (bone_name.ToString().Contains("1"))
				{
					HandComponent->L_BoneNameMappings[EHandJoint::Thumb_1] = bone_name;
				}
				if (bone_name.ToString().Contains("2"))
				{
					HandComponent->L_BoneNameMappings[EHandJoint::Thumb_2] = bone_name;
				}
				if (bone_name.ToString().Contains("3"))
				{
					HandComponent->L_BoneNameMappings[EHandJoint::Thumb_3] = bone_name;
				}
			}
			if (bone_name.ToString().Contains("Index"))
			{
				if (bone_name.ToString().Contains("1"))
				{
					HandComponent->L_BoneNameMappings[EHandJoint::Index_1] = bone_name;
				}
				if (bone_name.ToString().Contains("2"))
				{
					HandComponent->L_BoneNameMappings[EHandJoint::Index_2] = bone_name;
				}
				if (bone_name.ToString().Contains("3"))
				{
					HandComponent->L_BoneNameMappings[EHandJoint::Index_3] = bone_name;
				}
			}
			if (bone_name.ToString().Contains("Middle"))
			{
				if (bone_name.ToString().Contains("1"))
				{
					HandComponent->L_BoneNameMappings[EHandJoint::Middle_1] = bone_name;
				}
				if (bone_name.ToString().Contains("2"))
				{
					HandComponent->L_BoneNameMappings[EHandJoint::Middle_2] = bone_name;
				}
				if (bone_name.ToString().Contains("3"))
				{
					HandComponent->L_BoneNameMappings[EHandJoint::Middle_3] = bone_name;
				}
			}
			if (bone_name.ToString().Contains("Ring"))
			{
				if (bone_name.ToString().Contains("1"))
				{
					HandComponent->L_BoneNameMappings[EHandJoint::Ring_1] = bone_name;
				}
				if (bone_name.ToString().Contains("2"))
				{
					HandComponent->L_BoneNameMappings[EHandJoint::Ring_2] = bone_name;
				}
				if (bone_name.ToString().Contains("3"))
				{
					HandComponent->L_BoneNameMappings[EHandJoint::Ring_3] = bone_name;
				}
			}
			if (bone_name.ToString().Contains("Pinky"))
			{
				if (bone_name.ToString().Contains("1"))
				{
					HandComponent->L_BoneNameMappings[EHandJoint::Pinky_1] = bone_name;
				}
				if (bone_name.ToString().Contains("2"))
				{
					HandComponent->L_BoneNameMappings[EHandJoint::Pinky_2] = bone_name;
				}
				if (bone_name.ToString().Contains("3"))
				{
					HandComponent->L_BoneNameMappings[EHandJoint::Pinky_3] = bone_name;
				}
			}
		}

		if (HandComponent->R_BoneNameMappings.Num() < 16)
		{
			return;
		}
		if (bone_name.ToString().Contains("Right"))
		{
			if (bone_name.ToString().Contains("Thumb"))
			{
				if (bone_name.ToString().Contains("1"))
				{
					HandComponent->R_BoneNameMappings[EHandJoint::Thumb_1] = bone_name;
				}
				if (bone_name.ToString().Contains("2"))
				{
					HandComponent->R_BoneNameMappings[EHandJoint::Thumb_2] = bone_name;
				}
				if (bone_name.ToString().Contains("3"))
				{
					HandComponent->R_BoneNameMappings[EHandJoint::Thumb_3] = bone_name;
				}
			}
			if (bone_name.ToString().Contains("Index"))
			{
				if (bone_name.ToString().Contains("1"))
				{
					HandComponent->R_BoneNameMappings[EHandJoint::Index_1] = bone_name;
				}
				if (bone_name.ToString().Contains("2"))
				{
					HandComponent->R_BoneNameMappings[EHandJoint::Index_2] = bone_name;
				}
				if (bone_name.ToString().Contains("3"))
				{
					HandComponent->R_BoneNameMappings[EHandJoint::Index_3] = bone_name;
				}
			}
			if (bone_name.ToString().Contains("Middle"))
			{
				if (bone_name.ToString().Contains("1"))
				{
					HandComponent->R_BoneNameMappings[EHandJoint::Middle_1] = bone_name;
				}
				if (bone_name.ToString().Contains("2"))
				{
					HandComponent->R_BoneNameMappings[EHandJoint::Middle_2] = bone_name;
				}
				if (bone_name.ToString().Contains("3"))
				{
					HandComponent->R_BoneNameMappings[EHandJoint::Middle_3] = bone_name;
				}
			}
			if (bone_name.ToString().Contains("Ring"))
			{
				if (bone_name.ToString().Contains("1"))
				{
					HandComponent->R_BoneNameMappings[EHandJoint::Ring_1] = bone_name;
				}
				if (bone_name.ToString().Contains("2"))
				{
					HandComponent->R_BoneNameMappings[EHandJoint::Ring_2] = bone_name;
				}
				if (bone_name.ToString().Contains("3"))
				{
					HandComponent->R_BoneNameMappings[EHandJoint::Ring_3] = bone_name;
				}
			}
			if (bone_name.ToString().Contains("Pinky"))
			{
				if (bone_name.ToString().Contains("1"))
				{
					HandComponent->R_BoneNameMappings[EHandJoint::Pinky_1] = bone_name;
				}
				if (bone_name.ToString().Contains("2"))
				{
					HandComponent->R_BoneNameMappings[EHandJoint::Pinky_2] = bone_name;
				}
				if (bone_name.ToString().Contains("3"))
				{
					HandComponent->R_BoneNameMappings[EHandJoint::Pinky_3] = bone_name;
				}
			}
		}
	}
	IsInit = true;
}

void FAnimNode_UdexrealHandPose::ResetBonePose(FCSPose<FCompactPose>& Pose)
{
	// if (IsOrigin)
	// {
	// 	return;
	// }
	OriginRotations = TMap<FName, FQuat>();
	if (HandComponent->L_BoneNameMappings.Num() < EHandJointCount || HandComponent->R_BoneNameMappings.Num() < EHandJointCount)
	{
		return;
	}
	for (int i = 0; i < EHandJointCount; i++)
	{
		EHandJoint joint = static_cast<EHandJoint>(i);

		FName bone_name = HandComponent->L_BoneNameMappings[joint];
		if (bone_name == NAME_None)
		{
			continue;
		}
		FQuat quat;
		if (bone_name.ToString().Contains("index") || bone_name.ToString().Contains("middle") || bone_name.ToString().
			Contains("ring") || bone_name.ToString().Contains("pinky"))
		{
			if (HandComponent->L_Straighten)
			{
				quat = FQuat::Identity;
			}
			
			
		}
		else
		{
			
				quat = GetComponentSpaceRotation(bone_name, Pose);
			
		}
		OriginRotations.Add(bone_name, quat);

		bone_name = HandComponent->R_BoneNameMappings[joint];
		if (bone_name == NAME_None)
		{
			continue;
		}
		
		if (bone_name.ToString().Contains("index") || bone_name.ToString().Contains("middle") || bone_name.ToString().
			Contains("ring") || bone_name.ToString().Contains("pinky"))
		{
		
			if (HandComponent->R_Straighten)
			{
				quat = FQuat::Identity;
			}
			
		}else
		{
			
				quat = GetComponentSpaceRotation(bone_name, Pose);
			
		}
		OriginRotations.Add(bone_name, quat);
	}
	IsOrigin = true;
}

void FAnimNode_UdexrealHandPose::Update_AnyThread(const FAnimationUpdateContext& Context)
{
	GetEvaluateGraphExposedInputs().Execute(Context);
	if (HandComponent == nullptr)
	{
		UAnimInstance* anim = Context.AnimInstanceProxy->GetSkelMeshComponent()->GetAnimInstance();
		if (anim == nullptr || anim->GetOwningActor() == nullptr)
		{
			return;
		}

		UActorComponent* controller_comp = anim->GetOwningActor()->GetComponentByClass(
			UHandComponent::StaticClass());
		UHandComponent* handComponent = dynamic_cast<UHandComponent*>(controller_comp);
		if (handComponent == nullptr)
		{
			return;
		}
		HandComponent = handComponent;
	}
}

void FAnimNode_UdexrealHandPose::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	FAnimNode_Base::CacheBones_AnyThread(Context);
}


void FAnimNode_UdexrealHandPose::Evaluate_AnyThread(FPoseContext& Output)
{
	
		if (HandComponent == nullptr) return;

		if (HandComponent->L_CalibrationStatus < 3 && HandComponent->L_Angles.Num())
		{
			return;
		}

		FCSPose<FCompactPose> pose;
		pose.InitPose(&Output.Pose.GetBoneContainer());
		const FBoneContainer Container = pose.GetPose().GetBoneContainer();

		ResetBonePose(pose);

		HandComponentFingersValueToArray();
		

		//
		// int32 bone_index = Container.GetPoseBoneIndexForBoneName(HandComponent->L_BoneNameMappings[EHandJoint::Index_2]);
		// if (bone_index != INDEX_NONE)
		// {
		// 	FCompactPoseBoneIndex cp_index = Container.MakeCompactPoseIndex(FMeshPoseBoneIndex(bone_index));
		// 	FTransform cs_transform = pose.GetComponentSpaceTransform(cp_index);
		// 	FRotator rot = cs_transform.GetRotation().Rotator().Add(HandComponent->L_Angles[5],0,0);
		// 	cs_transform.SetRotation(rot.Quaternion());
		// 	pose.SetComponentSpaceTransform(cp_index, cs_transform);
		// }
		// bone_index = Container.GetPoseBoneIndexForBoneName(HandComponent->L_BoneNameMappings[EHandJoint::Index_3]);
		// if (bone_index != INDEX_NONE)
		// {
		// 	FCompactPoseBoneIndex cp_index = Container.MakeCompactPoseIndex(FMeshPoseBoneIndex(bone_index));
		// 	FTransform cs_transform = pose.GetComponentSpaceTransform(cp_index);
		// 	FRotator rot = cs_transform.GetRotation().Rotator().Add(HandComponent->L_Angles[4],0,0);
		// 	cs_transform.SetRotation(rot.Quaternion());
		// 	pose.SetComponentSpaceTransform(cp_index, cs_transform);
		// }
		/*if (HandComponent->L_EnableChanges)*/
		
			if (HandComponent->L_CalibrationStatus >= 3 && !HandComponent->L_BoneNameMappings.Num()==0)
			{
				if (!HandComponent->bUseThumbAxis_L)
				{UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Thumb_1],HandComponent->L_Angles[3] + HandComponent->L_Thumb_Yaw_Offset,
					HandComponent->L_Yaw_Axis, pose);
					UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Thumb_1],HandComponent->L_Angles[2] * HandComponent->L_Thumb_Coefficient + HandComponent->L_Thumb_Pitch_Offset,
					HandComponent->L_Pitch_Axis, pose);
					UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Thumb_1],HandComponent->L_Angles[20] + HandComponent->L_Thumb_Roll_Offset,
					HandComponent->L_Roll_Axis,pose);
					UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Thumb_2], HandComponent->L_Angles[1],
					HandComponent->L_Pitch_Axis, pose);
					UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Thumb_3], HandComponent->L_Angles[0],
					HandComponent->L_Pitch_Axis, pose);
			
				}
				else
				{
					UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Thumb_1],HandComponent->L_Angles[3] + HandComponent->L_Thumb_Yaw_Offset,
					HandComponent->L_Thumb_Yaw_Axis, pose);
					UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Thumb_1],HandComponent->L_Angles[2]*HandComponent->L_Thumb_Coefficient + HandComponent->L_Thumb_Pitch_Offset,
					HandComponent->L_Thumb_Pitch_Axis,pose);
					UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Thumb_1],HandComponent->L_Angles[20] + HandComponent->L_Thumb_Roll_Offset,
					HandComponent->L_Thumb_Roll_Axis,pose);
					UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Thumb_2],HandComponent->L_Angles[1],
					HandComponent->L_Pitch_Axis, pose);
					UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Thumb_3],HandComponent->L_Angles[0],
					HandComponent->L_Pitch_Axis, pose);
				}
		
		
				//
				// //
				UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Index_1],
							   HandComponent->L_Angles[6] + HandComponent->L_Finger_Pitch_Offset, HandComponent->L_Pitch_Axis,
							   pose);
				float a1 = UKismetMathLibrary::Abs(HandComponent->L_Angles[6]) / 100;
				if (a1 > 1)
				{
					a1 = 1;
				}
				float b = HandComponent->L_Finger_Offsets[0];
				float a2 = HandComponent->L_Finger_Coefficient - b;

				float offset = a1 * a2 + b;
				UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Index_1], HandComponent->L_Angles[7] + offset,/////StraightFinger
							   HandComponent->L_Yaw_Axis, pose);
				UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Index_1], HandComponent->L_Angles[21],
							   HandComponent->L_Roll_Axis, pose);
				UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Index_2],
							   HandComponent->L_Angles[5] + HandComponent->L_Finger_Pitch_Offset, HandComponent->L_Pitch_Axis,
							   pose);
				UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Index_3], HandComponent->L_Angles[4],
							   HandComponent->L_Pitch_Axis, pose);
				// //
				UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Middle_1],
							   HandComponent->L_Angles[10] + HandComponent->L_Finger_Pitch_Offset, HandComponent->L_Pitch_Axis,
							   pose);

				UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Middle_1], -HandComponent->L_Angles[11],
							   HandComponent->L_Yaw_Axis, pose);
				UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Middle_2],
							   HandComponent->L_Angles[9] + HandComponent->L_Finger_Pitch_Offset, HandComponent->L_Pitch_Axis,
							   pose);
				UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Middle_3], HandComponent->L_Angles[8],
							   HandComponent->L_Pitch_Axis, pose);
				// //
				UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Ring_1],
							   HandComponent->L_Angles[14] + HandComponent->L_Finger_Pitch_Offset, HandComponent->L_Pitch_Axis,
							   pose);
				a1 = UKismetMathLibrary::Abs(HandComponent->L_Angles[14]) / 100;
				if (a1 > 1)
				{
					a1 = 1;
				}
				b = HandComponent->L_Finger_Offsets[2];
				a2 = HandComponent->L_Finger_Coefficient - b;
				offset = a1 * a2 + b;
				UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Ring_1], -HandComponent->L_Angles[15] - offset,
							   HandComponent->L_Yaw_Axis, pose);
				//UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Ring_1], -HandComponent->L_Finger_Coefficient, HandComponent->L_Roll_Axis, pose);
				UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Ring_2],
							   HandComponent->L_Angles[13] + HandComponent->L_Finger_Pitch_Offset, HandComponent->L_Pitch_Axis,
							   pose);
				UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Ring_3], HandComponent->L_Angles[12],
							   HandComponent->L_Pitch_Axis, pose);
				// //
				UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Pinky_1],
							   HandComponent->L_Angles[18] + HandComponent->L_Finger_Pitch_Offset, HandComponent->L_Pitch_Axis,
							   pose);
				a1 = UKismetMathLibrary::Abs(HandComponent->L_Angles[18]) / 100;
				if (a1 > 1)
				{
					a1 = 1;
				}
				b = HandComponent->L_Finger_Offsets[3];
				a2 = HandComponent->L_Finger_Coefficient - b;
				offset = a1 * a2 + b;
				UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Pinky_1], -HandComponent->L_Angles[19] - offset,
							   HandComponent->L_Yaw_Axis, pose);
				UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Pinky_1], HandComponent->L_Angles[22],
							   HandComponent->L_Roll_Axis, pose);
				UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Pinky_2],
							   HandComponent->L_Angles[17] + HandComponent->L_Finger_Pitch_Offset, HandComponent->L_Pitch_Axis,
							   pose);
				UpdateBonePose(HandComponent->L_BoneNameMappings[EHandJoint::Pinky_3], HandComponent->L_Angles[16],
							   HandComponent->L_Pitch_Axis, pose);
			}
		

////下面是RightHand

		
		
			if (HandComponent->R_CalibrationStatus >= 3 && !HandComponent->R_BoneNameMappings.Num()==0)
			{
				if (!HandComponent->bUseThumbAxis_R)
				{
					UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Thumb_1],HandComponent->R_Angles[3] + HandComponent->R_Thumb_Yaw_Offset,
					HandComponent->R_Yaw_Axis, pose);
					UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Thumb_1],HandComponent->R_Angles[2] * HandComponent->R_Thumb_Coefficient +HandComponent->R_Thumb_Pitch_Offset,
					HandComponent->R_Pitch_Axis, pose);
					UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Thumb_1],HandComponent->R_Angles[20] + HandComponent->R_Thumb_Roll_Offset,
					HandComponent->R_Roll_Axis,pose);
					UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Thumb_2], HandComponent->R_Angles[1],
					HandComponent->R_Pitch_Axis, pose);
					UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Thumb_3], HandComponent->R_Angles[0],
					HandComponent->R_Pitch_Axis, pose);
			
				}
				else
				{
					UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Thumb_1],HandComponent->R_Angles[3] + HandComponent->R_Thumb_Yaw_Offset,
					HandComponent->R_Thumb_Yaw_Axis, pose);
					UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Thumb_1],HandComponent->R_Angles[2] * HandComponent->R_Thumb_Coefficient + HandComponent->R_Thumb_Pitch_Offset,
					HandComponent->R_Thumb_Pitch_Axis, pose);
					UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Thumb_1],HandComponent->R_Angles[20] + HandComponent->R_Thumb_Roll_Offset,
					HandComponent->R_Thumb_Roll_Axis,pose);
					UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Thumb_2], HandComponent->R_Angles[1],
					HandComponent->R_Pitch_Axis, pose);
					UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Thumb_3], HandComponent->R_Angles[0],
					HandComponent->R_Pitch_Axis, pose);
				}
		
				//
				// //
				UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Index_1],
							   HandComponent->R_Angles[6] + HandComponent->R_Finger_Pitch_Offset, HandComponent->R_Pitch_Axis,
							   pose);
				float a1 = UKismetMathLibrary::Abs(HandComponent->R_Angles[6]) / 100;
				if (a1 > 1)
				{
					a1 = 1;
				}
				float b = HandComponent->R_Finger_Offsets[0];
				float a2 = HandComponent->R_Finger_Coefficient - b;
				float offset = a1 * a2 + b;
				UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Index_1], HandComponent->R_Angles[7] + offset,
							   HandComponent->R_Yaw_Axis, pose);
				UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Index_1], HandComponent->R_Angles[21],
							   HandComponent->R_Roll_Axis, pose);
				UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Index_2],
							   HandComponent->R_Angles[5] + HandComponent->R_Finger_Pitch_Offset, HandComponent->R_Pitch_Axis,
							   pose);
				UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Index_3], HandComponent->R_Angles[4],
							   HandComponent->R_Pitch_Axis, pose);
				// //
				UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Middle_1],
							   HandComponent->R_Angles[10] + HandComponent->R_Finger_Pitch_Offset, HandComponent->R_Pitch_Axis,
							   pose);
				UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Middle_1], -HandComponent->R_Angles[11],
							   HandComponent->R_Yaw_Axis, pose);
				//UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Middle_1], -HandComponent->R_Finger_Coefficient, HandComponent->R_Roll_Axis, pose);
				UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Middle_2],
							   HandComponent->R_Angles[9] + HandComponent->R_Finger_Pitch_Offset, HandComponent->R_Pitch_Axis,
							   pose);
				UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Middle_3], HandComponent->R_Angles[8],
							   HandComponent->R_Pitch_Axis, pose);
				// //
				UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Ring_1],
							   HandComponent->R_Angles[14] + HandComponent->R_Finger_Pitch_Offset, HandComponent->R_Pitch_Axis,
							   pose);
				a1 = UKismetMathLibrary::Abs(HandComponent->R_Angles[14]) / 100;
				if (a1 > 1)
				{
					a1 = 1;
				}
				b = HandComponent->R_Finger_Offsets[2];
				a2 = HandComponent->R_Finger_Coefficient - b;
				offset = a1 * a2 + b;
				UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Ring_1], -HandComponent->R_Angles[15] - offset,
				HandComponent->R_Yaw_Axis, pose);
				//UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Ring_1], -HandComponent->R_Finger_Coefficient, HandComponent->R_Roll_Axis, pose);
				UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Ring_2],HandComponent->R_Angles[13] + HandComponent->R_Finger_Pitch_Offset,
				HandComponent->R_Pitch_Axis,pose);
				UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Ring_3], HandComponent->R_Angles[12],
				HandComponent->R_Pitch_Axis, pose);
				// // 
				UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Pinky_1],HandComponent->R_Angles[18] + HandComponent->R_Finger_Pitch_Offset,
				HandComponent->R_Pitch_Axis,pose);
				a1 = UKismetMathLibrary::Abs(HandComponent->R_Angles[18]) / 100;
				if (a1 > 1)
				{
					a1 = 1;
				}
				b = HandComponent->R_Finger_Offsets[3];
				a2 = HandComponent->R_Finger_Coefficient - b;
				offset = a1 * a2 + b;
				UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Pinky_1], -HandComponent->R_Angles[19] - offset,
							   HandComponent->R_Yaw_Axis, pose);
				UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Pinky_1], HandComponent->R_Angles[22],
							   HandComponent->R_Roll_Axis, pose);
				UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Pinky_2],
							   HandComponent->R_Angles[17] + HandComponent->R_Finger_Pitch_Offset, HandComponent->R_Pitch_Axis,
							   pose);
				UpdateBonePose(HandComponent->R_BoneNameMappings[EHandJoint::Pinky_3], HandComponent->R_Angles[16],
							   HandComponent->R_Pitch_Axis, pose);
			}
		
	
			
		
		// for (auto bone_rot : OriginRotations)
		// {
		// 	int32 MeshBoneIndex = Container.GetPoseBoneIndexForBoneName(bone_rot.Key);
		// 	if (MeshBoneIndex != INDEX_NONE)
		// 	{
		// 		FCompactPoseBoneIndex CPIndex = Container.MakeCompactPoseIndex(FMeshPoseBoneIndex(MeshBoneIndex));
		// 		FTransform CSTransformFromSource = pose.GetComponentSpaceTransform(CPIndex);
		// 		CSTransformFromSource.SetRotation(bone_rot.Value);
		// 		pose.SetComponentSpaceTransform(CPIndex, CSTransformFromSource);
		// 	}
		// }
		FCSPose<FCompactPose>::ConvertComponentPosesToLocalPoses(pose, Output.Pose);
	
	
}

void FAnimNode_UdexrealHandPose::UpdateBonePose(FName bone_name, float angle, EHandAxis axis, FCSPose<FCompactPose>& pose)
{
	FRotator bone_rotate;
	FQuat rot;
	if (OriginRotations.Contains(bone_name))
	{
		rot = OriginRotations[bone_name];
	}
	else
	{
		rot = GetComponentSpaceRotation(bone_name, pose);
	}
	switch (axis)
	{
	case EHandAxis::negative_X:
		bone_rotate = rot.Rotator().Add(-angle, 0, 0);
		break;
	case EHandAxis::negative_Y:
		bone_rotate = rot.Rotator().Add(0, -angle, 0);
		break;
	case EHandAxis::negative_Z:
		bone_rotate = rot.Rotator().Add(0, 0, -angle);
		break;
	case EHandAxis::X:
		bone_rotate = rot.Rotator().Add(angle, 0, 0);
		break;
	case EHandAxis::Y:
		bone_rotate = rot.Rotator().Add(0, angle, 0);
		break;
	case EHandAxis::Z:
		bone_rotate = rot.Rotator().Add(0, 0, angle);
		break;
	}
	if (OriginRotations.Contains(bone_name))
	{
		OriginRotations[bone_name] = bone_rotate.Quaternion();
	}
	else
	{
		OriginRotations.Add(bone_name, bone_rotate.Quaternion());
	}
	SetComponentSpaceRotation(bone_name, bone_rotate.Quaternion(), pose);
}

void FAnimNode_UdexrealHandPose::HandComponentFingersValueToArray()
{
	HandComponent->L_Finger_Offsets[0]=HandComponent->L_Index;
	HandComponent->L_Finger_Offsets[1]=HandComponent->L_Middle;
	HandComponent->L_Finger_Offsets[2]=HandComponent->L_Ring;
	HandComponent->L_Finger_Offsets[3]=HandComponent->L_Pinky;

	HandComponent->R_Finger_Offsets[0]=HandComponent->R_Index;
	HandComponent->R_Finger_Offsets[1]=HandComponent->R_Middle;
	HandComponent->R_Finger_Offsets[2]=HandComponent->R_Ring;
	HandComponent->R_Finger_Offsets[3]=HandComponent->R_Pinky;
}

/*
void FAnimNode_UdexrealHandPose::UpdateBonePose(FName bone_name, float angle1, float angle2, EHandAxis axis1, int32 axis2,
                                                FCSPose<FCompactPose>& pose)
{
	FRotator bone_rotate;

	FQuat rot = GetComponentSpaceRotation(bone_name, pose);

	switch (axis1)
	{
	case EHandAxis::negative_X:
		bone_rotate = rot.Rotator().Add(-angle2, -angle1, 0);
		break;
	case EHandAxis::negative_Y:
		bone_rotate = rot.Rotator().Add(angle2, -angle1, 0);
		break;
	case EHandAxis::negative_Z:
		bone_rotate = rot.Rotator().Add(-angle2, angle1, 0);
		break;
	case EHandAxis::X:
		bone_rotate = rot.Rotator().Add(angle2, angle1, 0);
		break;
	}
	if (OriginRotations.Contains(bone_name))
	{
		OriginRotations[bone_name] = bone_rotate.Quaternion();
	}
	else
	{
		OriginRotations.Add(bone_name, bone_rotate.Quaternion());
	}
	SetComponentSpaceRotation(bone_name, bone_rotate.Quaternion(), pose);
}

void FAnimNode_UdexrealHandPose::UpdateBonePose(FName bone_name, float angle1, float angle2, float angle3, EHandAxis axis1,
                                                int32 axis2, FCSPose<FCompactPose>& pose)
{
	FRotator bone_rotate;

	FQuat rot = GetComponentSpaceRotation(bone_name, pose);
	if (bone_name.ToString().Contains("Index") || bone_name.ToString().Contains("Middle") || bone_name.ToString().
		Contains("Ring") || bone_name.ToString().Contains("Pinky"))
	{
		rot = FQuat::Identity;
	}

	switch (axis1)
	{
	case EHandAxis::negative_X:
		bone_rotate = rot.Rotator().Add(-angle2, angle1, angle3);
		break;
	case EHandAxis::negative_Y:
		bone_rotate = rot.Rotator().Add(angle2, -angle1, angle3);
		break;
	case EHandAxis::negative_Z:
		bone_rotate = rot.Rotator().Add(angle2, angle1, -angle3);
		break;
	case EHandAxis::X:
		bone_rotate = rot.Rotator().Add(angle2, angle1, angle3);
		break;
	case EHandAxis::Y:
		bone_rotate = rot.Rotator().Add(-angle2, angle1, -angle3);
		break;
	case EHandAxis::Z:
		bone_rotate = rot.Rotator().Add(angle2, -angle1, -angle3);
		break;
	/*case	6:
		bone_rotate = rot.Rotator().Add(-angle2, -angle1, angle3);
		break;
	case 7:
		bone_rotate = rot.Rotator().Add(-angle2, -angle1, -angle3);
		break;#1#
	}
	if (OriginRotations.Contains(bone_name))
	{
		OriginRotations[bone_name] = bone_rotate.Quaternion();
	}
	else
	{
		OriginRotations.Add(bone_name, bone_rotate.Quaternion());
	}
	SetComponentSpaceRotation(bone_name, bone_rotate.Quaternion(), pose);
}
*/


void FAnimNode_UdexrealHandPose::SetComponentSpaceRotation(const FName& BoneName, const FQuat& Rotation,
                                                           FCSPose<FCompactPose>& Pose)
{
	const FBoneContainer BoneContainer = Pose.GetPose().GetBoneContainer();

	int32 bone_index = BoneContainer.GetPoseBoneIndexForBoneName(BoneName);
	if (bone_index > INDEX_NONE)
	{
		FCompactPoseBoneIndex cp_index = BoneContainer.MakeCompactPoseIndex(FMeshPoseBoneIndex(bone_index));
		FTransform cs_transform = Pose.GetLocalSpaceTransform(cp_index);
		cs_transform.SetRotation(Rotation);
		FCompactPoseBoneIndex ParentIndex = BoneContainer.MakeCompactPoseIndex(
			FMeshPoseBoneIndex(BoneContainer.GetParentBoneIndex(bone_index)));
		if (ParentIndex != INDEX_NONE)	
		{
			const FTransform& ParentTM = Pose.GetComponentSpaceTransform(ParentIndex);
			FTransform NewTransform = cs_transform * ParentTM;
			Pose.SetComponentSpaceTransform(cp_index, NewTransform);
		}
	}
}

FQuat FAnimNode_UdexrealHandPose::GetComponentSpaceRotation(const FName& BoneName, FCSPose<FCompactPose>& Pose)
{
	const FBoneContainer BoneContainer = Pose.GetPose().GetBoneContainer();

	const int32 bone_index = BoneContainer.GetPoseBoneIndexForBoneName(BoneName);

	if (bone_index > INDEX_NONE) 
	{
		const FCompactPoseBoneIndex cp_index = BoneContainer.MakeCompactPoseIndex(FMeshPoseBoneIndex(bone_index));
		const FTransform cs_transform = Pose.GetLocalSpaceTransform(cp_index);
		const FQuat rotation = cs_transform.GetRotation();
		return rotation;
	}
	return FQuat::Identity;
}
