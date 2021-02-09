using System;
using System.Runtime.InteropServices;

namespace LibSWBF2
{
    internal static class APIWrapper
    {
        const string LIB_NAME = "LibSWBF2";

        // Memory //
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static unsafe extern void Memory_Blit(void *dest, void *src, int numBytes);


        // Logging //

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void LogCallback(IntPtr LoggerEntryPtr);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool LOG_GetNextLog(out IntPtr msg, out Logging.ELogType level, out uint line, out IntPtr file);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void LOG_SetLogfileLevel(Logging.ELogType LogfileLevel);


        // Container //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Container_Initialize();  

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern uint Container_AddLevel(IntPtr container, [MarshalAs(UnmanagedType.LPStr)] string path);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern uint Container_AddLevelFiltered(IntPtr container, [MarshalAs(UnmanagedType.LPStr)] string path, IntPtr[] subLVLs, uint subLVLCount);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern uint Container_AddSoundBank(IntPtr container, [MarshalAs(UnmanagedType.LPStr)] string path);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Container_FreeAll(IntPtr container, [MarshalAs(UnmanagedType.U1)] bool force);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern float Container_GetProgress(IntPtr container, uint handle);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern float Container_GetOverallProgress(IntPtr container);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Container_GetLevel(IntPtr container, uint handle); 
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Container_GetWrapper(IntPtr container, uint type, [MarshalAs(UnmanagedType.LPStr)] string name);        

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Container_GetConfig(IntPtr container, uint type, uint nameHash);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Container_LoadLevels(IntPtr container);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Container_IsDone(IntPtr container);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Container_Delete(IntPtr container);


        // Level //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Level_FromFile([MarshalAs(UnmanagedType.LPStr)] string path);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Level_Destroy(IntPtr level);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Level_IsWorldLevel(IntPtr level);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Level_GetName(IntPtr level);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Level_GetPath(IntPtr level);
        

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Level_GetConfig(IntPtr level, uint cfgType, uint hash);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Level_GetConfigs(IntPtr level, uint cfgType, out int numConfigs);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Level_GetWrapper(IntPtr level, uint type, string name);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Level_GetWrappers(IntPtr level, uint type, out uint num, out uint inc);

        //Terrain

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Terrain_FetchSimpleFields(IntPtr ter, out int numTexes, out IntPtr texNames,
                                                            out float heightUpper, out float heightLower, 
                                                            out uint numVerts, out IntPtr vBuf,
                                                            out uint numNormals, out IntPtr nBuf,
                                                            out uint numUVs, out IntPtr uvBuf);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetIndicies(IntPtr terrain, out uint numIndicies, out IntPtr indices);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetHeightMap(IntPtr terrain, out uint dim, out uint dimScale, out IntPtr heightData);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetBlendMap(IntPtr terrain, out uint edgeLength, out uint numLayers, out IntPtr data);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetIndexBuffer(IntPtr terPtr, out IntPtr buf, out uint numInds);



        // Model //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Model_FetchSimpleFields(IntPtr model, out IntPtr name,
                                                            [MarshalAs(UnmanagedType.U1)] out bool skinned,
                                                            [MarshalAs(UnmanagedType.U1)] out bool skelBroken,
                                                            out IntPtr segArr, out int segCount, out int segInc,
                                                            out IntPtr boneArr, out int boneCount, out int boneInc,
                                                            out IntPtr collMeshPtr);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Model_GetPrimitivesMasked(IntPtr NativeInstance, uint mask,
                                                            out int numPrims, out IntPtr ptr);


        // Bone //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]    
        public static extern void Bone_FetchAllFields(IntPtr NativeInstance, out IntPtr namePtr, out IntPtr parentNamePtr, out IntPtr loc, out IntPtr rot);


        // Segment //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Segment_FetchAllFields(IntPtr seg, [MarshalAs(UnmanagedType.U1)] out bool pretx, out IntPtr boneName,
                                                        out uint numVerts, out IntPtr pBuf, out IntPtr nBuf, out IntPtr uvBuf,
                                                        out uint numVWs, out IntPtr vwBuf,
                                                        out int topo, out uint numInds, out IntPtr iBuf,
                                                        out IntPtr mat);

         // World //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool World_FetchAllFields(IntPtr world, out IntPtr nameOut, out IntPtr skyNameOut,
                                        out IntPtr instanceArr, out int instCount, out int instInc,
                                        out IntPtr regionArr, out int regCount, out int regInc,
                                        out IntPtr terrPtr);
        // Region // 

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Region_FetchAllFields(IntPtr reg, out IntPtr size, 
                                                        out IntPtr pos, out IntPtr rot,
                                                        out IntPtr name, out IntPtr type);       
        

        // Script //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Script_GetName(IntPtr script);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Script_GetData(IntPtr script, out IntPtr data, out uint size);

        // Instance //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Instance_FetchSimpleFields(IntPtr inst, out IntPtr name, out IntPtr rot, out IntPtr pos, out IntPtr ecName);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Instance_GetOverriddenProperties(IntPtr ec, out IntPtr hashBuffer, out IntPtr valueBuffer, out int count);


        // Light //
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Light_GetAllFields(IntPtr lightPtr,   out IntPtr rotPtr,
                                                    out IntPtr posPtr, out uint lightType, 
                                                    out IntPtr colPtr, out float range,
                                                    out IntPtr conePtr);


        // Texture //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Texture_FetchAllFields(IntPtr tex, out int width, out int height, out IntPtr bufOut, out IntPtr nameOut);      


        // CollisionMesh //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool CollisionMesh_FetchAllFields(IntPtr cmPtr, out uint iCount, out IntPtr iBuf,
                                                                out uint vCount, out IntPtr vBuf, out uint maskFlags);


        // CollisionPrimitive //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void CollisionPrimitive_FetchAllFields(IntPtr nativePtr,
                                                    out float f1, out float f2, out float f3,
                                                    out IntPtr name, out IntPtr parentName,
                                                    out uint maskFlags, out uint primitiveType,
                                                    out IntPtr pos, out IntPtr rot);
   

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


        // EntityClass //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr EntityClass_GetProperty(IntPtr ecPtr, string propName);  

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr EntityClass_GetBaseName(IntPtr ecPtr);    

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr EntityClass_GetName(IntPtr ecPtr); 

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool EntityClass_GetOverriddenProperties(IntPtr ec, out IntPtr hashBuffer, out IntPtr valueBuffer, out int count);


        // Material //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]        
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Material_FetchAllFields(IntPtr matPtr, out IntPtr specular,
                                out IntPtr diffuse, out IntPtr texNames, out int numTexes,
                                out IntPtr attachedLightName, out uint matFlags, out uint specExp);





        // Config //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]        
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Config_FetchSimpleFields(IntPtr cfg, out uint name);


        // Config / Scope // 

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]        
        public static extern IntPtr ConfigScope_GetFields(IntPtr ptr, uint hash, bool isScope, out uint count);


        // Field //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]        
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Field_FetchAllFields(IntPtr cfg, out IntPtr scop, out uint hash);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]        
        public static extern float  Field_GetFloat(IntPtr cfg);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]        
        public static extern IntPtr Field_GetVec2(IntPtr cfg); 

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]        
        public static extern IntPtr Field_GetVec3(IntPtr cfg); 

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]        
        public static extern IntPtr Field_GetVec4(IntPtr cfg); 

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]        
        public static extern IntPtr Field_GetString(IntPtr cfg); 
        
    }
}
