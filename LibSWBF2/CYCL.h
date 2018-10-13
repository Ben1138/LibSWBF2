#pragma once
#include "BaseChunk.h"
#include "STRING.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct ANM2;

	struct CYCL : public BaseChunk
	{
		CYCL() = default;
		~CYCL() = default;

		uint32_t m_NumberOfAnimations;
		STRING m_AnimationName;
		float_t m_FrameRate;
		uint32_t m_PlayStyle;
		uint32_t m_FirstFrame;
		uint32_t m_LastFrame;

	protected:
		friend CYCL;
		
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}