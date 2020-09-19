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

        // Vectors 
        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Vector4_FromPtr(IntPtr ptr, out float x,
                                                    out float y, out float z,
                                                                 out float w);

        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Vector3_FromPtr(IntPtr ptr, out float x,
                                                    out float y, out float z);

        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
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

        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Level_GetTerrain(IntPtr level);

        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Level_GetWorlds(IntPtr level, out IntPtr worldArr, out uint modelCount);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Level_GetLights(IntPtr level, out IntPtr lightArr, out uint lightCount);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Level_GetLight(IntPtr level,  string lightName);

        //Basic texture handling
        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Level_GetTextureData(IntPtr level, [MarshalAs(UnmanagedType.LPStr)] string texName, 
                                                        out IntPtr imgData, out int width, out int height);
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Level_GetGlobalLighting(IntPtr level, out IntPtr topColor, out IntPtr bottomColor, 
                                                        out IntPtr light1Name, out IntPtr light2Name);        

        //Terrain

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetTexNames(IntPtr terrain, out uint numTextures, out IntPtr names);
        
        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetHeightMap(IntPtr terrain, out uint dim, out uint dimScale,
                                                    out IntPtr heightData);
        
        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetVerts(IntPtr terrain, out uint numVertices, out IntPtr vertices);
        
        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetIndicies(IntPtr terrain, out uint numIndicies, out IntPtr indices);

        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetBlendMap(IntPtr terrain, out uint edgeLength, out uint numLayers, out IntPtr data);

        [DllImport("SWBF2", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetHeightBounds(IntPtr terrain, out float floor, out float ceiling);

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
    

        // Segment //
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Segment_GetIndexBuffer(IntPtr seg, out uint numIndicies, out IntPtr indexBuffer);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Segment_GetUVBuffer(IntPtr seg, out uint numUVCoords, out IntPtr indexBuffer);
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Segment_GetVertexBuffer(IntPtr seg, out uint numVerts, out IntPtr vertsBuffer);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Segment_GetNormalBuffer(IntPtr seg, out uint numNormals, out IntPtr normalsBuffer);
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int Segment_GetTopology(IntPtr segment);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Segment_GetMaterialTexName(IntPtr seg);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Segment_GetMaterialFlags(IntPtr seg);


         // World //
         [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr World_GetName(IntPtr world);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void World_GetInstances(IntPtr world, out IntPtr instanceArr, out uint instCount);


        // Instance //
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Instance_GetName(IntPtr instance);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Instance_GetRotation(IntPtr instance);
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Instance_GetPosition(IntPtr instance);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Instance_GetModelName(IntPtr instance);


        // Light - All-getter method called on class construction w/valid ptr //
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Light_GetAllFields(
                                    IntPtr lightPtr,   out IntPtr rotPtr,
                                    out IntPtr posPtr, out uint lightType, 
                                    out IntPtr colPtr, out float range,
                                    out IntPtr conePtr
                                );
    }
}
