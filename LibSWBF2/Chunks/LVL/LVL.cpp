#include "stdafx.h"
#include "LVL.h"
#include "Hashing.h"

namespace LibSWBF2::Chunks::LVL
{
	LVL* LVL::Create()
	{
		return new LVL();
	}

	void LVL::Destroy(LVL* lvl)
	{
		delete lvl;
	}

	bool LVL::ReadFromFile(const String& Path, const List<String>& subLVLsToLoad)
	{
		m_SubLVLsToLoad.Clear();
		for (size_t i = 0; i < subLVLsToLoad.Size(); ++i)
		{
			m_SubLVLsToLoad.Add(FNV::Hash(subLVLsToLoad[i]));
		}

		bool success = BaseChunk::ReadFromFile(Path);
		m_SubLVLsToLoad.Clear();
		return success;
	}
}