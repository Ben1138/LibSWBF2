#pragma once


using LibSWBF2::Types::String;


namespace LibSWBF2::Types
{
	struct Hub
	{
		LibSWBF2::Types::String name;
		Vector3 position;
		float_t radius;

		uint8_t layerWeights[5];

		String ToString() const;
		void ReadFromStream(FileReader& stream, uint16_t count);
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