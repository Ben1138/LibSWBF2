#pragma once

#include "stdafx.h"
#include "Chunks/GenericChunk.h"
#include "Chunks/RawData.h"
#include "Chunks/LVL/common/DATA.h"
#include "Types/Enums.h"

using LibSWBF2::Chunks::LVL::common::DATA;

namespace LibSWBF2::Chunks::LVL::lght
{
struct LIBSWBF2_API DATA_LIGHTTYPE : public DATA {

	float_t m_LightType;
	void RefreshSize() override;
	void WriteToStream(FileWriter& stream) override;
	void ReadFromStream(FileReader& stream) override;

	String ToString() override;

};
}
