#include "stdafx.h"
#include "LoggerEntry.h"

namespace LibSWBF2::Logging
{
	LoggerEntry::LoggerEntry(const std::string &message, const ELogType &level)
	{
		this->m_Message = message;
		this->m_Level = level;
	}

	std::string LoggerEntry::GetLogMessage()
	{
		return m_Message;
	}

	ELogType LoggerEntry::GetLogLevel()
	{
		return m_Level;
	}
}