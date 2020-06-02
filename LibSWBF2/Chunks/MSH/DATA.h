#pragma once
#include "Chunks\BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MATD;

	struct LIBSWBF2_EXP DATA : public BaseChunk
	{
		DATA() = default;
		~DATA() = default;

		Color m_Diffuse;
		Color m_Specular;
		Color m_Ambient;
		float_t m_SpecularSharpness = 0.0f;

	protected:
		friend MATD;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}