using System;
using System.Runtime.InteropServices;

namespace LibSWBF2
{
    internal static class APIWrapper
    {
        const string LIB_NAME = "LibSWBF2";

        // Logging //
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
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool LOG_GetNextLog(out IntPtr msg, out Logging.ELogType level, out uint line, out IntPtr file);

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
        public static extern IntPtr Level_GetAnimationBank(IntPtr level, string bankName);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Level_GetModel(IntPtr level, [MarshalAs(UnmanagedType.LPStr)] string modelName);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Level_GetTerrains(IntPtr level, out IntPtr terrainArr, out uint terrainCount);

        //Basic texture handling
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Level_GetTextureData(IntPtr level, [MarshalAs(UnmanagedType.LPStr)] string texName, 
                                                        out IntPtr imgData, out int width, out int height);


        //Terrain
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetTexNames(IntPtr terrain, out uint numTextures, out IntPtr names);
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetHeightMap(IntPtr terrain, out uint dim, out uint dimScale, out IntPtr heightData);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetBlendMap(IntPtr terrain, out uint edgeLength, out uint numLayers, out IntPtr data);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
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

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Model_GetCollisionMesh(IntPtr model);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Model_GetPrimitivesMasked(IntPtr NativeInstance, uint mask,
                                                            out int numPrims, out IntPtr ptr);


        // AnimationBank // 

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool AnimationBank_GetCurve(IntPtr setPtr, uint animCRC, uint boneCRC, uint comp, 
                                                        out IntPtr indicesBuffer, out IntPtr valuesBuffer, out int numKeys);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr AnimationBank_GetAnimationCRCs(IntPtr setPtr, out int numCRCs);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool AnimationBank_GetAnimationMetadata(IntPtr setPtr, uint animCRC,
                                                        out int numFrames, out int numBones);



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
