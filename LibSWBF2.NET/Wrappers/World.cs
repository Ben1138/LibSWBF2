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
        public World(IntPtr worldPtr) : base(worldPtr){}

        public World() : base(IntPtr.Zero){}

        public string Name
        {
            get 
            {
                if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
                return Marshal.PtrToStringAnsi( APIWrapper.World_GetName(NativeInstance) ); 
            }
        }

        public Instance[] GetInstances()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.World_GetInstances(NativeInstance, out IntPtr instArr, out uint instCount);
            return MemUtils.IntPtrToWrapperArray<Instance>(instArr, (int) instCount);
        }


        public Terrain GetTerrain()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            IntPtr terPtr = APIWrapper.World_GetTerrain(NativeInstance);

            if (terPtr == IntPtr.Zero)
            {
                return null;
            }

            return new Terrain(terPtr);
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
            if (!APIWrapper.World_GetLights(NativeInstance, out IntPtr lightArr, out int count, out int inc))
            {
                return new Light[0];
            }

            return MemUtils.IntPtrToWrapperArray<Light>(lightArr, count, inc);
        }
    }
}
