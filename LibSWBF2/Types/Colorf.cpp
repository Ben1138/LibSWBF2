#include "stdafx.h"
#include "Colorf.h"
#include "Logging\Logger.h"

namespace LibSWBF2::Types
{
	Colorf::Colorf() : Colorf(0, 0, 0, 1) { }
	Colorf::Colorf(const float_t Red, const float_t Green, const float_t Blue) : Colorf(Red, Green, Blue, 1) { }

	Colorf::Colorf(const float_t Red, const float_t Green, const float_t Blue, const float_t Alpha) : 
		m_Red(clamp(m_Red, 0.0f, 1.0f)),
		m_Green(clamp(m_Green, 0.0f, 1.0f)),
		m_Blue(clamp(m_Blue, 0.0f, 1.0f)),
		m_Alpha(clamp(m_Alpha, 0.0f, 1.0f))
	{
		
	}

	Colorf::~Colorf()
	{
		
	}

	void Colorf::WriteToStream(FileWriter& stream)
	{
		stream.WriteFloat(m_Red);
		stream.WriteFloat(m_Green);
		stream.WriteFloat(m_Blue);
		stream.WriteFloat(m_Alpha);
	}

	void Colorf::ReadFromStream(FileReader& stream)
	{
		m_Red = stream.ReadFloat();
		m_Green = stream.ReadFloat();
		m_Blue = stream.ReadFloat();
		m_Alpha = stream.ReadFloat();
	}
}