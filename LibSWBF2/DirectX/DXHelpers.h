// THIS IS NOT MEANT TO BE INCLUDED IN OTHER EXPOSDED HEADERS

#pragma once
#include "D3D9Types.h"
#include "Types/Enums.h"
#include <DirectXTex.h>

namespace LibSWBF2
{
	DXGI_FORMAT D3DToDXGI(D3DFORMAT d3dFormat);
	Types::String D3DToString(D3DFORMAT d3dFormat);
	DXGI_FORMAT TextureFormatToDXGI(ETextureFormat format);
}