#pragma once
#include "ManagedObject.h"

namespace LibSWBF2NET::Logging
{
	typedef LibSWBF2::Logging::LoggerEntry NativeEntry;

	public enum class ELogType : Byte
	{
		ENUM_LOGTYPE
	};

	public value struct LoggerEntry
	{
	internal:
		String^ m_Message;
		ELogType m_Level;
		UINT64 m_Line;
		String^ m_File;

	public:
		property String^ Message
		{
			String^ get()
			{
				return m_Message;
			}
		}

		property ELogType Level
		{
			ELogType get()
			{
				return m_Level;
			}
		}

		property UINT64 LineNumber
		{
			UINT64 get()
			{
				return m_Line;
			}
		}

		property String^ FileName
		{
			String^ get()
			{
				return m_File;
			}
		}

		String^ ToString() override
		{
			if (m_Level == ELogType::Info)
			{
				return "[" + m_Level.ToString() + "] " + m_Message;
			}
			else
			{
				return "[" + m_Level.ToString() + "] " + m_Message + " - IN " + m_Line + " " + m_File;
			}
		}
	};
}