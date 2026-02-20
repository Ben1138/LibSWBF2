#pragma once
#include <LibSWBF2/Chunks/BaseChunk.h>

namespace LibSWBF2::Chunks::MSH
{
	struct GEOM;
	struct SINF;

	struct LIBSWBF2_API BBOX : public BaseChunk
	{
		BBOX() = default;
		~BBOX() = default;

		Vector4 m_Quaternion;
		Vector3 m_Center;
		Vector3 m_Extent;
		float m_SphereRadius = 0.0f;

	protected:
		friend GEOM;
		friend SINF;
		
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}