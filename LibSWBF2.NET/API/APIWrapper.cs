using System;
using System.Runtime.InteropServices;

namespace LibSWBF2
{
    internal static class APIWrapper
    {
#if WIN32
        const string LIB_NAME = "LibSWBF2";
#else
        const string LIB_NAME = "SWBF2";
#endif

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void LogCallback(IntPtr LoggerEntryPtr);


        // Logging //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void LOG_SetCallbackMethod(LogCallback Callback);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void LOG_SetLogfileLevel(Logging.ELogType LogfileLevel);


        // Container //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Container_Initialize();  

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern uint Container_AddLevel(IntPtr container, [MarshalAs(UnmanagedType.LPStr)] string path);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern float Container_GetProgress(IntPtr container, uint handle);  

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Container_GetLevel(IntPtr container, uint handle); 
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Container_GetWrapper(IntPtr container, uint type, [MarshalAs(UnmanagedType.LPStr)] string name);        

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Container_LoadLevels(IntPtr container);

        // Level //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Level_FromFile([MarshalAs(UnmanagedType.LPStr)] string path);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Level_Destroy(IntPtr level);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Level_IsWorldLevel(IntPtr level);
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Level_GetModels(IntPtr level, out IntPtr modelArr, out uint modelCount);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Level_GetModel(IntPtr level, [MarshalAs(UnmanagedType.LPStr)] string modelName);


        // Model //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Model_GetName(IntPtr model);
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Model_GetSegments(IntPtr model, out IntPtr segmentArr, out uint segmentCount);
		
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Model_IsSkeletalMesh(IntPtr model);
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Model_GetSkeleton(IntPtr model, out IntPtr boneArr, out uint boneCount);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Model_GetCollisionMesh(IntPtr model);



        // CollisionMesh //
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void CollisionMesh_GetIndexBuffer(IntPtr collMesh, out uint count, out IntPtr buffer);
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void CollisionMesh_GetVertexBuffer(IntPtr collMesh, out uint count, out IntPtr buffer);

    }
}
