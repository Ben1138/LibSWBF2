#include "stdafx.h"
#include "Logger.h"

namespace LibSWBF2::Logging
{
	size_t Logger::lastIndex = 0;
	vector<LoggerEntry> Logger::logEntrys;

	
	void Logger::Add(const string &message, const ELogType &level)
	{
		if (message.length() > 0)
			logEntrys.push_back(LoggerEntry(message, level));
	}

	string Logger::GetAllLines(const ELogType &level)
	{
		string resLines;

		for (size_t i = 0; i < logEntrys.size(); i++)
		{
			if (logEntrys[i].GetLogLevel() >= level)
			{
				resLines += logEntrys[i].GetLogMessage() + "\n";
			}
		}

		return resLines;
	}

	string Logger::GetLastLines(const ELogType &level)
	{
		string resLines;

		for (size_t i = lastIndex; i < logEntrys.size(); i++)
		{
			if (logEntrys[i].GetLogLevel() >= level)
			{
				resLines += logEntrys[i].GetLogMessage() + "\n";
			}
		}

		//save position for next request
		lastIndex = logEntrys.size() - 1;

		return resLines;
	}
}
