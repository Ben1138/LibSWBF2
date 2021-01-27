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
        public static extern void Level_GetModels(IntPtr level, out IntPtr modelArr, out uint modelCount, out int inc);
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Level_GetEntityClasses(IntPtr level, out IntPtr classArr, out int classCount, out int inc);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Level_GetModel(IntPtr level, [MarshalAs(UnmanagedType.LPStr)] string modelName);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Level_GetTerrains(IntPtr level, out IntPtr terrainArr, out uint terrainCount);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Level_GetWorlds(IntPtr level, out IntPtr worldArr, out uint modelCount);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Level_GetLights(IntPtr level, out IntPtr lightArr, out uint lightCount);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Level_GetLight(IntPtr level, string lightName);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Level_GetAnimationBank(IntPtr level, string setName);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Level_GetEntityClass(IntPtr level, string name);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Level_GetTexture(IntPtr level, string texName);
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Level_GetGlobalLighting(IntPtr level, out IntPtr topColor, out IntPtr bottomColor, 
                                                        out IntPtr light1Name, out IntPtr light2Name);        


        //Terrain
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetTexNames(IntPtr terrain, out uint numTextures, out IntPtr names);
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetVerts(IntPtr terrain, out uint numVertices, out IntPtr vertices);
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetIndicies(IntPtr terrain, out uint numIndicies, out IntPtr indices);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetHeightMap(IntPtr terrain, out uint dim, out uint dimScale, out IntPtr heightData);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetBlendMap(IntPtr terrain, out uint edgeLength, out uint numLayers, out IntPtr data);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetHeightBounds(IntPtr terrain, out float floor, out float ceiling);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetVertexBuffer(IntPtr terPtr, out IntPtr buf, out int numVerts);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetNormalsBuffer(IntPtr terPtr, out IntPtr buf, out int numNormals);
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terrain_GetIndexBuffer(IntPtr terPtr, out IntPtr buf, out int numInds);



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
        public static extern bool Model_GetSkeleton(IntPtr model, out IntPtr boneArr, out uint boneCount, out int inc);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Model_HasNonTrivialHierarchy(IntPtr model);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Model_GetCollisionMesh(IntPtr model);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Model_GetPrimitivesMasked(IntPtr NativeInstance, uint mask,
                                                            out int numPrims, out IntPtr ptr);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Model_IsSkeletonBroken(IntPtr model);


        // Bone //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]    
        public static extern void Bone_FetchAllFields(IntPtr NativeInstance, out IntPtr namePtr, out IntPtr parentNamePtr, out IntPtr loc, out IntPtr rot);


        // Segment //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern uint Segment_GetVertexBufferLength(IntPtr seg);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Segment_GetIndexBuffer(IntPtr seg, out uint numIndicies, out IntPtr indexBuffer);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Segment_GetUVBuffer(IntPtr seg, out uint numUVCoords, out IntPtr indexBuffer);
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Segment_GetVertexBuffer(IntPtr seg, out uint numVerts, out IntPtr vertsBuffer);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Segment_GetNormalBuffer(IntPtr seg, out uint numNormals, out IntPtr normalsBuffer);
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Segment_GetVertexWeightsBuffer(IntPtr seg, out int numVWeights, out IntPtr vwsBuffer);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int Segment_GetTopology(IntPtr segment);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Segment_GetBone(IntPtr seg);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Segment_IsPretransformed(IntPtr seg);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Segment_GetMaterial(IntPtr segPtr);


         // World //
        
         [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr World_GetName(IntPtr world);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void World_GetInstances(IntPtr world, out IntPtr instanceArr, out uint instCount);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr World_GetTerrain(IntPtr world);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool World_GetLights(IntPtr world, out IntPtr lightArr, out int count, out int inc);


        // Instance //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Instance_GetName(IntPtr instance);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Instance_GetRotation(IntPtr instance);
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Instance_GetPosition(IntPtr instance);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Instance_GetEntityClassName(IntPtr instance);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Instance_GetOverriddenProperties(IntPtr ec, out IntPtr hashBuffer, out IntPtr valueBuffer, out int count);


        // Light //
        
        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Light_GetAllFields(
                                    IntPtr lightPtr,   out IntPtr rotPtr,
                                    out IntPtr posPtr, out uint lightType, 
                                    out IntPtr colPtr, out float range,
                                    out IntPtr conePtr
                                );


        // Texture //

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Texture_GetMetadata(IntPtr texture, out int width, 
                                                        out int height, out IntPtr namePtr);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Texture_GetData(IntPtr texture, out int width, out int height, out IntPtr bufferPtr);

        [DllImport(LIB_NAME, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool Texture_GetBytesRGBA(IntPtr texture, out IntPtr buffer);         


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

    }
}
