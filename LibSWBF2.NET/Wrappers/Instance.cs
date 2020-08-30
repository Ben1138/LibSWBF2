using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using LibSWBF2.Logging;

namespace LibSWBF2.Wrappers
{
    public class Instance : NativeWrapper
    {
        internal Instance(IntPtr modelPtr) : base(modelPtr){}

        public string Name
        {
            get 
            {
                if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
                return APIWrapper.Instace_GetName(NativeInstance); 
            }
        }

        public Vector4 GetRotation()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Instance_GetRotation(NativeInstance, out float x, out float y, out float z, out float w); 
            return new Vector4(x,y,z,w);   
        }

        public Vector3 GetPosition()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            APIWrapper.Instance_GetPosition(NativeInstance, out float x, out float y, out float z);
            return new Vector3(x,y,z);
        }
    }
}
