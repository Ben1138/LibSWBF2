#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Chunks/LVL/tern/PTCH.VBUF.h>
#include <LibSWBF2/Chunks/LVL/tern/PTCH.IBUF.h>
#include <LibSWBF2/Chunks/LVL/tern/PTCH.INFO.h>

namespace LibSWBF2::Chunks::LVL::terrain
{
	struct LIBSWBF2_API PTCH : public GenericChunk<"PTCH"_m>
	{
	public:
		VBUF* m_TextureBuffer;
		VBUF* m_GeometryBuffer;
		VBUF* m_TextureExtraBuffer;

		IBUF* m_GeometryIndexBuffer;
		IBUF* m_TextureExtraIndexBuffer;

		PTCH_INFO* p_PatchInfo;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}