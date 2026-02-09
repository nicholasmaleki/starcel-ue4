// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Text3D/Public/Text3DComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeText3DComponent() {}
// Cross Module References
	TEXT3D_API UEnum* Z_Construct_UEnum_Text3D_EText3DHorizontalTextAlignment();
	UPackage* Z_Construct_UPackage__Script_Text3D();
	TEXT3D_API UEnum* Z_Construct_UEnum_Text3D_EText3DVerticalTextAlignment();
	TEXT3D_API UClass* Z_Construct_UClass_UText3DComponent_NoRegister();
	TEXT3D_API UClass* Z_Construct_UClass_UText3DComponent();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
	ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
	TEXT3D_API UEnum* Z_Construct_UEnum_Text3D_EText3DBevelType();
	ENGINE_API UClass* Z_Construct_UClass_UFont_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
// End Cross Module References
	static UEnum* EText3DHorizontalTextAlignment_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_Text3D_EText3DHorizontalTextAlignment, Z_Construct_UPackage__Script_Text3D(), TEXT("EText3DHorizontalTextAlignment"));
		}
		return Singleton;
	}
	template<> TEXT3D_API UEnum* StaticEnum<EText3DHorizontalTextAlignment>()
	{
		return EText3DHorizontalTextAlignment_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EText3DHorizontalTextAlignment(EText3DHorizontalTextAlignment_StaticEnum, TEXT("/Script/Text3D"), TEXT("EText3DHorizontalTextAlignment"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_Text3D_EText3DHorizontalTextAlignment_Hash() { return 1491982317U; }
	UEnum* Z_Construct_UEnum_Text3D_EText3DHorizontalTextAlignment()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_Text3D();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EText3DHorizontalTextAlignment"), 0, Get_Z_Construct_UEnum_Text3D_EText3DHorizontalTextAlignment_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EText3DHorizontalTextAlignment::Left", (int64)EText3DHorizontalTextAlignment::Left },
				{ "EText3DHorizontalTextAlignment::Center", (int64)EText3DHorizontalTextAlignment::Center },
				{ "EText3DHorizontalTextAlignment::Right", (int64)EText3DHorizontalTextAlignment::Right },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "Center.DisplayName", "Center" },
				{ "Center.Name", "EText3DHorizontalTextAlignment::Center" },
				{ "Left.DisplayName", "Left" },
				{ "Left.Name", "EText3DHorizontalTextAlignment::Left" },
				{ "ModuleRelativePath", "Public/Text3DComponent.h" },
				{ "Right.DisplayName", "Right" },
				{ "Right.Name", "EText3DHorizontalTextAlignment::Right" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_Text3D,
				nullptr,
				"EText3DHorizontalTextAlignment",
				"EText3DHorizontalTextAlignment",
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
	static UEnum* EText3DVerticalTextAlignment_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_Text3D_EText3DVerticalTextAlignment, Z_Construct_UPackage__Script_Text3D(), TEXT("EText3DVerticalTextAlignment"));
		}
		return Singleton;
	}
	template<> TEXT3D_API UEnum* StaticEnum<EText3DVerticalTextAlignment>()
	{
		return EText3DVerticalTextAlignment_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EText3DVerticalTextAlignment(EText3DVerticalTextAlignment_StaticEnum, TEXT("/Script/Text3D"), TEXT("EText3DVerticalTextAlignment"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_Text3D_EText3DVerticalTextAlignment_Hash() { return 4117480040U; }
	UEnum* Z_Construct_UEnum_Text3D_EText3DVerticalTextAlignment()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_Text3D();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EText3DVerticalTextAlignment"), 0, Get_Z_Construct_UEnum_Text3D_EText3DVerticalTextAlignment_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EText3DVerticalTextAlignment::FirstLine", (int64)EText3DVerticalTextAlignment::FirstLine },
				{ "EText3DVerticalTextAlignment::Top", (int64)EText3DVerticalTextAlignment::Top },
				{ "EText3DVerticalTextAlignment::Center", (int64)EText3DVerticalTextAlignment::Center },
				{ "EText3DVerticalTextAlignment::Bottom", (int64)EText3DVerticalTextAlignment::Bottom },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "Bottom.DisplayName", "Bottom" },
				{ "Bottom.Name", "EText3DVerticalTextAlignment::Bottom" },
				{ "Center.DisplayName", "Center" },
				{ "Center.Name", "EText3DVerticalTextAlignment::Center" },
				{ "FirstLine.DisplayName", "First Line" },
				{ "FirstLine.Name", "EText3DVerticalTextAlignment::FirstLine" },
				{ "ModuleRelativePath", "Public/Text3DComponent.h" },
				{ "Top.DisplayName", "Top" },
				{ "Top.Name", "EText3DVerticalTextAlignment::Top" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_Text3D,
				nullptr,
				"EText3DVerticalTextAlignment",
				"EText3DVerticalTextAlignment",
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
	DEFINE_FUNCTION(UText3DComponent::execSetFreeze)
	{
		P_GET_UBOOL(Z_Param_bFreeze);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetFreeze(Z_Param_bFreeze);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UText3DComponent::execSetScaleProportionally)
	{
		P_GET_UBOOL(Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetScaleProportionally(Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UText3DComponent::execSetMaxHeight)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetMaxHeight(Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UText3DComponent::execSetHasMaxHeight)
	{
		P_GET_UBOOL(Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetHasMaxHeight(Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UText3DComponent::execSetMaxWidth)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetMaxWidth(Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UText3DComponent::execSetHasMaxWidth)
	{
		P_GET_UBOOL(Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetHasMaxWidth(Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UText3DComponent::execSetVerticalAlignment)
	{
		P_GET_ENUM(EText3DVerticalTextAlignment,Z_Param_value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetVerticalAlignment(EText3DVerticalTextAlignment(Z_Param_value));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UText3DComponent::execSetHorizontalAlignment)
	{
		P_GET_ENUM(EText3DHorizontalTextAlignment,Z_Param_value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetHorizontalAlignment(EText3DHorizontalTextAlignment(Z_Param_value));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UText3DComponent::execSetWordSpacing)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetWordSpacing(Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UText3DComponent::execSetLineSpacing)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetLineSpacing(Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UText3DComponent::execSetKerning)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetKerning(Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UText3DComponent::execSetBackMaterial)
	{
		P_GET_OBJECT(UMaterialInterface,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetBackMaterial(Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UText3DComponent::execSetExtrudeMaterial)
	{
		P_GET_OBJECT(UMaterialInterface,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetExtrudeMaterial(Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UText3DComponent::execSetBevelMaterial)
	{
		P_GET_OBJECT(UMaterialInterface,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetBevelMaterial(Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UText3DComponent::execSetFrontMaterial)
	{
		P_GET_OBJECT(UMaterialInterface,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetFrontMaterial(Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UText3DComponent::execSetBevelSegments)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetBevelSegments(Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UText3DComponent::execSetBevelType)
	{
		P_GET_ENUM(EText3DBevelType,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetBevelType(EText3DBevelType(Z_Param_Value));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UText3DComponent::execSetBevel)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetBevel(Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UText3DComponent::execSetExtrude)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetExtrude(Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UText3DComponent::execSetOutline)
	{
		P_GET_UBOOL(Z_Param_bValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetOutline(Z_Param_bValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UText3DComponent::execSetFont)
	{
		P_GET_OBJECT(UFont,Z_Param_InFont);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetFont(Z_Param_InFont);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UText3DComponent::execSetText)
	{
		P_GET_PROPERTY_REF(FTextProperty,Z_Param_Out_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetText(Z_Param_Out_Value);
		P_NATIVE_END;
	}
	void UText3DComponent::StaticRegisterNativesUText3DComponent()
	{
		UClass* Class = UText3DComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "SetBackMaterial", &UText3DComponent::execSetBackMaterial },
			{ "SetBevel", &UText3DComponent::execSetBevel },
			{ "SetBevelMaterial", &UText3DComponent::execSetBevelMaterial },
			{ "SetBevelSegments", &UText3DComponent::execSetBevelSegments },
			{ "SetBevelType", &UText3DComponent::execSetBevelType },
			{ "SetExtrude", &UText3DComponent::execSetExtrude },
			{ "SetExtrudeMaterial", &UText3DComponent::execSetExtrudeMaterial },
			{ "SetFont", &UText3DComponent::execSetFont },
			{ "SetFreeze", &UText3DComponent::execSetFreeze },
			{ "SetFrontMaterial", &UText3DComponent::execSetFrontMaterial },
			{ "SetHasMaxHeight", &UText3DComponent::execSetHasMaxHeight },
			{ "SetHasMaxWidth", &UText3DComponent::execSetHasMaxWidth },
			{ "SetHorizontalAlignment", &UText3DComponent::execSetHorizontalAlignment },
			{ "SetKerning", &UText3DComponent::execSetKerning },
			{ "SetLineSpacing", &UText3DComponent::execSetLineSpacing },
			{ "SetMaxHeight", &UText3DComponent::execSetMaxHeight },
			{ "SetMaxWidth", &UText3DComponent::execSetMaxWidth },
			{ "SetOutline", &UText3DComponent::execSetOutline },
			{ "SetScaleProportionally", &UText3DComponent::execSetScaleProportionally },
			{ "SetText", &UText3DComponent::execSetText },
			{ "SetVerticalAlignment", &UText3DComponent::execSetVerticalAlignment },
			{ "SetWordSpacing", &UText3DComponent::execSetWordSpacing },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UText3DComponent_SetBackMaterial_Statics
	{
		struct Text3DComponent_eventSetBackMaterial_Parms
		{
			UMaterialInterface* Value;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UText3DComponent_SetBackMaterial_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Text3DComponent_eventSetBackMaterial_Parms, Value), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetBackMaterial_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetBackMaterial_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetBackMaterial_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "Comment", "/** Set the text back material */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Set the text back material" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetBackMaterial_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetBackMaterial", nullptr, nullptr, sizeof(Text3DComponent_eventSetBackMaterial_Parms), Z_Construct_UFunction_UText3DComponent_SetBackMaterial_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetBackMaterial_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetBackMaterial_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetBackMaterial_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetBackMaterial()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetBackMaterial_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UText3DComponent_SetBevel_Statics
	{
		struct Text3DComponent_eventSetBevel_Parms
		{
			float Value;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetBevel_Statics::NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UText3DComponent_SetBevel_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Text3DComponent_eventSetBevel_Parms, Value), METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetBevel_Statics::NewProp_Value_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetBevel_Statics::NewProp_Value_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetBevel_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetBevel_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetBevel_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "Comment", "/** Set the 3d bevel value */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Set the 3d bevel value" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetBevel_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetBevel", nullptr, nullptr, sizeof(Text3DComponent_eventSetBevel_Parms), Z_Construct_UFunction_UText3DComponent_SetBevel_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetBevel_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetBevel_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetBevel_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetBevel()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetBevel_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UText3DComponent_SetBevelMaterial_Statics
	{
		struct Text3DComponent_eventSetBevelMaterial_Parms
		{
			UMaterialInterface* Value;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UText3DComponent_SetBevelMaterial_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Text3DComponent_eventSetBevelMaterial_Parms, Value), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetBevelMaterial_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetBevelMaterial_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetBevelMaterial_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "Comment", "/** Set the text bevel material */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Set the text bevel material" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetBevelMaterial_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetBevelMaterial", nullptr, nullptr, sizeof(Text3DComponent_eventSetBevelMaterial_Parms), Z_Construct_UFunction_UText3DComponent_SetBevelMaterial_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetBevelMaterial_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetBevelMaterial_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetBevelMaterial_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetBevelMaterial()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetBevelMaterial_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UText3DComponent_SetBevelSegments_Statics
	{
		struct Text3DComponent_eventSetBevelSegments_Parms
		{
			int32 Value;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetBevelSegments_Statics::NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UText3DComponent_SetBevelSegments_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Text3DComponent_eventSetBevelSegments_Parms, Value), METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetBevelSegments_Statics::NewProp_Value_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetBevelSegments_Statics::NewProp_Value_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetBevelSegments_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetBevelSegments_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetBevelSegments_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "Comment", "/** Set the amount of segments that will be used to tesselate the Bevel */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Set the amount of segments that will be used to tesselate the Bevel" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetBevelSegments_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetBevelSegments", nullptr, nullptr, sizeof(Text3DComponent_eventSetBevelSegments_Parms), Z_Construct_UFunction_UText3DComponent_SetBevelSegments_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetBevelSegments_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetBevelSegments_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetBevelSegments_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetBevelSegments()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetBevelSegments_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UText3DComponent_SetBevelType_Statics
	{
		struct Text3DComponent_eventSetBevelType_Parms
		{
			EText3DBevelType Value;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Value_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UText3DComponent_SetBevelType_Statics::NewProp_Value_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetBevelType_Statics::NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UText3DComponent_SetBevelType_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Text3DComponent_eventSetBevelType_Parms, Value), Z_Construct_UEnum_Text3D_EText3DBevelType, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetBevelType_Statics::NewProp_Value_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetBevelType_Statics::NewProp_Value_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetBevelType_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetBevelType_Statics::NewProp_Value_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetBevelType_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetBevelType_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "Comment", "/** Set the 3d bevel type */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Set the 3d bevel type" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetBevelType_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetBevelType", nullptr, nullptr, sizeof(Text3DComponent_eventSetBevelType_Parms), Z_Construct_UFunction_UText3DComponent_SetBevelType_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetBevelType_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetBevelType_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetBevelType_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetBevelType()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetBevelType_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UText3DComponent_SetExtrude_Statics
	{
		struct Text3DComponent_eventSetExtrude_Parms
		{
			float Value;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetExtrude_Statics::NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UText3DComponent_SetExtrude_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Text3DComponent_eventSetExtrude_Parms, Value), METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetExtrude_Statics::NewProp_Value_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetExtrude_Statics::NewProp_Value_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetExtrude_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetExtrude_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetExtrude_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "Comment", "/** Set the text extrusion size and signal the primitives to be rebuilt */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Set the text extrusion size and signal the primitives to be rebuilt" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetExtrude_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetExtrude", nullptr, nullptr, sizeof(Text3DComponent_eventSetExtrude_Parms), Z_Construct_UFunction_UText3DComponent_SetExtrude_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetExtrude_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetExtrude_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetExtrude_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetExtrude()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetExtrude_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UText3DComponent_SetExtrudeMaterial_Statics
	{
		struct Text3DComponent_eventSetExtrudeMaterial_Parms
		{
			UMaterialInterface* Value;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UText3DComponent_SetExtrudeMaterial_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Text3DComponent_eventSetExtrudeMaterial_Parms, Value), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetExtrudeMaterial_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetExtrudeMaterial_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetExtrudeMaterial_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "Comment", "/** Set the text extrude material */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Set the text extrude material" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetExtrudeMaterial_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetExtrudeMaterial", nullptr, nullptr, sizeof(Text3DComponent_eventSetExtrudeMaterial_Parms), Z_Construct_UFunction_UText3DComponent_SetExtrudeMaterial_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetExtrudeMaterial_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetExtrudeMaterial_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetExtrudeMaterial_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetExtrudeMaterial()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetExtrudeMaterial_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UText3DComponent_SetFont_Statics
	{
		struct Text3DComponent_eventSetFont_Parms
		{
			const UFont* InFont;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InFont_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_InFont;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetFont_Statics::NewProp_InFont_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UText3DComponent_SetFont_Statics::NewProp_InFont = { "InFont", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Text3DComponent_eventSetFont_Parms, InFont), Z_Construct_UClass_UFont_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetFont_Statics::NewProp_InFont_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetFont_Statics::NewProp_InFont_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetFont_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetFont_Statics::NewProp_InFont,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetFont_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "Comment", "/** Set the text font and signal the primitives to be rebuilt */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Set the text font and signal the primitives to be rebuilt" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetFont_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetFont", nullptr, nullptr, sizeof(Text3DComponent_eventSetFont_Parms), Z_Construct_UFunction_UText3DComponent_SetFont_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetFont_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetFont_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetFont_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetFont()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetFont_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UText3DComponent_SetFreeze_Statics
	{
		struct Text3DComponent_eventSetFreeze_Parms
		{
			bool bFreeze;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bFreeze_MetaData[];
#endif
		static void NewProp_bFreeze_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bFreeze;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetFreeze_Statics::NewProp_bFreeze_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_UText3DComponent_SetFreeze_Statics::NewProp_bFreeze_SetBit(void* Obj)
	{
		((Text3DComponent_eventSetFreeze_Parms*)Obj)->bFreeze = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UText3DComponent_SetFreeze_Statics::NewProp_bFreeze = { "bFreeze", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(Text3DComponent_eventSetFreeze_Parms), &Z_Construct_UFunction_UText3DComponent_SetFreeze_Statics::NewProp_bFreeze_SetBit, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetFreeze_Statics::NewProp_bFreeze_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetFreeze_Statics::NewProp_bFreeze_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetFreeze_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetFreeze_Statics::NewProp_bFreeze,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetFreeze_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "Comment", "/** Freeze mesh rebuild, to avoid unnecessary mesh rebuilds when setting a few properties together */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Freeze mesh rebuild, to avoid unnecessary mesh rebuilds when setting a few properties together" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetFreeze_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetFreeze", nullptr, nullptr, sizeof(Text3DComponent_eventSetFreeze_Parms), Z_Construct_UFunction_UText3DComponent_SetFreeze_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetFreeze_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetFreeze_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetFreeze_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetFreeze()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetFreeze_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UText3DComponent_SetFrontMaterial_Statics
	{
		struct Text3DComponent_eventSetFrontMaterial_Parms
		{
			UMaterialInterface* Value;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UText3DComponent_SetFrontMaterial_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Text3DComponent_eventSetFrontMaterial_Parms, Value), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetFrontMaterial_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetFrontMaterial_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetFrontMaterial_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "Comment", "/** Set the text front material */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Set the text front material" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetFrontMaterial_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetFrontMaterial", nullptr, nullptr, sizeof(Text3DComponent_eventSetFrontMaterial_Parms), Z_Construct_UFunction_UText3DComponent_SetFrontMaterial_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetFrontMaterial_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetFrontMaterial_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetFrontMaterial_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetFrontMaterial()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetFrontMaterial_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UText3DComponent_SetHasMaxHeight_Statics
	{
		struct Text3DComponent_eventSetHasMaxHeight_Parms
		{
			bool Value;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static void NewProp_Value_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetHasMaxHeight_Statics::NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_UText3DComponent_SetHasMaxHeight_Statics::NewProp_Value_SetBit(void* Obj)
	{
		((Text3DComponent_eventSetHasMaxHeight_Parms*)Obj)->Value = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UText3DComponent_SetHasMaxHeight_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(Text3DComponent_eventSetHasMaxHeight_Parms), &Z_Construct_UFunction_UText3DComponent_SetHasMaxHeight_Statics::NewProp_Value_SetBit, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetHasMaxHeight_Statics::NewProp_Value_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetHasMaxHeight_Statics::NewProp_Value_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetHasMaxHeight_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetHasMaxHeight_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetHasMaxHeight_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "Comment", "/** Enable / Disable a Maximum Height */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Enable / Disable a Maximum Height" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetHasMaxHeight_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetHasMaxHeight", nullptr, nullptr, sizeof(Text3DComponent_eventSetHasMaxHeight_Parms), Z_Construct_UFunction_UText3DComponent_SetHasMaxHeight_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetHasMaxHeight_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetHasMaxHeight_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetHasMaxHeight_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetHasMaxHeight()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetHasMaxHeight_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UText3DComponent_SetHasMaxWidth_Statics
	{
		struct Text3DComponent_eventSetHasMaxWidth_Parms
		{
			bool Value;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static void NewProp_Value_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetHasMaxWidth_Statics::NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_UText3DComponent_SetHasMaxWidth_Statics::NewProp_Value_SetBit(void* Obj)
	{
		((Text3DComponent_eventSetHasMaxWidth_Parms*)Obj)->Value = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UText3DComponent_SetHasMaxWidth_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(Text3DComponent_eventSetHasMaxWidth_Parms), &Z_Construct_UFunction_UText3DComponent_SetHasMaxWidth_Statics::NewProp_Value_SetBit, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetHasMaxWidth_Statics::NewProp_Value_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetHasMaxWidth_Statics::NewProp_Value_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetHasMaxWidth_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetHasMaxWidth_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetHasMaxWidth_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "Comment", "/** Enable / Disable a Maximum Width */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Enable / Disable a Maximum Width" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetHasMaxWidth_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetHasMaxWidth", nullptr, nullptr, sizeof(Text3DComponent_eventSetHasMaxWidth_Parms), Z_Construct_UFunction_UText3DComponent_SetHasMaxWidth_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetHasMaxWidth_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetHasMaxWidth_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetHasMaxWidth_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetHasMaxWidth()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetHasMaxWidth_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UText3DComponent_SetHorizontalAlignment_Statics
	{
		struct Text3DComponent_eventSetHorizontalAlignment_Parms
		{
			EText3DHorizontalTextAlignment value;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_value_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_value_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UText3DComponent_SetHorizontalAlignment_Statics::NewProp_value_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetHorizontalAlignment_Statics::NewProp_value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UText3DComponent_SetHorizontalAlignment_Statics::NewProp_value = { "value", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Text3DComponent_eventSetHorizontalAlignment_Parms, value), Z_Construct_UEnum_Text3D_EText3DHorizontalTextAlignment, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetHorizontalAlignment_Statics::NewProp_value_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetHorizontalAlignment_Statics::NewProp_value_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetHorizontalAlignment_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetHorizontalAlignment_Statics::NewProp_value_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetHorizontalAlignment_Statics::NewProp_value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetHorizontalAlignment_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "Comment", "/** Set the horizontal alignment value and signal the primitives to be rebuilt */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Set the horizontal alignment value and signal the primitives to be rebuilt" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetHorizontalAlignment_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetHorizontalAlignment", nullptr, nullptr, sizeof(Text3DComponent_eventSetHorizontalAlignment_Parms), Z_Construct_UFunction_UText3DComponent_SetHorizontalAlignment_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetHorizontalAlignment_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetHorizontalAlignment_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetHorizontalAlignment_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetHorizontalAlignment()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetHorizontalAlignment_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UText3DComponent_SetKerning_Statics
	{
		struct Text3DComponent_eventSetKerning_Parms
		{
			float Value;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetKerning_Statics::NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UText3DComponent_SetKerning_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Text3DComponent_eventSetKerning_Parms, Value), METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetKerning_Statics::NewProp_Value_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetKerning_Statics::NewProp_Value_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetKerning_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetKerning_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetKerning_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "Comment", "/** Set the kerning value and signal the primitives to be rebuilt */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Set the kerning value and signal the primitives to be rebuilt" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetKerning_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetKerning", nullptr, nullptr, sizeof(Text3DComponent_eventSetKerning_Parms), Z_Construct_UFunction_UText3DComponent_SetKerning_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetKerning_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetKerning_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetKerning_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetKerning()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetKerning_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UText3DComponent_SetLineSpacing_Statics
	{
		struct Text3DComponent_eventSetLineSpacing_Parms
		{
			float Value;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetLineSpacing_Statics::NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UText3DComponent_SetLineSpacing_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Text3DComponent_eventSetLineSpacing_Parms, Value), METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetLineSpacing_Statics::NewProp_Value_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetLineSpacing_Statics::NewProp_Value_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetLineSpacing_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetLineSpacing_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetLineSpacing_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "Comment", "/** Set the line spacing value and signal the primitives to be rebuilt */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Set the line spacing value and signal the primitives to be rebuilt" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetLineSpacing_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetLineSpacing", nullptr, nullptr, sizeof(Text3DComponent_eventSetLineSpacing_Parms), Z_Construct_UFunction_UText3DComponent_SetLineSpacing_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetLineSpacing_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetLineSpacing_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetLineSpacing_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetLineSpacing()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetLineSpacing_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UText3DComponent_SetMaxHeight_Statics
	{
		struct Text3DComponent_eventSetMaxHeight_Parms
		{
			float Value;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetMaxHeight_Statics::NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UText3DComponent_SetMaxHeight_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Text3DComponent_eventSetMaxHeight_Parms, Value), METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetMaxHeight_Statics::NewProp_Value_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetMaxHeight_Statics::NewProp_Value_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetMaxHeight_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetMaxHeight_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetMaxHeight_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "Comment", "/** Set the Maximum Height - If height is larger, mesh will scale down to fit MaxHeight value */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Set the Maximum Height - If height is larger, mesh will scale down to fit MaxHeight value" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetMaxHeight_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetMaxHeight", nullptr, nullptr, sizeof(Text3DComponent_eventSetMaxHeight_Parms), Z_Construct_UFunction_UText3DComponent_SetMaxHeight_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetMaxHeight_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetMaxHeight_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetMaxHeight_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetMaxHeight()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetMaxHeight_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UText3DComponent_SetMaxWidth_Statics
	{
		struct Text3DComponent_eventSetMaxWidth_Parms
		{
			float Value;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetMaxWidth_Statics::NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UText3DComponent_SetMaxWidth_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Text3DComponent_eventSetMaxWidth_Parms, Value), METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetMaxWidth_Statics::NewProp_Value_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetMaxWidth_Statics::NewProp_Value_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetMaxWidth_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetMaxWidth_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetMaxWidth_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "Comment", "/** Set the Maximum Width - If width is larger, mesh will scale down to fit MaxWidth value */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Set the Maximum Width - If width is larger, mesh will scale down to fit MaxWidth value" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetMaxWidth_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetMaxWidth", nullptr, nullptr, sizeof(Text3DComponent_eventSetMaxWidth_Parms), Z_Construct_UFunction_UText3DComponent_SetMaxWidth_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetMaxWidth_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetMaxWidth_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetMaxWidth_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetMaxWidth()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetMaxWidth_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UText3DComponent_SetOutline_Statics
	{
		struct Text3DComponent_eventSetOutline_Parms
		{
			bool bValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bValue_MetaData[];
#endif
		static void NewProp_bValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetOutline_Statics::NewProp_bValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_UText3DComponent_SetOutline_Statics::NewProp_bValue_SetBit(void* Obj)
	{
		((Text3DComponent_eventSetOutline_Parms*)Obj)->bValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UText3DComponent_SetOutline_Statics::NewProp_bValue = { "bValue", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(Text3DComponent_eventSetOutline_Parms), &Z_Construct_UFunction_UText3DComponent_SetOutline_Statics::NewProp_bValue_SetBit, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetOutline_Statics::NewProp_bValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetOutline_Statics::NewProp_bValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetOutline_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetOutline_Statics::NewProp_bValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetOutline_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetOutline_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetOutline", nullptr, nullptr, sizeof(Text3DComponent_eventSetOutline_Parms), Z_Construct_UFunction_UText3DComponent_SetOutline_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetOutline_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetOutline_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetOutline_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetOutline()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetOutline_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UText3DComponent_SetScaleProportionally_Statics
	{
		struct Text3DComponent_eventSetScaleProportionally_Parms
		{
			bool Value;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static void NewProp_Value_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetScaleProportionally_Statics::NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_UText3DComponent_SetScaleProportionally_Statics::NewProp_Value_SetBit(void* Obj)
	{
		((Text3DComponent_eventSetScaleProportionally_Parms*)Obj)->Value = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UText3DComponent_SetScaleProportionally_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(Text3DComponent_eventSetScaleProportionally_Parms), &Z_Construct_UFunction_UText3DComponent_SetScaleProportionally_Statics::NewProp_Value_SetBit, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetScaleProportionally_Statics::NewProp_Value_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetScaleProportionally_Statics::NewProp_Value_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetScaleProportionally_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetScaleProportionally_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetScaleProportionally_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "Comment", "/** Set if the mesh should scale proportionally when Max Width/Height is set */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Set if the mesh should scale proportionally when Max Width/Height is set" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetScaleProportionally_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetScaleProportionally", nullptr, nullptr, sizeof(Text3DComponent_eventSetScaleProportionally_Parms), Z_Construct_UFunction_UText3DComponent_SetScaleProportionally_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetScaleProportionally_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetScaleProportionally_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetScaleProportionally_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetScaleProportionally()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetScaleProportionally_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UText3DComponent_SetText_Statics
	{
		struct Text3DComponent_eventSetText_Parms
		{
			FText Value;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static const UE4CodeGen_Private::FTextPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetText_Statics::NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FTextPropertyParams Z_Construct_UFunction_UText3DComponent_SetText_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Text3DComponent_eventSetText_Parms, Value), METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetText_Statics::NewProp_Value_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetText_Statics::NewProp_Value_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetText_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetText_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetText_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "Comment", "/** Set the text value and signal the primitives to be rebuilt */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Set the text value and signal the primitives to be rebuilt" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetText_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetText", nullptr, nullptr, sizeof(Text3DComponent_eventSetText_Parms), Z_Construct_UFunction_UText3DComponent_SetText_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetText_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetText_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetText_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetText()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetText_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UText3DComponent_SetVerticalAlignment_Statics
	{
		struct Text3DComponent_eventSetVerticalAlignment_Parms
		{
			EText3DVerticalTextAlignment value;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_value_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_value_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UText3DComponent_SetVerticalAlignment_Statics::NewProp_value_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetVerticalAlignment_Statics::NewProp_value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UText3DComponent_SetVerticalAlignment_Statics::NewProp_value = { "value", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Text3DComponent_eventSetVerticalAlignment_Parms, value), Z_Construct_UEnum_Text3D_EText3DVerticalTextAlignment, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetVerticalAlignment_Statics::NewProp_value_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetVerticalAlignment_Statics::NewProp_value_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetVerticalAlignment_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetVerticalAlignment_Statics::NewProp_value_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetVerticalAlignment_Statics::NewProp_value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetVerticalAlignment_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "Comment", "/** Set the vertical alignment and signal the primitives to be rebuilt */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Set the vertical alignment and signal the primitives to be rebuilt" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetVerticalAlignment_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetVerticalAlignment", nullptr, nullptr, sizeof(Text3DComponent_eventSetVerticalAlignment_Parms), Z_Construct_UFunction_UText3DComponent_SetVerticalAlignment_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetVerticalAlignment_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetVerticalAlignment_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetVerticalAlignment_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetVerticalAlignment()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetVerticalAlignment_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UText3DComponent_SetWordSpacing_Statics
	{
		struct Text3DComponent_eventSetWordSpacing_Parms
		{
			float Value;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetWordSpacing_Statics::NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UText3DComponent_SetWordSpacing_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Text3DComponent_eventSetWordSpacing_Parms, Value), METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetWordSpacing_Statics::NewProp_Value_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetWordSpacing_Statics::NewProp_Value_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UText3DComponent_SetWordSpacing_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UText3DComponent_SetWordSpacing_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UText3DComponent_SetWordSpacing_Statics::Function_MetaDataParams[] = {
		{ "Category", "Rendering|Components|Text3D" },
		{ "Comment", "/** Set the word spacing value and signal the primitives to be rebuilt */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Set the word spacing value and signal the primitives to be rebuilt" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UText3DComponent_SetWordSpacing_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UText3DComponent, nullptr, "SetWordSpacing", nullptr, nullptr, sizeof(Text3DComponent_eventSetWordSpacing_Parms), Z_Construct_UFunction_UText3DComponent_SetWordSpacing_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetWordSpacing_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UText3DComponent_SetWordSpacing_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UText3DComponent_SetWordSpacing_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UText3DComponent_SetWordSpacing()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UText3DComponent_SetWordSpacing_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UText3DComponent_NoRegister()
	{
		return UText3DComponent::StaticClass();
	}
	struct Z_Construct_UClass_UText3DComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Text_MetaData[];
#endif
		static const UE4CodeGen_Private::FTextPropertyParams NewProp_Text;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Extrude_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Extrude;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Bevel_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Bevel;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_BevelType_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BevelType_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_BevelType;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BevelSegments_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_BevelSegments;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bOutline_MetaData[];
#endif
		static void NewProp_bOutline_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bOutline;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FrontMaterial_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_FrontMaterial;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BevelMaterial_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_BevelMaterial;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ExtrudeMaterial_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ExtrudeMaterial;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BackMaterial_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_BackMaterial;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Font_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Font;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_HorizontalAlignment_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_HorizontalAlignment_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_HorizontalAlignment;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_VerticalAlignment_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_VerticalAlignment_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_VerticalAlignment;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Kerning_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Kerning;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LineSpacing_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_LineSpacing;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_WordSpacing_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_WordSpacing;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bHasMaxWidth_MetaData[];
#endif
		static void NewProp_bHasMaxWidth_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bHasMaxWidth;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaxWidth_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MaxWidth;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bHasMaxHeight_MetaData[];
#endif
		static void NewProp_bHasMaxHeight_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bHasMaxHeight;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaxHeight_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MaxHeight;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bScaleProportionally_MetaData[];
#endif
		static void NewProp_bScaleProportionally_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bScaleProportionally;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TextRoot_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_TextRoot;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CharacterKernings_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CharacterKernings_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_CharacterKernings;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CharacterMeshes_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CharacterMeshes_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_CharacterMeshes;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UText3DComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USceneComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_Text3D,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UText3DComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UText3DComponent_SetBackMaterial, "SetBackMaterial" }, // 3208336970
		{ &Z_Construct_UFunction_UText3DComponent_SetBevel, "SetBevel" }, // 3305886433
		{ &Z_Construct_UFunction_UText3DComponent_SetBevelMaterial, "SetBevelMaterial" }, // 962014081
		{ &Z_Construct_UFunction_UText3DComponent_SetBevelSegments, "SetBevelSegments" }, // 3659299030
		{ &Z_Construct_UFunction_UText3DComponent_SetBevelType, "SetBevelType" }, // 2606760175
		{ &Z_Construct_UFunction_UText3DComponent_SetExtrude, "SetExtrude" }, // 2977411864
		{ &Z_Construct_UFunction_UText3DComponent_SetExtrudeMaterial, "SetExtrudeMaterial" }, // 2588964788
		{ &Z_Construct_UFunction_UText3DComponent_SetFont, "SetFont" }, // 3422343876
		{ &Z_Construct_UFunction_UText3DComponent_SetFreeze, "SetFreeze" }, // 3768659064
		{ &Z_Construct_UFunction_UText3DComponent_SetFrontMaterial, "SetFrontMaterial" }, // 694733641
		{ &Z_Construct_UFunction_UText3DComponent_SetHasMaxHeight, "SetHasMaxHeight" }, // 1947278292
		{ &Z_Construct_UFunction_UText3DComponent_SetHasMaxWidth, "SetHasMaxWidth" }, // 1500378430
		{ &Z_Construct_UFunction_UText3DComponent_SetHorizontalAlignment, "SetHorizontalAlignment" }, // 1565520759
		{ &Z_Construct_UFunction_UText3DComponent_SetKerning, "SetKerning" }, // 3661088131
		{ &Z_Construct_UFunction_UText3DComponent_SetLineSpacing, "SetLineSpacing" }, // 400855721
		{ &Z_Construct_UFunction_UText3DComponent_SetMaxHeight, "SetMaxHeight" }, // 1478625827
		{ &Z_Construct_UFunction_UText3DComponent_SetMaxWidth, "SetMaxWidth" }, // 2667862470
		{ &Z_Construct_UFunction_UText3DComponent_SetOutline, "SetOutline" }, // 3172619398
		{ &Z_Construct_UFunction_UText3DComponent_SetScaleProportionally, "SetScaleProportionally" }, // 71537633
		{ &Z_Construct_UFunction_UText3DComponent_SetText, "SetText" }, // 3975113834
		{ &Z_Construct_UFunction_UText3DComponent_SetVerticalAlignment, "SetVerticalAlignment" }, // 1941454292
		{ &Z_Construct_UFunction_UText3DComponent_SetWordSpacing, "SetWordSpacing" }, // 3186601682
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Text3D" },
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "Text3DComponent.h" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_Text_MetaData[] = {
		{ "BlueprintSetter", "SetText" },
		{ "Category", "Text3D" },
		{ "Comment", "/** The text to generate a 3d mesh */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "MultiLine", "TRUE" },
		{ "ToolTip", "The text to generate a 3d mesh" },
	};
#endif
	const UE4CodeGen_Private::FTextPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_Text = { "Text", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DComponent, Text), METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_Text_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_Text_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_Extrude_MetaData[] = {
		{ "BlueprintSetter", "SetExtrude" },
		{ "Category", "Text3D" },
		{ "ClampMin", "0" },
		{ "Comment", "/** Size of the extrude */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Size of the extrude" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_Extrude = { "Extrude", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DComponent, Extrude), METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_Extrude_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_Extrude_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_Bevel_MetaData[] = {
		{ "BlueprintSetter", "SetBevel" },
		{ "Category", "Text3D" },
		{ "ClampMin", "0" },
		{ "Comment", "/** Size of bevel */" },
		{ "EditCondition", "!bOutline" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Size of bevel" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_Bevel = { "Bevel", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DComponent, Bevel), METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_Bevel_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_Bevel_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_BevelType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_BevelType_MetaData[] = {
		{ "BlueprintSetter", "SetBevelType" },
		{ "Category", "Text3D" },
		{ "Comment", "/** Bevel Type */" },
		{ "EditCondition", "!bOutline" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Bevel Type" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_BevelType = { "BevelType", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DComponent, BevelType), Z_Construct_UEnum_Text3D_EText3DBevelType, METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_BevelType_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_BevelType_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_BevelSegments_MetaData[] = {
		{ "BlueprintSetter", "SetBevelSegments" },
		{ "Category", "Text3D" },
		{ "ClampMax", "15" },
		{ "ClampMin", "1" },
		{ "Comment", "/** Bevel Segments (Defines the amount of tesselation for the bevel part) */" },
		{ "EditCondition", "!bOutline" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Bevel Segments (Defines the amount of tesselation for the bevel part)" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_BevelSegments = { "BevelSegments", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DComponent, BevelSegments), METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_BevelSegments_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_BevelSegments_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_bOutline_MetaData[] = {
		{ "BlueprintSetter", "SetOutline" },
		{ "Category", "Text3D" },
		{ "Comment", "/** Generate Outline */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Generate Outline" },
	};
#endif
	void Z_Construct_UClass_UText3DComponent_Statics::NewProp_bOutline_SetBit(void* Obj)
	{
		((UText3DComponent*)Obj)->bOutline = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_bOutline = { "bOutline", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UText3DComponent), &Z_Construct_UClass_UText3DComponent_Statics::NewProp_bOutline_SetBit, METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_bOutline_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_bOutline_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_FrontMaterial_MetaData[] = {
		{ "BlueprintSetter", "SetFrontMaterial" },
		{ "Category", "Text3D" },
		{ "Comment", "/** Material for the front part */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Material for the front part" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_FrontMaterial = { "FrontMaterial", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DComponent, FrontMaterial), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_FrontMaterial_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_FrontMaterial_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_BevelMaterial_MetaData[] = {
		{ "BlueprintSetter", "SetBevelMaterial" },
		{ "Category", "Text3D" },
		{ "Comment", "/** Material for the bevel part */" },
		{ "EditCondition", "!bOutline" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Material for the bevel part" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_BevelMaterial = { "BevelMaterial", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DComponent, BevelMaterial), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_BevelMaterial_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_BevelMaterial_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_ExtrudeMaterial_MetaData[] = {
		{ "BlueprintSetter", "SetExtrudeMaterial" },
		{ "Category", "Text3D" },
		{ "Comment", "/** Material for the extruded part */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Material for the extruded part" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_ExtrudeMaterial = { "ExtrudeMaterial", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DComponent, ExtrudeMaterial), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_ExtrudeMaterial_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_ExtrudeMaterial_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_BackMaterial_MetaData[] = {
		{ "BlueprintSetter", "SetBackMaterial" },
		{ "Category", "Text3D" },
		{ "Comment", "/** Material for the back part */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Material for the back part" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_BackMaterial = { "BackMaterial", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DComponent, BackMaterial), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_BackMaterial_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_BackMaterial_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_Font_MetaData[] = {
		{ "BlueprintSetter", "SetFont" },
		{ "Category", "Text3D" },
		{ "Comment", "/** Text font */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Text font" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_Font = { "Font", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DComponent, Font), Z_Construct_UClass_UFont_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_Font_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_Font_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_HorizontalAlignment_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_HorizontalAlignment_MetaData[] = {
		{ "BlueprintSetter", "SetHorizontalAlignment" },
		{ "Category", "Text3D" },
		{ "Comment", "/** Horizontal text alignment */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Horizontal text alignment" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_HorizontalAlignment = { "HorizontalAlignment", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DComponent, HorizontalAlignment), Z_Construct_UEnum_Text3D_EText3DHorizontalTextAlignment, METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_HorizontalAlignment_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_HorizontalAlignment_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_VerticalAlignment_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_VerticalAlignment_MetaData[] = {
		{ "BlueprintSetter", "SetVerticalAlignment" },
		{ "Category", "Text3D" },
		{ "Comment", "/** Vertical text alignment */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Vertical text alignment" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_VerticalAlignment = { "VerticalAlignment", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DComponent, VerticalAlignment), Z_Construct_UEnum_Text3D_EText3DVerticalTextAlignment, METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_VerticalAlignment_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_VerticalAlignment_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_Kerning_MetaData[] = {
		{ "BlueprintSetter", "SetKerning" },
		{ "Category", "Text3D" },
		{ "Comment", "/** Text kerning */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Text kerning" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_Kerning = { "Kerning", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DComponent, Kerning), METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_Kerning_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_Kerning_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_LineSpacing_MetaData[] = {
		{ "BlueprintSetter", "SetLineSpacing" },
		{ "Category", "Text3D" },
		{ "Comment", "/** Extra line spacing */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Extra line spacing" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_LineSpacing = { "LineSpacing", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DComponent, LineSpacing), METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_LineSpacing_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_LineSpacing_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_WordSpacing_MetaData[] = {
		{ "BlueprintSetter", "SetWordSpacing" },
		{ "Category", "Text3D" },
		{ "Comment", "/** Extra word spacing */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Extra word spacing" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_WordSpacing = { "WordSpacing", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DComponent, WordSpacing), METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_WordSpacing_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_WordSpacing_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_bHasMaxWidth_MetaData[] = {
		{ "BlueprintSetter", "SetHasMaxWidth" },
		{ "Category", "Text3D" },
		{ "Comment", "/** Enables a maximum width to the 3D Text */" },
		{ "InlineEditConditionToggle", "" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Enables a maximum width to the 3D Text" },
	};
#endif
	void Z_Construct_UClass_UText3DComponent_Statics::NewProp_bHasMaxWidth_SetBit(void* Obj)
	{
		((UText3DComponent*)Obj)->bHasMaxWidth = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_bHasMaxWidth = { "bHasMaxWidth", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UText3DComponent), &Z_Construct_UClass_UText3DComponent_Statics::NewProp_bHasMaxWidth_SetBit, METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_bHasMaxWidth_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_bHasMaxWidth_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_MaxWidth_MetaData[] = {
		{ "BlueprintSetter", "SetMaxWidth" },
		{ "Category", "Text3D" },
		{ "ClampMin", "1" },
		{ "Comment", "/** Sets a maximum width to the 3D Text */" },
		{ "EditCondition", "bHasMaxWidth" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Sets a maximum width to the 3D Text" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_MaxWidth = { "MaxWidth", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DComponent, MaxWidth), METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_MaxWidth_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_MaxWidth_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_bHasMaxHeight_MetaData[] = {
		{ "BlueprintSetter", "SetHasMaxHeight" },
		{ "Category", "Text3D" },
		{ "Comment", "/** Enables a maximum height to the 3D Text */" },
		{ "InlineEditConditionToggle", "" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Enables a maximum height to the 3D Text" },
	};
#endif
	void Z_Construct_UClass_UText3DComponent_Statics::NewProp_bHasMaxHeight_SetBit(void* Obj)
	{
		((UText3DComponent*)Obj)->bHasMaxHeight = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_bHasMaxHeight = { "bHasMaxHeight", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UText3DComponent), &Z_Construct_UClass_UText3DComponent_Statics::NewProp_bHasMaxHeight_SetBit, METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_bHasMaxHeight_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_bHasMaxHeight_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_MaxHeight_MetaData[] = {
		{ "BlueprintSetter", "SetMaxHeight" },
		{ "Category", "Text3D" },
		{ "ClampMin", "1" },
		{ "Comment", "/** Sets a maximum height to the 3D Text */" },
		{ "EditCondition", "bHasMaxHeight" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Sets a maximum height to the 3D Text" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_MaxHeight = { "MaxHeight", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DComponent, MaxHeight), METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_MaxHeight_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_MaxHeight_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_bScaleProportionally_MetaData[] = {
		{ "BlueprintSetter", "SetScaleProportionally" },
		{ "Category", "Text3D" },
		{ "Comment", "/** Should the mesh scale proportionally when Max Width/Height is set */" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
		{ "ToolTip", "Should the mesh scale proportionally when Max Width/Height is set" },
	};
#endif
	void Z_Construct_UClass_UText3DComponent_Statics::NewProp_bScaleProportionally_SetBit(void* Obj)
	{
		((UText3DComponent*)Obj)->bScaleProportionally = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_bScaleProportionally = { "bScaleProportionally", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UText3DComponent), &Z_Construct_UClass_UText3DComponent_Statics::NewProp_bScaleProportionally_SetBit, METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_bScaleProportionally_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_bScaleProportionally_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_TextRoot_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_TextRoot = { "TextRoot", nullptr, (EPropertyFlags)0x0040000000082008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DComponent, TextRoot), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_TextRoot_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_TextRoot_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_CharacterKernings_Inner = { "CharacterKernings", nullptr, (EPropertyFlags)0x0000000000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_CharacterKernings_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_CharacterKernings = { "CharacterKernings", nullptr, (EPropertyFlags)0x0040008000002008, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DComponent, CharacterKernings), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_CharacterKernings_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_CharacterKernings_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_CharacterMeshes_Inner = { "CharacterMeshes", nullptr, (EPropertyFlags)0x0000000000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UText3DComponent_Statics::NewProp_CharacterMeshes_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Text3DComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UText3DComponent_Statics::NewProp_CharacterMeshes = { "CharacterMeshes", nullptr, (EPropertyFlags)0x0040008000002008, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UText3DComponent, CharacterMeshes), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::NewProp_CharacterMeshes_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::NewProp_CharacterMeshes_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UText3DComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_Text,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_Extrude,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_Bevel,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_BevelType_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_BevelType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_BevelSegments,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_bOutline,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_FrontMaterial,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_BevelMaterial,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_ExtrudeMaterial,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_BackMaterial,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_Font,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_HorizontalAlignment_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_HorizontalAlignment,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_VerticalAlignment_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_VerticalAlignment,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_Kerning,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_LineSpacing,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_WordSpacing,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_bHasMaxWidth,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_MaxWidth,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_bHasMaxHeight,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_MaxHeight,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_bScaleProportionally,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_TextRoot,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_CharacterKernings_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_CharacterKernings,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_CharacterMeshes_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UText3DComponent_Statics::NewProp_CharacterMeshes,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UText3DComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UText3DComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UText3DComponent_Statics::ClassParams = {
		&UText3DComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UText3DComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UText3DComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UText3DComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UText3DComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UText3DComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UText3DComponent, 3049776945);
	template<> TEXT3D_API UClass* StaticClass<UText3DComponent>()
	{
		return UText3DComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UText3DComponent(Z_Construct_UClass_UText3DComponent, &UText3DComponent::StaticClass, TEXT("/Script/Text3D"), TEXT("UText3DComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UText3DComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
