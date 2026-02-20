#include <LibSWBF2/pch.h>
#include <LibSWBF2/Types/LibString.h>
#include <LibSWBF2/Types/Vector3.h>
#include <LibSWBF2/IO/FileReader.h>
#include <LibSWBF2/IO/FileWriter.h>
#include <fmt/format.h>


namespace LibSWBF2::Types
{
	Vector3::Vector3()
	{
		m_X = 0.0;
		m_Y = 0.0;
		m_Z = 0.0;
	}

	Vector3::Vector3(const float x, const float y, const float z)
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
		return fmt::format("[{}, {}, {}]", (float) m_X, (float) m_Y, (float) m_Z).c_str();
	}
}
