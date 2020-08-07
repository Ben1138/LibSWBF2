#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"



/*
'lght' chunk spec

Example with a single omnidirectional light

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

	struct DATA;
	struct SCOP;

	struct LIBSWBF2_API lght : public GenericChunk<"lght"_m>
	{
	public:

		/*
		Childchunks for each light.  Each light
		has a single header and block chunk.  
		Each DATA contains light's the name and ?.
		Each SCOP contains DATA children which describe
		the various traits of each light.
		*/

		List<DATA *> p_localLightHeaders;
		List<SCOP *> p_localLightBlocks;

		List<DATA *> p_globalLightHeaders; //**will be changed**
		List<SCOP *> p_globalLightBlocks;  //**will be changed**

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}
