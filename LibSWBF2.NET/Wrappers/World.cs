using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using LibSWBF2.Logging;
using LibSWBF2.Utils;

namespace LibSWBF2.Wrappers
{
    public class World : NativeWrapper
    {
        public World(IntPtr worldPtr) : base(IntPtr.Zero){ SetPtr(worldPtr); }
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
            if (APIWrapper.World_FetchAllFields(worldPtr, out IntPtr nameOut, out IntPtr skyNameOut,
                                        out lightArray, out lightCount, out lightIncrement,
                                        out instanceArray, out instanceCount, out instanceIncrement,
                                        out terrainPtr))
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


        public Light[] GetLights()
        {            
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return MemUtils.IntPtrToWrapperArray<Light>(lightArray, lightCount, lightIncrement);
        }
    }
}
