#pragma once
#include "Chunks/HeaderNames.h"
#include "Types/LibString.h"
#include <stdexcept>
#include <exception>
#include <string>

namespace LibSWBF2
{
	class InvalidChunkException : public std::runtime_error
	{
	public:
		InvalidChunkException(std::string msg) : std::runtime_error(msg) {}
	};

	class InvalidHeaderException : public InvalidChunkException
	{
	public:
		InvalidHeaderException(ChunkHeader header) 
			: InvalidChunkException("Illegal chunk header: "+ std::string(header.ToString().Buffer()))
		{
			m_Header = header;
		}

		ChunkHeader m_Header;
	};

	class InvalidSizeException : public InvalidChunkException
	{
	public:
		InvalidSizeException(ChunkSize size)
			: InvalidChunkException("Illegal chunk size: " + std::to_string(size))
		{
			m_Size = size;
		}

		ChunkSize m_Size;
	};
}