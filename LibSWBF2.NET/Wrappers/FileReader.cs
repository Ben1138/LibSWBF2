using System;
using System.Runtime.InteropServices;

namespace LibSWBF2.Wrappers
{
    public sealed class FileReader : NativeWrapper
    {
        public static FileReader FromFile(string Path, bool UseMemoryMapping = false)
        {
            return FromNative<FileReader>(APIWrapper.FileReader_FromFile(Path, UseMemoryMapping));
        }

        public IntPtr GetNativePtr()
        {
            CheckValidity();
            return NativeInstance;
        }

        ~FileReader()
        {
            //CheckValidity();
            APIWrapper.FileReader_Delete(NativeInstance);
            Invalidate();
        }
    }
}
