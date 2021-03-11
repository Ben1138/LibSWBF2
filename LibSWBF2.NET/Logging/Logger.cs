using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace LibSWBF2.Logging
{
    public static class Logger
    {
        static Queue<LoggerEntry> m_ManagedLogs = new Queue<LoggerEntry>();

        public static void SetLogLevel(ELogType level)
        {
            APIWrapper.LOG_SetLogfileLevel(level);
        }

        public static bool GetNextLog(out LoggerEntry next)
        {
            if (APIWrapper.LOG_GetNextLog(out IntPtr msg, out Logging.ELogType level, out uint line, out IntPtr file))
            {
                next = new LoggerEntry(
                    Marshal.PtrToStringAnsi(msg),
                    level,
                    line,
                    Marshal.PtrToStringAnsi(file)
                );
                return true;
            }
            if (m_ManagedLogs.Count > 0)
            {
                next = m_ManagedLogs.Dequeue();
                return true;
            }
            next = null;
            return false;
        }

        // For use in this CS wrapper
        internal static void Log(string msg, ELogType level, [CallerLineNumber] uint lineNumber = 0, [CallerFilePath] string file = "")
        {
            m_ManagedLogs.Enqueue(new LoggerEntry(msg, level, lineNumber, Path.GetFileName(file)));
        }

        internal static void LogInfo(string msg, [CallerLineNumber] uint lineNumber = 0, [CallerFilePath] string file = "") => Log(msg, ELogType.Info, lineNumber, file);
        internal static void LogWarn(string msg, [CallerLineNumber] uint lineNumber = 0, [CallerFilePath] string file = "") => Log(msg, ELogType.Warning, lineNumber, file);
        internal static void LogErr(string msg, [CallerLineNumber] uint lineNumber = 0, [CallerFilePath] string file = "") => Log(msg, ELogType.Error, lineNumber, file);
    }
}
