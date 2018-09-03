#include "stdafx.h"
#include "Vector2.h"

namespace LibSWBF2
{
	Vector2::Vector2() : x(x), y(y) 
	{
	
	}

	Vector2::Vector2(const float_t& x, const float_t& y) : x(x), y(y) 
	{
	
	}

	Vector2::~Vector2()
	{

	}

	void Vector2::WriteToStream(ofstream& stream)
	{
		stream << x << y;
	}

	void Vector2::ReadFromStream(ifstream& stream)
	{
		stream >> x >> y;
	}
}