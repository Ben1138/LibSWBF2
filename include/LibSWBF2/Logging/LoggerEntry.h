#pragma once
#include <LibSWBF2/Types/LibString.h>
#include <LibSWBF2/Types/Enums.h>

namespace LibSWBF2::Logging
{
	using LibSWBF2::Types::String;

	struct LoggerEntry
	{
		LoggerEntry() = default;
		LoggerEntry(const char* message, const ELogType level, const uint32_t line, const char* file);
		LIBSWBF2_API String ToString() const;

		String m_Message;
		ELogType m_Level;
		uint32_t m_Line;
		String m_File;
	};
}