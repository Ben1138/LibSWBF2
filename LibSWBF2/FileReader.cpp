#include "stdafx.h"
#include "FileReader.h"
#include "InternalHelpers.h"
#include "InternalHelpers.h"

namespace LibSWBF2
{
	using LibSWBF2::Logging::Logger;

	FileReader::FileReader()
	{

	}

	FileReader::~FileReader()
	{

	}

	bool FileReader::Open(const Types::String& File)
	{
		m_Reader.open(File.Buffer(), std::ofstream::in | std::ofstream::binary | std::ofstream::ate);
		bool success = m_Reader.good() && m_Reader.is_open();

		if (!success)
		{
			LOG_WARN("File '{}' could not be found / opened!", File);
			m_Reader.close();
			return false;
		}

		m_FileName = File;
		m_FileSize = (size_t)m_Reader.tellg();
		m_Reader.seekg(0);

		LOG_INFO("File '{}' ({} bytes) successfully opened.", m_FileName, m_FileSize);
		return true;
	}

	ChunkHeader FileReader::ReadChunkHeader(bool peek)
	{
		ChunkHeader value;
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

	bool FileReader::ReadBytes(uint8_t* data, size_t length)
	{
		if (CheckGood(length))
		{
			m_Reader.read((char*)data, length);
			return true;
		}
		return false;
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

	int16_t FileReader::ReadInt16()
	{
		int16_t value = 0;
		if (CheckGood(sizeof(int16_t)))
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
		float_t value = 0.0f;
		if (CheckGood(sizeof(float_t)))
		{
			m_Reader.read((char*)&value, sizeof(value));
		}
		return value;
	}

	Types::String FileReader::ReadString(size_t length)
	{
		Types::String value;
		if (CheckGood(length))
		{
			char* str = new char[length+1];
			m_Reader.read(str, length);
			str[length] = 0;
			value = str;
			delete[] str;
		}
		return value;
	}

	Types::String FileReader::ReadString()
	{
		char str[1024]; // should be enough
		uint8_t current = 1;
		for (uint16_t i = 0; CheckGood(1) && current != 0; ++i)
		{
			if (i >= 1024)
			{
				LOG_WARN("Reading null terminated string exceeded buffer size!");
				break;
			}
			current = ReadByte();
			str[i] = current;
		}
		return str;
	}

	void FileReader::Close()
	{
		if (!m_Reader.is_open())
		{
			THROW("Nothing has been opened yet!");
		}

		m_FileName = "";
		m_Reader.close();
	}

	size_t FileReader::GetPosition()
	{
		return (size_t)m_Reader.tellg();
	}

	void FileReader::SetPosition(size_t NewPosition)
	{
		if (NewPosition < 0 || NewPosition > m_FileSize)
		{
			LOG_WARN("Cannot set read position to {} because it is out of range! Range: 0 - {}", NewPosition, m_FileSize);
			return;
		}

		m_Reader.seekg(NewPosition);
	}

	size_t FileReader::GetFileSize()
	{
		return m_FileSize;
	}

	bool FileReader::CheckGood(size_t ReadSize)
	{
		if (!m_Reader.is_open())
		{
			THROW("Error during read process! File '{}' is not open!", m_FileName);
		}

		if (!m_Reader.good())
		{
			std::string reason = "";
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
			THROW("Error during read process in '{}'! Reason: {}", m_FileName, reason);
		}

		size_t current = (size_t)m_Reader.tellg();
		if (current + ReadSize > m_FileSize)
		{
			THROW("Reading {} bytes will end up out of file!  Current position: {}  FileSize: {}", ReadSize, current, m_FileSize);
		}

		return true;
	}

	bool FileReader::SkipBytes(const size_t& Amount)
	{
		if (CheckGood(Amount))
		{
			m_Reader.seekg(GetPosition() + Amount);
			return true;
		}
		return false;
	}
}