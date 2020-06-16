#pragma once

namespace LibSWBF2
{
	class CRC
	{
	private:
		static uint32_t table32[256];
		static uint8_t toLower[256];

	public:
		LIBSWBF2_API static CRCChecksum CalcLowerCRC(const char* str);
	};
}