// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"



/**
 * 
 */

UENUM(BlueprintType)
enum class EHandJoint : uint8
{
	Wrist,
	Thumb_1,
	Thumb_2,
	Thumb_3,
	Index_1,
	Index_2,
	Index_3,
	Middle_1,
	Middle_2,
	Middle_3,
	Ring_1,
	Ring_2,
	Ring_3,
	Pinky_1,
	Pinky_2,
	Pinky_3,
	
};

constexpr int32 EHandJointCount = static_cast<int32>(EHandJoint::Pinky_3) + 1;


class HandDriverTypes
{
public:
	HandDriverTypes();
	~HandDriverTypes();
};
