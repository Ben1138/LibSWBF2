#include "stdafx.h"
#include "BODY.h"
#include "FMT_.h"
#include "Logging/Logger.h"
#include "DirectX/DXHelpers.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include <algorithm>
#include <cstring>

#ifndef _WIN32
#include "DXTexCrossPlat.h"
#endif


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

        size_t dataSize = GetDataSize();
        D3DFORMAT d3dFormat = fmt->p_Info->m_Format;

        // it seems like sometimes (in core.lvl) the specified image size
        // is far smaller than the actual BODY data size... So just do a quick
        // sanity check here before allocating and performing a memcpy
        if (dataSize > width * height * 4)
        {
            stream.SkipBytes(dataSize);
            LOG_WARN("Suspicious image size: {}! Skipping image!", dataSize);
            BaseChunk::EnsureEnd(stream);
            return;
        }

        uint8_t* bytes = new uint8_t[dataSize];
        if (!stream.ReadBytes(bytes, dataSize))
        {
            LOG_ERROR("Reading image data of size '{}' failed!", dataSize);
            BaseChunk::EnsureEnd(stream);
            return;
        }

#ifdef _WIN32
        p_Image = new DirectX::ScratchImage();
        p_Image->Initialize2D(D3DToDXGI(d3dFormat), width, height, 1, 1);
        const DirectX::Image* img = p_Image->GetImage(0, 0, 0);
        memcpy(img->pixels, bytes, dataSize);
#else
        p_Image = new DXTexCrossPlat::CrossPlatImage(width, height, 
                                                    d3dFormat, bytes,
                                                    dataSize);
#endif
        delete[] bytes;
        BaseChunk::EnsureEnd(stream);       
    }


    bool BODY::GetImageData(ETextureFormat format, uint16_t& width, uint16_t& height, const uint8_t*& data)
    {
        if (p_Image == nullptr)
        {
            LOG_WARN("No image!");
            width = 0;
            height = 0;
            data = nullptr;
            return false;
        }

#ifdef _WIN32

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

#else 
        width = p_Image->width;
        height = p_Image->height;
        data = p_Image -> DumpRGBA();

#endif //_WIN32

        return data != nullptr;    
    }

    BODY::~BODY()
    {
        delete p_Image;
    }

}