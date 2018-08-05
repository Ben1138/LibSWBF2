#include "stdafx.h"
#include "LoggerEntry.h"

namespace LibSWBF2 
{
	LoggerEntry::LoggerEntry(const std::string &message, const ELogType &level)
	{
		this->message = message;
		this->level = level;
	}

	std::string LoggerEntry::GetLogMessage()
	{
		return message;
	}

	ELogType LoggerEntry::GetLogLevel()
	{
		return level;
	}
}