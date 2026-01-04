// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef WINDOWCAPTURE2D_CaptureMachineProperties_generated_h
#error "CaptureMachineProperties.generated.h already included, missing '#pragma once' in CaptureMachineProperties.h"
#endif
#define WINDOWCAPTURE2D_CaptureMachineProperties_generated_h

#define Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachineProperties_h_45_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FCaptureMachineProperties_Statics; \
	static class UScriptStruct* StaticStruct();


template<> WINDOWCAPTURE2D_API UScriptStruct* StaticStruct<struct FCaptureMachineProperties>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Starcel9_Plugins_WindowCapture2D_Source_WindowCapture2D_Public_CaptureMachineProperties_h


#define FOREACH_ENUM_ETITLEMATCHINGWINDOWSEARCH(op) \
	op(ETitleMatchingWindowSearch::PerfectMatch) \
	op(ETitleMatchingWindowSearch::ForwardMatch) \
	op(ETitleMatchingWindowSearch::PartialMatch) \
	op(ETitleMatchingWindowSearch::BackwardMatch) \
	op(ETitleMatchingWindowSearch::RegularExpression) 

enum class ETitleMatchingWindowSearch : uint8;
template<> WINDOWCAPTURE2D_API UEnum* StaticEnum<ETitleMatchingWindowSearch>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
