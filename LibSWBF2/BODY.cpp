#include "stdafx.h"
#include "BODY.h"
#include "FMT_.h"
#include "DXHelpers.h"

namespace LibSWBF2::Chunks::LVL
{
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

        width = img->width;
        height = img->height;
        data = img->pixels;
    }
}