using System;
using System.Runtime.InteropServices;

namespace LibSWBF2.Types
{
    [StructLayout(LayoutKind.Sequential, Pack=4)]
    public struct Vector3
    {
        public float X;
        public float Y;
        public float Z;

        public unsafe Vector3(IntPtr nativePtr) : this()
        {
            if (nativePtr != IntPtr.Zero && nativePtr != null)
            {
                float* fPtr = (float*) nativePtr.ToPointer();
                X = *fPtr;
                Y = *(fPtr + 1);                
                Z = *(fPtr + 2);                
            }
        }

        public override String ToString()
        {
            return "(" + X + ", " + Y + ", " + Z + ")";
        }

        public float Magnitude()
        {
            return (float) Math.Sqrt(X * X + Y * Y + Z * Z);
        }
    }
}
