#include "stdafx.h"
#include "Vector3u8.h"
#include "FileReader.h"
#include "FileWriter.h"
#include <fmt/format.h>

namespace LibSWBF2::Types
{
	Vector3u8::Vector3u8()
	{
		
	}

	Vector3u8::Vector3u8(const uint8_t x, const uint8_t y, const uint8_t z) : 
		m_X(x), m_Y(y), m_Z(z)
	{
		
	}

	Vector3u8::~Vector3u8()
	{

	}

	void Vector3u8::WriteToStream(FileWriter& stream)
	{
		stream.WriteByte(m_X);
		stream.WriteByte(m_Y);
		stream.WriteByte(m_Z);
	}

	void Vector3u8::ReadFromStream(FileReader& stream)
	{
		m_X = stream.ReadByte();
		m_Y = stream.ReadByte();
		m_Z = stream.ReadByte();
	}

	String Vector3u8::ToString()
	{
		return fmt::format("[{}, {}, {}]", m_X, m_Y, m_Z).c_str();
	}
}