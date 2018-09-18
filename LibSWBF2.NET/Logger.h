#pragma once
#include "LoggerEntry.h"

using namespace System;

namespace LibSWBF2NET::Logging
{
	typedef LibSWBF2::Logging::Logger NativeLogger;
	typedef LibSWBF2::Logging::LoggerEntry NativeEntry;

	public ref class Logger abstract sealed
	{
	public:
		static Logger();

		static void Log(String^ Message, ELogType Level);
		static Action<LoggerEntry>^ OnLogCallback;
	private:
		static void NativeLogCallback(NativeEntry Entry);
	};
}