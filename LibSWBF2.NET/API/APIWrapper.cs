﻿using System;
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



        // Vectors 
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Vector4_FromPtr(IntPtr ptr, out float x,
                                                    out float y, out float z,
                                                                 out float w);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Vector3_FromPtr(IntPtr ptr, out float x,
                                                    out float y, out float z);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Vector2_FromPtr(IntPtr ptr, out float x,
                                                              out float y);



        // Logging //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void LOG_SetCallbackMethod(LogCallback Callback);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void LOG_SetLogfileLevel(Logging.ELogType LogfileLevel);


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

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Model_GetPrimitivesMasked(IntPtr NativeInstance, uint mask,
                                                            out int numPrims, out IntPtr ptr);



        // CollisionMesh //
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void CollisionMesh_GetIndexBuffer(IntPtr collMesh, out uint count, out IntPtr buffer);
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void CollisionMesh_GetVertexBuffer(IntPtr collMesh, out uint count, out IntPtr buffer);



        // CollisionPrimitive //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void CollisionPrimitive_FetchAllFields(IntPtr nativePtr,
                                                    out float f1, out float f2, out float f3,
                                                    out IntPtr name, out IntPtr parentName,
                                                    out uint maskFlags, out uint primitiveType,
                                                    out IntPtr pos, out IntPtr rot);

    }
}
