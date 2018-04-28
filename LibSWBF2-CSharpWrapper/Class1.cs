using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace LibSWBF2
{
    public enum ELogType {
        Info = 0,
        Warning = 1,
        Error = 2
    };

    public static class Class1
    {
        [DllImport("LibSWBF2.dll")]
        public static extern void AddLogMessage(string message, ELogType Type);
    }
}
