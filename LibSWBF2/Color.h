#pragma once
#include "FileWriter.h"
#include "FileReader.h"

namespace LibSWBF2::Types
{
	struct Color
	{
		static const ChunkSize Size = sizeof(float_t) * 4;

		Color();
		Color(const float_t& r, const float_t& g, const float_t& b);
		Color(const float_t& r, const float_t& g, const float_t& b, const float_t& a);
		~Color();

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		float_t r;
		float_t g;
		float_t b;
		float_t a;
	};
}