using System;
using System.Runtime.InteropServices;

namespace LibSWBF2.Types
{
    public unsafe class Vector2
    {
        [StructLayout(LayoutKind.Sequential)]
        internal struct NativeStruct
        {
            public float X;
            public float Y;

            // For more details see BacseChunk.NativeStruct.__vfptr
            private IntPtr __vfptr;
        }

        private NativeStruct* Ptr = null;

        public float X
        {
            get { return Ptr->X; }
            set { Ptr->X = value; }
        }
        public float Y
        {
            get { return Ptr->Y; }
            set { Ptr->Y = value; }
        }

        internal Vector2(NativeStruct* ptr)
        {
            Ptr = ptr;
        }
    }
}
