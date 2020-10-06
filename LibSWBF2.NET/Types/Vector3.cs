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

            if (nativePtr != IntPtr.Zero && nativePtr != null)
            {
                APIWrapper.Vector3_FromPtr(nativePtr, out X, out Y, out Z);
            }
            else 
            {
                X = 0.0f;
                Y = 0.0f;
                Z = 0.0f;
            }
        }

        public override String ToString()
        {
            return "(" + X + ", " + Y + ", " + Z + ")";
        }
    }
}
