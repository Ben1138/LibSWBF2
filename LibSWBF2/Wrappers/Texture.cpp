#include "stdafx.h"
#include "Level.h"
#include "Chunks\LVL\\tex_\tex_.LVL_.h"

namespace LibSWBF2::Wrappers
{
	using Chunks::LVL::LVL_texture::LVL_;

	bool Texture::FromChunk(tex_* textureChunk, Texture& out)
	{
		if (textureChunk == nullptr)
		{
			LOG("Given textureChunk was NULL!", ELogType::Error);
			return false;
		}

		out.p_Texture = textureChunk;

		List<FMT_*>& fmts = out.p_Texture->m_FMTs;
		if (fmts.Size() == 0)
		{
			LOG(string("Texture '")+textureChunk->p_Name->m_Text.Buffer()+"' does not contain any data!", ELogType::Warning);
			return false;
		}

		// Grab FMT chunk with the least amount of compression
		// TODO: proper format sorting for choosing the right FMT chunk
		out.p_FMT = nullptr;
		for (size_t i = 0; i < fmts.Size(); ++i)
		{
			if (fmts[i]->p_Info->m_Format == D3DFMT_DXT3)
			{
				out.p_FMT = fmts[i];
				break;
			}
			if (fmts[i]->p_Info->m_Format == D3DFMT_DXT1)
			{
				out.p_FMT = fmts[i];
				break;
			}
		}

		if (out.p_FMT == nullptr)
		{
			out.p_FMT = fmts[0];
		}

		return true;
	}

	String Texture::GetName() const
	{
		return p_Texture->p_Name->m_Text;
	}

	uint32_t Texture::GetNumMipMaps() const
	{
		return p_FMT->p_Info->m_MipmapCount;
	}

	bool Texture::GetImageData(ETextureFormat format, uint8_t mipLevel, uint16_t& width, uint16_t& height, uint8_t*& data) const
	{
		List<LVL_*>& mipChunks = p_FMT->p_Face->m_LVLs;
		for (size_t i = 0; i < mipChunks.Size(); ++i)
		{
			if (mipChunks[i]->p_Info->m_MipLevel == mipLevel)
			{
				return mipChunks[i]->p_Body->GetImageData(format, width, height, data);
			}
		}
		width = 0;
		height = 0;
		data = nullptr;
		return false;
	}
}