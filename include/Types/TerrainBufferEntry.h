#pragma once
#include <Types/LibString.h>
#include <Types/Vector3.h>
#include <Types/Color4u8.h>

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

		String ToString() const;

		Vector3 m_Position;
		Vector3 m_Normal;
		Color4u8 m_Color;
	};
}