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

		
		void Log::add(const std::string &message, const LogType &level)
		{
			if (message.length() > 0)
				logEntrys.push_back(LogEntry(message, level));
		}

		void Log::getAllLines(const LogType &level, char* buffer)
		{
			std::string resLines;

			for (unsigned int i = 0; i < logEntrys.size(); i++)
			{
				if (logEntrys[i].getLevel() >= level)
				{
					resLines += logEntrys[i].getMessage() + "\n";
				}
			}

			strcpy_s(buffer, resLines.length() + 1, resLines.c_str());
		}

		void Log::getLastLines(const LogType &level, char* buffer)
		{
			std::string resLines;

			for (unsigned int i = lastIndex; i < logEntrys.size(); i++)
			{
				if (logEntrys[i].getLevel() >= level)
				{
					resLines += logEntrys[i].getMessage() + "\n";
				}
			}

			//save position for next request
			lastIndex = logEntrys.size() - 1;

			strcpy_s(buffer, resLines.length() + 1, resLines.c_str());
		}
	}
}
