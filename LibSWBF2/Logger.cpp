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
	
	void Logger::Log(const string &message, const ELogType &level, const unsigned long line, const char* file)
	{
		if (message.length() > 0)
		{
			if (level == ELogType::Info)
			{
				m_Writer.WriteLine("[" + SLogType[level] + "] " + message);
			}
			else
			{
				m_Writer.WriteLine("[" + SLogType[level] + "] " + message + " - IN " + std::to_string(line) + " " + file);
			}

			if (m_OnLogCallback)
			{
				m_OnLogCallback(LoggerEntry(message, level, line, file));
			}
		}
	}
}
