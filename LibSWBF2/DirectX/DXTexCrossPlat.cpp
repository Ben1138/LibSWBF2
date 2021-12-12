#include "pch.h"
#include "DXTexCrossPlat.h"
#include "DXTexCrossPlatConverters.h"
#include "DXHelpers.h"

#include "InternalHelpers.h"
#include "Logging/Logger.h"

namespace DXTexCrossPlat {

#define VALIDATE_DIMS(w,h) m_IsValid = true; uint32_t m=w*h; if (m == 0 || (m & (m-1)) != 0){ LOG_ERROR("Texture dims ({0},{1}) must both be powers of 2 and nonzero",w,h); m_IsValid = false; }


CrossPlatImage::CrossPlatImage(uint16_t w, uint16_t h,
                              D3DFORMAT f, 
                              uint8_t*& dataPtr, size_t dataSize){
  VALIDATE_DIMS(w,h);

  if (m_IsValid) 
  {   
    width = w;
    height = h;
    cellSize = dataSize / (width * height);
    
    m_DataLength = dataSize;
    
    format = f;

    p_Data = dataPtr;
    dataPtr = nullptr;
  }
}


CrossPlatImage::CrossPlatImage(uint16_t w, uint16_t h, D3DFORMAT f, size_t dataSize)
{
  VALIDATE_DIMS(w,h);

  if (m_IsValid)
  {
    width = w;
    height = h;
    cellSize = dataSize / (width * height);

    m_DataLength = dataSize;

    format = f;

    p_Data = new uint8_t[dataSize];
  }
}


CrossPlatImage::~CrossPlatImage()
{
  delete[] p_Data;
}


bool CrossPlatImage::IsConvertibleTo(D3DFORMAT f)
{
  if (format == f) return true;

  if (f != D3DFMT_R8G8B8A8) return false;

  switch (format)
  {
    case D3DFMT_R5G6B5:
    case D3DFMT_A8R8G8B8:
    case D3DFMT_DXT1:
    case D3DFMT_DXT2:
    case D3DFMT_DXT3:
    case D3DFMT_DXT4:
    case D3DFMT_DXT5:
    case D3DFMT_L8:
    case D3DFMT_A8L8:
    case D3DFMT_L16:
    case D3DFMT_A4L4:
      return true;
    default:
      return false;
  }
}


uint8_t* CrossPlatImage::GetPixelsPtr()
{
  return m_IsValid ? p_Data : nullptr;
}


bool CrossPlatImage::ConvertTo(D3DFORMAT f)
{
  if (format == f) return true;
  if (f != D3DFMT_R8G8B8A8) return false;
  return ToRGBA();
}


bool CrossPlatImage::ToRGBA(){

  if (!m_IsValid) return false;

  uint32_t* sink = new uint32_t[width * height]();

  switch (format){
    case D3DFMT_R5G6B5:
      r5g6b5ToRGBA(width, height, p_Data, sink);
      break;
    //case D3DFMT_A1R5G5B5:
    //  a1r5g5b5ToRGBA(width, height, source, sink);
    //  break;
    case D3DFMT_A8R8G8B8:
      a8r8g8b8ToRBGA(width, height, p_Data, sink);
      break;
    case D3DFMT_DXT1:                //mode 1 = bc1, 2 = bc2,...
      bcToRGBA(width, height, p_Data, sink, 1);
      break;
    case D3DFMT_DXT2:
    case D3DFMT_DXT3:
      bcToRGBA(width, height, p_Data, sink, 2);
      break;
    case D3DFMT_DXT4:
    case D3DFMT_DXT5:
      bcToRGBA(width, height, p_Data, sink, 3);
      break;
    case D3DFMT_L8:
    case D3DFMT_A8L8:
    case D3DFMT_L16:
    case D3DFMT_A4L4:
      lumToRGBA(width, height, p_Data, sink, format);
      break;
    default:
      LOG_ERROR("(Shouldn't happen...) Cannot convert {} to R8_G8_B8_A8!", LibSWBF2::D3DToString(format));
      delete[] sink;
      return false;
  }

  delete[] p_Data;
  p_Data = (uint8_t *) sink;

  return true;
}


}