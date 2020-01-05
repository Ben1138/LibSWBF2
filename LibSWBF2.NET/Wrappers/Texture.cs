using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using LibSWBF2.Utils;
using LibSWBF2.Enums;

namespace LibSWBF2.Wrappers
{
    public class Texture : NativeWrapper
    {
        public string name = "";
        public int height = 0, width = 0;

        private byte[] dataRGBA;
        private bool IsConvertibleFormat = false;

        internal Texture(IntPtr TexturePtr) : base(TexturePtr) { SetPtr(TexturePtr); }
        public Texture() : base(IntPtr.Zero){}


        internal override void SetPtr(IntPtr ptr)
        {
            NativeInstance = ptr;

            IsConvertibleFormat = APIWrapper.Texture_GetData(NativeInstance, out int w,
                                                    out int h, out IntPtr bufferPtr);
            if (IsConvertibleFormat)
            {
                width = w;
                height = h;
                dataRGBA = MemUtils.IntPtrToArray<byte>(bufferPtr, width * height * 4);
            }
            else 
            {
                Console.WriteLine("Format cannot be converted to RGBA");
            }

            APIWrapper.Texture_GetMetadata(NativeInstance, out w, out h, out IntPtr namePtr);
            name = Marshal.PtrToStringAnsi(namePtr);
        }

        /*
        Eventually, I'll write better functions that preallocate a managed byte array,
        which is then filled by a memcpy/DumpRGBA on the unmanaged side... 
        */

        // Get bytes in the texture's existing format
        /*
        public byte[] GetBytesRaw()
        {
            return null;
        }
        */

        // Get bytes of texture after converting to RGBA32
        public byte[] GetBytesRGBA()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            
            if (!IsConvertibleFormat)
            {
                return new byte[width * height * 4];
            }
            else 
            {
                return dataRGBA;
            }
        } 
    }
}