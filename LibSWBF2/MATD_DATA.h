#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::MSH
{
	struct MATD_DATA : public BaseChunk
	{
		MATD_DATA();
		~MATD_DATA();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

	private:
		Color Diffuse;
		Color Specular;
		Color Ambient;
		float_t SpecularSharpness;
	};
}