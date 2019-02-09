#pragma once

namespace LibSWBF2
{
	using std::ofstream;

	namespace Types { struct String; }
	using LibSWBF2::Types::String;

	class FileWriter
	{
	public:
		FileWriter();
		~FileWriter();

		bool Open(const string& File);
		bool Open(const string& File, const bool& LogFile);
		void WriteChunkHeader(const ChunkHeader& value);
		void WriteChunkSize(const ChunkSize& value);
		void WriteByte(const uint8_t& value);
		void WriteInt32(const int32_t& value);
		void WriteUInt32(const uint32_t& value);
		void WriteUInt16(const uint16_t& value);
		void WriteFloat(const float_t& value);
		void WriteString(const String& value);
		void WriteString(const String& value, uint16_t fixedSize);
		void WriteLine(const string& line);
		size_t GetPosition();
		void Close();
	private:
		bool CheckGood();

		string m_FileName;
		ofstream m_Writer;
	};
}
