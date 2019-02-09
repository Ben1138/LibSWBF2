using System.Runtime.InteropServices;

namespace LibSWBF2.Chunks.Mesh
{
    public unsafe class MATD
    {
        [StructLayout(LayoutKind.Sequential)]
        internal struct NativeStruct
        {
            private BaseChunk.NativeStruct BaseChunk;
        }

        private NativeStruct* Ptr = null;

        internal MATD(NativeStruct* ptr)
        {
            Ptr = ptr;
        }
    }
}
