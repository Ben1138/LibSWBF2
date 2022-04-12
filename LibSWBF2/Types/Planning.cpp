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
        m_Name = LibSWBF2::Types::String(reinterpret_cast<char*>(chars));

        m_Position.ReadFromStream(stream);
        m_Radius = stream.ReadFloat();

        stream.ReadBytes(m_ConnectionIndices, 8);
        stream.ReadBytes(m_ConnectionsPerLayer, 5);

        uint32_t sum = 0;
        for (int i = 0; i < 5; i++)
        {
            sum += m_ConnectionsPerLayer[i];
        }

        size_t quantizedDataBufferSize = sum * count;
        m_QuantizedDataBuffer = List<uint8_t>(quantizedDataBufferSize);
        for (int i = 0; i < quantizedDataBufferSize; i++)
        {
        	m_QuantizedDataBuffer.Add(stream.ReadByte());
        }
	}


	String Hub::ToString() const
	{
		return fmt::format(
			"Name: {0}, Position: {1}, Radius: {2}", 
			m_Name.Buffer(), m_Position.ToString().Buffer(), m_Radius
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
        m_Name = LibSWBF2::Types::String(reinterpret_cast<char*>(chars));

        m_Start = stream.ReadByte();
        m_End = stream.ReadByte();
        m_FilterFlags = (EArcFilterFlags) stream.ReadUInt32();
        m_AttributeFlags = (EArcAttributeFlags) stream.ReadUInt32();
	}


	String Connection::ToString() const
	{
		return fmt::format(
			"Name: {0}, Start: {1}, End: {2}, Filters: {3}, Attributes: {4}", 
			m_Name.Buffer(), m_Start, m_End, ArcFilterToString(m_FilterFlags).Buffer(), ArcAttributesToString(m_AttributeFlags).Buffer()
		).c_str();
	}
}