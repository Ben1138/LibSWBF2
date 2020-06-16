#pragma once
#include "Types/LibString.h"
#include "Types/Enums.h"

namespace LibSWBF2::Logging
{
	using LibSWBF2::Types::String;

	struct LoggerEntry
	{
		LoggerEntry(const char* message, const ELogType level, const uint64_t line, const char* file);
		LIBSWBF2_API String ToString() const;

		const char* m_Message;
		ELogType m_Level;
		uint64_t m_Line;
		const char* m_File;
	};
}