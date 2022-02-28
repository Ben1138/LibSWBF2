#include "pch.h"
#include "RawData.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks
{
	template<uint32_t Header>
	RawData<Header>::~RawData()
	{
		delete[] p_Data;
	}

	template<uint32_t Header>
	bool RawData<Header>::GetData(const uint8_t*& data, size_t& size) const
	{
		if (p_Data == nullptr || BaseChunk::GetDataSize() == 0)
		{
			data = nullptr;
			size = 0;
			return false;
		}

		data = p_Data;
		size = BaseChunk::GetDataSize();
		return true;
	}

	template<uint32_t Header>
	void RawData<Header>::RefreshSize()
	{
		THROW("Not implemented!");
	}

	template<uint32_t Header>
	void RawData<Header>::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
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
			LOG_WARN("Could not read binary data of size {:#x} at position {:#x}", dataSize, stream.GetPosition());
			delete[] p_Data;
			p_Data = nullptr;
		}

		BaseChunk::EnsureEnd(stream);
	}

	template<uint32_t Header>
	String RawData<Header>::ToString() const
	{
		return fmt::format("Raw data chunk with {} bytes of data.\nData successfully read: {}", BaseChunk::GetDataSize(), p_Data != nullptr).c_str();
	}

}

namespace LibSWBF2::Chunks
{
	template LIBSWBF2_API struct RawData<"BODY"_m>;
    template LIBSWBF2_API struct RawData<"DATA"_m>;
    template LIBSWBF2_API struct RawData<"POSK"_m>;
    template LIBSWBF2_API struct RawData<"ROTK"_m>;
    template LIBSWBF2_API struct RawData<"Data"_fnv>;
}
