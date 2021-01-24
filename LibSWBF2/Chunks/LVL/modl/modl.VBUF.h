#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"
#include "Types/Enums.h"

namespace LibSWBF2::Chunks::LVL::modl
{
	struct LIBSWBF2_API VBUF : public GenericChunk<"VBUF"_m>
	{
	public:
		uint32_t m_Count;
		uint32_t m_Stride;	// bytes per vertex
		EVBUFFlags m_Flags;
		
		List<Vector3> m_Positions;
		List<Vector3> m_Normals;
		List<Vector3> m_Tangents;
		List<Vector3> m_BiTangents;
		List<Color4u8> m_Colors;
		List<Vector2> m_TexCoords;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}