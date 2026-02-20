#include <LibSWBF2/pch.h>
#include <LibSWBF2/Types/Color4u8.h>
#include "InternalHelpers.h"
#include <LibSWBF2/IO/FileWriter.h>
#include <LibSWBF2/IO/FileReader.h>
#include <algorithm>
#include <fmt/format.h>


namespace LibSWBF2::Types
{
	Color4u8::Color4u8() : Color4u8(0, 0, 0, 1) { }
	Color4u8::Color4u8(const uint8_t Red, const uint8_t Green, const uint8_t Blue) : Color4u8(Red, Green, Blue, 1) { }

	Color4u8::Color4u8(const uint8_t Red, const uint8_t Green, const uint8_t Blue, const uint8_t Alpha) :
		m_Red(m_Red),
		m_Green(m_Green),
		m_Blue(m_Blue),
		m_Alpha(m_Alpha)
	{
		
	}

	Color4u8::~Color4u8()
	{
		
	}

	void Color4u8::WriteToStream(FileWriter& stream)
	{
		// in LVL -> MTRL, color order is BGRA
		stream.WriteByte(m_Blue);
		stream.WriteByte(m_Green);
		stream.WriteByte(m_Red);
		stream.WriteByte(m_Alpha);
	}

	void Color4u8::ReadFromStream(FileReader& stream)
	{
		// in LVL -> MTRL, color order is BGRA
		m_Blue = stream.ReadByte();
		m_Green = stream.ReadByte();
		m_Red = stream.ReadByte();
		m_Alpha = stream.ReadByte();
	}

	String Color4u8::ToString() const
	{
		return fmt::format("[R: {}, G: {}, B: {}, A: {}]", m_Red, m_Green, m_Blue, m_Alpha).c_str();
	}
}
