#pragma once
#include "HeaderNames.h"

namespace LibSWBF2
{
	using std::ifstream;

	namespace Types{ struct String; }
	using LibSWBF2::Types::String;

	class FileReader
	{
	public:
		FileReader();
		~FileReader();

		bool Open(const string& File);
		ChunkHeader ReadChunkHeader(const bool& peek);
		ChunkSize ReadChunkSize();
		uint8_t ReadByte();
		bool ReadBytes(uint8_t* data, size_t length);
		int32_t ReadInt32();
		uint32_t ReadUInt32();
		uint16_t ReadUInt16();
		float_t ReadFloat();
		String ReadString(size_t length);
		size_t GetPosition();
		void SetPosition(size_t NewPosition);
		size_t GetFileSize();
		bool SkipBytes(const size_t& Amount);
		void Close();
	private:
		bool CheckGood(size_t ReadSize);

		size_t m_FileSize = 0;
		string m_FileName;
		ifstream m_Reader;
	};
}
