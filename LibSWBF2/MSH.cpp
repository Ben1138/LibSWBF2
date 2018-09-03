#include "stdafx.h"
#include "MSH.h"
#include "HeaderNames.h"

namespace LibSWBF2::Chunks::MSH
{
	MSH::MSH()
	{

	}

	MSH::~MSH()
	{

	}

	void MSH::RefreshSize()
	{
		shvo.RefreshSize();

		Size = shvo.GetSize();
	}

	void MSH::WriteToStream(ofstream& stream)
	{
		BaseChunk::WriteToStream(stream);
		shvo.WriteToStream(stream);
	}

	void MSH::ReadFromStream(ifstream& stream)
	{
		BaseChunk::ReadFromStream(stream);
		int32_t head = BaseChunk::PeekHeader(stream);

		if (head == HeaderNames::SHVO)
			shvo.ReadFromStream(stream);
	}
}