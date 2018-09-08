#pragma once
#include "LoggerEntry.h"
#include "FileWriter.h"

namespace LibSWBF2::Logging
{
	// Singleton
	class Logger
	{
	public:
		Logger();
		~Logger();

		const string LOG_FILE = "LibSWBF2.log";
		static unique_ptr<Logger>& GetInstance();

		void Add(const std::string &message, const ELogType &level);
		string GetAllLines(const ELogType &level);
		string GetLastLines(const ELogType &level);
		bool HasNewLogs();
	private:
		static unique_ptr<Logger> instance;

		FileWriter writer;
		vector<LoggerEntry> logEntrys;
		size_t lastIndex = 0;
	};

	inline void Log(const std::string &message, const ELogType &level)
	{
		Logger::GetInstance()->Add(message, level);
	}
}