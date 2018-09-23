#include "stdafx.h"
#include "LoggerEntry.h"

namespace LibSWBF2::Logging
{
	LoggerEntry::LoggerEntry(const string &message, const ELogType &level, const uint64_t &line, const string &file)
	{
		this->m_Message = message;
		this->m_Level = level;
		this->m_Line = line;
		this->m_File = file;
	}

	string LoggerEntry::GetLogMessage()
	{
		return m_Message;
	}

	ELogType LoggerEntry::GetLogLevel()
	{
		return m_Level;
	}

	uint64_t LoggerEntry::GetLineNumber()
	{
		return m_Line;
	}

	string LoggerEntry::GetFileName()
	{
		return m_File;
	}
}