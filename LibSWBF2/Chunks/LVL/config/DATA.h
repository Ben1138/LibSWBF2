#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/RawData.h"
#include "Types/Enums.h"

namespace LibSWBF2::Chunks::LVL::config
{
	struct LIBSWBF2_API DATA_CONFIG : public GenericChunk<"DATA"_m>
	{
		FNVHash m_NameHash;
		uint8_t m_NumElements;

		uint8_t* p_Content = nullptr;
		size_t m_ContentSize = 0;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	
		String ToString() override;

		~DATA_CONFIG();
		
		bool GetFloat(float_t& floatMember, uint32_t index=0);
		bool GetVec2(Vector2 &vec2Out);
		bool GetVec3(Vector3 &vec3Out);
		bool GetVec4(Vector4 &vec4Out);
		bool GetString(String &stringOut, uint32_t index=0);

		static FNVHash PeekDATAHash(FileReader& stream);
		static void ReadDATAChild(FileReader& stream, GenericBaseChunk *parent,  DATA_CONFIG*& ptr);
		#define READ_CHILD_DATA(stream, member) DATA_CONFIG::ReadDATAChild(stream, this, member);


	private:
		bool IsFloatData();

	};
}