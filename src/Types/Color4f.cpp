#include <LibSWBF2/pch.h>
#include <LibSWBF2/Types/Color4f.h>
#include "InternalHelpers.h"
#include <LibSWBF2/IO/FileWriter.h>
#include <LibSWBF2/IO/FileReader.h>
#include <algorithm>


namespace LibSWBF2::Types
{
	Color4f::Color4f() : Color4f(0, 0, 0, 1) { }
	Color4f::Color4f(const float Red, const float Green, const float Blue) : Color4f(Red, Green, Blue, 1) { }

	Color4f::Color4f(const float Red, const float Green, const float Blue, const float Alpha) : 
		m_Red(std::clamp(m_Red, 0.0f, 1.0f)),
		m_Green(std::clamp(m_Green, 0.0f, 1.0f)),
		m_Blue(std::clamp(m_Blue, 0.0f, 1.0f)),
		m_Alpha(std::clamp(m_Alpha, 0.0f, 1.0f))
	{
		
	}

	Color4f::~Color4f()
	{
		
	}

	void Color4f::WriteToStream(FileWriter& stream)
	{
		stream.WriteFloat(m_Blue);
		stream.WriteFloat(m_Green);
		stream.WriteFloat(m_Red);
		stream.WriteFloat(m_Alpha);
	}

	void Color4f::ReadFromStream(FileReader& stream)
	{
		m_Blue = stream.ReadFloat();
		m_Green = stream.ReadFloat();
		m_Red = stream.ReadFloat();
		m_Alpha = stream.ReadFloat();
	}

	String Color4f::ToString() const
	{
		return fmt::format("[R: {}, G: {}, B: {}, A: {}]", m_Red, m_Green, m_Blue, m_Alpha).c_str();
	}

}
