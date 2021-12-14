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

        public unsafe Vector4(IntPtr nativePtr) : this()
        {
            if (nativePtr != IntPtr.Zero && nativePtr != null)
            {
                float* fPtr = (float*) nativePtr.ToPointer();
                X = *fPtr;
                Y = *(fPtr + 1);                
                Z = *(fPtr + 2);                
                W = *(fPtr + 3);                
            }
        }

        public override String ToString()
        {
            return "(" + X + ", " + Y + ", " + Z + ", " + W + ")";
        }

        public float Magnitude()
        {
            return (float) Math.Sqrt(X * X + Y * Y + Z * Z + W * W);
        }
    }
}