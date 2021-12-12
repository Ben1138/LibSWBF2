#include "pch.h"
#include "Color4.h"
#include "InternalHelpers.h"
#include "FileWriter.h"
#include "FileReader.h"
#include <algorithm>

namespace LibSWBF2::Types
{
	Color4::Color4() : Color4(0, 0, 0, 1) { }
	Color4::Color4(const float_t Red, const float_t Green, const float_t Blue) : Color4(Red, Green, Blue, 1) { }

	Color4::Color4(const float_t Red, const float_t Green, const float_t Blue, const float_t Alpha) : 
		m_Red(std::clamp(m_Red, 0.0f, 1.0f)),
		m_Green(std::clamp(m_Green, 0.0f, 1.0f)),
		m_Blue(std::clamp(m_Blue, 0.0f, 1.0f)),
		m_Alpha(std::clamp(m_Alpha, 0.0f, 1.0f))
	{
		
	}

	Color4::~Color4()
	{
		
	}

	void Color4::WriteToStream(FileWriter& stream)
	{
		stream.WriteFloat(m_Blue);
		stream.WriteFloat(m_Green);
		stream.WriteFloat(m_Red);
		stream.WriteFloat(m_Alpha);
	}

	void Color4::ReadFromStream(FileReader& stream)
	{
		m_Blue = stream.ReadFloat();
		m_Green = stream.ReadFloat();
		m_Red = stream.ReadFloat();
		m_Alpha = stream.ReadFloat();
	}

	String Color4::ToString() const
	{
		return fmt::format("[R: {}, G: {}, B: {}, A: {}]", m_Red, m_Green, m_Blue, m_Alpha).c_str();
	}

}
