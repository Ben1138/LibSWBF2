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
		Vector3 Scale;
		Vector4 Rotation;
		Vector3 Translation;
	};
}