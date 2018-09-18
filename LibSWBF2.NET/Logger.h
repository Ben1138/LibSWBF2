#pragma once
using namespace System;

namespace LibSWBF2NET::Logging
{
	typedef LibSWBF2::Logging::Logger NativeLogger;
	using LibSWBF2::Logging::LoggerEntry;
	using LibSWBF2::Logging::ELogType;

	public ref class Logger abstract sealed
	{
	public:
		static void Log(String^ Message, ELogType Level);
		//static void OnLogCallback(LoggerEntry LogMessage);
	};
}