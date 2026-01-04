// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UTexture2D;
#ifdef WINDOWCAPTURE2D_WindowCaptureActor_generated_h
#error "WindowCaptureActor.generated.h already included, missing '#pragma once' in WindowCaptureActor.h"
#endif
#define WINDOWCAPTURE2D_WindowCaptureActor_generated_h

#define Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_12_DELEGATE \
struct _Script_WindowCapture2D_eventWindowCaptureActorChangeTexture_Parms \
{ \
	UTexture2D* NewTexture; \
}; \
static inline void FWindowCaptureActorChangeTexture_DelegateWrapper(const FMulticastScriptDelegate& WindowCaptureActorChangeTexture, UTexture2D* NewTexture) \
{ \
	_Script_WindowCapture2D_eventWindowCaptureActorChangeTexture_Parms Parms; \
	Parms.NewTexture=NewTexture; \
	WindowCaptureActorChangeTexture.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_18_SPARSE_DATA
#define Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_18_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnChangeTexture); \
	DECLARE_FUNCTION(execStart);


#define Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnChangeTexture); \
	DECLARE_FUNCTION(execStart);


#define Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAWindowCaptureActor(); \
	friend struct Z_Construct_UClass_AWindowCaptureActor_Statics; \
public: \
	DECLARE_CLASS(AWindowCaptureActor, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/WindowCapture2D"), NO_API) \
	DECLARE_SERIALIZER(AWindowCaptureActor)


#define Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_18_INCLASS \
private: \
	static void StaticRegisterNativesAWindowCaptureActor(); \
	friend struct Z_Construct_UClass_AWindowCaptureActor_Statics; \
public: \
	DECLARE_CLASS(AWindowCaptureActor, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/WindowCapture2D"), NO_API) \
	DECLARE_SERIALIZER(AWindowCaptureActor)


#define Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_18_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AWindowCaptureActor(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AWindowCaptureActor) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AWindowCaptureActor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AWindowCaptureActor); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AWindowCaptureActor(AWindowCaptureActor&&); \
	NO_API AWindowCaptureActor(const AWindowCaptureActor&); \
public:


#define Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_18_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AWindowCaptureActor(AWindowCaptureActor&&); \
	NO_API AWindowCaptureActor(const AWindowCaptureActor&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AWindowCaptureActor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AWindowCaptureActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AWindowCaptureActor)


#define Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_18_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__CaptureMachine() { return STRUCT_OFFSET(AWindowCaptureActor, CaptureMachine); }


#define Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_15_PROLOG
#define Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_18_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_18_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_18_SPARSE_DATA \
	Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_18_RPC_WRAPPERS \
	Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_18_INCLASS \
	Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_18_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_18_PRIVATE_PROPERTY_OFFSET \
	Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_18_SPARSE_DATA \
	Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_18_INCLASS_NO_PURE_DECLS \
	Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> WINDOWCAPTURE2D_API UClass* StaticClass<class AWindowCaptureActor>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_WindowCaptureActor_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
