#include "DXTexCrossPlat.h"
#include "DXTexCrossPlatConverters.h"
#include "DXHelpers.h"

#include "InternalHelpers.h"
#include "Logging/Logger.h"
#include <cstring>

namespace DXTexCrossPlat {

CrossPlatImage::CrossPlatImage(uint16_t w, uint16_t h,
                              D3DFORMAT f, 
                              uint8_t* dataPtr, size_t dataSize){

  if (w % 4 != 0 || h % 4 != 0 || w * h == 0) {
    valid = false;
    //LOG_ERROR("Texture dims must both be multiples of 4 and nonzero")
  }

  if (valid) { 
    width = w;
    height = h;
    unitSize = dataSize / (width * height);
    format = f;
    dataLength = dataSize;

    uint8_t* bytes = new uint8_t[dataSize]();

    if (dataPtr != nullptr)
      memcpy(bytes, dataPtr, dataSize);

    data = bytes;
  }
}


CrossPlatImage::~CrossPlatImage()
{
  delete[] data;
}


uint8_t* CrossPlatImage::DumpRaw(){

  if (!valid) return nullptr;

  uint8_t* sink = new uint8_t[dataLength];
  memcpy(sink, data, dataLength);

  return sink;
}


uint8_t* CrossPlatImage::DumpRGBA(){

  if (!valid) return nullptr;

  uint32_t* sink = new uint32_t[width * height]();
  uint8_t* source = data;

  switch (format){
    case D3DFMT_R5G6B5:
      r5g6b5ToRGBA(width, height, source, sink);
      break;
    //case D3DFMT_A1R5G5B5:
    //  a1r5g5b5ToRGBA(width, height, source, sink);
    //  break;
    case D3DFMT_A8R8G8B8:
      a8r8g8b8ToRBGA(width, height, source, sink);
      break;
    case D3DFMT_DXT1:                     //mode 1 = bc1, 2 = bc2,...
      bcToRGBA(width, height, source, sink, 1);
      break;
    case D3DFMT_DXT2:
    case D3DFMT_DXT3:
      bcToRGBA(width, height, source, sink, 2);
      break;
    case D3DFMT_DXT4:
    case D3DFMT_DXT5:
      bcToRGBA(width, height, source, sink, 3);
      break;
    case D3DFMT_L8:
    case D3DFMT_A8L8:
    case D3DFMT_L16:
    case D3DFMT_A4L4:
      lumToRGBA(width, height, source, sink, format);
      break;
    default:
      LOG_ERROR("Cannot convert {} to R8_G8_B8_A8", LibSWBF2::D3DToString(format));
      //delete[] sink;
      //sink = nullptr;   
      break; 
  }
  return reinterpret_cast<uint8_t *>(sink);
}


}