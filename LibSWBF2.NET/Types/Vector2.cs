using System;
using System.Runtime.InteropServices;

namespace LibSWBF2.Types
{
    [StructLayout(LayoutKind.Sequential, Pack=4)]
    public struct Vector2
    {
        public float X;
        public float Y;

        public unsafe Vector2(IntPtr nativePtr) : this()
        {
            if (nativePtr != IntPtr.Zero && nativePtr != null)
            {
                float* fPtr = (float*) nativePtr.ToPointer();
                X = *fPtr;
                Y = *(fPtr + 1);                
            }
        }

        public Vector2(float val = 0.0f)
        {
            X = val;
            Y = val;
        }

        public override String ToString()
        {
            return "(" + X + ", " + Y + ")";
        }
    }
}
