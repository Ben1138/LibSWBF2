#ifndef D3D9FORMAT_H
#define D3D9FORMAT_H
/*==========================================================================;
 *
 *  Partially copied header from D3D9Types.h and altered for the snippet
 *  to work independently
 *
 ***************************************************************************/

#include "req.h"



 /* Formats
  * Most of these names have the following convention:
  *      A = Alpha
  *      R = Red
  *      G = Green
  *      B = Blue
  *      X = Unused Bits
  *      P = Palette
  *      L = Luminance
  *      U = dU coordinate for BumpMap
  *      V = dV coordinate for BumpMap
  *      S = Stencil
  *      D = Depth (e.g. Z or W buffer)
  *      C = Computed from other channels (typically on certain read operations)
  *
  *      Further, the order of the pieces are from MSB first; hence
  *      D3DFMT_A8L8 indicates that the high byte of this two byte
  *      format is alpha.
  *
  *      D3DFMT_D16_LOCKABLE indicates:
  *           - An integer 16-bit value.
  *           - An app-lockable surface.
  *
  *      D3DFMT_D32F_LOCKABLE indicates:
  *           - An IEEE 754 floating-point value.
  *           - An app-lockable surface.
  *
  *      All Depth/Stencil formats except D3DFMT_D16_LOCKABLE and D3DFMT_D32F_LOCKABLE indicate:
  *          - no particular bit ordering per pixel, and
  *          - are not app lockable, and
  *          - the driver is allowed to consume more than the indicated
  *            number of bits per Depth channel (but not Stencil channel).
  */
#ifndef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
                ((uint32_t)(uint8_t)(ch0) | ((uint32_t)(uint8_t)(ch1) << 8) |       \
                ((uint32_t)(uint8_t)(ch2) << 16) | ((uint32_t)(uint8_t)(ch3) << 24 ))
#endif /* defined(MAKEFOURCC) */


typedef enum _D3DFORMAT
{
    D3DFMT_UNKNOWN = 0,

    D3DFMT_R8G8B8 = 20,
    D3DFMT_A8R8G8B8 = 21,
    D3DFMT_X8R8G8B8 = 22,
    D3DFMT_R5G6B5 = 23,
    D3DFMT_X1R5G5B5 = 24,
    D3DFMT_A1R5G5B5 = 25,
    D3DFMT_A4R4G4B4 = 26,
    D3DFMT_R3G3B2 = 27,
    D3DFMT_A8 = 28,
    D3DFMT_A8R3G3B2 = 29,
    D3DFMT_X4R4G4B4 = 30,
    D3DFMT_A2B10G10R10 = 31,
    D3DFMT_A8B8G8R8 = 32,
    D3DFMT_X8B8G8R8 = 33,
    D3DFMT_G16R16 = 34,
    D3DFMT_A2R10G10B10 = 35,
    D3DFMT_A16B16G16R16 = 36,

    D3DFMT_A8P8 = 40,
    D3DFMT_P8 = 41,

    D3DFMT_L8 = 50,
    D3DFMT_A8L8 = 51,
    D3DFMT_A4L4 = 52,

    D3DFMT_V8U8 = 60,
    D3DFMT_L6V5U5 = 61,
    D3DFMT_X8L8V8U8 = 62,
    D3DFMT_Q8W8V8U8 = 63,
    D3DFMT_V16U16 = 64,
    D3DFMT_A2W10V10U10 = 67,

    D3DFMT_UYVY = MAKEFOURCC('U', 'Y', 'V', 'Y'),
    D3DFMT_R8G8_B8G8 = MAKEFOURCC('R', 'G', 'B', 'G'),
    D3DFMT_YUY2 = MAKEFOURCC('Y', 'U', 'Y', '2'),
    D3DFMT_G8R8_G8B8 = MAKEFOURCC('G', 'R', 'G', 'B'),
    D3DFMT_DXT1 = MAKEFOURCC('D', 'X', 'T', '1'),
    D3DFMT_DXT2 = MAKEFOURCC('D', 'X', 'T', '2'),
    D3DFMT_DXT3 = MAKEFOURCC('D', 'X', 'T', '3'),
    D3DFMT_DXT4 = MAKEFOURCC('D', 'X', 'T', '4'),
    D3DFMT_DXT5 = MAKEFOURCC('D', 'X', 'T', '5'),

    D3DFMT_D16_LOCKABLE = 70,
    D3DFMT_D32 = 71,
    D3DFMT_D15S1 = 73,
    D3DFMT_D24S8 = 75,
    D3DFMT_D24X8 = 77,
    D3DFMT_D24X4S4 = 79,
    D3DFMT_D16 = 80,

    D3DFMT_D32F_LOCKABLE = 82,
    D3DFMT_D24FS8 = 83,

    /* D3D9Ex only -- */
#if !defined(D3D_DISABLE_9EX)

    /* Z-Stencil formats valid for CPU access */
    D3DFMT_D32_LOCKABLE = 84,
    D3DFMT_S8_LOCKABLE = 85,

#endif // !D3D_DISABLE_9EX
    /* -- D3D9Ex only */


    D3DFMT_L16 = 81,

    D3DFMT_VERTEXDATA = 100,
    D3DFMT_INDEX16 = 101,
    D3DFMT_INDEX32 = 102,

    D3DFMT_Q16W16V16U16 = 110,

    D3DFMT_MULTI2_ARGB8 = MAKEFOURCC('M', 'E', 'T', '1'),

    // Floating point surface formats

    // s10e5 formats (16-bits per channel)
    D3DFMT_R16F = 111,
    D3DFMT_G16R16F = 112,
    D3DFMT_A16B16G16R16F = 113,

    // IEEE s23e8 formats (32-bits per channel)
    D3DFMT_R32F = 114,
    D3DFMT_G32R32F = 115,
    D3DFMT_A32B32G32R32F = 116,

    D3DFMT_CxV8U8 = 117,

    /* D3D9Ex only -- */
#if !defined(D3D_DISABLE_9EX)

    // Monochrome 1 bit per pixel format
    D3DFMT_A1 = 118,

    // 2.8 biased fixed point
    D3DFMT_A2B10G10R10_XR_BIAS = 119,


    // Binary format indicating that the data has no inherent type
    D3DFMT_BINARYBUFFER = 199,

#endif // !D3D_DISABLE_9EX
    /* -- D3D9Ex only */


    D3DFMT_FORCE_DWORD = 0x7fffffff
} D3DFORMAT;



#ifndef _WIN32

//Lazy redef copy/pasted from D3DToDXGI
//for crossplat compilation's sake 

typedef enum _DXGI_FORMAT
{

DXGI_FORMAT_B8G8R8A8_UNORM = __LINE__,
DXGI_FORMAT_B8G8R8X8_UNORM = __LINE__,
DXGI_FORMAT_B5G6R5_UNORM = __LINE__,
DXGI_FORMAT_B5G5R5A1_UNORM = __LINE__,
DXGI_FORMAT_B4G4R4A4_UNORM = __LINE__,
DXGI_FORMAT_A8_UNORM = __LINE__,
DXGI_FORMAT_R10G10B10A2_UNORM = __LINE__,
DXGI_FORMAT_R8G8B8A8_UNORM = __LINE__,
DXGI_FORMAT_R16G16_UNORM = __LINE__,
DXGI_FORMAT_R16G16B16A16_UNORM = __LINE__,
DXGI_FORMAT_R8G8_SNORM = __LINE__,
DXGI_FORMAT_R8G8B8A8_SNORM = __LINE__,
DXGI_FORMAT_R16G16_SNORM = __LINE__,
DXGI_FORMAT_G8R8_G8B8_UNORM = __LINE__,
DXGI_FORMAT_R8G8_B8G8_UNORM = __LINE__,
DXGI_FORMAT_BC1_UNORM = __LINE__,
DXGI_FORMAT_BC2_UNORM = __LINE__,
DXGI_FORMAT_BC3_UNORM = __LINE__,
DXGI_FORMAT_BC4_UNORM = __LINE__,
DXGI_FORMAT_BC5_UNORM = __LINE__,
DXGI_FORMAT_BC6_UNORM = __LINE__,
DXGI_FORMAT_BC7_UNORM = __LINE__,
DXGI_FORMAT_D16_UNORM = __LINE__,
DXGI_FORMAT_D24_UNORM_S8_UINT = __LINE__,
DXGI_FORMAT_D32_FLOAT = __LINE__,
DXGI_FORMAT_R16G16B16A16_SNORM = __LINE__,
DXGI_FORMAT_R16_FLOAT = __LINE__,
DXGI_FORMAT_R16G16_FLOAT = __LINE__,
DXGI_FORMAT_R16G16B16A16_FLOAT = __LINE__,
DXGI_FORMAT_R32_FLOAT = __LINE__,
DXGI_FORMAT_R32G32_FLOAT = __LINE__,
DXGI_FORMAT_R32G32B32A32_FLOAT = __LINE__,
DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM = __LINE__,
DXGI_FORMAT_R8_UNORM = __LINE__,
DXGI_FORMAT_R8G8_UNORM = __LINE__,
DXGI_FORMAT_R16_UNORM = __LINE__,

DXGI_FORMAT_BC1_TYPELESS = __LINE__,
DXGI_FORMAT_BC1_UNORM_SRGB = __LINE__,
DXGI_FORMAT_BC2_TYPELESS = __LINE__,
DXGI_FORMAT_BC2_UNORM_SRGB = __LINE__,
DXGI_FORMAT_BC3_TYPELESS = __LINE__,
DXGI_FORMAT_BC3_UNORM_SRGB = __LINE__,
DXGI_FORMAT_BC4_TYPELESS = __LINE__,
DXGI_FORMAT_BC4_SNORM = __LINE__,
DXGI_FORMAT_BC5_TYPELESS = __LINE__,
DXGI_FORMAT_BC5_SNORM = __LINE__,
DXGI_FORMAT_BC6H_TYPELESS = __LINE__,
DXGI_FORMAT_BC6H_UF16 = __LINE__,
DXGI_FORMAT_BC6H_SF16 = __LINE__,
DXGI_FORMAT_BC7_TYPELESS = __LINE__,
DXGI_FORMAT_BC7_UNORM_SRGB = __LINE__,

DX_FORMAT_FORCE_DWORD = 0x7fffffff

} DXGI_FORMAT;


inline bool IsCompressed(DXGI_FORMAT fmt) {
  switch (fmt) {   
      case DXGI_FORMAT_BC1_TYPELESS:
      case DXGI_FORMAT_BC1_UNORM:
      case DXGI_FORMAT_BC1_UNORM_SRGB:
      case DXGI_FORMAT_BC2_TYPELESS:
      case DXGI_FORMAT_BC2_UNORM:
      case DXGI_FORMAT_BC2_UNORM_SRGB:
      case DXGI_FORMAT_BC3_TYPELESS:
      case DXGI_FORMAT_BC3_UNORM:
      case DXGI_FORMAT_BC3_UNORM_SRGB:
      case DXGI_FORMAT_BC4_TYPELESS:
      case DXGI_FORMAT_BC4_UNORM:
      case DXGI_FORMAT_BC4_SNORM:
      case DXGI_FORMAT_BC5_TYPELESS:
      case DXGI_FORMAT_BC5_UNORM:
      case DXGI_FORMAT_BC5_SNORM:
      case DXGI_FORMAT_BC6H_TYPELESS:
      case DXGI_FORMAT_BC6H_UF16:
      case DXGI_FORMAT_BC6H_SF16:
      case DXGI_FORMAT_BC7_TYPELESS:
      case DXGI_FORMAT_BC7_UNORM:
      case DXGI_FORMAT_BC7_UNORM_SRGB:
          return true;
      default:
          return false;
  }
}

#endif /*_WIN32*/



#endif //D3D9FORMAT_H