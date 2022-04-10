#pragma once


using LibSWBF2::Types::String;


namespace LibSWBF2::Types
{
	struct Hub
	{
		LibSWBF2::Types::String name;
		Vector3 position;
		float_t radius;

		// Indices into ARCS, referenced by last 3 bytes of
		// each quantized branchweight
		uint8_t connectionIndices[8];

		uint8_t connectionsPerLayer[5];

		uint8_t * quantizedDataBuffer = nullptr;

		String ToString() const;
		void ReadFromStream(FileReader& stream, uint16_t count);

		~Hub()
		{
			ReleaseDataBuffer();
		}

		void ReleaseDataBuffer()
		{
			if (quantizedDataBuffer != nullptr)
			{
				delete[] quantizedDataBuffer;
				quantizedDataBuffer = nullptr;	
			}
		}
	};


	struct Connection
	{
		LibSWBF2::Types::String name;
		uint8_t start;
		uint8_t end;
		uint32_t flag_one;
		uint32_t flag_two;

		String ToString() const;
		void ReadFromStream(FileReader& stream);
	};
}