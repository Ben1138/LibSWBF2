#pragma once
#include "BaseChunk.h"
#include "Animation.h"

namespace LibSWBF2::Chunks::Mesh
{
	using Types::Animation;

	struct ANM2;

	struct CYCL : public BaseChunk
	{
		const int ANIMATION_NAME_STR_SIZE = 64;

		CYCL() = default;
		~CYCL() = default;

		vector<Animation> m_Animations;

	protected:
		friend ANM2;
		
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}