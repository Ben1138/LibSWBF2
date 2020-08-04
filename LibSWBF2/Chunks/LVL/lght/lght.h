#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"

/*
'lght' chunk spec

'lght' (number of lights not explicitly stated, presumably derived from lght chunk length)

	'name' (? 8 bytes, seems to signal start of light list, kind of redundant...)
		
		'data' local light/global light flag (? bytes), name string (? bytes)

		'scop' lighttype/chunklength (uint32) a8 = omni, f4 = spot, e0 = dir
		              						  c0 = omni (cast specular)
		    'data' rotation, 25 (28) bytes

		    'data' position, 21 (24) bytes

		    'data' 		  ?, 13 (16) bytes

			'data'    color, 21 (24) bytes

			'data'		  ?,  9 (12) bytes

			'data'		  ?, 13 (16) bytes
*/

namespace LibSWBF2::Chunks::LVL::light
{
	struct LIBSWBF2_API lght : public GenericChunk<"lght"_m>
	{
	public:
		STR<"NAME"_m>* p_Name;
		List<DATA*> lightHeaders;
		List<SCOP*> lightBlocks;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}
