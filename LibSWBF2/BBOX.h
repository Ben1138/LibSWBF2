#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct GEOM;
	struct SINF;

	struct BBOX : public BaseChunk
	{
		BBOX() = default;
		~BBOX() = default;

		Vector4 m_Quaternion;
		Vector3 m_Center;
		Vector3 m_Extent;
		float_t m_SphereRadius;

	protected:
		friend GEOM;
		friend SINF;
		
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}