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
		return Open(File, false);
	}

	bool FileWriter::Open(const string& File, const bool& LogFile)
	{
		m_Writer.open(File, std::ofstream::out | (LogFile ? std::ofstream::app : std::ofstream::binary | std::ofstream::trunc));
		bool success = m_Writer.good() && m_Writer.is_open();

		if (!success)
		{
			if (!LogFile)
			{
				LOG("File '" + File + "' could not be found / created!", ELogType::Error);
			}
			m_FileName = "";
			m_Writer.close();
			return false;
		}

		m_FileName = File;

		if (!LogFile)
		{
			LOG("File '" + m_FileName + "' successfully created/opened.", ELogType::Info);
		}
		return true;
	}

	void FileWriter::WriteChunkHeader(const ChunkHeader& value)
	{
		if (CheckGood())
		{
			m_Writer.write((char*)&value, sizeof(value));
		}
	}

	void FileWriter::WriteChunkSize(const ChunkSize& value)
	{
		if (CheckGood())
		{
			m_Writer.write((char*)&value, sizeof(value));
		}
	}

	void FileWriter::WriteByte(const uint8_t& value)
	{
		if (CheckGood())
		{
			m_Writer.write((char*)&value, sizeof(value));
		}
	}

	void FileWriter::WriteInt32(const int32_t& value)
	{
		if (CheckGood())
		{
			m_Writer.write((char*)&value, sizeof(value));
		}
	}

	void FileWriter::WriteUInt32(const uint32_t& value)
	{
		if (CheckGood())
		{
			m_Writer.write((char*)&value, sizeof(value));
		}
	}

	void FileWriter::WriteFloat(const float_t& value)
	{
		if (CheckGood())
		{
			m_Writer.write((char*)&value, sizeof(value));
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
			m_Writer.write(value.c_str(), length);

			int remaining = 4 - (length % 4);
			char* empty = new char[remaining];

			for (int i = 0; i < remaining; i++)
				empty[i] = 0;

			m_Writer.write(empty, remaining);
			delete[] empty;
		}
	}

	void FileWriter::WriteLine(const string& line)
	{
		if (CheckGood())
		{
			string tmp = line + "\n";
			m_Writer.write(tmp.c_str(), tmp.size());
			m_Writer.flush();
		}
	}

	void FileWriter::Close()
	{
		if (!m_Writer.is_open())
		{
			LOG("Nothing has been opened yet!", ELogType::Error);
			return;
		}

		m_FileName = "";
		m_Writer.close();
	}

	bool FileWriter::CheckGood()
	{
		if (!m_Writer.is_open())
		{
			LOG("Error during write process! File '" + m_FileName + "' is not open!", ELogType::Error);
			return false;
		}

		if (!m_Writer.good())
		{
			string reason = "";
			if (m_Writer.eof())
			{
				reason += " End of File reached!";
			}
			if (m_Writer.fail())
			{
				reason += " Logical Error on I/O operation!";
			}
			if (m_Writer.bad())
			{
				reason += " Writing Error on I/O operation!";
			}
			LOG("Error during write process in '" + m_FileName + "'! Reason: " + reason, ELogType::Error);
			return false;
		}

		return true;
	}

	size_t FileWriter::GetPosition()
	{
		return (size_t)m_Writer.tellp();
	}
}