#pragma once

/*
Format conversion functions.  Kept things relatively low level
since most libraries (glaring at you GLI) that claimed to handle
this exact task kept pretty dismal or no documentation... 
*/

#include "D3D9FORMAT.h"
#include <stdint.h>

namespace DXTexCrossPlat {

void r5g6b5ToRGBA(int w, int h, uint8_t *src, uint32_t *sink);
void a8r8g8b8ToRBGA(int w, int h, uint8_t *src, uint32_t *sink);
void bcToRGBA(int w, int h, uint8_t *src, uint32_t *sink, int mode);
void lumToRGBA(int w, int h, uint8_t *src, uint32_t *sink, const D3DFORMAT format);

}