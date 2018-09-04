#include "stdafx.h"
#include "FileReader.h"
#include "Logger.h"

namespace LibSWBF2
{
	using LibSWBF2::Logging::Logger;
	using LibSWBF2::Logging::ELogType;

	FileReader::FileReader()
	{

	}

	FileReader::~FileReader()
	{

	}

	bool FileReader::Open(const string& File)
	{
		open(File, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
		bool success = good() && is_open();

		if (!success)
		{
			Logger::Add("File '" + File + "' could not be found / opened!", ELogType::Error);
			FileName = "";
			return false;
		}

		FileName = File;
		return true;
	}

	int32_t FileReader::ReadInt32()
	{
		CheckGood();
		int32_t value;
		operator>>(value);
		return value;
	}

	float_t FileReader::ReadFloat()
	{
		CheckGood();
		float_t value;
		operator>>(value);
		return value;
	}

	void FileReader::Close()
	{
		if (!is_open())
		{
			Logger::Add("Nothing has been opened yet!", ELogType::Error);
			return;
		}

		FileName = "";
		close();
	}

	void FileReader::CheckGood()
	{
		if (!is_open())
			Logger::Add("Error during read process! File '" + FileName + "' is not open!", ELogType::Error);

		if (!good())
			Logger::Add("Error during read process in '" + FileName + "'!", ELogType::Error);
	}
}