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
		LoggerEntry(const char* message, const ELogType& level, const uint64_t& line, const char* file);
		LIBSWBF2_EXP string ToString() const;

		const char* m_Message;
		uint8_t m_Level;
		uint64_t m_Line;
		const char* m_File;
	};
}