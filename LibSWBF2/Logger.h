#pragma once
#include "LoggerEntry.h"
#include "FileWriter.h"

namespace LibSWBF2::Logging
{
	typedef function<void(LoggerEntry)> LogCallback;

	// Singleton
	class Logger
	{
	public:
		Logger();	// do not call anywhere else!
		~Logger();

		const string LOG_FILE = "LibSWBF2.log";
		static unique_ptr<Logger>& GetInstance();

		LIBSWBF2_EXP static void SetLogCallback(const LogCallback& Callback);
		void Log(const std::string &message, const ELogType &level, const unsigned long line, const char* file);

	private:
		static unique_ptr<Logger> m_Instance;
		LogCallback m_OnLogCallback;
		FileWriter m_Writer;
	};

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define LOG(message, level) LibSWBF2::Logging::Logger::GetInstance()->Log(message, level, __LINE__, __FILENAME__);
}