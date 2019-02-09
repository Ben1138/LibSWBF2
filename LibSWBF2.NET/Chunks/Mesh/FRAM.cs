using System.Runtime.InteropServices;

namespace LibSWBF2.Chunks.Mesh
{
    public unsafe class FRAM
    {
        [StructLayout(LayoutKind.Sequential)]
        internal struct NativeStruct
        {
            private BaseChunk.NativeStruct BaseChunk;
            public int FrameRangeStart;
            public int FrameRangeEnd;
            public float FramesPerSecond;
        }

        private NativeStruct* Ptr = null;

        public int FrameRangeStart
        {
            get { return Ptr->FrameRangeStart; }
            set { Ptr->FrameRangeStart = value; }
        }
        public int FrameRangeEnd
        {
            get { return Ptr->FrameRangeEnd; }
            set { Ptr->FrameRangeEnd = value; }
        }
        public float FramesPerSecond
        {
            get { return Ptr->FramesPerSecond; }
            set { Ptr->FramesPerSecond = value; }
        }

        internal FRAM(NativeStruct* ptr)
        {
            Ptr = ptr;
        }
    }
}
