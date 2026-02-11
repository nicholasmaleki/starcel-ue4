/// Created by HISPlayer © - 2024  

#pragma once
#include "HISPlayerLogLevel.generated.h"

UENUM(BlueprintType, Category = "HISPlayer|Types")
enum class HISPlayerLogLevel : uint8 {

	DEBUG = 0		UMETA(DisplayName = "DEBUG"),				// Logs messages useful for debugging and troubleshooting purposes
	
	INFO = 1		UMETA(DisplayName = "INFO"),				// Provides general informational messages about the application's execution

	WARNING = 2		UMETA(DisplayName = "WARNING"),				// Indicates potential issues or situations that may require attention
	
	ERROR = 3		UMETA(DisplayName = "ERROR"),				// Indicates critical errors that may prevent the application from functioning correctly
	
	NONE = 4		UMETA(DisplayName = "NONE")					// No log messages will appear
	
};
