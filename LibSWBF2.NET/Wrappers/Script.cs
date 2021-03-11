using System;
using System.Runtime.InteropServices;

namespace LibSWBF2.Wrappers
{
    public sealed class Script : NativeWrapper
    {
        public string Name 
        { 
            get 
            {
                CheckValidity();
                return Marshal.PtrToStringAnsi(APIWrapper.Script_GetName(NativeInstance)); 
            } 
        }

        public bool GetData(out IntPtr data, out uint size)
        {
            CheckValidity();
            return APIWrapper.Script_GetData(NativeInstance, out data, out size);
        }
    }
}
