using System;
using System.Runtime.InteropServices;


using LibSWBF2.Enums;

namespace LibSWBF2.Wrappers
{
    public sealed class Sound : NativeWrapper
    {
        public uint         Name { get; private set; }
        public ESoundFormat Format { get; private set; }
        public int          NumChannels { get; private set; }
        public int          SampleRate { get; private set; }
        public int          NumSamples { get; private set; }
        public uint         Alias { get; private set; }
        public bool         HasData { get; private set; }


        internal override void SetPtr(IntPtr soundPtr)
        {
            base.SetPtr(soundPtr);
            if (APIWrapper.Sound_FetchAllFields(soundPtr, out uint format, 
                                                out int numChannels, out int sampleRate,
                                                out int numSamples, out uint alias, 
                                                out bool hasData, out uint name))
            {
                Format = (ESoundFormat) format;
                NumChannels = numChannels;
                SampleRate = sampleRate;
                NumSamples = numSamples;
                Alias = alias;
                HasData = hasData;
                Name = name;
            }
        }


        public bool GetData(out uint sampleRate, out uint sampleCount, out byte blockAlign, out IntPtr data)
        {
            CheckValidity();
            return APIWrapper.Sound_GetData(NativeInstance, out sampleRate, out sampleCount, out blockAlign, out data);
        }

        public bool GetData(out uint sampleRate, out uint sampleCount, out byte blockAlign, out byte[] data)
        {
            CheckValidity();
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


        public short[] GetPCM16()
        {
            CheckValidity();
            short[] buffer = new short[NumSamples * NumChannels];
            bool result;
            unsafe
            {
                fixed (short* destPtr = buffer)
                {
                    result = APIWrapper.Sound_FillDataBuffer(NativeInstance, destPtr);
                }
            }  

            return result ? buffer : new short[0];             
        }
    }
}
