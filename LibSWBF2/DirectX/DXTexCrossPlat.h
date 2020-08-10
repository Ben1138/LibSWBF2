#pragma once


#include <memory>
#include <stdint.h>

#include "D3D9FORMAT.h"


namespace DXTexCrossPlat {

class CrossPlatImage {

public:
	CrossPlatImage(uint16_t w, uint16_t h,  
				   D3DFORMAT f, 
				   uint8_t *dataPtr=nullptr,
				   size_t dataSize=0);

	uint8_t* DumpRGBA();
	uint8_t* DumpRaw();
	//~CrossPlatImage();

	uint16_t width,height,unitSize;

private:
	size_t dataLength;
	std::shared_ptr<uint8_t> data;
	D3DFORMAT format;
	bool valid = true;
};

}