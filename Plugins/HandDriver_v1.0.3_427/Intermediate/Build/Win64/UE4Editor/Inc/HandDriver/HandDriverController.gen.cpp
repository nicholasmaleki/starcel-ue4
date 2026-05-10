// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HandDriver/Private/HandDriverController.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHandDriverController() {}
// Cross Module References
	HANDDRIVER_API UScriptStruct* Z_Construct_UScriptStruct_FHandDriverControllerData();
	UPackage* Z_Construct_UPackage__Script_HandDriver();
	HANDDRIVER_API UClass* Z_Construct_UClass_UHandDriverController_NoRegister();
	HANDDRIVER_API UClass* Z_Construct_UClass_UHandDriverController();
	LIVELINKCOMPONENTS_API UClass* Z_Construct_UClass_ULiveLinkControllerBase();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FComponentReference();
// End Cross Module References
class UScriptStruct* FHandDriverControllerData::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern HANDDRIVER_API uint32 Get_Z_Construct_UScriptStruct_FHandDriverControllerData_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FHandDriverControllerData, Z_Construct_UPackage__Script_HandDriver(), TEXT("HandDriverControllerData"), sizeof(FHandDriverControllerData), Get_Z_Construct_UScriptStruct_FHandDriverControllerData_Hash());
	}
	return Singleton;
}
template<> HANDDRIVER_API UScriptStruct* StaticStruct<FHandDriverControllerData>()
{
	return FHandDriverControllerData::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FHandDriverControllerData(FHandDriverControllerData::StaticStruct, TEXT("/Script/HandDriver"), TEXT("HandDriverControllerData"), false, nullptr, nullptr);
static struct FScriptStruct_HandDriver_StaticRegisterNativesFHandDriverControllerData
{
	FScriptStruct_HandDriver_StaticRegisterNativesFHandDriverControllerData()
	{
		UScriptStruct::DeferCppStructOps<FHandDriverControllerData>(FName(TEXT("HandDriverControllerData")));
	}
} ScriptStruct_HandDriver_StaticRegisterNativesFHandDriverControllerData;
	struct Z_Construct_UScriptStruct_FHandDriverControllerData_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bWorldTransform_MetaData[];
#endif
		static void NewProp_bWorldTransform_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bWorldTransform;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bUseLocation_MetaData[];
#endif
		static void NewProp_bUseLocation_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bUseLocation;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bUseRotation_MetaData[];
#endif
		static void NewProp_bUseRotation_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bUseRotation;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bUseScale_MetaData[];
#endif
		static void NewProp_bUseScale_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bUseScale;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bSweep_MetaData[];
#endif
		static void NewProp_bSweep_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bSweep;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bTeleport_MetaData[];
#endif
		static void NewProp_bTeleport_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bTeleport;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bUseHandDriver_MetaData[];
#endif
		static void NewProp_bUseHandDriver_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bUseHandDriver;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "//DECLARE_LOG_CATEGORY_EXTERN(LogHandDriver, Log, All);\n" },
		{ "ModuleRelativePath", "Private/HandDriverController.h" },
		{ "ToolTip", "DECLARE_LOG_CATEGORY_EXTERN(LogHandDriver, Log, All);" },
	};
#endif
	void* Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FHandDriverControllerData>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bWorldTransform_MetaData[] = {
		{ "Category", "HandDriver" },
		{ "ModuleRelativePath", "Private/HandDriverController.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bWorldTransform_SetBit(void* Obj)
	{
		((FHandDriverControllerData*)Obj)->bWorldTransform = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bWorldTransform = { "bWorldTransform", nullptr, (EPropertyFlags)0x0010000000000015, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FHandDriverControllerData), &Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bWorldTransform_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bWorldTransform_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bWorldTransform_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseLocation_MetaData[] = {
		{ "Category", "HandDriver" },
		{ "ModuleRelativePath", "Private/HandDriverController.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseLocation_SetBit(void* Obj)
	{
		((FHandDriverControllerData*)Obj)->bUseLocation = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseLocation = { "bUseLocation", nullptr, (EPropertyFlags)0x0010040000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FHandDriverControllerData), &Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseLocation_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseLocation_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseLocation_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseRotation_MetaData[] = {
		{ "Category", "HandDriver" },
		{ "ModuleRelativePath", "Private/HandDriverController.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseRotation_SetBit(void* Obj)
	{
		((FHandDriverControllerData*)Obj)->bUseRotation = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseRotation = { "bUseRotation", nullptr, (EPropertyFlags)0x0010040000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FHandDriverControllerData), &Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseRotation_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseRotation_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseRotation_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseScale_MetaData[] = {
		{ "Category", "HandDriver" },
		{ "ModuleRelativePath", "Private/HandDriverController.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseScale_SetBit(void* Obj)
	{
		((FHandDriverControllerData*)Obj)->bUseScale = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseScale = { "bUseScale", nullptr, (EPropertyFlags)0x0010040000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FHandDriverControllerData), &Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseScale_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseScale_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseScale_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bSweep_MetaData[] = {
		{ "Category", "HandDriver" },
		{ "Comment", "/**\n\x09* Whether we sweep to the destination location, triggering overlaps along the way and stopping short of the target if blocked by something.\n\x09* Only the root component is swept and checked for blocking collision, child components move without sweeping. If collision is off, this has no effect.\n\x09*/" },
		{ "ModuleRelativePath", "Private/HandDriverController.h" },
		{ "ToolTip", "Whether we sweep to the destination location, triggering overlaps along the way and stopping short of the target if blocked by something.\nOnly the root component is swept and checked for blocking collision, child components move without sweeping. If collision is off, this has no effect." },
	};
#endif
	void Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bSweep_SetBit(void* Obj)
	{
		((FHandDriverControllerData*)Obj)->bSweep = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bSweep = { "bSweep", nullptr, (EPropertyFlags)0x0010040000000015, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FHandDriverControllerData), &Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bSweep_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bSweep_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bSweep_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bTeleport_MetaData[] = {
		{ "Category", "HandDriver" },
		{ "Comment", "/**\n\x09* Whether we teleport the physics state (if physics collision is enabled for this object).\n\x09* If true, physics velocity for this object is unchanged (so ragdoll parts are not affected by change in location).\n\x09* If false, physics velocity is updated based on the change in position (affecting ragdoll parts).\n\x09* If CCD is on and not teleporting, this will affect objects along the entire sweep volume.\n\x09*/" },
		{ "ModuleRelativePath", "Private/HandDriverController.h" },
		{ "ToolTip", "Whether we teleport the physics state (if physics collision is enabled for this object).\nIf true, physics velocity for this object is unchanged (so ragdoll parts are not affected by change in location).\nIf false, physics velocity is updated based on the change in position (affecting ragdoll parts).\nIf CCD is on and not teleporting, this will affect objects along the entire sweep volume." },
	};
#endif
	void Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bTeleport_SetBit(void* Obj)
	{
		((FHandDriverControllerData*)Obj)->bTeleport = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bTeleport = { "bTeleport", nullptr, (EPropertyFlags)0x0010040000000015, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FHandDriverControllerData), &Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bTeleport_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bTeleport_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bTeleport_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseHandDriver_MetaData[] = {
		{ "Category", "HandDriver" },
		{ "ModuleRelativePath", "Private/HandDriverController.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseHandDriver_SetBit(void* Obj)
	{
		((FHandDriverControllerData*)Obj)->bUseHandDriver = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseHandDriver = { "bUseHandDriver", nullptr, (EPropertyFlags)0x0010040000000015, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FHandDriverControllerData), &Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseHandDriver_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseHandDriver_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseHandDriver_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bWorldTransform,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseLocation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseRotation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseScale,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bSweep,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bTeleport,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::NewProp_bUseHandDriver,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_HandDriver,
		nullptr,
		&NewStructOps,
		"HandDriverControllerData",
		sizeof(FHandDriverControllerData),
		alignof(FHandDriverControllerData),
		Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FHandDriverControllerData()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FHandDriverControllerData_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_HandDriver();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("HandDriverControllerData"), sizeof(FHandDriverControllerData), Get_Z_Construct_UScriptStruct_FHandDriverControllerData_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FHandDriverControllerData_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FHandDriverControllerData_Hash() { return 4133427362U; }
	void UHandDriverController::StaticRegisterNativesUHandDriverController()
	{
	}
	UClass* Z_Construct_UClass_UHandDriverController_NoRegister()
	{
		return UHandDriverController::StaticClass();
	}
	struct Z_Construct_UClass_UHandDriverController_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_EDITORONLY_DATA
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ComponentToControlloer_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ComponentToControlloer;
#endif // WITH_EDITORONLY_DATA
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_HandDriverData_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_HandDriverData;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_EDITORONLY_DATA
#endif // WITH_EDITORONLY_DATA
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UHandDriverController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ULiveLinkControllerBase,
		(UObject* (*)())Z_Construct_UPackage__Script_HandDriver,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandDriverController_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "HandDriverController.h" },
		{ "ModuleRelativePath", "Private/HandDriverController.h" },
	};
#endif
#if WITH_EDITORONLY_DATA
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandDriverController_Statics::NewProp_ComponentToControlloer_MetaData[] = {
		{ "ModuleRelativePath", "Private/HandDriverController.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHandDriverController_Statics::NewProp_ComponentToControlloer = { "ComponentToControlloer", nullptr, (EPropertyFlags)0x0010000820000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandDriverController, ComponentToControlloer_DEPRECATED), Z_Construct_UScriptStruct_FComponentReference, METADATA_PARAMS(Z_Construct_UClass_UHandDriverController_Statics::NewProp_ComponentToControlloer_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandDriverController_Statics::NewProp_ComponentToControlloer_MetaData)) };
#endif // WITH_EDITORONLY_DATA
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHandDriverController_Statics::NewProp_HandDriverData_MetaData[] = {
		{ "Category", "HandDriver" },
		{ "ModuleRelativePath", "Private/HandDriverController.h" },
		{ "ShowOnlyInnerProperties", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHandDriverController_Statics::NewProp_HandDriverData = { "HandDriverData", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHandDriverController, HandDriverData), Z_Construct_UScriptStruct_FHandDriverControllerData, METADATA_PARAMS(Z_Construct_UClass_UHandDriverController_Statics::NewProp_HandDriverData_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHandDriverController_Statics::NewProp_HandDriverData_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UHandDriverController_Statics::PropPointers[] = {
#if WITH_EDITORONLY_DATA
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandDriverController_Statics::NewProp_ComponentToControlloer,
#endif // WITH_EDITORONLY_DATA
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHandDriverController_Statics::NewProp_HandDriverData,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UHandDriverController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHandDriverController>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UHandDriverController_Statics::ClassParams = {
		&UHandDriverController::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UHandDriverController_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UHandDriverController_Statics::PropPointers),
		0,
		0x000010A0u,
		METADATA_PARAMS(Z_Construct_UClass_UHandDriverController_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UHandDriverController_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UHandDriverController()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UHandDriverController_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UHandDriverController, 3188335760);
	template<> HANDDRIVER_API UClass* StaticClass<UHandDriverController>()
	{
		return UHandDriverController::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UHandDriverController(Z_Construct_UClass_UHandDriverController, &UHandDriverController::StaticClass, TEXT("/Script/HandDriver"), TEXT("UHandDriverController"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UHandDriverController);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
