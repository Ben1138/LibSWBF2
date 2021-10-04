#pragma once
#include "Chunks/GenericChunk.h"
#include "Types/Vector3.h"
#include "Types/Vector4.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	struct LIBSWBF2_API TNOJ : public GenericChunk<"TNOJ"_m>
	{
	public:

		Vector3 m_BasePosition;
		Vector4 m_BaseRotation;

		uint32_t m_BoneCRC;
		uint32_t m_ParentBoneCRC;

		// Child and sibling CRCs as well? Why would these be included in the first place?



	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}