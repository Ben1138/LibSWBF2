#include "stdafx.h"
#include "Vector4.h"

namespace LibSWBF2
{
	Vector4::Vector4() : Vector3(), w(0)
	{
		
	}

	Vector4::Vector4(const float& x, const float& y, const float& z, const float& w) : Vector3(x, y, z), w(w)
	{
		
	}

	Vector4::~Vector4()
	{

	}
}