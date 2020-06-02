#include "stdafx.h"
#include "Color.h"
#include "Logging\Logger.h"

namespace LibSWBF2::Types
{
	Color::Color() : Color(0, 0, 0, 1) { }
	Color::Color(const uint8_t Red, const uint8_t Green, const uint8_t Blue) : Color(Red, Green, Blue, 1) { }

	Color::Color(const uint8_t Red, const uint8_t Green, const uint8_t Blue, const uint8_t Alpha) :
		m_Red(clamp(m_Red, (uint8_t)0, (uint8_t)255)),
		m_Green(clamp(m_Green, (uint8_t)0, (uint8_t)255)),
		m_Blue(clamp(m_Blue, (uint8_t)0, (uint8_t)255)),
		m_Alpha(clamp(m_Alpha, (uint8_t)0, (uint8_t)255))
	{
		
	}

	Color::~Color()
	{
		
	}

	void Color::WriteToStream(FileWriter& stream)
	{
		// in LVL -> MTRL, color order is BRGA
		stream.WriteByte(m_Blue);
		stream.WriteByte(m_Red);
		stream.WriteByte(m_Green);
		stream.WriteByte(m_Alpha);
	}

	void Color::ReadFromStream(FileReader& stream)
	{
		// in LVL -> MTRL, color order is BRGA
		m_Blue = stream.ReadByte();
		m_Red = stream.ReadByte();
		m_Green = stream.ReadByte();
		m_Alpha = stream.ReadByte();
	}

	String Color::ToString()
	{
		return
			("[R: " + std::to_string(m_Red) +
			", G: " + std::to_string(m_Green) +
			", B: " + std::to_string(m_Blue) +
			", A: " + std::to_string(m_Alpha) +
			"]").c_str();
	}
}