using System;
using System.Runtime.InteropServices;

namespace LibSWBF2.Chunks
{
    internal abstract class BaseChunk
    {
        [StructLayout(LayoutKind.Sequential)]
        internal struct NativeStruct
        {
            private int Header;
            private uint Size;
            private ulong ChunkDataPosition;

            // Member added by the C++ compiler. 
            // This is for no use in our Wrapper and can be ignored.
            // See: https://en.wikipedia.org/wiki/Virtual_method_table
            private IntPtr __vfptr;
        }
    }
}
