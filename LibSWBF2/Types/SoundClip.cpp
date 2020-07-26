#include "stdafx.h"
#include "Types/LibString.h"
#include "SoundBank.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "InternalHelpers.h"

namespace LibSWBF2::Types
{
	SoundClip::SoundClip()
	{
		this->m_Data = nullptr;
		this->m_NameHash = 0;
		this->m_SampleRate = 0;
		this->m_SmaplesCount = 0;
		this->m_DataLength = 0;
	}

	SoundClip::~SoundClip()
	{
		delete[] m_Data;
	}

	uint8_t* SoundClip::GetSampleData() const
	{
		return m_Data;
	}

	void SoundClip::ReadHeaderFromStream(FileReader& stream)
	{
		// Sound clip header are either 48 or 56 bytes in size

		size_t headerPos = stream.GetPosition();
		uint16_t magic = stream.ReadUInt16();
		if (magic != 0x3738)
		{
			THROW("Next clip doesn't start with magic! pos: {}", headerPos);
		}

		m_NameHash = stream.ReadUInt32();
		stream.SkipBytes(4);
		m_SampleRate = stream.ReadUInt32();
		stream.SkipBytes(4);
		m_DataLength = stream.ReadUInt32();
		stream.SkipBytes(4);
		m_SmaplesCount = stream.ReadUInt32();
		
		if (m_SampleRate != 44100 && m_SampleRate != 22050)
		{
			LOG_WARN("Weird sample rate {} encountered in sound clip header at pos: {}", m_SampleRate, headerPos);
		}

		stream.SkipBytes(8);
		uint32_t unknown1 = stream.ReadUInt32();
		if (unknown1 != 0x2E789FB4)
		{
			stream.SkipBytes(4);
			unknown1 = stream.ReadUInt32();
			if (unknown1 != 0x2E789FB4)
			{
				THROW("Unknown sound clip header size/type at pos: {}", headerPos);
			}
		}
		stream.SkipBytes(6);
	}

	void SoundClip::ReadDataFromStream(FileReader& stream)
	{
		if (m_DataLength == 0)
		{
			LOG_ERROR("Sound Clip data length is 0! Forgot to call 'ReadHeaderFromStream' first?");
			return;
		}

		delete[] m_Data;
		m_Data = new uint8_t[m_DataLength];
		stream.ReadBytes(m_Data, m_DataLength);
	}

	String SoundClip::ToString()
	{
		return fmt::format(
			"Name Hash: {}\n"
			"Sample Rate: {}\n"
			"Sample Count: {}\n"
			"Data Length: {}\n",
			m_NameHash,
			m_SampleRate,
			m_SmaplesCount,
			m_DataLength
		).c_str();
	}
}