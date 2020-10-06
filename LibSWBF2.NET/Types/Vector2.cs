using System;
using System.Runtime.InteropServices;

namespace LibSWBF2.Types
{
    public struct Vector2
    {
        public float X;
        public float Y;

        public Vector2(IntPtr nativePtr)
        {
        	APIWrapper.Vector2_FromPtr(nativePtr, out X, out Y);
        }

        public Vector2(float val = 0)
        {
            X = 0.0f;
            Y = 0.0f;
        }

        public override String ToString()
        {
            return "(" + X + ", " + Y + ")";
        }
    }
}
