#pragma once
#include "BaseChunk.h"
#include "NAME.h"
#include "MTYP.h"
#include "FLGS.h"
#include "TRAN.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MODL : public BaseChunk
	{
		MODL();
		~MODL();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		STRING m_NAME;
		MTYP m_MTYP;
		STRING m_PRNT;
		FLGS m_FLGS;
		TRAN m_TRAN;
	};
}
