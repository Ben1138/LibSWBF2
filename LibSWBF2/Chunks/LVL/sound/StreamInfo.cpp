#include "pch.h"

#include "StreamInfo.h"
#include "Stream.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::sound
{
	void StreamInfo::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void StreamInfo::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void StreamInfo::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		bool breakOut = false;

		while (ThereIsAnother(stream))
		{
			FNVHash next = (FNVHash) stream.ReadUInt32();

			/*
			if (m_NumSegments == m_SoundHeaders.Size() && m_NumSegments > 0)
			{
				break;
			}
			*/

			switch (next)
			{
				case "Name"_fnv:
					m_Name = (FNVHash) stream.ReadUInt32();
					break;

				case "Format"_fnv:
					m_Format = (FNVHash) stream.ReadUInt32(); 
					break;

				case "NumChannels"_fnv:
					m_NumChannels = stream.ReadUInt32();
					break;

				case "NumSegments"_fnv:
					m_NumSegments = stream.ReadUInt32();

				case "Size"_fnv:
					m_CombinedSoundSize = stream.ReadUInt32(); 
					break;

				case "Sample"_fnv:
					m_SoundHeaders.Emplace().ReadHeaderFromStream(stream); 
					break;	

				case "Padding"_fnv:
					m_Padding = stream.ReadUInt32(); 
					breakOut = true;
					break;		

				default:
					break;
			}

			if (breakOut)
			{ 
				break;
			}
		}

		BaseChunk::EnsureEnd(stream);
	}

	String StreamInfo::ToString() const
	{
		String soundsStr;
		for (int i = 0; i < m_SoundHeaders.Size(); i++)
		{
			soundsStr = soundsStr + fmt::format("\n{}:\n", i).c_str();
			soundsStr = soundsStr + m_SoundHeaders[i].ToString();
		}

		return fmt::format(
			"Name: 0x{0:x}\n"
			"Format: 0x{1:x}\n"
			"Num Channels: {2}\n"
			"Num Segments: {3}\n"
			"Combined Sound Size: {4}\n"
			"Padding: {5}\n"
			"\n{6} Segments:\n{7}",
			m_Name,
			m_Format,
			m_NumChannels,
			m_NumSegments,
			m_CombinedSoundSize,
			m_Padding,
			m_SoundHeaders.Size(),
			soundsStr.Buffer()
		).c_str();
	}
}