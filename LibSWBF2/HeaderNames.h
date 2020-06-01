#pragma once
#include "stdafx.h"
#include <set>

namespace LibSWBF2
{
	union ChunkHeader
	{
		uint32_t m_Magic = 0;
		uint8_t m_Name[4];

		string ToString() const;
		bool operator==(const ChunkHeader other) const;
		bool operator!=(const ChunkHeader other) const;

		// the following mainly exist to meet std::set's expectations
		bool operator<(const ChunkHeader other) const;
		bool operator>(const ChunkHeader other) const;
	};

	constexpr ChunkHeader operator""_h(const char* chars, const std::size_t length)
	{
		return *(ChunkHeader*)chars;
	}

	constexpr uint32_t operator""_m(const char* chars, const std::size_t length)
	{
		uint32_t result = 0;
		result |= chars[0] << 0;
		result |= chars[1] << 8;
		result |= chars[2] << 16;
		result |= chars[3] << 24;
		return result;
	}

	bool IsValidHeader(const ChunkHeader hedr);
	bool IsKnownHeader(const ChunkHeader hedr);
}