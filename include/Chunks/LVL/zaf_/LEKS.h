#pragma once
#include "Chunks/GenericChunk.h"
//#include "TNOJ.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	struct TNOJ;

	struct LIBSWBF2_API LEKS : public GenericChunk<"LEKS"_m> //SKEL
	{
	public:

		List<TNOJ *> m_Joints; 

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}