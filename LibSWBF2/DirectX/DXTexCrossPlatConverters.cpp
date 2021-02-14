#include "DXTexCrossPlat.h"
#include "DXTexCrossPlatConverters.h"

#define DETEX_VERSION 1
#include "detex/detex.h"

#include <math.h>


#define BMASK_5BIT 0x001f
#define GMASK_6BIT 0x07e0
#define RMASK_5BIT 0xf800
#define MASK 0xff

namespace DXTexCrossPlat {


void a1r5g5b5(int w, int h, uint8_t *src, uint32_t *sink)
{
    uint16_t *inPixels = reinterpret_cast<uint16_t *>(src);

    for(int i = 0; i < w * h; i++) {

        uint32_t outPixel = 0;
        uint16_t inPixel = inPixels[i];

        outPixel |= (inPixel & BMASK_5BIT) << 19;
        outPixel |= (inPixel & GMASK_6BIT) << 5;
        outPixel |= (inPixel & RMASK_5BIT) >> 8;
        outPixel |= MASK << 24;

        sink[i] = outPixel;     
    }

}




void r5g6b5ToRGBA(int w, int h, unsigned char *src, uint32_t *sink) {

	uint16_t *inPixels = reinterpret_cast<uint16_t *>(src);

    for(int i = 0; i < w * h; i++) {

        uint32_t outPixel = 0;
    	uint16_t inPixel = inPixels[i];

        outPixel |= (inPixel & BMASK_5BIT) << 19;
        outPixel |= (inPixel & GMASK_6BIT) << 5;
        outPixel |= (inPixel & RMASK_5BIT) >> 8;
        outPixel |= MASK << 24;

        sink[i] = outPixel;     
    }
}


void a8r8g8b8ToRBGA(int w, int h, unsigned char *src, uint32_t *sink) { 

    uint32_t *inPixels = reinterpret_cast<uint32_t *>(src);

    for (int i = 0; i < w * h; i++) {

        uint32_t inPixel = inPixels[i];
        uint32_t outPixel = 0;

        outPixel |= 0xff00ff00    & inPixel;
        outPixel |= ( MASK        & inPixel) << 16; //swap r and b
        outPixel |= ((MASK << 16) & inPixel) >> 16;

        sink[i] = outPixel;       
    }
}


void bcToRGBA(int w, int h, unsigned char *src, uint32_t *sink, int mode) {
    
    static uint32_t *blockSink = new uint32_t[16]; 

    bool (*decomp_func) (const uint8_t * DETEX_RESTRICT bitstring, uint32_t mode_mask,
                        uint32_t flags, uint8_t * DETEX_RESTRICT pixel_buffer);

    int blockSize = 16, srcSize = w * h;
    if (mode == 1){   
        blockSize = 8; //BC1 uses 8 byte blocks, 
                       //must half size of srcdata comsumed
        srcSize /= 2;
        decomp_func = &detexDecompressBlockBC1A;
    } else if (mode == 2){
        decomp_func = &detexDecompressBlockBC2;
    } else {
        decomp_func = &detexDecompressBlockBC3;
    }

    //Iterate through each block
    for (int i = 0; i < srcSize; i += blockSize) {
        
        //Decompresses a 4x4 block (16 bytes, but pixels are not byte-aligned)
        //2nd & 3rd params aren't even used in detex...
        (*decomp_func) (src + i, 1, 1, reinterpret_cast<uint8_t *>(blockSink));

        //Good to be explicit w/this kind of thing
        int blockNum = i / blockSize;
        int numBlocksInRow = w / 4;

        int x = 4 * (blockNum % numBlocksInRow);
        int y = 4 * (blockNum / numBlocksInRow);

        int startIndex = y * w + x; 

        for (int j = 0; j < 16; j++) {
            int outIndex = startIndex + (j / 4) * w + (j % 4);
            sink[outIndex] = blockSink[j];
        }
    }
}


void lumToRGBA(int w, int h, uint8_t *src, uint32_t *sink, const D3DFORMAT format) {

    int stepSize = (format == D3DFMT_L16 || format == D3DFMT_A8L8) ? 2 : 1;

    for (int i = 0; i < w * h * stepSize; i+=stepSize) {
          
        uint8_t *curAddr = src + i;
        uint32_t l = 0, a = 0xff, pixel = 0;

        switch (format){
            case D3DFMT_L8:
                l |= *curAddr & 0xff;
                break;
            case D3DFMT_L16:
                l |= (*(uint16_t *) curAddr) >> 8; 
                break;
            case D3DFMT_A8L8:
                l |= (*(uint16_t *) curAddr & 0xff);
                a |= (*(uint16_t *) curAddr & 0xff00) >> 8;
                break;
            default: //A4L4
                l |= (*curAddr & 0xf) << 4;
                a |= (*curAddr & 0xf0);
                break;
        }

        pixel = l;
        pixel |= (l << 8);
        pixel |= (l << 16);
        pixel |= (a << 24);

        sink[i / stepSize] = pixel;
    }
}



}