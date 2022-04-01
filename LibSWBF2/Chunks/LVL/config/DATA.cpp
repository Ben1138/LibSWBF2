#include "pch.h"
#include "DATA.h"
#include "FileReader.h"
#include "InternalHelpers.h"
#include "Hashing.h"


namespace LibSWBF2::Chunks::LVL::config
{
	void DATA_CONFIG::RefreshSize()
	{
		THROW("Not implemented!");
	}
	
	void DATA_CONFIG::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void DATA_CONFIG::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
        Check(stream);

		// DATA layout
		// +-------------+----------------+---------------------------------------------+
		// | byte length |      type      |                   purpose                   |
		// +-------------+----------------+---------------------------------------------+
		// | 4           | uint32         | name hash                                   |
		// | 1           | uint8          | n number of values                          |
		// | 4 * n       | float32/uint32 | float value OR unknown int                  |
		// | 4           | uint32         | length of string values, separated with x00 |
		// +-------------+----------------+---------------------------------------------+
		//
		// Real Example: 
		// 
		//     InputLock(0.15, "Sprint", "Jump", "Crouch");
		//     +----------------------------------------------------------+-----------------------------------+
		//     | 54 00 4F F9                                              | name hash of "InputLock"          |
		//     | 04                                                       | n = 4                             |
		//     | 9A 99 19 3E                                              | value[0] = 0.15                   |
		//     | 10 00 00 00                                              | value[1] = ???                    |
		//     | 17 00 00 00                                              | value[2] = ???                    |
		//     | 1C 00 00 00                                              | value[3] = ???                    |
		//     | 13 00 00 00                                              | string length = 19                |
		//     | 53 70 72 69 6E 74 00 4A 75 6D 70 00 43 72 6F 75 63 68 00 | "Sprint[x00]Jump[x00]Crouch[x00]" |
		//     +----------------------------------------------------------+-----------------------------------+
		//
		// Fictional Example:
		//     SomeData(3.1416, "never", 42, "gonna", 2.71828, "give", 69, "you up")
		//     indixes:    0       1     2      3        4       5     6      7


		if (m_Size < 5)
		{
			LOG_WARN("Encountered DATA chunk with size {0} < 5!", m_Size);
		}
		else
		{
			m_ContentSize = m_Size - 5;
			m_NameHash = stream.ReadUInt32();
			m_NumValues = stream.ReadByte();

			if (m_ContentSize > 0)
			{
				p_Data = new uint8_t[m_ContentSize];
				stream.ReadBytes(p_Data, m_ContentSize);
			}
			else
			{
				p_Data = nullptr;
			}
		}

        BaseChunk::EnsureEnd(stream);
	}

	bool DATA_CONFIG::GetFloat(float_t& floatMember, uint8_t index) const
	{
		if (m_NumValues > index)
		{
			floatMember = *(((float_t *) p_Data) + index);
			return true;
		}

		return false;
	}
	
	bool DATA_CONFIG::GetVec2(Vector2 &vec2Out) const
	{
		if (m_NumValues >= 2)
		{
			float_t *floatsPtr = (float_t *) p_Data;
			vec2Out = Vector2(floatsPtr[0], floatsPtr[1]);
			return true;
		}

		return false;
	}

	bool DATA_CONFIG::GetVec3(Vector3 &vec3Out) const
	{
		if (m_NumValues >= 3)
		{
			float_t *floatsPtr = (float_t *) p_Data;
			vec3Out = Vector3(floatsPtr[0], floatsPtr[1], floatsPtr[2]);
			return true;
		}

		return false;
	}

	bool DATA_CONFIG::GetVec4(Vector4 &vec4Out) const
	{
		if (m_NumValues >= 4)
		{
			float_t *floatsPtr = (float_t *) p_Data;
			vec4Out = Vector4(floatsPtr[0], floatsPtr[1], floatsPtr[2], floatsPtr[3]);
			return true;
		}

		return false;
	}

	bool DATA_CONFIG::GetString(String &stringOut, uint8_t index) const
	{
		stringOut = "";
		if (index >= m_NumValues)
		{
			return false;
		}

		// For strings, the 4 byte value slot serves as an offset to where the string starts
		const uint32_t strOffset = *(((uint32_t*)p_Data) + index);
		const uint8_t* strStart = (p_Data + 4 + strOffset);

		uint32_t concatStringsLength = *((uint32_t*) (p_Data + 4 * m_NumValues));
		if (concatStringsLength == 0 || strOffset >= (m_ContentSize - 1))
		{
			LOG_ERROR("GetString failed! No string present at index {0}!", index);
			stringOut = "ERROR";
			return false;
		}

		stringOut = (const char*)strStart;
		return true;
	}

	bool DATA_CONFIG::GetUInt32(uint32_t& uintMember, uint8_t index) const
	{
		if (m_NumValues > index)
		{
			uintMember = *(((uint32_t *) p_Data) + index);
			return true;
		}

		return false;
	}

	String DATA_CONFIG::ToString() const
	{
		std::string rep = fmt::format("Name hash: 0x{0:x}\n", m_NameHash);

		String name;
		if (FNV::Lookup(m_NameHash, name))
		{
			rep += fmt::format("Lookup Name: {0}\n", name.Buffer());
		}
		rep += fmt::format("Num elements: {0}\n", m_NumValues);

		for (uint8_t i = 0; i < m_NumValues; ++i)
		{
			String str;
			GetString(str, i);

			float f;
			GetFloat(f, i);

			uint32_t uint;
			GetUInt32(uint, i);

			rep += fmt::format("\t[{0}]\t\t{1}\t{2}\t\"{3}\"\n", i, f, uint, str.Buffer());
		}

		return rep.c_str();
	}
}
