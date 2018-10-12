#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MODL;

	struct TRAN : public BaseChunk
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