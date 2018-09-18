#include "stdafx.h"
#include "Logger.h"

namespace LibSWBF2::Logging
{
	unique_ptr<Logger> Logger::m_Instance = nullptr;

	Logger::Logger()
	{
		m_Writer.Open(LOG_FILE, true);
	}

	Logger::~Logger()
	{
		m_Writer.Close();
	}

	unique_ptr<Logger>& Logger::GetInstance()
	{
		if (m_Instance == nullptr)
		{
			m_Instance = std::make_unique<Logger>();
		}

		return m_Instance;
	}
	
	void Logger::Add(const string &message, const ELogType &level)
	{
		if (message.length() > 0)
		{
			m_LogEntrys.push_back(LoggerEntry(message, level));
			m_Writer.WriteLine("[" + SLogType[level] + "] " + message);
		}
	}

	string Logger::GetAllLines(const ELogType &level)
	{
		string resLines;

		for (size_t i = 0; i < m_LogEntrys.size(); i++)
		{
			if (m_LogEntrys[i].GetLogLevel() >= level)
			{
				resLines += m_LogEntrys[i].GetLogMessage() + "\n";
			}
		}

		return resLines;
	}

	string Logger::GetLastLines(const ELogType &level)
	{
		string resLines;

		for (size_t i = m_LastIndex; i < m_LogEntrys.size(); i++)
		{
			if (m_LogEntrys[i].GetLogLevel() >= level)
			{
				resLines += m_LogEntrys[i].GetLogMessage() + "\n";
			}
		}

		//save position for next request
		m_LastIndex = m_LogEntrys.size() - 1;

		return resLines;
	}

	bool Logger::HasNewLogs()
	{
		return m_LastIndex < m_LogEntrys.size() - 1;
	}
}
