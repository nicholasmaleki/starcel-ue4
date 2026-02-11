/// Created by HISPlayer © - 2024  

#pragma once

#include "CoreMinimal.h"
#include "HISPlayerTypes/HISPlayerLogLevel.h"

class HISPlayerLogs 
{
public:

	static void Log( FString logMessage, HISPlayerLogLevel _logLevel, int index);
	static void Log(FString logMessage, HISPlayerLogLevel _logLevel);
	static void setLogLevel(HISPlayerLogLevel level);

private:
	static HISPlayerLogLevel logLevel;
	HISPlayerLogs() {};
};
