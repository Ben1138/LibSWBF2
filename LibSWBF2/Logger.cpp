#include <string>
#include <vector>
#include "stdafx.h"
#include "LoggerEntry.h"
#include "Logger.h"

namespace LibSWBF2
{
	int Logger::lastIndex = 0;
	std::vector<LoggerEntry> Logger::logEntrys;

	
	void Logger::Add(const std::string &message, const ELogType &level)
	{
		if (message.length() > 0)
			logEntrys.push_back(LoggerEntry(message, level));
	}

	void Logger::GetAllLines(const ELogType &level, char* buffer)
	{
		std::string resLines;

		for (unsigned int i = 0; i < logEntrys.size(); i++)
		{
			if (logEntrys[i].GetLogLevel() >= level)
			{
				resLines += logEntrys[i].GetLogMessage() + "\n";
			}
		}

		strcpy_s(buffer, resLines.length() + 1, resLines.c_str());
	}

	void Logger::GetLastLines(const ELogType &level, char* buffer)
	{
		std::string resLines;

		for (unsigned int i = lastIndex; i < logEntrys.size(); i++)
		{
			if (logEntrys[i].GetLogLevel() >= level)
			{
				resLines += logEntrys[i].GetLogMessage() + "\n";
			}
		}

		//save position for next request
		lastIndex = logEntrys.size() - 1;

		strcpy_s(buffer, resLines.length() + 1, resLines.c_str());
	}
}
