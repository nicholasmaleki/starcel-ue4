// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef LARGEDATA_LargeTensor_generated_h
#error "LargeTensor.generated.h already included, missing '#pragma once' in LargeTensor.h"
#endif
#define LARGEDATA_LargeTensor_generated_h

#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h_17_SPARSE_DATA
#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h_17_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execUpdateRegion);


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execUpdateRegion);


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULargeTensor(); \
	friend struct Z_Construct_UClass_ULargeTensor_Statics; \
public: \
	DECLARE_CLASS(ULargeTensor, ULargeDataObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LargeData"), NO_API) \
	DECLARE_SERIALIZER(ULargeTensor) \
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		RegionUpdates=NETFIELD_REP_START, \
		NETFIELD_REP_END=RegionUpdates	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h_17_INCLASS \
private: \
	static void StaticRegisterNativesULargeTensor(); \
	friend struct Z_Construct_UClass_ULargeTensor_Statics; \
public: \
	DECLARE_CLASS(ULargeTensor, ULargeDataObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LargeData"), NO_API) \
	DECLARE_SERIALIZER(ULargeTensor) \
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		RegionUpdates=NETFIELD_REP_START, \
		NETFIELD_REP_END=RegionUpdates	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h_17_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULargeTensor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULargeTensor) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULargeTensor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULargeTensor); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULargeTensor(ULargeTensor&&); \
	NO_API ULargeTensor(const ULargeTensor&); \
public:


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h_17_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULargeTensor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULargeTensor(ULargeTensor&&); \
	NO_API ULargeTensor(const ULargeTensor&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULargeTensor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULargeTensor); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULargeTensor)


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h_17_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__RegionUpdates() { return STRUCT_OFFSET(ULargeTensor, RegionUpdates); }


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h_14_PROLOG
#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h_17_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h_17_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h_17_SPARSE_DATA \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h_17_RPC_WRAPPERS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h_17_INCLASS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h_17_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h_17_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h_17_SPARSE_DATA \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h_17_INCLASS_NO_PURE_DECLS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LARGEDATA_API UClass* StaticClass<class ULargeTensor>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeTensor_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
