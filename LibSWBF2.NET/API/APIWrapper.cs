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

        /* Vector3 
        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetVector3Elements(IntPtr ptr, out float x,
                                                    out float y, out float z);

        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetVector2Elements(IntPtr ptr, out float x,
                                                                 out float y);
        */

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

        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Level_GetTerrain(IntPtr level);


        //Terrain
        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern void Terrain_GetTexNames(IntPtr terrain, out uint numTextures, out IntPtr names);
        
        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetHeights(IntPtr terrain, out uint width, out uint height, out IntPtr heightData);
        
        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetVerts(IntPtr terrain, out uint numVertices, out IntPtr vertices);
        
        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetIndicies(IntPtr terrain, out uint numIndicies, out IntPtr indices);


        //Basic texture handling
        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Level_GetTextureData(IntPtr level, [MarshalAs(UnmanagedType.LPStr)] string texName, 
                                        out IntPtr imgData, out int width, out int height);


        // Model //
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string Model_GetName(IntPtr model);
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Model_GetSegments(IntPtr model, out IntPtr segmentArr, out uint segmentCount);
		
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Model_IsSkeletalMesh(IntPtr model);
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Model_GetSkeleton(IntPtr model, out IntPtr boneArr, out uint boneCount);
    

        // Segment //
        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Segment_GetIndexBuffer(IntPtr seg, out uint numIndicies, out IntPtr indexBuffer);

        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Segment_GetUVBuffer(IntPtr seg, out uint numUVCoords, out IntPtr indexBuffer);
        
        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Segment_GetVertexBuffer(IntPtr seg, out uint numVerts, out IntPtr vertsBuffer);

        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Segment_GetNormalBuffer(IntPtr seg, out uint numNormals, out IntPtr normalsBuffer);

        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]//TODO: fix memleak in elegant way
        public static extern string Segment_GetMaterialTexName(IntPtr seg);
    }
}
