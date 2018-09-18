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
	
	void Logger::Log(const string &message, const ELogType &level)
	{
		if (message.length() > 0)
		{
			m_Writer.WriteLine("[" + SLogType[level] + "] " + message);

			if (m_OnLogCallback)
			{
				m_OnLogCallback(LoggerEntry(message, level));
			}
		}
	}
}
