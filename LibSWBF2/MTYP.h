#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	enum EModelType : uint32_t
	{
		Null = 0,
		Skin = 1,
		Envelope = 3,
		Static = 4,
		Shadow = 6
	};

	struct MTYP : public BaseChunk
	{
		MTYP();
		~MTYP();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

	private:
		EModelType ModelType;
	};
}
