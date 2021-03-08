using System;
using System.Runtime.InteropServices;

namespace LibSWBF2.Wrappers
{
    public class Sound : NativeWrapper
    {
        internal Sound(IntPtr scriptPtr) : base(scriptPtr) { }

        public Sound() : base(IntPtr.Zero) { }

        public string Name
        {
            get
            {
                if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
                return Marshal.PtrToStringAnsi(APIWrapper.Sound_GetName(NativeInstance));
            }
        }

        public bool GetData(out uint sampleRate, out uint sampleCount, out byte blockAlign, out IntPtr data)
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
            return APIWrapper.Sound_GetData(NativeInstance, out sampleRate, out sampleCount, out blockAlign, out data);
        }

        public bool GetData(out uint sampleRate, out uint sampleCount, out byte blockAlign, out byte[] data)
        {
            if (!IsValid()) throw new Exception("Underlying native class is destroyed!");
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
