// THIS IS NOT MEANT TO BE INCLUDED IN OTHER EXPOSDED HEADERS
#pragma once

#include "DirectX/D3D9FORMAT.h"
#include "Types/Enums.h"

#ifdef _WIN32
#include <DirectXTex.h>
#endif

namespace LibSWBF2
{
	DXGI_FORMAT D3DToDXGI(D3DFORMAT d3dFormat);
	Types::String D3DToString(D3DFORMAT d3dFormat);
	DXGI_FORMAT TextureFormatToDXGI(ETextureFormat format);
}