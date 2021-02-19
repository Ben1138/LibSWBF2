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

        public byte[] dataRGBA;
        public bool IsConvertibleFormat;

        IntPtr NativeRawImageData;

        internal Texture(IntPtr TexturePtr) : base(TexturePtr) { SetPtr(TexturePtr); }
        public Texture() : base(IntPtr.Zero) { }


        internal override void SetPtr(IntPtr ptr)
        {
            NativeInstance = ptr;

            IsConvertibleFormat = APIWrapper.Texture_FetchAllFields(NativeInstance,
                                                        out int w, out int h,
                                                        out NativeRawImageData,
                                                        out IntPtr namePtr);

            width = w;
            height = h;
            dataRGBA = IsConvertibleFormat ? MemUtils.IntPtrToArray<byte>(NativeRawImageData, width * height * 4) : new byte[0];

            name = Marshal.PtrToStringAnsi(namePtr);
        }

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

        IntPtr GetNativeRawImageData()
        {
            return NativeRawImageData;
        }
    }
}