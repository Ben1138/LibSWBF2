#include "stdafx.h"
#include "API.h"

namespace LibSWBF2::API
{
	LIBSWBF2_API MSH* MSH_Create()
	{
		return new MSH();
	}

	LIBSWBF2_API void MSH_Delete(MSH* ptr)
	{
		delete ptr;
	}

	LIBSWBF2_API void MSH_ReadFromFile(MSH* ptr, const char* path)
	{
		if (ptr == nullptr)
		{
			LOG("[API] Given MSH pointer was NULL!", ELogType::Error);
			return;
		}

		ptr->ReadFromFile(string(path));
	}

	// Logging //
	LIBSWBF2_API void AddLogMessage(const char* message, const ELogType logType)
	{
		LOG("[API] " + string(message), logType);
	}
}