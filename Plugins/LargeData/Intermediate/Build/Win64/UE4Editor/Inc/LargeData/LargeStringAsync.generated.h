// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef LARGEDATA_LargeStringAsync_generated_h
#error "LargeStringAsync.generated.h already included, missing '#pragma once' in LargeStringAsync.h"
#endif
#define LARGEDATA_LargeStringAsync_generated_h

#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_16_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FByteChunk_Statics; \
	LARGEDATA_API static class UScriptStruct* StaticStruct();


template<> LARGEDATA_API UScriptStruct* StaticStruct<struct FByteChunk>();

#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_8_DELEGATE \
static inline void FOnChunksBuilt_DelegateWrapper(const FMulticastScriptDelegate& OnChunksBuilt) \
{ \
	OnChunksBuilt.ProcessMulticastDelegate<UObject>(NULL); \
}


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_7_DELEGATE \
static inline void FOnLargeStringAsyncReceived_DelegateWrapper(const FMulticastScriptDelegate& OnLargeStringAsyncReceived) \
{ \
	OnLargeStringAsyncReceived.ProcessMulticastDelegate<UObject>(NULL); \
}


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_35_SPARSE_DATA
#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_35_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetSerializedSize); \
	DECLARE_FUNCTION(execToString); \
	DECLARE_FUNCTION(execGetChunk); \
	DECLARE_FUNCTION(execIsFullyReceived); \
	DECLARE_FUNCTION(execGetExpectedChunkCount); \
	DECLARE_FUNCTION(execGetChunkCount); \
	DECLARE_FUNCTION(execGetChunkSize); \
	DECLARE_FUNCTION(execSetChunkSize); \
	DECLARE_FUNCTION(execReassembleFromChunksAsync); \
	DECLARE_FUNCTION(execReceiveChunk); \
	DECLARE_FUNCTION(execSetFromStringAsync);


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_35_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetSerializedSize); \
	DECLARE_FUNCTION(execToString); \
	DECLARE_FUNCTION(execGetChunk); \
	DECLARE_FUNCTION(execIsFullyReceived); \
	DECLARE_FUNCTION(execGetExpectedChunkCount); \
	DECLARE_FUNCTION(execGetChunkCount); \
	DECLARE_FUNCTION(execGetChunkSize); \
	DECLARE_FUNCTION(execSetChunkSize); \
	DECLARE_FUNCTION(execReassembleFromChunksAsync); \
	DECLARE_FUNCTION(execReceiveChunk); \
	DECLARE_FUNCTION(execSetFromStringAsync);


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_35_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULargeStringAsync(); \
	friend struct Z_Construct_UClass_ULargeStringAsync_Statics; \
public: \
	DECLARE_CLASS(ULargeStringAsync, ULargeDataObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LargeData"), NO_API) \
	DECLARE_SERIALIZER(ULargeStringAsync)


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_35_INCLASS \
private: \
	static void StaticRegisterNativesULargeStringAsync(); \
	friend struct Z_Construct_UClass_ULargeStringAsync_Statics; \
public: \
	DECLARE_CLASS(ULargeStringAsync, ULargeDataObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LargeData"), NO_API) \
	DECLARE_SERIALIZER(ULargeStringAsync)


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_35_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULargeStringAsync(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULargeStringAsync) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULargeStringAsync); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULargeStringAsync); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULargeStringAsync(ULargeStringAsync&&); \
	NO_API ULargeStringAsync(const ULargeStringAsync&); \
public:


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_35_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULargeStringAsync(ULargeStringAsync&&); \
	NO_API ULargeStringAsync(const ULargeStringAsync&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULargeStringAsync); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULargeStringAsync); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULargeStringAsync)


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_35_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__ChunkSize() { return STRUCT_OFFSET(ULargeStringAsync, ChunkSize); } \
	FORCEINLINE static uint32 __PPO__Value() { return STRUCT_OFFSET(ULargeStringAsync, Value); } \
	FORCEINLINE static uint32 __PPO__SerializedData() { return STRUCT_OFFSET(ULargeStringAsync, SerializedData); } \
	FORCEINLINE static uint32 __PPO__Chunks() { return STRUCT_OFFSET(ULargeStringAsync, Chunks); } \
	FORCEINLINE static uint32 __PPO__ReceivedChunks() { return STRUCT_OFFSET(ULargeStringAsync, ReceivedChunks); } \
	FORCEINLINE static uint32 __PPO__ExpectedChunks() { return STRUCT_OFFSET(ULargeStringAsync, ExpectedChunks); }


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_32_PROLOG
#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_35_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_35_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_35_SPARSE_DATA \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_35_RPC_WRAPPERS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_35_INCLASS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_35_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_35_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_35_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_35_SPARSE_DATA \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_35_RPC_WRAPPERS_NO_PURE_DECLS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_35_INCLASS_NO_PURE_DECLS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h_35_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LARGEDATA_API UClass* StaticClass<class ULargeStringAsync>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringAsync_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
