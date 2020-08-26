#include "stdafx.h"
#include "FileWriter.h"
#include "InternalHelpers.h"
#include "InternalHelpers.h"
#include <string>

namespace LibSWBF2
{
	using LibSWBF2::Logging::Logger;

	FileWriter::FileWriter()
	{
		
	}

	FileWriter::~FileWriter()
	{
	}

	bool FileWriter::Open(const Types::String& File)
	{
		return Open(File, false);
	}

	bool FileWriter::Open(const Types::String& File, const bool& LogFile)
	{
		m_Writer.open(File.Buffer(), std::ofstream::out | (LogFile ? std::ofstream::app : std::ofstream::binary | std::ofstream::trunc));
		bool success = m_Writer.good() && m_Writer.is_open();

		if (!success)
		{
			if (!LogFile)
			{
				LOG_ERROR("File '{}' could not be found / created!", File);
			}
			m_FileName = "";
			m_Writer.close();
			return false;
		}

		m_FileName = File;

		if (!LogFile)
		{
			LOG_INFO("File '{}' successfully created/opened.", m_FileName);
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

	void FileWriter::WriteBytes(const uint8_t* data, size_t size)
	{
		if (CheckGood())
		{
			m_Writer.write((const char*)data, size);
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

	void FileWriter::WriteString(const Types::String& value)
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

	void FileWriter::WriteString(const Types::String& value, uint16_t fixedSize)
	{
		if (CheckGood())
		{
			if (value.Length() > fixedSize)
			{
				LOG_WARN("Actual string size ({}) is greater than fixed size ({}) !", value.Length(), fixedSize);
			}

			m_Writer.write(value.Buffer(), fixedSize);
		}
	}

	void FileWriter::WriteLine(const Types::String& line)
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
			LOG_WARN("Nothing has been opened yet!");
			return;
		}

		m_FileName = "";
		m_Writer.close();
	}

	bool FileWriter::CheckGood()
	{
		if (!m_Writer.is_open())
		{
			THROW("Error during write process! File '{}' is not open!", m_FileName);
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
			THROW("Error during write process in '{}'! Reason: {}", m_FileName, reason);
		}

		return true;
	}

	size_t FileWriter::GetPosition()
	{
		return (size_t)m_Writer.tellp();
	}
}