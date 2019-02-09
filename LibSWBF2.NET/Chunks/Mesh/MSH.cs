using System;
using System.Runtime.InteropServices;
using LibSWBF2.Logging;

namespace LibSWBF2.Chunks.Mesh
{
    public unsafe class MSH
    {
        [StructLayout(LayoutKind.Sequential)]
        internal struct NativeStruct
        {
            private BaseChunk.NativeStruct BaseChunk;

            public SHVO.NativeStruct ShadowVolume;
            public MSH2.NativeStruct MeshBlock;
            //TODO: public ANM2.NativeStruct Animations;
        }

        public IntPtr NativePtr { get { return (IntPtr)Ptr; } }
        private NativeStruct* Ptr;

        public SHVO ShadowVolume { get; private set; }
        public MSH2 MeshBlock { get; private set; }

        public static MSH CreateMSH()
        {
            MSH msh = new MSH();

            msh.Ptr = (NativeStruct*)APIWrapper.MSH_Create();
            if (msh.Ptr == null)
            {
                Logger.Log("MSH_Create returned NULL!", ELogType.Error);
                return null;
            }

            msh.ShadowVolume = new SHVO(&msh.Ptr->ShadowVolume);
            msh.MeshBlock = new MSH2(&msh.Ptr->MeshBlock);

            return msh;
        }

        private MSH()
        {

        }

        ~MSH()
        {
            APIWrapper.MSH_Delete(NativePtr);
        }

        public bool ReadFromFile(string path)
        {
            return APIWrapper.MSH_ReadFromFile(NativePtr, path);
        }

        public bool WriteToFile(string path)
        {
            return APIWrapper.MSH_WriteToFile(NativePtr, path);
        }
    }
}
