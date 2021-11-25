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

		while (ThereIsAnother(stream))
		{
			FNVHash next = (FNVHash) stream.ReadUInt32();

			switch (next)
			{
				case "Name"_fnv:
					m_Name = (FNVHash) stream.ReadUInt32();
					break;

				case "Format"_fnv:
					m_Format = (ESoundFormat) stream.ReadUInt32(); 
					break;

				case "NumChannels"_fnv:
					m_NumChannels = stream.ReadUInt32();
					break;

				case "NumSegments"_fnv:
					m_NumSegments = stream.ReadUInt32();

				case "Size"_fnv:
					m_CombinedSoundSize = stream.ReadUInt32(); 
					break;

				case "SegmentInfo"_fnv:
					next = (FNVHash) stream.ReadUInt32();
					while (next == "Sample"_fnv)
					{
						m_SoundHeaders.Emplace().ReadHeaderFromStream(stream);
						next = (FNVHash) stream.ReadUInt32(); 
					}
					stream.SetPosition(stream.GetPosition() - 4);
					break;	

				case "Padding"_fnv:
					m_Padding = stream.ReadUInt32();
					stream.SkipBytes(m_Padding - 4);
					break;		

				default:
					break;
			}
		}

		BaseChunk::EnsureEnd(stream);
	}

	String StreamInfo::HeaderToString() const
	{
		return fmt::format(
			"Name: 0x{0:x}\n"
			"Format: {1}\n"
			"Num Channels: {2}\n"
			"Num Segments: {3}\n"
			"Combined Sound Size: {4}\n"
			"Padding: {5}\n",
			m_Name,
			SoundFormatToString(m_Format),
			m_NumChannels,
			m_NumSegments,
			m_CombinedSoundSize,
			m_Padding
		).c_str();
	}

	String StreamInfo::SegmentInfoToString() const
	{
		String soundsStr;
		for (int i = 0; i < m_SoundHeaders.Size(); i++)
		{
			soundsStr = soundsStr + fmt::format("\n{}:\n", i).c_str();
			soundsStr = soundsStr + m_SoundHeaders[i].ToString();
		}
		return soundsStr;
	}

	String StreamInfo::ToString() const
	{
		return HeaderToString() + "\nSegment headers: \n" + SegmentInfoToString();
	}
}