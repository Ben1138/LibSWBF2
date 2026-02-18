#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Chunks/STR.h>
#include <LibSWBF2/Chunks/STRMULT.h>
#include <LibSWBF2/Chunks/LVL/skel/skel.INFO.h>
#include <LibSWBF2/Chunks/LVL/skel/skel.XFRM.h>

namespace LibSWBF2::Chunks::LVL::skel
{
	struct LIBSWBF2_API skel : public GenericChunk<"skel"_m>
	{
	public:
		INFO* p_Info;
		STRMULT<"NAME"_m>* p_BoneNames;
		STRMULT<"PRNT"_m>* p_BoneParents;
		XFRM* p_BoneTransforms;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}