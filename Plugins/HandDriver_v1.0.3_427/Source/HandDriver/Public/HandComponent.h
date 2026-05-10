#pragma once

#include "CoreMinimal.h"
#include "HandDriver/Private/HandDriverTypes.h"
#include "HandComponent.generated.h"


UENUM(BlueprintType)
enum class EHandAxis : uint8
{
	X,
	Y,
	Z,
	negative_X UMETA(DisplayName = "-X"),
	negative_Y UMETA(DisplayName = "-Y"),
	negative_Z UMETA(DisplayName = "-Z"),
	
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HANDDRIVER_API UHandComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHandComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EEndPlayReason)override;

public:


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "L_Data")
		float L_CalibrationStatus = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_Data")
		float R_CalibrationStatus = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "L_Data")
		TArray<float> L_Angles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_Data")
		TArray<float> R_Angles;

	
	
	UPROPERTY(EditAnywhere, Category = "LeftHand_Map")
		TMap<EHandJoint, FName> L_BoneNameMappings;

	

	////////
	UPROPERTY(EditAnywhere,Category = "LeftHand_Map")
		EHandAxis L_Pitch_Axis;
	UPROPERTY(EditAnywhere, Category = "LeftHand_Map")
		EHandAxis L_Yaw_Axis;
	UPROPERTY(EditAnywhere, Category = "LeftHand_Map")
		EHandAxis L_Roll_Axis;

	
	UPROPERTY(EditAnywhere, Category = "LeftHand_Map|Thumb Offset")
	float L_Thumb_Coefficient;
	UPROPERTY(EditAnywhere, Category = "LeftHand_Map|Thumb Offset")
	float L_Thumb_Yaw_Offset;
	UPROPERTY(EditAnywhere, Category = "LeftHand_Map|Thumb Offset")
	float L_Thumb_Pitch_Offset;
	UPROPERTY(EditAnywhere, Category = "LeftHand_Map|Thumb Offset")
	float L_Thumb_Roll_Offset;
	/////
	UPROPERTY(EditAnywhere,DisplayName="Adjustment for Thumb Axis",Category = "LeftHand_Map|Thumb Axis")
	bool bUseThumbAxis_L;;	
	UPROPERTY(EditAnywhere, DisplayName="Thumb Pitch Axis",Category = "LeftHand_Map|Thumb Axis")
	EHandAxis L_Thumb_Pitch_Axis;
	UPROPERTY(EditAnywhere, DisplayName="Thumb Yaw Axis",Category = "LeftHand_Map|Thumb Axis")
	EHandAxis L_Thumb_Yaw_Axis;
	UPROPERTY(EditAnywhere, DisplayName="Thumb Roll Axis",Category = "LeftHand_Map|Thumb Axis")
	EHandAxis L_Thumb_Roll_Axis;
	/////
	UPROPERTY()
	float L_Finger_Offsets[4];
	UPROPERTY(EditAnywhere, Category = "LeftHand_Map|Other Fingers Yaw Offsets")
	float L_Index;
	UPROPERTY(EditAnywhere, Category = "LeftHand_Map|Other Fingers Yaw Offsets")
	float L_Middle;
	UPROPERTY(EditAnywhere, Category = "LeftHand_Map|Other Fingers Yaw Offsets")
	float L_Ring;
	UPROPERTY(EditAnywhere, Category = "LeftHand_Map|Other Fingers Yaw Offsets")
	float L_Pinky;
	////
	UPROPERTY(EditAnywhere, BlueprintReadOnly,DisplayName="StraightenFinger",Category="LeftHand_Map|Overall Fingers Adjust" )
	bool L_Straighten ;
	UPROPERTY(EditAnywhere, Category = "LeftHand_Map|Overall Fingers Adjust")
	float L_Finger_Pitch_Offset;
	UPROPERTY(EditAnywhere, Category = "LeftHand_Map|Overall Fingers Adjust")
	float L_Finger_Coefficient;



	//////////////////////////////////下面是right
	UPROPERTY(EditAnywhere, Category = "RightHand_Map")
	TMap<EHandJoint, FName> R_BoneNameMappings;
	
	UPROPERTY(EditAnywhere, Category = "RightHand_Map")
	EHandAxis R_Pitch_Axis;
	UPROPERTY(EditAnywhere, Category = "RightHand_Map")
	EHandAxis R_Yaw_Axis;
	UPROPERTY(EditAnywhere, Category = "RightHand_Map")
	EHandAxis R_Roll_Axis;
	////

	UPROPERTY(EditAnywhere, Category = "RightHand_Map|Thumb Offset")
	float R_Thumb_Coefficient;
	UPROPERTY(EditAnywhere, Category = "RightHand_Map|Thumb Offset")
	float R_Thumb_Yaw_Offset;
	UPROPERTY(EditAnywhere, Category = "RightHand_Map|Thumb Offset")
	float R_Thumb_Pitch_Offset;
	UPROPERTY(EditAnywhere, Category = "RightHand_Map|Thumb Offset")
	float R_Thumb_Roll_Offset;
	////
	
	
	UPROPERTY(EditAnywhere,DisplayName="Adjustment for Thumb Axis",Category = "RightHand_Map|Thumb Axis")
	bool bUseThumbAxis_R;;	
	UPROPERTY(EditAnywhere, DisplayName="Thumb Pitch Axis",Category = "RightHand_Map|Thumb Axis")
	EHandAxis R_Thumb_Pitch_Axis;
	UPROPERTY(EditAnywhere, DisplayName="Thumb Yaw Axis",Category = "RightHand_Map|Thumb Axis")
	EHandAxis R_Thumb_Yaw_Axis;
	UPROPERTY(EditAnywhere, DisplayName="Thumb Roll Axis",Category = "RightHand_Map|Thumb Axis")
	EHandAxis R_Thumb_Roll_Axis;
	////

	UPROPERTY()
	float R_Finger_Offsets[4];
	UPROPERTY(EditAnywhere, Category = "RightHand_Map|Other Fingers Yaw Offsets")
	float R_Index;
	UPROPERTY(EditAnywhere, Category = "RightHand_Map|Other Fingers Yaw Offsets")
	float R_Middle;
	UPROPERTY(EditAnywhere, Category = "RightHand_Map|Other Fingers Yaw Offsets")
	float R_Ring;
	UPROPERTY(EditAnywhere, Category = "RightHand_Map|Other Fingers Yaw Offsets")
	float R_Pinky;
	/////////

	UPROPERTY(EditAnywhere, DisplayName="EnableChanges",Category = "RightHand_Map|Overall Fingers Adjust")
	bool R_Straighten;
	
	UPROPERTY(EditAnywhere, Category = "RightHand_Map|Overall Fingers Adjust")
	float R_Finger_Pitch_Offset;
	UPROPERTY(EditAnywhere, Category = "RightHand_Map|Overall Fingers Adjust")
	float R_Finger_Coefficient;

	
	

	void Init();

	

};

