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
    public sealed class Region : NativeWrapper
    {
        public Vector3 Position { get; private set; }
        public Vector3 Size { get; private set; }
        public Vector4 Rotation { get; private set; }
        public string  Name { get; private set; }
        public string  Type { get; private set; }

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
    }



    public sealed class WorldAnimation : NativeWrapper
    {
        public string Name { get; private set; }
        public bool IsLooping { get; private set; }
        public bool IsTranslationLocal { get; private set; }

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
        public string Name { get; private set; }
        public string SkydomeName { get; private set; }


        IntPtr terrainPtr;

        IntPtr instanceArray;
        int instanceCount, instanceIncrement;

        IntPtr regionArray;
        int regionCount, regionIncrement;

        IntPtr animArray;
        int animCount, animIncrement;
        
        IntPtr animGroupArray;
        int animGroupCount, animGroupIncrement;

        IntPtr animHierArray;
        int animHierCount, animHierIncrement;

        internal override void SetPtr(IntPtr worldPtr)
        {
            base.SetPtr(worldPtr);
            if (APIWrapper.World_FetchAllFields(worldPtr, out IntPtr nameOut, out IntPtr skyNameOut,
                                        out instanceArray, out instanceCount, out instanceIncrement,
                                        out regionArray, out regionCount, out regionIncrement,
                                        out animArray, out animCount, out animIncrement,
                                        out animGroupArray, out animGroupCount, out animGroupIncrement,
                                        out animHierArray, out animHierCount, out animHierIncrement,
                                        out terrainPtr))
            {
                Name = Marshal.PtrToStringAnsi(nameOut);
                SkydomeName = Marshal.PtrToStringAnsi(skyNameOut);
            }
        }


        public Instance[] GetInstances()
        {
            CheckValidity();
            return RegisterChildren(MemUtils.IntPtrToWrapperArray<Instance>(instanceArray, instanceCount, instanceIncrement));
        }

        public Terrain GetTerrain()
        {
            CheckValidity();
            return RegisterChild(FromNative<Terrain>(terrainPtr));
        }

        public Region[] GetRegions()
        {
            CheckValidity();
            return RegisterChildren(MemUtils.IntPtrToWrapperArray<Region>(regionArray, regionCount, regionIncrement));
        }
    
        public WorldAnimation[] GetAnimations()
        {
            CheckValidity();
            return RegisterChildren(MemUtils.IntPtrToWrapperArray<WorldAnimation>(animArray, animCount, animIncrement));
        }

        public WorldAnimationGroup[] GetAnimationGroups()
        {
            CheckValidity();
            return RegisterChildren(MemUtils.IntPtrToWrapperArray<WorldAnimationGroup>(animGroupArray, animGroupCount, animGroupIncrement));
        }  

        public WorldAnimationHierarchy[] GetAnimationHierarchies()
        {
            CheckValidity();
            return RegisterChildren(MemUtils.IntPtrToWrapperArray<WorldAnimationHierarchy>(animHierArray, animHierCount, animHierIncrement));
        }   
    }
}
