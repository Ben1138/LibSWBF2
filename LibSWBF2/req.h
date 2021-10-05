// External requirements to compile the include headers in third party applications
#pragma once

#include <stdint.h>		// for uint32_t, etc. declarations
#include <math.h>		// for float_t declaration

#ifdef WIN32

#ifdef LibSWBF2_EXPORTS
#define LIBSWBF2_API __declspec(dllexport)
#else
#define LIBSWBF2_API __declspec(dllimport)
#endif //LIBSWBF2_EXPORTS

#else

#define LIBSWBF2_API __attribute__((visibility("default")))

#endif //_WIN32

namespace LibSWBF2
{
	// only reason for a ChunkSize definition here is so we
	// can easily change the type to uin64_t if ever necessary
	typedef uint32_t ChunkSize;

	typedef uint32_t CRCChecksum;
	typedef uint32_t FNVHash;

	typedef uint16_t SWBF2Handle;

#define SWBF2HANDLE_INVALID 0xffff
}