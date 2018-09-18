#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct TRAN : public BaseChunk
	{
		TRAN();
		~TRAN();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

	private:
		Vector3 m_Scale;
		Vector4 m_Rotation;
		Vector3 m_Translation;
	};
}