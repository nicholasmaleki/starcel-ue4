// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HandDriver/Private/HandDriverTypes.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHandDriverTypes() {}
// Cross Module References
	HANDDRIVER_API UEnum* Z_Construct_UEnum_HandDriver_EHandJoint();
	UPackage* Z_Construct_UPackage__Script_HandDriver();
// End Cross Module References
	static UEnum* EHandJoint_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_HandDriver_EHandJoint, Z_Construct_UPackage__Script_HandDriver(), TEXT("EHandJoint"));
		}
		return Singleton;
	}
	template<> HANDDRIVER_API UEnum* StaticEnum<EHandJoint>()
	{
		return EHandJoint_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EHandJoint(EHandJoint_StaticEnum, TEXT("/Script/HandDriver"), TEXT("EHandJoint"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_HandDriver_EHandJoint_Hash() { return 957217924U; }
	UEnum* Z_Construct_UEnum_HandDriver_EHandJoint()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_HandDriver();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EHandJoint"), 0, Get_Z_Construct_UEnum_HandDriver_EHandJoint_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EHandJoint::Wrist", (int64)EHandJoint::Wrist },
				{ "EHandJoint::Thumb_1", (int64)EHandJoint::Thumb_1 },
				{ "EHandJoint::Thumb_2", (int64)EHandJoint::Thumb_2 },
				{ "EHandJoint::Thumb_3", (int64)EHandJoint::Thumb_3 },
				{ "EHandJoint::Index_1", (int64)EHandJoint::Index_1 },
				{ "EHandJoint::Index_2", (int64)EHandJoint::Index_2 },
				{ "EHandJoint::Index_3", (int64)EHandJoint::Index_3 },
				{ "EHandJoint::Middle_1", (int64)EHandJoint::Middle_1 },
				{ "EHandJoint::Middle_2", (int64)EHandJoint::Middle_2 },
				{ "EHandJoint::Middle_3", (int64)EHandJoint::Middle_3 },
				{ "EHandJoint::Ring_1", (int64)EHandJoint::Ring_1 },
				{ "EHandJoint::Ring_2", (int64)EHandJoint::Ring_2 },
				{ "EHandJoint::Ring_3", (int64)EHandJoint::Ring_3 },
				{ "EHandJoint::Pinky_1", (int64)EHandJoint::Pinky_1 },
				{ "EHandJoint::Pinky_2", (int64)EHandJoint::Pinky_2 },
				{ "EHandJoint::Pinky_3", (int64)EHandJoint::Pinky_3 },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "Comment", "/**\n * \n */" },
				{ "Index_1.Comment", "/**\n * \n */" },
				{ "Index_1.Name", "EHandJoint::Index_1" },
				{ "Index_2.Comment", "/**\n * \n */" },
				{ "Index_2.Name", "EHandJoint::Index_2" },
				{ "Index_3.Comment", "/**\n * \n */" },
				{ "Index_3.Name", "EHandJoint::Index_3" },
				{ "Middle_1.Comment", "/**\n * \n */" },
				{ "Middle_1.Name", "EHandJoint::Middle_1" },
				{ "Middle_2.Comment", "/**\n * \n */" },
				{ "Middle_2.Name", "EHandJoint::Middle_2" },
				{ "Middle_3.Comment", "/**\n * \n */" },
				{ "Middle_3.Name", "EHandJoint::Middle_3" },
				{ "ModuleRelativePath", "Private/HandDriverTypes.h" },
				{ "Pinky_1.Comment", "/**\n * \n */" },
				{ "Pinky_1.Name", "EHandJoint::Pinky_1" },
				{ "Pinky_2.Comment", "/**\n * \n */" },
				{ "Pinky_2.Name", "EHandJoint::Pinky_2" },
				{ "Pinky_3.Comment", "/**\n * \n */" },
				{ "Pinky_3.Name", "EHandJoint::Pinky_3" },
				{ "Ring_1.Comment", "/**\n * \n */" },
				{ "Ring_1.Name", "EHandJoint::Ring_1" },
				{ "Ring_2.Comment", "/**\n * \n */" },
				{ "Ring_2.Name", "EHandJoint::Ring_2" },
				{ "Ring_3.Comment", "/**\n * \n */" },
				{ "Ring_3.Name", "EHandJoint::Ring_3" },
				{ "Thumb_1.Comment", "/**\n * \n */" },
				{ "Thumb_1.Name", "EHandJoint::Thumb_1" },
				{ "Thumb_2.Comment", "/**\n * \n */" },
				{ "Thumb_2.Name", "EHandJoint::Thumb_2" },
				{ "Thumb_3.Comment", "/**\n * \n */" },
				{ "Thumb_3.Name", "EHandJoint::Thumb_3" },
				{ "Wrist.Comment", "/**\n * \n */" },
				{ "Wrist.Name", "EHandJoint::Wrist" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_HandDriver,
				nullptr,
				"EHandJoint",
				"EHandJoint",
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
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
