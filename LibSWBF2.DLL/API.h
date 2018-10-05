#pragma once
#include "../LibSWBF2/Logger.h"
#include "../LibSWBF2/LoggerEntry.h"
#include "../LibSWBF2/Color.h"
#include "../LibSWBF2/Vector2.h"
#include "../LibSWBF2/Vector3.h"
#include "../LibSWBF2/Vector4.h"
#include "../LibSWBF2/MSH.h"

#ifdef LIBSWBF2DLL_EXPORTS
#define LIBSWBF2_API __declspec(dllexport)
#else
#define LIBSWBF2_API __declspec(dllimport)
#pragma comment(lib, "LibSWBF2.dll")
#endif

namespace LibSWBF2::API
{
	// be carefull in the futute!
	// there might be multiple chunks with the same m_NAME
	using namespace Chunks::Mesh;
	using namespace Types;
	using namespace Logging;

	extern "C"
	{
		LIBSWBF2_API MSH* MSH_Create();
		LIBSWBF2_API void MSH_Delete(MSH* ptr);
		LIBSWBF2_API void MSH_ReadFromFile(MSH* ptr, const char* path);

		LIBSWBF2_API void AddLogMessage(const char* message, const ELogType logType);
	}
}