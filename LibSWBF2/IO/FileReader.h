#pragma once
#include "Chunks/HeaderNames.h"
#include "Types/LibString.h"
#include <atomic>



namespace LibSWBF2
{
	class FileReader
	{
	public:
		virtual ~FileReader() = default;

		virtual bool Open(const Types::String& File) = 0;
		virtual ChunkHeader ReadChunkHeader(bool peek) = 0;
		virtual ChunkSize ReadChunkSize() = 0;
		virtual uint8_t ReadByte() = 0;
		virtual bool ReadBytes(uint8_t* data, size_t length) = 0;
		virtual int32_t ReadInt32() = 0;
		virtual int16_t ReadInt16() = 0;
		virtual uint32_t ReadUInt32() = 0;
		virtual uint16_t ReadUInt16() = 0;
		virtual float_t ReadFloat() = 0;
		virtual Types::String ReadString(size_t length) = 0;
		virtual Types::String ReadString() = 0;// will read until the first null terminator
		virtual size_t GetPosition() = 0;
		virtual void SetPosition(size_t NewPosition) = 0;
		virtual size_t GetFileSize() = 0;
		virtual bool SkipBytes(const size_t& Amount) = 0;
		virtual void Close() = 0;

		virtual bool CheckGood(size_t ReadSize) = 0;

		size_t GetLatestChunkPosition() { return m_LatestChunkPos; }

		const Types::String& GetFileName() { return m_FileName; }

	protected:

		size_t m_FileSize = 0;
		Types::String m_FileName;
		
		std::atomic_size_t m_LatestChunkPos;
	};
}
