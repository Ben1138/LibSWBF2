#pragma once
#include "Vector2.h"

namespace LibSWBF2::Types
{
	struct Vector3 : public Vector2
	{
		Vector3();
		Vector3(const float_t& x, const float_t& y, const float_t& z);
		~Vector3();

		void WriteToStream(ofstream& stream) override;
		void ReadFromStream(ifstream& stream) override;

		float_t z;
	};
}