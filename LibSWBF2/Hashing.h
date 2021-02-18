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


	constexpr FNVHash FNV::HashConstexpr(const std::string_view str)
	{
		constexpr uint32_t FNV_prime = 16777619;
		constexpr uint32_t offset_basis = 2166136261;

		uint32_t hash = offset_basis;

		for (auto c : str)
		{
			c |= 0x20;

			hash ^= c;
			hash *= FNV_prime;
		}

		return hash;
	}

	constexpr FNVHash operator""_fnv(const char* str, const std::size_t length)
	{
		return FNV::HashConstexpr({ str, length });
	}
}