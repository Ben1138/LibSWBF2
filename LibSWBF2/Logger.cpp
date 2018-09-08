#include "stdafx.h"
#include "Logger.h"

namespace LibSWBF2::Logging
{
	unique_ptr<Logger> Logger::instance = nullptr;

	Logger::Logger()
	{
		writer.Open(LOG_FILE, true);
	}

	Logger::~Logger()
	{
		writer.Close();
	}

	unique_ptr<Logger>& Logger::GetInstance()
	{
		if (instance == nullptr)
		{
			instance = std::make_unique<Logger>();
		}

		return instance;
	}
	
	void Logger::Add(const string &message, const ELogType &level)
	{
		if (message.length() > 0)
		{
			logEntrys.push_back(LoggerEntry(message, level));
			writer.WriteLine("[" + SLogType[level] + "] " + message);
		}
	}

	string Logger::GetAllLines(const ELogType &level)
	{
		string resLines;

		for (size_t i = 0; i < logEntrys.size(); i++)
		{
			if (logEntrys[i].GetLogLevel() >= level)
			{
				resLines += logEntrys[i].GetLogMessage() + "\n";
			}
		}

		return resLines;
	}

	string Logger::GetLastLines(const ELogType &level)
	{
		string resLines;

		for (size_t i = lastIndex; i < logEntrys.size(); i++)
		{
			if (logEntrys[i].GetLogLevel() >= level)
			{
				resLines += logEntrys[i].GetLogMessage() + "\n";
			}
		}

		//save position for next request
		lastIndex = logEntrys.size() - 1;

		return resLines;
	}

	bool Logger::HasNewLogs()
	{
		return lastIndex < logEntrys.size() - 1;
	}
}
