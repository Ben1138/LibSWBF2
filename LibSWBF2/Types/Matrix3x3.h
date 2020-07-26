#pragma once

namespace LibSWBF2
{
	class FileReader;
	class FileWriter;
}

namespace LibSWBF2::Types
{
	struct LIBSWBF2_API Matrix3x3
	{
		static const ChunkSize SIZE = sizeof(float_t) * 3 * 3;

		Matrix3x3() = default;
		~Matrix3x3() = default;

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		// first index = row, second index = column
		float_t matrix[3][3];

		String ToString();
	};
}