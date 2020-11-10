#include "stdafx.h"
#include "Logger.h"
#include "FileWriter.h"
#include "InternalHelpers.h"

namespace LibSWBF2::Logging
{
	std::unique_ptr<Logger> Logger::m_Instance = nullptr;

	Logger::Logger()
	{
		m_Writer = new FileWriter();
		m_Writer->Open(LOG_FILE, true);
	}

	Logger::~Logger()
	{
		m_Writer->Close();
		delete m_Writer;
	}

	std::unique_ptr<Logger>& Logger::GetInstance()
	{
		if (m_Instance == nullptr)
		{
			m_Instance = std::make_unique<Logger>();
		}

		return m_Instance;
	}

	void Logger::SetLogfileLevel(const ELogType LogfileLevel)
	{
		GetInstance()->m_LogfileLevel = LogfileLevel;
	}

	bool Logger::GetNextLog(LoggerEntry& nextLogEntry)
	{
		Logger& inst = *GetInstance();
		LOCK(inst.m_Lock);
		if (inst.m_Logs.empty())
		{
			return false;
		}
		nextLogEntry = std::move(inst.m_Logs.front());
		inst.m_Logs.pop();
		return true;
	}
	
	void Logger::Log(const std::string &message, const ELogType level, const unsigned long line, const char* file)
	{
		if (message.length() > 0 && level >= m_LogfileLevel)
		{
			LOCK(m_Lock);
			LoggerEntry entry(message.c_str(), level, line, file);
			m_Writer->WriteLine(entry.ToString());

			m_Logs.push(std::move(entry));
			while (m_Logs.size() > MAX_ENTRIES)
			{
				m_Logs.pop();
			}
		}
	}
}