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
		uint16_t magic = stream.ReadUInt16();
		if (magic != 0x3738)
		{
			THROW("Next clip doesn't start with magic! pos: {:#x}", m_HeaderPosition);
		}

		m_NameHash = stream.ReadUInt32();
		stream.SkipBytes(4);
		m_SampleRate = stream.ReadUInt32();
		stream.SkipBytes(4);
		m_DataLength = stream.ReadUInt32();
		stream.SkipBytes(4);
		m_SampleCount = stream.ReadUInt32();

		// in emo_, it seems like data length and sample count are switched...
		if (m_SampleCount > m_DataLength)
		{
			//LOG_WARN("swapped data length and sample count in sound clip!");
			//std::swap(m_DataLength, m_SampleCount);
		}

		if (m_DataLength == 0 || m_SampleCount == 0)
		{
			LOG_WARN("Found empty sound clip? Data length: {:#x}, Sample count: {} at pos: {:#x}", m_DataLength, m_SampleCount, m_HeaderPosition);
		}
		else
		{
			float_t blockAlign = (float_t)m_DataLength / (float_t)m_SampleCount;
			if (blockAlign != 2.0f)
			{
				LOG_WARN("Found sound clip with a block align of {}! Data length: {:#x}, Sample count: {} at pos: {:#x}", blockAlign, m_DataLength, m_SampleCount, m_HeaderPosition);
			}
		}
		
		//if (m_SampleRate != 44100 && m_SampleRate != 22050)
		//{
		//	LOG_WARN("Weird sample rate {} encountered in sound clip header at pos: {:#x}", m_SampleRate, headerPos);
		//}

		uint8_t headerSize = 48;
		stream.SkipBytes(8);

		// check whether we're in a 48 or 56 sized header, using offset 38
		// as an indicator since it always seems to be 0x2E789FB4 in both BNK and emo_
		uint32_t unknown1 = stream.ReadUInt32();
		if (unknown1 != 0x2E789FB4)
		{
			headerSize = 56;
			stream.SkipBytes(4);
			unknown1 = stream.ReadUInt32();
			if (unknown1 != 0x2E789FB4)
			{
				THROW("Unknown sound clip header size/type at pos: {:#x}", m_HeaderPosition);
			}
		}
		stream.SkipBytes(6);
		return headerSize;
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
	}

	bool SoundClip::TryLookupName(String& result)
	{
		return FNV::Lookup(m_NameHash, result);
	}

	String SoundClip::ToString() const
	{
		String clipName;
		if (!FNV::Lookup(m_NameHash, clipName))
			clipName = std::to_string(m_NameHash).c_str();

		return fmt::format(
			"Name: {}\n"
			"Sample Rate: {}\n"
			"Sample Count: {}\n"
			"Data Length: {}\n"
			"Header Position: {}\n"
			"Data Position: {}\n",
			clipName,
			m_SampleRate,
			m_SampleCount,
			m_DataLength,
			m_HeaderPosition,
			m_DataPosition
		).c_str();
	}
}