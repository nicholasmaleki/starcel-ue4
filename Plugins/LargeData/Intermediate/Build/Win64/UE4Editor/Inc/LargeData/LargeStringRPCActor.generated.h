// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef LARGEDATA_LargeStringRPCActor_generated_h
#error "LargeStringRPCActor.generated.h already included, missing '#pragma once' in LargeStringRPCActor.h"
#endif
#define LARGEDATA_LargeStringRPCActor_generated_h

#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_SPARSE_DATA
#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_RPC_WRAPPERS \
	virtual void Client_ReceiveChunk_Implementation(TArray<uint8> const& Chunk, int32 Index, int32 TotalChunks); \
	virtual void Multicast_ReceiveChunk_Implementation(TArray<uint8> const& Chunk, int32 Index, int32 TotalChunks); \
	virtual void Server_ReceiveChunk_Implementation(TArray<uint8> const& Chunk, int32 Index, int32 TotalChunks); \
 \
	DECLARE_FUNCTION(execClient_ReceiveChunk); \
	DECLARE_FUNCTION(execMulticast_ReceiveChunk); \
	DECLARE_FUNCTION(execServer_ReceiveChunk); \
	DECLARE_FUNCTION(execServer_OnFullStringReceived);


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void Client_ReceiveChunk_Implementation(TArray<uint8> const& Chunk, int32 Index, int32 TotalChunks); \
	virtual void Multicast_ReceiveChunk_Implementation(TArray<uint8> const& Chunk, int32 Index, int32 TotalChunks); \
	virtual void Server_ReceiveChunk_Implementation(TArray<uint8> const& Chunk, int32 Index, int32 TotalChunks); \
 \
	DECLARE_FUNCTION(execClient_ReceiveChunk); \
	DECLARE_FUNCTION(execMulticast_ReceiveChunk); \
	DECLARE_FUNCTION(execServer_ReceiveChunk); \
	DECLARE_FUNCTION(execServer_OnFullStringReceived);


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_EVENT_PARMS \
	struct LargeStringRPCActor_eventClient_ReceiveChunk_Parms \
	{ \
		TArray<uint8> Chunk; \
		int32 Index; \
		int32 TotalChunks; \
	}; \
	struct LargeStringRPCActor_eventMulticast_ReceiveChunk_Parms \
	{ \
		TArray<uint8> Chunk; \
		int32 Index; \
		int32 TotalChunks; \
	}; \
	struct LargeStringRPCActor_eventServer_ReceiveChunk_Parms \
	{ \
		TArray<uint8> Chunk; \
		int32 Index; \
		int32 TotalChunks; \
	};


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_CALLBACK_WRAPPERS
#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesALargeStringRPCActor(); \
	friend struct Z_Construct_UClass_ALargeStringRPCActor_Statics; \
public: \
	DECLARE_CLASS(ALargeStringRPCActor, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LargeData"), NO_API) \
	DECLARE_SERIALIZER(ALargeStringRPCActor)


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_INCLASS \
private: \
	static void StaticRegisterNativesALargeStringRPCActor(); \
	friend struct Z_Construct_UClass_ALargeStringRPCActor_Statics; \
public: \
	DECLARE_CLASS(ALargeStringRPCActor, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LargeData"), NO_API) \
	DECLARE_SERIALIZER(ALargeStringRPCActor)


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ALargeStringRPCActor(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ALargeStringRPCActor) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ALargeStringRPCActor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ALargeStringRPCActor); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ALargeStringRPCActor(ALargeStringRPCActor&&); \
	NO_API ALargeStringRPCActor(const ALargeStringRPCActor&); \
public:


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ALargeStringRPCActor(ALargeStringRPCActor&&); \
	NO_API ALargeStringRPCActor(const ALargeStringRPCActor&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ALargeStringRPCActor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ALargeStringRPCActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ALargeStringRPCActor)


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_PRIVATE_PROPERTY_OFFSET
#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_8_PROLOG \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_EVENT_PARMS


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_SPARSE_DATA \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_RPC_WRAPPERS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_CALLBACK_WRAPPERS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_INCLASS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_SPARSE_DATA \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_CALLBACK_WRAPPERS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_INCLASS_NO_PURE_DECLS \
	Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h_11_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LARGEDATA_API UClass* StaticClass<class ALargeStringRPCActor>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Starcel9_Plugins_LargeData_Source_LargeData_Public_LargeStringRPCActor_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
