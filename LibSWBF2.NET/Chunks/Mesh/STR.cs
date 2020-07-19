using System.Runtime.InteropServices;
using LibSWBF2.Types;

namespace LibSWBF2.Chunks.Mesh
{
    public unsafe class STR
    {
        [StructLayout(LayoutKind.Sequential)]
        internal struct NativeStruct
        {
            private BaseChunk.NativeStruct BaseChunk;
            public String.NativeStruct Text;
        }

        private NativeStruct* Ptr = null;
        public String Name { get; private set; }

        internal STR(NativeStruct* ptr)
        {
            Ptr = ptr;
            Name = new String(&ptr->Text);
        }
    }
}
