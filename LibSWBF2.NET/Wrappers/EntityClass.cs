using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using LibSWBF2.Logging;
using LibSWBF2.Types;
using LibSWBF2.Utils;

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

        public string GetBaseName()
        {
            if (!IsValid()) return "";// throw new Exception("Underlying native class is destroyed!");
            return Marshal.PtrToStringAnsi(APIWrapper.EntityClass_GetBaseName(NativeInstance));               
        }

        public bool GetOverriddenProperties(out uint[] properties, out string[] values)
        {
            bool status = APIWrapper.EntityClass_GetOverriddenProperties(NativeInstance, out IntPtr props, out IntPtr vals, out int count);

            if (status)
            {
                properties = MemUtils.IntPtrToArray<uint>(props, count);
                values = MemUtils.IntPtrToStringList(vals, count).ToArray();
            }
            else 
            {
                properties = new uint[0];
                values = new string[0];
            }

            return status;
        }
    }
}
