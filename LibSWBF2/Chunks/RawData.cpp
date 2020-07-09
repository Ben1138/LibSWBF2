#include "stdafx.h"
#include "RawData.h"
#include "Exceptions.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks
{
	template<uint32_t Header>
	RawData<Header>::~RawData()
	{
		delete[] p_Data;
	}

	template<uint32_t Header>
	bool RawData<Header>::GetData(uint8_t*& data, size_t& size)
	{
		if (p_Data == nullptr || BaseChunk::GetDataSize() == 0)
		{
			data = nullptr;
			size = 0;
			return false;
		}

		data = p_Data;
		size = BaseChunk::GetDataSize();
	}

	template<uint32_t Header>
	void RawData<Header>::RefreshSize()
	{
		throw LibException("Not implemented!");
	}

	template<uint32_t Header>
	void RawData<Header>::WriteToStream(FileWriter& stream)
	{
		throw LibException("Not implemented!");
	}

	template<uint32_t Header>
	void RawData<Header>::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		GenericChunk<Header>::Check(stream);

		size_t dataSize = BaseChunk::GetDataSize();
		p_Data = new uint8_t[dataSize];
		
		if (!stream.ReadBytes(p_Data, dataSize))
		{
			LOG_ERROR("Could not read binary data of size {} at position {}", dataSize, stream.GetPosition());
			delete[] p_Data;
			p_Data = nullptr;
		}

		BaseChunk::EnsureEnd(stream);
	}
}

namespace LibSWBF2::Chunks
{
	template LIBSWBF2_API struct RawData<"BODY"_m>;
}