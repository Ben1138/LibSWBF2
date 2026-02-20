#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Chunks/STR.h>
#include <LibSWBF2/Types/Enums.h>
#include <LibSWBF2/Types/Vector3.h>

namespace LibSWBF2::Chunks::LVL::modl
{
	struct LIBSWBF2_API INFO : public GenericChunk<"INFO"_m>
	{
	public:
		uint32_t m_Unknown[5];
		Vector3 m_VertexBox[2];
		Vector3 m_VisibilityBox[2];
		uint32_t m_FaceCount;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}