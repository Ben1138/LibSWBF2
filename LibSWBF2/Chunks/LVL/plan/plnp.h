#pragma once

#include "Chunks/GenericChunk.h"

#include "Types/Planning.h"


using LibSWBF2::Types::String;
using LibSWBF2::Types::Hub;
using LibSWBF2::Types::Connection;


namespace LibSWBF2::Chunks::plnp
{
	struct LIBSWBF2_API plnp : public GenericChunk<"plnp"_m>
	{
		List<uint8_t> m_NumConnectionsInEachGroup;
		List<FNVHash> m_ConnectionHashes;

		void ReadFromStream(FileReader& stream) override;
		String ToString() const override;
	};
}