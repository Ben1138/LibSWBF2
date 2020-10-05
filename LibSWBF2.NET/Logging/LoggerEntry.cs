using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace LibSWBF2.Logging
{
    public enum ELogType : byte
    {
        Info = 0,
        Warning = 1,
        Error = 2
    }

    public class LoggerEntry
    {
        public string Message { get; private set; }
        public ELogType Level { get; private set; }
        public uint Line { get; private set; }
        public string File { get; private set; }

        internal LoggerEntry(string msg, ELogType level, uint line, string file)
        {
            Message = msg;
            Level = level;
            Line = line;
            File = file;
        }

        public override string ToString()
        {
            if (Level == ELogType.Info)
            {
                return "[" + Level + "] " + Message;
            }
            else
            {
                return "[" + Level + "] " + Message + " - IN " + Line + " " + File;
            }
        }
    }
}
