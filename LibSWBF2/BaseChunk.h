#pragma once

namespace LibSWBF2
{
	namespace HeaderNames
	{
		constexpr int32_t str2int(const char* str)
		{
			return *(int32_t*)str;
		}

		static const int32_t HEDR = str2int("HEDR");
		static const int32_t SHVO = str2int("SHVO");
	}

	struct BaseChunk
	{
		BaseChunk();
		~BaseChunk();

		virtual void WriteToStream(ofstream& stream);
		virtual void ReadFromStream(ifstream& stream);
		static int32_t PeekHeader(ifstream& stream);

	private:
		int32_t Header;
		int32_t Size;
	};
}