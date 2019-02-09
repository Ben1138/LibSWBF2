using System.Runtime.InteropServices;

namespace LibSWBF2.Chunks.Mesh
{
    public unsafe class MATL
    {
        [StructLayout(LayoutKind.Sequential)]
        internal struct NativeStruct
        {
            private BaseChunk.NativeStruct BaseChunk;
        }

        private NativeStruct* Ptr = null;

        internal MATL(NativeStruct* ptr)
        {
            Ptr = ptr;
        }
    }
}
