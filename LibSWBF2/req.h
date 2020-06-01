// This file should include all requirements

#if defined _LIB || defined LIBSWBF2DLL_EXPORTS
#define LIBSWBF2_EXP __declspec(dllexport)
#else
#define LIBSWBF2_EXP __declspec(dllimport)
#endif

#pragma once
#include <string>
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
	using std::queue;
	using std::unique_ptr;
	using std::function;

	// only reason for a ChunkSize definition here is so we
	// can easily change the type to uin64_t if ever necessary
	typedef uint32_t ChunkSize;

	typedef uint32_t CRCChecksum;
}