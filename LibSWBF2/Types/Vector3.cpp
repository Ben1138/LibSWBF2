#include "stdafx.h"
#include "Vector3.h"

namespace LibSWBF2::Types
{
	Vector3::Vector3() : Vector2(), m_Z(0)
	{
		
	}

	Vector3::Vector3(const float_t& x, const float_t& y, const float_t& z) : Vector2(x, y), m_Z(z)
	{
		
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
}