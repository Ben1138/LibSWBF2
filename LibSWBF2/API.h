#pragma once
#include "LoggerEntry.h"

#ifdef LIBSWBF2_EXPORTS
#define API __declspec(dllexport) 
#else
#define API __declspec(dllimport) 
#endif

namespace LibSWBF2
{
	extern "C"
	{
		API void AddLogMessage(char* message, const ELogType logType);
		API void GetLogMessages(const ELogType logType);
	}
}