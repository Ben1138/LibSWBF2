#pragma once

namespace LibSWBF2
{
	namespace HeaderNames
	{
		constexpr int str2int(const char* str)
		{
			return *(int*)str;
		}

		static const int HEDR = str2int("HEDR");
		static const int SHVO = str2int("SHVO");
	}

	struct BaseChunk
	{
		BaseChunk();
		~BaseChunk();

		virtual void WriteToStream(ofstream& stream);
		virtual void ReadFromStream(ifstream& stream);
		static int PeekHeader(ifstream& stream);

	private:
		int Header;
		int Size;
	};
}