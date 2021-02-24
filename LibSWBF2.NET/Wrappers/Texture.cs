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
        public int height, width;

        public bool IsConvertibleFormat;

        private IntPtr NativeRawImageData;

        internal Texture(IntPtr TexturePtr) : base(TexturePtr) { SetPtr(TexturePtr); }
        public Texture() : base(IntPtr.Zero) { }


        internal override void SetPtr(IntPtr ptr)
        {
            NativeInstance = ptr;

            IsConvertibleFormat = APIWrapper.Texture_FetchAllFields(NativeInstance,
                                                        out ushort w, out ushort h,
                                                        out NativeRawImageData,
                                                        out IntPtr namePtr);
            width = w;
            height = h;

            name = Marshal.PtrToStringAnsi(namePtr);
        }


        public byte[] GetBytesRGBA()
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            
            int length = width * height * 4;
            return IsConvertibleFormat ? MemUtils.IntPtrToArray<byte>(NativeRawImageData, length) : new byte[length]; 
        }


        IntPtr GetNativeRawImageData()
        {
            return NativeRawImageData;
        }
    }
}