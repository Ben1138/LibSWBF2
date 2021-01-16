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

    }
}
