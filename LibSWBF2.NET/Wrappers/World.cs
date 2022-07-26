using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using LibSWBF2.Logging;
using LibSWBF2.Utils;
using LibSWBF2.Types;

namespace LibSWBF2.Wrappers
{
    public sealed class Barrier : NativeWrapper
    {
        public Vector3 Position 
        { 
            get 
            {
                CheckValidity();
                return MemUtils.DerefUnmanaged<Vector3>(APIWrapper.Barrier_GetFieldPtr(NativeInstance, 0));
            }
        }

        public Vector4 Rotation 
        { 
            get
            {
                CheckValidity();
                return MemUtils.DerefUnmanaged<Vector4>(APIWrapper.Barrier_GetFieldPtr(NativeInstance, 1));
            } 
        }

        public uint Flag 
        { 
            get
            {
                CheckValidity();
                return MemUtils.DerefUnmanaged<uint>(APIWrapper.Barrier_GetFieldPtr(NativeInstance, 2));
            }
        }

        public string Name 
        { 
            get
            {
                CheckValidity();
                return Marshal.PtrToStringAnsi(APIWrapper.Barrier_GetFieldPtr(NativeInstance, 3));
            }
        }

        public Vector3 Size 
        { 
            get
            {
                CheckValidity();
                return MemUtils.DerefUnmanaged<Vector3>(APIWrapper.Barrier_GetFieldPtr(NativeInstance, 4));                
            }
        }

        public Barrier(){}
    }




    public sealed class HintNode : NativeWrapper
    {
        public Vector3 Position 
        { 
            get 
            {
                CheckValidity();
                return MemUtils.DerefUnmanaged<Vector3>(APIWrapper.HintNode_GetFieldPtr(NativeInstance, 0));
            }
        }

        public Vector4 Rotation 
        { 
            get
            {
                CheckValidity();
                return MemUtils.DerefUnmanaged<Vector4>(APIWrapper.HintNode_GetFieldPtr(NativeInstance, 1));
            } 
        }

        public uint Type 
        { 
            get
            {
                CheckValidity();
                return MemUtils.DerefUnmanaged<ushort>(APIWrapper.HintNode_GetFieldPtr(NativeInstance, 2));
            }
        }

        public string Name 
        { 
            get
            {
                CheckValidity();
                return Marshal.PtrToStringAnsi(APIWrapper.HintNode_GetFieldPtr(NativeInstance, 3));
            }
        }

        public void GetProperties(out uint[] properties, out string[] values)
        {
            CheckValidity();
            APIWrapper.HintNode_GetProperties(NativeInstance, out IntPtr props, out IntPtr vals, out int count);
            properties = MemUtils.IntPtrToArray<uint>(props, count);
            values = MemUtils.IntPtrToStringList(vals, count).ToArray();
        }

        public HintNode(){}
    }


    public sealed class Region : NativeWrapper
    {
        public Vector3 Position { get; private set; }
        public Vector3 Size { get; private set; }
        public Vector4 Rotation { get; private set; }
        public string  Name { get; private set; }
        public string  Type { get; private set; }
        public Region(){}

        internal override void SetPtr(IntPtr ptr)
        {
            base.SetPtr(ptr);
            if (APIWrapper.Region_FetchAllFields(ptr, out IntPtr sizePtr, out IntPtr posPtr, 
                                                out IntPtr rotPtr, out IntPtr namePtr, 
                                                out IntPtr typePtr))
            {
                Size = new Vector3(sizePtr);
                Position = new Vector3(posPtr);
                Rotation = new Vector4(rotPtr);
                Name = Marshal.PtrToStringAnsi(namePtr);
                Type = Marshal.PtrToStringAnsi(typePtr);
            }
        }

        public void GetProperties(out uint[] properties, out string[] values)
        {
            CheckValidity();
            APIWrapper.Region_GetProperties(NativeInstance, out IntPtr props, out IntPtr vals, out int count);
            properties = MemUtils.IntPtrToArray<uint>(props, count);
            values = MemUtils.IntPtrToStringList(vals, count).ToArray();
        }
    }



    public sealed class WorldAnimation : NativeWrapper
    {
        public string Name { get; private set; }
        public bool IsLooping { get; private set; }
        public bool IsTranslationLocal { get; private set; }
        public WorldAnimation(){}

        internal override void SetPtr(IntPtr ptr)
        {
            base.SetPtr(ptr);
            if (APIWrapper.WorldAnim_FetchAllFields(ptr, out bool loop, out bool localT, 
                                                    out IntPtr namePtr))
            {
                Name = Marshal.PtrToStringAnsi(namePtr);
                IsLooping = loop;
                IsTranslationLocal = localT;
            }
        }

        public WorldAnimationKey[] GetRotationKeys()
        {
            CheckValidity();
            APIWrapper.WorldAnim_GetAnimKeys(NativeInstance, out IntPtr keyBuff, out int numKeys, true);
            return MemUtils.IntPtrToArray<WorldAnimationKey>(keyBuff, numKeys);            
        }

        public WorldAnimationKey[] GetPositionKeys()
        {
            CheckValidity();
            APIWrapper.WorldAnim_GetAnimKeys(NativeInstance, out IntPtr keyBuff, out int numKeys, false);
            return MemUtils.IntPtrToArray<WorldAnimationKey>(keyBuff, numKeys);            
        }

        public override string ToString()
        {
            CheckValidity();
            return String.Format(
                "{0}: IsLooping? {1}, Has Local Translation? {2}, Has {3} Rotation Keys and {4} Position Keys",
                Name, IsLooping, IsTranslationLocal, GetRotationKeys().Length, GetPositionKeys().Length     
            );
        }
    }


    public sealed class WorldAnimationGroup : NativeWrapper
    {
        public string Name { get; private set; }
        public bool PlaysAtStart { get; private set; }
        public bool DisablesHierarchies { get; private set; }
        public WorldAnimationGroup(){}

        internal override void SetPtr(IntPtr ptr)
        {
            base.SetPtr(ptr);
            if (APIWrapper.WorldAnimGroup_FetchAllFields(ptr, out bool f1, out bool f2, 
                                                    out IntPtr namePtr))
            {
                Name = Marshal.PtrToStringAnsi(namePtr);
                PlaysAtStart = f1;
                DisablesHierarchies = f2;
            }
        }

        public List<Tuple<string, string>> GetAnimationInstancePairs()
        {
            CheckValidity();
            APIWrapper.WorldAnimGroup_GetAnimInstPairs(NativeInstance, out IntPtr animNamesPtr, out IntPtr instNamesPtr, out int numPairs);
            
            string[] animNames = MemUtils.IntPtrToStringList(animNamesPtr, numPairs);
            string[] instNames = MemUtils.IntPtrToStringList(instNamesPtr, numPairs);

            List<Tuple<string, string>> pairs = new List<Tuple<string, string>>();
            for (int i = 0; i < numPairs; i++)
            {
                pairs.Add(Tuple.Create(animNames[i], instNames[i]));
            }

            return pairs;          
        }

        public override string ToString()
        {
            CheckValidity();
            return String.Format(
                "{0}: PlaysAtStart? {1}, DisablesHierarchies? {2}, Has {3} Animation-Instance pairs",
                Name, PlaysAtStart, DisablesHierarchies, GetAnimationInstancePairs().Count     
            );
        }
    }


    public sealed class WorldAnimationHierarchy : NativeWrapper
    {
        public string RootName { get; private set; }
        public string[] ChildrenNames { get; private set; }
        public WorldAnimationHierarchy(){}

        internal override void SetPtr(IntPtr ptr)
        {
            base.SetPtr(ptr);
            if (APIWrapper.WorldAnimHier_FetchAllFields(ptr, out IntPtr namePtr, out IntPtr childrenBuf, out int numChildren))
            {
                RootName = Marshal.PtrToStringAnsi(namePtr);
                ChildrenNames = MemUtils.IntPtrToStringList(childrenBuf, numChildren);
            }
        }

        public override string ToString()
        {
            CheckValidity();
            return String.Format(
                "Animation Hierarchy with root {0} and {1} children",
                RootName, ChildrenNames.Length   
            );
        }
    }



    public sealed class World : NativeWrapper
    {
        static readonly Dictionary<Type, byte> SubWrapperTypeMapping = new Dictionary<Type, byte>()
        {
            { typeof(Instance),                0 },
            { typeof(Region),                  1 },
            { typeof(WorldAnimation),          2 },
            { typeof(WorldAnimationGroup),     3 },
            { typeof(WorldAnimationHierarchy), 4 },
            { typeof(Barrier),                 5 },
            { typeof(HintNode),                6 },
        };



        public string Name { get; private set; }
        public string SkydomeName { get; private set; }


        IntPtr terrainPtr;

        internal override void SetPtr(IntPtr worldPtr)
        {
            base.SetPtr(worldPtr);
            if (APIWrapper.World_FetchAllFields(worldPtr, out IntPtr nameOut, out IntPtr skyNameOut, out terrainPtr))
            {
                Name = Marshal.PtrToStringAnsi(nameOut);
                SkydomeName = Marshal.PtrToStringAnsi(skyNameOut);
            }
        }

        public Terrain GetTerrain()
        {
            CheckValidity();
            return RegisterChild(FromNative<Terrain>(terrainPtr));
        }


        T[] GetChildWrappers<T>() where T : NativeWrapper, new()
        {
            if (SubWrapperTypeMapping.TryGetValue(typeof(T), out byte typeID))
            {
                APIWrapper.World_GetChildrenList(NativeInstance, typeID, out IntPtr listPtr, out int listCount, out int elSize);
                return RegisterChildren(MemUtils.IntPtrToWrapperArray<T>(listPtr, listCount, elSize));
            }

            return null;
        } 


        public Instance[] GetInstances()
        {
            CheckValidity();
            return GetChildWrappers<Instance>();
        }

        public Region[] GetRegions()
        {
            CheckValidity();
            return GetChildWrappers<Region>();
        }

        public Barrier[] GetBarriers()
        {
            CheckValidity();
            return GetChildWrappers<Barrier>();
        }

        public HintNode[] GetHintNodes()
        {
            CheckValidity();
            return GetChildWrappers<HintNode>();
        }
    
        public WorldAnimation[] GetAnimations()
        {
            CheckValidity();
            return GetChildWrappers<WorldAnimation>();
        }

        public WorldAnimationGroup[] GetAnimationGroups()
        {
            CheckValidity();
            return GetChildWrappers<WorldAnimationGroup>();
        }  

        public WorldAnimationHierarchy[] GetAnimationHierarchies()
        {
            CheckValidity();
            return GetChildWrappers<WorldAnimationHierarchy>();
        }   
    }
}
