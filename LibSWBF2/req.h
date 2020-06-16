// External requirements to compile the include headers in third party applications
#pragma once

#include <stdint.h>		// for uint32_t, etc. declarations
#include <math.h>		// for float_t declaration

#ifdef LIBSWBF2_EXPORTS
#define LIBSWBF2_API __declspec(dllexport)
#else
#define LIBSWBF2_API __declspec(dllimport)
#endif

namespace LibSWBF2
{
	// only reason for a ChunkSize definition here is so we
	// can easily change the type to uin64_t if ever necessary
	typedef uint32_t ChunkSize;

	typedef uint32_t CRCChecksum;
}