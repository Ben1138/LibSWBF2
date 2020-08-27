#pragma once

#include "stdafx.h"
#include "Chunks/GenericChunk.h"
#include "Chunks/RawData.h"
#include "Chunks/LVL/common/DATA.h"
#include "Types/Enums.h"

using namespace LibSWBF2::Chunks::LVL::common;


namespace LibSWBF2::Chunks::LVL::lght
{

struct LIBSWBF2_API DATA_TAG : public DATA {

	bool m_LocalLight;
	String m_Name;

	void RefreshSize() override;
	void WriteToStream(FileWriter& stream) override;
	void ReadFromStream(FileReader& stream) override;
};
}
