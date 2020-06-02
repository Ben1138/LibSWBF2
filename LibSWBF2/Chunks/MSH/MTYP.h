#pragma once
#include "Chunks\BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	enum class EModelType : uint32_t
	{
		Null = 0,
		Skin = 1,
		Envelope = 3,
		Static = 4,
		Shadow = 6
	};

	struct MODL;

	struct LIBSWBF2_EXP MTYP : public BaseChunk
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
