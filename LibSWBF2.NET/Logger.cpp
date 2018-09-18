#include "stdafx.h"
#include "Logger.h"
#include "ManagedObject.h"

namespace LibSWBF2NET::Logging
{
	Logger::Logger()
	{
		NativeLogger::GetInstance()->m_OnLogCallback = NativeLogCallback;
	}

	void Logger::Log(String^ Message, ELogType Level)
	{
		NativeLogger::GetInstance()->Log(MarshalString(Message), (LibSWBF2::Logging::ELogType)Level);
	}

	void Logger::NativeLogCallback(NativeEntry Entry)
	{
		if (OnLogCallback)
		{
			LoggerEntry log;
			log.m_Message = MarshalString(Entry.GetLogMessage());
			log.m_Level = (ELogType)Entry.GetLogLevel();
			OnLogCallback->Invoke(log);
		}
	}
}