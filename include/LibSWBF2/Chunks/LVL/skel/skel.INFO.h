#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Types/LibString.h>
#include <LibSWBF2/Types/Enums.h>
#include <LibSWBF2/Types/Vector3.h>

namespace LibSWBF2::Chunks::LVL::skel
{
	struct LIBSWBF2_API INFO : public GenericChunk<"INFO"_m>
	{
	public:
		String m_ModelName;
		uint32_t m_BoneCount;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}