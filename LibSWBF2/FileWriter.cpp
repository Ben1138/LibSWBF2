#include "stdafx.h"
#include "FileWriter.h"
#include "Logger.h"

namespace LibSWBF2
{
	using LibSWBF2::Logging::Logger;
	using LibSWBF2::Logging::ELogType;

	FileWriter::FileWriter()
	{
		
	}


	FileWriter::~FileWriter()
	{
	}

	bool FileWriter::Open(const string& File)
	{
		open(File, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
		bool success = good() && is_open();

		if (!success)
		{
			Logger::Add("File '" + File + "' could not be found / created!", ELogType::Error);
			FileName = "";
			return false;
		}
		
		FileName = File;
		return true;
	}

	void FileWriter::WriteChunkHeader(const ChunkHeader& value)
	{
		if (CheckGood())
		{
			operator<<(value);
		}
	}

	void FileWriter::WriteChunkSize(const ChunkSize& value)
	{
		if (CheckGood())
		{
			operator<<(value);
		}
	}

	void FileWriter::WriteInt32(const int32_t& value)
	{
		if (CheckGood())
		{
			operator<<(value);
		}
	}

	void FileWriter::WriteFloat(const float_t& value)
	{
		if (CheckGood())
		{
			operator<<(value);
		}
	}

	void FileWriter::WriteString(const string& value, const bool& SizeShouldBeMultipleOfFour)
	{
		// string in chunk needs to be a zero terminated c-string
		// size must be a multiple of 4
		// remaining bytes should be filled with 0x00

		if (CheckGood())
		{
			size_t length = value.size();
			write(value.c_str(), length);

			int remaining = 4 - (length % 4);
			char* empty = new char[remaining];

			for (int i = 0; i < remaining; i++)
				empty[i] = 0;

			write(empty, remaining);
			delete[] empty;
		}
	}

	void FileWriter::Close()
	{
		if (!is_open())
		{
			Logger::Add("Nothing has been opened yet!", ELogType::Error);
			return;
		}

		FileName = "";
		close();
	}

	bool FileWriter::CheckGood()
	{
		if (!is_open())
		{
			Logger::Add("Error during write process! File '" + FileName + "' is not open!", ELogType::Error);
			return false;
		}

		if (!good())
		{
			Logger::Add("Error during write process in '" + FileName + "'!", ELogType::Error);
			return false;
		}

		return true;
	}
}