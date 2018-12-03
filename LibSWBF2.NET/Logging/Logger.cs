using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace LibSWBF2.Logging
{
    /// <summary>
    /// Call Logger.Initialize before use!
    /// </summary>
    public static class Logger
    {
        public static Action<LoggerEntry> OnLog;
        static bool bInit = false;

        static APIWrapper.LogCallback logCallback = new APIWrapper.LogCallback(ReceivedLog);
        static void ReceivedLog(IntPtr LoggerEntryPtr)
        {
            var nativeLoggerEntry = (LoggerEntry._NativeStruct)Marshal.PtrToStructure(LoggerEntryPtr, typeof(LoggerEntry._NativeStruct));
            var log = new LoggerEntry(
                Marshal.PtrToStringAuto(nativeLoggerEntry.m_Message),
                nativeLoggerEntry.m_Level,
                nativeLoggerEntry.m_Line,
                Marshal.PtrToStringAuto(nativeLoggerEntry.m_File)
            );

            OnLog?.Invoke(log);
        }

        public static void Initialize()
        {
            if (!bInit)
            {
                APIWrapper.LOG_SetCallbackMethod(logCallback);
                bInit = true;
            }
        }

        public static void SetLogLevel(ELogType level)
        {
            if (bInit)
            {
                APIWrapper.LOG_SetLogfileLevel(level);
            }
        }
    }
}
