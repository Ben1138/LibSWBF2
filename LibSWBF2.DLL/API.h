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

	// Provide mangling free functions to keep
	// compatibility to compilers other than VS2017
	extern "C"
	{
		// Logging //
		LIBSWBF2_API void LOG_SetCallbackMethod(LogCallback* Callback);

		// MSH //
		LIBSWBF2_API MSH* MSH_Create();
		LIBSWBF2_API void MSH_Delete(MSH* msh);
		LIBSWBF2_API void MSH_ReadFromFile(MSH* msh, const char* path);
		LIBSWBF2_API void STRP_CalcPolygons(STRP* strp);
		LIBSWBF2_API EModelPurpose MODL_GetEstimatedPurpose(MODL* modl);

		LIBSWBF2_API uint32_t CalcLowerCRC(const char* str);
	}
}