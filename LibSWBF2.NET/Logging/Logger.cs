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

        static APIWrapper.LogCallback logCallback = new APIWrapper.LogCallback(ReceivedLog);
        static void ReceivedLog(IntPtr LoggerEntryPtr)
        {
            var nativeLoggerEntry = (LoggerEntry.NativeStruct)Marshal.PtrToStructure(LoggerEntryPtr, typeof(LoggerEntry.NativeStruct));
            var log = new LoggerEntry(
                Marshal.PtrToStringAnsi(nativeLoggerEntry.m_Message),
                (ELogType)nativeLoggerEntry.m_Level,
                nativeLoggerEntry.m_Line,
                Marshal.PtrToStringAuto(nativeLoggerEntry.m_File)
            );

            OnLog?.Invoke(log);
        }

        static Logger()
        {
            APIWrapper.LOG_SetCallbackMethod(logCallback);
        }

        public static void SetLogLevel(ELogType level)
        {
            APIWrapper.LOG_SetLogfileLevel(level);
        }
    }
}
