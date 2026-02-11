/// Created by HISPlayer © - 2024  


#include "HISPlayerLogs.h"
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

HISPlayerLogLevel HISPlayerLogs::logLevel = HISPlayerLogLevel::INFO;

std::string getCurrentTimestamp() {
	// Get the current time
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

	// Convert the time to a time_t (seconds since epoch)
	std::time_t time = std::chrono::system_clock::to_time_t(now);

	// Convert time_t to a struct tm (broken down time)
	std::tm tm_time;
#if PLATFORM_WINDOWS
	localtime_s(&tm_time, &time); // Use localtime_s for Windows, use localtime_r for Unix-based systems
#endif
	// Format the timestamp
	std::ostringstream oss;
	oss << std::put_time(&tm_time, "%Y-%m-%d %H:%M:%S");

	return oss.str();
}


void HISPlayerLogs::Log(FString logMessage, HISPlayerLogLevel _logLevel, int index)
{
	FString timeStamp = FString(getCurrentTimestamp().c_str());

	switch (_logLevel)
	{
	case HISPlayerLogLevel::DEBUG:
		if ((int)logLevel == 0)
			UE_LOG(LogTemp, Display, TEXT("[%s][HISPlayer | DEBUG]: %s. Index: %d"), *timeStamp, *logMessage, index);
		break;
	case HISPlayerLogLevel::INFO:
		if ((int)logLevel <= 1)
			UE_LOG(LogTemp, Display, TEXT("[%s][HISPlayer | INFO]: %s. Index: %d"), *timeStamp, *logMessage, index);
		break;
	case HISPlayerLogLevel::WARNING:
		if ((int)logLevel <= 2)
			UE_LOG(LogTemp, Warning, TEXT("[%s][HISPlayer | WARNING]: %s. Index: %d"), *timeStamp, *logMessage, index);
		break;
	case HISPlayerLogLevel::ERROR:
		if ((int)logLevel <= 3)
			UE_LOG(LogTemp, Error, TEXT("[%s][HISPlayer | ERROR]: %s. Index: %d"), *timeStamp, *logMessage, index);
		break;
	default:
		break;
	}

}

void HISPlayerLogs::Log(FString logMessage, HISPlayerLogLevel _logLevel)
{
	FString timeStamp = FString(getCurrentTimestamp().c_str());

	switch (_logLevel)
	{
	case HISPlayerLogLevel::DEBUG:
		if ((int)logLevel == 0)
			UE_LOG(LogTemp, Display, TEXT("[%s][HISPlayer | DEBUG]: %s."), *timeStamp, *logMessage);
		break;
	case HISPlayerLogLevel::INFO:
		if ((int)logLevel <= 1)
			UE_LOG(LogTemp, Display, TEXT("[%s][HISPlayer | INFO]: %s."), *timeStamp, *logMessage);
		break;
	case HISPlayerLogLevel::WARNING:
		if ((int)logLevel <= 2)
			UE_LOG(LogTemp, Warning, TEXT("[%s][HISPlayer | WARNING]: %s."), *timeStamp, *logMessage);
		break;
	case HISPlayerLogLevel::ERROR:
		if ((int)logLevel <= 3)
			UE_LOG(LogTemp, Error, TEXT("[%s][HISPlayer | ERROR]: %s."), *timeStamp, *logMessage);
		break;
	default:
		break;
	}
}



void HISPlayerLogs::setLogLevel(HISPlayerLogLevel level)
{
	logLevel = level;
}

