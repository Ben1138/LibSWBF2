#pragma once

#include <memory>
#include <stdint.h>

#include "D3D9FORMAT.h"


namespace LibSWBF2::Chunks::LVL::LVL_texture
{
	struct BODY;
}

namespace DXTexCrossPlat
{
	class CrossPlatImage
	{
		friend LibSWBF2::Chunks::LVL::LVL_texture::BODY;

	public:
		CrossPlatImage(uint16_t w, uint16_t h,  
					   D3DFORMAT f, 
					   uint8_t *&dataPtr,
					   size_t dataSize);

		CrossPlatImage(uint16_t w, uint16_t h, 
					D3DFORMAT f, size_t dataSize);

		bool ConvertTo(D3DFORMAT f);

		uint8_t* GetPixelsPtr();

		bool IsConvertibleTo(D3DFORMAT format);

		uint16_t width,height,cellSize;

		D3DFORMAT format;

	private:
		size_t m_DataLength;
		uint8_t* p_Data = nullptr;
		D3DFORMAT m_Format;
		bool m_IsValid = true;

		~CrossPlatImage();
		bool ToRGBA();

	};
}