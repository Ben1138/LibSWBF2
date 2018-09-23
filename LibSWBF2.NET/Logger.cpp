#include "stdafx.h"
#include "Logger.h"
#include "ManagedObject.h"

namespace LibSWBF2NET::Logging
{
	Logger::Logger()
	{
		NativeLogger::GetInstance()->m_OnLogCallback = NativeLogCallback;
	}

	void Logger::Log(String^ Message, ELogType Level, UINT64 Line, String^ File)
	{
		NativeLogger::GetInstance()->Log(MarshalString(Message), (LibSWBF2::Logging::ELogType)Level, (const unsigned long)Line, MarshalString(File).c_str());
	}

	void Logger::NativeLogCallback(NativeEntry Entry)
	{
		if (OnLogCallback)
		{
			LoggerEntry log;
			log.m_Message = MarshalString(Entry.GetLogMessage());
			log.m_Level = (ELogType)Entry.GetLogLevel();
			log.m_Line = Entry.GetLineNumber();
			log.m_File = MarshalString(Entry.GetFileName());
			OnLogCallback->Invoke(log);
		}
	}
}