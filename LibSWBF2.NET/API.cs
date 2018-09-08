using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace LibSWBF2
{
    internal static unsafe class API
    {
        const int MARSH_STRING_BUFFER_SIZE = 4096;


        [DllImport("LibSWBF2.dll")]
        public static extern MSH._MSH* MSH_LoadFromFile(string path);

        [DllImport("LibSWBF2.dll")]
        public static extern MSH._MSH* MSH_Create();

        [DllImport("LibSWBF2.dll")]
        public static extern void MSH_Delete(MSH._MSH* color);



        [DllImport("LibSWBF2.dll")]
        public static extern void AddLogMessage(string message, ELogType Type);

        [DllImport("LibSWBF2.dll")]
        static extern void GetLogMessages(StringBuilder messages, int length, ELogType Type);
        public static string[] GetLogMessages(ELogType Type)
        {
            List<string> result = new List<string>();

            StringBuilder builder = new StringBuilder(MARSH_STRING_BUFFER_SIZE);
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

        [DllImport("LibSWBF2.dll")]
        static extern void GetLastLogMessages(StringBuilder messages, int length, ELogType Type);
        public static string[] GetLastLogMessages(ELogType Type)
        {
            List<string> result = new List<string>();

            StringBuilder builder = new StringBuilder(MARSH_STRING_BUFFER_SIZE);
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
