#pragma once

#include <stdint.h>
#include "Hashing.h"

namespace LibSWBF2
{
	namespace Types { struct String; }

	union ChunkHeader
	{
		uint32_t m_Magic = 0;
		uint8_t m_Name[4];

		Types::String ToString() const;
		bool operator==(const ChunkHeader other) const;
		bool operator!=(const ChunkHeader other) const;

		// the following mainly exist to meet std::set's expectations
		bool operator<(const ChunkHeader other) const;
		bool operator>(const ChunkHeader other) const;
	};

	constexpr ChunkHeader operator""_h(const char* chars, const size_t length)
	{
		return *(ChunkHeader*)chars;
	}

	constexpr uint32_t operator""_m(const char* chars, const size_t length)
	{
		uint32_t result = 0;
		result |= chars[0] << 0;
		result |= chars[1] << 8;
		result |= chars[2] << 16;
		result |= chars[3] << 24;
		return result;
	}
	
	constexpr ChunkHeader operator""_fnvh(const char* chars, const size_t length)
	{
		FNVHash fnvHeader = FNV::HashConstexpr({ chars, length });
		return *((ChunkHeader *) &fnvHeader);
	}

	bool IsPrintableHeader(const ChunkHeader hedr);
	bool IsKnownHeader(const ChunkHeader hedr);
}
