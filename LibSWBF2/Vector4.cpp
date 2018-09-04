#include "stdafx.h"
#include "Vector4.h"

namespace LibSWBF2::Types
{
	Vector4::Vector4() : Vector3(), w(0)
	{
		
	}

	Vector4::Vector4(const float_t& x, const float_t& y, const float_t& z, const float_t& w) : Vector3(x, y, z), w(w)
	{
		
	}

	Vector4::~Vector4()
	{

	}

	void Vector4::WriteToStream(FileWriter& stream)
	{
		stream.WriteFloat(x);
		stream.WriteFloat(y);
		stream.WriteFloat(z);
		stream.WriteFloat(w);
	}

	void Vector4::ReadFromStream(FileReader& stream)
	{
		x = stream.ReadFloat();
		y = stream.ReadFloat();
		z = stream.ReadFloat();
		w = stream.ReadFloat();
	}
}