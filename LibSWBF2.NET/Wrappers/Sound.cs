using System;
using System.Runtime.InteropServices;

namespace LibSWBF2.Wrappers
{
    public sealed class Sound : NativeWrapper
    {
        public string Name
        {
            get
            {
                if (!IsValid()) CheckValidity();
                return Marshal.PtrToStringAnsi(APIWrapper.Sound_GetName(NativeInstance));
            }
        }

        public bool GetData(out uint sampleRate, out uint sampleCount, out byte blockAlign, out IntPtr data)
        {
            if (!IsValid()) CheckValidity();
            return APIWrapper.Sound_GetData(NativeInstance, out sampleRate, out sampleCount, out blockAlign, out data);
        }

        public bool GetData(out uint sampleRate, out uint sampleCount, out byte blockAlign, out byte[] data)
        {
            if (!IsValid()) CheckValidity();
            if (APIWrapper.Sound_GetData(NativeInstance, out sampleRate, out sampleCount, out blockAlign, out IntPtr dataPtr))
            {
                int dataSize = (int)(sampleCount * blockAlign);
                data = new byte[dataSize];
                Marshal.Copy(dataPtr, data, 0, dataSize);
                return true;
            }
            data = null;
            return false;
        }
    }
}
