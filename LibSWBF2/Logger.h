#pragma once
#include "LoggerEntry.h"

namespace LibSWBF2::Logging
{
	class Logger
	{
	public:
		static void Add(const std::string &message, const ELogType &level);
		static string GetAllLines(const ELogType &level);
		static string GetLastLines(const ELogType &level);
		static bool HasNewLogs();
	private:
		static vector<LoggerEntry> logEntrys;
		static size_t lastIndex;

		Logger() {};
		~Logger() {};
	};
}