#include "stdafx.h"
#include "LoggerEntry.h"

namespace LibSWBF2::Logging
{
	LoggerEntry::LoggerEntry(const char* message, const ELogType& level, const uint64_t& line, const char* file)
	{
		this->m_Message = message;
		this->m_Level = (uint8_t)level;
		this->m_Line = line;
		this->m_File = file;
	}

	String LoggerEntry::ToString() const
	{
		if (m_Level == (uint8_t)ELogType::Info)
		{
			return "[" + SLogType[m_Level] + "] " + m_Message;
		}
		else
		{
			return "[" + SLogType[m_Level] + "] " + m_Message + " - IN " + std::to_string(m_Line) + " " + m_File;
		}
	}
}