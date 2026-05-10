// Fill out your copyright notice in the Description page of Project Settings.


#include "HandDriverController.h"
#include "Roles/LiveLinkAnimationRole.h"
#include "Components/PoseableMeshComponent.h"
#include "HandComMeshComponent.h"


#if WITH_EDITOR
#include "Framework/Notifications/NotificationManager.h"
#include <Widgets/Notifications/SNotificationList.h>

#endif
#include <UObject/EnterpriseObjectVersion.h>

#include "HandComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHandDriver, Log, All);

#define LOCTEXT_NAMESPACE "HandDriverController"

void FHandDriverControllerData::ApplyTransform(USceneComponent* SceneComponent, const FTransform& Transform,
                                               const FLiveLinkSkeletonStaticData& StaticData) const
{
	if (SceneComponent)
	{
		if (bUseRotation)
		{
			if (bWorldTransform)
			{
				SceneComponent->SetWorldRotation(Transform.GetRotation(), bSweep, nullptr,
				                                 bTeleport
					                                 ? ETeleportType::TeleportPhysics
					                                 : ETeleportType::ResetPhysics);
			}
			else
			{
				SceneComponent->SetRelativeRotation(Transform.GetRotation(), bSweep, nullptr,
				                                    bTeleport
					                                    ? ETeleportType::TeleportPhysics
					                                    : ETeleportType::ResetPhysics);
			}
		}
	}
}

void FHandDriverControllerData::CheckForError(FName OwnerName, USceneComponent* SceneComponent) const
{
	if (SceneComponent == nullptr)
	{
		UE_LOG(LogHandDriver, Warning, TEXT("The component to control is invalid for '%s'."), *OwnerName.ToString());
#if WITH_EDITOR
		FNotificationInfo NotificationInfo(LOCTEXT("InvalidComponent", "The component to control is invalid."));
		NotificationInfo.ExpireDuration = 2.0f;
		FSlateNotificationManager::Get().AddNotification(NotificationInfo);
#endif
	}
	else if (SceneComponent->Mobility != EComponentMobility::Movable)
	{
		UE_LOG(LogHandDriver, Warning, TEXT("The component '%s' has an invalid mobility."), *OwnerName.ToString());
#if WITH_EDITOR
		FNotificationInfo NotificationInfo(
			FText::Format(LOCTEXT("InvalidMobility", "'{0}' has an invalid mobility"), FText::FromName(OwnerName)));
		NotificationInfo.ExpireDuration = 2.0f;
		FSlateNotificationManager::Get().AddNotification(NotificationInfo);
#endif
	}
}

void UHandDriverController::OnEvaluateRegistered()
{
	AActor* OuterActor = GetOuterActor();
	HandDriverData.CheckForError(OuterActor ? OuterActor->GetFName() : NAME_None,
	                             Cast<USceneComponent>(AttachedComponent));
}

void UHandDriverController::Tick(float DeltaTime, const FLiveLinkSubjectFrameData& SubjectData)
{
	if (SubjectData.StaticData.IsValid() && SubjectData.FrameData.IsValid())
	{
		const FLiveLinkSkeletonStaticData* StaticData = SubjectData.StaticData.Cast<FLiveLinkSkeletonStaticData>();
		const FLiveLinkAnimationFrameData* FrameData = SubjectData.FrameData.Cast<FLiveLinkAnimationFrameData>();
		if (StaticData && FrameData)
		{
			if (HandDriverData.bUseHandDriver)
			{
				UActorComponent* ac =  GetOuterActor()->GetComponentByClass(UHandComponent::StaticClass());
				UHandComponent* hand_comp = dynamic_cast<UHandComponent*>(ac);

				StaticData->FindPropertyValue(*FrameData, TEXT("L_CalibrationStatus"), hand_comp->L_CalibrationStatus);
				StaticData->FindPropertyValue(*FrameData, TEXT("R_CalibrationStatus"), hand_comp->R_CalibrationStatus);
				for (int i = 0; i < 27; i++)
				{
					float angle = 0;
					FString name = FString::Printf(TEXT("l%d"), i);
					StaticData->FindPropertyValue(*FrameData, FName(*name), angle);
					hand_comp->L_Angles[i] = angle;
				}
				for (int i = 0; i < 27; i++)
				{
					float angle = 0;
					FString name = FString::Printf(TEXT("r%d"), i);
					StaticData->FindPropertyValue(*FrameData, FName(*name), angle);
					hand_comp->R_Angles[i] = angle;
				}
				// handComMeshComponent->Init();
				// handComMeshComponent->ResetBonePose();
				//
				// //handComMeshComponent->UpdateWristRotate(handComMeshComponent->BoneNameMappings[EHandJoint::Wrist],FQuat(HandDriverData.bAngles[22], HandDriverData.bAngles[23], HandDriverData.bAngles[24], HandDriverData.bAngles[21]));
				//
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->L_BoneNameMappings[EHandJoint::Thumb_3], HandDriverData.L_Angles[0], -2);
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->L_BoneNameMappings[EHandJoint::Thumb_2], HandDriverData.L_Angles[1], -2);
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->L_BoneNameMappings[EHandJoint::Thumb_1], -HandDriverData.L_Angles[3], HandDriverData.L_Angles[2],-HandDriverData.L_Angles[20], 1,-2);
				//
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->L_BoneNameMappings[EHandJoint::Index_3], HandDriverData.L_Angles[4], -2);
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->L_BoneNameMappings[EHandJoint::Index_2], HandDriverData.L_Angles[5], -2);
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->L_BoneNameMappings[EHandJoint::Index_1], HandDriverData.L_Angles[6], HandDriverData.L_Angles[7], HandDriverData.L_Angles[21], 1, -3);
				//
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->L_BoneNameMappings[EHandJoint::Middle_3], HandDriverData.L_Angles[8], -2);
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->L_BoneNameMappings[EHandJoint::Middle_2], HandDriverData.L_Angles[9], -2);
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->L_BoneNameMappings[EHandJoint::Middle_1], HandDriverData.L_Angles[10], HandDriverData.L_Angles[11], 1, -3);
				//
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->L_BoneNameMappings[EHandJoint::Ring_3], HandDriverData.L_Angles[12], -2);
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->L_BoneNameMappings[EHandJoint::Ring_2], HandDriverData.L_Angles[13], -2);
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->L_BoneNameMappings[EHandJoint::Ring_1], HandDriverData.L_Angles[14], -HandDriverData.L_Angles[15], 1, -3);
				//
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->L_BoneNameMappings[EHandJoint::Pinky_3], HandDriverData.L_Angles[16], -2);
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->L_BoneNameMappings[EHandJoint::Pinky_2], HandDriverData.L_Angles[17], -2);
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->L_BoneNameMappings[EHandJoint::Pinky_1], HandDriverData.L_Angles[18], -HandDriverData.L_Angles[19], -HandDriverData.L_Angles[22], 1, -3);
				//
				//
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->R_BoneNameMappings[EHandJoint::Thumb_3], HandDriverData.R_Angles[0], -2);
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->R_BoneNameMappings[EHandJoint::Thumb_2], HandDriverData.R_Angles[1], -2);
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->R_BoneNameMappings[EHandJoint::Thumb_1], -HandDriverData.R_Angles[3], HandDriverData.R_Angles[2],-HandDriverData.R_Angles[20], 1,-2);
				//
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->R_BoneNameMappings[EHandJoint::Index_3], HandDriverData.R_Angles[4], -2);
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->R_BoneNameMappings[EHandJoint::Index_2], HandDriverData.R_Angles[5], -2);
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->R_BoneNameMappings[EHandJoint::Index_1], HandDriverData.R_Angles[6], HandDriverData.R_Angles[7], HandDriverData.R_Angles[21], 1, -3);
				//
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->R_BoneNameMappings[EHandJoint::Middle_3], HandDriverData.R_Angles[8], -2);
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->R_BoneNameMappings[EHandJoint::Middle_2], HandDriverData.R_Angles[9], -2);
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->R_BoneNameMappings[EHandJoint::Middle_1], HandDriverData.R_Angles[10], HandDriverData.R_Angles[11], 1, -3);
				//
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->R_BoneNameMappings[EHandJoint::Ring_3], HandDriverData.R_Angles[12], -2);
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->R_BoneNameMappings[EHandJoint::Ring_2], HandDriverData.R_Angles[13], -2);
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->R_BoneNameMappings[EHandJoint::Ring_1], HandDriverData.R_Angles[14], -HandDriverData.R_Angles[15], 1, -3);
				//
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->R_BoneNameMappings[EHandJoint::Pinky_3], HandDriverData.R_Angles[16], -2);
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->R_BoneNameMappings[EHandJoint::Pinky_2], HandDriverData.R_Angles[17], -2);
				// handComMeshComponent->UpdateBonePose(handComMeshComponent->R_BoneNameMappings[EHandJoint::Pinky_1], HandDriverData.R_Angles[18], -HandDriverData.R_Angles[19], -HandDriverData.R_Angles[22], 1, -3);
			}
		}
	}
}

bool UHandDriverController::IsRoleSupported(const TSubclassOf<ULiveLinkRole>& RoleToSupport)
{
	return RoleToSupport == ULiveLinkAnimationRole::StaticClass();
}

TSubclassOf<UActorComponent> UHandDriverController::GetDesiredComponentClass() const
{
	return USceneComponent::StaticClass();
}

void UHandDriverController::SetAttachedComponent(UActorComponent* ActorComponent)
{
	Super::SetAttachedComponent(ActorComponent);
	AActor* OuterActor = GetOuterActor();
	HandDriverData.CheckForError(OuterActor ? OuterActor->GetFName() : NAME_None,
	                             Cast<USceneComponent>(AttachedComponent));
}

void UHandDriverController::PostLoad()
{
	Super::PostLoad();
#if WITH_EDITOR
	const int32 Version = GetLinkerCustomVersion(FEnterpriseObjectVersion::GUID);
	if (Version < FEnterpriseObjectVersion::LiveLinkControllerSplitPerRole)
	{
		AActor* MyActor = GetOuterActor();
		if (MyActor)
		{
			MyActor->ConditionalPostLoad();
		}
	}

#endif //WITH_EDITOR
}
#undef LOCTEXT_NAMESPACE
