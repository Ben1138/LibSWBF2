#pragma once
#include "LoggerEntry.h"
#include "Types/LibString.h"
#include "Chunks/HeaderNames.h"
#include "Chunks/BaseChunk.h"
#include <memory>
#include <queue>
#include <mutex>


namespace LibSWBF2
{
	class FileWriter;
}

namespace LibSWBF2::Logging
{
	// Singleton
	class Logger
	{
	public:
		Logger(); // do not call anywhere else
		~Logger();

		static std::unique_ptr<Logger>& GetInstance();

		LIBSWBF2_API static void SetLogfileLevel(const ELogType LogfileLevel);
		LIBSWBF2_API static bool GetNextLog(LoggerEntry& nextLogEntry);

		void Log(const std::string &message, const ELogType level, const unsigned long line, const char* file);

	private:
		const String LOG_FILE = "LibSWBF2.log";
		const int MAX_ENTRIES = 10000;

		static std::unique_ptr<Logger> m_Instance;
		FileWriter* m_Writer;
		ELogType m_LogfileLevel = ELogType::Warning;
		std::queue<LoggerEntry> m_Logs;
		std::mutex m_Lock;
	};
}