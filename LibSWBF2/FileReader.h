#pragma once
#include "Chunks/HeaderNames.h"
#include "Types/LibString.h"
#include <fstream>
#include <atomic>

namespace LibSWBF2
{
	class FileReader
	{
	public:
		FileReader();
		~FileReader();

		bool Open(const Types::String& File);
		ChunkHeader ReadChunkHeader(bool peek);
		ChunkSize ReadChunkSize();
		uint8_t ReadByte();
		bool ReadBytes(uint8_t* data, size_t length);
		int32_t ReadInt32();
		int16_t ReadInt16();
		uint32_t ReadUInt32();
		uint16_t ReadUInt16();
		float_t ReadFloat();
		Types::String ReadString(size_t length);
		Types::String ReadString(); // will read until the first null terminator
		size_t GetPosition();
		void SetPosition(size_t NewPosition);
		size_t GetFileSize();
		bool SkipBytes(const size_t& Amount);
		void Close();

		size_t GetLatestChunkPosition();
		void SetLatestChunkPosition(size_t position);


	private:
		bool CheckGood(size_t ReadSize);

		size_t m_FileSize = 0;
		Types::String m_FileName;
		std::ifstream m_Reader;
		
		std::atomic_size_t m_LatestChunkPos;
	};
}
