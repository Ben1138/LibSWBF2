#pragma once
#include "FileWriter.h"
#include "FileReader.h"

namespace LibSWBF2::Types
{
	struct LIBSWBF2_API Matrix3x3
	{
		static const ChunkSize SIZE = sizeof(float_t) * 3 * 3;

		Matrix3x3() = default;
		~Matrix3x3() = default;

		virtual void WriteToStream(FileWriter& stream);
		virtual void ReadFromStream(FileReader& stream);

		// first index = row, second index = column
		float_t matrix[3][3];

		virtual String ToString();
	};
}