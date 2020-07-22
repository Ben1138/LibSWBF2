#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"
#include "segm.INFO.h"
#include "MTRL.h"
#include "TNAM.h"
#include "IBUF.h"
#include "SKIN.h"
#include "BMAP.h"
#include "modl.VBUF.h"

namespace LibSWBF2::Chunks::LVL::modl
{
	struct LIBSWBF2_API segm : public GenericChunk<"segm"_m>
	{
	public:
		segment::INFO* p_Info;
		MTRL* p_Material;
		STR<"RTYP"_m>* p_RenderType;	// string seems to represent an enum
		IBUF* p_IndexBuffer;
		STR<"BNAM"_m>* p_Parent;
		SKIN* p_Skin;					// OPTIONAL
		BMAP* p_BoneMap;				// OPTIONAL. This mapper seems unnecessary to me...

		List<VBUF*> m_VertexBuffers;
		List<TNAM*> m_Textures;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}