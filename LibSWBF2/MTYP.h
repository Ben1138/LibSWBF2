#pragma once
#include "BaseChunk.h"

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

	struct MTYP : public BaseChunk
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
