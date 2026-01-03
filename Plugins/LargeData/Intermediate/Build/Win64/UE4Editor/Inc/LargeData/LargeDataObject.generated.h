// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"
#include "Net/Core/PushModel/PushModelMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef LARGEDATA_LargeDataObject_generated_h
#error "LargeDataObject.generated.h already included, missing '#pragma once' in LargeDataObject.h"
#endif
#define LARGEDATA_LargeDataObject_generated_h

#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_29_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLargeChunkArray_Statics; \
	LARGEDATA_API static class UScriptStruct* StaticStruct(); \
	typedef FFastArraySerializer Super;


template<> LARGEDATA_API UScriptStruct* StaticStruct<struct FLargeChunkArray>();

#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_13_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLargeDataChunk_Statics; \
	LARGEDATA_API static class UScriptStruct* StaticStruct(); \
	typedef FFastArraySerializerItem Super;


template<> LARGEDATA_API UScriptStruct* StaticStruct<struct FLargeDataChunk>();

#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_51_SPARSE_DATA
#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_51_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnRep_ReplicatedChunks); \
	DECLARE_FUNCTION(execApplyChunks); \
	DECLARE_FUNCTION(execBuildChunks);


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_51_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnRep_ReplicatedChunks); \
	DECLARE_FUNCTION(execApplyChunks); \
	DECLARE_FUNCTION(execBuildChunks);


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_51_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULargeDataObject(); \
	friend struct Z_Construct_UClass_ULargeDataObject_Statics; \
public: \
	DECLARE_CLASS(ULargeDataObject, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LargeData"), NO_API) \
	DECLARE_SERIALIZER(ULargeDataObject) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		ReplicatedChunks=NETFIELD_REP_START, \
		NETFIELD_REP_END=ReplicatedChunks	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override; \
private: \
	REPLICATED_BASE_CLASS(ULargeDataObject) \
public:


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_51_INCLASS \
private: \
	static void StaticRegisterNativesULargeDataObject(); \
	friend struct Z_Construct_UClass_ULargeDataObject_Statics; \
public: \
	DECLARE_CLASS(ULargeDataObject, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LargeData"), NO_API) \
	DECLARE_SERIALIZER(ULargeDataObject) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		ReplicatedChunks=NETFIELD_REP_START, \
		NETFIELD_REP_END=ReplicatedChunks	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override; \
private: \
	REPLICATED_BASE_CLASS(ULargeDataObject) \
public:


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_51_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULargeDataObject(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULargeDataObject) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULargeDataObject); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULargeDataObject); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULargeDataObject(ULargeDataObject&&); \
	NO_API ULargeDataObject(const ULargeDataObject&); \
public:


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_51_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULargeDataObject(ULargeDataObject&&); \
	NO_API ULargeDataObject(const ULargeDataObject&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULargeDataObject); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULargeDataObject); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULargeDataObject)


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_51_PRIVATE_PROPERTY_OFFSET
#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_48_PROLOG
#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_51_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_51_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_51_SPARSE_DATA \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_51_RPC_WRAPPERS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_51_INCLASS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_51_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_51_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_51_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_51_SPARSE_DATA \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_51_RPC_WRAPPERS_NO_PURE_DECLS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_51_INCLASS_NO_PURE_DECLS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h_51_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LARGEDATA_API UClass* StaticClass<class ULargeDataObject>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeDataObject_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
