#include "stdafx.h"
#include "BODY.h"
#include "FMT_.h"
#include <DirectXTex.h>

namespace LibSWBF2::Chunks::LVL
{
    static DirectX::ScratchImage* p_Image = nullptr;

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
            throw std::runtime_error("Unknown D3D Format: " + std::to_string(d3dFormat));
        }
    }

    void BODY::RefreshSize()
    {
        throw std::runtime_error("Not implemented!");
    }

    void BODY::WriteToStream(FileWriter& stream)
    {
        throw std::runtime_error("Not implemented!");
    }

    void BODY::ReadFromStream(FileReader& stream)
    {
        BaseChunk::ReadFromStream(stream);

        //                                             LVL_         FACE         FMT_
        const FMT_* fmt = dynamic_cast<const FMT_*>(GetParent()->GetParent()->GetParent());
        if (fmt == nullptr)
        {
            LOG("Could not grab FMT parent!", ELogType::Error);
            BaseChunk::EnsureEnd(stream);
            return;
        }

        if (p_Image != nullptr)
        {
            delete p_Image;
            p_Image = nullptr;
        }

        p_Image = new DirectX::ScratchImage();
        p_Image->Initialize2D(D3DToDXGI(fmt->p_Info->m_Format), fmt->p_Info->m_Width, fmt->p_Info->m_Height, 1, 1);
        const DirectX::Image* img = p_Image->GetImage(0, 0, 0);

        if (!stream.ReadBytes(img->pixels, GetDataSize()))
        {
            LOG("Reading data failed!", ELogType::Error);
            BaseChunk::EnsureEnd(stream);
            return;
        }

        BaseChunk::EnsureEnd(stream);
    }

    void BODY::GetImageData(uint16_t& width, uint16_t& height, uint8_t*& data)
    {
        if (p_Image == nullptr)
        {
            LOG("Called GetImageData before reading!", ELogType::Warning);
            data = nullptr;
            return;
        }

        const DirectX::Image* img = p_Image->GetImage(0, 0, 0);
        if (img == nullptr)
        {
            LOG("Called GetImageData before reading!", ELogType::Warning);
            data = nullptr;
            return;
        }

        //                                             LVL_         FACE         FMT_
        const FMT_* fmt = dynamic_cast<const FMT_*>(GetParent()->GetParent()->GetParent());
        if (fmt == nullptr)
        {
            LOG("Could not grab FMT parent!", ELogType::Error);
            return;
        }

        if (DirectX::IsCompressed(img->format))
        {
            DirectX::ScratchImage* result = new DirectX::ScratchImage();
            if (FAILED(DirectX::Decompress(*img, DXGI_FORMAT_R8G8B8A8_UNORM, *result)))
            {
                LOG("Could not decompress Image", ELogType::Warning);
                delete result;
                return;
            }
            delete p_Image;
            p_Image = result;
            img = p_Image->GetImage(0, 0, 0);
        }

        if (img->format != DXGI_FORMAT_R8G8B8A8_UNORM)
        {
            DirectX::ScratchImage* result = new DirectX::ScratchImage();
            if (FAILED(DirectX::Convert(*img, DXGI_FORMAT_R8G8B8A8_UNORM, DirectX::TEX_FILTER_DEFAULT, DirectX::TEX_THRESHOLD_DEFAULT, *result)))
            {
                LOG("Could not convert Image", ELogType::Warning);
                delete result;
                return;
            }
            
            delete p_Image;
            p_Image = result;
            img = p_Image->GetImage(0, 0, 0);
        }

        width = fmt->p_Info->m_Width;
        height = fmt->p_Info->m_Height;
        data = img->pixels;
    }
}