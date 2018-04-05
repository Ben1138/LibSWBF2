#pragma once
#include <string>

namespace LibSWBF2
{
	namespace Log
	{
		enum LogType
		{
			Info = 0,
			Warning = 1,
			Error = 2
		};

		class LogEntry
		{
		public:
			LogEntry(const std::string &message, const LogType &level);

			std::string getMessage();
			LogType getLevel();
		private:
			std::string message;
			LogType level;
		};
	}
}