using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace LibSWBF2.Logging
{
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
                Marshal.PtrToStringAnsi(nativeLoggerEntry.m_File)
            );

            OnLog?.Invoke(log);
        }

        static Logger()
        {
            APIWrapper.LOG_SetCallbackMethod(logCallback);
        }

        // For use in this CS wrapper
        internal static void Log(string msg, ELogType level, [CallerLineNumber] ulong lineNumber = 0, [CallerFilePath] string file = "")
        {
            OnLog?.Invoke(new LoggerEntry(msg, level, lineNumber, Path.GetFileName(file)));
        }

        public static void SetLogLevel(ELogType level)
        {
            APIWrapper.LOG_SetLogfileLevel(level);
        }
    }
}
