#include "pch.h"
#include "Types/LibString.h"
#include "Vector3.h"
#include "FileReader.h"
#include "FileWriter.h"
#include <fmt/format.h>

namespace LibSWBF2::Types
{
	Vector3::Vector3()
	{
		m_X = 0.0;
		m_Y = 0.0;
		m_Z = 0.0;
	}

	Vector3::Vector3(const float_t x, const float_t y, const float_t z)
	{
		m_X = x;
		m_Y = y;
		m_Z = z;
	}

	Vector3::~Vector3()
	{

	}

	void Vector3::WriteToStream(FileWriter& stream)
	{
		stream.WriteFloat(m_X);
		stream.WriteFloat(m_Y);
		stream.WriteFloat(m_Z);
	}

	void Vector3::ReadFromStream(FileReader& stream)
	{
		m_X = stream.ReadFloat();
		m_Y = stream.ReadFloat();
		m_Z = stream.ReadFloat();
	}

	String Vector3::ToString() const
	{
		return fmt::format("[{}, {}, {}]", (float_t) m_X, (float_t) m_Y, (float_t) m_Z).c_str();
	}
}