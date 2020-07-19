using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace LibSWBF2
{
    internal static class APIWrapper
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void LogCallback(IntPtr LoggerEntryPtr);


        // Logging //

        [DllImport("LibSWBF2")]
        public static extern void LOG_SetCallbackMethod(LogCallback Callback);

        [DllImport("LibSWBF2")]
        public static extern void LOG_SetLogfileLevel(Logging.ELogType LogfileLevel);


        // MSH //

        [DllImport("LibSWBF2")]
        public static extern IntPtr MSH_Create();

        [DllImport("LibSWBF2")]
        public static extern void MSH_Delete(IntPtr msh);

        [DllImport("LibSWBF2")]
        public static extern bool MSH_ReadFromFile(IntPtr msh, [MarshalAs(UnmanagedType.LPStr)] string path);

        [DllImport("LibSWBF2")]
        public static extern bool MSH_WriteToFile(IntPtr msh, [MarshalAs(UnmanagedType.LPStr)] string path);


        // MATL //

        [DllImport("LibSWBF2")]
        public static extern IntPtr MATL_GetMaterials(IntPtr matl);

        [DllImport("LibSWBF2")]
        public static extern ulong MATL_GetNumMaterials(IntPtr matl);
    }
}
