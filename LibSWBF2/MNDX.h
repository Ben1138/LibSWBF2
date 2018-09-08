#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::MSH
{
	enum EModelType : uint32_t
	{
		Null = 0,
		Skin = 1,
		Envelope = 3,
		Static = 4,
		Shadow = 6
	};

	struct MNDX : public BaseChunk
	{
		MNDX();
		~MNDX();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

	private:
		uint32_t ModelIndex;
	};
}
