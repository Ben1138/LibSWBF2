using System.Runtime.InteropServices;

namespace LibSWBF2.Chunks.Mesh
{
    public unsafe class SINF
    {
        [StructLayout(LayoutKind.Sequential)]
        internal struct NativeStruct
        {
            private BaseChunk.NativeStruct BaseChunk;

            public STR.NativeStruct Name;
            public FRAM.NativeStruct FrameInformation;
            public BBOX.NativeStruct BoundingBox;
        }

        private NativeStruct* Ptr = null;

        public STR Name { get; private set; }
        public FRAM FrameInformation { get; private set; }
        public BBOX BoundingBox { get; private set; }

        internal SINF(NativeStruct* ptr)
        {
            Ptr = ptr;
            Name = new STR(&ptr->Name);
            FrameInformation = new FRAM(&ptr->FrameInformation);
            BoundingBox = new BBOX(&ptr->BoundingBox);
        }
    }
}
