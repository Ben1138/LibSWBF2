#pragma once

namespace LibSWBF2::Logging
{
#define ENUM_LOGTYPE Info = 0, Warning = 1, Error = 2

	enum ELogType
	{
		ENUM_LOGTYPE
	};

	const string SLogType[] = 
	{
		"Info",
		"Warning",
		"Error"
	};

	struct LoggerEntry
	{
		LoggerEntry(const string &message, const ELogType &level, const uint64_t &line, const string &file);

		string GetLogMessage();
		ELogType GetLogLevel();
		uint64_t GetLineNumber();
		string GetFileName();
	private:
		string m_Message;
		ELogType m_Level;
		uint64_t m_Line;
		string m_File;
	};
}