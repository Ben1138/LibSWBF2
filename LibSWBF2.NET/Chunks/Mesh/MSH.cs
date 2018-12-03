using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LibSWBF2.Chunks.Mesh
{
    public class MSH
    {
        public IntPtr NativePtr { get; private set; }


        public MSH()
        {
            NativePtr = APIWrapper.MSH_Create();
        }

        ~MSH()
        {
            APIWrapper.MSH_Delete(NativePtr);
        }

        public bool ReadFromFile(string path)
        {
            return APIWrapper.MSH_ReadFromFile(NativePtr, path);
        }
    }
}
