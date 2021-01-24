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
			//LOG_ERROR("Anim read failed....");
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
		BIN_ *parent = dynamic_cast<BIN_*>(GetParent());

		if (parent != nullptr)
		{
			MINA *metadata = parent -> p_AnimsMetadata;
			if (metadata != nullptr)
			{
				//Detailed summary
				std::string fancy = "";

				auto nameCRCs = metadata -> m_AnimNameHashes;

				int rotOffsetI = 0;
				int locOffsetI = 0;
				int locParamsI = 0;

				for (int i = 0; i < nameCRCs.Size(); i++)
				{
					fancy += fmt::format("\nAnim 0x{0:x} decompression parameters: \n", nameCRCs[i]).c_str();

					for (int j = 0; j < metadata -> m_AnimBoneCounts[i]; j++)
					{
						fancy += fmt::format("\tBone 0x{0:x}: \n", m_BoneCRCs[j]).c_str();
						
						fancy += "\t\tComponent TADA offsets: \n\n";

						fancy += fmt::format("\t\t\tRot x: {}\n", m_RotationOffsets[rotOffsetI++]).c_str();
						fancy += fmt::format("\t\t\tRot y: {}\n", m_RotationOffsets[rotOffsetI++]).c_str();
						fancy += fmt::format("\t\t\tRot z: {}\n", m_RotationOffsets[rotOffsetI++]).c_str();
						fancy += fmt::format("\t\t\tRot w: {}\n\n", m_RotationOffsets[rotOffsetI++]).c_str();

						fancy += fmt::format("\t\t\tLoc x: {}\n", m_TranslationOffsets[locOffsetI++]).c_str();
						fancy += fmt::format("\t\t\tLoc y: {}\n", m_TranslationOffsets[locOffsetI++]).c_str();
						fancy += fmt::format("\t\t\tLoc z: {}\n\n", m_TranslationOffsets[locOffsetI++]).c_str();

						fancy += "\t\tLocation component dequantization params: \n";

						fancy += fmt::format("\t\t\tLoc x bias: {}\n", m_TranslationParams[locParamsI++]).c_str();
						fancy += fmt::format("\t\t\tLoc y bias: {}\n", m_TranslationParams[locParamsI++]).c_str();
						fancy += fmt::format("\t\t\tLoc z bias: {}\n", m_TranslationParams[locParamsI++]).c_str();
						fancy += fmt::format("\t\t\tLoc multiplier: {}\n", m_TranslationParams[locParamsI++]).c_str();
					}
				}

				return fancy.c_str();
			}
		}

		//Basic summary
		return fmt::format(
			"Num bone CRCs: {}\n",
			m_BoneCRCs.Size()
		).c_str();
	}
}