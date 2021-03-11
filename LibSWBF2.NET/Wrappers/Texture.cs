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
    public sealed class Texture : NativeWrapper
    {
        public string Name { get; private set; }
        public int    Height { get; private set; }
        public int    Width { get; private set; }
        public bool   IsConvertibleFormat { get; private set; }
        public IntPtr NativeRawImageData { get; private set; }


        internal override void SetPtr(IntPtr ptr)
        {
            base.SetPtr(ptr);
            IsConvertibleFormat = APIWrapper.Texture_FetchAllFields(NativeInstance,
                                                        out ushort w, out ushort h,
                                                        out IntPtr nativeRawImageData,
                                                        out IntPtr namePtr);
            Width = w;
            Height = h;
            Name = Marshal.PtrToStringAnsi(namePtr);
            NativeRawImageData = nativeRawImageData;
        }


        public byte[] GetBytesRGBA()
        {
            CheckValidity();
            
            int length = Width * Height * 4;
            return IsConvertibleFormat ? MemUtils.IntPtrToArray<byte>(NativeRawImageData, length) : new byte[length]; 
        }
    }
}