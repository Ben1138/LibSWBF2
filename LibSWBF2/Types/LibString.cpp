#include "stdafx.h"
#include "LibString.h"
#include "InternalHelpers.h"

namespace LibSWBF2::Types
{
	String::String()
	{
		buffer = new char[1] { 0 };
	}

	String::String(const char* cStr) : String()
	{
		if (cStr == nullptr)
		{
			buffer = new char[1]{ 0 };
			length = 0;
			return;
		}

		length = strnlen_s(cStr, MAX_LENGTH);

		if (length > MAX_LENGTH)
		{
			LOG_WARN("String length {} exceeds max supported length of {}! String will end up empty!", length, MAX_LENGTH);
			buffer = new char[1]{ 0 };
			length = 0;
			return;
		}

		if (length > 0)
		{
			delete[] buffer;
			buffer = new char[length + 1];
			memcpy_s(buffer, length, cStr, length);
			buffer[length] = 0;
		}
	}

	String::String(const String& other) : length(other.length)
	{
		if (other.buffer == nullptr)
		{
			LOG_WARN("Given String is invalid (buffer is NULL)! This should never happen!");
			buffer = new char[1]{ 0 };
			length = 0;
		}
		else
		{
			buffer = new char[length + 1];
			memcpy_s(buffer, length + 1, other.buffer, length + 1);
		}
	}

	String::String(String&& other) : length(other.length), buffer(other.buffer)
	{
		if (other.buffer == nullptr)
		{
			LOG_WARN("Given String is invalid (buffer is NULL)! This should never happen!");
		}

		other.buffer = new char[1]{ 0 };
		other.length = 0;
	}

	String::~String()
	{
		delete[] buffer;
		buffer = nullptr;
	}

	const char* String::Buffer() const
	{
		return buffer;
	}

	size_t String::Length() const
	{
		return length;
	}

	String& String::operator=(const String& other)
	{
		if (&other != this)
		{
			if (other.buffer == nullptr)
			{
				LOG_WARN("Given String is invalid (buffer is NULL)! String won't be copied!");
			}
			else
			{
				length = other.length;
				delete[] buffer;
				buffer = new char[length + 1];
				memcpy_s(buffer, length + 1, other.buffer, length + 1);
			}
		}
		return *this;
	}

	String String::operator+=(const String& a)
	{
		return *this + a;
	}

	String operator+(const String& a, const String& b)
	{
		String result;
		delete[] result.buffer;
		result.length = a.length + b.length;
		result.buffer = new char[result.length + 1];

		memcpy(result.buffer, a.buffer, a.length);
		memcpy(result.buffer + a.length, b.buffer, b.length);
		result.buffer[result.length] = 0;

		return result;
	}

	String operator+(const String& a, const char* b)
	{
		return a + String(b);
	}

	String operator+(const char* a, const String& b)
	{
		return String(a) + b;
	}

	bool String::operator==(const String& other) const
	{
		return buffer != nullptr && other.buffer != nullptr && length == other.length && memcmp(buffer, other.buffer, length) == 0;
	}

	bool String::operator!=(const String& other) const
	{
		return buffer == nullptr || other.buffer == nullptr || length != other.length || memcmp(buffer, other.buffer, length) != 0;
	}

	bool String::IsEmpty() const
	{
		return buffer == nullptr || buffer[0] == 0;
	}
}