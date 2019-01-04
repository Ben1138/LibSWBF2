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
        [StructLayout(LayoutKind.Sequential)]
        internal struct NativeStruct
        {
            public IntPtr m_Message;
            public byte m_Level;
            public ulong m_Line;
            public IntPtr m_File;
        }

        public string Message { get; private set; }
        public ELogType Level { get; private set; }
        public ulong Line { get; private set; }
        public string File { get; private set; }

        internal LoggerEntry(string msg, ELogType level, ulong line, string file)
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
