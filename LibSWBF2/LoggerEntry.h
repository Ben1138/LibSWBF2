#pragma once

namespace LibSWBF2::Logging
{
	enum ELogType
	{
		Info = 0,
		Warning = 1,
		Error = 2
	};

	const string SLogType[] = 
	{
		"Info",
		"Warning",
		"Error"
	};

	struct LoggerEntry
	{
		LoggerEntry(const std::string &message, const ELogType &level);

		string GetLogMessage();
		ELogType GetLogLevel();
	private:
		string message;
		ELogType level;
	};
}