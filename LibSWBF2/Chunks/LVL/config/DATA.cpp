#include "stdafx.h"
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

	bool DATA_CONFIG::GetValueType(EDataValueType& type, uint8_t index) const
	{
		if (m_NumValues > index)
		{
			type = EDataValueType::Float;

			// Let's consider a value to be a string, if the last 3 of the 4 bytes are 0x00
			// TODO: Idk a better approach right now...
			uint8_t* value = p_Data + sizeof(float_t) * index;
			if (value[1] == 0 && value[2] == 0 && value[3] == 0)
			{
				type = EDataValueType::String;
			}
			return true;
		}

		return false;
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

		// NOTE: I want to match the index behaviour of GetFloat() here, such that in a DATA block like
		// 
		//           InputLock(0.15, "Sprint", "Jump", "Crouch")
		// 
		//       GetString(index = 2) returns "Jump" (since it's at index 2) and not "Crouch", 
		//       which would be the case if we were just splitting the suffixed string 
		//       "Sprint.Jump.Crouch" (see table and examples above)
		// 
		//       Additionally, the call GetString(index = 0) should return "0.15" as string

		EDataValueType type;
		GetValueType(type, index);

		if (type == EDataValueType::Float)
		{
			float floatMember = *(((float_t*)p_Data) + index);
			stringOut = std::to_string(floatMember).c_str();
			return true;
		}

		// Count number of string values to our index, in order to obtain the string split index
		uint8_t splitIdx = 0;
		for (uint8_t i = 0; i < index; ++i)
		{
			GetValueType(type, i);
			if (type == EDataValueType::String)
			{
				splitIdx++;
			}
		}

		const uint8_t* strStart = (p_Data + 4 * m_NumValues + 4);
		uint32_t stringLength = *((uint32_t *) (p_Data + 4 * m_NumValues));
		if (stringLength > 0 && strStart[0] != 0)
		{
			std::vector<const uint8_t*> strings;
			strings.emplace_back(strStart);

			for (uint32_t i = 1; i < stringLength - 1; ++i)
			{
				if (strStart[i] == 0)
				{
					strings.emplace_back(&strStart[++i]);
				}
			}

			if (splitIdx >= strings.size())
			{
				LOG_ERROR("GetString at index {0} resolved to split index {1}, which is out of range of {2}!", index, splitIdx, (int)strings.size());
				stringOut = "ERROR";
				return false;
			}
			else
			{
				stringOut = (const char*)strings[splitIdx];
			}
		}

		return true;
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
			EDataValueType type;
			GetValueType(type, i);

			String str;
			GetString(str, i);

			if (type == EDataValueType::String)
			{
				rep += fmt::format("\t[{0}] String\t = \"{1}\"\n", i, str.Buffer());
			}
			else
			{
				rep += fmt::format("\t[{0}] Float\t = {1}\n", i, str.Buffer());
			}
		}

		return rep.c_str();
	}
}
