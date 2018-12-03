#pragma once

namespace LibSWBF2::Logging
{
	enum ELogType : uint8_t
	{
		Info = 0,
		Warning = 1,
		Error = 2
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
		LIBSWBF2_EXP string ToString();

		string m_Message;
		ELogType m_Level;
		uint64_t m_Line;
		string m_File;
	};
}