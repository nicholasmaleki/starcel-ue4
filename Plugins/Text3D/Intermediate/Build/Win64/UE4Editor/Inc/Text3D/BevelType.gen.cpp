// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Text3D/Public/BevelType.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBevelType() {}
// Cross Module References
	TEXT3D_API UEnum* Z_Construct_UEnum_Text3D_EText3DBevelType();
	UPackage* Z_Construct_UPackage__Script_Text3D();
// End Cross Module References
	static UEnum* EText3DBevelType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_Text3D_EText3DBevelType, Z_Construct_UPackage__Script_Text3D(), TEXT("EText3DBevelType"));
		}
		return Singleton;
	}
	template<> TEXT3D_API UEnum* StaticEnum<EText3DBevelType>()
	{
		return EText3DBevelType_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EText3DBevelType(EText3DBevelType_StaticEnum, TEXT("/Script/Text3D"), TEXT("EText3DBevelType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_Text3D_EText3DBevelType_Hash() { return 1187494830U; }
	UEnum* Z_Construct_UEnum_Text3D_EText3DBevelType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_Text3D();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EText3DBevelType"), 0, Get_Z_Construct_UEnum_Text3D_EText3DBevelType_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EText3DBevelType::Linear", (int64)EText3DBevelType::Linear },
				{ "EText3DBevelType::HalfCircle", (int64)EText3DBevelType::HalfCircle },
				{ "EText3DBevelType::Convex", (int64)EText3DBevelType::Convex },
				{ "EText3DBevelType::Concave", (int64)EText3DBevelType::Concave },
				{ "EText3DBevelType::OneStep", (int64)EText3DBevelType::OneStep },
				{ "EText3DBevelType::TwoSteps", (int64)EText3DBevelType::TwoSteps },
				{ "EText3DBevelType::Engraved", (int64)EText3DBevelType::Engraved },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "Concave.Name", "EText3DBevelType::Concave" },
				{ "Convex.Name", "EText3DBevelType::Convex" },
				{ "Engraved.Name", "EText3DBevelType::Engraved" },
				{ "HalfCircle.Name", "EText3DBevelType::HalfCircle" },
				{ "Linear.Name", "EText3DBevelType::Linear" },
				{ "ModuleRelativePath", "Public/BevelType.h" },
				{ "OneStep.Name", "EText3DBevelType::OneStep" },
				{ "TwoSteps.Name", "EText3DBevelType::TwoSteps" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_Text3D,
				nullptr,
				"EText3DBevelType",
				"EText3DBevelType",
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
