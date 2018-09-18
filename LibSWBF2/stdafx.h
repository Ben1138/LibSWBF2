#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Don't include rarely used windows stuff
#include <windows.h>


// TODO: Place additional headers here
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <type_traits>
#include <cmath>
#include <algorithm>
#include <functional>

namespace LibSWBF2
{
	// we don't want to lift up everything from std!
	// so just lift up what we need
	using std::clamp;
	using std::string;
	using std::vector;
	using std::queue;
	using std::unique_ptr;
	using std::function;

	// define types
	typedef int32_t ChunkHeader;
	typedef uint32_t ChunkSize;
}