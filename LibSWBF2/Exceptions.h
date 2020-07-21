#pragma once
#include "Types/LibString.h"
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
}