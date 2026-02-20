#pragma once
#include <LibSWBF2/Hashing.h>
#include <stdint.h>
#include <assert.h>

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
		assert(length == 4);
		return *(ChunkHeader*)chars;
	}

	constexpr uint32_t operator""_m(const char* chars, const size_t length)
	{
		assert(length == 4);

		uint32_t result = 0;
		result |= chars[0] << 0;
		result |= chars[1] << 8;
		result |= chars[2] << 16;
		result |= chars[3] << 24;
		return result;
	}
	
	constexpr ChunkHeader operator""_fnvh(const char* chars, const size_t length)
	{
		ChunkHeader ch;
		ch.m_Magic = FNV::HashConstexpr(chars, length);
		return ch;
	}

	bool IsPrintableHeader(const ChunkHeader hedr);
	bool IsKnownHeader(const ChunkHeader hedr);
}
