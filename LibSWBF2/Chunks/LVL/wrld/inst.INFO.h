#pragma once
#include "Chunks\GenericChunk.h"
#include "Chunks\STR.h"
#include "XFRM.h"

namespace LibSWBF2::Chunks::LVL::wrld::instance
{
	struct LIBSWBF2_EXP INFO : public GenericChunk<"INFO"_m>
	{
	public:
		STR<"TYPE"_m>* p_Type;
		STR<"NAME"_m>* p_Name;
		XFRM* p_XFRM;				// contains rotation and position

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}