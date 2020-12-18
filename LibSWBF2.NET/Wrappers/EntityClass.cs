using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using LibSWBF2.Logging;
using LibSWBF2.Types;

namespace LibSWBF2.Wrappers
{
    public class EntityClass : NativeWrapper
    {
        public EntityClass(IntPtr ecPtr) : base(ecPtr){}

        public EntityClass() : base(IntPtr.Zero) {}


        public string GetProperty(string propName)
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return Marshal.PtrToStringAnsi(APIWrapper.EntityClass_GetProperty(NativeInstance, propName));   
        }
    }
}
