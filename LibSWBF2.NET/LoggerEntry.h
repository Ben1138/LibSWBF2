#pragma once
#include "ManagedObject.h"

namespace LibSWBF2NET::Logging
{
	typedef LibSWBF2::Logging::LoggerEntry NativeEntry;

	public enum class ELogType : Byte
	{
		Info = 0,
		Warning = 1,
		Error = 2
	};

	public value struct LoggerEntry
	{
	internal:
		String^ m_Message;
		ELogType^ m_Level;

	public:
		property String^ Message
		{
			String^ get()
			{
				return m_Message;
			}
		}

		property ELogType^ Level
		{
			ELogType^ get()
			{
				return m_Level;
			}
		}

		String^ ToString() override
		{
			return "[" + m_Level + "] " + m_Message;
		}
	};
}