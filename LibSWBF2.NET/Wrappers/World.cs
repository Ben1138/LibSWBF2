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

        public string Name
        {
            get 
            {
                if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
                return APIWrapper.World_GetName(NativeInstance); 
            }
        }

        public Instance[] GetInstances()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.World_GetInstances(NativeInstance, out IntPtr instArr, out uint instCount);
            return ptrsToObjects<Instance>(instArr, (int) instCount);
        }
    }
}
