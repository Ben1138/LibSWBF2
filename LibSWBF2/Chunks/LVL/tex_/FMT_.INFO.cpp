#include "stdafx.h"
#include "FMT_.INFO.h"
#include "InternalHelpers.h"
#include "DirectX/DXHelpers.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include <fmt/format.h>

namespace LibSWBF2::Chunks::LVL::FMT
{
	void INFO::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void INFO::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
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
		return fmt::format(
			"Format:\t{}\n"
			"Width:\t{}\n"
			"Height:\t{}\n"
			"Depth:\t{}\n"
			"Mip Map Count:\t{}\n"
			"Type:\t{}\n",
			D3DToString(m_Format), m_Width, m_Height, m_Depth, m_MipmapCount, m_Type).c_str();
	}
}