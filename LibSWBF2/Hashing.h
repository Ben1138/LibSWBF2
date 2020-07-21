#pragma once
#include "Types/LibString.h"
#include <unordered_map>
#include <string_view>

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
		static std::unordered_map<FNVHash, std::string>* p_LookupTable;

	public:
		static FNVHash Hash(const Types::String& str);
		static bool Lookup(FNVHash hash, Types::String& result);

		static constexpr FNVHash HashConstexpr(const std::string_view str);

		static void ReadLookupTable();
		static void ReleaseLookupTable();
	};

	constexpr FNVHash operator""_fnv(const char* str, const std::size_t length);
}