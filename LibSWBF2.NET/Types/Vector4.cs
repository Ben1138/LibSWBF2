using System;
using System.Runtime.InteropServices;

namespace LibSWBF2.Types
{
    public unsafe class Vector4
    {
        [StructLayout(LayoutKind.Sequential)]
        internal struct NativeStruct
        {
            public float X;
            public float Y;
            public float Z;
            public float W;

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
        public float Z
        {
            get { return Ptr->Z; }
            set { Ptr->Z = value; }
        }
        public float W
        {
            get { return Ptr->W; }
            set { Ptr->W = value; }
        }

        internal Vector4(NativeStruct* ptr)
        {
            Ptr = ptr;
        }
    }
}
