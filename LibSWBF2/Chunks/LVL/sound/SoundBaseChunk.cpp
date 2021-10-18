#include "pch.h"
#include "Chunks/BaseChunk.h"
#include "SoundBaseChunk.h"
#include "InternalHelpers.h"
#include "FileReader.h"

#include <iostream>

namespace LibSWBF2::Chunks::LVL::sound
{
	template<uint32_t Header>
	void SoundBaseChunk<Header>::RefreshSize()
	{
		THROW("Not implemented!");
	}

	template<uint32_t Header>
	void SoundBaseChunk<Header>::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	template<uint32_t Header>
	void SoundBaseChunk<Header>::ReadFromStream(FileReader& stream)
	{
		BaseChunk::m_ChunkPosition = stream.GetPosition();
		BaseChunk::m_Header = stream.ReadChunkHeader(false);

		//std::cout << "On header: " << BaseChunk::m_Header.ToString().Buffer() << std::endl;


		/*
		m_SignedSize = stream.ReadInt32();
		stream.SetPosition(stream.GetPosition() - 4);
		m_BadSize = stream.ReadUInt32();
		*/

		BaseChunk::m_Size = stream.ReadUInt32(); //(uint32_t) m_SignedSize;

		LOG_INFO("Position: {}", BaseChunk::m_ChunkPosition);
		LOG_INFO("Header: {}", BaseChunk::m_Header);
		LOG_INFO("Size: {:#x}", BaseChunk::m_Size);

		if (BaseChunk::m_Size < 0)
		{
			THROW("Invalid Chunk: '{}' Size: {:#x} At Position: {:#x} with File Size of: {:#x}", BaseChunk::m_Header, BaseChunk::m_Size, stream.GetPosition(), stream.GetFileSize());
		}

		if (stream.GetPosition() + BaseChunk::m_Size > 8 + stream.GetFileSize())
		{
			THROW("Chunk is too big and will end up out of file! Chunk: '{}' Size: {:#x} At Position: {:#x} with File Size of: {:#x}", BaseChunk::m_Header, BaseChunk::m_Size, stream.GetPosition() - 8, stream.GetFileSize());
		}
	}


	template<uint32_t Header>
	Types::String SoundBaseChunk<Header>::ToString() const
	{
		std::string r = fmt::format("Sound chunk with size: {0} (would've been mistaken for {1})", m_SignedSize, m_BadSize);
		return r.c_str();
	}


	template struct LIBSWBF2_API SoundBaseChunk<0>;
	template struct LIBSWBF2_API SoundBaseChunk<"StreamList"_fnv>;
	template struct LIBSWBF2_API SoundBaseChunk<"Stream"_fnv>;
	template struct LIBSWBF2_API SoundBaseChunk<"Info"_fnv>;
	template struct LIBSWBF2_API SoundBaseChunk<"SoundBankList"_fnv>;
	template struct LIBSWBF2_API SoundBaseChunk<"Data"_fnv>;
	template struct LIBSWBF2_API SoundBaseChunk<"SampleBank"_fnv>;
}
