#pragma once
#include "Chunks/GenericChunk.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	struct LEKS;


	struct LIBSWBF2_API ZAF_BIN_ : public GenericChunk<"BIN_"_m>
	{
	public:

		/*
		Should always be 8, as in zaa_.
		If there are other versions relevant to BF1/2, I'm not
		sure how they could be reversed since Zenasset
		doesn't take versioning parameters...
		*/ 
		uint32_t m_Version = 8; 

		// Just a list of joints
		LEKS *p_Skeleton;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}