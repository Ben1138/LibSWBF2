using System;
using System.Runtime.InteropServices;

namespace LibSWBF2.Types
{
    public struct Vector4
    {
        public float X;
        public float Y;
        public float Z;
        public float W;

        public Vector4(IntPtr nativePtr)
        {
        	APIWrapper.Vector4_FromPtr(nativePtr, out X, out Y, out Z, out W);
        }

        public override String ToString()
        {
            return "(" + X + ", " + Y + ", " + Z + ", " + W + ")";
        }
    }
}
