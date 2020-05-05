#include "stdafx.h"
#include "Color.h"
#include "Logger.h"

namespace LibSWBF2::Types
{
	Color::Color() : Color(0, 0, 0, 1) { }
	Color::Color(const float_t& Red, const float_t& Green, const float_t& Blue) : Color(Red, Green, Blue, 1) { }

	Color::Color(const float_t& Red, const float_t& Green, const float_t& Blue, const float_t& Alpha) : 
		m_Red(clamp(m_Red, 0.0f, 1.0f)),
		m_Green(clamp(m_Green, 0.0f, 1.0f)),
		m_Blue(clamp(m_Blue, 0.0f, 1.0f)),
		m_Alpha(clamp(m_Alpha, 0.0f, 1.0f))
	{
		
	}

	Color::~Color()
	{
		
	}

	void Color::WriteToStream(FileWriter& stream)
	{
		stream.WriteFloat(m_Blue);
		stream.WriteFloat(m_Green);
		stream.WriteFloat(m_Red);
		stream.WriteFloat(m_Alpha);
	}

	void Color::ReadFromStream(FileReader& stream)
	{
		m_Blue = stream.ReadFloat();
		m_Green = stream.ReadFloat();
		m_Red = stream.ReadFloat();
		m_Alpha = stream.ReadFloat();
	}
}
