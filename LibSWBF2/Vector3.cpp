#include "stdafx.h"
#include "Vector3.h"

namespace LibSWBF2
{
	Vector3::Vector3() : Vector2(), z(0)
	{
		
	}

	Vector3::Vector3(const float_t& x, const float_t& y, const float_t& z) : Vector2(x, y), z(z)
	{
		
	}

	Vector3::~Vector3()
	{

	}

	void Vector3::WriteToStream(ofstream& stream)
	{
		stream << x << y << z;
	}

	void Vector3::ReadFromStream(ifstream& stream)
	{
		stream >> x >> y >> z;
	}
}