#pragma once
#include "Chunks\MSH\\MSH.h"
#include "Wrappers\Level.h"

namespace LibSWBF2::API
{
	// be carefull in the future!
	// there might be multiple chunks with the same Name
	using Chunks::MSH::MSH;
	using Chunks::MSH::MODL;
	using Chunks::MSH::STRP;
	using namespace Types;
	using Logging::LogCallback;
	using Logging::Logger;
	using Logging::ELogType;
	using Wrappers::Level;

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
		LIBSWBF2_API EModelPurpose MODL_GetPurpose(MODL* modl);

		// Wrappers
		LIBSWBF2_API Level* Level_FromFile(const char* path);
		LIBSWBF2_API void Level_Destroy(Level* level);

		LIBSWBF2_API const char* ENUM_TopologyToString(ETopology topology);
		LIBSWBF2_API const char* ENUM_MaterialFlagsToString(EMaterialFlags flags);
		LIBSWBF2_API const char* ENUM_EVBUFFlagsToString(EVBUFFlags flags);
	}
}