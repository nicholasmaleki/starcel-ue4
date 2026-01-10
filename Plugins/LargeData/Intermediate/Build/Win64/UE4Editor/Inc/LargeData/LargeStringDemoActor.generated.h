// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef LARGEDATA_LargeStringDemoActor_generated_h
#error "LargeStringDemoActor.generated.h already included, missing '#pragma once' in LargeStringDemoActor.h"
#endif
#define LARGEDATA_LargeStringDemoActor_generated_h

#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_SPARSE_DATA
#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_RPC_WRAPPERS \
	virtual void Server_SendChunk_Implementation(TArray<uint8> const& Chunk, int32 Index, int32 TotalChunks); \
	virtual void Client_ReceiveChunk_Implementation(TArray<uint8> const& Chunk, int32 Index, int32 TotalChunks); \
 \
	DECLARE_FUNCTION(execOnStringFullyReceived); \
	DECLARE_FUNCTION(execServer_SendChunk); \
	DECLARE_FUNCTION(execClient_ReceiveChunk);


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void Server_SendChunk_Implementation(TArray<uint8> const& Chunk, int32 Index, int32 TotalChunks); \
	virtual void Client_ReceiveChunk_Implementation(TArray<uint8> const& Chunk, int32 Index, int32 TotalChunks); \
 \
	DECLARE_FUNCTION(execOnStringFullyReceived); \
	DECLARE_FUNCTION(execServer_SendChunk); \
	DECLARE_FUNCTION(execClient_ReceiveChunk);


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_EVENT_PARMS \
	struct LargeStringDemoActor_eventClient_ReceiveChunk_Parms \
	{ \
		TArray<uint8> Chunk; \
		int32 Index; \
		int32 TotalChunks; \
	}; \
	struct LargeStringDemoActor_eventServer_SendChunk_Parms \
	{ \
		TArray<uint8> Chunk; \
		int32 Index; \
		int32 TotalChunks; \
	};


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_CALLBACK_WRAPPERS
#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesALargeStringDemoActor(); \
	friend struct Z_Construct_UClass_ALargeStringDemoActor_Statics; \
public: \
	DECLARE_CLASS(ALargeStringDemoActor, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LargeData"), NO_API) \
	DECLARE_SERIALIZER(ALargeStringDemoActor)


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_INCLASS \
private: \
	static void StaticRegisterNativesALargeStringDemoActor(); \
	friend struct Z_Construct_UClass_ALargeStringDemoActor_Statics; \
public: \
	DECLARE_CLASS(ALargeStringDemoActor, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LargeData"), NO_API) \
	DECLARE_SERIALIZER(ALargeStringDemoActor)


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ALargeStringDemoActor(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ALargeStringDemoActor) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ALargeStringDemoActor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ALargeStringDemoActor); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ALargeStringDemoActor(ALargeStringDemoActor&&); \
	NO_API ALargeStringDemoActor(const ALargeStringDemoActor&); \
public:


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ALargeStringDemoActor(ALargeStringDemoActor&&); \
	NO_API ALargeStringDemoActor(const ALargeStringDemoActor&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ALargeStringDemoActor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ALargeStringDemoActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ALargeStringDemoActor)


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_PRIVATE_PROPERTY_OFFSET
#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_13_PROLOG \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_EVENT_PARMS


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_SPARSE_DATA \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_RPC_WRAPPERS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_CALLBACK_WRAPPERS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_INCLASS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_SPARSE_DATA \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_CALLBACK_WRAPPERS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_INCLASS_NO_PURE_DECLS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LARGEDATA_API UClass* StaticClass<class ALargeStringDemoActor>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringDemoActor_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
