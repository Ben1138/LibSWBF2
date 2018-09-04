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

	void FileWriter::WriteInt32(const int32_t& value)
	{
		CheckGood();
		operator<<(value);
	}

	void FileWriter::WriteFloat(const float_t& value)
	{
		CheckGood();
		operator<<(value);
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

	void FileWriter::CheckGood()
	{
		if (!is_open())
			Logger::Add("Error during write process! File '"+ FileName +"' is not open!", ELogType::Error);

		if (!good())
			Logger::Add("Error during write process in '"+ FileName +"'!", ELogType::Error);
	}
}