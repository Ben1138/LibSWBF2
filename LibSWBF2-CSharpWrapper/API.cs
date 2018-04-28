using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace LibSWBF2
{
    public enum ELogType
    {
        Info = 0,
        Warning = 1,
        Error = 2
    };

    static class API
    {
        [DllImport("LibSWBF2.dll")]
        public static extern IntPtr Color_Create(float r, float g, float b, float a);

        [DllImport("LibSWBF2.dll")]
        public static extern void Color_Delete(IntPtr color);


        [DllImport("LibSWBF2.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void AddLogMessage(string message, ELogType Type);

        [DllImport("LibSWBF2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void GetLogMessages(StringBuilder messages, int length, ELogType Type);
        public static string[] GetLogMessages(ELogType Type)
        {
            List<string> result = new List<string>();

            StringBuilder builder = new StringBuilder(4096);
            GetLogMessages(builder, builder.Capacity, Type);

            string currLine = "";

            for (int i = 0; i < builder.Length; i++)
            {
                if (builder[i] == '\n')
                {
                    result.Add(currLine);
                    currLine = "";
                }
                else
                {
                    //zero-terminated string
                    if ((byte)builder[i] == 0)
                        break;

                    currLine += builder[i];
                }
            }

            return result.ToArray();
        }

        [DllImport("LibSWBF2.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void GetLastLogMessages(StringBuilder messages, int length, ELogType Type);
        public static string[] GetLastLogMessages(ELogType Type)
        {
            List<string> result = new List<string>();

            StringBuilder builder = new StringBuilder(4096);
            GetLastLogMessages(builder, builder.Capacity, Type);

            string currLine = "";

            for (int i = 0; i < builder.Length; i++)
            {
                if (builder[i] == '\n')
                {
                    result.Add(currLine);
                    currLine = "";
                }
                else
                {
                    //zero-terminated string
                    if ((byte)builder[i] == 0)
                        break;

                    currLine += builder[i];
                }
            }

            return result.ToArray();
        }
    }
}
