#pragma once
#include <string>
#include <vector>
#include "LoggerEntry.h"

namespace LibSWBF2
{
	class Logger
	{
	public:
		static void Add(const std::string &message, const ELogType &level);
		static void GetAllLines(const ELogType &level, char* buffer);
		static void GetLastLines(const ELogType &level, char* buffer);
	private:
		static std::vector<LoggerEntry> logEntrys;
		static int lastIndex;

		Logger() {};
		~Logger() {};
	};
}