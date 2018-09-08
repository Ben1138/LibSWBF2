#pragma once

namespace LibSWBF2
{
	using std::ofstream;

	class FileWriter : private ofstream
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
		void WriteFloat(const float_t& value);
		void WriteString(const string& value, const bool& SizeShouldBeMultipleOfFour);
		void WriteLine(const string& line);
		void Close();
	private:
		bool CheckGood();

		string FileName;
	};
}
