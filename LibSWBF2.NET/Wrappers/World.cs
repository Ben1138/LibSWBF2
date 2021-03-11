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

    public sealed class World : NativeWrapper
    {
        public string Name { get; private set; }
        public string SkydomeName { get; private set; }


        IntPtr terrainPtr;

        IntPtr instanceArray;
        int instanceCount, instanceIncrement;

        IntPtr regionArray;
        int regionCount, regionIncrement;


        internal override void SetPtr(IntPtr worldPtr)
        {
            base.SetPtr(worldPtr);
            if (APIWrapper.World_FetchAllFields(worldPtr, out IntPtr nameOut, out IntPtr skyNameOut,
                                        out instanceArray, out instanceCount, out instanceIncrement,
                                        out regionArray, out regionCount, out regionIncrement,
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
    }
}
