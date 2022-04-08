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

	void Hub::ReadFromStream(FileReader& stream, uint16_t count)
	{
		   //Names are a constant length
        uint8_t chars[NAME_LENGTH];

        stream.ReadBytes(chars, NAME_LENGTH);
        name = LibSWBF2::Types::String(reinterpret_cast<char*>(chars));

        position.ReadFromStream(stream);
        radius = stream.ReadFloat();

        //Unknown 8 bytes
        stream.SkipBytes(8);

        //5 weight counts?
        //uint8_t weightCounts[5];

        stream.ReadBytes(layerWeights, 5);

        uint32_t sum = 0;
        for (int i = 0; i < 5; i++)
        {
            sum += layerWeights[i];
        }

        stream.SkipBytes(sum * count);
	}


	String Hub::ToString() const
	{
		return fmt::format(
			"Name: {0}, Position: {1}, Radius: {2} Weight bytes: {3}, {4}, {5}, {6}, {7}", 
			name.Buffer(), position.ToString().Buffer(), radius, 
			layerWeights[0], layerWeights[1], layerWeights[2], layerWeights[3], layerWeights[4]
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