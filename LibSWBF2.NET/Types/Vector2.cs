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

        public override String ToString()
        {
            return "(" + X + ", " + Y + ")";
        }
    }
}
