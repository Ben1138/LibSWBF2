#pragma once

#include "stdafx.h"
#include "Chunks/GenericChunk.h"
#include "Chunks/RawData.h"
#include "Chunks/LVL/common/DATA.h"
#include "Types/Enums.h"

using namespace LibSWBF2::Chunks::LVL::common;

namespace LibSWBF2::Chunks::LVL::lght
{

struct LIBSWBF2_API DATA_VEC4 : public DATA {

	Vector4 m_Vec;
	void RefreshSize() override;
	void WriteToStream(FileWriter& stream) override;
	void ReadFromStream(FileReader& stream) override;

};
}
