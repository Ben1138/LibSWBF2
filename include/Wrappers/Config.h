#pragma once
#include "Types/Color4.h"
#include "Types/Vector4.h"
#include "Types/Vector3.h"


namespace LibSWBF2::Chunks
{
	struct GenericBaseChunk;

	namespace LVL::config
	{
		struct SCOP;
		struct ConfigChunkNC;
		struct DATA_CONFIG;
	}
}


namespace LibSWBF2::Wrappers
{
	using namespace LibSWBF2::Types;

	struct Field;


	struct Scope
	{
	typedef LibSWBF2::Chunks::LVL::config::SCOP SCOP;


	friend Field;

	public:
		List<const Field *> GetFields(FNVHash name = 0) const;
		const Field& GetField(FNVHash name = 0) const;

		bool IsEmpty() const;

		Scope() = default;
	
	private:
		Scope(SCOP *scopePtr);
		SCOP *p_Scope;

		// These are lazily initialized, since we may not
		// use many Config types
		mutable List<Field> m_Fields;
		mutable bool m_IsValid;

		// Inits above members
		const void Cache() const;
	};




	struct Field
	{
	typedef LibSWBF2::Chunks::GenericBaseChunk GenericBaseChunk;
	typedef LibSWBF2::Chunks::LVL::config::DATA_CONFIG DATA_CONFIG;
	typedef LibSWBF2::Chunks::LVL::config::SCOP SCOP;

	public:
		Field(DATA_CONFIG* data, SCOP* scope);
		Field() = default;

		static List<Field> FieldsFromChunkChildren(GenericBaseChunk *chunk);

		FNVHash GetNameHash() const;

		uint8_t GetNumValues() const;
		float_t GetFloat(uint8_t index=0) const;
		uint32_t GetUInt32(uint8_t index=0) const;
		Vector2 GetVector2() const;
		Vector3 GetVector3() const;
		Vector4 GetVector4() const;
		String GetString(uint8_t index=0) const;
		String GetName() const;

		Scope m_Scope;

	private:
		friend Scope;
		friend class Config;

		DATA_CONFIG* p_Data;
	};





	class LIBSWBF2_API Config
	{

	typedef LibSWBF2::Chunks::LVL::config::ConfigChunkNC ConfigChunkNC;
	typedef LibSWBF2::Chunks::GenericBaseChunk GenericBaseChunk;

	friend class Level;
	friend List<Config>;

	public:

		EConfigType m_Type;
		FNVHash m_Name;
				
		const Field& GetField(FNVHash hash = 0) const;
		List<const Field *> GetFields(FNVHash hash = 0) const;

		static bool FromChunk(GenericBaseChunk *cfg, Config& wrapperOut);

	private:

		ConfigChunkNC *p_Chunk;
		List<Field> m_Fields;
	};
}
