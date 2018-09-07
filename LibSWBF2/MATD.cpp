#include "stdafx.h"
#include "MATD.h"

namespace LibSWBF2::Chunks::MSH
{
	MATD::MATD()
	{

	}

	MATD::~MATD()
	{

	}

	void MATD::RefreshSize()
	{
		name.RefreshSize();
		data.RefreshSize();
		tx0d.RefreshSize();
		tx1d.RefreshSize();
		tx2d.RefreshSize();
		tx3d.RefreshSize();

		Size = name.GetSize() + data.GetSize();

		if (tx0d.Text.size() > 0)
			Size += tx0d.GetSize();

		if (tx1d.Text.size() > 0)
			Size += tx1d.GetSize();

		if (tx2d.Text.size() > 0)
			Size += tx2d.GetSize();

		if (tx3d.Text.size() > 0)
			Size += tx3d.GetSize();
	}

	void MATD::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		name.WriteToStream(stream);
		data.WriteToStream(stream);

		if (tx0d.Text.size() > 0)
			tx0d.WriteToStream(stream);

		if (tx1d.Text.size() > 0)
			tx1d.WriteToStream(stream);

		if (tx2d.Text.size() > 0)
			tx2d.WriteToStream(stream);

		if (tx3d.Text.size() > 0)
			tx3d.WriteToStream(stream);
	}

	void MATD::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		ChunkHeader head = stream.ReadChunkHeader(true);

		if (head == HeaderNames::NAME)
		{
			name.ReadFromStream(stream);
		}
		else if (head == HeaderNames::DATA)
		{
			data.ReadFromStream(stream);
		}
		else if (head == HeaderNames::TX0D)
		{
			tx0d.ReadFromStream(stream);
		}
		else if (head == HeaderNames::TX1D)
		{
			tx1d.ReadFromStream(stream);
		}
		else if (head == HeaderNames::TX2D)
		{
			tx2d.ReadFromStream(stream);
		}
		else if (head == HeaderNames::TX3D)
		{
			tx3d.ReadFromStream(stream);
		}
		else
		{
			Logger::Add("Unknown Chunk found: " + HeaderNames::GetHeaderString(head), ELogType::Warning);
		}
	}
}