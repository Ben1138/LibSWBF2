#include "stdafx.h"
#include "API.h"

namespace LibSWBF2::API
{
	// Logging //
	LIBSWBF2_API void LOG_SetCallbackMethod(LogCallback* Callback)
	{
		if (!Callback)
		{
			LOG("[API] Given Callback function pointer was NULL!", ELogType::Warning);
			return;
		}

		Logger::SetLogCallback(*Callback);
	}


	// MSH //
	LIBSWBF2_API MSH* MSH_Create()
	{
		return MSH::Create();
	}

	LIBSWBF2_API void MSH_Delete(MSH* msh)
	{
		return MSH::Destroy(msh);
	}

	LIBSWBF2_API void MSH_ReadFromFile(MSH* msh, const char* path)
	{
		if (!msh)
		{
			LOG("[API] Given MSH pointer was NULL!", ELogType::Error);
			return;
		}

		msh->ReadFromFile(string(path));
	}

	LIBSWBF2_API void STRP_CalcPolygons(STRP* strp)
	{
		if (!strp)
		{
			LOG("[API] Given STRP pointer was NULL!", ELogType::Error);
			return;
		}

		strp->CalcPolygons();
	}

	LIBSWBF2_API EModelPurpose MODL_GetEstimatedPurpose(MODL* modl)
	{
		if (!modl)
		{
			LOG("[API] Given MODL pointer was NULL!", ELogType::Error);
			return EModelPurpose::Miscellaneous;
		}

		return modl->GetEstimatedPurpose();
	}

	LIBSWBF2_API CRCChecksum CalcLowerCRC(const char* str)
	{
		return LibSWBF2::CRC::CalcLowerCRC(str);
	}
}