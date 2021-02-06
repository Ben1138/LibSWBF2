#pragma once
#include "Chunks/LVL/tex_/tex_.h"
#include "Types/Enums.h"
#include "Types/List.h"

namespace LibSWBF2::Wrappers
{
	using Chunks::LVL::texture::tex_;
	using Chunks::LVL::texture::FMT_;
	using LibSWBF2::Types::String;
	using LibSWBF2::Types::List;

	class Level;

	class LIBSWBF2_API Texture
	{
	private:
		friend Level;
		friend List<Texture>;

		Texture() = default;
		~Texture() = default;

	private:
		tex_* p_Texture;
		FMT_* p_FMT;

	public:
		static bool FromChunk(tex_* textureCHunk, Texture& out);

		String GetName() const;
		uint32_t GetNumMipMaps() const;

		bool GetImageData(ETextureFormat format, uint8_t mipLevel, uint16_t& width, uint16_t& height, const uint8_t*& data) const;
	};
}