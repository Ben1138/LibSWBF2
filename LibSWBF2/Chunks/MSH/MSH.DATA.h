#pragma once
#include "Chunks/BaseChunk.h"

namespace LibSWBF2::Chunks::MSH
{
	struct MATD;

	struct LIBSWBF2_API DATA : public BaseChunk
	{
		DATA() = default;
		~DATA() = default;

		Color4u8 m_Diffuse;
		Color4u8 m_Specular;
		Color4u8 m_Ambient;
		float_t m_SpecularSharpness = 0.0f;

	protected:
		friend MATD;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}