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
    public class Instance : NativeWrapper
    {
        public Instance(IntPtr modelPtr) : base(modelPtr){}

        public Instance() : base(IntPtr.Zero) {}


        public string Name
        {
            get 
            {
                if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
                return Marshal.PtrToStringAnsi( APIWrapper.Instance_GetName(NativeInstance) ); 
            }
        }

        public Vector4 GetRotation()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return new Vector4(APIWrapper.Instance_GetRotation(NativeInstance)); 
        }

        public Vector3 GetPosition()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return new Vector3(APIWrapper.Instance_GetPosition(NativeInstance));
        }

        public string GetEntityClassName()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return Marshal.PtrToStringAnsi(APIWrapper.Instance_GetEntityClassName(NativeInstance));   
        }
    }
}
