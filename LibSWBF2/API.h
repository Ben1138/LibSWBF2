#pragma once
#include "LoggerEntry.h"
#include "Color.h"

#ifdef LIBSWBF2_EXPORTS
#define LIBSWBF2_API __declspec(dllexport)
#else
#define LIBSWBF2_API __declspec(dllimport)
#endif

namespace LibSWBF2
{
	extern "C"
	{
		LIBSWBF2_API Color* Color_Create(const float r, const float g, const float b, const float a);
		LIBSWBF2_API void Color_Delete(Color* color);

		LIBSWBF2_API void AddLogMessage(const char* message, const ELogType logType);
		LIBSWBF2_API void GetLogMessages(char* messages, const int length, const ELogType logType);
		LIBSWBF2_API void GetLastLogMessages(char* messages, const int length, const ELogType logType);
	}
}