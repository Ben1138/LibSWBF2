#include "stdafx.h"
#include "BODY.h"
#include "FMT_.h"
#include "Logging/Logger.h"
//#include "DirectX/DXHelpers.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include <algorithm>


namespace LibSWBF2::Chunks::LVL::LVL_texture
{
    using LVL::texture::FMT_;

    void BODY::RefreshSize()
    {
        THROW("Not implemented!");
    }

    void BODY::WriteToStream(FileWriter& stream)
    {
        THROW("Not implemented!");
    }

    void BODY::ReadFromStream(FileReader& stream)
    {
        /*
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        const LVL_* lvl = dynamic_cast<const LVL_*>(GetParent());

        //                                                  FACE         FMT_
        const FMT_* fmt = dynamic_cast<const FMT_*>(lvl->GetParent()->GetParent());
        if (fmt == nullptr)
        {
            LOG_ERROR("Could not grab FMT parent!");
            BaseChunk::EnsureEnd(stream);
            return;
        }

        if (p_Image != nullptr)
        {
            delete p_Image;
            p_Image = nullptr;
        }

        size_t width = fmt->p_Info->m_Width;
        size_t height = fmt->p_Info->m_Height;
        // mip levels start at 0
        // divide resolution by 2 for each increasing mip level
        size_t div = (size_t)std::pow(2, lvl->p_Info->m_MipLevel);

        // don't go below 2x2 pixels, DirectX will crash otherwise
        // in e.g. geo1.lvl there's a case with a 512x256 image with
        // a mip level up to 9 (dafuq)
        width = std::max(width / div, (size_t)2);
        height = std::max(height / div, (size_t)2);

        p_Image = new DirectX::ScratchImage();
        p_Image->Initialize2D(D3DToDXGI(fmt->p_Info->m_Format), width, height, 1, 1);
        const DirectX::Image* img = p_Image->GetImage(0, 0, 0);

        if (!stream.ReadBytes(img->pixels, GetDataSize()))
        {
            LOG_ERROR("Reading data failed!");
            BaseChunk::EnsureEnd(stream);
            return;
        }

        BaseChunk::EnsureEnd(stream);
        */
    }

    bool BODY::GetImageData(ETextureFormat format, uint16_t& width, uint16_t& height, const uint8_t*& data)
    {
        /*
        if (p_Image == nullptr)
        {
            LOG_WARN("Called GetImageData before reading!");
            data = nullptr;
            return false;
        }

        const DirectX::Image* img = p_Image->GetImage(0, 0, 0);
        if (img == nullptr)
        {
            LOG_WARN("Called GetImageData before reading!");
            data = nullptr;
            return false;
        }

        DXGI_FORMAT targetFormat = TextureFormatToDXGI(format);
        if (DirectX::IsCompressed(img->format))
        {
            DirectX::ScratchImage* result = new DirectX::ScratchImage();
            if (FAILED(DirectX::Decompress(*img, targetFormat, *result)))
            {
                LOG_WARN("Could not decompress Image");
                delete result;
                return false;
            }
            delete p_Image;
            p_Image = result;
            img = p_Image->GetImage(0, 0, 0);
        }

        if (img->format != targetFormat)
        {
            DirectX::ScratchImage* result = new DirectX::ScratchImage();
            if (FAILED(DirectX::Convert(*img, targetFormat, DirectX::TEX_FILTER_DEFAULT, DirectX::TEX_THRESHOLD_DEFAULT, *result)))
            {
                LOG_WARN("Could not convert Image");
                delete result;
                return false;
            }
            
            delete p_Image;
            p_Image = result;
            img = p_Image->GetImage(0, 0, 0);
        }

        width = (uint16_t)img->width;
        height = (uint16_t)img->height;
        data = img->pixels;
        return data != nullptr;
        */
        return true;
    }
}