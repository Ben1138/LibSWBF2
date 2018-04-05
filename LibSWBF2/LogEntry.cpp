#include <string>
#include "LogEntry.h"

namespace LibSWBF2 
{
	namespace Log 
	{
		LogEntry::LogEntry(const std::string &message, const LogType &level)
		{
			this->message = message;
			this->level = level;
		}

		std::string LogEntry::getMessage()
		{
			return message;
		}

		LogType LogEntry::getLevel()
		{
			return level;
		}
	}
}