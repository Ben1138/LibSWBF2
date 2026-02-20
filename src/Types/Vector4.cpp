#include <LibSWBF2/pch.h>
#include <LibSWBF2/Types/LibString.h>
#include <LibSWBF2/Types/Vector4.h>
#include <LibSWBF2/IO/FileReader.h>
#include <LibSWBF2/IO/FileWriter.h>
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

	Vector4::Vector4(const float x, const float y, const float z, const float w)
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

	String Vector4::ToString() const
	{
		return fmt::format("[{}, {}, {}, {}]",(float) m_X, (float) m_Y,(float) m_Z,(float) m_W).c_str();
	}
}
