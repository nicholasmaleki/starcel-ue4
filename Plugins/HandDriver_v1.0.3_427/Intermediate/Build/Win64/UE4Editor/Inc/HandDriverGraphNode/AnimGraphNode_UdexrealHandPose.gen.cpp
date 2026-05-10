// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HandDriverGraphNode/Public/AnimGraphNode_UdexrealHandPose.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAnimGraphNode_UdexrealHandPose() {}
// Cross Module References
	HANDDRIVERGRAPHNODE_API UClass* Z_Construct_UClass_UAnimGraphNode_UdexrealHandPose_NoRegister();
	HANDDRIVERGRAPHNODE_API UClass* Z_Construct_UClass_UAnimGraphNode_UdexrealHandPose();
	ANIMGRAPH_API UClass* Z_Construct_UClass_UAnimGraphNode_Base();
	UPackage* Z_Construct_UPackage__Script_HandDriverGraphNode();
	HANDDRIVER_API UScriptStruct* Z_Construct_UScriptStruct_FAnimNode_UdexrealHandPose();
// End Cross Module References
	void UAnimGraphNode_UdexrealHandPose::StaticRegisterNativesUAnimGraphNode_UdexrealHandPose()
	{
	}
	UClass* Z_Construct_UClass_UAnimGraphNode_UdexrealHandPose_NoRegister()
	{
		return UAnimGraphNode_UdexrealHandPose::StaticClass();
	}
	struct Z_Construct_UClass_UAnimGraphNode_UdexrealHandPose_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Node_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Node;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAnimGraphNode_UdexrealHandPose_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UAnimGraphNode_Base,
		(UObject* (*)())Z_Construct_UPackage__Script_HandDriverGraphNode,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAnimGraphNode_UdexrealHandPose_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "AnimGraphNode_UdexrealHandPose.h" },
		{ "ModuleRelativePath", "Public/AnimGraphNode_UdexrealHandPose.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAnimGraphNode_UdexrealHandPose_Statics::NewProp_Node_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimGraphNode_UdexrealHandPose.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAnimGraphNode_UdexrealHandPose_Statics::NewProp_Node = { "Node", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAnimGraphNode_UdexrealHandPose, Node), Z_Construct_UScriptStruct_FAnimNode_UdexrealHandPose, METADATA_PARAMS(Z_Construct_UClass_UAnimGraphNode_UdexrealHandPose_Statics::NewProp_Node_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAnimGraphNode_UdexrealHandPose_Statics::NewProp_Node_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAnimGraphNode_UdexrealHandPose_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAnimGraphNode_UdexrealHandPose_Statics::NewProp_Node,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAnimGraphNode_UdexrealHandPose_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAnimGraphNode_UdexrealHandPose>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UAnimGraphNode_UdexrealHandPose_Statics::ClassParams = {
		&UAnimGraphNode_UdexrealHandPose::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UAnimGraphNode_UdexrealHandPose_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UAnimGraphNode_UdexrealHandPose_Statics::PropPointers),
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UAnimGraphNode_UdexrealHandPose_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UAnimGraphNode_UdexrealHandPose_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAnimGraphNode_UdexrealHandPose()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAnimGraphNode_UdexrealHandPose_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAnimGraphNode_UdexrealHandPose, 2427067783);
	template<> HANDDRIVERGRAPHNODE_API UClass* StaticClass<UAnimGraphNode_UdexrealHandPose>()
	{
		return UAnimGraphNode_UdexrealHandPose::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAnimGraphNode_UdexrealHandPose(Z_Construct_UClass_UAnimGraphNode_UdexrealHandPose, &UAnimGraphNode_UdexrealHandPose::StaticClass, TEXT("/Script/HandDriverGraphNode"), TEXT("UAnimGraphNode_UdexrealHandPose"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAnimGraphNode_UdexrealHandPose);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
