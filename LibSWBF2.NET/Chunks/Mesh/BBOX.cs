using System.Runtime.InteropServices;
using LibSWBF2.Types;

namespace LibSWBF2.Chunks.Mesh
{
    public unsafe class BBOX
    {
        [StructLayout(LayoutKind.Sequential)]
        internal struct NativeStruct
        {
            private BaseChunk.NativeStruct BaseChunk;

            public Vector4.NativeStruct Quaternion;
            public Vector3.NativeStruct Center;
            public Vector3.NativeStruct Extend;
            public float SphereRadius;
        }

        private NativeStruct* Ptr = null;

        public Vector4 Quaternion { get; private set; }
        public Vector3 Center { get; private set; }
        public Vector3 Extend { get; private set; }
        public float SphereRadius
        {
            get { return Ptr->SphereRadius; }
            set { Ptr->SphereRadius = value; }
        }

        internal BBOX(NativeStruct* ptr)
        {
            Ptr = ptr;
            Quaternion = new Vector4(&ptr->Quaternion);
            Center = new Vector3(&ptr->Center);
            Extend = new Vector3(&ptr->Extend);
        }
    }
}
