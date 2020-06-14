#pragma once
#include "Chunks\BaseChunk.h"
#include "Types\Enums.h"

namespace LibSWBF2::Chunks::MSH
{
	struct MODL;

	struct LIBSWBF2_API MTYP : public BaseChunk
	{
		MTYP() = default;
		~MTYP() = default;

		EModelType m_ModelType = EModelType::Null;

	protected:
		friend MODL;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}
