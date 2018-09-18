#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct BBOX : public BaseChunk
	{
		BBOX();
		~BBOX();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		Vector4 m_Quaternion;
		Vector3 m_Center;
		Vector3 m_Extent;
		float_t m_SphereRadius;
	};
}