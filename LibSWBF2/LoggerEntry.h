#pragma once
#include <string>

namespace LibSWBF2
{
	enum ELogType
	{
		Info = 0,
		Warning = 1,
		Error = 2
	};

	struct LoggerEntry
	{
		LoggerEntry(const std::string &message, const ELogType &level);

		std::string GetLogMessage();
		ELogType GetLogLevel();
	private:
		std::string message;
		ELogType level;
	};
}