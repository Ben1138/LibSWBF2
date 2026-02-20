#include <LibSWBF2/pch.h>
#include <LibSWBF2/Types/Vector2.h>
#include <LibSWBF2/Types/LibString.h>
#include <LibSWBF2/IO/FileWriter.h>
#include <LibSWBF2/IO/FileReader.h>
#include <fmt/format.h>


namespace LibSWBF2::Types
{
	Vector2::Vector2() : m_X(m_X), m_Y(m_Y) 
	{
		m_X = 0.0;
		m_Y = 0.0;
	}

	Vector2::Vector2(const float x, const float y)
	{
		m_X = x;
		m_Y = y;
	}

	Vector2::~Vector2()
	{

	}

	void Vector2::WriteToStream(FileWriter& stream)
	{
		stream.WriteFloat(m_X);
		stream.WriteFloat(m_Y);
	}

	void Vector2::ReadFromStream(FileReader& stream)
	{
		m_X = stream.ReadFloat();
		m_Y = stream.ReadFloat();
	}

	Types::String Vector2::ToString() const
	{
		return fmt::format("[{}, {}]", (float) m_X, (float) m_Y).c_str();
	}
}
