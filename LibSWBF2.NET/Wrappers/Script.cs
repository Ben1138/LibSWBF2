using System;
using System.Runtime.InteropServices;

namespace LibSWBF2.Wrappers
{
    public class Script : NativeWrapper
    {
        internal Script(IntPtr scriptPtr) : base(scriptPtr) { }

        public Script() : base(IntPtr.Zero) { }

        public string Name 
        { 
            get 
            {
                if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
                return Marshal.PtrToStringAnsi(APIWrapper.Script_GetName(NativeInstance)); 
            } 
        }

        public bool GetData(out IntPtr data, out uint size)
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return APIWrapper.Script_GetData(NativeInstance, out data, out size);
        }
    }
}
