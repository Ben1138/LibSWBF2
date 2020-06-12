#pragma once
#include "Logging\Logger.h"

namespace LibSWBF2
{
	using Logging::ELogType;

	class CRC
	{
	private:
		static uint32_t table32[256];
		static uint8_t toLower[256];

	public:
		LIBSWBF2_EXP static CRCChecksum CalcLowerCRC(const char* str);
	};
}