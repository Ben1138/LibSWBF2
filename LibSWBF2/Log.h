#pragma once
#include <string>
#include <vector>
#include "LogEntry.h"

#define DllExport __declspec(dllexport)

namespace LibSWBF2
{
	namespace Log
	{
		extern "C" class Log
		{
		public:
			static DllExport void add(const std::string &message, const LogType &level);
			static DllExport void getAllLines(const LogType &level, char* buffer);
			static DllExport void getLastLines(const LogType &level, char* buffer);
		private:
			static std::vector<LogEntry> logEntrys;
			static int lastIndex;

			Log() {};
			~Log() {};
		};
	}
}