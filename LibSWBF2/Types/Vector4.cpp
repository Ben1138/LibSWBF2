#include "stdafx.h"
#include "Types/LibString.h"
#include "Vector4.h"
#include "FileReader.h"
#include "FileWriter.h"
#include <fmt/format.h>

namespace LibSWBF2::Types
{
	Vector4::Vector4()
	{
		m_X = 0.0;
		m_Y = 0.0;
		m_Z = 0.0;
		m_W = 0.0;
	}

	Vector4::Vector4(const float_t x, const float_t y, const float_t z, const float_t w)
	{
		m_X = x;
		m_Y = y;
		m_Z = z;
		m_W = w;
	}

	Vector4::~Vector4()
	{

	}

	void Vector4::WriteToStream(FileWriter& stream)
	{
		stream.WriteFloat(m_X);
		stream.WriteFloat(m_Y);
		stream.WriteFloat(m_Z);
		stream.WriteFloat(m_W);
	}

	void Vector4::ReadFromStream(FileReader& stream)
	{
		m_X = stream.ReadFloat();
		m_Y = stream.ReadFloat();
		m_Z = stream.ReadFloat();
		m_W = stream.ReadFloat();
	}

	String Vector4::ToString()
	{
		return fmt::format("[{}, {}, {}, {}]",(float_t) m_X, (float_t) m_Y,(float_t) m_Z,(float_t) m_W).c_str();
	}
}