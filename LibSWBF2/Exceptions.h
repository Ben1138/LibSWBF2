#pragma once
#include "Chunks/HeaderNames.h"
#include "Types/LibString.h"
#include "InternalHelpers.h"
#include <fmt/format.h>
#include <stdexcept>
#include <exception>
#include <string>


namespace LibSWBF2
{
	class LibException : public std::runtime_error
	{
	public:
		LibException(const char* msg) : std::runtime_error(msg) {}
		LibException(const std::string& msg) : std::runtime_error(msg) {}
		LibException(const Types::String& msg) : std::runtime_error(msg.Buffer()) {}
	};

	class InvalidChunkException : public LibException
	{
	public:
		InvalidChunkException(const char* msg) : LibException(msg) {}
		InvalidChunkException(const std::string& msg) : LibException(msg) {}
		InvalidChunkException(const Types::String& msg) : LibException(msg) {}
	};

	class InvalidHeaderException : public InvalidChunkException
	{
	public:
		InvalidHeaderException(ChunkHeader header) 
			: InvalidChunkException(fmt::format("Illegal chunk header: {}", header))
		{
			m_Header = header;
		}

		ChunkHeader m_Header;
	};

	class InvalidSizeException : public InvalidChunkException
	{
	public:
		InvalidSizeException(ChunkSize size)
			: InvalidChunkException(fmt::format("Illegal chunk size: {}", size))
		{
			m_Size = size;
		}

		ChunkSize m_Size;
	};
}

#define THROW_LIBEX(...) throw LibException(fmt::format(__VA_ARGS__));