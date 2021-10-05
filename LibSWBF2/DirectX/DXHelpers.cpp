#include "pch.h"
#include "DXHelpers.h"
#include "InternalHelpers.h"
#include "InternalHelpers.h"

namespace LibSWBF2
{
    // This is copied from:
    // https://github.com/SleepKiller/swbf-unmunge
    DXGI_FORMAT D3DToDXGI(D3DFORMAT d3dFormat)
    {
        switch (d3dFormat)
        {
            case D3DFMT_A8R8G8B8:
                return DXGI_FORMAT_B8G8R8A8_UNORM;
            case D3DFMT_X8R8G8B8:
                return DXGI_FORMAT_B8G8R8X8_UNORM;
            case D3DFMT_R5G6B5:
                return DXGI_FORMAT_B5G6R5_UNORM;
            case D3DFMT_A1R5G5B5:
            case D3DFMT_X1R5G5B5:
                return DXGI_FORMAT_B5G5R5A1_UNORM;
            case D3DFMT_A4R4G4B4:
                return DXGI_FORMAT_B4G4R4A4_UNORM;
            case D3DFMT_A8:
                return DXGI_FORMAT_A8_UNORM;
            case D3DFMT_A2B10G10R10:
                return DXGI_FORMAT_R10G10B10A2_UNORM;
            case D3DFMT_A8B8G8R8:
                return DXGI_FORMAT_R8G8B8A8_UNORM;
            case D3DFMT_G16R16:
                return DXGI_FORMAT_R16G16_UNORM;
            case D3DFMT_A16B16G16R16:
                return DXGI_FORMAT_R16G16B16A16_UNORM;
            case D3DFMT_V8U8:
                return DXGI_FORMAT_R8G8_SNORM;
            case D3DFMT_Q8W8V8U8:
                return DXGI_FORMAT_R8G8B8A8_SNORM;
            case D3DFMT_V16U16:
                return DXGI_FORMAT_R16G16_SNORM;
            case D3DFMT_R8G8_B8G8:
                return DXGI_FORMAT_G8R8_G8B8_UNORM;
            case D3DFMT_G8R8_G8B8:
                return DXGI_FORMAT_R8G8_B8G8_UNORM;
            case D3DFMT_DXT1:
                return DXGI_FORMAT_BC1_UNORM;
            case D3DFMT_DXT2:
            case D3DFMT_DXT3:
                return DXGI_FORMAT_BC2_UNORM;
            case D3DFMT_DXT4:
            case D3DFMT_DXT5:
                return DXGI_FORMAT_BC3_UNORM;
            case D3DFMT_D16_LOCKABLE:
            case D3DFMT_D16:
                return DXGI_FORMAT_D16_UNORM;
            case D3DFMT_D24S8:
                return DXGI_FORMAT_D24_UNORM_S8_UINT;
            case D3DFMT_D32:
            case D3DFMT_D32F_LOCKABLE:
                return DXGI_FORMAT_D32_FLOAT;
            case D3DFMT_Q16W16V16U16:
                return DXGI_FORMAT_R16G16B16A16_SNORM;
            case D3DFMT_R16F:
                return DXGI_FORMAT_R16_FLOAT;
            case D3DFMT_G16R16F:
                return DXGI_FORMAT_R16G16_FLOAT;
            case D3DFMT_A16B16G16R16F:
                return DXGI_FORMAT_R16G16B16A16_FLOAT;
            case D3DFMT_R32F:
                return DXGI_FORMAT_R32_FLOAT;
            case D3DFMT_G32R32F:
                return DXGI_FORMAT_R32G32_FLOAT;
            case D3DFMT_A32B32G32R32F:
                return DXGI_FORMAT_R32G32B32A32_FLOAT;
            case D3DFMT_A2B10G10R10_XR_BIAS:
                return DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;
            case D3DFMT_L8:
                return DXGI_FORMAT_R8_UNORM;
            case D3DFMT_A8L8:
                return DXGI_FORMAT_R8G8_UNORM;
            case D3DFMT_L16:
                return DXGI_FORMAT_R16_UNORM;
            default:
                THROW("Unknown D3D Format: {}", (int)d3dFormat);
        }
    }

    Types::String D3DToString(D3DFORMAT d3dFormat)
    {
        switch (d3dFormat)
        {
            case D3DFMT_A8R8G8B8:
                return "D3DFMT_A8R8G8B8";
            case D3DFMT_X8R8G8B8:
                return "D3DFMT_X8R8G8B8";
            case D3DFMT_R5G6B5:
                return "D3DFMT_R5G6B5";
            case D3DFMT_A1R5G5B5:
                return "D3DFMT_A1R5G5B5";
            case D3DFMT_X1R5G5B5:
                return "D3DFMT_X1R5G5B5";
            case D3DFMT_A4R4G4B4:
                return "D3DFMT_A4R4G4B4";
            case D3DFMT_A8:
                return "D3DFMT_A8";
            case D3DFMT_A2B10G10R10:
                return "D3DFMT_A2B10G10R10";
            case D3DFMT_A8B8G8R8:
                return "D3DFMT_A8B8G8R8";
            case D3DFMT_G16R16:
                return "D3DFMT_G16R16";
            case D3DFMT_A16B16G16R16:
                return "D3DFMT_A16B16G16R16";
            case D3DFMT_V8U8:
                return "D3DFMT_V8U8";
            case D3DFMT_Q8W8V8U8:
                return "D3DFMT_Q8W8V8U8";
            case D3DFMT_V16U16:
                return "D3DFMT_V16U16";
            case D3DFMT_R8G8_B8G8:
                return "D3DFMT_R8G8_B8G8";
            case D3DFMT_G8R8_G8B8:
                return "D3DFMT_G8R8_G8B8";
            case D3DFMT_DXT1:
                return "D3DFMT_DXT1";
            case D3DFMT_DXT2:
                return "D3DFMT_DXT2";
            case D3DFMT_DXT3:
                return "D3DFMT_DXT3";
            case D3DFMT_DXT4:
                return "D3DFMT_DXT4";
            case D3DFMT_DXT5:
                return "D3DFMT_DXT5";
            case D3DFMT_D16_LOCKABLE:
                return "D3DFMT_D16_LOCKABLE";
            case D3DFMT_D16:
                return "D3DFMT_D16";
            case D3DFMT_D24S8:
                return "D3DFMT_D24S8";
            case D3DFMT_D32:
                return "D3DFMT_D32";
            case D3DFMT_D32F_LOCKABLE:
                return "D3DFMT_D32F_LOCKABLE";
            case D3DFMT_Q16W16V16U16:
                return "D3DFMT_Q16W16V16U16";
            case D3DFMT_R16F:
                return "D3DFMT_R16F";
            case D3DFMT_G16R16F:
                return "D3DFMT_G16R16F";
            case D3DFMT_A16B16G16R16F:
                return "D3DFMT_A16B16G16R16F";
            case D3DFMT_R32F:
                return "D3DFMT_R32F";
            case D3DFMT_G32R32F:
                return "D3DFMT_G32R32F";
            case D3DFMT_A32B32G32R32F:
                return "D3DFMT_A32B32G32R32F";
            case D3DFMT_A2B10G10R10_XR_BIAS:
                return "D3DFMT_A2B10G10R10_XR_BIAS";
            case D3DFMT_L8:
                return "D3DFMT_L8";
            case D3DFMT_A8L8:
                return "D3DFMT_A8L8";
            case D3DFMT_L16:
                return "D3DFMT_L16";
            default:
                return fmt::format("Unknown Format: {}", (int)d3dFormat).c_str();
        }
    }

    DXGI_FORMAT TextureFormatToDXGI(ETextureFormat format)
    {
        switch (format)
        {
            case ETextureFormat::R8_G8_B8_A8:
                return DXGI_FORMAT_R8G8B8A8_UNORM;
            case ETextureFormat::B8_G8_R8_A8:
                return DXGI_FORMAT_B8G8R8A8_UNORM;
            default:
                THROW("Unknown ETextureFormat Format: {}", (int)format);
        }
    }
}