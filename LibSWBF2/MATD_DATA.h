#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MATD;

	struct MATD_DATA : public BaseChunk
	{
		MATD_DATA() = default;
		~MATD_DATA() = default;

		Color m_Diffuse;
		Color m_Specular;
		Color m_Ambient;
		float_t m_SpecularSharpness;

	protected:
		friend MATD;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}