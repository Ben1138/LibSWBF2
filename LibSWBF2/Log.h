#pragma once
#include <string>
#include <vector>
#include "LogEntry.h"

namespace LibSWBF2
{
	namespace Log
	{
		class Log
		{
		public:
			static void Add(const std::string &message, const LogType &level);
			static std::string* getAllLines(const LogType &level);
			static std::string* getLastLines(const LogType &level);
		private:
			static std::vector<LogEntry> logEntrys;
			static int lastIndex;

			Log() {};
			~Log() {};
		};
	}
}