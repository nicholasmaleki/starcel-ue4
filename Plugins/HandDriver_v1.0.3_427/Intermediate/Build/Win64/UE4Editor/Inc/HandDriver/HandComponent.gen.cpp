// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HandDriver/Public/HandComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHandComponent() {}
// Cross Module References
	HANDDRIVER_API UEnum* Z_Construct_UEnum_HandDriver_EHandAxis();
	UPackage* Z_Construct_UPackage__Script_HandDriver();
	HANDDRIVER_API UClass* Z_Construct_UClass_UHandComponent_NoRegister();
	HANDDRIVER_API UClass* Z_Construct_UClass_UHandComponent();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
	HANDDRIVER_API UEnum* Z_Construct_UEnum_HandDriver_EHandJoint();
// End Cross Module References
	static UEnum* EHandAxis_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_HandDriver_EHandAxis, Z_Construct_UPackage__Script_HandDriver(), TEXT("EHandAxis"));
		}
		return Singleton;
	}
	template<> HANDDRIVER_API UEnum* StaticEnum<EHandAxis>()
	{
		return EHandAxis_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EHandAxis(EHandAxis_StaticEnum, TEXT("/Script/HandDriver"), TEXT("EHandAxis"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_HandDriver_EHandAxis_Hash() { return 1508054114U; }
	UEnum* Z_Construct_UEnum_HandDriver_EHandAxis()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_HandDriver();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EHandAxis"), 0, Get_Z_Construct_UEnum_HandDriver_EHandAxis_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EHandAxis::X", (int64)EHandAxis::X },
				{ "EHandAxis::Y", (int64)EHandAxis::Y },
				{ "EHandAxis::Z", (int64)EHandAxis::Z },
				{ "EHandAxis::negative_X", (int64)EHandAxis::negative_X },
				{ "EHandAxis::negative_Y", (int64)EHandAxis::negative_Y },
				{ "EHandAxis::negative_Z", (int64)EHandAxis::negative_Z },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Public/HandComponent.h" },
				{ "negative_X.DisplayName", "-X" },
				{ "negative_X.Name", "EHandAxis::negative_X" },
				{ "negative_Y.DisplayName", "-Y" },
				{ "negative_Y.Name", "EHandAxis::negative_Y" },
				{ "negative_Z.DisplayName", "-Z" },
				{ "negative_Z.Name", "EHandAxis::negative_Z" },
				{ "X.Name", "EHandAxis::X" },
				{ "Y.Name", "EHandAxis::Y" },
				{ "Z.Name", "EHandAxis::Z" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_HandDriver,
				nullptr,
				"EHandAxis",
				"EHandAxis",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	void UHandComponent::StaticRegisterNativesUHandComponent()
	{
	}
	UClass* Z_Construct_UClass_UHandComponent_NoRegister()
	{
		return UHandComponent::StaticClass();
	}
	struct Z_Construct_UClass_UHandComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_L_CalibrationStatus_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_L_CalibrationStatus;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_R_CalibrationStatus_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_R_CalibrationStatus;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_L_Angles_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_L_Angles_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_L_Angles;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_R_Angles_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_R_Angles_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_R_Angles;
		static const UE4CodeGen_Private::FNamePropertyParams NewProp_L_BoneNameMappings_ValueProp;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_L_BoneNameMappings_Key_KeyProp_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_L_BoneNameMappings_Key_KeyProp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_L_BoneNameMappings_MetaData[];
#endif
		static const UE4CodeGen_Private::FMapPropertyParams NewProp_L_BoneNameMappings;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_L_Pitch_Axis_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_L_Pitch_Axis_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_L_Pitch_Axis;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_L_Yaw_Axis_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_L_Yaw_Axis_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_L_Yaw_Axis;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_L_Roll_Axis_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_L_Roll_Axis_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_L_Roll_Axis;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_L_Thumb_Coefficient_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_L_Thumb_Coefficient;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_L_Thumb_Yaw_Offset_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_L_Thumb_Yaw_Offset;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_L_Thumb_Pitch_Offset_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_L_Thumb_Pitch_Offset;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_L_Thumb_Roll_Offset_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_L_Thumb_Roll_Offset;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bUseThumbAxis_L_MetaData[];
#endif
		static void NewProp_bUseThumbAxis_L_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bUseThumbAxis_L;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_L_Thumb_Pitch_Axis_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_L_Thumb_Pitch_Axis_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_L_Thumb_Pitch_Axis;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_L_Thumb_Yaw_Axis_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_L_Thumb_Yaw_Axis_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_L_Thumb_Yaw_Axis;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_L_Thumb_Roll_Axis_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_L_Thumb_Roll_Axis_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_L_Thumb_Roll_Axis;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_L_Finger_Offsets_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_L_Finger_Offsets;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_L_Index_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_L_Index;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_L_Middle_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_L_Middle;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_L_Ring_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_L_Ring;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_L_Pinky_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_L_Pinky;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_L_Straighten_MetaData[];
#endif
		static void NewProp_L_Straighten_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_L_Straighten;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_L_Finger_Pitch_Offset_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_L_Finger_Pitch_Offset;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_L_Finger_Coefficient_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_L_Finger_Coefficient;
		static const UE4CodeGen_Private::FNamePropertyParams NewProp_R_BoneNameMappings_ValueProp;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_R_BoneNameMappings_Key_KeyProp_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_R_BoneNameMappings_Key_KeyProp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_R_BoneNameMappings_MetaData[];
#endif
		static const UE4CodeGen_Private::FMapPropertyParams NewProp_R_BoneNameMappings;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_R_Pitch_Axis_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_R_Pitch_Axis_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_R_Pitch_Axis;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_R_Yaw_Axis_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_R_Yaw_Axis_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_R_Yaw_Axis;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_R_Roll_Axis_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_R_Roll_Axis_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_R_Roll_Axis;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_R_Thumb_Coefficient_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_R_Thumb_Coefficient;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_R_Thumb_Yaw_Offset_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_R_Thumb_Yaw_Offset;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_R_Thumb_Pitch_Offset_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_R_Thumb_Pitch_Offset;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_R_Thumb_Roll_Offset_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_R_Thumb_Roll_Offset;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bUseThumbAxis_R_MetaData[];
#endif
		static void NewProp_bUseThumbAxis_R_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bUseThumbAxis_R;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_R_Thumb_Pitch_Axis_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_R_Thumb_Pitch_Axis_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_R_Thumb_Pitch_Axis;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_R_Thumb_Yaw_Axis_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_R_Thumb_Yaw_Axis_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_R_Thumb_Yaw_Axis;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_R_Thumb_Roll_Axis_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_R_Thumb_Roll_Axis_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_R_Thumb_Roll_Axis;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_R_Finger_Offsets_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_R_Finger_Offsets;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_R_Index_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_R_Index;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_R_Middle_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_R_Middle;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_R_Ring_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_R_Ring;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_R_Pinky_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_R_Pinky;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_R_Straighten_MetaData[];
#endif
		static void NewProp_R_Straighten_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_R_Straighten;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_R_Finger_Pitch_Offset_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_R_Finger_Pitch_Offset;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_R_Finger_Coefficient_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_R_Finger_Coefficient;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UHandComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USceneComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_HandDriver,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "HandComponent.h" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_L_CalibrationStatus_MetaData[] = {
		{ "Category", "L_Data" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_CalibrationStatus = { "L_CalibrationStatus", nullptr, (EPropertyFlags)0x0010000000000015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, L_CalibrationStatus), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_CalibrationStatus_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_CalibrationStatus_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_R_CalibrationStatus_MetaData[] = {
		{ "Category", "R_Data" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_CalibrationStatus = { "R_CalibrationStatus", nullptr, (EPropertyFlags)0x0010000000000015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, R_CalibrationStatus), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_CalibrationStatus_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_CalibrationStatus_MetaData)) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Angles_Inner = { "L_Angles", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Angles_MetaData[] = {
		{ "Category", "L_Data" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Angles = { "L_Angles", nullptr, (EPropertyFlags)0x0010000000000015, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, L_Angles), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Angles_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Angles_MetaData)) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Angles_Inner = { "R_Angles", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Angles_MetaData[] = {
		{ "Category", "R_Data" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Angles = { "R_Angles", nullptr, (EPropertyFlags)0x0010000000000015, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, R_Angles), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Angles_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Angles_MetaData)) };
	const UE4CodeGen_Private::FNamePropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_BoneNameMappings_ValueProp = { "L_BoneNameMappings", nullptr, (EPropertyFlags)0x0000000000000001, UE4CodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_BoneNameMappings_Key_KeyProp_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_BoneNameMappings_Key_KeyProp = { "L_BoneNameMappings_Key", nullptr, (EPropertyFlags)0x0000000000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UEnum_HandDriver_EHandJoint, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_L_BoneNameMappings_MetaData[] = {
		{ "Category", "LeftHand_Map" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FMapPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_BoneNameMappings = { "L_BoneNameMappings", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, L_BoneNameMappings), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_BoneNameMappings_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_BoneNameMappings_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Pitch_Axis_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Pitch_Axis_MetaData[] = {
		{ "Category", "LeftHand_Map" },
		{ "Comment", "////////\n" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Pitch_Axis = { "L_Pitch_Axis", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, L_Pitch_Axis), Z_Construct_UEnum_HandDriver_EHandAxis, METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Pitch_Axis_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Pitch_Axis_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Yaw_Axis_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Yaw_Axis_MetaData[] = {
		{ "Category", "LeftHand_Map" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Yaw_Axis = { "L_Yaw_Axis", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, L_Yaw_Axis), Z_Construct_UEnum_HandDriver_EHandAxis, METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Yaw_Axis_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Yaw_Axis_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Roll_Axis_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Roll_Axis_MetaData[] = {
		{ "Category", "LeftHand_Map" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Roll_Axis = { "L_Roll_Axis", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, L_Roll_Axis), Z_Construct_UEnum_HandDriver_EHandAxis, METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Roll_Axis_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Roll_Axis_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Coefficient_MetaData[] = {
		{ "Category", "LeftHand_Map|Thumb Offset" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Coefficient = { "L_Thumb_Coefficient", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, L_Thumb_Coefficient), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Coefficient_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Coefficient_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Yaw_Offset_MetaData[] = {
		{ "Category", "LeftHand_Map|Thumb Offset" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Yaw_Offset = { "L_Thumb_Yaw_Offset", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, L_Thumb_Yaw_Offset), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Yaw_Offset_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Yaw_Offset_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Pitch_Offset_MetaData[] = {
		{ "Category", "LeftHand_Map|Thumb Offset" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Pitch_Offset = { "L_Thumb_Pitch_Offset", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, L_Thumb_Pitch_Offset), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Pitch_Offset_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Pitch_Offset_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Roll_Offset_MetaData[] = {
		{ "Category", "LeftHand_Map|Thumb Offset" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Roll_Offset = { "L_Thumb_Roll_Offset", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, L_Thumb_Roll_Offset), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Roll_Offset_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Roll_Offset_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_bUseThumbAxis_L_MetaData[] = {
		{ "Category", "LeftHand_Map|Thumb Axis" },
		{ "Comment", "/////\n" },
		{ "DisplayName", "Adjustment for Thumb Axis" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	void Z_Construct_UClass_UHandComponent_Statics::NewProp_bUseThumbAxis_L_SetBit(void* Obj)
	{
		((UHandComponent*)Obj)->bUseThumbAxis_L = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_bUseThumbAxis_L = { "bUseThumbAxis_L", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UHandComponent), &Z_Construct_UClass_UHandComponent_Statics::NewProp_bUseThumbAxis_L_SetBit, METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_bUseThumbAxis_L_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_bUseThumbAxis_L_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Pitch_Axis_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Pitch_Axis_MetaData[] = {
		{ "Category", "LeftHand_Map|Thumb Axis" },
		{ "DisplayName", "Thumb Pitch Axis" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Pitch_Axis = { "L_Thumb_Pitch_Axis", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, L_Thumb_Pitch_Axis), Z_Construct_UEnum_HandDriver_EHandAxis, METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Pitch_Axis_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Pitch_Axis_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Yaw_Axis_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Yaw_Axis_MetaData[] = {
		{ "Category", "LeftHand_Map|Thumb Axis" },
		{ "DisplayName", "Thumb Yaw Axis" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Yaw_Axis = { "L_Thumb_Yaw_Axis", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, L_Thumb_Yaw_Axis), Z_Construct_UEnum_HandDriver_EHandAxis, METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Yaw_Axis_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Yaw_Axis_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Roll_Axis_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Roll_Axis_MetaData[] = {
		{ "Category", "LeftHand_Map|Thumb Axis" },
		{ "DisplayName", "Thumb Roll Axis" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Roll_Axis = { "L_Thumb_Roll_Axis", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, L_Thumb_Roll_Axis), Z_Construct_UEnum_HandDriver_EHandAxis, METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Roll_Axis_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Roll_Axis_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Finger_Offsets_MetaData[] = {
		{ "Comment", "/////\n" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Finger_Offsets = { "L_Finger_Offsets", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, CPP_ARRAY_DIM(L_Finger_Offsets, UHandComponent), STRUCT_OFFSET(UHandComponent, L_Finger_Offsets), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Finger_Offsets_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Finger_Offsets_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Index_MetaData[] = {
		{ "Category", "LeftHand_Map|Other Fingers Yaw Offsets" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Index = { "L_Index", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, L_Index), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Index_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Index_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Middle_MetaData[] = {
		{ "Category", "LeftHand_Map|Other Fingers Yaw Offsets" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Middle = { "L_Middle", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, L_Middle), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Middle_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Middle_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Ring_MetaData[] = {
		{ "Category", "LeftHand_Map|Other Fingers Yaw Offsets" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Ring = { "L_Ring", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, L_Ring), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Ring_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Ring_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Pinky_MetaData[] = {
		{ "Category", "LeftHand_Map|Other Fingers Yaw Offsets" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Pinky = { "L_Pinky", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, L_Pinky), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Pinky_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Pinky_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Straighten_MetaData[] = {
		{ "Category", "LeftHand_Map|Overall Fingers Adjust" },
		{ "Comment", "////\n" },
		{ "DisplayName", "StraightenFinger" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	void Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Straighten_SetBit(void* Obj)
	{
		((UHandComponent*)Obj)->L_Straighten = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Straighten = { "L_Straighten", nullptr, (EPropertyFlags)0x0010000000000015, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UHandComponent), &Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Straighten_SetBit, METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Straighten_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Straighten_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Finger_Pitch_Offset_MetaData[] = {
		{ "Category", "LeftHand_Map|Overall Fingers Adjust" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Finger_Pitch_Offset = { "L_Finger_Pitch_Offset", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, L_Finger_Pitch_Offset), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Finger_Pitch_Offset_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Finger_Pitch_Offset_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Finger_Coefficient_MetaData[] = {
		{ "Category", "LeftHand_Map|Overall Fingers Adjust" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Finger_Coefficient = { "L_Finger_Coefficient", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, L_Finger_Coefficient), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Finger_Coefficient_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Finger_Coefficient_MetaData)) };
	const UE4CodeGen_Private::FNamePropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_BoneNameMappings_ValueProp = { "R_BoneNameMappings", nullptr, (EPropertyFlags)0x0000000000000001, UE4CodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_BoneNameMappings_Key_KeyProp_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_BoneNameMappings_Key_KeyProp = { "R_BoneNameMappings_Key", nullptr, (EPropertyFlags)0x0000000000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UEnum_HandDriver_EHandJoint, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_R_BoneNameMappings_MetaData[] = {
		{ "Category", "RightHand_Map" },
		{ "Comment", "//////////////////////////////////\xe4\xb8\x8b\xe9\x9d\xa2\xe6\x98\xafright\n" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
		{ "ToolTip", "/\xe4\xb8\x8b\xe9\x9d\xa2\xe6\x98\xafright" },
	};
#endif
	const UE4CodeGen_Private::FMapPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_BoneNameMappings = { "R_BoneNameMappings", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, R_BoneNameMappings), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_BoneNameMappings_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_BoneNameMappings_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Pitch_Axis_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Pitch_Axis_MetaData[] = {
		{ "Category", "RightHand_Map" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Pitch_Axis = { "R_Pitch_Axis", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, R_Pitch_Axis), Z_Construct_UEnum_HandDriver_EHandAxis, METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Pitch_Axis_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Pitch_Axis_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Yaw_Axis_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Yaw_Axis_MetaData[] = {
		{ "Category", "RightHand_Map" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Yaw_Axis = { "R_Yaw_Axis", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, R_Yaw_Axis), Z_Construct_UEnum_HandDriver_EHandAxis, METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Yaw_Axis_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Yaw_Axis_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Roll_Axis_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Roll_Axis_MetaData[] = {
		{ "Category", "RightHand_Map" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Roll_Axis = { "R_Roll_Axis", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, R_Roll_Axis), Z_Construct_UEnum_HandDriver_EHandAxis, METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Roll_Axis_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Roll_Axis_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Coefficient_MetaData[] = {
		{ "Category", "RightHand_Map|Thumb Offset" },
		{ "Comment", "////\n" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Coefficient = { "R_Thumb_Coefficient", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, R_Thumb_Coefficient), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Coefficient_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Coefficient_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Yaw_Offset_MetaData[] = {
		{ "Category", "RightHand_Map|Thumb Offset" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Yaw_Offset = { "R_Thumb_Yaw_Offset", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, R_Thumb_Yaw_Offset), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Yaw_Offset_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Yaw_Offset_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Pitch_Offset_MetaData[] = {
		{ "Category", "RightHand_Map|Thumb Offset" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Pitch_Offset = { "R_Thumb_Pitch_Offset", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, R_Thumb_Pitch_Offset), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Pitch_Offset_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Pitch_Offset_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Roll_Offset_MetaData[] = {
		{ "Category", "RightHand_Map|Thumb Offset" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Roll_Offset = { "R_Thumb_Roll_Offset", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, R_Thumb_Roll_Offset), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Roll_Offset_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Roll_Offset_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_bUseThumbAxis_R_MetaData[] = {
		{ "Category", "RightHand_Map|Thumb Axis" },
		{ "Comment", "////\n" },
		{ "DisplayName", "Adjustment for Thumb Axis" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	void Z_Construct_UClass_UHandComponent_Statics::NewProp_bUseThumbAxis_R_SetBit(void* Obj)
	{
		((UHandComponent*)Obj)->bUseThumbAxis_R = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_bUseThumbAxis_R = { "bUseThumbAxis_R", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UHandComponent), &Z_Construct_UClass_UHandComponent_Statics::NewProp_bUseThumbAxis_R_SetBit, METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_bUseThumbAxis_R_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_bUseThumbAxis_R_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Pitch_Axis_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Pitch_Axis_MetaData[] = {
		{ "Category", "RightHand_Map|Thumb Axis" },
		{ "DisplayName", "Thumb Pitch Axis" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Pitch_Axis = { "R_Thumb_Pitch_Axis", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, R_Thumb_Pitch_Axis), Z_Construct_UEnum_HandDriver_EHandAxis, METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Pitch_Axis_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Pitch_Axis_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Yaw_Axis_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Yaw_Axis_MetaData[] = {
		{ "Category", "RightHand_Map|Thumb Axis" },
		{ "DisplayName", "Thumb Yaw Axis" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Yaw_Axis = { "R_Thumb_Yaw_Axis", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, R_Thumb_Yaw_Axis), Z_Construct_UEnum_HandDriver_EHandAxis, METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Yaw_Axis_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Yaw_Axis_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Roll_Axis_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Roll_Axis_MetaData[] = {
		{ "Category", "RightHand_Map|Thumb Axis" },
		{ "DisplayName", "Thumb Roll Axis" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Roll_Axis = { "R_Thumb_Roll_Axis", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, R_Thumb_Roll_Axis), Z_Construct_UEnum_HandDriver_EHandAxis, METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Roll_Axis_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Roll_Axis_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Finger_Offsets_MetaData[] = {
		{ "Comment", "////\n" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Finger_Offsets = { "R_Finger_Offsets", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, CPP_ARRAY_DIM(R_Finger_Offsets, UHandComponent), STRUCT_OFFSET(UHandComponent, R_Finger_Offsets), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Finger_Offsets_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Finger_Offsets_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Index_MetaData[] = {
		{ "Category", "RightHand_Map|Other Fingers Yaw Offsets" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Index = { "R_Index", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, R_Index), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Index_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Index_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Middle_MetaData[] = {
		{ "Category", "RightHand_Map|Other Fingers Yaw Offsets" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Middle = { "R_Middle", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, R_Middle), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Middle_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Middle_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Ring_MetaData[] = {
		{ "Category", "RightHand_Map|Other Fingers Yaw Offsets" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Ring = { "R_Ring", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, R_Ring), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Ring_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Ring_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Pinky_MetaData[] = {
		{ "Category", "RightHand_Map|Other Fingers Yaw Offsets" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Pinky = { "R_Pinky", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, R_Pinky), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Pinky_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Pinky_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Straighten_MetaData[] = {
		{ "Category", "RightHand_Map|Overall Fingers Adjust" },
		{ "Comment", "/////////\n" },
		{ "DisplayName", "EnableChanges" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	void Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Straighten_SetBit(void* Obj)
	{
		((UHandComponent*)Obj)->R_Straighten = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Straighten = { "R_Straighten", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UHandComponent), &Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Straighten_SetBit, METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Straighten_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Straighten_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Finger_Pitch_Offset_MetaData[] = {
		{ "Category", "RightHand_Map|Overall Fingers Adjust" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Finger_Pitch_Offset = { "R_Finger_Pitch_Offset", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, R_Finger_Pitch_Offset), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Finger_Pitch_Offset_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Finger_Pitch_Offset_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Finger_Coefficient_MetaData[] = {
		{ "Category", "RightHand_Map|Overall Fingers Adjust" },
		{ "ModuleRelativePath", "Public/HandComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Finger_Coefficient = { "R_Finger_Coefficient", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandComponent, R_Finger_Coefficient), METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Finger_Coefficient_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Finger_Coefficient_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UHandComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_CalibrationStatus,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_CalibrationStatus,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Angles_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Angles,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Angles_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Angles,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_BoneNameMappings_ValueProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_BoneNameMappings_Key_KeyProp_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_BoneNameMappings_Key_KeyProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_BoneNameMappings,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Pitch_Axis_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Pitch_Axis,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Yaw_Axis_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Yaw_Axis,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Roll_Axis_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Roll_Axis,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Coefficient,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Yaw_Offset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Pitch_Offset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Roll_Offset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_bUseThumbAxis_L,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Pitch_Axis_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Pitch_Axis,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Yaw_Axis_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Yaw_Axis,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Roll_Axis_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Thumb_Roll_Axis,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Finger_Offsets,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Middle,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Ring,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Pinky,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Straighten,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Finger_Pitch_Offset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_L_Finger_Coefficient,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_BoneNameMappings_ValueProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_BoneNameMappings_Key_KeyProp_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_BoneNameMappings_Key_KeyProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_BoneNameMappings,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Pitch_Axis_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Pitch_Axis,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Yaw_Axis_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Yaw_Axis,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Roll_Axis_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Roll_Axis,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Coefficient,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Yaw_Offset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Pitch_Offset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Roll_Offset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_bUseThumbAxis_R,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Pitch_Axis_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Pitch_Axis,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Yaw_Axis_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Yaw_Axis,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Roll_Axis_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Thumb_Roll_Axis,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Finger_Offsets,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Middle,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Ring,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Pinky,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Straighten,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Finger_Pitch_Offset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandComponent_Statics::NewProp_R_Finger_Coefficient,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UHandComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHandComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UHandComponent_Statics::ClassParams = {
		&UHandComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UHandComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UHandComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UHandComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UHandComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UHandComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UHandComponent, 2302383055);
	template<> HANDDRIVER_API UClass* StaticClass<UHandComponent>()
	{
		return UHandComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UHandComponent(Z_Construct_UClass_UHandComponent, &UHandComponent::StaticClass, TEXT("/Script/HandDriver"), TEXT("UHandComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UHandComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
