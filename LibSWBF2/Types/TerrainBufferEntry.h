#pragma once
#include "LibString.h"
#include "Vector3.h"
#include "Color.h"

namespace LibSWBF2
{
	class FileReader;
	class FileWriter;
}

namespace LibSWBF2::Types
{
	struct LIBSWBF2_API TerrainBufferEntry
	{
		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		String ToString();

		Vector3 m_Position;
		Vector3 m_Normal;
		Color m_Color;
	};
}