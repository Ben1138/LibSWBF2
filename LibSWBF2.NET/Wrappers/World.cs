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
        internal Model(IntPtr worldPtr) : base(worldPtr)
        {

        }

        public string Name
        {
            get 
            {
                if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
                return APIWrapper._GetName(NativeInstance); 
            }
        }

        public Instance[] GetInstances()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Model_GetSegments(NativeInstance, out IntPtr instArr, out uint instCount);
            return ptrsToObjects<Instance>(instArr, instCount);
        }
    }
}
