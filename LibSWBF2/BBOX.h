#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::MSH
{
	struct BBOX : public BaseChunk
	{
		BBOX();
		~BBOX();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

	private:
		Vector4 Quaternion;
		Vector3 Center;
		Vector3 Extent;
		float_t SphereRadius;
	};
}