#pragma once


#include "Types/Enums.h"

using LibSWBF2::Types::String;



namespace LibSWBF2::Types
{
	struct Hub
	{
		LibSWBF2::Types::String m_Name;
		Vector3 m_Position;
		float_t m_Radius;

		// Indices into ARCS, referenced by last 3 bytes of
		// each quantized branchweight
		uint8_t m_ConnectionIndices[8];

		uint8_t m_ConnectionsPerLayer[5];

		// Would ideally use shared_ptr here but will stick with List for now
		// since handling a raw buffer would be a headache without shared_ptr
		List<uint8_t> m_QuantizedDataBuffer;

		String ToString() const;
		void ReadFromStream(FileReader& stream, uint16_t count);
	};


	struct Connection
	{
		LibSWBF2::Types::String m_Name;
		uint8_t m_Start;
		uint8_t m_End;
		EArcFilterFlags m_FilterFlags;
		EArcAttributeFlags m_AttributeFlags;

		String ToString() const;
		void ReadFromStream(FileReader& stream);
	};
}