#include "pch.h"
#include "Types/LibString.h"
#include "SoundClip.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "InternalHelpers.h"
#include "Hashing.h"

namespace LibSWBF2::Types
{
	SoundClip::SoundClip()
	{
		this->m_HeaderPosition = 0;
		this->m_DataPosition = 0;

		this->m_NameHash = 0;
		this->m_SampleRate = 0;
		this->m_SampleCount = 0;
		this->m_DataLength = 0;
		this->m_Padding = 0;
		this->m_Alias = 0;

		this->m_Data = nullptr;
	}

	SoundClip::~SoundClip()
	{
		delete[] m_Data;
	}

	const uint8_t* SoundClip::GetSampleData() const
	{
		return m_Data;
	}

	uint8_t SoundClip::GetBytesPerSample() const
	{
		float_t blockAlign = (float_t)m_DataLength / (float_t)m_SampleCount;
		return (uint8_t)std::ceil(blockAlign);
	}

	uint8_t SoundClip::ReadHeaderFromStream(FileReader& stream)
	{
		// Sound clip header are either 48 or 56 bytes in size

		m_HeaderPosition = stream.GetPosition();
		
		FNVHash CurrentFieldName = (FNVHash) stream.ReadUInt32();

		while (CurrentFieldName != "SampleEnd"_fnv)
		{
			switch (CurrentFieldName)
			{
				case "ID"_fnv:
					m_NameHash = stream.ReadUInt32();
					break;

				case "Frequency"_fnv:
					m_SampleRate = stream.ReadUInt32();
					break;

				case "Size"_fnv:
					m_DataLength = stream.ReadUInt32();
					break;				

				case "SizeSamples"_fnv:
					m_SampleCount = stream.ReadUInt32();
					break;	

				case "Padding"_fnv:
					m_Padding = stream.ReadUInt32();
					break;	

				case "Alias"_fnv:
					m_Alias = stream.ReadUInt32();
					break;	

				default:
					break;
			}

			CurrentFieldName = (FNVHash) stream.ReadUInt32();
		}

		if (m_DataLength == 0 || m_SampleCount == 0)
		{
			LOG_WARN("Found empty sound clip? Data length: {:#x}, Sample count: {} at pos: {:#x}", m_DataLength, m_SampleCount, m_HeaderPosition);
		}

		return stream.GetPosition() - m_HeaderPosition;
	}

	void SoundClip::ReadDataFromStream(FileReader& stream)
	{
		if (m_DataLength == 0)
		{
			LOG_ERROR("Sound Clip data length is 0! Forgot to call 'ReadHeaderFromStream' first?");
			return;
		}

		m_DataPosition = stream.GetPosition();

		delete[] m_Data;
		m_Data = new uint8_t[m_DataLength];
		stream.ReadBytes(m_Data, m_DataLength);
		stream.SkipBytes(m_Padding);
	}

	bool SoundClip::TryLookupName(String& result)
	{
		return FNV::Lookup(m_NameHash, result);
	}

	String SoundClip::ToString() const
	{
		String clipName;
		if (!FNV::Lookup(m_NameHash, clipName))
			clipName = fmt::format("0x{0:x}", m_NameHash).c_str();

		return fmt::format(
			"Name: {0}\n"
			"Sample Rate: {1}\n"
			"Sample Count: {2}\n"
			"Data Length: {3}\n"
			"Header Position: {4}\n"
			"Data Position: {5}\n"
			"Padding: {6}\n"
			"Alias: 0x{7:x}\n",
			clipName,
			m_SampleRate,
			m_SampleCount,
			m_DataLength,
			m_HeaderPosition,
			m_DataPosition,
			m_Padding,
			m_Alias
		).c_str();
	}
}