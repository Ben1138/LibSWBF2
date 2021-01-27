#pragma once
#include "req.h"
#include "Chunks/LVL/modl/MTRL.h"
#include "Types/List.h"
#include "Types/Color4u8.h"
#include "Types/LibString.h"
#include "Texture.h"

namespace LibSWBF2
{
	class Container;
}

namespace LibSWBF2::Wrappers
{
	using Chunks::LVL::modl::MTRL;
	using Types::List;
	using Types::Color4u8;
	using Types::String;

	class Level;
	class Segment;

	class LIBSWBF2_API Material
	{
	private:
		friend Level;
		friend Segment;
		friend List<Material>;

		Material() = default;
		~Material() = default;

	private:
		Level* m_MainContainer = nullptr;
		MTRL* p_Material = nullptr;

	public:
		static bool FromChunk(Level* mainContainer, MTRL* materialChunk, Material& out);

		EMaterialFlags GetFlags() const;
		const Color4u8& GetDiffuseColor() const;
		const Color4u8& GetSpecularColor() const;
		uint32_t GetSpecularExponent() const;
		const String& GetAttachedLight() const;
		bool GetTextureName(uint8_t index, String& outName) const;

		// will try to resolve within this Level
		const Texture* GetTexture(uint8_t index) const;
	};
}