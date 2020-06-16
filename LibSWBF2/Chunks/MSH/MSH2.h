#pragma once
#include "Chunks/BaseChunk.h"
#include "SINF.h"
#include "MATL.h"
#include "MODL.h"

namespace LibSWBF2::Chunks::MSH
{
	struct MSH;

	struct LIBSWBF2_API MSH2 : public BaseChunk
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