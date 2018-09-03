#pragma once

namespace LibSWBF2::Types
{
	struct Color
	{
		static const int32_t Size = sizeof(float_t) * 4;

		Color();
		Color(const float_t& r, const float_t& g, const float_t& b);
		Color(const float_t& r, const float_t& g, const float_t& b, const float_t& a);
		~Color();

		void WriteToStream(ofstream& stream);
		void ReadFromStream(ifstream& stream);

		float_t r;
		float_t g;
		float_t b;
		float_t a;
	};
}