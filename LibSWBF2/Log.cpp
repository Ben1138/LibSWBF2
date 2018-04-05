#include <string>
#include <vector>
#include "LogEntry.h"
#include "Log.h"


namespace LibSWBF2
{
	namespace Log
	{
		int Log::lastIndex = 0;
		std::vector<LogEntry> Log::logEntrys;

		void Log::Add(const std::string &message, const LogType &level)
		{
			if (message.length() > 0)
				logEntrys.push_back(LogEntry(message, level));
		}

		std::string* Log::getAllLines(const LogType &level)
		{
			std::vector<std::string> resLines;

			for (unsigned int i = 0; i < logEntrys.size(); i++)
			{
				if (logEntrys[i].getLevel() >= level)
				{
					resLines.push_back(logEntrys[i].getMessage());
				}
			}

			return &resLines[0];
		}

		std::string* Log::getLastLines(const LogType &level)
		{
			std::vector<std::string> resLines;

			for (unsigned int i = lastIndex; i < logEntrys.size(); i++)
			{
				if (logEntrys[i].getLevel() >= level)
				{
					resLines.push_back(logEntrys[i].getMessage());
				}
			}

			//save position for next request
			lastIndex = logEntrys.size() - 1;

			return &resLines[0];
		}
	}
}
