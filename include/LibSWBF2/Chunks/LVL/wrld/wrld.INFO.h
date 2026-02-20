#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Chunks/STR.h>
#include <LibSWBF2/Chunks/LVL/wrld/XFRM.h>
#include <LibSWBF2/Chunks/LVL/wrld/SIZE.h>

namespace LibSWBF2::Chunks::LVL::wrld
{
	struct LIBSWBF2_API INFO : public GenericChunk<"INFO"_m>
	{
	public:
		STR<"TYPE"_m>* p_Type;
		STR<"NAME"_m>* p_Name;
		XFRM* p_XFRM;				// contains rotation and position
		SIZE* p_SIZE;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}