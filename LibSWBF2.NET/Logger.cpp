#include "stdafx.h"
#include "Logger.h"
#include "ManagedObject.h"

namespace LibSWBF2NET::Logging
{
	void Logger::Log(String^ Message, ELogType Level)
	{
		NativeLogger::GetInstance()->Log(MarshalString(Message), Level);
	}
}