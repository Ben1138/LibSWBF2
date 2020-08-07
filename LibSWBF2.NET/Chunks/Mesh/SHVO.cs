using System.Runtime.InteropServices;

namespace LibSWBF2.Chunks.Mesh
{
    public unsafe class SHVO
    {
        [StructLayout(LayoutKind.Sequential)]
        internal struct NativeStruct
        {
            private BaseChunk.NativeStruct BaseChunk;

            public int ShadowVolume;
        }

        private NativeStruct* Ptr = null;

        public int ShadowVolume
        {
            get { return Ptr->ShadowVolume; }
            set { Ptr->ShadowVolume = value; }
        }

        internal SHVO(NativeStruct* ptr)
        {
            Ptr = ptr;
        }
    }
}
