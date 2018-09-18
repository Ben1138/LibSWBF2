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

	private:
		NAME m_NAME;
		MTYP m_MTYP;
		NAME m_PRNT;
		FLGS m_FLGS;
		TRAN m_TRAN;
	};
}
