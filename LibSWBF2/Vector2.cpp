#include "stdafx.h"
#include "Vector2.h"

namespace LibSWBF2::Types
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

	void Vector2::WriteToStream(FileWriter& stream)
	{
		stream.WriteFloat(x);
		stream.WriteFloat(y);
	}

	void Vector2::ReadFromStream(FileReader& stream)
	{
		x = stream.ReadFloat();
		y = stream.ReadFloat();
	}
}