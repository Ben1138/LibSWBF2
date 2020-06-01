#pragma once
#include "HeaderNames.h"
#include <exception>

namespace LibSWBF2
{
	class InvalidChunkException : public std::runtime_error
	{
	public:
		InvalidChunkException(string msg) : std::runtime_error(msg) {}
	};

	class InvalidHeaderException : public InvalidChunkException
	{
	public:
		InvalidHeaderException(ChunkHeader header) 
			: InvalidChunkException("Illegal chunk header: "+ header.ToString())
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