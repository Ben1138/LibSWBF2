#pragma once
#include "BaseChunk.h"
#include "MATI.h"
#include "POSL.h"
#include "WGHT.h"
#include "NRML.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct SEGM : public BaseChunk
	{
		SEGM();
		~SEGM();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		MATI m_MATI;
		POSL m_POSL;
		WGHT m_WGHT;
		NRML m_NRML;
	};
}