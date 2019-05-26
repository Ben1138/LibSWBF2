#pragma once
#ifdef LIBSWBF2DLL_EXPORTS
#define LIBSWBF2_API __declspec(dllexport)
#else
#define LIBSWBF2_API __declspec(dllimport)
#endif

namespace LibSWBF2::API
{
	// be carefull in the future!
	// there might be multiple chunks with the same Name
	using namespace Chunks::Mesh;
	using namespace Types;
	using namespace Logging;

	// Provide mangling free C-functions to be
	// accessible from C# wrapper
	extern "C"
	{
		// Logging //
		LIBSWBF2_API void LOG_SetCallbackMethod(const LogCallback Callback);
		LIBSWBF2_API void LOG_SetLogfileLevel(ELogType LogfileLevel);

		// MSH //
		LIBSWBF2_API MSH* MSH_Create();
		LIBSWBF2_API bool MSH_Delete(MSH* msh);
		LIBSWBF2_API bool MSH_ReadFromFile(MSH* msh, const char* path);
		LIBSWBF2_API bool MSH_WriteToFile(MSH* msh, const char* path);
		LIBSWBF2_API void STRP_CalcPolygons(STRP* strp);
		LIBSWBF2_API EModelPurpose MODL_GetEstimatedPurpose(MODL* modl);

		LIBSWBF2_API CRCChecksum CalcLowerCRC(const char* str);
	}
}