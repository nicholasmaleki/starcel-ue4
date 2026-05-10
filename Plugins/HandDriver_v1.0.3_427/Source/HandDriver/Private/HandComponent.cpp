#include "HandComponent.h"

UHandComponent::UHandComponent()
{
	
	L_Angles = TArray<float>();
	R_Angles = TArray<float>();

	for (int i = 0; i < 27; i++)
	{
		L_Angles.Add(0);
	}
	for (int i = 0; i < 27; i++)
	{
		R_Angles.Add(0);
	}

	if (L_BoneNameMappings.Num() <= 0)
	{
		for (int8 BoneIndex = 0; BoneIndex < EHandJointCount; BoneIndex++)
		{
			L_BoneNameMappings.Add(static_cast<EHandJoint>(BoneIndex), TEXT(""));
		}
	}
	if (R_BoneNameMappings.Num() <= 0)
	{
		for (int8 BoneIndex = 0; BoneIndex < EHandJointCount; BoneIndex++)
		{
			R_BoneNameMappings.Add(static_cast<EHandJoint>(BoneIndex), TEXT(""));
		}
	}
}


void UHandComponent::BeginPlay()
{

	Super::BeginPlay();
}

void UHandComponent::EndPlay(const EEndPlayReason::Type EEndPlayReason)
{
	Super::EndPlay(EEndPlayReason);
}



void UHandComponent::Init()
{
	//UE_LOG(LogTemp, Warning, TEXT("Init"));
}