// THIS IS NOT MEANT TO BE INCLUDED IN OTHER EXPOSDED HEADERS
#pragma once

#include <LibSWBF2/DirectX/D3D9FORMAT.h>
#include <LibSWBF2/Types/Enums.h>

namespace LibSWBF2
{
	DXGI_FORMAT D3DToDXGI(D3DFORMAT d3dFormat);
	Types::String D3DToString(D3DFORMAT d3dFormat);
	DXGI_FORMAT TextureFormatToDXGI(ETextureFormat format);
}