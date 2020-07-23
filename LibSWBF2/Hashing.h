#pragma once
#include "Types/LibString.h"
#include <unordered_map>

namespace LibSWBF2
{
	class CRC
	{
	private:
		static uint32_t m_Table32[256];
		static uint8_t m_ToLower[256];

	public:
		LIBSWBF2_API static CRCChecksum CalcLowerCRC(const char* str);
	};

	class FNV
	{
	private:
		const static std::unordered_map<std::uint32_t, std::string_view> m_LookupTable;

	public:
		static FNVHash Hash(const Types::String& str);
		static bool Lookup(FNVHash hash, Types::String& result);

		static constexpr FNVHash HashConstexpr(const std::string_view str);
	};

	constexpr FNVHash operator""_fnv(const char* str, const std::size_t length);
}