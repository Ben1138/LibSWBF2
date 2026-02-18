#pragma once
#include <LibSWBF2/Chunks/BaseChunk.h>
#include <LibSWBF2/Chunks/MSH/SINF.h>
#include <LibSWBF2/Chunks/MSH/MATL.h>
#include <LibSWBF2/Chunks/MSH/MODL.h>

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