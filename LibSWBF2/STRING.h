#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MATD;
	struct MODL;
	struct SINF;

	struct STRING : public BaseChunk
	{
		STRING() = default;
		~STRING() = default;

		string m_Text;

	protected:
		friend MATD;
		friend MODL;
		friend SINF;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}