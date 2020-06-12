#pragma once
#include "Chunks\BaseChunk.h"

namespace LibSWBF2::Chunks::MSH
{
	struct MODL;

	struct LIBSWBF2_EXP TRAN : public BaseChunk
	{
		TRAN() = default;
		~TRAN() = default;

		Vector3 m_Scale;
		Vector4 m_Rotation;
		Vector3 m_Translation;

	protected:
		friend MODL;
		
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}