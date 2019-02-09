using System.Runtime.InteropServices;

namespace LibSWBF2.Chunks.Mesh
{
    public unsafe class MSH2
    {
        [StructLayout(LayoutKind.Sequential)]
        internal struct NativeStruct
        {
            private BaseChunk.NativeStruct BaseChunk;

            public SINF.NativeStruct SceneInformation;
            public MATL.NativeStruct MaterialList;
        }

        private NativeStruct* Ptr = null;
        public SINF SceneInformation { get; private set; }
        public MATL MaterialList { get; private set; }

        internal MSH2(NativeStruct* ptr)
        {
            Ptr = ptr;
            SceneInformation = new SINF(&ptr->SceneInformation);
            MaterialList = new MATL(&ptr->MaterialList);
        }
    }
}
