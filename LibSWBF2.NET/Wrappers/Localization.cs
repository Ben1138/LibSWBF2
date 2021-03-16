using System;
using System.Runtime.InteropServices;
using System.Text;

namespace LibSWBF2.Wrappers
{
    public sealed class Localization : NativeWrapper
    {
        public string Name
        {
            get
            {
                CheckValidity();
                return Marshal.PtrToStringAnsi(APIWrapper.Localization_GetName(NativeInstance));
            }
        }

        public bool GetLocalizedWideString(string path, out string localizedUnicode)
        {
            localizedUnicode = null;
            IntPtr pathPtr = Marshal.StringToHGlobalAnsi(path);
            bool success = APIWrapper.Localization_GetLocalizedWideString(NativeInstance, pathPtr, out IntPtr chars, out uint charCount);
            if (success)
            {
                int byteCount = (int)charCount * sizeof(ushort);
                byte[] unicodeChars = new byte[byteCount];
                Marshal.Copy(chars, unicodeChars, 0, byteCount);

                localizedUnicode = Encoding.Unicode.GetString(unicodeChars);
            }
            Marshal.FreeHGlobal(pathPtr);
            return success;
        }
    }
}
