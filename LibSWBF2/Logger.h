#pragma once
#include "LoggerEntry.h"

namespace LibSWBF2::Logging
{
	using std::string;
	using std::vector;

	class Logger
	{
	public:
		static void Add(const std::string &message, const ELogType &level);
		static string GetAllLines(const ELogType &level);
		static string GetLastLines(const ELogType &level);
	private:
		static vector<LoggerEntry> logEntrys;
		static size_t lastIndex;

		Logger() {};
		~Logger() {};
	};
}