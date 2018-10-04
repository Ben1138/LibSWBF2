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
		m_Reader.open(File, std::ofstream::in | std::ofstream::binary | std::ofstream::ate);
		bool success = m_Reader.good() && m_Reader.is_open();

		if (!success)
		{
			LOG("File '" + File + "' could not be found / opened!", ELogType::Error);
			m_FileName = "";
			m_Reader.close();
			return false;
		}

		m_FileName = File;
		m_FileSize = (size_t)m_Reader.tellg();
		m_Reader.seekg(0);

		LOG("File '"+ m_FileName +"' ("+ std::to_string(m_FileSize) +" bytes) successfully opened.", ELogType::Info);
		return true;
	}

	ChunkHeader FileReader::ReadChunkHeader(const bool& peek)
	{
		ChunkHeader value = -42;
		if (CheckGood(sizeof(ChunkHeader)))
		{
			auto pos = m_Reader.tellg();
			m_Reader.read((char*)&value, sizeof(value));

			// do not advance our reading position when peeking
			if (peek)
			{
				m_Reader.seekg(pos);
			}
		}
		return value;
	}

	ChunkSize FileReader::ReadChunkSize()
	{
		ChunkSize value = 0;
		if (CheckGood(sizeof(ChunkSize)))
		{
			m_Reader.read((char*)&value, sizeof(value));
		}
		return value;
	}

	uint8_t FileReader::ReadByte()
	{
		uint8_t value = 0;
		if (CheckGood(sizeof(uint8_t)))
		{
			m_Reader.read((char*)&value, sizeof(value));
		}
		return value;
	}

	int32_t FileReader::ReadInt32()
	{
		int32_t value = 0;
		if (CheckGood(sizeof(int32_t)))
		{
			m_Reader.read((char*)&value, sizeof(value));
		}
		return value;
	}

	uint32_t FileReader::ReadUInt32()
	{
		uint32_t value = 0;
		if (CheckGood(sizeof(uint32_t)))
		{
			m_Reader.read((char*)&value, sizeof(value));
		}
		return value;
	}

	uint16_t FileReader::ReadUInt16()
	{
		uint16_t value = 0;
		if (CheckGood(sizeof(uint16_t)))
		{
			m_Reader.read((char*)&value, sizeof(value));
		}
		return value;
	}

	float_t FileReader::ReadFloat()
	{
		float_t value = 0;
		if (CheckGood(sizeof(float_t)))
		{
			m_Reader.read((char*)&value, sizeof(value));
		}
		return value;
	}

	string FileReader::ReadString(size_t length)
	{
		string value = "";
		if (CheckGood(length))
		{
			char* str = new char[length];
			m_Reader.read(str, length);
			value = str;
			delete[] str;
		}
		return value;
	}

	void FileReader::Close()
	{
		if (!m_Reader.is_open())
		{
			LOG("Nothing has been opened yet!", ELogType::Error);
			return;
		}

		m_FileName = "";
		m_Reader.close();
	}

	size_t FileReader::GetPosition()
	{
		return (size_t)m_Reader.tellg();
	}

	size_t FileReader::GetFileSize()
	{
		return m_FileSize;
	}

	bool FileReader::CheckGood(size_t ReadSize)
	{
		if (!m_Reader.is_open())
		{
			LOG("Error during read process! File '" + m_FileName + "' is not open!", ELogType::Error);
			return false;
		}

		if (!m_Reader.good())
		{
			string reason = "";
			if (m_Reader.eof())
			{
				reason += " End of File reached!";
			}
			if (m_Reader.fail())
			{
				reason += " Logical Error on I/O operation!";
			}
			if (m_Reader.bad())
			{
				reason += " Reading Error on I/O operation!";
			}
			LOG("Error during read process in '" + m_FileName + "'! Reason: " + reason, ELogType::Error);
			return false;
		}

		size_t current = (size_t)m_Reader.tellg();
		if (current + ReadSize > m_FileSize)
		{
			LOG("Reading " + std::to_string(ReadSize) + " bytes will end up out of file!  Current position: " + std::to_string(current) + "  FileSize: " + std::to_string(m_FileSize), ELogType::Error);
			return false;
		}

		return true;
	}

	bool FileReader::SkipBytes(const size_t& Amount)
	{
		if (CheckGood(GetPosition() + Amount))
		{
			m_Reader.seekg(GetPosition() + Amount);
			return true;
		}
		return false;
	}
}