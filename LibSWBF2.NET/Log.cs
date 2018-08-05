using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LibSWBF2
{
    public enum ELogType
    {
        Info = 0,
        Warning = 1,
        Error = 2
    };

    public static class Log
    {
        public static void Add(string message, ELogType level)
        {
            API.AddLogMessage(message, level);
        }

        public static string[] GetAll(ELogType level)
        {
            return API.GetLogMessages(level);
        }

        public static string[] GetLatest(ELogType level)
        {
            return API.GetLastLogMessages(level);
        }
    }
}
