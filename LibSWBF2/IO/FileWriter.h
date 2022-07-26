#pragma once
//#include "Chunks/HeaderNames.h"
//#include "LibSWBF2.h"
#include "Types/LibString.h"
#include <fstream>

namespace LibSWBF2
{
	union ChunkHeader;

	class FileWriter
	{
	public:
		FileWriter();
		~FileWriter();

		bool Open(const Types::String& File);
		bool Open(const Types::String& File, const bool& LogFile);
		void WriteChunkHeader(const ChunkHeader& value);
		void WriteChunkSize(ChunkSize value);
		void WriteByte(uint8_t value);
		void WriteBytes(uint8_t* data, size_t size);
		void WriteInt32(int32_t value);
		void WriteUInt32(uint32_t value);
		void WriteUInt16(uint16_t value);
		void WriteFloat(float_t value);
		void WriteString(const Types::String& value);
		void WriteString(const Types::String& value, uint16_t fixedSize);
		void WriteLine(const Types::String& line);
		size_t GetPosition();
		void Close();
	private:
		bool CheckGood();

		Types::String m_FileName;
		std::ofstream m_Writer;
	};
}
