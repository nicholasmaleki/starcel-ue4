// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "CaptureMachine.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UTexture2D;
#ifdef WINDOWCAPTURE2D_CaptureMachine_generated_h
#error "CaptureMachine.generated.h already included, missing '#pragma once' in CaptureMachine.h"
#endif
#define WINDOWCAPTURE2D_CaptureMachine_generated_h

#define FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_17_DELEGATE \
struct _Script_WindowCapture2D_eventCaptureMachineChangeTexture_Parms \
{ \
	UTexture2D* NewTexture; \
}; \
static inline void FCaptureMachineChangeTexture_DelegateWrapper(const FMulticastScriptDelegate& CaptureMachineChangeTexture, UTexture2D* NewTexture) \
{ \
	_Script_WindowCapture2D_eventCaptureMachineChangeTexture_Parms Parms; \
	Parms.NewTexture=NewTexture; \
	CaptureMachineChangeTexture.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_23_SPARSE_DATA
#define FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_23_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execCreateTexture);


#define FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execCreateTexture);


#define FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_23_ACCESSORS
#define FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_23_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCaptureMachine(); \
	friend struct Z_Construct_UClass_UCaptureMachine_Statics; \
public: \
	DECLARE_CLASS(UCaptureMachine, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WindowCapture2D"), NO_API) \
	DECLARE_SERIALIZER(UCaptureMachine)


#define FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_23_INCLASS \
private: \
	static void StaticRegisterNativesUCaptureMachine(); \
	friend struct Z_Construct_UClass_UCaptureMachine_Statics; \
public: \
	DECLARE_CLASS(UCaptureMachine, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WindowCapture2D"), NO_API) \
	DECLARE_SERIALIZER(UCaptureMachine)


#define FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_23_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCaptureMachine(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCaptureMachine) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCaptureMachine); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCaptureMachine); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCaptureMachine(UCaptureMachine&&); \
	NO_API UCaptureMachine(const UCaptureMachine&); \
public: \
	NO_API virtual ~UCaptureMachine();


#define FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_23_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCaptureMachine(UCaptureMachine&&); \
	NO_API UCaptureMachine(const UCaptureMachine&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCaptureMachine); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCaptureMachine); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UCaptureMachine) \
	NO_API virtual ~UCaptureMachine();


#define FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_20_PROLOG
#define FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_23_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_23_SPARSE_DATA \
	FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_23_RPC_WRAPPERS \
	FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_23_ACCESSORS \
	FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_23_INCLASS \
	FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_23_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_23_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_23_SPARSE_DATA \
	FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_23_ACCESSORS \
	FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_23_INCLASS_NO_PURE_DECLS \
	FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h_23_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> WINDOWCAPTURE2D_API UClass* StaticClass<class UCaptureMachine>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_xnick_Documents_Unreal_Projects_starcel_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachine_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
