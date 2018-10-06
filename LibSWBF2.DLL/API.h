#pragma once
#ifdef LIBSWBF2DLL_EXPORTS
#define LIBSWBF2_API __declspec(dllexport)
#else
#define LIBSWBF2_API __declspec(dllimport)
#endif

namespace LibSWBF2::API
{
	// be carefull in the futute!
	// there might be multiple chunks with the same Name
	using namespace Chunks::Mesh;
	using namespace Types;
	using namespace Logging;

	extern "C"
	{
		// Logging //
		LIBSWBF2_API void LOG_SetCallbackMethod(function<void(LoggerEntry)>* Callback);
		LIBSWBF2_API const char* LOG_LoggerEntryToString(LoggerEntry* Entry);
		LIBSWBF2_API void LOG_Log(const char* message, const ELogType logType);

		// MSH //
		LIBSWBF2_API MSH* MSH_Create();
		LIBSWBF2_API void MSH_Delete(MSH* msh);
		LIBSWBF2_API void MSH_ReadFromFile(MSH* msh, const char* path);
	}
}