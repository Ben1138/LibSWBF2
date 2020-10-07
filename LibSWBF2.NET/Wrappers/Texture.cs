using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using LibSWBF2.Utils;

namespace LibSWBF2.Wrappers
{
    public class Texture : NativeWrapper
    {
        private byte[] dataRGBA = null;

        public string name;
        public uint height, width;

        public bool isValidFormat = false;

        internal Texture(IntPtr TexturePtr) : base(TexturePtr)
        {
            SetPtr(TexturePtr);   
        }
        
        public Texture() : base(IntPtr.Zero){}

        internal override void SetPtr(IntPtr ptr)
        {
            NativeInstance = ptr;

            IntPtr namePtr;
            isValidFormat = APIWrapper.Texture_GetMetaData(NativeInstance, out height,
                                                            out width, out namePtr);
            name = Marshal.PtrToStringAnsi(namePtr);
        }

        public byte[] GetBytesRGBA()
        {
            if (dataRGBA == null && isValidFormat)
            {
                dataRGBA = MemUtils.IntPtrToArray<byte>(APIWrapper.Texture_GetBytes(NativeInstance),
                                                   (int) (width * height * 4));
            }

            return dataRGBA;
        } 
    }
}
