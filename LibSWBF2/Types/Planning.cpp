#include "pch.h"
#include "Planning.h"
#include "FileWriter.h"
#include "FileReader.h"

#define NAME_LENGTH 16


namespace LibSWBF2::Types
{	

	/*
	Hub
	*/

	/*
	void Hub::UnpackConnectionWeight(uint8_t PackedWeight)
	{
		float weight;
		uint8_t connectionIndex;

		weight = (PackedWeight >> 3) / 31f;
		connectionIndex = PackedWeight & 0x3;
	}
	*/



	void Hub::ReadFromStream(FileReader& stream, uint16_t count)
	{
		//Names are a constant length
        uint8_t chars[NAME_LENGTH];

        stream.ReadBytes(chars, NAME_LENGTH);
        name = LibSWBF2::Types::String(reinterpret_cast<char*>(chars));

        position.ReadFromStream(stream);
        radius = stream.ReadFloat();

        stream.ReadBytes(connectionIndices, 8);
        stream.ReadBytes(connectionsPerLayer, 5);

        uint32_t sum = 0;
        for (int i = 0; i < 5; i++)
        {
            sum += connectionsPerLayer[i];
        }

        size_t quantizedDataBufferSize = sum * count;
        quantizedDataBuffer = List<uint8_t>(quantizedDataBufferSize);
        for (int i = 0; i < quantizedDataBufferSize; i++)
        {
        	quantizedDataBuffer.Add(stream.ReadByte());
        }
	}


	String Hub::ToString() const
	{
		return fmt::format(
			"Name: {0}, Position: {1}, Radius: {2}", 
			name.Buffer(), position.ToString().Buffer(), radius
		).c_str();
	}



	/*
	Connection
	*/

	void Connection::ReadFromStream(FileReader& stream)
	{
		//Names are a constant length
        uint8_t chars[NAME_LENGTH];

        stream.ReadBytes(chars, NAME_LENGTH);
        name = LibSWBF2::Types::String(reinterpret_cast<char*>(chars));

        start = stream.ReadByte();
        end = stream.ReadByte();
        flag_one = stream.ReadUInt32();
        flag_two = stream.ReadUInt32();
	}


	String Connection::ToString() const
	{
		return fmt::format(
			"Name: {0}, Start: {1}, End: {2}, Flag1: {3}, Flag2: {4}", 
			name.Buffer(), start, end, flag_one, flag_two
		).c_str();
	}
}