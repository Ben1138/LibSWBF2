#include "stdafx.h"
#include "FileWriter.h"
#include "Logging\Logger.h"
#include "Types\LibString.h"
#include <string>

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

	bool FileWriter::Open(const String& File)
	{
		return Open(File, false);
	}

	bool FileWriter::Open(const String& File, const bool& LogFile)
	{
		m_Writer.open(File.Buffer(), std::ofstream::out | (LogFile ? std::ofstream::app : std::ofstream::binary | std::ofstream::trunc));
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

	void FileWriter::WriteUInt16(const uint16_t& value)
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

	void FileWriter::WriteString(const String& value)
	{
		// string in chunk needs to be a zero terminated c-string
		// size must be a multiple of 4
		// remaining bytes should be filled with 0x00

		if (CheckGood())
		{
			size_t length = value.Length();
			m_Writer.write(value.Buffer(), length);

			int remaining = 4 - (length % 4);
			char* empty = new char[remaining];

			for (int i = 0; i < remaining; i++)
				empty[i] = 0;

			m_Writer.write(empty, remaining);
			delete[] empty;
		}
	}

	void FileWriter::WriteString(const String& value, uint16_t fixedSize)
	{
		if (CheckGood())
		{
			if (value.Length() > fixedSize)
			{
				LOG("Actual string size ("+std::to_string(value.Length())+") is greater than fixed size ("+std::to_string(fixedSize)+") !", ELogType::Error);
				return;
			}

			char* str = new char[fixedSize];
			strcpy_s(str, value.Length(), value.Buffer());
			m_Writer.write(str, fixedSize);
			delete[] str;
		}
	}

	void FileWriter::WriteLine(const String& line)
	{
		if (CheckGood())
		{
			std::string tmp = line.Buffer() + std::string("\n");
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
			//LOG("Error during write process! File '" + m_FileName + "' is not open!", ELogType::Error);
			throw std::runtime_error("Error during write process! File '" + std::string(m_FileName.Buffer()) + "' is not open!");
		}

		if (!m_Writer.good())
		{
			std::string reason = "";
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
			//LOG("Error during write process in '" + m_FileName + "'! Reason: " + reason, ELogType::Error);
			throw std::runtime_error("Error during write process in '" + std::string(m_FileName.Buffer()) + "'! Reason: " + reason);
		}

		return true;
	}

	size_t FileWriter::GetPosition()
	{
		return (size_t)m_Writer.tellp();
	}
}