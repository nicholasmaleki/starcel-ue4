#include "AnimNode_BlendHandMoCap.h"
#include "HandComponent.h"
#include "HandDriverTypes.h"
#include "Animation/AnimInstanceProxy.h"

FAnimNode_BlendHandMocap::FAnimNode_BlendHandMocap()
{
}

void FAnimNode_BlendHandMocap::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	FAnimNode_Base::Initialize_AnyThread(Context);

	Hand.Initialize(Context);
	MoCap.Initialize(Context);
	UAnimInstance* anim = Context.AnimInstanceProxy->GetSkelMeshComponent()->GetAnimInstance();
	if (anim == nullptr || anim->GetOwningActor() == nullptr)
	{
		return;
	}
	UActorComponent* controller_comp = anim->GetOwningActor()->GetComponentByClass(UHandComponent::StaticClass());
	UHandComponent* handComponent = dynamic_cast<UHandComponent*>(controller_comp);
	if (handComponent == nullptr)
	{
		return;
	}
	HandComponent = handComponent;
}


void FAnimNode_BlendHandMocap::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	Hand.CacheBones(Context);
	MoCap.CacheBones(Context);
}

void FAnimNode_BlendHandMocap::Update_AnyThread(const FAnimationUpdateContext& Context)
{
	Hand.Update(Context);
	MoCap.Update(Context);
	GetEvaluateGraphExposedInputs().Execute(Context);

	if (HandComponent == nullptr)
	{
		UAnimInstance* anim = Context.AnimInstanceProxy->GetSkelMeshComponent()->GetAnimInstance();
		if (anim == nullptr || anim->GetOwningActor() == nullptr)
		{
			return;
		}
		UActorComponent* controller_comp = anim->GetOwningActor()->GetComponentByClass(UHandComponent::StaticClass());
		UHandComponent* handComponent = dynamic_cast<UHandComponent*>(controller_comp);
		if (handComponent == nullptr)
		{
			return;
		}
		HandComponent = handComponent;
	}
}

void FAnimNode_BlendHandMocap::Evaluate_AnyThread(FPoseContext& Output)
{
	MoCap.Evaluate(Output);

	if (HandComponent == nullptr) return;
	if (HandComponent->L_CalibrationStatus != 3 && HandComponent->R_CalibrationStatus != 3)
	{
		return;
	}
	FCSPose<FCompactPose> FinalPose;
	FinalPose.InitPose(&Output.Pose.GetBoneContainer());
	const FBoneContainer Container = FinalPose.GetPose().GetBoneContainer();

	FPoseContext HandContext(Output);
	Hand.Evaluate(HandContext);

	TArray<int32> handBoneIndex;
	if (HandComponent->L_BoneNameMappings.Num()<16)
	{
		return;
	}
	int32 l_thumb3_index = Container.GetPoseBoneIndexForBoneName(HandComponent->L_BoneNameMappings[EHandJoint::Thumb_3]);
	int32 l_thumb2_index = Container.GetPoseBoneIndexForBoneName(HandComponent->L_BoneNameMappings[EHandJoint::Thumb_2]);
	int32 l_thumb1_index = Container.GetPoseBoneIndexForBoneName(HandComponent->L_BoneNameMappings[EHandJoint::Thumb_1]);
	if (l_thumb3_index != INDEX_NONE && l_thumb2_index != INDEX_NONE && l_thumb1_index != INDEX_NONE)
	{
		handBoneIndex.Push(l_thumb3_index);
		handBoneIndex.Push(l_thumb2_index);
		handBoneIndex.Push(l_thumb1_index);
	}

	int32 l_index3_index = Container.GetPoseBoneIndexForBoneName(HandComponent->L_BoneNameMappings[EHandJoint::Index_3]);
	int32 l_index2_index = Container.GetPoseBoneIndexForBoneName(HandComponent->L_BoneNameMappings[EHandJoint::Index_2]);
	int32 l_index1_index = Container.GetPoseBoneIndexForBoneName(HandComponent->L_BoneNameMappings[EHandJoint::Index_1]);
	if (l_index3_index != INDEX_NONE && l_index2_index != INDEX_NONE && l_index1_index != INDEX_NONE)
	{
		handBoneIndex.Push(l_index3_index);
		handBoneIndex.Push(l_index2_index);
		handBoneIndex.Push(l_index1_index);
	}

	int32 l_middle3_index = Container.GetPoseBoneIndexForBoneName(HandComponent->L_BoneNameMappings[EHandJoint::Middle_3]);
	int32 l_middle2_index = Container.GetPoseBoneIndexForBoneName(HandComponent->L_BoneNameMappings[EHandJoint::Middle_2]);
	int32 l_middle1_index = Container.GetPoseBoneIndexForBoneName(HandComponent->L_BoneNameMappings[EHandJoint::Middle_1]);
	if (l_middle3_index != INDEX_NONE && l_middle2_index != INDEX_NONE && l_middle1_index != INDEX_NONE)
	{
		handBoneIndex.Push(l_middle3_index);
		handBoneIndex.Push(l_middle2_index);
		handBoneIndex.Push(l_middle1_index);
	}

	int32 l_ring3_index = Container.GetPoseBoneIndexForBoneName(HandComponent->L_BoneNameMappings[EHandJoint::Ring_3]);
	int32 l_ring2_index = Container.GetPoseBoneIndexForBoneName(HandComponent->L_BoneNameMappings[EHandJoint::Ring_2]);
	int32 l_ring1_index = Container.GetPoseBoneIndexForBoneName(HandComponent->L_BoneNameMappings[EHandJoint::Ring_1]);
	if (l_ring3_index != INDEX_NONE && l_ring2_index != INDEX_NONE && l_ring1_index != INDEX_NONE)
	{
		handBoneIndex.Push(l_ring3_index);
		handBoneIndex.Push(l_ring2_index);
		handBoneIndex.Push(l_ring1_index);
	}

	int32 l_pinky3_index = Container.GetPoseBoneIndexForBoneName(HandComponent->L_BoneNameMappings[EHandJoint::Pinky_3]);
	int32 l_pinky2_index = Container.GetPoseBoneIndexForBoneName(HandComponent->L_BoneNameMappings[EHandJoint::Pinky_2]);
	int32 l_pinky1_index = Container.GetPoseBoneIndexForBoneName(HandComponent->L_BoneNameMappings[EHandJoint::Pinky_1]);
	if (l_pinky3_index != INDEX_NONE && l_pinky2_index != INDEX_NONE && l_pinky1_index != INDEX_NONE)
	{
		handBoneIndex.Push(l_pinky3_index);
		handBoneIndex.Push(l_pinky2_index);
		handBoneIndex.Push(l_pinky1_index);
	}
	if (HandComponent->R_BoneNameMappings.Num() < 16)
	{
		return;
	}
	int32 r_thumb3_index = Container.GetPoseBoneIndexForBoneName(HandComponent->R_BoneNameMappings[EHandJoint::Thumb_3]);
	int32 r_thumb2_index = Container.GetPoseBoneIndexForBoneName(HandComponent->R_BoneNameMappings[EHandJoint::Thumb_2]);
	int32 r_thumb1_index = Container.GetPoseBoneIndexForBoneName(HandComponent->R_BoneNameMappings[EHandJoint::Thumb_1]);
	if (r_thumb3_index != INDEX_NONE && r_thumb2_index != INDEX_NONE && r_thumb1_index != INDEX_NONE)
	{
		handBoneIndex.Push(r_thumb3_index);
		handBoneIndex.Push(r_thumb2_index);
		handBoneIndex.Push(r_thumb1_index);
	}

	int32 r_index3_index = Container.GetPoseBoneIndexForBoneName(HandComponent->R_BoneNameMappings[EHandJoint::Index_3]);
	int32 r_index2_index = Container.GetPoseBoneIndexForBoneName(HandComponent->R_BoneNameMappings[EHandJoint::Index_2]);
	int32 r_index1_index = Container.GetPoseBoneIndexForBoneName(HandComponent->R_BoneNameMappings[EHandJoint::Index_1]);
	if (r_index3_index != INDEX_NONE && r_index2_index != INDEX_NONE && r_index1_index != INDEX_NONE)
	{
		handBoneIndex.Push(r_index3_index);
		handBoneIndex.Push(r_index2_index);
		handBoneIndex.Push(r_index1_index);
	}

	int32 r_middle3_index = Container.GetPoseBoneIndexForBoneName(HandComponent->R_BoneNameMappings[EHandJoint::Middle_3]);
	int32 r_middle2_index = Container.GetPoseBoneIndexForBoneName(HandComponent->R_BoneNameMappings[EHandJoint::Middle_2]);
	int32 r_middle1_index = Container.GetPoseBoneIndexForBoneName(HandComponent->R_BoneNameMappings[EHandJoint::Middle_1]);
	if (r_middle3_index != INDEX_NONE && r_middle2_index != INDEX_NONE && r_middle1_index != INDEX_NONE)
	{
		handBoneIndex.Push(r_middle3_index);
		handBoneIndex.Push(r_middle2_index);
		handBoneIndex.Push(r_middle1_index);
	}

	int32 r_ring3_index = Container.GetPoseBoneIndexForBoneName(HandComponent->R_BoneNameMappings[EHandJoint::Ring_3]);
	int32 r_ring2_index = Container.GetPoseBoneIndexForBoneName(HandComponent->R_BoneNameMappings[EHandJoint::Ring_2]);
	int32 r_ring1_index = Container.GetPoseBoneIndexForBoneName(HandComponent->R_BoneNameMappings[EHandJoint::Ring_1]);
	if (r_ring3_index != INDEX_NONE && r_ring2_index != INDEX_NONE && r_ring1_index != INDEX_NONE)
	{
		handBoneIndex.Push(r_ring3_index);
		handBoneIndex.Push(r_ring2_index);
		handBoneIndex.Push(r_ring1_index);
	}

	int32 r_pinky3_index = Container.GetPoseBoneIndexForBoneName(HandComponent->R_BoneNameMappings[EHandJoint::Pinky_3]);
	int32 r_pinky2_index = Container.GetPoseBoneIndexForBoneName(HandComponent->R_BoneNameMappings[EHandJoint::Pinky_2]);
	int32 r_pinky1_index = Container.GetPoseBoneIndexForBoneName(HandComponent->R_BoneNameMappings[EHandJoint::Pinky_1]);
	if (r_pinky3_index != INDEX_NONE && r_pinky2_index != INDEX_NONE && r_pinky1_index != INDEX_NONE)
	{
		handBoneIndex.Push(r_pinky3_index);
		handBoneIndex.Push(r_pinky2_index);
		handBoneIndex.Push(r_pinky1_index);
	}
	
	for (FCompactPoseBoneIndex BoneIndex : Output.Pose.ForEachBoneIndex())
	{
		if (handBoneIndex.Find(BoneIndex.GetInt()) != INDEX_NONE) {
			Output.Pose[BoneIndex] = HandContext.Pose[BoneIndex];
		}
	}

}

