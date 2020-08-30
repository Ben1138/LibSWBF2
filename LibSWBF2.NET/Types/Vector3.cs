using System;
using System.Runtime.InteropServices;

namespace LibSWBF2.Types
{
    public struct Vector3
    {
        public float X;
        public float Y;
        public float Z;

        public Vector3(IntPtr nativePtr)
        {
        	APIWrapper.Vector3_FromPtr(nativePtr, out X, out Y, out Z);
        }

        public override String ToString()
        {
            return "(" + X + ", " + Y + ", " + Z + ")";
        }
    }
}
