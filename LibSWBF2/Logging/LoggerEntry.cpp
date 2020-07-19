#include "stdafx.h"
#include "LoggerEntry.h"
#include <string>

namespace LibSWBF2::Logging
{
	LoggerEntry::LoggerEntry(const char* message, const ELogType level, const uint64_t line, const char* file)
	{
		this->m_Message = message;
		this->m_Level = level;
		this->m_Line = line;
		this->m_File = file;
	}

	String LoggerEntry::ToString() const
	{
		if (m_Level == ELogType::Info)
		{
			return "[" + LogTypeToString(m_Level) + "] " + m_Message;
		}
		else
		{
			return "[" + LogTypeToString(m_Level) + "] " + m_Message + " - IN " + std::to_string(m_Line).c_str() + " " + m_File;
		}
	}
}