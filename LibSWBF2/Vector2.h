#pragma once
#include "stdafx.h"

namespace LibSWBF2
{
	struct Vector2
	{
		Vector2();
		Vector2(const float_t& x, const float_t& y);
		~Vector2();

		virtual void WriteToStream(ofstream& stream);
		virtual void ReadFromStream(ifstream& stream);

		float_t x;
		float_t y;
	};
}