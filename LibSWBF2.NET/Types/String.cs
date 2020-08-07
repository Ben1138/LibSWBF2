using System;
using System.Runtime.InteropServices;

namespace LibSWBF2.Types
{
    public unsafe class String
    {
        [StructLayout(LayoutKind.Sequential)]
        internal struct NativeStruct
        {
            public IntPtr buffer;
            public ulong length;

            // For more details see BacseChunk.NativeStruct.__vfptr
            private IntPtr __vfptr;
        }

        private NativeStruct* Ptr = null;
        internal String(NativeStruct* ptr)
        {
            Ptr = ptr;
        }

        public static implicit operator string(String str)
        {
            return Marshal.PtrToStringAnsi(str.Ptr->buffer, (int)str.Ptr->length);
        }
    }
}
