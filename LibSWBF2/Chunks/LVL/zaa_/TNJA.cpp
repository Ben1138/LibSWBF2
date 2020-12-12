#include "stdafx.h"
#include "zaa_.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	void TNJA::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void TNJA::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void TNJA::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		MINA *animData = dynamic_cast<BIN_*>(GetParent()) -> p_AnimsMetadata;

		if (animData == nullptr)
		{
			LOG_ERROR("Anim read failed....");
			BaseChunk::EnsureEnd(stream);
			return;
		}

		for (int i = 0; i < animData -> m_AnimNameHashes.Size(); i++)
		{
			for (int j = 0; j < animData -> m_AnimBoneCounts[i]; j++)
			{
				m_BoneCRCs.Add(stream.ReadUInt32());

				for (int k = 0; k < 11; k++)
				{
					if (k < 4)
					{
						m_RotationOffsets.Add(stream.ReadUInt32());
					}
					else if (k < 7)
					{
						m_TranslationOffsets.Add(stream.ReadUInt32());
					}
					else
					{
						m_TranslationParams.Add(stream.ReadFloat());
					}
				}				
			}
		}

		BaseChunk::EnsureEnd(stream);
	}

	String TNJA::ToString()
	{
		return fmt::format(
			"Num bone CRCs: {}\n",
			m_BoneCRCs.Size()
		).c_str();
	}
}