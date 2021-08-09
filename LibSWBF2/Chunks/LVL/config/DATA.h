#pragma once
#include "Chunks/RawData.h"

namespace LibSWBF2::Chunks::LVL::config
{
	// A DATA can have a variable amount of values stored, from 0 to 255 values
	struct LIBSWBF2_API DATA_CONFIG : public RawData<"DATA"_m>
	{
		FNVHash m_NameHash;
		uint8_t m_NumValues;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	
		String ToString() const override;
		
		bool GetValueType(EDataValueType& type, uint8_t index) const;
		bool GetFloat(float_t& floatMember, uint8_t index=0) const;
		bool GetVec2(Vector2 &vec2Out) const;
		bool GetVec3(Vector3 &vec3Out) const;
		bool GetVec4(Vector4 &vec4Out) const;
		bool GetString(String &stringOut, uint8_t index=0) const;

	private:
		size_t m_ContentSize;
	};
}