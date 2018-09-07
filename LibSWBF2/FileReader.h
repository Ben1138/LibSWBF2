#pragma once

namespace LibSWBF2
{
	using std::ifstream;

	class FileReader : private ifstream
	{
	public:
		FileReader();
		~FileReader();

		bool Open(const string& File);
		ChunkHeader ReadChunkHeader(const bool& peek);
		ChunkSize ReadChunkSize();
		uint8_t ReadByte();
		int32_t ReadInt32();
		float_t ReadFloat();
		string ReadString(size_t length);
		void Close();
	private:
		bool CheckGood(size_t ReadSize);

		size_t FileSize;
		string FileName;
	};
}
