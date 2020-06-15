#pragma once
#include "LoggerEntry.h"
#include "FileWriter.h"
#include <memory>

namespace LibSWBF2::Logging
{
	typedef void(*LogCallback)(const LoggerEntry*);

	// Singleton
	// TODO: Make static class instead of singleton
	class Logger
	{
	public:
		Logger();	// do not call anywhere else!
		~Logger();

		const String LOG_FILE = "LibSWBF2.log";
		static std::unique_ptr<Logger>& GetInstance();

		LIBSWBF2_API static void SetLogCallback(const LogCallback Callback);
		LIBSWBF2_API static void SetLogfileLevel(const ELogType LogfileLevel);
		void Log(const std::string &message, const ELogType level, const unsigned long line, const char* file);

	private:
		static std::unique_ptr<Logger> m_Instance;
		LogCallback m_OnLogCallback = nullptr;
		FileWriter m_Writer;
		ELogType m_LogfileLevel = ELogType::Warning;
	};

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define LOG(message, level) LibSWBF2::Logging::Logger::GetInstance()->Log(message, level, __LINE__, __FILENAME__);
}