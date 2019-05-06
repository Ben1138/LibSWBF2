#pragma once
#include "BaseChunk.h"
#include "SINF.h"
#include "MATL.h"
#include "MODL.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MSH;

	struct LIBSWBF2_EXP MSH2 : public BaseChunk
	{
		SINF m_SceneInformation;
		MATL m_MaterialList;
		List<MODL> m_Models;

	protected:
		friend MSH;

		MSH2() = default;
		~MSH2() = default;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}