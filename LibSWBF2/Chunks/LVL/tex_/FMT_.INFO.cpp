#include "stdafx.h"
#include "FMT_.INFO.h"
#include "Logging\Logger.h"
#include "DirectX\DXHelpers.h"

namespace LibSWBF2::Chunks::LVL::FMT
{
	void INFO::RefreshSize()
	{
		throw std::runtime_error("Not implemented!");
	}

	void INFO::WriteToStream(FileWriter& stream)
	{
		throw std::runtime_error("Not implemented!");
	}

	void INFO::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		m_Format = (D3DFORMAT)stream.ReadUInt32();
		m_Width = stream.ReadUInt16();
		m_Height = stream.ReadUInt16();
		m_Depth = stream.ReadUInt16();
		m_MipmapCount = stream.ReadUInt16();
		m_Type = stream.ReadUInt32();

		BaseChunk::EnsureEnd(stream);
	}

	String INFO::ToString()
	{
		string result = "Format:\t" + D3DToString(m_Format) + "\n";
		result += "Width:\t" + std::to_string(m_Width) + "\n";
		result += "Height:\t" + std::to_string(m_Height) + "\n";
		result += "Depth:\t" + std::to_string(m_Depth) + "\n";
		result += "Mip Map Count:\t" + std::to_string(m_MipmapCount) + "\n";
		result += "Type:\t" + std::to_string(m_Type) + "\n";
		return result.c_str();
	}
}