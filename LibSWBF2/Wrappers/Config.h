#pragma once
#include "Chunks/LVL/config/ConfigChunk.h"
#include "Chunks/LVL/config/SCOP.h"

#include "Types/Color4.h"
#include "Types/Vector4.h"
#include "Types/Vector3.h"


namespace LibSWBF2::Wrappers
{
	using LibSWBF2::Chunks::GenericBaseChunk;
	using namespace LibSWBF2::Chunks::LVL::config;
	using namespace LibSWBF2::Types;


	class LIBSWBF2_API Config
	{

		friend class Level;
		friend List<Config>;

	public:

		FNVHash m_Name;
		EConfigType m_ConfigType;

		bool IsPropertySet(FNVHash hash) const;
		float_t GetFloat(FNVHash hash, uint32_t index = 0) const;
		
		Vector2 GetVector2(FNVHash hash) const;
		Vector3 GetVector3(FNVHash hash) const;
		Vector4 GetVector4(FNVHash hash) const;
		String GetString(FNVHash hash) const;
		List<String> GetStrings(FNVHash hash) const;

		List<Config> GetChildConfigs(FNVHash hash) const;

		static bool FromChunk(GenericBaseChunk *cfg, Config& wrapperOut);


	private:

		Config() = default;
		Config(DATA_CONFIG *data, SCOP *scop);
		GenericBaseChunk *p_Chunk;

		DATA_CONFIG *SearchProperty(FNVHash hash) const;
		List<DATA_CONFIG *> SearchPropertyAll(FNVHash hash) const;

	};
}
