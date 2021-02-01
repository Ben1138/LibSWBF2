

#include "stdafx.h"
#include "FileReader.h"

#ifdef MEMORY_MAPPED_READER




#include "InternalHelpers.h"
#include "InternalHelpers.h"

#include <limits>
#include <memory>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <errno.h>

#include <filesystem>

#include <iostream>

namespace fs = std::filesystem;


namespace LibSWBF2
{
	using LibSWBF2::Logging::Logger;

	FileReader::FileReader()
	{
		m_LatestChunkPos = 0;
	    m_Reader = nullptr;
	    m_MMapStart = nullptr;
	}

	FileReader::~FileReader()
	{
		//static int counter = 0;
		//LOG_WARN("Unmapping file: {} for the {} time", m_FileName, ++counter);
		munmap(m_MMapStart, m_FileSize);
	}

	bool FileReader::Open(const Types::String& File)
	{
		fs::path path = File.Buffer();
		if (!fs::exists(path) || fs::is_directory(path))
		{
			LOG_WARN("File '{}' could not be found!", File);
			return false;
		}
		   
		const auto file_size = fs::file_size(path);


		const String fname = path.string().c_str(); 
		m_FileSize = static_cast<std::uint32_t>(file_size);
		   
		int fd = open(fname.Buffer(), O_RDONLY);

		if (fd < 0)
		{
			//char buffer[ 256 ];
   	 		//strerror_r( errno, buffer, 256 ); // get string message from errno, XSI-compliant version
    		//printf("Error %s", buffer);
     		// or
    		//char * errorMsg = strerror_r( errno, buffer, 256 ); // GNU-specific version, Linux default
    		//printf("Error %s", errorMsg); //r

			LOG_WARN("File '{}': failed to open file!", File);
			return false;
		}

	    m_MMapStart = (uint8_t *) mmap(0,m_FileSize,PROT_READ,MAP_FILE|MAP_PRIVATE,fd,0);
	  
	    if (m_MMapStart == MAP_FAILED){
			LOG_WARN("File '{}': memory map failed!", File);
			return false;
	    }
	  
	    close(fd);

		m_FileName = File;
		m_Reader = m_MMapStart;

		LOG_INFO("File '{}' ({} bytes) successfully opened.", m_FileName, m_FileSize);
		return true;
	}

	ChunkHeader FileReader::ReadChunkHeader(bool peek)
	{
		ChunkHeader value;
		if (CheckGood(sizeof(ChunkHeader)))
		{
			auto pos = m_Reader - m_MMapStart;

			memcpy(&value, m_Reader, sizeof(value));
			m_Reader += sizeof(value);

			//m_Reader.read((char*)&value, sizeof(value));

			// do not advance our reading position when peeking
			if (peek)
			{
				m_Reader = m_MMapStart + pos;
			}

			m_LatestChunkPos = pos;
		}
		return value;
	}

	ChunkSize FileReader::ReadChunkSize()
	{
		ChunkSize value = 0;
		if (CheckGood(sizeof(ChunkSize)))
		{
			//m_Reader.read((char*)&value, sizeof(value));
			//memcpy(value, m_Reader, sizeof(value));

			value = *((uint32_t *) m_Reader);
			m_Reader += sizeof(value);
		}
		return value;
	}

	uint8_t FileReader::ReadByte()
	{
		uint8_t value = 0;
		if (CheckGood(sizeof(uint8_t)))
		{
			value = *(m_Reader++);//m_Reader.read((char*)&value, sizeof(value));
		}
		return value;
	}

	bool FileReader::ReadBytes(uint8_t* data, size_t length)
	{
		if (CheckGood(length))
		{
			//m_Reader.read((char*)data, length);
			memcpy(data, m_Reader, length);
			m_Reader += length;

			return true;
		}
		return false;
	}

	int32_t FileReader::ReadInt32()
	{
		int32_t value = 0;
		if (CheckGood(sizeof(int32_t)))
		{
			//m_Reader.read((char*)&value, sizeof(value));
			value = *((int32_t *) m_Reader);
			m_Reader+=4;
		}
		return value;
	}

	int16_t FileReader::ReadInt16()
	{
		int16_t value = 0;
		if (CheckGood(sizeof(int16_t)))
		{
			//m_Reader.read((char*)&value, sizeof(value));
			value = *((int16_t *) m_Reader);
			m_Reader+=2;
		}
		return value;
	}

	uint32_t FileReader::ReadUInt32()
	{
		uint32_t value = 0;
		if (CheckGood(sizeof(uint32_t)))
		{
			//m_Reader.read((char*)&value, sizeof(value));
			value = *((uint32_t *) m_Reader);
			m_Reader+=4;
		}
		return value;
	}

	uint16_t FileReader::ReadUInt16()
	{
		uint16_t value = 0;
		if (CheckGood(sizeof(uint16_t)))
		{
			//m_Reader.read((char*)&value, sizeof(value));
			value = *((uint16_t *) m_Reader);
			m_Reader+=2;
		}
		return value;
	}

	float_t FileReader::ReadFloat()
	{
		float_t value = 0.0f;
		if (CheckGood(sizeof(float_t)))
		{
			//m_Reader.read((char*)&value, sizeof(value));
			value = *((float_t *) m_Reader);
			m_Reader+=4;
		}
		return value;
	}

	Types::String FileReader::ReadString(size_t length)
	{
		Types::String value;
		if (CheckGood(length))
		{
			char* str = new char[length+1];
			//m_Reader.read(str, length);
			memcpy((char *) str, (char *) m_Reader, length);
			m_Reader += length;

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
		/*
		if (!m_Reader.is_open())
		{
			THROW("Nothing has been opened yet!");
		}

		m_FileName = "";
		m_Reader.close();
		*/
	}

	size_t FileReader::GetPosition()
	{
		return (size_t) (m_Reader - m_MMapStart);
	}

	void FileReader::SetPosition(size_t NewPosition)
	{
		if (NewPosition < 0 || NewPosition > m_FileSize)
		{
			LOG_WARN("Cannot set read position to {:#x} because it is out of range! Range: 0x00 - {:#x}", NewPosition, m_FileSize);
			return;
		}

		m_Reader = m_MMapStart + NewPosition;
	}

	size_t FileReader::GetFileSize()
	{
		return m_FileSize;
	}

	bool FileReader::CheckGood(size_t ReadSize)
	{
		size_t current = (size_t) (m_Reader - m_MMapStart);
		if (current + ReadSize > m_FileSize)
		{
			THROW("Reading {:#x} bytes will end up out of file!  Current position: {:#x}  FileSize: {:#x}", ReadSize, current, m_FileSize);
		}

		return true;
	}

	bool FileReader::SkipBytes(const size_t& Amount)
	{
		if (CheckGood(Amount))
		{
			m_Reader += Amount;
			return true;
		}
		return false;
	}


	size_t FileReader::GetLatestChunkPosition()
	{
		return m_LatestChunkPos;
	}
}

#endif