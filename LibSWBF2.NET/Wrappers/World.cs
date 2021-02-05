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
    public class Region : NativeWrapper
    {
        //public Region(IntPtr RegionPtr) : base(RegionPtr){}
        public Region() : base(IntPtr.Zero){} 

        internal override void SetPtr(IntPtr ptr)
        {
            APIWrapper.Region_FetchAllFields(ptr, out IntPtr sizePtr, out IntPtr posPtr, out IntPtr rotPtr, out IntPtr namePtr, out IntPtr typePtr);
            size = new Vector3(sizePtr);
            position = new Vector3(posPtr);
            rotation = new Vector4(rotPtr);
            name = Marshal.PtrToStringAnsi(namePtr);
            type = Marshal.PtrToStringAnsi(typePtr);
        }

        public Vector3 position, size;
        public Vector4 rotation;
        public string name, type;
    }





    public class World : NativeWrapper
    {
        public World(IntPtr worldPtr) : base(worldPtr){ SetPtr(worldPtr); }
        public World() : base(IntPtr.Zero){}

        public string name = "";
        public string skydomeName = "";

        private IntPtr terrainPtr;

        private IntPtr lightArray;
        private int lightCount, lightIncrement;

        private IntPtr instanceArray;
        private int instanceCount, instanceIncrement;


        internal override void SetPtr(IntPtr worldPtr)
        {
            NativeInstance = IntPtr.Zero;
            bool status = APIWrapper.World_FetchAllFields(worldPtr, out IntPtr nameOut, out IntPtr skyNameOut,
                                        out lightArray, out lightCount, out lightIncrement,
                                        out instanceArray, out instanceCount, out instanceIncrement,
                                        out terrainPtr);

            if (status)
            {
                NativeInstance = worldPtr;
                name = Marshal.PtrToStringAnsi(nameOut);
                skydomeName = Marshal.PtrToStringAnsi(skyNameOut);
            }
        }


        public Instance[] GetInstances()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return MemUtils.IntPtrToWrapperArray<Instance>(instanceArray, instanceCount, instanceIncrement);
        }


        public Terrain GetTerrain()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            if (terrainPtr == IntPtr.Zero) return null;
            return new Terrain(terrainPtr);
        }


        public Region[] GetRegions()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.World_GetRegions(NativeInstance, out IntPtr regArr, out uint regCount);
            return MemUtils.IntPtrToWrapperArray<Region>(regArr, (int) regCount);
        }


        public Light[] GetLights()
        {            
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return MemUtils.IntPtrToWrapperArray<Light>(lightArray, lightCount, lightIncrement);
        }
    }
}
