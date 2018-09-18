#pragma once
#include "LoggerEntry.h"
#include "FileWriter.h"

namespace LibSWBF2::Logging
{
	// Singleton
	class Logger
	{
	public:
		Logger();	// do not call anywhere else!
		~Logger();

		const string LOG_FILE = "LibSWBF2.log";
		static unique_ptr<Logger>& GetInstance();

		function<void(LoggerEntry)> m_OnLogCallback;

		void Log(const std::string &message, const ELogType &level);

	private:
		static unique_ptr<Logger> m_Instance;
		FileWriter m_Writer;
	};

	inline void Log(const std::string &message, const ELogType &level)
	{
		Logger::GetInstance()->Log(message, level);
	}
}