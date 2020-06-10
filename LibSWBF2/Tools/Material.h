#pragma once
#include "req.h"
#include "Chunks\LVL\modl\MTRL.h"
#include "Types\List.h"
#include "Types\Color.h"
#include "Types\LibString.h"
#include "Texture.h"

namespace LibSWBF2::Tools
{
	using Chunks::LVL::modl::MTRL;
	using Types::List;
	using Types::Color;
	using Types::String;

	class Level;

	class LIBSWBF2_EXP Material
	{
	public:
		Material() = default;
		~Material() = default;

	private:
		Level* m_MainContainer = nullptr;
		MTRL* p_Material = nullptr;

	public:
		static bool FromChunk(Level* mainContainer, MTRL* materialChunk, Material& out);

		EMaterialFlags GetFlags() const;
		const Color& GetDiffuseColor() const;
		const Color& GetSpecularColor() const;
		uint32_t GetSpecularExponent() const;
		const String& GetAttachedLight() const;

		const Texture* GetTexture(uint8_t index) const;
	};
}