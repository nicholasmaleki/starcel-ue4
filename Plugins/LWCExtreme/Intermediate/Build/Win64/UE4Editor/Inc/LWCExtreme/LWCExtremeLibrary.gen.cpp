// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LWCExtreme/Public/LWCExtremeLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLWCExtremeLibrary() {}
// Cross Module References
	LWCEXTREME_API UClass* Z_Construct_UClass_ULWCExtremeLibrary_NoRegister();
	LWCEXTREME_API UClass* Z_Construct_UClass_ULWCExtremeLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_LWCExtreme();
	LWCEXTREME_API UScriptStruct* Z_Construct_UScriptStruct_FHybridNumber();
	LWCEXTREME_API UScriptStruct* Z_Construct_UScriptStruct_FHybridQuaternion();
	LWCEXTREME_API UScriptStruct* Z_Construct_UScriptStruct_FHybridVector();
	LWCEXTREME_API UScriptStruct* Z_Construct_UScriptStruct_FHybridTransform();
// End Cross Module References
	DEFINE_FUNCTION(ULWCExtremeLibrary::execTransformGetScale)
	{
		P_GET_STRUCT_REF(FHybridTransform,Z_Param_Out_T);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridVector*)Z_Param__Result=ULWCExtremeLibrary::TransformGetScale(Z_Param_Out_T);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execTransformGetRotation)
	{
		P_GET_STRUCT_REF(FHybridTransform,Z_Param_Out_T);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridQuaternion*)Z_Param__Result=ULWCExtremeLibrary::TransformGetRotation(Z_Param_Out_T);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execTransformGetLocation)
	{
		P_GET_STRUCT_REF(FHybridTransform,Z_Param_Out_T);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridVector*)Z_Param__Result=ULWCExtremeLibrary::TransformGetLocation(Z_Param_Out_T);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execTransformVector)
	{
		P_GET_STRUCT_REF(FHybridTransform,Z_Param_Out_T);
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_Vec);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridVector*)Z_Param__Result=ULWCExtremeLibrary::TransformVector(Z_Param_Out_T,Z_Param_Out_Vec);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execTransformPosition)
	{
		P_GET_STRUCT_REF(FHybridTransform,Z_Param_Out_T);
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_Point);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridVector*)Z_Param__Result=ULWCExtremeLibrary::TransformPosition(Z_Param_Out_T,Z_Param_Out_Point);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execTransformInverse)
	{
		P_GET_STRUCT_REF(FHybridTransform,Z_Param_Out_T);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridTransform*)Z_Param__Result=ULWCExtremeLibrary::TransformInverse(Z_Param_Out_T);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execTransformMultiply)
	{
		P_GET_STRUCT_REF(FHybridTransform,Z_Param_Out_A);
		P_GET_STRUCT_REF(FHybridTransform,Z_Param_Out_B);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridTransform*)Z_Param__Result=ULWCExtremeLibrary::TransformMultiply(Z_Param_Out_A,Z_Param_Out_B);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execQuatRotateVector)
	{
		P_GET_STRUCT_REF(FHybridQuaternion,Z_Param_Out_Quat);
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_Vec);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridVector*)Z_Param__Result=ULWCExtremeLibrary::QuatRotateVector(Z_Param_Out_Quat,Z_Param_Out_Vec);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execQuatSlerp)
	{
		P_GET_STRUCT_REF(FHybridQuaternion,Z_Param_Out_From);
		P_GET_STRUCT_REF(FHybridQuaternion,Z_Param_Out_To);
		P_GET_STRUCT_REF(FHybridNumber,Z_Param_Out_Alpha);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridQuaternion*)Z_Param__Result=ULWCExtremeLibrary::QuatSlerp(Z_Param_Out_From,Z_Param_Out_To,Z_Param_Out_Alpha);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execQuatInverse)
	{
		P_GET_STRUCT_REF(FHybridQuaternion,Z_Param_Out_Quat);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridQuaternion*)Z_Param__Result=ULWCExtremeLibrary::QuatInverse(Z_Param_Out_Quat);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execQuatConjugate)
	{
		P_GET_STRUCT_REF(FHybridQuaternion,Z_Param_Out_Quat);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridQuaternion*)Z_Param__Result=ULWCExtremeLibrary::QuatConjugate(Z_Param_Out_Quat);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execQuatNormalize)
	{
		P_GET_STRUCT_REF(FHybridQuaternion,Z_Param_Out_Quat);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridQuaternion*)Z_Param__Result=ULWCExtremeLibrary::QuatNormalize(Z_Param_Out_Quat);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execQuatScalarMultiply)
	{
		P_GET_STRUCT_REF(FHybridQuaternion,Z_Param_Out_Quat);
		P_GET_STRUCT_REF(FHybridNumber,Z_Param_Out_Scalar);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridQuaternion*)Z_Param__Result=ULWCExtremeLibrary::QuatScalarMultiply(Z_Param_Out_Quat,Z_Param_Out_Scalar);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execQuatSubtract)
	{
		P_GET_STRUCT_REF(FHybridQuaternion,Z_Param_Out_A);
		P_GET_STRUCT_REF(FHybridQuaternion,Z_Param_Out_B);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridQuaternion*)Z_Param__Result=ULWCExtremeLibrary::QuatSubtract(Z_Param_Out_A,Z_Param_Out_B);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execQuatAdd)
	{
		P_GET_STRUCT_REF(FHybridQuaternion,Z_Param_Out_A);
		P_GET_STRUCT_REF(FHybridQuaternion,Z_Param_Out_B);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridQuaternion*)Z_Param__Result=ULWCExtremeLibrary::QuatAdd(Z_Param_Out_A,Z_Param_Out_B);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execQuatMultiply)
	{
		P_GET_STRUCT_REF(FHybridQuaternion,Z_Param_Out_A);
		P_GET_STRUCT_REF(FHybridQuaternion,Z_Param_Out_B);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridQuaternion*)Z_Param__Result=ULWCExtremeLibrary::QuatMultiply(Z_Param_Out_A,Z_Param_Out_B);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execVectorProjectOn)
	{
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_Vec);
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_Target);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridVector*)Z_Param__Result=ULWCExtremeLibrary::VectorProjectOn(Z_Param_Out_Vec,Z_Param_Out_Target);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execVectorDistanceSquared)
	{
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_A);
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_B);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridNumber*)Z_Param__Result=ULWCExtremeLibrary::VectorDistanceSquared(Z_Param_Out_A,Z_Param_Out_B);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execVectorDistance)
	{
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_A);
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_B);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridNumber*)Z_Param__Result=ULWCExtremeLibrary::VectorDistance(Z_Param_Out_A,Z_Param_Out_B);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execVectorLerp)
	{
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_A);
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_B);
		P_GET_STRUCT_REF(FHybridNumber,Z_Param_Out_Alpha);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridVector*)Z_Param__Result=ULWCExtremeLibrary::VectorLerp(Z_Param_Out_A,Z_Param_Out_B,Z_Param_Out_Alpha);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execVectorNormalize)
	{
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_Vec);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridVector*)Z_Param__Result=ULWCExtremeLibrary::VectorNormalize(Z_Param_Out_Vec);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execVectorSize)
	{
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_Vec);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridNumber*)Z_Param__Result=ULWCExtremeLibrary::VectorSize(Z_Param_Out_Vec);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execVectorCombine)
	{
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_A);
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_B);
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_C);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridVector*)Z_Param__Result=ULWCExtremeLibrary::VectorCombine(Z_Param_Out_A,Z_Param_Out_B,Z_Param_Out_C);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execVectorComponentScale)
	{
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_Vec);
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_ScaleVec);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridVector*)Z_Param__Result=ULWCExtremeLibrary::VectorComponentScale(Z_Param_Out_Vec,Z_Param_Out_ScaleVec);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execVectorScale)
	{
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_Vec);
		P_GET_STRUCT_REF(FHybridNumber,Z_Param_Out_Scalar);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridVector*)Z_Param__Result=ULWCExtremeLibrary::VectorScale(Z_Param_Out_Vec,Z_Param_Out_Scalar);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execVectorSubtract)
	{
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_A);
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_B);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridVector*)Z_Param__Result=ULWCExtremeLibrary::VectorSubtract(Z_Param_Out_A,Z_Param_Out_B);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execVectorAdd)
	{
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_A);
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_B);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridVector*)Z_Param__Result=ULWCExtremeLibrary::VectorAdd(Z_Param_Out_A,Z_Param_Out_B);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execVectorCross)
	{
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_A);
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_B);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridVector*)Z_Param__Result=ULWCExtremeLibrary::VectorCross(Z_Param_Out_A,Z_Param_Out_B);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execVectorDot)
	{
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_A);
		P_GET_STRUCT_REF(FHybridVector,Z_Param_Out_B);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridNumber*)Z_Param__Result=ULWCExtremeLibrary::VectorDot(Z_Param_Out_A,Z_Param_Out_B);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execTan)
	{
		P_GET_STRUCT_REF(FHybridNumber,Z_Param_Out_Num);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridNumber*)Z_Param__Result=ULWCExtremeLibrary::Tan(Z_Param_Out_Num);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execCos)
	{
		P_GET_STRUCT_REF(FHybridNumber,Z_Param_Out_Num);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridNumber*)Z_Param__Result=ULWCExtremeLibrary::Cos(Z_Param_Out_Num);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execSin)
	{
		P_GET_STRUCT_REF(FHybridNumber,Z_Param_Out_Num);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridNumber*)Z_Param__Result=ULWCExtremeLibrary::Sin(Z_Param_Out_Num);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execExp)
	{
		P_GET_STRUCT_REF(FHybridNumber,Z_Param_Out_Num);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridNumber*)Z_Param__Result=ULWCExtremeLibrary::Exp(Z_Param_Out_Num);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execLn)
	{
		P_GET_STRUCT_REF(FHybridNumber,Z_Param_Out_Num);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridNumber*)Z_Param__Result=ULWCExtremeLibrary::Ln(Z_Param_Out_Num);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULWCExtremeLibrary::execSqrt)
	{
		P_GET_STRUCT_REF(FHybridNumber,Z_Param_Out_Num);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FHybridNumber*)Z_Param__Result=ULWCExtremeLibrary::Sqrt(Z_Param_Out_Num);
		P_NATIVE_END;
	}
	void ULWCExtremeLibrary::StaticRegisterNativesULWCExtremeLibrary()
	{
		UClass* Class = ULWCExtremeLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "Cos", &ULWCExtremeLibrary::execCos },
			{ "Exp", &ULWCExtremeLibrary::execExp },
			{ "Ln", &ULWCExtremeLibrary::execLn },
			{ "QuatAdd", &ULWCExtremeLibrary::execQuatAdd },
			{ "QuatConjugate", &ULWCExtremeLibrary::execQuatConjugate },
			{ "QuatInverse", &ULWCExtremeLibrary::execQuatInverse },
			{ "QuatMultiply", &ULWCExtremeLibrary::execQuatMultiply },
			{ "QuatNormalize", &ULWCExtremeLibrary::execQuatNormalize },
			{ "QuatRotateVector", &ULWCExtremeLibrary::execQuatRotateVector },
			{ "QuatScalarMultiply", &ULWCExtremeLibrary::execQuatScalarMultiply },
			{ "QuatSlerp", &ULWCExtremeLibrary::execQuatSlerp },
			{ "QuatSubtract", &ULWCExtremeLibrary::execQuatSubtract },
			{ "Sin", &ULWCExtremeLibrary::execSin },
			{ "Sqrt", &ULWCExtremeLibrary::execSqrt },
			{ "Tan", &ULWCExtremeLibrary::execTan },
			{ "TransformGetLocation", &ULWCExtremeLibrary::execTransformGetLocation },
			{ "TransformGetRotation", &ULWCExtremeLibrary::execTransformGetRotation },
			{ "TransformGetScale", &ULWCExtremeLibrary::execTransformGetScale },
			{ "TransformInverse", &ULWCExtremeLibrary::execTransformInverse },
			{ "TransformMultiply", &ULWCExtremeLibrary::execTransformMultiply },
			{ "TransformPosition", &ULWCExtremeLibrary::execTransformPosition },
			{ "TransformVector", &ULWCExtremeLibrary::execTransformVector },
			{ "VectorAdd", &ULWCExtremeLibrary::execVectorAdd },
			{ "VectorCombine", &ULWCExtremeLibrary::execVectorCombine },
			{ "VectorComponentScale", &ULWCExtremeLibrary::execVectorComponentScale },
			{ "VectorCross", &ULWCExtremeLibrary::execVectorCross },
			{ "VectorDistance", &ULWCExtremeLibrary::execVectorDistance },
			{ "VectorDistanceSquared", &ULWCExtremeLibrary::execVectorDistanceSquared },
			{ "VectorDot", &ULWCExtremeLibrary::execVectorDot },
			{ "VectorLerp", &ULWCExtremeLibrary::execVectorLerp },
			{ "VectorNormalize", &ULWCExtremeLibrary::execVectorNormalize },
			{ "VectorProjectOn", &ULWCExtremeLibrary::execVectorProjectOn },
			{ "VectorScale", &ULWCExtremeLibrary::execVectorScale },
			{ "VectorSize", &ULWCExtremeLibrary::execVectorSize },
			{ "VectorSubtract", &ULWCExtremeLibrary::execVectorSubtract },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_Cos_Statics
	{
		struct LWCExtremeLibrary_eventCos_Parms
		{
			FHybridNumber Num;
			FHybridNumber ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Num_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Num;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_Cos_Statics::NewProp_Num_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_Cos_Statics::NewProp_Num = { "Num", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventCos_Parms, Num), Z_Construct_UScriptStruct_FHybridNumber, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_Cos_Statics::NewProp_Num_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_Cos_Statics::NewProp_Num_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_Cos_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventCos_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridNumber, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_Cos_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_Cos_Statics::NewProp_Num,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_Cos_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_Cos_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Math" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_Cos_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "Cos", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventCos_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_Cos_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_Cos_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_Cos_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_Cos_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_Cos()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_Cos_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_Exp_Statics
	{
		struct LWCExtremeLibrary_eventExp_Parms
		{
			FHybridNumber Num;
			FHybridNumber ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Num_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Num;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_Exp_Statics::NewProp_Num_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_Exp_Statics::NewProp_Num = { "Num", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventExp_Parms, Num), Z_Construct_UScriptStruct_FHybridNumber, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_Exp_Statics::NewProp_Num_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_Exp_Statics::NewProp_Num_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_Exp_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventExp_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridNumber, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_Exp_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_Exp_Statics::NewProp_Num,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_Exp_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_Exp_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Math" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_Exp_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "Exp", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventExp_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_Exp_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_Exp_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_Exp_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_Exp_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_Exp()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_Exp_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_Ln_Statics
	{
		struct LWCExtremeLibrary_eventLn_Parms
		{
			FHybridNumber Num;
			FHybridNumber ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Num_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Num;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_Ln_Statics::NewProp_Num_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_Ln_Statics::NewProp_Num = { "Num", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventLn_Parms, Num), Z_Construct_UScriptStruct_FHybridNumber, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_Ln_Statics::NewProp_Num_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_Ln_Statics::NewProp_Num_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_Ln_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventLn_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridNumber, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_Ln_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_Ln_Statics::NewProp_Num,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_Ln_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_Ln_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Math" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_Ln_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "Ln", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventLn_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_Ln_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_Ln_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_Ln_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_Ln_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_Ln()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_Ln_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd_Statics
	{
		struct LWCExtremeLibrary_eventQuatAdd_Parms
		{
			FHybridQuaternion A;
			FHybridQuaternion B;
			FHybridQuaternion ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_A_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_A;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_B_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_B;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd_Statics::NewProp_A_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd_Statics::NewProp_A = { "A", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatAdd_Parms, A), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd_Statics::NewProp_A_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd_Statics::NewProp_A_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd_Statics::NewProp_B_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd_Statics::NewProp_B = { "B", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatAdd_Parms, B), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd_Statics::NewProp_B_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd_Statics::NewProp_B_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatAdd_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd_Statics::NewProp_A,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd_Statics::NewProp_B,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Quaternion" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "QuatAdd", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventQuatAdd_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_QuatConjugate_Statics
	{
		struct LWCExtremeLibrary_eventQuatConjugate_Parms
		{
			FHybridQuaternion Quat;
			FHybridQuaternion ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Quat_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Quat;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatConjugate_Statics::NewProp_Quat_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatConjugate_Statics::NewProp_Quat = { "Quat", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatConjugate_Parms, Quat), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatConjugate_Statics::NewProp_Quat_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatConjugate_Statics::NewProp_Quat_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatConjugate_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatConjugate_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_QuatConjugate_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatConjugate_Statics::NewProp_Quat,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatConjugate_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatConjugate_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Quaternion" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatConjugate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "QuatConjugate", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventQuatConjugate_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_QuatConjugate_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatConjugate_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatConjugate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatConjugate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_QuatConjugate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_QuatConjugate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_QuatInverse_Statics
	{
		struct LWCExtremeLibrary_eventQuatInverse_Parms
		{
			FHybridQuaternion Quat;
			FHybridQuaternion ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Quat_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Quat;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatInverse_Statics::NewProp_Quat_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatInverse_Statics::NewProp_Quat = { "Quat", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatInverse_Parms, Quat), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatInverse_Statics::NewProp_Quat_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatInverse_Statics::NewProp_Quat_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatInverse_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatInverse_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_QuatInverse_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatInverse_Statics::NewProp_Quat,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatInverse_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatInverse_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Quaternion" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatInverse_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "QuatInverse", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventQuatInverse_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_QuatInverse_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatInverse_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatInverse_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatInverse_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_QuatInverse()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_QuatInverse_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply_Statics
	{
		struct LWCExtremeLibrary_eventQuatMultiply_Parms
		{
			FHybridQuaternion A;
			FHybridQuaternion B;
			FHybridQuaternion ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_A_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_A;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_B_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_B;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply_Statics::NewProp_A_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply_Statics::NewProp_A = { "A", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatMultiply_Parms, A), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply_Statics::NewProp_A_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply_Statics::NewProp_A_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply_Statics::NewProp_B_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply_Statics::NewProp_B = { "B", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatMultiply_Parms, B), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply_Statics::NewProp_B_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply_Statics::NewProp_B_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatMultiply_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply_Statics::NewProp_A,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply_Statics::NewProp_B,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Quaternion" },
		{ "Comment", "// -------------------------------\n// FHybridQuaternion math\n// -------------------------------\n" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
		{ "ToolTip", "FHybridQuaternion math" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "QuatMultiply", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventQuatMultiply_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_QuatNormalize_Statics
	{
		struct LWCExtremeLibrary_eventQuatNormalize_Parms
		{
			FHybridQuaternion Quat;
			FHybridQuaternion ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Quat_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Quat;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatNormalize_Statics::NewProp_Quat_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatNormalize_Statics::NewProp_Quat = { "Quat", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatNormalize_Parms, Quat), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatNormalize_Statics::NewProp_Quat_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatNormalize_Statics::NewProp_Quat_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatNormalize_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatNormalize_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_QuatNormalize_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatNormalize_Statics::NewProp_Quat,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatNormalize_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatNormalize_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Quaternion" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatNormalize_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "QuatNormalize", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventQuatNormalize_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_QuatNormalize_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatNormalize_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatNormalize_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatNormalize_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_QuatNormalize()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_QuatNormalize_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector_Statics
	{
		struct LWCExtremeLibrary_eventQuatRotateVector_Parms
		{
			FHybridQuaternion Quat;
			FHybridVector Vec;
			FHybridVector ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Quat_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Quat;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Vec_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Vec;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector_Statics::NewProp_Quat_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector_Statics::NewProp_Quat = { "Quat", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatRotateVector_Parms, Quat), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector_Statics::NewProp_Quat_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector_Statics::NewProp_Quat_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector_Statics::NewProp_Vec_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector_Statics::NewProp_Vec = { "Vec", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatRotateVector_Parms, Vec), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector_Statics::NewProp_Vec_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector_Statics::NewProp_Vec_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatRotateVector_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector_Statics::NewProp_Quat,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector_Statics::NewProp_Vec,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Quaternion" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "QuatRotateVector", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventQuatRotateVector_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply_Statics
	{
		struct LWCExtremeLibrary_eventQuatScalarMultiply_Parms
		{
			FHybridQuaternion Quat;
			FHybridNumber Scalar;
			FHybridQuaternion ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Quat_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Quat;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Scalar_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Scalar;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply_Statics::NewProp_Quat_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply_Statics::NewProp_Quat = { "Quat", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatScalarMultiply_Parms, Quat), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply_Statics::NewProp_Quat_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply_Statics::NewProp_Quat_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply_Statics::NewProp_Scalar_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply_Statics::NewProp_Scalar = { "Scalar", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatScalarMultiply_Parms, Scalar), Z_Construct_UScriptStruct_FHybridNumber, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply_Statics::NewProp_Scalar_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply_Statics::NewProp_Scalar_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatScalarMultiply_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply_Statics::NewProp_Quat,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply_Statics::NewProp_Scalar,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Quaternion" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "QuatScalarMultiply", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventQuatScalarMultiply_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics
	{
		struct LWCExtremeLibrary_eventQuatSlerp_Parms
		{
			FHybridQuaternion From;
			FHybridQuaternion To;
			FHybridNumber Alpha;
			FHybridQuaternion ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_From_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_From;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_To_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_To;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Alpha_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Alpha;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::NewProp_From_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::NewProp_From = { "From", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatSlerp_Parms, From), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::NewProp_From_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::NewProp_From_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::NewProp_To_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::NewProp_To = { "To", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatSlerp_Parms, To), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::NewProp_To_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::NewProp_To_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::NewProp_Alpha_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::NewProp_Alpha = { "Alpha", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatSlerp_Parms, Alpha), Z_Construct_UScriptStruct_FHybridNumber, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::NewProp_Alpha_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::NewProp_Alpha_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatSlerp_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::NewProp_From,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::NewProp_To,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::NewProp_Alpha,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Quaternion" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "QuatSlerp", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventQuatSlerp_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract_Statics
	{
		struct LWCExtremeLibrary_eventQuatSubtract_Parms
		{
			FHybridQuaternion A;
			FHybridQuaternion B;
			FHybridQuaternion ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_A_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_A;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_B_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_B;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract_Statics::NewProp_A_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract_Statics::NewProp_A = { "A", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatSubtract_Parms, A), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract_Statics::NewProp_A_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract_Statics::NewProp_A_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract_Statics::NewProp_B_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract_Statics::NewProp_B = { "B", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatSubtract_Parms, B), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract_Statics::NewProp_B_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract_Statics::NewProp_B_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventQuatSubtract_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract_Statics::NewProp_A,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract_Statics::NewProp_B,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Quaternion" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "QuatSubtract", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventQuatSubtract_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_Sin_Statics
	{
		struct LWCExtremeLibrary_eventSin_Parms
		{
			FHybridNumber Num;
			FHybridNumber ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Num_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Num;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_Sin_Statics::NewProp_Num_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_Sin_Statics::NewProp_Num = { "Num", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventSin_Parms, Num), Z_Construct_UScriptStruct_FHybridNumber, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_Sin_Statics::NewProp_Num_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_Sin_Statics::NewProp_Num_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_Sin_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventSin_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridNumber, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_Sin_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_Sin_Statics::NewProp_Num,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_Sin_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_Sin_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Math" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_Sin_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "Sin", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventSin_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_Sin_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_Sin_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_Sin_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_Sin_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_Sin()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_Sin_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_Sqrt_Statics
	{
		struct LWCExtremeLibrary_eventSqrt_Parms
		{
			FHybridNumber Num;
			FHybridNumber ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Num_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Num;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_Sqrt_Statics::NewProp_Num_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_Sqrt_Statics::NewProp_Num = { "Num", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventSqrt_Parms, Num), Z_Construct_UScriptStruct_FHybridNumber, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_Sqrt_Statics::NewProp_Num_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_Sqrt_Statics::NewProp_Num_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_Sqrt_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventSqrt_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridNumber, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_Sqrt_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_Sqrt_Statics::NewProp_Num,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_Sqrt_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_Sqrt_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Math" },
		{ "Comment", "// -------------------------------\n// FHybridNumber math\n// -------------------------------\n" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
		{ "ToolTip", "FHybridNumber math" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_Sqrt_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "Sqrt", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventSqrt_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_Sqrt_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_Sqrt_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_Sqrt_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_Sqrt_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_Sqrt()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_Sqrt_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_Tan_Statics
	{
		struct LWCExtremeLibrary_eventTan_Parms
		{
			FHybridNumber Num;
			FHybridNumber ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Num_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Num;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_Tan_Statics::NewProp_Num_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_Tan_Statics::NewProp_Num = { "Num", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventTan_Parms, Num), Z_Construct_UScriptStruct_FHybridNumber, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_Tan_Statics::NewProp_Num_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_Tan_Statics::NewProp_Num_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_Tan_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventTan_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridNumber, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_Tan_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_Tan_Statics::NewProp_Num,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_Tan_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_Tan_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Math" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_Tan_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "Tan", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventTan_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_Tan_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_Tan_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_Tan_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_Tan_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_Tan()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_Tan_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetLocation_Statics
	{
		struct LWCExtremeLibrary_eventTransformGetLocation_Parms
		{
			FHybridTransform T;
			FHybridVector ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_T_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_T;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetLocation_Statics::NewProp_T_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetLocation_Statics::NewProp_T = { "T", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventTransformGetLocation_Parms, T), Z_Construct_UScriptStruct_FHybridTransform, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetLocation_Statics::NewProp_T_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetLocation_Statics::NewProp_T_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventTransformGetLocation_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetLocation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetLocation_Statics::NewProp_T,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetLocation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetLocation_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Transform" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "TransformGetLocation", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventTransformGetLocation_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetLocation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetLocation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetLocation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetLocation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetRotation_Statics
	{
		struct LWCExtremeLibrary_eventTransformGetRotation_Parms
		{
			FHybridTransform T;
			FHybridQuaternion ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_T_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_T;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetRotation_Statics::NewProp_T_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetRotation_Statics::NewProp_T = { "T", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventTransformGetRotation_Parms, T), Z_Construct_UScriptStruct_FHybridTransform, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetRotation_Statics::NewProp_T_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetRotation_Statics::NewProp_T_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetRotation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventTransformGetRotation_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridQuaternion, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetRotation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetRotation_Statics::NewProp_T,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetRotation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetRotation_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Transform" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetRotation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "TransformGetRotation", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventTransformGetRotation_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetRotation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetRotation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetRotation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetRotation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetRotation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetRotation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetScale_Statics
	{
		struct LWCExtremeLibrary_eventTransformGetScale_Parms
		{
			FHybridTransform T;
			FHybridVector ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_T_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_T;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetScale_Statics::NewProp_T_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetScale_Statics::NewProp_T = { "T", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventTransformGetScale_Parms, T), Z_Construct_UScriptStruct_FHybridTransform, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetScale_Statics::NewProp_T_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetScale_Statics::NewProp_T_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetScale_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventTransformGetScale_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetScale_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetScale_Statics::NewProp_T,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetScale_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetScale_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Transform" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetScale_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "TransformGetScale", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventTransformGetScale_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetScale_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetScale_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetScale_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetScale_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetScale()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetScale_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_TransformInverse_Statics
	{
		struct LWCExtremeLibrary_eventTransformInverse_Parms
		{
			FHybridTransform T;
			FHybridTransform ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_T_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_T;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_TransformInverse_Statics::NewProp_T_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformInverse_Statics::NewProp_T = { "T", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventTransformInverse_Parms, T), Z_Construct_UScriptStruct_FHybridTransform, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_TransformInverse_Statics::NewProp_T_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformInverse_Statics::NewProp_T_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformInverse_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventTransformInverse_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridTransform, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_TransformInverse_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_TransformInverse_Statics::NewProp_T,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_TransformInverse_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_TransformInverse_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Transform" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformInverse_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "TransformInverse", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventTransformInverse_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_TransformInverse_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformInverse_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_TransformInverse_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformInverse_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_TransformInverse()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_TransformInverse_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply_Statics
	{
		struct LWCExtremeLibrary_eventTransformMultiply_Parms
		{
			FHybridTransform A;
			FHybridTransform B;
			FHybridTransform ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_A_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_A;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_B_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_B;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply_Statics::NewProp_A_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply_Statics::NewProp_A = { "A", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventTransformMultiply_Parms, A), Z_Construct_UScriptStruct_FHybridTransform, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply_Statics::NewProp_A_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply_Statics::NewProp_A_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply_Statics::NewProp_B_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply_Statics::NewProp_B = { "B", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventTransformMultiply_Parms, B), Z_Construct_UScriptStruct_FHybridTransform, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply_Statics::NewProp_B_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply_Statics::NewProp_B_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventTransformMultiply_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridTransform, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply_Statics::NewProp_A,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply_Statics::NewProp_B,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Transform" },
		{ "Comment", "// -------------------------------\n// FHybridTransform math\n// -------------------------------\n" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
		{ "ToolTip", "FHybridTransform math" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "TransformMultiply", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventTransformMultiply_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition_Statics
	{
		struct LWCExtremeLibrary_eventTransformPosition_Parms
		{
			FHybridTransform T;
			FHybridVector Point;
			FHybridVector ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_T_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_T;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Point_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Point;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition_Statics::NewProp_T_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition_Statics::NewProp_T = { "T", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventTransformPosition_Parms, T), Z_Construct_UScriptStruct_FHybridTransform, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition_Statics::NewProp_T_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition_Statics::NewProp_T_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition_Statics::NewProp_Point_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition_Statics::NewProp_Point = { "Point", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventTransformPosition_Parms, Point), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition_Statics::NewProp_Point_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition_Statics::NewProp_Point_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventTransformPosition_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition_Statics::NewProp_T,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition_Statics::NewProp_Point,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Transform" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "TransformPosition", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventTransformPosition_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector_Statics
	{
		struct LWCExtremeLibrary_eventTransformVector_Parms
		{
			FHybridTransform T;
			FHybridVector Vec;
			FHybridVector ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_T_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_T;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Vec_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Vec;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector_Statics::NewProp_T_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector_Statics::NewProp_T = { "T", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventTransformVector_Parms, T), Z_Construct_UScriptStruct_FHybridTransform, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector_Statics::NewProp_T_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector_Statics::NewProp_T_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector_Statics::NewProp_Vec_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector_Statics::NewProp_Vec = { "Vec", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventTransformVector_Parms, Vec), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector_Statics::NewProp_Vec_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector_Statics::NewProp_Vec_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventTransformVector_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector_Statics::NewProp_T,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector_Statics::NewProp_Vec,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Transform" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "TransformVector", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventTransformVector_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd_Statics
	{
		struct LWCExtremeLibrary_eventVectorAdd_Parms
		{
			FHybridVector A;
			FHybridVector B;
			FHybridVector ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_A_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_A;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_B_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_B;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd_Statics::NewProp_A_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd_Statics::NewProp_A = { "A", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorAdd_Parms, A), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd_Statics::NewProp_A_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd_Statics::NewProp_A_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd_Statics::NewProp_B_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd_Statics::NewProp_B = { "B", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorAdd_Parms, B), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd_Statics::NewProp_B_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd_Statics::NewProp_B_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorAdd_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd_Statics::NewProp_A,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd_Statics::NewProp_B,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Vector" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "VectorAdd", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventVectorAdd_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics
	{
		struct LWCExtremeLibrary_eventVectorCombine_Parms
		{
			FHybridVector A;
			FHybridVector B;
			FHybridVector C;
			FHybridVector ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_A_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_A;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_B_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_B;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_C_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_C;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::NewProp_A_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::NewProp_A = { "A", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorCombine_Parms, A), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::NewProp_A_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::NewProp_A_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::NewProp_B_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::NewProp_B = { "B", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorCombine_Parms, B), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::NewProp_B_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::NewProp_B_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::NewProp_C_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::NewProp_C = { "C", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorCombine_Parms, C), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::NewProp_C_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::NewProp_C_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorCombine_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::NewProp_A,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::NewProp_B,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::NewProp_C,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Vector" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "VectorCombine", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventVectorCombine_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale_Statics
	{
		struct LWCExtremeLibrary_eventVectorComponentScale_Parms
		{
			FHybridVector Vec;
			FHybridVector ScaleVec;
			FHybridVector ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Vec_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Vec;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ScaleVec_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ScaleVec;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale_Statics::NewProp_Vec_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale_Statics::NewProp_Vec = { "Vec", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorComponentScale_Parms, Vec), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale_Statics::NewProp_Vec_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale_Statics::NewProp_Vec_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale_Statics::NewProp_ScaleVec_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale_Statics::NewProp_ScaleVec = { "ScaleVec", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorComponentScale_Parms, ScaleVec), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale_Statics::NewProp_ScaleVec_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale_Statics::NewProp_ScaleVec_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorComponentScale_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale_Statics::NewProp_Vec,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale_Statics::NewProp_ScaleVec,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Vector" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "VectorComponentScale", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventVectorComponentScale_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross_Statics
	{
		struct LWCExtremeLibrary_eventVectorCross_Parms
		{
			FHybridVector A;
			FHybridVector B;
			FHybridVector ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_A_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_A;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_B_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_B;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross_Statics::NewProp_A_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross_Statics::NewProp_A = { "A", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorCross_Parms, A), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross_Statics::NewProp_A_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross_Statics::NewProp_A_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross_Statics::NewProp_B_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross_Statics::NewProp_B = { "B", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorCross_Parms, B), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross_Statics::NewProp_B_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross_Statics::NewProp_B_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorCross_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross_Statics::NewProp_A,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross_Statics::NewProp_B,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Vector" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "VectorCross", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventVectorCross_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance_Statics
	{
		struct LWCExtremeLibrary_eventVectorDistance_Parms
		{
			FHybridVector A;
			FHybridVector B;
			FHybridNumber ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_A_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_A;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_B_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_B;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance_Statics::NewProp_A_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance_Statics::NewProp_A = { "A", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorDistance_Parms, A), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance_Statics::NewProp_A_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance_Statics::NewProp_A_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance_Statics::NewProp_B_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance_Statics::NewProp_B = { "B", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorDistance_Parms, B), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance_Statics::NewProp_B_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance_Statics::NewProp_B_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorDistance_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridNumber, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance_Statics::NewProp_A,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance_Statics::NewProp_B,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Vector" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "VectorDistance", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventVectorDistance_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared_Statics
	{
		struct LWCExtremeLibrary_eventVectorDistanceSquared_Parms
		{
			FHybridVector A;
			FHybridVector B;
			FHybridNumber ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_A_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_A;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_B_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_B;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared_Statics::NewProp_A_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared_Statics::NewProp_A = { "A", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorDistanceSquared_Parms, A), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared_Statics::NewProp_A_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared_Statics::NewProp_A_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared_Statics::NewProp_B_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared_Statics::NewProp_B = { "B", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorDistanceSquared_Parms, B), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared_Statics::NewProp_B_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared_Statics::NewProp_B_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorDistanceSquared_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridNumber, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared_Statics::NewProp_A,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared_Statics::NewProp_B,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Vector" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "VectorDistanceSquared", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventVectorDistanceSquared_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot_Statics
	{
		struct LWCExtremeLibrary_eventVectorDot_Parms
		{
			FHybridVector A;
			FHybridVector B;
			FHybridNumber ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_A_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_A;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_B_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_B;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot_Statics::NewProp_A_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot_Statics::NewProp_A = { "A", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorDot_Parms, A), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot_Statics::NewProp_A_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot_Statics::NewProp_A_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot_Statics::NewProp_B_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot_Statics::NewProp_B = { "B", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorDot_Parms, B), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot_Statics::NewProp_B_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot_Statics::NewProp_B_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorDot_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridNumber, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot_Statics::NewProp_A,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot_Statics::NewProp_B,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Vector" },
		{ "Comment", "// -------------------------------\n// FHybridVector math\n// -------------------------------\n" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
		{ "ToolTip", "FHybridVector math" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "VectorDot", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventVectorDot_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics
	{
		struct LWCExtremeLibrary_eventVectorLerp_Parms
		{
			FHybridVector A;
			FHybridVector B;
			FHybridNumber Alpha;
			FHybridVector ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_A_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_A;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_B_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_B;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Alpha_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Alpha;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::NewProp_A_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::NewProp_A = { "A", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorLerp_Parms, A), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::NewProp_A_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::NewProp_A_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::NewProp_B_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::NewProp_B = { "B", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorLerp_Parms, B), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::NewProp_B_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::NewProp_B_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::NewProp_Alpha_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::NewProp_Alpha = { "Alpha", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorLerp_Parms, Alpha), Z_Construct_UScriptStruct_FHybridNumber, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::NewProp_Alpha_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::NewProp_Alpha_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorLerp_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::NewProp_A,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::NewProp_B,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::NewProp_Alpha,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Vector" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "VectorLerp", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventVectorLerp_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_VectorNormalize_Statics
	{
		struct LWCExtremeLibrary_eventVectorNormalize_Parms
		{
			FHybridVector Vec;
			FHybridVector ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Vec_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Vec;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorNormalize_Statics::NewProp_Vec_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorNormalize_Statics::NewProp_Vec = { "Vec", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorNormalize_Parms, Vec), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorNormalize_Statics::NewProp_Vec_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorNormalize_Statics::NewProp_Vec_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorNormalize_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorNormalize_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_VectorNormalize_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorNormalize_Statics::NewProp_Vec,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorNormalize_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorNormalize_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Vector" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorNormalize_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "VectorNormalize", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventVectorNormalize_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_VectorNormalize_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorNormalize_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorNormalize_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorNormalize_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_VectorNormalize()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_VectorNormalize_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn_Statics
	{
		struct LWCExtremeLibrary_eventVectorProjectOn_Parms
		{
			FHybridVector Vec;
			FHybridVector Target;
			FHybridVector ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Vec_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Vec;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Target_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Target;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn_Statics::NewProp_Vec_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn_Statics::NewProp_Vec = { "Vec", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorProjectOn_Parms, Vec), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn_Statics::NewProp_Vec_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn_Statics::NewProp_Vec_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn_Statics::NewProp_Target_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn_Statics::NewProp_Target = { "Target", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorProjectOn_Parms, Target), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn_Statics::NewProp_Target_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn_Statics::NewProp_Target_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorProjectOn_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn_Statics::NewProp_Vec,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn_Statics::NewProp_Target,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Vector" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "VectorProjectOn", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventVectorProjectOn_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale_Statics
	{
		struct LWCExtremeLibrary_eventVectorScale_Parms
		{
			FHybridVector Vec;
			FHybridNumber Scalar;
			FHybridVector ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Vec_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Vec;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Scalar_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Scalar;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale_Statics::NewProp_Vec_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale_Statics::NewProp_Vec = { "Vec", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorScale_Parms, Vec), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale_Statics::NewProp_Vec_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale_Statics::NewProp_Vec_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale_Statics::NewProp_Scalar_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale_Statics::NewProp_Scalar = { "Scalar", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorScale_Parms, Scalar), Z_Construct_UScriptStruct_FHybridNumber, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale_Statics::NewProp_Scalar_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale_Statics::NewProp_Scalar_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorScale_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale_Statics::NewProp_Vec,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale_Statics::NewProp_Scalar,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Vector" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "VectorScale", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventVectorScale_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_VectorSize_Statics
	{
		struct LWCExtremeLibrary_eventVectorSize_Parms
		{
			FHybridVector Vec;
			FHybridNumber ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Vec_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Vec;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorSize_Statics::NewProp_Vec_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorSize_Statics::NewProp_Vec = { "Vec", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorSize_Parms, Vec), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorSize_Statics::NewProp_Vec_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorSize_Statics::NewProp_Vec_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorSize_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorSize_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridNumber, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_VectorSize_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorSize_Statics::NewProp_Vec,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorSize_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorSize_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Vector" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorSize_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "VectorSize", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventVectorSize_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_VectorSize_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorSize_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorSize_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorSize_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_VectorSize()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_VectorSize_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract_Statics
	{
		struct LWCExtremeLibrary_eventVectorSubtract_Parms
		{
			FHybridVector A;
			FHybridVector B;
			FHybridVector ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_A_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_A;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_B_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_B;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract_Statics::NewProp_A_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract_Statics::NewProp_A = { "A", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorSubtract_Parms, A), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract_Statics::NewProp_A_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract_Statics::NewProp_A_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract_Statics::NewProp_B_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract_Statics::NewProp_B = { "B", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorSubtract_Parms, B), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract_Statics::NewProp_B_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract_Statics::NewProp_B_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LWCExtremeLibrary_eventVectorSubtract_Parms, ReturnValue), Z_Construct_UScriptStruct_FHybridVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract_Statics::NewProp_A,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract_Statics::NewProp_B,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract_Statics::Function_MetaDataParams[] = {
		{ "Category", "LWCExtreme|Vector" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULWCExtremeLibrary, nullptr, "VectorSubtract", nullptr, nullptr, sizeof(LWCExtremeLibrary_eventVectorSubtract_Parms), Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ULWCExtremeLibrary_NoRegister()
	{
		return ULWCExtremeLibrary::StaticClass();
	}
	struct Z_Construct_UClass_ULWCExtremeLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULWCExtremeLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_LWCExtreme,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULWCExtremeLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_Cos, "Cos" }, // 3402965572
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_Exp, "Exp" }, // 2842320784
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_Ln, "Ln" }, // 3414431119
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_QuatAdd, "QuatAdd" }, // 91164176
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_QuatConjugate, "QuatConjugate" }, // 42102968
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_QuatInverse, "QuatInverse" }, // 3033884395
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_QuatMultiply, "QuatMultiply" }, // 2762686730
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_QuatNormalize, "QuatNormalize" }, // 2741256778
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_QuatRotateVector, "QuatRotateVector" }, // 600661490
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_QuatScalarMultiply, "QuatScalarMultiply" }, // 1902587774
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_QuatSlerp, "QuatSlerp" }, // 1819269271
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_QuatSubtract, "QuatSubtract" }, // 1953315351
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_Sin, "Sin" }, // 3932791733
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_Sqrt, "Sqrt" }, // 3593433535
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_Tan, "Tan" }, // 4267515952
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetLocation, "TransformGetLocation" }, // 3719573622
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetRotation, "TransformGetRotation" }, // 734526222
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_TransformGetScale, "TransformGetScale" }, // 425693630
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_TransformInverse, "TransformInverse" }, // 303736327
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_TransformMultiply, "TransformMultiply" }, // 957088923
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_TransformPosition, "TransformPosition" }, // 3667237978
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_TransformVector, "TransformVector" }, // 2639735217
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_VectorAdd, "VectorAdd" }, // 47748045
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_VectorCombine, "VectorCombine" }, // 914640384
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_VectorComponentScale, "VectorComponentScale" }, // 2817737856
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_VectorCross, "VectorCross" }, // 3476964092
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistance, "VectorDistance" }, // 2769011732
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_VectorDistanceSquared, "VectorDistanceSquared" }, // 3983147601
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_VectorDot, "VectorDot" }, // 133207372
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_VectorLerp, "VectorLerp" }, // 1299970232
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_VectorNormalize, "VectorNormalize" }, // 2554811474
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_VectorProjectOn, "VectorProjectOn" }, // 1667326070
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_VectorScale, "VectorScale" }, // 3028283243
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_VectorSize, "VectorSize" }, // 193328545
		{ &Z_Construct_UFunction_ULWCExtremeLibrary_VectorSubtract, "VectorSubtract" }, // 2218548636
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULWCExtremeLibrary_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "LWCExtremeLibrary.h" },
		{ "ModuleRelativePath", "Public/LWCExtremeLibrary.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULWCExtremeLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULWCExtremeLibrary>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULWCExtremeLibrary_Statics::ClassParams = {
		&ULWCExtremeLibrary::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_ULWCExtremeLibrary_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULWCExtremeLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULWCExtremeLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULWCExtremeLibrary_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULWCExtremeLibrary, 2492540013);
	template<> LWCEXTREME_API UClass* StaticClass<ULWCExtremeLibrary>()
	{
		return ULWCExtremeLibrary::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULWCExtremeLibrary(Z_Construct_UClass_ULWCExtremeLibrary, &ULWCExtremeLibrary::StaticClass, TEXT("/Script/LWCExtreme"), TEXT("ULWCExtremeLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULWCExtremeLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
