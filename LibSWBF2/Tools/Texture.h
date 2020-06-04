#pragma once
#include "req.h"
#include "Chunks\LVL\tex_\tex_.h"

namespace LibSWBF2::Tools
{
	using Chunks::LVL::texture::tex_;
	using Chunks::LVL::texture::FMT_;

	class LIBSWBF2_EXP Texture
	{
	private:
		Texture(tex_* textureChunks);

		// no need to destroy p_Texture, since it's owned by the Level's LVL
		~Texture() = default;

	private:
		tex_* p_Texture;
		FMT_* p_FMT;

	public:
		static Texture* FromChunk(tex_* textureCHunk);
		static void Destroy(Texture* texture);

		String GetName() const;
		uint32_t GetNumMipMaps() const;

		// always delivers format R8 G8 B8 A8
		bool GetImageData(uint8_t mipLevel, uint16_t& width, uint16_t& height, uint8_t*& data) const;
	};
}