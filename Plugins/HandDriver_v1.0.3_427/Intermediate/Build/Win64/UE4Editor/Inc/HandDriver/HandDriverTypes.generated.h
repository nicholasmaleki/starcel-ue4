// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef HANDDRIVER_HandDriverTypes_generated_h
#error "HandDriverTypes.generated.h already included, missing '#pragma once' in HandDriverTypes.h"
#endif
#define HANDDRIVER_HandDriverTypes_generated_h

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Starcel9_Plugins_HandDriver_v1_0_3_427_Source_HandDriver_Private_HandDriverTypes_h


#define FOREACH_ENUM_EHANDJOINT(op) \
	op(EHandJoint::Wrist) \
	op(EHandJoint::Thumb_1) \
	op(EHandJoint::Thumb_2) \
	op(EHandJoint::Thumb_3) \
	op(EHandJoint::Index_1) \
	op(EHandJoint::Index_2) \
	op(EHandJoint::Index_3) \
	op(EHandJoint::Middle_1) \
	op(EHandJoint::Middle_2) \
	op(EHandJoint::Middle_3) \
	op(EHandJoint::Ring_1) \
	op(EHandJoint::Ring_2) \
	op(EHandJoint::Ring_3) \
	op(EHandJoint::Pinky_1) \
	op(EHandJoint::Pinky_2) \
	op(EHandJoint::Pinky_3) 

enum class EHandJoint : uint8;
template<> HANDDRIVER_API UEnum* StaticEnum<EHandJoint>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
