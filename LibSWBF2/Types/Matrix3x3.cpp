#include "stdafx.h"
#include "Types\LibString.h"
#include "Matrix3x3.h"
#include "FileWriter.h"
#include "FileReader.h"

namespace LibSWBF2::Types
{
	void Matrix3x3::WriteToStream(FileWriter& stream)
	{
		stream.WriteFloat(matrix[0][0]);
		stream.WriteFloat(matrix[0][1]);
		stream.WriteFloat(matrix[0][2]);

		stream.WriteFloat(matrix[1][0]);
		stream.WriteFloat(matrix[1][1]);
		stream.WriteFloat(matrix[1][2]);

		stream.WriteFloat(matrix[2][0]);
		stream.WriteFloat(matrix[2][1]);
		stream.WriteFloat(matrix[2][2]);
	}

	void Matrix3x3::ReadFromStream(FileReader& stream)
	{
		matrix[0][0] = stream.ReadFloat();
		matrix[0][1] = stream.ReadFloat();
		matrix[0][2] = stream.ReadFloat();

		matrix[1][0] = stream.ReadFloat();
		matrix[1][1] = stream.ReadFloat();
		matrix[1][2] = stream.ReadFloat();

		matrix[2][0] = stream.ReadFloat();
		matrix[2][1] = stream.ReadFloat();
		matrix[2][2] = stream.ReadFloat();
	}

	String Matrix3x3::ToString()
	{
		return (
			"[[" + std::to_string(matrix[0][0]) + ", " + std::to_string(matrix[0][1]) + ", " + std::to_string(matrix[0][2]) + "]" +
			" [" + std::to_string(matrix[1][0]) + ", " + std::to_string(matrix[1][1]) + ", " + std::to_string(matrix[1][2]) + "]" +
			" [" + std::to_string(matrix[2][0]) + ", " + std::to_string(matrix[2][1]) + ", " + std::to_string(matrix[2][2]) + "]]"
			).c_str();
	}
}